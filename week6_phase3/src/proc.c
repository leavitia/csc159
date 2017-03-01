// proc.c, 159
// all processes are coded here
// processes do not use kernel space (data.h) or code (handlers, tools, etc.)
// all must be done thru system service calls

#include "services.h"
#include "spede.h"      // cons_xxx below needs
#include "data.h"       // current_pid needed below
#include "proc.h"       // prototypes of processes

// Init PID 1, always ready to run, never preempted
void Init(void) {
  int i;

  while(1){
	//  cons_printf("%d..", 1); //show on Target PC: "1.." (since Init has PID 1 as we know)      
	  for(i=0; i<FAST_LOOP; i++){ //loop for LOOP times { // to cause approx 1 second of delay
      asm("inb $0x80"); // call asm("inb $0x80") which delay .6 microsecond
    }
  }
}

// PID 2, 3, 4, etc. mimicking a usual user process
void UserProc(void) {
  int pid;
  pid = GetPid();
  
  while(1){
    int sleep_amount = (pid %5) + 1; 
	  cons_printf("%d..", pid); //show on Target PC: "%d..", current_pid 
	  Sleep(sleep_amount);
  }
}

void Vehicle(void){ //phase 3 tester (multiple processes)
  int i, my_pid;

  if(vehicle_sid == -1){
    vehicle_sid = SemAlloc(3); //max passes 3
  }
  my_pid = GetPid();

  while(1){
    ch_p =(unsigned short *)0xB8000 + my_pid * 80 + 45;
    *ch_p = 0xf00 + 'f';  //show i'm off the bridge
    
    for(i =0; i<FAST_LOOP; i++){           //spend a sec in RUN state
      asm("inb $0x80");           
    }
    SemWait(vehicle_sid);           //ask for a pass
    ch_p = (unsigned short *)0xB8000 + my_pid * 80 + 45;
    *ch_p = 0xf00 + 'o'; //show i'm on the bridge
    Sleep(1);
    SemPost(vehicle_sid);             //return the pass
  }
}