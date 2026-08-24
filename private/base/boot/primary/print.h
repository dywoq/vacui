//
// Copyright 2026 dywoq - Apache License 2.0
// https://github.com/dywoq/vacui
//
// Module Description
//
//      Printing functionality
// 
// Environment
// 
//      VQBoot primary stage
//

#ifndef PRINT_H
#define PRINT_H

//
// Module Description
//
//      Iterates over the string characters and prints them using
//      PrimaryPrintChar function. Returns if it encountered a 
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
// Module Description
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
