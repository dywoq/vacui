//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      This header provides printing functionality.
// 
// Environment
// 
//      VQBoot primary stage
//

#ifndef PRINT_H
#define PRINT_H

//
// Routine Description
//
//      Iterates over the string characters and prints them using
//      PrimaryPrintChar function. Returns if it encounters a 
//      null-terminator. Returns if MessagePtr is null.
//
// Parameters
// 
//      MessagePtr
// 
//          The null-terminated string to print.
//
void
PrimaryPrintMsg(const char *MessagePtr);

//
// Routine Description
// 
//      Generates a BIOS interrupt (Teletype Output) putting a character 
//      into the AL register.
// 
// Parameters
// 
//      Character
// 
//          The character to print.
// 
void
PrimaryPrintChar(char Character);

#endif
