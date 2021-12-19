//IO ADC AS OF 11-23


#include <xc.h>
#include "IOs.h"
#include "UART2.h"
#include <stdio.h>
//global PB1Flag to track PB1 state
int PB1Flag = 0;

void IOinit(void){ 
    //Inputs
    TRISAbits.TRISA2 = 1;
    
    //Enable interrupt for pin RA2
    CNEN2bits.CN30IE = 1;
    
    //Enable CN bits for RA2
    CNPU2bits.CN30PUE = 1;
    
   // TRISAbits.TRISA3 = 1;       //used to be one
    
    //Allow for interrupts to occur
    IEC1bits.CNIE = 1;
    //Set priority level
    IPC4bits.CNIP = 3;
    //Clear interrupt flag
    IFS1bits.CNIF = 0;
}
//unused IOCheck() function)
void IOcheck(void){
    while(1){
       
    }
}

//CN interrupt -> button presses
void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(IFS1bits.CNIF == 1){
        
        //RA2 press sets PB1Flag high
        if(PORTAbits.RA2 == 0){             
            PB1Flag = 1;
        }
        
        //All off
        else{
            //if pb1flag is high
            if(PB1Flag == 1){
               
                //call do_ADC() and save the return
                uint16_t value = do_ADC();
                //resets PB1 flag
                PB1Flag = 0;
            }
        }
    }
    
    IFS1bits.CNIF = 0;
    
    
}


