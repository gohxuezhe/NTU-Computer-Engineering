// Bump.c
// Runs on MSP432
// Provide low-level functions that interface bump switches the robot.
// Daniel Valvano and Jonathan Valvano
// July 2, 2017

/* This example accompanies the books
   "Embedded Systems: Introduction to the MSP432 Microcontroller",
       ISBN: 978-1512185676, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Interfacing to the MSP432 Microcontroller",
       ISBN: 978-1514676585, Jonathan Valvano, copyright (c) 2017
   "Embedded Systems: Real-Time Operating Systems for ARM Cortex-M Microcontrollers",
       ISBN: 978-1466468863, , Jonathan Valvano, copyright (c) 2017
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2017, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

#include <stdint.h>
#include "msp.h"

uint8_t Bump_Read(void);
// Initialize Bump sensors
// Make six Port 4 pins inputs
// Activate interface pullup
// pins 7,6,5,3,2,0
void Bump_Init(void){
    // write this as part of Lab 3
    P4->SEL0 &= ~0xED;
    P4->SEL1 &= ~0xED;   // 1) configure P4.7,6,5,3,2,0 as GPIO
    P4->DIR &= ~0xED;     // 2) make P4.7,6,5,3,2,0 in
    P4->REN |= 0xED;     // 3) enable pull resistors on P4.7,6,5,3,2,0
    P4->OUT |= 0xED;    //    P4.7,6,5,3,2,0 are pull-up
    P4->IES |= 0xED;    // P4.7,6,5,3,2,0 are falling edge event
    P4->IFG &= ~0xED;   // clear flag4 and flag1
    P4->IE |= 0xED;     //arm interrupt on P4.7,6,5,3,2,0
    NVIC->IP[9] = (NVIC->IP[9]&0xFF00FFFF)|0x00400000; // priority 2
    NVIC->ISER[1] = 0x00000040;     // enable interrupt 38 in NVIC
}

// Uses P1IV to solve critical section/race


// Read current state of 6 switches
// Returns a 6-bit positive logic result (0 to 63)
// bit 5 Bump5 -> P4.7 -> Pin 4 and 1 not needed -> 11101101
// bit 4 Bump4
// bit 3 Bump3
// bit 2 Bump2
// bit 1 Bump1
// bit 0 Bump0
uint8_t Bump_Read(void){
    // write this as part of Lab 3
    uint8_t bump0, bump1, bump2, bump3, bump4, bump5, result;
    bump0 = (P4->IN&0x01);
    bump1 = (P4->IN&0x04) >> 1;
    bump2 = (P4->IN&0x08) >> 1;
    bump3 = (P4->IN&0x20) >> 2;
    bump4 = (P4->IN&0x40) >> 2;
    bump5 = (P4->IN&0x80) >> 2;
    result = bump0 + bump1 + bump2 + bump3 + bump4 + bump5 ;

    return result;
}

void PORT4_IRQHandler(void){
    uint8_t bump_data;
    bump_data = Bump_Read();
    P4->IFG &= ~0xED;   // clear flag4 and flag1
}

