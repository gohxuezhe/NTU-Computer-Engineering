// RSLK Self Test via UART

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

#include "msp.h"
#include <stdint.h>
#include <string.h>
#include "..\inc\UART0.h"
#include "..\inc\EUSCIA0.h"
#include "..\inc\FIFO0.h"
#include "..\inc\Clock.h"
//#include "..\inc\SysTick.h"/
#include "..\inc\SysTickInts.h"
#include "..\inc\CortexM.h"
#include "..\inc\TimerA1.h"
//#include "..\inc\Bump.h"
#include "..\inc\BumpInt.h"
#include "..\inc\LaunchPad.h"
#include "..\inc\Motor.h"
#include "../inc/IRDistance.h"
#include "../inc/ADC14.h"
#include "../inc/LPF.h"
#include "..\inc\Reflectance.h"
#include "../inc/TA3InputCapture.h"
#include "../inc/Tachometer.h"

#define P2_4 (*((volatile uint8_t *)(0x42098070)))
#define P2_3 (*((volatile uint8_t *)(0x4209806C)))
#define P2_2 (*((volatile uint8_t *)(0x42098068)))
#define P2_1 (*((volatile uint8_t *)(0x42098064)))
#define P2_0 (*((volatile uint8_t *)(0x42098060)))

// At 115200, the bandwidth = 11,520 characters/sec
// 86.8 us/character
// normally one would expect it to take 31*86.8us = 2.6ms to output 31 characters
// Random number generator
// from Numerical Recipes
// by Press et al.
// number from 0 to 31
uint32_t Random(void){
static uint32_t M=1;
  M = 1664525*M+1013904223;
  return(M>>27);
}
char WriteData,ReadData;
uint32_t NumSuccess,NumErrors;
void TestFifo(void){char data;
  while(TxFifo0_Get(&data)==FIFOSUCCESS){
    if(ReadData==data){
      ReadData = (ReadData+1)&0x7F; // 0 to 127 in sequence
      NumSuccess++;
    }else{
      ReadData = data; // restart
      NumErrors++;
    }
  }
}
uint32_t Size;
int Program5_1(void){
//int main(void){
    // test of TxFifo0, NumErrors should be zero
  uint32_t i;
  Clock_Init48MHz();
  WriteData = ReadData = 0;
  NumSuccess = NumErrors = 0;
  TxFifo0_Init();
  TimerA1_Init(&TestFifo,43);  // 83us, = 12kHz
  EnableInterrupts();
  while(1){
    Size = Random(); // 0 to 31
    for(i=0;i<Size;i++){
      TxFifo0_Put(WriteData);
      WriteData = (WriteData+1)&0x7F; // 0 to 127 in sequence
    }
    Clock_Delay1ms(10);
  }
}

char String[64];
uint32_t MaxTime,First,Elapsed;
int Program5_2(void){
//int main(void){
    // measurement of busy-wait version of OutString
  uint32_t i;
  DisableInterrupts();
  Clock_Init48MHz();
  UART0_Init();
  WriteData = 'a';
  SysTick_Init(0x1000000,2); //OHL - using systick INT api
  MaxTime = 0;
  while(1){
    Size = Random(); // 0 to 31
    for(i=0;i<Size;i++){
      String[i] = WriteData;
      WriteData++;
      if(WriteData == 'z') WriteData = 'a';
    }
    String[i] = 0; // null termination
    First = SysTick->VAL;
    UART0_OutString(String);
    Elapsed = ((First - SysTick->VAL)&0xFFFFFF)/48; // usec

    if(Elapsed > MaxTime){
        MaxTime = Elapsed;
    }
    UART0_OutChar(CR);UART0_OutChar(LF);
    Clock_Delay1ms(100);
  }
}

