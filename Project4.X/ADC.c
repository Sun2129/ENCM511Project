/*
 * File:   ADC.c
//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
 */
#include <xc.h>
#include "ADC.h"
#include "UART2.h"

//ADCinit function ->unused
void ADCinit(void) {
    //ADC setting configuration bits are set in this function (taken from notes)
    
    AD1CON1bits.ADON=0;
    AD1CON1bits.ADSIDL=0;
    AD1CON1bits.FORM=0b00;
    AD1CON1bits.SSRC=0b111;
    AD1CON1bits.ASAM=0;
    AD1CON1bits.SAMP=0;
    
    AD1CON2bits.VCFG=0b000;
    AD1CON2bits.CSCNA=0;
    AD1CON2bits.SMPI=0b0000;
    AD1CON2bits.BUFM=0;
    AD1CON2bits.ALTS=0;
    AD1CON3bits.ADRC=0;
    AD1CON3bits.SAMC = 0b10100;
    AD1CON3bits.ADCS = 0b00111111;
    
    AD1CHSbits.CH0NB=0;
    AD1CHSbits.CH0SB=0b0101;
    AD1CHSbits.CH0NA=0;
    AD1CHSbits.CH0SA=0b0101;
    
    TRISAbits.TRISA3 = 1;
    AD1PCFG=0XFFFF;
    AD1PCFGbits.PCFG5=0;
    AD1CSSL=0;
    
    //IPC3bits.AD1IP=7;
    
    AD1CON1bits.ADON=1;
    
    
    return;
    
}

uint16_t do_ADC(void) {
    //ensure any other button press ignored in function!
    IEC1bits.CNIE=0;
    
    //lines 51 - 81: ADC initialization and setting configuration (taken from notes)
    AD1CON1bits.ADON=0;
    AD1CON1bits.ADSIDL=0;
    AD1CON1bits.FORM=0b00;
    AD1CON1bits.SSRC=0b111;
    AD1CON1bits.ASAM=0;
    AD1CON1bits.SAMP=0;
    
    AD1CON2bits.VCFG=0b000;
    AD1CON2bits.CSCNA=0;
    AD1CON2bits.SMPI=0b0000;
    AD1CON2bits.BUFM=0;
    AD1CON2bits.ALTS=0;
    AD1CON3bits.ADRC=0;                 
    
        AD1CON3bits.SAMC = 0b11111;

    AD1CON3bits.ADCS = 0b00111111;      
    
   // AD1CHSbits.CH0NB=0;
   // AD1CHSbits.CH0SB=0b0101;
    AD1CHSbits.CH0NA=0;
    AD1CHSbits.CH0SA=0b0101;
    
    TRISAbits.TRISA3 = 1;     
    AD1PCFG=0XFFFF;       
    AD1PCFGbits.PCFG5=0;
    AD1CSSL=0;
    
    IPC3bits.AD1IP=7;
    
    AD1CON1bits.ADON=1;
//    AD1CSSLbits.CSSL5=0;          //removed 11-25
    //keep track of ADCvalue (reset here))
    uint16_t ADCvalue =0;
    //loop tracking variable
    int track = 0;
    //outer loop setting up 10 measurements
    while(track<10) {
        //reset ADCvalue
        ADCvalue = 0;
        //inner loop tracker
        int loop_tracker = 0;
        //obtain 1000 samples
        while(loop_tracker<1000) {
            //begin sampling
             AD1CON1bits.SAMP=1;
             //samp]e
            while(AD1CON1bits.DONE==0) {
        
            }
             //turn off sampling
            AD1CON1bits.SAMP=0;
            //add sampled value to ADCvalue
            ADCvalue += ADC1BUF0;
            //increment inner loop
            loop_tracker++;
        }
       //new line and carriage return
        Disp2String("\n\r");
        //local bar graph constant to print bar graph width
        double bar_const = 1;
        //print the bar graph using '='
        while(bar_const<ADCvalue/1000) {
            Disp2String("=");
            //mulitply by constant to print bar to the right of previous
            bar_const=bar_const*1.075;
        }
        //end of bar -> print |
        Disp2String("|");
        //display sampled ADC average at end of graph
        Disp2Hex(ADCvalue/1000);
        //increment outer loop for next measure
        track++;
    }
    
    
    //now stop ignoring button presses again
    IEC1bits.CNIE=1;
    //return ADCvalue average back to calling function
    return(ADCvalue/1000);
}

//unused DispADC function
void DispADC(void) {
    
    uint16_t adcbuf;
    //call do_ADC
    adcbuf = do_ADC();
    //display ADC return from do_ADC())
    XmitUART2('\n', 1);
    XmitUART2('\r', 1);
    Disp2Hex(adcbuf);
    
    return;
}

/*void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF=0;
}*/