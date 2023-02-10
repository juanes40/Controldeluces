
#include <xc.h>
#include <pic16f887.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "adc.h"
#include "uart.h"
#include <math.h>

//DELARACIÓN DE VARIABLES
#define TMR2PRESCALE 4
#define _XTAL_FREQ 8000000
//#define MUCHA_LUZ 20 //
//#define lUZ_IDEAL 150 //
//#define POCA_LUZ 900 //


unsigned char idx = 0; 
char luz [4]; //Valor de salida para el LCD de la intensidad de luz
char sensorSalida1 [3]; //Servia para pruebas del sensor de proximidad 1, ahora es para la salida del bus serial
char sensorSalida2 [3]; //Servia para pruebas del sensor de proximidad 2, ahora es para la salida del bus serial
char Fila1[16];
char Fila2[16];
long sensorLuz; //Valor de salida de la conversion analogica-digital entre 0 y 1023 del sensor de luz
long pwmFrecuencia = 5000; 
long bloque1; //Valor de salida de la conversion analogica-digital entre 0 y 1023 del sensor de proximidad 1
long bloque2; //Valor de salida de la conversion analogica-digital entre 0 y 1023 del sensor de proximidad 2
char stringBT [50];



/*Procedimientos para el CCP1*/
PWM_Inicializar(){
    OSCCON = 0x71;
    PR2 = (_XTAL_FREQ/(pwmFrecuencia*4*TMR2PRESCALE)) - 1; //Establecer el valor del PR2 haciendo que el PWM funcione a 5 kHz
    CCP1M3 = 1; CCP1M2 = 1;   //Habilita la salida CCP1
    T2CKPS0 = 1;T2CKPS1 = 0; TMR2ON = 1; 
    TRISB2 = 0; 
}
PWM_Duty(unsigned int duty){
    OSCCON = 0x71;
    if(duty<1023){
        duty = ((float)duty/1023)*(_XTAL_FREQ/(pwmFrecuencia*TMR2PRESCALE)); //Establece el valor del ancho del pulso
        DC1B1 = duty & 1; 
        DC1B0 = duty & 2; 
        CCPR1L = duty>>2;

    }
}

/*Procedimietos para el CCP2*/
PWM_Inicializar2(){
    OSCCON = 0x71;
    PR2 = (_XTAL_FREQ/(pwmFrecuencia*4*TMR2PRESCALE)) - 1; //Setting the PR2 formulae using Datasheet // Makes the PWM work in 5KHZ
    CCP2M3 = 1; CCP2M2 = 1;   
    T2CKPS0 = 1;T2CKPS1 = 0; TMR2ON = 1; 
    TRISC2 = 0; 
}
PWM_Duty2(unsigned int duty){
    OSCCON = 0x71;
    if(duty<1023){
        duty = ((float)duty/1023)*(_XTAL_FREQ/(pwmFrecuencia*TMR2PRESCALE)); 
        DC2B1 = duty & 1; 
        DC2B0 = duty & 2; 
        CCPR2L = duty>>2;

    }
}

//===========

void main() {
    //Configura Fosc = 8Mhz interno, Fuente de Fosc del sistema = interno
    OSCCON = 0x71; //Configura oscilador interno (FOSC = 8Mhz)
    TRISE = 0x00;
    TRISC = 0x00;
    TRISB = 0x00;
    ANSEL = 0x07;
    
    USART_Init(9600);
    USART_SendString("SistemaLuz \r\n");
    
    LCD_Init(); //Inicializa el LCD
    ADC_Init(); //Inicializa el LCD
    PWM_Inicializar(); //Inicializa el PWM para el CCP1
    PWM_Inicializar2(); //Inicializa el PWM para el CCP2
    PWM_Duty(0); //Establece el valor de inicio del ancho del pulso en 0
    PWM_Duty2(0); 
    __delay_ms(5000);
    LCD_String_xy(1,0,"LEDS...");
    __delay_ms(2000);
    LCD_Clear();
    //=======
    while (1) {
        //Etapa de adquision de datos para trabajr el PWM 
       sensorLuz = ADC_Read(0);
       __delay_ms(400);
       bloque1 = ADC_Read(1);
       __delay_ms(400);
       bloque2 = ADC_Read(2);
        __delay_ms(400);  
        
       //Salida de la cantidad de luz
       sprintf(luz,"%d ", (int)(sensorLuz));
       LCD_String_xy(1,0,"L:");
       LCD_String(luz);
       __delay_ms(400);
       USART_SendString("Luz: ");
       strcpy(stringBT, luz); //timestamp
       strcat(stringBT, ",");
        
       
       sprintf(sensorSalida1, "%d", (int)(bloque1));
       sprintf(sensorSalida2, "%d", (int)(bloque2));
       
   
       //========== 
        //Etapa de procesamiento de los datos recibidos
        if(bloque1 < 400){
            PWM_Duty(sensorLuz);
            LCD_String_xy(1,9,"L1: ON");
            strcat(stringBT, "L1: ON"); 
            strcat(stringBT, ","); 
        
            __delay_ms(400);
        } else{
            PWM_Duty(0);
            LCD_String_xy(1,9,"L1: OFF");
            strcat(stringBT, "L1: OFF"); 
            strcat(stringBT, ","); 
            __delay_ms(400);
        }
       if (bloque2 < 400){
            PWM_Duty2(sensorLuz);
            LCD_String_xy(2,0,"L2: ON");
            strcat(stringBT, "L2: ON\r\n"); 
            __delay_ms(400);
        }else{
            PWM_Duty2(0);
            LCD_String_xy(2,0,"L2: OFF");
            strcat(stringBT, "L2:OFF  \r\n"); 
            __delay_ms(400);
        }
        /*convert integer value to ASCII string */
        
        //Comparación limites temperatura
        __delay_ms(2000);
       
       

        USART_SendString(stringBT);
        LCD_Clear();
    }
}


