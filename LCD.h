/*!
\file   LCD.h
\date   2022-06-08
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  Functions Handler LCD 16x2 mode 4 bits.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
/**
 * @file LCD.h 
 * @version 1.0
 * @date 10/02/2023 
 * @title Salida en el LCD
 * @brief Muestra en el LCD lo que se ha programado
 * @code {
 *   LCD_String(const char *msg){
        while((*msg)!=0){		
            LCD_Char(*msg);
            msg++;	
        }
     }
 *   }
 *
 * @endcode
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

   
#define RS PORTDbits.RD2  /*PIN 0 of PORTD is assigned for register select Pin of LCD*/
#define EN PORTDbits.RD3  /*PIN 1 of PORTD is assigned for enable Pin of LCD */
#define ldata PORTD  /*PORTD(PD4-PD7) is assigned for LCD Data Output*/ 
#define LCD_Port TRISD  /*define macros for PORTD Direction Register*/
/**
 * @brief LCD_Init inicializar el conversor
 * @param void
 */
void LCD_Init(void);                   /*Initialize LCD*/
/**
 * @brief LCD_Command Enviar datos a los puertos del microcontrolador 
 * @param cmd El valor de la posicion en el LCD tipo char
 */
void LCD_Command(unsigned char );  /*Send command to LCD*/
/**
 * @brief LCD_Char Envira y registrar variables de tipo char en el LCD
 * @param x El caracter a mostrar en el LCD 
 */
void LCD_Char(unsigned char x);    /*Send data to LCD*/
/**
 * @brief LCD_String Cadena a imprimir en el LCD
 * @param * Para mostrar la cadena de texto
 */
void LCD_String(const char *);     /*Display data string on LCD*/
/**
 * @brief LCD_String_xy Para imprimir el mensaje en la primera y segunda fila
 * @param row Fila donde se va a mostrar
 * @param pos Posicion donde va 
 * @param *msg Parametro que se va a mostrar uno a uno 
 */
void LCD_String_xy(char, char , const char *);
/**
 * @brief LCD_clear Borra lo que aparece en el LCD
 * @param void
 */
void LCD_Clear(void);                  /*Clear LCD Screen*/


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */



