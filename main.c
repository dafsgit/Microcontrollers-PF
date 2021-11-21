/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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

#include "mcc.h"
#include "stdio.h"
#include "stdlib.h"
#include <xlcd.h>

/*
                         Main application
 */

unsigned char ADC_Buffer[10], ud, nave, enemigo, temp_row1 = ' ', temp_row2 = ' ', temp_points = ' ', LCDi = 0x00, act_row1, act_row2;
unsigned char top_row[6] = {2, 11, 20, 29, 38, 39};
unsigned char bottom_row[4] = {7, 16, 25, 34};

void restart(void){
    GAME_OVER = 0;
    ADC_Flag = 0;
    LCD_Flag = 0;
    currentNote = 0;
    points = 0;
    segundos = 0;
    v = 1;
    vi = 12;
    f = 0;
    i = 0;
    ciclos = 0;
    j = 0;
    
    act_row1 = ' ';
    act_row2 = nave;
        
    //the obstacles are shown, top row
    for(unsigned char i=0; i < 6; i++)
    {
        while(BusyXLCD());
        SetDDRamAddr(top_row[i]);
        
        while(BusyXLCD());
        WriteDataXLCD(enemigo);
    }
    //bottom row
    for(unsigned char i=0; i < 4; i++)
    {
        while(BusyXLCD());
        SetDDRamAddr(64+bottom_row[i]);
        
        while(BusyXLCD());
        WriteDataXLCD(enemigo);
    }
    
    PORTDbits.RD7 = 0;
    PIE1bits.ADIE = 1;
    TMR0_StartTimer();
    TMR2_StartTimer();
    
    ADC_StartConversion(0);
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
    
    //PORTCbits.RC1 = 0;
        
    while(BusyXLCD());
    SetCGRamAddr(0x40);
    while(BusyXLCD());
    // Navecita
    WriteDataXLCD(0x10);
    WriteDataXLCD(0x1E);
    WriteDataXLCD(0x18);
    WriteDataXLCD(0x1F);
    WriteDataXLCD(0x18);
    WriteDataXLCD(0x1E);
    WriteDataXLCD(0x10);
    WriteDataXLCD(0x00);
    // Enemigo
    WriteDataXLCD(0x11);
    WriteDataXLCD(0x0A);
    WriteDataXLCD(0x0E);
    WriteDataXLCD(0x1F);
    WriteDataXLCD(0x0E);
    WriteDataXLCD(0x0A);
    WriteDataXLCD(0x11);
    
    nave = 0x00;
    enemigo = 0x01;
    
    act_row1 = ' ';
    act_row2 = nave;
        
    //the obstacles are shown, top row
    for(unsigned char i=0; i < 6; i++)
    {
        while(BusyXLCD());
        SetDDRamAddr(top_row[i]);
        
        while(BusyXLCD());
        WriteDataXLCD(enemigo);
    }
    //bottom row
    for(unsigned char i=0; i < 4; i++)
    {
        while(BusyXLCD());
        SetDDRamAddr(64+bottom_row[i]);
        
        while(BusyXLCD());
        WriteDataXLCD(enemigo);
    }
        
    while(BusyXLCD());
    WriteCmdXLCD(CURSOR_OFF & BLINK_OFF);
    
    PORTDbits.RD7 = 0;
    TMR0_StartTimer();
    TMR2_StartTimer();
    
    //start first ADC conversion with AN0
    ADC_StartConversion(0);
    
    while (1){
        if(LCD_Flag == 1){
            LCD_Flag = 0;
            
            // Shift LCD to the left
            while(BusyXLCD());
            WriteCmdXLCD(0b00011000);
            // Assign what was previously there
            while(BusyXLCD());
            SetDDRamAddr(LCDi);
            while(BusyXLCD());
            WriteDataXLCD(temp_row1);
            while(BusyXLCD());
            SetDDRamAddr(LCDi+0x40);
            while(BusyXLCD());
            WriteDataXLCD(temp_row2);
            if(LCDi < 24){//*************
                while(BusyXLCD());
                SetDDRamAddr(LCDi+13);
                while(BusyXLCD());
                WriteDataXLCD(temp_points);
            }//*************
            // Increment the index
            if(LCDi < 39){
                LCDi++;
            }else{
                LCDi = 0;
            }
            // Keep the characters of the next column
            while(BusyXLCD());
            SetDDRamAddr(LCDi);
            while(BusyXLCD());
            temp_row1 = ReadDataXLCD();
            while(BusyXLCD());
            SetDDRamAddr(LCDi+0x40);
            while(BusyXLCD());
            temp_row2 = ReadDataXLCD();
            if(LCDi < 21){//*************
                while(BusyXLCD());
                SetDDRamAddr(LCDi+16);
                while(BusyXLCD());
                temp_points = ReadDataXLCD();
            }else{
                while(BusyXLCD());
                SetDDRamAddr(0x00);
                while(BusyXLCD());
                temp_points = ReadDataXLCD();
            }//*************
            // Negative points
            if(act_row1 == nave){
                if(temp_row1 == enemigo){
                    points -= v;
                }
            }else{
                act_row1 = temp_row1;
            }
            
            if(act_row2 == nave){
                if(temp_row2 == enemigo){
                    points -= v;
                }
            }else{
                act_row2 = temp_row2;
            }
            
        }
        if(ADC_Flag == 1){   
            ADC_Flag = 0;
            
            if(ADC_Value>512){
                if(act_row1 != nave){
                    // Negative points
                    if(act_row1 == enemigo){
                        points -= v;
                    }
                    act_row1 = nave;
                    act_row2 = temp_row2;
                }
            }else{
                if(act_row2 != nave){
                    // Negative points
                    if(act_row2 == enemigo){
                        points -= v;
                    }
                    act_row2 = nave;
                    act_row1 = temp_row1;
                }
            }
            
            // Put player in the next column
            while(BusyXLCD());
            SetDDRamAddr(LCDi);
            while(BusyXLCD());
            WriteDataXLCD(act_row1);
            while(BusyXLCD());
            SetDDRamAddr(LCDi+0x40);
            while(BusyXLCD());
            WriteDataXLCD(act_row2);
            
            // Put points in the next column
            if(LCDi < 24){//*************
                while(BusyXLCD());
                SetDDRamAddr(LCDi+13);
            }else{
                while(BusyXLCD());
                SetDDRamAddr(37);
            }
            sprintf(ADC_Buffer, "%03d", points);
            while(BusyXLCD());
            putsXLCD((unsigned char *) ADC_Buffer); //*************
            
            //start new conversion
            ADC_StartConversion(0);
        }
        if(GAME_OVER == 1){   
            GAME_OVER = 0;
            
            //prints a message
            while(BusyXLCD());
            SetDDRamAddr(LCDi);
            while(BusyXLCD());
            putrsXLCD("** GAME  OVER **");
            
            while(BusyXLCD());
            SetDDRamAddr(LCDi+0x40);
            while(BusyXLCD());
            WriteDataXLCD(nave);
            
            sprintf(ADC_Buffer, "     %04d     ", points);
            while(BusyXLCD());
            putsXLCD((unsigned char *) ADC_Buffer);
            
            while(BusyXLCD());
            WriteDataXLCD(enemigo);
        }
    }
}

/**
 End of File
*/