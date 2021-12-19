/*
 * File:   IOs.c
//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
 */

#include <xc.h>
#include "IOs.h"
#include "UART2.h"
#include <stdio.h>
//pushbutton global flags - set lo initial
int PB1Flag = 0;
int PB2Flag = 0;
int PB3Flag = 0;
//counter for while loop
int while_count = 0;
//signal alarm variable
int ALARM = 0;
//signal countdown variable
int COUNTDOWN = 0;
//signal start variable
int start = 0;
//signal pause variable
int pause = 1;
//misc. flags
int flagg = 0;
int flaggg = 0;
//minutes variable
unsigned int minutes = 0;
//seconds variable
unsigned int seconds = 0;

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

void IOcheck(void){
    while(1){
        //Disp2Hex(PB3Flag);
        
        //Only PB1 is pressed ...SETTING THE MINUTES before countdown
        if(PB1Flag == 1 && PB2Flag == 0){
            //ensure light is off
            LATBbits.LATB8 = 0;
            //alarm off
            ALARM = 0;
            //once minutes hits 59, set back to one
            if(minutes == 59){
                minutes = 0;
            }
            //otherwise increment minutes by one
            else{
                minutes = minutes + 1;
            }
            //delay 2000 ms (slow enough for user to easily select required minute)
            Delay_ms(2000);            
        }

        //Only PB2 is pressed...SETTING SECONDS before countdown
        else if(PB2Flag == 1 && PB1Flag == 0){
            //ensure light off
            LATBbits.LATB8 = 0;
            //alarm off
            ALARM = 0;
            //if seconds 59, set minutes to 0 and increment minute
            if(seconds == 59){
                seconds = 0;
                minutes = minutes + 1;
            }
            //else increment seconds
            else{
                seconds = seconds + 1;
            }
            //delay 2000 ms for slow enough selection of seconds
            Delay_ms(2000);
        }
        
        //If we need to start the countdown(start=true and pause=false)
        else if(start == 1 && pause == 0){
            //this is the countdown logic!
            
            //while minutes greater than or equal to 0
            while(minutes >= 0){
                //if pause flag high, break out of while (stop decrementing minutes)
                if(pause==1) {break;}
                //while seconds greater than/equal to 1
                while(seconds >= 1){
//                  if pause flag set high, break out of seconds increment
                    if(pause==1) { break;}
                    //decrement seconds
                     seconds = seconds - 1;     //added 11-07
                    //turn on light
                     LATBbits.LATB8 = 1;
                     //delay one second
                    Delay_ms(1000);
                    //turn off light
                    LATBbits.LATB8 = 0;
                    //delay one second
                    Delay_ms(1000);
                    
                    

                    //carriage return
                    Disp2String("\r");
            
                    //logic to print minutes to screen
                    //if minutes < 10, print 0 then minute value 
                    if(minutes < 10){
                        Disp2String("0");
                        Disp2Dec(minutes);
                    }
                    //display minute to screen
                    else{
                        Disp2Dec(minutes);
                    }
                    //display m: to signify minute portion
                    Disp2String("m ; ");

                    //logic to display seconds
                    //if seconds<10, display 0 before seconds
                    if(seconds < 10){
                        Disp2String("0");
                        Disp2Dec(seconds);
                    }
                    //display seconds
                    else{
                        Disp2Dec(seconds);
                    }
                    //display s: to signify seconds part of number displayed
                    Disp2String("s");
                
                }
                //outside of second decrement while loop!(second's break goes here))
                
                //if pause high, break out of outer loop(minute decrement))
                if(pause==1){break;}
                //when seconds switches from 0 to 59, decrement minutes by 1
                //ensure this doesn't occur when minutes is 0 (ie. minutes-1==-1)
                if(minutes-1 != -1) {
                minutes = minutes - 1;
                
                seconds = 59;
                //light on
                LATBbits.LATB8 = 1;
                //delay 1 second
                Delay_ms(1000);
                //light off
                LATBbits.LATB8 = 0; 
                //carriage return
                Disp2String("\r");
                }
                //break otherwise
                else{break;}
                
                //logic to display minutes
                //if minutes <10, print 0 first (eg 04 for 4))
                if(minutes < 10){
                    Disp2String("0");
                    Disp2Dec(minutes);
                }
                //display minutes
                else{
                    Disp2Dec(minutes);
                }
                //display m: to show minutes
                Disp2String("m ; ");
                //if seconds<10, print 0 before seconds value
                if(seconds < 10){
                    Disp2String("0");
                    Disp2Dec(seconds);
                }
                //print seconds value
                else{
                    Disp2Dec(seconds);
                }
                Disp2String("s");
                
            }
            
            /*if start hasn't been restarted and it hasn't been paused and we've reached the end...
             then set the ALARM on */
            if(start!=2&&pause!=1) {
                //alarm on
            ALARM = 1;
            //start now false (countdown over)
            start = 0;
            //countdown false
            COUNTDOWN = 0;
            }
           
        }
      
        
        //If we need to pause the countdown
       //if countdown started and puase is high
        else if(start == 1 && pause == 1){
            //turn off LED
            LATBbits.LATB8=0;
           
           
         }
        
        //If we need to reset the countdown
        else if(start == 2){
           //countdown now off
            COUNTDOWN = 0;
            //start back to begin state
            start = 0;
            //reset minutes and seconds
            minutes = 0;
            seconds = 0;
        }
       
        //No PBs are pressed
     
        
        //If there is no ALARM and no Countdown...
        if(ALARM == 0 && start == 0){
            Disp2String("\r");
            //display minutes (eg. m:04 or m:42)
            if(minutes < 10){
                Disp2String("0");
                Disp2Dec(minutes);
            }
            
            else{
                Disp2Dec(minutes);
            }
            
            Disp2String("m ; ");
            //display seconds (eg. s:03 or s:45)
            if(seconds < 10){
                Disp2String("0");
                Disp2Dec(seconds);
            }
            
            else{
                Disp2Dec(seconds);
            }
            Disp2String("s");
        }
        
        //If the Alarm has gone off...
        else if(ALARM == 1 && start == 0){
            //reset seconds and minutes
            minutes = 0;
            seconds = 0;
            //display alarm message
            Disp2String("\r 00m: 00s -- ALARM");
            //turn on ALARM
            LATBbits.LATB8 = 1;
            //pause = 1;      //added
        }
    }
}

