/*
  * Integrantes:
  * * Eric Alejandro Ramírez Juárez
  * * Claudia Espinosa Gúzman 
  * * Miguel Alejandro Gútierrez Silva
  * Práctica 1: Mapeo de direcciones en nachOS
  * Fecha: 28/02/2025
*/

// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"

#define UserStackSize		1024 	// increase this as necessary!

#define SwapNameSize		256 // Size of the swap file name

class AddrSpace {
  public:
  char swapFileName[SwapNameSize]; // Name of the swap file
    
    AddrSpace(OpenFile *executable, char* filename);	// Create an address space,
					// initializing it with the program
					// stored in the file "executable"
    ~AddrSpace();			// De-allocate an address space

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch 
    void createSwapFile(OpenFile *executable, char* filename);
    
    void createRevFile(OpenFile *executable, char* filename);

    void SwapIn();			// Swap in a page from the swap file
          // into the main memory

    void SwapOut(int pageNumber);	// Swap out a page from the main memory
          // into the swap file

    void PrintPageTable();

  private:
    TranslationEntry *pageTable;	// Assume linear page table translation
					// for now!
    unsigned int numPages;		// Number of pages in the virtual 
					// address space
};

#endif // ADDRSPACE_H
