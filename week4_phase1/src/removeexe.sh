#!/bin/bash

# remove files so env is clean for spede-mkmf execution
rm GDB159.RC
rm Makefile
rm make.orig
rm main.o
rm tools.o
rm handlers.o
rm events.o
rm MyOS.dli
rm proc.o
#spede-mkmf -q
#sed -ie 's/MyOS/GidOS/g' Makefile
#make
