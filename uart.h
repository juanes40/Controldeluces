/* 
 * File:   uart.h
 * Author: Logicos
 *
 * Created on 26 de enero de 2023, 10:52 AM
 */
/**
 * @file uart.h 
 * @version 1.0
 * @date 10/02/2023 
 * @title Salida para usar el serial
 * @brief Es para transmitir ,recibir, enviar cadena e inicializar el serial 
 * @code {
 *   USART_TxChar(char out){        
        while(TXIF==0);            
        TXREG=out;                     
     }
 *  }
 *
 * @endcode
 */
#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic16f887.h>
#include <xc.h>
/**
 * @brief USART_Init Asigna los pines para la comunicacion serial
 * @param baud_rate 
 */
void USART_Init(long);
/**
 * @brief USART_TxChar Transmitir los datos al receptor
 * @param out variable de salida para la transmision de el caracter
 */
void USART_TxChar(char);
/**
 * @brief USART_SendString Envia el mensaje entre el receptor y el transmisor
 * @param *out Cadena a enviar
 */
void USART_SendString(const char *);
/**
 * @brief USART_RxChar Se usa para guardar el registro enviado por el transmisor 
 * @return Retorna una variable que recibe los datos.
 */
char USART_RxChar();

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)




#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */



