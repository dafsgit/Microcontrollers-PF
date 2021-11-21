/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCC_H
#define	MCC_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "adc.h"
#include "tmr0.h"
#include "memory.h"
#include "i2c1.h"
#include "spi1.h"
#include "eusart1.h"
#include "tmr1.h"
#include "user_xlcd.h"
#include "pwm2.h"
#include "tmr2.h"
#include "ccp2.h"
#include "tmr3.h"
#include "i2c_user.h"
#include "keypad.h"

#define _XTAL_FREQ  24000000ul

//global variables
unsigned char ADC_Flag = 0, LCD_Flag = 0, GAME_OVER = 0;
unsigned int  ADC_Value, currentNote = 0, points = 0;
unsigned char segundos = 0, v = 1, vi = 6, ready;
int f = 0, i = 0, ciclos = 0, ciclos1s, j = 0;
uint16_t init = 0;
unsigned char sizeNotas = 96;
unsigned char notas[] = {'C','e','C', 'e', 'e','C','e', 'C', 'C','e','C', 'e', 'e','C','e', 'C',
                        'C','e','C', 'e', 'e','C','e', 'C', 'C','e','C', 'e', 'e','C','e', 'C',
                        'b','D','b', 'D', 'D','b','D', 'b', 'b','D','b', 'D', 'D','b','D', 'b',
                        'b','D','b', 'D', 'D','b','D', 'b', 'b','D','b', 'D', 'D','b','D', 'b',
                        'a','C','a', 'C', 'C','a','C', 'a', 'a','C','a', 'C', 'C','a','C', 'a',
                        'e','G','e', 'G', 'G','e','G', 'e', 'e','G','e', 'G', 'G','e','G', 'e'};


// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

void SYSTEM_Initialize(void);
 

void OSCILLATOR_Initialize(void);

#endif	/* MCC_H */

