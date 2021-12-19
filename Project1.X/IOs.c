//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
//In IOs.c, IOinit() configures all input and outputs and allows for interrupts to occur
//Meanwhile, the CN interrupt sets the appropriate flag to high if a specific button is pressed
//IOcheck()checks if any of the flags were set high by a CN interrupt, and calls the appropriate delay function between LED on/LED off cycles based on that flag
#include <xc.h>
#include "IOs.h"

//global variable flags to track when a specific pushbutton has been pressed (pressed==1)
int PB1Flag = 0;    //flag for RA2
int PB2Flag = 0;    //flag for RA4
int PB3Flag = 0;    //flag for RB4
int allFlag = 0;    //flag for all pressed

void IOinit(void){
    AD1PCFG = 0xFFFF;       //all analog pins digital
    
    //Inputs RA2, RA4 AND RB4
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    //Output LED on RB8
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

void IOcheck(void){
    while(1){               
    if(PB1Flag == 1){       //check if PB1 (RA2) flag on from interrupt
        
        LATBbits.LATB8 = 1;     //turn on LED output
        Delay_ms(1000);         //delay by 1 second
        LATBbits.LATB8 = 0;     //turn off LED output
        Delay_ms(1000);         //delay by 1 second
        LATBbits.LATB8 = 1;     //turn on LED
        
    }
    else if(PB2Flag == 1){      //if PB2 (RA4) flag on from interrupt
        //Delay_ms(2000);
          LATBbits.LATB8 = 1;       //turn on LED
        Delay_ms(2000);             //delay by 2 seconds
        LATBbits.LATB8 = 0;         //turn off LED
        Delay_ms(2000);             //delay 2 seconds
        LATBbits.LATB8 = 1;         //turn on LED
    }
    else if(PB3Flag == 1){      //if PB3 (RB4) flag on from interrupt)
          LATBbits.LATB8 = 1;   //turn on light
        Delay_ms(3000);         //DELAY 3 SECONDS
        LATBbits.LATB8 = 0;     //turn off light
        Delay_ms(3000);            //delay 3 seconds
        LATBbits.LATB8 = 1;         //turn on light
       // Delay_ms(3000);
    }
    else if(allFlag == 1){      //if allflag on 
        LATBbits.LATB8 = 1;     //continuous led on
    }
    else{
        LATBbits.LATB8 = 0;     //if none of the above conditions met, no lights should be on
    }
    }
}


void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){    //CN interrupt to detect if a press button is physically pressed
    
    if(IFS1bits.CNIF == 1){
        
        if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){             //if RA2 was pressed
              PB1Flag = 1;                                                          //turn on PB1flag
            //clear any non-PB1 existing flags
              PB2Flag = 0;                                                             
            PB3Flag = 0;
           
        }
        
        //if RA4 caused interrupt
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 ==0 && PORTBbits.RB4 == 1){
            //turn on PB2 flag
            PB2Flag = 1;
            //clear any other existing flags
            PB1Flag = 0;
            PB3Flag = 0;
        }
        //if rb4 caused interrupt
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
            //turn on pb3flag
            PB3Flag = 1;
            //clear any other existing flags
            PB1Flag = 0;
            PB2Flag = 0;
        }
        //if no buttons
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){
            //clear all flags
            PB1Flag = 0;
            PB2Flag = 0;
            PB3Flag = 0;
            allFlag = 0;
        }
        //else condition, ie. multiple buttons together triggered interrupt
        else{
            //set allflag to high
            allFlag = 1;
            //clear any existing individual flags
            PB1Flag = 0;
            PB2Flag = 0;
          PB3Flag = 0;
            
        }
    }
    //clear CN interrupt
    IFS1bits.CNIF = 0;
    
    
}
