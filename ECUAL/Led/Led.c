/******************************************************************************
 *
 * Module: Led
 *
 * File Name: Led.c
 *
 * Description: Source file for Led Module.
 *
 * Author: Khaled Saleh
 ******************************************************************************/
#include "MCAL\Dio\dio.h"
#include "MCAL\Port\Port.h"
#include "Led.h"


/*********************************************************************************************/

void Led_SetOn(void)
{
    Dio_WriteChannel(DioConfig_LED1_CHANNEL_INDEX,LED_ON);  /* LED ON */
}

/*********************************************************************************************/
void Led_SetOff(void)
{
    Dio_WriteChannel(DioConfig_LED1_CHANNEL_INDEX,LED_OFF); /* LED OFF */
}

/*********************************************************************************************/
void Led_RefreshOutput(void)
{
    Dio_LevelType state = Dio_ReadChannel(DioConfig_LED1_CHANNEL_INDEX);
    Dio_WriteChannel(DioConfig_LED1_CHANNEL_INDEX,state); /* re-write the same value */
}

/*********************************************************************************************/
void Led_Toggle(void)
{
    Dio_LevelType state = Dio_FlipChannel(DioConfig_LED1_CHANNEL_INDEX);
}

/*********************************************************************************************/