int Program5_3(void){
//int main(void){
    // measurement of interrupt-driven version of OutString
  uint32_t i;
  DisableInterrupts();
  Clock_Init48MHz();
  EUSCIA0_Init();
  WriteData = 'a';
  SysTick_Init(0x1000000,2); //OHL - using systick INT api
  MaxTime = 0;
  EnableInterrupts();
  while(1){
    Size = Random(); // 0 to 31
    for(i=0;i<Size;i++){
      String[i] = WriteData;
      WriteData++;
      if(WriteData == 'z') WriteData = 'a';
    }
    String[i] = 0; // null termination
    First = SysTick->VAL;
    EUSCIA0_OutString(String);
    Elapsed = ((First - SysTick->VAL)&0xFFFFFF)/48; // usec
    if(Elapsed > MaxTime){
        MaxTime = Elapsed;
    }
    EUSCIA0_OutChar(CR);EUSCIA0_OutChar(LF);
    Clock_Delay1ms(100);
  }
}
int Program5_4(void){
//int main(void){
    // demonstrates features of the EUSCIA0 driver
  char ch;
  char string[20];
  uint32_t n;
  DisableInterrupts();
  Clock_Init48MHz();  // makes SMCLK=12 MHz
  EUSCIA0_Init();     // initialize UART
  EnableInterrupts();
  EUSCIA0_OutString("\nLab 5 Test program for EUSCIA0 driver\n\rEUSCIA0_OutChar examples\n");
  for(ch='A'; ch<='Z'; ch=ch+1){// print the uppercase alphabet
     EUSCIA0_OutChar(ch);
  }
  EUSCIA0_OutChar(LF);
  for(ch='a'; ch<='z'; ch=ch+1){// print the lowercase alphabet
    EUSCIA0_OutChar(ch);
  }
  while(1){
    EUSCIA0_OutString("\n\rInString: ");
    EUSCIA0_InString(string,19); // user enters a string
    EUSCIA0_OutString(" OutString="); EUSCIA0_OutString(string); EUSCIA0_OutChar(LF);

    EUSCIA0_OutString("InUDec: ");   n=EUSCIA0_InUDec();
    EUSCIA0_OutString(" OutUDec=");  EUSCIA0_OutUDec(n); EUSCIA0_OutChar(LF);
    EUSCIA0_OutString(" OutUFix1="); EUSCIA0_OutUFix1(n); EUSCIA0_OutChar(LF);
    EUSCIA0_OutString(" OutUFix2="); EUSCIA0_OutUFix2(n); EUSCIA0_OutChar(LF);

    EUSCIA0_OutString("InUHex: ");   n=EUSCIA0_InUHex();
    EUSCIA0_OutString(" OutUHex=");  EUSCIA0_OutUHex(n); EUSCIA0_OutChar(LF);
  }
}

//**************IR Sensor*******************
volatile uint32_t ADCvalue;
volatile uint32_t ADCflag;
volatile uint32_t nr,nc,nl;

void SensorRead_ISR(void){  // runs at 2000 Hz
  uint32_t raw17,raw12,raw16;
  P1OUT ^= 0x01;         // profile
  P1OUT ^= 0x01;         // profile
  ADC_In17_12_16(&raw17,&raw12,&raw16);  // sample
  nr = LPF_Calc(raw17);  // right is channel 17 P9.0
  nc = LPF_Calc2(raw12); // center is channel 12, P4.1
  nl = LPF_Calc3(raw16); // left is channel 16, P9.1
  ADCflag = 1;           // semaphore
  P1OUT ^= 0x01;         // profile
}

void IRSensor_Init(void){
    uint32_t raw17,raw12,raw16;
    uint32_t s;
    s = 256; // replace with your choice
    ADC0_InitSWTriggerCh17_12_16();   // initialize channels 17,12,16
    ADC_In17_12_16(&raw17,&raw12,&raw16);  // sample
    LPF_Init(raw17,s);     // P9.0/channel 17 right
    LPF_Init2(raw12,s);    // P4.1/channel 12 center
    LPF_Init3(raw16,s);    // P9.1/channel 16 left
    TimerA1_Init(&SensorRead_ISR,250);    // 2000 Hz sampling
    ADCflag = 0;
}

//**************Bump Switch*******************
int prev_x = -1;
volatile uint8_t CollisionData, CollisionFlag, CollisionRecord;
void HandleCollision(uint8_t bumpSensor){
   Motor_Stop();
   CollisionData = bumpSensor;
   CollisionFlag = 1;
   P4->IFG &= ~0xED;                  // clear interrupt flags
}

//**************Reflectance*******************
uint8_t Data;

