/* 
 * File:   adc.h
 * Author: Usuario
 *
 * Created on 6 de febrero de 2023, 09:27 PM
 */
/**
 * @file adc.h 
 * @version 1.0
 * @date 10/02/2023
 * @author JuanesandMarcela
 * @title Conversor Analogico-digital
 * @brief Hace toda la conversion
 * @code {
 *   ADC_Init(void){
 *      TRISA0 = 1;
 *   }
 *
 * @endcode
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif
/**
 * @brief ADC_Init inicializar el conversor
 * @param void
 */
void ADC_Init(void);

/**
 * @brief ADC_Read Lee la entrada y la convierte a digital
 * @param channel Canal de entrada, salida del sensor
 * @return El valor del convertido entero entre 0 y 1023
 */
int ADC_Read(int channel);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

