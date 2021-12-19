//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
//In IOs.c, IOinit() configures all input and outputs and allows for interrupts to occur
//Meanwhile, the CN interrupt sets the appropriate flag to high if a specific button is pressed
//IOcheck()checks if any of the flags were set high by a CN interrupt, and calls the appropriate delay function between LED on/LED off cycles based on that flag
//debounceCheck() creates small delay and re-checks if the states changed. If changed, then it re-evaluates in the loop and ignores the previous states)
#include <xc.h>
#include "IOs.h"
#include "UART2.h"
#include <stdio.h>

int PB1Flag = 0;
int PB2Flag = 0;
int PB3Flag = 0;
int allFlag = 0;

void IOinit(void){
    AD1PCFG = 0xFFFF;
    
    //Inputs
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    //Output
    TRISBbits.TRISB8 = 0;
    
    //Enable interrupt for pin RA2
    CNEN2bits.CN30IE = 1;
    //Enable interrupt for pin RA4
    CNEN1bits.CN0IE = 1;
    //Enable interrupt for pin RB4
    CNEN1bits.CN1IE = 1;
    
    //Enable CN bits for RA2
    CNPU2bits.CN30PUE = 1;
    //Enable CN bits for RA4
    CNPU1bits.CN0PUE = 1;
    //Enable CN bits for RB4
    CNPU1bits.CN1PUE = 1;
    
    //Allow for interrupts to occur
    IEC1bits.CNIE = 1;
    //Set priority level
    IPC4bits.CNIP = 3;
    //Clear interrupt flag
    IFS1bits.CNIF = 0;
}
//debounce check function that produces slight delay and then checks if states remain smae after
//returns true(1) if states remain same, false(0) if states did change after slight delay (thus debounce))
int debounceCheck(int state1, int state2, int state3) {
    //delay short period
    Delay_ms(100);
    //check if states remain same after slight delay
    if(PB1Flag!=state1 || PB2Flag !=state2 || PB3Flag!=state3){
      //return false
        return 0;
    }
    //return true
    return 1;
}

void IOcheck(void){
    while(1){
        //top label to re-evaluate states if debounced
        top:
        //All buttons are pressed
        if(allFlag == 1){
            //check for debounce effects
            debounceCheck(1, 1, 1);
            //led on
            LATBbits.LATB8 = 1;
            //debounceCheck(1,1, 1);
        }

        //PB1 and PB2 are pressed
        else if(PB1Flag == 1 && PB2Flag == 1 && PB3Flag == 0){
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            if(!debounceCheck(1, 1, 0)){goto top;}
            //led on
            LATBbits.LATB8 = 1;
            
            
        }

        //PB1 and PB3 are pressed
        else if(PB1Flag == 1 && PB2Flag == 0 && PB3Flag == 1){
            //Delay_ms(100);
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            if(debounceCheck(1, 0, 1)==0) {goto top;}
            //led on
            LATBbits.LATB8 = 1;
           
        }

        //PB2 and PB3 are pressed
        else if(PB2Flag == 1 && PB1Flag == 0 && PB3Flag == 1){
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            
            if(debounceCheck(0, 1, 1)==0) {goto top;}
            //LED on
            LATBbits.LATB8 = 1;
            
        }
        
        
        //Only PB1 is pressed 
        else if(PB1Flag == 1 && PB2Flag == 0 && PB3Flag == 0){
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            if(!debounceCheck(1,0,0)){goto top;}
            //TURN ON led
            LATBbits.LATB8 = 1;
            //DELAY 500 MS
            Delay_ms(500);
            //turn LED off
            LATBbits.LATB8 = 0;
            //delay 500 ms
            Delay_ms(500);
            //turn on LED
            LATBbits.LATB8 = 1;
            
        }

        //Only PB2 is pressed
        else if(PB2Flag == 1 && PB1Flag == 0 && PB3Flag == 0){
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            if(!debounceCheck(0, 1, 0)){goto top;}
            //turn on LED
            LATBbits.LATB8 = 1;
            //delay 2000 ms
            Delay_ms(2000);
            //turn off LED
            LATBbits.LATB8 = 0;
            //delay 2000 ms
            Delay_ms(2000);
            //turn on LED
            LATBbits.LATB8 = 1;
            
        }

        //Only PB3 is pressed
        else if(PB3Flag == 1 && PB1Flag == 0 && PB2Flag == 0){
            //if debouncecheck false (ie. states changed after small delay), goto top to reevaluate new states
            if(debounceCheck(0, 0, 1)==0) {goto top;} 
            //Delay_ms(100);
            //turn on LED
            LATBbits.LATB8 = 1;
            //delay 3000 ms
            Delay_ms(3000);
            //turn off LED
            LATBbits.LATB8 = 0;
            //delay 3000 ms
            Delay_ms(3000);
            //turn on LED
            LATBbits.LATB8 = 1;
            
        }

        //No PBs are pressed
        else{
            //no LED on
            LATBbits.LATB8 = 0; 
            
        }
    }
}


void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        //Delay_ms(3000);
        //RA2 pressed
        if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){             //100
           //turn on PB1 flag
            PB1Flag = 1;
            //clear all other flags
           PB2Flag = 0;
           PB3Flag = 0;
           allFlag = 0;
           //display to screen 
           Disp2String("\n\rPB1 is pressed.");
        }
        
        //RA4 pressed
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 ==0 && PORTBbits.RB4 == 1){
            //turn on PB2 flag
            PB2Flag = 1;
            //turn off all other flags
            PB1Flag = 0;
            PB3Flag = 0;
            allFlag = 0;
            //display to screen
            Disp2String("\n\rPB2 is pressed.");
        }
        
        //RB4 pressed
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
            //turn on PB3 flag
            PB3Flag = 1;
            //clear all other flags
            PB1Flag = 0;
            PB2Flag = 0;
            allFlag = 0;
            //display to screen
            Disp2String("\n\rPB3 is pressed.");
        }
        
        //All on
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0){
            //set all flag hi
            allFlag = 1;
            //clear other flags
            PB1Flag = 0;
            PB2Flag = 0;
            PB3Flag = 0;
  //display to screen
            Disp2String("\n\rAll PBs pressed.");
        }
        
        //RA2 and RA4
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 1){
            //clear flags
            allFlag = 0;
            //set PB1 and PB2 high
            PB1Flag = 1;
            PB2Flag = 1;
            //clear flag
            PB3Flag = 0;
//display to screen
            Disp2String("\n\rPB1 and PB2 are pressed.");
        }
        
        //RA2 and RB4
        else if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
            //clear flags, set PB1 and PB3 high
            allFlag = 0;
            PB1Flag = 1;
            PB2Flag = 0;
            PB3Flag = 1;
            //display to screen
            Disp2String("\n\rPB1 and PB3 are pressed.");
        }
        
        //RA4 and RB4
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 0 && PORTBbits.RB4 == 0){
            //clear flags
            allFlag = 0;
            PB1Flag = 0;
            //set PB2 and PB3 flags hi
            PB2Flag = 1;
            PB3Flag = 1;
//display
            Disp2String("\n\rPB2 and PB3 are pressed.");
        }
        
        //All off
        else{
            //clear all flags
            allFlag = 0;
            PB1Flag = 0;
            PB2Flag = 0;
            PB3Flag = 0;
//display
            Disp2String("\n\rNo PBs are pressed.");
        }
    }
    //clear CN interrupt
    IFS1bits.CNIF = 0;
    
    
}

