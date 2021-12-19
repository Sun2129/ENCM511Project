

#include <xc.h>
#include "TimeDelay.h"
#include "IOs.h"
//global flag
int flag1 = 0;
//delay function
void Delay_ms(uint16_t time_ms){
    //Set base clock speed (at 8MHz currently)
    OSCCONbits.COSC0 = 1;
    OSCCONbits.COSC1 = 1;
    OSCCONbits.COSC2 = 1;
    
    //Set clock division to further change clock speed (clock speed divided by 1)
    //Current clock speed is 8 MHz
    CLKDIVbits.RCDIV0 = 0;
    CLKDIVbits.RCDIV1 = 0;
    CLKDIVbits.RCDIV2 = 0;
    
    //Make sure that the internal clock is being used by the timer.
    T2CONbits.TCS = 0;
    
    //Make sure that the timer doesn't turn off when in idle mode.
    T2CONbits.TSIDL = 0;
    
    //Set priority level.
    IPC1bits.T2IP = 2;
    //Clear the interrupt flag.
    IFS0bits.T2IF = 0;
    //Allow for interrupts to occur.
    IEC0bits.T2IE = 1;
    
    //Turn the timer on.
    T2CONbits.TON = 1;
    //delay for 1 second
    if(time_ms == 1000){
        T2CONbits.TCKPS0 = 1;           //PR2*2/FCLK*PRESCALER = DELAY(ms) ... PR2*2*Tclk*prescaler = delay 
        T2CONbits.TCKPS1 = 1;           //PR2 = 31250*1/4 for 1 second oscillations
        PR2 = (int)(31250*0.25);
        //PR2 = 100000;                
    }
    //delay for 2 seconds
    else if(time_ms == 2000){           //PR2*2*0.000125*256 = 2000 ... pr2 = 31250
        T2CONbits.TCKPS0 = 1;
        T2CONbits.TCKPS1 = 1;
        //PR2 = 1000000;
        PR2 = 31250;
    }
    //delay for 3 seconds
    else if(time_ms == 3000){
        T2CONbits.TCKPS0 = 1;
        T2CONbits.TCKPS1 = 1;
        //PR2 = 1500000;
        PR2 = 46875;
    }
    
    Idle();     //Remain in idle state
}

//timer interrupt
void __attribute__((interrupt,no_auto_psv))_T2Interrupt(void){
    
    IFS0bits.T2IF = 0;
    
    if(flag1 == 0){
        //turn on LED
        LATBbits.LATB8 = 1;
        //toggle global flag
        flag1 = 1;
    }
    
    else if(flag1 == 1){
        //turn off LED
        LATBbits.LATB8 = 0;
        //toggle global flag
        flag1 = 0;
    }
    
    if(PORTBbits.RB4 == 0){
        //turn on Countdown
        COUNTDOWN = 1;
    }
}


