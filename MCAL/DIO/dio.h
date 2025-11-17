/******************************************************************************
 * File Name: dio.h
 *
 * Module: Dio
 *
 * File Description: A header file that contain the functions prototypes and symbolic
 *                   names for the Errors detected needed in the Dio driver for TM4C123GH6PM
 *                   Micro-controller.
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

/* The vendors id */
#define DIO_VENDOR_ID                  (1111U)

/* Dio Module Id */
#define DIO_MODULE_ID                  (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID                (0U)

/* The software version of the DIO module 1.0.0 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/* AUTOSAR Version 4.0.3 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (0U)
#define DIO_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Dio Status macros
 */
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)

#include "Std_Types.h"
/*
 * check the compatibility of the AUTOSAR version and Std_Types AUTOSAR version
 */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

#include "Dio_Cfg.h"
/*
 * check the compatibility of the configuration software version and the
 * current dio software version
 */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/*
 * AUTOSAR Version checking between Dio_Cfg.h and Dio.h files
 */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

#include "Common_Macros.h"
/******************************************************************************
 *                              DET errors macros                             *
 ******************************************************************************/

/* Invalid channel name requested */
#define DIO_E_PARAM_INVALID_CHANNEL_ID              (uint8)0x0A

/* API service called with NULL pointer parameter */
#define DIO_E_PARAM_CONFIG                          (uint8)0x10

/* Invalid port name requested */
#define DIO_E_PARAM_INVALID_PORT_ID                 (uint8)0x14

/* Invalid Channel group passed */
#define DIO_E_PARAM_INVALID_GROUP                   (uint8)0x1F

/*
 * API service called with a NULL pointer. In case of this error, the API service
 * shall return immediately without any further action, beside reporting this development error
 */
#define DIO_E_PARAM_POINTER                         (uint8)0x20

#define DIO_E_UNINIT                                (uint8)0xF0
/******************************************************************************
 *                            API Service Id Macros                           *
 ******************************************************************************/
#define DIO_READ_CHANNEL_SID                        (uint8)0X00

#define DIO_WRITE_CHANNEL_SID                       (uint8)0X01

#define DIO_READ_PORT_SID                           (uint8)0X02

#define DIO_WRITE_PORT_SID                          (uint8)0X03

#define DIO_READ_CHANNEL_GROUP_SID                  (uint8)0X04

#define DIO_WRITE_CHANNEL_GROUP_SID                 (uint8)0X05

#define DIO_INIT_SID                                (uint8)0X10

#if(DIO_VERSION_INFO_API == STD_ON)
#define DIO_VERSION_INFO_SID                        (uint8)0X12
#endif

#if(DIO_FLIP_CHANNEL_API == STD_ON)
#define DIO_FLIP_CHANNEL_SID                        (uint8)0X11
#endif
/*******************************************************************************
 *                              Type Definitions                               *
 *******************************************************************************/
/*
 * Numeric ID of a DIO channel
 */
typedef uint8 Dio_ChannelType;

/*
 * Numeric ID of a DIO port
 */
typedef uint8 Dio_PortType;

/*
 * Type for the definition of a channel group, which consists of several adjoining
 * channels within a port
 */
typedef struct {

    /* Defines the positions of the channel group */
    uint8 mask;

    /* Position of the Channel Group on the port, counted from the LSB */
    uint8 offset;

    /* The port on which the Channel group is defined */
    Dio_PortType port;

}Dio_ChannelGroupType;

/* The possible levels a DIO channel can have */
typedef uint8 Dio_LevelType ;

/* The possible levels a port can have  */
typedef uint8 Dio_PortLevelType;

/* Structure that contain all the post build configurable parameters */
typedef struct {
    /* The number of the port of the channel */
    uint8 portNum ;

    /* The number of the channel inside its port */
    uint8 channelNum ;
}Dio_ConfigChannel;

