 /******************************************************************************
 *
 * File Name: Dio_Cfg.h
 *
 * Module: Dio
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller
 *              Dio Driver
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_

/*
 * Module Version 1.0.0
 */
#define DIO_CFG_SW_MAJOR_VERSION                (1U)
#define DIO_CFG_SW_MINOR_VERSION                (0U)
#define DIO_CFG_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION        (0U)
#define DIO_CFG_AR_RELEASE_PATCH_VERSION        (3U)

/* pre-compile option to detect the development errors */
#define DIO_DEV_ERROR_DETECT                    (STD_ON)

/* pre-compile option for version info API */
#define DIO_VERSION_INFO_API                    (STD_ON)

/* Add/remove the service Dio_FlipChannel() */
#define DIO_FLIP_CHANNEL_API                    (STD_ON)

/* Number of ports in the micro-controller */
#define DIO_NUMBER_OF_PORTS                     (6u)

#define DIO_PORTF_LEDS_MASK                     (0X0E)

/**************************************************************************************
 *                              Configured Channels IDs                               *
 **************************************************************************************/
/* DIO configured Channel Index */
#define DioConfig_SW1_CHANNEL_INDEX             (uint8)0X02
#define DioConfig_LED1_CHANNEL_INDEX            (uint8)0X00
#define DioConfig_LED2_CHANNEL_INDEX            (uint8)0X01
#define DioConfig_SW2_CHANNEL_INDEX             (uint8)0X03

/* DIO Configured Port ID's  */
#define DioConf_LED1_PORT_NUM                (Dio_PortType)5 /* PORTF */
#define DioConf_LED2_PORT_NUM                (Dio_PortType)5 /* PORTF */
#define DioConf_SW1_PORT_NUM                 (Dio_PortType)5 /* PORTF */
#define DioConf_SW2_PORT_NUM                 (Dio_PortType)5 /* PORTF */

/* DIO Configured Channel ID's */
#define DioConf_LED1_CHANNEL_NUM             (Dio_ChannelType)1 /* Pin 1 in PORTF */
#define DioConf_LED2_CHANNEL_NUM             (Dio_ChannelType)2 /* Pin 2 in PORTF */
#define DioConf_SW1_CHANNEL_NUM              (Dio_ChannelType)4 /* Pin 0 in PORTF */
#define DioConf_SW2_CHANNEL_NUM              (Dio_ChannelType)0 /* Pin 0 in PORTF */
#define DIO_CONFIGURED_CHANNELS              (4u)

/***************************************************************************************
 *                                  Memory offsets                                     *
 ***************************************************************************************/
#define DIR_REG_OFFSET      0X00000400
#define DATA_REG_OFFSET     0X000003FC

#endif /* DIO_CFG_H_ */
