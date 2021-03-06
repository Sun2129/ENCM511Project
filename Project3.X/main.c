


/*
 * File:   main.c
//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
 */

//Lines 7-30 macros, etc. provided by main file on D2L
// MPLAB header libraries
#include <xc.h>

#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>

// User header files
#include "IOs.h"
#include "ChangeClk.h"


//Preprocessor directives - Configuration bits for MCU start up
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled


// MACROS for Idle, Sleep modes
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   //Sleep() - put MCU in sleep mode - CPU and some peripherals off
#define Idle() {__asm__ volatile ("pwrsav #1");}    //Idle() - put MCU in idle mode - only CPU off
#define dsen() {__asm__ volatile ("BSET DSCON, #15");} //

//MAIN
void main(void) {
    //initialize IO and UART modules
    IOinit();
    InitUART2();
    // Change Clock
     NewClk(8); // 8 for 8 MHz; 500 for 500 kHz; 32 for 32 kHz
     
   // Initialize IOs for low-power wake-up
    AD1PCFG = 0xFFFF; // Turn all analog pins as digital
    
    while(1)
    {
           //continuos check of IO pins
        IOcheck();
       
    }
    
    
    return;
}


