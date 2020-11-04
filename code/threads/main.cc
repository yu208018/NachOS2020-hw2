// main.cc 
//	Driver code to initialize, selftest, and run the 
//	operating system kernel.  
//
// Usage: nachos -u -z -d <debugflags> ...
//   -u prints entire set of legal flags
//   -z prints copyright string
//   -d causes certain debugging messages to be printed (cf. debug.h)
//
//  NOTE: Other flags are defined for each assignment, and
//  incorrect flag usage is not caught.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#define MAIN
#include "copyright.h"
#undef MAIN

#include "main.h"

// global variables
KernelType *kernel;
Debug *debug;


//----------------------------------------------------------------------
// Cleanup
//	Delete kernel data structures; called when user hits "ctl-C".
//----------------------------------------------------------------------

static void 
Cleanup(int x) 
{     
    cerr << "\nCleaning up after signal " << x << "\n";
    delete kernel; 
}


//----------------------------------------------------------------------
// main
// 	Bootstrap the operating system kernel.  
//	
//	Initialize kernel data structures
//	Call selftest procedure
//	Run the kernel
//
//	"argc" is the number of command line arguments (including the name
//		of the command) -- ex: "nachos -d +" -> argc = 3 
//	"argv" is an array of strings, one for each command line argument
//		ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}
//----------------------------------------------------------------------

int
main(int argc, char **argv)
{
    int i;
    char *debugArg = "";

    debug = new Debug(debugArg);
    
    DEBUG(dbgThread, "Entering main");

    SchedulerType type = RR;
    if(strcmp(argv[1], "FCFS") == 0) {
    type = FIFO;
    } else if (strcmp(argv[1], "SJF") == 0) {
    type = SJF;
    } else if (strcmp(argv[1], "PRIORITY") == 0) {
    type = Priority;
    } else if (strcmp(argv[1], "RR") == 0) {
    type = RR;
    }

    kernel = new KernelType(argc, argv);
    kernel->Initialize();
    
    CallOnUserAbort(Cleanup);		// if user hits ctl-C

    kernel->SelfTest();
    kernel->Run();
    
    return 0;
}