//**************Tachometer*******************
uint16_t Power;
uint16_t Period0, Period2;              // (1/SMCLK) units = 83.3 ns units
uint16_t First0, First2;               // Timer A3 first edge, P10.4
int Done0, Done2;                     // set each rising
void PeriodMeasure0(uint16_t time){
  P2_0 = P2_0^0x01;           // thread profile, P2.0
  Period0 = (time - First0)&0xFFFF; // 16 bits, 83.3 ns resolution
  First0 = time;                   // setup for next
  Done0 = 1;
}
void PeriodMeasure2(uint16_t time){
  P2_2 = P2_2^0x01;           // thread profile, P2.4
  Period2 = (time - First2)&0xFFFF; // 16 bits, 83.3 ns resolution
  First2 = time;                   // setup for next
  Done2 = 1;
}

void toggle_GPIO(void){
    P2_4 ^= 0x01;     // create output
}

uint32_t main_count=0;

void Tachometer_Init(void){
    P2->SEL0 &= ~0x11;
    P2->SEL1 &= ~0x11;  // configure P2.0 and P2.4 as GPIO
    P2->DIR |= 0x11;    // P2.0 and P2.4 outputs
    First0 = First2 = 0; // first will be wrong
    Done0 = Done2 = 0;   // set on subsequent
}
//**************Ruler*******************
int periodSum = 0;
int periodCount = 0;
double averagePeriod;

int length;
double wheelCircumference = 22.0;

double speedRPM, speedCMPS;

void Ruler(double averagePeriod){
    EUSCIA0_OutString("averagePeriod: ");EUSCIA0_OutUDec(averagePeriod); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

    EUSCIA0_OutString("Enter length(cm): ");
    length = EUSCIA0_InUDec(); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

    speedRPM = 2000000/averagePeriod;

    speedCMPS = speedRPM * wheelCircumference / 60;

    Motor_Forward(3000, 3000);
    Clock_Delay1ms((int)((length / speedCMPS) * 1000));
    Motor_Stop();
}
//**************Hand Follower*******************
int leftDistance, centerDistance, rightDistance;
//**************RSLK_Reset*******************
void RSLK_Reset(void){
    DisableInterrupts();
    Clock_Init48MHz();  // makes SMCLK=12 MHz
    //SysTick_Init(48000,2);  // set up SysTick for 1000 Hz interrupts
    Motor_Init();
    Motor_Stop();
    LaunchPad_Init();
    Reflectance_Init();
    IRSensor_Init();
    BumpInt_Init(&HandleCollision);
    //Bump_Init();
    //  Bumper_Init();
    Tachometer_Init(); //this prevents words from appearing
    EUSCIA0_Init();     // initialize UART
    EnableInterrupts();
}