/* Structure that contain all the post build configuration */
typedef struct Dio_ConfigType{

    Dio_ConfigChannel Channels [DIO_CONFIGURED_CHANNELS] ;
}Dio_ConfigType ;
/**************************************************************************
 *                          Commonly used macros                          *
 **************************************************************************/
#define PORT_DIRECTION_REGISTER     (*((volatile uint32 *)((uint8 *)Port_Ptr - DATA_REG_OFFSET + DIR_REG_OFFSET)))

/**************************************************************************
 *                            Function Prototype                          *
 **************************************************************************/

/*********************************************************************************
 * Service Name: Dio_ReadChannel
 * Service Id: 0X00
 * Parameters: Dio_ChannelType ChannelId
 * Service Description: Function That read the value of the channel passed to it
 *********************************************************************************/
Dio_LevelType Dio_ReadChannel
(
        Dio_ChannelType ChannelId
);

/*********************************************************************************
 * Service Name:  Dio_WriteChannel
 * Service Id: 0x01
 * Parameters: ID of DIO Channel, Level of the channel
 * Service Description: Function That writes the value to the channel passed to it
 *********************************************************************************/
void Dio_WriteChannel
(
        Dio_ChannelType ChannelId,
        Dio_LevelType Level
);

/*********************************************************************************
 * Service Name:  Dio_ReadPort
 * Service Id: 0x02
 * Parameters: ID of DIO Port
 * Service Description: Function That reads the value to the port passed to it
 *********************************************************************************/
Dio_PortLevelType Dio_ReadPort
(
        Dio_PortType PortId
);

/************************************************************************************
 * Service Name: Dio_WritePort
 * Service ID: 0x11
 * Parameters (in): ID of port.
 * Return value: None
 * Description: Function to write the whole port.
 ************************************************************************************/
void Dio_WritePort
(
        Dio_PortType PortId,
        Dio_PortLevelType Level
);

/************************************************************************************
 * Service Name: Dio_ReadChannelGroup
 * Service ID: 0x04
 * Parameters: ChannelGroupIdPtr - Pointer to ChannelGroup
 * Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
 * Description: Function that reads a subset of adjoining bits of a port
 ************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup
(
        const Dio_ChannelGroupType* ChannelGroupIdPtr
);

/************************************************************************************
 * Service Name: Dio_WriteChannelGroup
 * Service ID: 0x05
 * Parameters: ChannelGroupIdPtr - Pointer to ChannelGroup
 * Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
 *               Level             - value to be written
 * Description: Function that reads a subset of adjoining bits of a port
 ************************************************************************************/
void Dio_WriteChannelGroup
(
        const Dio_ChannelGroupType* ChannelGroupIdPtr,
        Dio_PortLevelType Level
);

#if(DIO_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Service ID: 0x12
 * Parameters: VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
void Dio_GetVersionInfo
(
        Std_VersionInfoType* VersionInfo
);
#endif

/********************************************************************************
 * Service Name: Dio_Init
 * Service Id: 0X10
 * Parameters: pointer to the post build configuration data
 * Service Description: Function that initialize all the global variables and
 *                      channels of used in the DIO module
 ********************************************************************************/
void Dio_Init
(
        const Dio_ConfigType* ConfigPtr
);

#if(DIO_FLIP_CHANNEL_API == STD_ON)
/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID: 0x11
 * Parameters (in): ID of DIO channel.
 * Return value: Dio_LevelType
 * Description: Function to flip the level of a channel and return the level of the channel after flip.
 ************************************************************************************/
Dio_LevelType Dio_FlipChannel
(
        Dio_ChannelType ChannelId
);
#endif

/************************************************************************************
 *                          Variable to use it in other files                       *
 ************************************************************************************/
extern const Dio_ConfigType Dio_Configurations ;
extern const Dio_ChannelGroupType Dio_PortfLedsGroup ;

#endif /* DIO_H_ */
