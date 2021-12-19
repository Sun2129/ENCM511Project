
//Lab B03 group 12 - Jared Lundy, Sanchit Kumar, Jordan Lundy

//Delay_ms() is responsible to create the requested time delay

#include <xc.h>
#include "TimeDelay.h"

int flag1 = 0;

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
    
    //if delay should be 1000
    if(time_ms == 1000){
        //clock divide by 8
        T2CONbits.TCKPS0 = 0;           //PR2*2/FCLK*PRESCALER = DELAY(ms) ... PR2*2*Tclk*prescaler = delay 
        T2CONbits.TCKPS1 = 1;           //PR2*2*(0.000125)*8 = 1000 -> thus, PR2 = 500000
        //necessary PR2
        PR2 = 500000;
        //PR2 = 15625;                
    }
    //if delay should be 2000
    else if(time_ms == 2000){           //PR2*2*0.000125*256 = 2000 ... pr2 = 31250
        //clock divide by 256
        T2CONbits.TCKPS0 = 1;
        T2CONbits.TCKPS1 = 1;
        //necessary PR2
        //PR2 = 1000000;
        PR2 = 31250;
    }
    //if delay should be 3000
    else if(time_ms == 3000){
        //clock divide by 256
        T2CONbits.TCKPS0 = 1;
        T2CONbits.TCKPS1 = 1;
        //PR2 = 1500000;
        //necessary PR2
        PR2 = 46875;
    }
    //500 ms delay
    else if(time_ms==500) {
        //clock divide by 8
        T2CONbits.TCKPS0 = 0;           //PR2*2/FCLK*PRESCALER = DELAY(ms) ... PR2*2*Tclk*prescaler = delay 
        T2CONbits.TCKPS1 = 1;           //PR2*2*(0.000125)*8 = 1000 -> thus, PR2 = 500000/2
        //calculated PR2
        PR2 = 250000;
    }
    //100 ms delay
     else if(time_ms==100) {
         //clock divide by 8
        T2CONbits.TCKPS0 = 0;           //PR2*2/FCLK*PRESCALER = DELAY(ms) ... PR2*2*Tclk*prescaler = delay 
        T2CONbits.TCKPS1 = 1;           //PR2*2*(0.000125)*8 = 1000 -> thus, PR2 = 500000
        //calculated PR2
        PR2 = 50000;
    }
    //put program in idle when nothing is happening
    Idle();
}

//timer interrupt
void __attribute__((interrupt,no_auto_psv))_T2Interrupt(void){
    
    IFS0bits.T2IF = 0;
    //turn LED on if flag1==0, then turn flag 1 high
    if(flag1 == 0){
        LATBbits.LATB8 = 1;
        flag1 = 1;
    }
    //turn off LED if flag1==1, then turn flag1 low
    else if(flag1 == 1){
        LATBbits.LATB8 = 0;
        flag1 = 0;
    }
}
