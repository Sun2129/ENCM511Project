
#include <xc.h>

void main(void){
    //We will need 4 pins to track input.
    //The first will be RA0
    TRISAbits.TRISA0 = 1; 
    //The second will be RA1
    TRISAbits.TRISA1 = 1; 
    //The third will be RA2
    TRISAbits.TRISA2 = 1; 
    //The fourth will be RA4
    TRISAbits.TRISA4 = 1; 
    
    //We will need 9 pins to track output (since my UCID has a 9 in it)
    //The first will be RB0
    TRISBbits.TRISB0 = 0;
    //The second will be RB1
    TRISBbits.TRISB1 = 0;
    //The third will be RB2
    TRISBbits.TRISB2 = 0;
    //The fourth will be RB4
    TRISBbits.TRISB4 = 0;
    //The fifth will be RB7
    TRISBbits.TRISB7 = 0;
    //The sixth will be RB8
    TRISBbits.TRISB8 = 0;
    //The seventh will be RB9
    TRISBbits.TRISB9 = 0;
    //The eighth will be RB12
    TRISBbits.TRISB12 = 0;
    //The ninth will be RB13
    TRISBbits.TRISB13 = 0;
    
    //We will manipulate which LEDS are on by setting the output of certain pins 
    //to be 0 (a LED that is turned off) or 1 (a LED that is turned on)
    while(1){
        
        //User input is 0000 so do nothing
        //We check the inputs at PORTA of the pins we are using 
        if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0){
            //Do not turn on any LEDS or turn of all LEDS that were turned on previously
            //Set all output pins to be 0 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0001 so display 1st number of UCID (3)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 1){
            //Only turn on 3 LEDS
            //Set 3 of the 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 1;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0010 so display 2nd number of UCID (0)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA0 == 0){
            //Do not turn on any LEDS
            //Set all output pins to be 0 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0011 so display 3rd number of UCID (0)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 1 && PORTAbits.RA0 == 1){
            //Do not turn on any LEDS
            //Set all output pins to be 0 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0100 so display 4th number of UCID (9)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0){
            //Turn on 9 LEDS
            //Set all 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB8 = 1;
            LATBbits.LATB9 = 1;
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 1;
        }
        
        //User input is 0101 so display 5th number of UCID (2)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 1){
            //Turn on 2 LEDS
            //Set 2 of the 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0110 so display 6th number of UCID (1)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA1 == 1 && PORTAbits.RA0 == 0){
            //Turn on 1 LED
            //Set 1 of the 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 0111 so display 7th number of UCID (8)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 0 && PORTAbits.RA2 == 1 && PORTAbits.RA1 == 1 && PORTAbits.RA0 == 1){
            //Turn on 8 LEDS
            //Set 8 of the 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB8 = 1;
            LATBbits.LATB9 = 1;
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 0;
        }
        
        //User input is 1000 so display 8th number of UCID (9)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 0){
            //Turn on 9 LEDS
            //Set all 9 output pins to be 1 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 1;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 1;
            LATBbits.LATB4 = 1;
            LATBbits.LATB7 = 1;
            LATBbits.LATB8 = 1;
            LATBbits.LATB9 = 1;
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 1;
        }
        
        //User input is 1001 so display 9th number of UCID (doesn't exist for me)
        //We check the inputs at PORTA of the pins we are using 
        else if(PORTAbits.RA4 == 1 && PORTAbits.RA2 == 0 && PORTAbits.RA1 == 0 && PORTAbits.RA0 == 1){
            //Do not turn on any LEDS or turn of all LEDS that were previously turned on
            //Set all output pins to be 0 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
        
        else{
            //Do not turn on any LEDS or turn of all LEDS that were previously turned on
            //Set all output pins to be 0 by changing the values of the LATB pins we are using
            LATBbits.LATB0 = 0;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            LATBbits.LATB7 = 0;
            LATBbits.LATB8 = 0;
            LATBbits.LATB9 = 0;
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 0;
        }
    }
    
    return;

}
