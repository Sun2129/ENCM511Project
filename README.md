# ENCM511Project

A collection of projects that use Embedded System Interfacing. The PIC24F16KA101 was used as a microcontroller and the MPLAB X IDE was used to program in C, compile the programs, and run them on the microcontroller. Tera Term was used for UART communications.

Project 1: This project tested the simulation tool in MPLAB X IDE. Certain LEDs in the simulation tool were turned on based off of user inputs which were simulated using the stimulus feature.

Project 2: This project was used to test the 16 bit Timer module in the microcontroller. It changed the speed at which a LED blinked, depending on the button pressed, using the Timer module in the microcontroller which created a delay for certain amounts of time.

Project 3: This project was used to test the UART module in the microcontroller. It changed the speed at which a LED blinked, depending on the button pressed, and it displayed the number of the button that was pressed using the UART module in the microcontroller. 

Project 4: This project combined everything used in the 3 previous projects. The goal of this project was creating a stopwatch using the microcontroller. Certain buttons were used to increase the seconds of the stopwatch, other buttons were used to increase the minutes of the stopwatch. Another button was used to start the countdown on the stopwatch from the time that was set for the stopwatch to zero minutes and zero seconds. 

Project 5: This project was used to test the ADC module of the microcontroller. It initialized the ADC of the microcontroller and then stored voltage measurements at the input for a certain period of time. It then averaged the measurements and displayed them using the ADC module. The voltage at the input was controlled using a potentiometer. 