//CN interrupt to control PBFlags and thus PB presses
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        
        //RA2 press sets pb1flag high
        if(PORTAbits.RA2 == 0 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 1){             //100
           PB1Flag = 1;
           PB2Flag = 0;
           start = 0;
        }
        
        //RA4 press sets pb2flag on
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 ==0 && PORTBbits.RB4 == 1){
            PB2Flag = 1;
            PB1Flag = 0;
            start = 0;
        }
        
        //RB4 oscillates value depending on previous state (allows pause/unpause functionality)
        else if(PORTAbits.RA2 == 1 && PORTAbits.RA4 == 1 && PORTBbits.RB4 == 0){
            if(PB3Flag==0) {PB3Flag=1;}
            else if(PB3Flag==1) {PB3Flag=0;}
            
        }

        
       
        
        //All off
        else{
            
            //If a short button press has occurred
            if(PB1Flag == 0 && PB2Flag == 0 && COUNTDOWN == 0 && ALARM == 0){
              //sets start to 1 (checked above if(start==1&&pause==1)
                start = 1;                                      
               
                
                //Determine whether to pause or not (opposite of previous state)
                if(pause == 1){
                    pause = 0;
                }
                
                else if(pause == 0){
                    pause = 1;
                }
            }
            
            //If a long button press has occurred
            else if(PB1Flag == 0 && PB2Flag == 0 && COUNTDOWN == 1 && ALARM == 0){
                //resets start (sets start to 2) 
                start = 2;
                
                //Reset pause as well
                pause = 1;
            }
            //reset PBFlags
            PB1Flag = 0;
            PB2Flag = 0;
        }
    }
    
    IFS1bits.CNIF = 0;
    
    
}


