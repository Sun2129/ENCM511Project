//Lab B03 Group 12 : Jared Lundy, Jordan Lundy, Sanchit Kumar
#include <xc.h>
#include "IOs.h"
#include "TimeDelay.h"

void main(void){
    IOinit();           //Initialize input/output pins
    
    while(1){
        IOcheck();      //Call IOcheck which checks for button flags raised by CN interrupts
        
    }
}