// RSLK Self-Test
int main(void) {
  uint32_t cmd=0xDEAD, menu=0, choice=0xDEAD;

  DisableInterrupts();
  Clock_Init48MHz();  // makes SMCLK=12 MHz
//  SysTick_Init(48000,2);  // set up SysTick for 1000 Hz interrupts
  Motor_Init();
  Motor_Stop();
  LaunchPad_Init();
  BumpInt_Init(&HandleCollision);
  //Bump_Init();
  //Bumper_Init();
  IRSensor_Init();
  Tachometer_Init();
  EUSCIA0_Init();     // initialize UART
  EnableInterrupts();

  while(1){                     // Loop forever
      // write this as part of Lab 5
      EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("RSLK Testing"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[0] RSLK Reset"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[1] Motor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[2] IR Sensor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[3] Bumper Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[4] Reflectance Sensor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[5] Tachometer Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[6] Line Tracer"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[7] Remote Control"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[8] Ruler"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
      EUSCIA0_OutString("[9] Hand Follower"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

      EUSCIA0_OutString("CMD: ");
      cmd=EUSCIA0_InUDec();
      EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

      switch(cmd){
          case 0: // RSLK Reset
            EUSCIA0_OutString("RSLK Reset"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            RSLK_Reset();
            menu =1;
            cmd=0xDEAD;
            break;

          case 1: // Motor Test
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Motor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("[1] Forward"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("[2] Backward"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("[3] Left wheel"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("[4] Right wheel"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("[0] Back"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            do{
                EUSCIA0_OutString("Choice: ");
                choice=EUSCIA0_InUDec();
                EUSCIA0_OutChar(CR);
                switch(choice){
                    case 1: // Motor Forward
                        Motor_Forward(3000,3000);
                        Clock_Delay1ms(1500);
                        Motor_Stop();
                        break;
                    case 2: // Motor Backward
                        Motor_Backward(3000,3000);
                        Clock_Delay1ms(1500);
                        Motor_Stop();
                        break;
                    case 3: // Motor Left
                        Motor_Right(0,3000);
                        Clock_Delay1ms(1500);
                        Motor_Stop();
                        break;
                    case 4: // Motor Right
                        Motor_Left(3000,0);
                        Clock_Delay1ms(1500);
                        Motor_Stop();
                        break;
                    default:
                        break;

                }
                EUSCIA0_OutString("\x1b[2K");
            } while(choice != 0);
            menu =1;
            cmd=0xDEAD;
            break;
        case 2: // IR Sensor Test
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("IR Sensor Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to exit"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            CollisionFlag = 0;
            EnableInterrupts();

            while(1){
                WaitForInterrupt();
                EUSCIA0_OutString("\x1b[2K");
                EUSCIA0_OutUDec5(LeftConvert(nl)/10); EUSCIA0_OutString(" cm,");
                EUSCIA0_OutUDec5(CenterConvert(nc)/10); EUSCIA0_OutString(" cm,");
                EUSCIA0_OutUDec5(RightConvert(nr)/10); EUSCIA0_OutString(" cm");
                EUSCIA0_OutChar(CR);
                if (CollisionFlag == 1){
                    break;
                }
                Clock_Delay1ms(50);
            }
            menu =1;
            cmd=0xDEAD;
            break;
        case 3: // Bump Test
            CollisionData = CollisionRecord = 0x3F;
            CollisionFlag = 0;

            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Bump Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press all switches at least once to exit"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            while (1){
                WaitForInterrupt(); //wait for bumper to be switched
                if (CollisionFlag == 1){
                    CollisionRecord &= CollisionData;
                    for(int x = 1; x < 7; x++ ){
                        if(CollisionData %2 == 0 && prev_x != x){
                            EUSCIA0_OutString("Bump Switch ");
                            EUSCIA0_OutUDec(x);
                            EUSCIA0_OutString(" Held. ");
                            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

                            prev_x = x;
                            break;
                        }
                        CollisionData = CollisionData >> 1;
                    }
                }
                CollisionFlag = 0;
                if(CollisionRecord == 0x00){
                    EUSCIA0_OutString("All bump switch tested and working"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
                    break;
                }
            }
            EUSCIA0_OutString("Press any key to escape"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            char character1;
            while(1){
                character1 = EUSCIA0_InChar();
                if (character1){
                    break;
                }
            }
            menu=1;
            cmd=0xDEAD;
            break;
        case 4: // Reflectance Test
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Reflectance Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to escape"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            CollisionFlag = 0;
            EnableInterrupts();

            while(1){
                WaitForInterrupt();
                Data = Reflectance_Read(1000);
                EUSCIA0_OutString("\x1b[2K");
                EUSCIA0_OutString("Reflectance Sensor Data Right (1) - Left (8): ");
                for (int j = 0; j < 8; j++){
                    EUSCIA0_OutUDec(Data%2);
                    EUSCIA0_OutString(" ");
                    Data/=2;
                }
                EUSCIA0_OutChar(CR);
                if (CollisionFlag == 1){
                    break;
                }
                Clock_Delay1ms(1000);
            }
            menu =1;
            cmd=0xDEAD;
            break;
        case 5: // Tachometer Test
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Tachometer Test"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            do{
                EUSCIA0_OutString("Enter power output of motor (0 - 6000): ");
                Power = EUSCIA0_InUDec(); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            }while(Power > 6000);
                EUSCIA0_OutString("Press bump switch to exit"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            TimerA1_Init(&toggle_GPIO,10);    // 50Khz sampling
            TimerA3Capture_Init(&PeriodMeasure0,&PeriodMeasure2);
            Clock_Delay1ms(500);
            Motor_Forward(Power,Power);
            CollisionFlag = 0;
            EnableInterrupts();
            while(1){
                WaitForInterrupt();
                main_count++;
                if(!(main_count%3000)){
                    EUSCIA0_OutString("\x1b[2K");
                    EUSCIA0_OutString("Period0 = ");EUSCIA0_OutUDec5(Period0);EUSCIA0_OutString(" Period2 = ");EUSCIA0_OutUDec5(Period2);EUSCIA0_OutChar(CR);
                    //Unit = 83.3 ns
                }
                if (CollisionFlag)
                  break;
            }
            Motor_Stop();
            menu =1;
            cmd=0xDEAD;
            break;
        case 6: // Line Tracer
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Line Tracer"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to exit"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            int direction;
            int weightage;

            CollisionFlag = 0;
            EnableInterrupts();

            while(1){
                WaitForInterrupt();
                direction = Reflectance_Position(Reflectance_Read(100));
                if(direction == 0){
                    Motor_Stop();
                }
                weightage = direction * (2000 / 711);
                Motor_Forward(2000 - weightage,2000 + weightage);
//                Clock_Delay1ms(1000);
//                Motor_Stop();

                if (CollisionFlag){
                  break;
                }
            }
            Motor_Stop();
            menu =1;
            cmd=0xDEAD;
            break;
        case 7: // Remote Control
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Remote Control"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to exit"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            CollisionFlag = 0;
            EnableInterrupts();
            WaitForInterrupt();
            char *stringOutput;

            while(1){
                char character;
                character = EUSCIA0_InChar();
                if (character == 'w'){
                    stringOutput = "Forward";
                    Motor_Forward(3000, 3000);
                }
                else if (character == 'a'){
                    stringOutput = "Left";
                    Motor_Left(3000, 3000);
                }
                else if (character == 's'){
                    stringOutput = "Backward";
                    Motor_Backward(3000, 3000);
                }
                else if (character == 'd'){
                    stringOutput = "Right";
                    Motor_Right(3000, 3000);
                }
                EUSCIA0_OutString("\x1b[2K");
                EUSCIA0_OutString(stringOutput); EUSCIA0_OutChar(CR);
                Clock_Delay1ms(50);
                Motor_Stop();
                if (CollisionFlag){
                    break;
                }
            }
            menu =1;
            cmd=0xDEAD;
            break;
        case 8: // Ruler
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Ruler"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            TimerA1_Init(&toggle_GPIO,10);    // 50Khz sampling
            TimerA3Capture_Init(&PeriodMeasure0,&PeriodMeasure2);
            CollisionFlag = 0;

            EUSCIA0_OutString("Calibrating Tachometer"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press any key to start"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to stop"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            char character2;
            while(1){
                character2 = EUSCIA0_InChar();
                if (character2){
                    break;
                }
            }
            Motor_Forward(3000,3000);
            while(1){
                WaitForInterrupt();
                main_count++;
                if(main_count%5000){
                    periodSum += Period0;
                    periodCount += 1;
                    EUSCIA0_OutString("\x1b[2K");
                    EUSCIA0_OutString("Period counts: "); EUSCIA0_OutUDec(periodCount); EUSCIA0_OutChar(CR);
                }
                if (CollisionFlag)
                  break;
            }
            EUSCIA0_OutChar(LF);
            averagePeriod = periodSum / periodCount;
            Ruler(averagePeriod);

            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Hope it was accurate"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press any key to escape"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            char character3;
            while(1){
                character3 = EUSCIA0_InChar();
                if (character3){
                    break;
                }
            }

            menu =1;
            cmd=0xDEAD;
            break;

        case 9: // Hand Follower
            EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Hand Follower"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);
            EUSCIA0_OutString("Press bump switch to escape"); EUSCIA0_OutChar(CR); EUSCIA0_OutChar(LF);

            EnableInterrupts();
            CollisionFlag = 0;

            while(1){
                WaitForInterrupt();
                leftDistance = LeftConvert(nl)/10;
                centerDistance = CenterConvert(nc)/10;
                rightDistance = RightConvert(nr)/10;
                if (centerDistance < 20){
                    Motor_Forward(1000, 1000);
                }
                else if (leftDistance < 20){
                    Motor_Forward(1500, 500);
                }
                else if (rightDistance < 20){
                    Motor_Forward(500, 1500);
                }
                Clock_Delay1ms(50);
                Motor_Stop();
                if (CollisionFlag == 1){
                    break;
                }
            }

            menu =1;
            cmd=0xDEAD;
            break;

        default:
            menu=1;
            break;
      }

      if(!menu)Clock_Delay1ms(3000);
      else{
          menu=0;
      }

      // ....
      // ....
  }
}
