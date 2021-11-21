/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC18F4550
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/


#include "tmr0.h"
#include "mcc.h"

/**
  Section: Global Variables Definitions
*/
volatile uint8_t timer0ReloadVal8bit;

volatile uint16_t timer0ReloadVal;

/**
  Section: TMR0 APIs
*/

void parseNote(unsigned char n){
    switch(n){
        case 'c': //261.63 Hz
            f = 33;
            //f = 65;
            //f = 131;
            init = 63624; // T = 3822 us -> T/2 = 1911 us
            break;
        case 'd': //293.67 Hz
            f = 37;
            //f = 73;
            //f = 147;
            init = 63832; // T = 3405 us -> T/2 = 1703 us
            break;
        case 'e': //329.63 Hz
            f = 41;
            //f = 82;
            //f = 165;
            init = 64018; // T = 3034 us -> T/2 = 1517 us
            break;
        case 'f': //349.23 Hz
            f = 44;
            //f = 87;
            //f = 175;
            init = 64103; // T = 2864 us -> T/2 = 1432 us
            break;
        case 'g': //392 Hz
            f = 49;
            //f = 98;
            //f = 196;
            init = 64259; // T = 2551 us -> T/2 = 1276 us
            break;
        case 'a': //440 Hz
            f = 55;
            //f = 110;
            //f = 220;
            init = 64398; // T = 2273 us -> T/2 = 1137 us
            break;
        case 'b': //493.88 Hz
            f = 62;
            //f = 123;
            //f = 247;
            init = 64523; // T = 2025 us -> T/2 = 1012 us
            break;
        case 'C': //277.18 Hz
            f = 35;
            //f = 70;
            //f = 139;
            init = 63731; // T = 3608 us -> T/2 = 1804 us
            break;
        case 'D': //311.13 Hz
            f = 39;
            //f = 78;
            //f = 156;
            init = 63928; // T = 3214 us -> T/2 = 1607 us
            break;
        case 'F': //369.99 Hz
            f = 46;
            //f = 92;
            //f = 185;
            init = 64183; // T = 2703 us -> T/2 = 1352 us
            break;
        case 'G': //415.3 Hz
            f = 52;
            //f = 104;
            //f = 208;
            init = 64331; // T = 2408 us -> T/2 = 1204 us
            break;
        case 'A': //466.16 Hz
            f = 58;
            //f = 116;
            //f = 233;
            init = 64462; // T = 2145 us -> T/2 = 1073 us
            break;
        // ...
        case 's': //0 Hz
            f = 0;
            init = 63624;
            break;
        default: // case 'c' -> 261.63 Hz
            f = 33;
            //f = 65;
            //f = 131;
            init = 63624; // T = 3822 us -> T/2 = 1911 us          
            break;
    }
    if(f == 0){
        ciclos = 33*vi; 
        //ciclos = 65*vi; 
    }else{
        ciclos = f*vi; 
    }
}

void TMR0_Initialize(void)
{
    // T0PS 1:256; T08BIT 8-bit; T0SE Increment_hi_lo; T0CS FOSC/4; TMR0ON enabled; PSA assigned; 
    //T0CON = 0xD7;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.T08BIT = 0;
    /*T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b011;
    TMR0_WriteTimer(3035);*/
    T0CONbits.PSA = 1;
    
    parseNote(notas[currentNote]);
    currentNote++;
    
    TMR0_WriteTimer(init);

    //TMR0_Write8bitTimer(246);

    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    // Start TMR0
    //TMR0_StartTimer();
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}


uint8_t TMR0_Read8bitTimer(void)
{
    uint8_t readVal;

    // read Timer0, low register only
    readVal = TMR0L;

    return readVal;
}

void TMR0_Write8bitTimer(uint8_t timerVal)
{
    // Write to the Timer0 registers, low register only
    TMR0L = timerVal;
 }

void TMR0_Reload8bit(void)
{
    //Write to the Timer0 register
    TMR0L = timer0ReloadVal8bit;
}

uint16_t TMR0_ReadTimer(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
    readValLow = TMR0L;
    readValHigh = TMR0H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void TMR0_WriteTimer(uint16_t timerVal)
{
    // Write to the Timer0 registers
    TMR0H = (timerVal >> 8);
    TMR0L = (uint8_t) timerVal;
    
}

void TMR0_Reload(void)
{
    // Write to the Timer1 register
    TMR0H = (timer0ReloadVal >> 8);
    TMR0L = (uint8_t) timer0ReloadVal;
}

void TMR0_ISR(void)
{
    // add your TMR0 interrupt custom code
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    if(i<ciclos){
        if(f!=0){
            if(PORTDbits.RD7 == 0){
                PORTDbits.RD7 = 1;
            }else if(PORTDbits.RD7 == 1){
                PORTDbits.RD7 = 0;
            }
        }
        else{
            PORTDbits.RD7 = 0;
        }
        TMR0_WriteTimer(init);
        i++;
    }else{
        PORTDbits.RD7 = 0;
        i = 0;
        if(currentNote<sizeNotas){
            parseNote(notas[currentNote]);
            currentNote++;
        }else{
            currentNote = 0;
        }
        // Shift LCD
        LCD_Flag = 1;
    }  
    T0CONbits.TMR0ON = 1;
}

/**
  End of File
*/