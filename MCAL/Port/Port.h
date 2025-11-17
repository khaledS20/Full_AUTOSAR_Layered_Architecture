/******************************************************************************
 * File Name: Port.h
 *
 * Module: Port
 *
 * File Description: A header file that contain the functions prototypes and symbolic
 *                   names for the Errors detected needed in the port driver for TM4C123GH6PM
 *                   Micro-controller.
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/* The vendors id */
#define PORT_VENDOR_ID                       (1111U)

/* Port Module Id */
#define PORT_MODULE_ID                       (125U)

/* Port Instance Id */
#define PORT_INSTANCE_ID                     (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION                (1U)
#define PORT_SW_MINOR_VERSION                (0U)
#define PORT_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION        (4U)
#define PORT_AR_RELEASE_MINOR_VERSION        (0U)
#define PORT_AR_RELEASE_PATCH_VERSION        (3U)

/**************************************************************************************************
 *                          File Includes And Version Checking                                    *
 **************************************************************************************************/
/*
 * Include the configuration file and check on the AUTOSAR and software version compatibility
 */
#include "Port_Cfg.h"
/* checking the software version compatibility */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/*
 * Include the standard types file check the AUTOSAR version compatibility
 */
#include "Std_Types.h"
/* checking the SW version compatibility */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/*
 * Include the the DIO header file to use its standard types and functions
 */
#include "MCAL\Dio\dio.h"
/* checking the software version compatibility */
#if ((DIO_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (DIO_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (DIO_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* checking the AUTOSAR version compatibility */
#if ((DIO_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* The common macros is not AUTOSAR file so ther is no version checking */
#include "Common_Macros.h"
#include "Port_Regs.h"
/**************************************************************************************************
 *                                      DET Errors IDs Macros                                     *
 **************************************************************************************************/
/* Invalid port pin id requested */
#define PORT_E_PARAM_PIN                                    (uint8)0X0A

/* Port pin direction is not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE                       (uint8)0X0B

/* Calling the Init service with wrong parameter */
#define PORT_E_PARAM_CONFIG                                 (uint8)0X0C

/*
 *  Set pin mode service is called when mode is unchangeable
 */
#define PORT_E_PARAM_INVALID_MODE                           (uint8)0X0D
#define PORT_E_MODE_UNCHANGEABLE                            (uint8)0X0E

/* API service is called without module initialization */
#define PORT_E_UNINIT                                       (uint8)0X0F

/* API is called with NULL pointer */
#define PORT_E_PARAM_POINTER                                (uint8)0X10

/**************************************************************************************************
 *                                      APIs IDs Macros                                     *
 **************************************************************************************************/
#define PORT_INIT_SID                                       (uint8)0X00

#define PORT_SET_PIN_DIRECTION_SID                          (uint8)0X01

#define PORT_REFRESH_PORT_DIRECTION_SID                     (uint8)0X02

#define PORT_VERSION_INFO_SID                               (uint8)0X03

#define PORT_SET_PIN_MODE_SID                               (uint8)0x04

/**************************************************************************************************
 *                                      Type Definitions                                          *
 **************************************************************************************************/
/*  used for the symbolic name of a Port Pin */
typedef uint8 Port_PinType;

/* type for defining the direction of a Port Pin */
typedef enum {
    PORT_PIN_IN, PORT_PIN_OUT

}Port_PinDirectionType ;

/* Type carry the different port pin mode */
typedef uint8 Port_PinModeType ;

typedef struct {
    /* The number of the channel in the MCU */
    Port_PinType PortPin_Num;

    /* The number of the port */
    uint8 Port_Num ;

    /* The mode of the channel */
    Port_PinModeType PortPin_Mode;

    /* The direction of the pin */
    Port_PinDirectionType PortPin_Direction;

    /* The initial value of the pin */
    uint8 PortPin_InitialValue;

    /* If we can change the direction during the runtime */
    boolean PortPin_DirChangeable;

    /* If we can change the pin mode during the runtime */
    boolean PortPin_ModeChangeable;

    /* Activate the internal pull up resistor */
    boolean PortPin_EnablePUR;

    /* Enable/Disable digital pins */
    boolean PortPin_DEN;

}Port_ConfigType;

/**************************************************************************************************
 *                                      Commonly used macros                                      *
 **************************************************************************************************/
/*
 * Macro to get the data register of the current port number
 */
#define PORT_DATA_REG           (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_DATA_REG_OFFSET)))

/*
 * Macro to get the data of the direction register of the current port number
 */
#define PORT_DIR_REG            (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_DIR_REG_OFFSET)))

/*
 * Macro to get the data of the alternative function register of the current port number
 */
#define PORT_AFSEL_REG          (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_AFSEL_REG_OFFSET)))

/*
 * Macro to get the data of the direction register of the current port number
 */
#define PORT_PUR_REG            (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_PUR_REG_OFFSET)))

/*
 * Macro to get the data of the digital enable register of the current port number
 */
#define PORT_DEN_REG            (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_DEN_REG_OFFSET)))

/*
 * Macro to get the data of the lock register of the current port number
 */
#define PORT_LOCK_REG           (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_LOCK_REG_OFFSET)))

/*
 * Macro to get the data of the commit register of the current port number
 */
#define PORT_CR_REG             (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_CR_REG_OFFSET)))

/*
 * Macro to get the data of the analog select register of the current port number
 */
#define PORT_AMSEL_REG          (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_AMSEL_REG_OFFSET)))

/*
 * Macro to get the data of the control register of the current port number
 */
#define PORT_PCTL_REG           (*((volatile uint32*)((uint8 *)Port_Ptr + GPIO_PCTL_REG_OFFSET)))

/**************************************************************************************************
 *                                      Functions Prototype                                       *
 **************************************************************************************************/

/********************************************************************************
 * Service Name: Port_Init
 * Service Id: 0X00
 * Parameters: ConfigPtr | Pointer to configuration set
 * Service Description: The function Port_Init shall initialize ALL ports and port pins
 *                      with the configuration set pointed to by the parameter
 ********************************************************************************/
void Port_Init
(
        const Port_ConfigType* ConfigPtr
);

/* Pre-compile option to keep set pin direction API or not */
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
/********************************************************************************
 * Service Name: Port_SetPinDirection
 * Service Id: 0X01
 * Parameters: Pin | Port Pin ID number, Direction | Port Pin Direction
 * Service Description: The function Port_SetPinDirection shall set the port pin
 *                      direction during runtime
 ********************************************************************************/
void Port_SetPinDirection
(
        Port_PinType Pin,
        Port_PinDirectionType Direction
);
#endif

/********************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service Id: 0X02
 * Parameters: none
 * Service Description: shall refresh the direction of all configured ports to the
 *                      configured direction
 ********************************************************************************/
void Port_RefreshPortDirection(void) ;

/* Pre-compile option to keep get version info API or not */
#if(PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
 * Service Name: Port_GetVersionInfo
 * Service ID: 0x03
 * Parameters: VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
void Port_GetVersionInfo(
        Std_VersionInfoType* versioninfo
);
#endif

/************************************************************************************
 * Service Name: Port_SetPinMode
 * Service ID: 0x04
 * Parameters: Pin | Port pin ID, Mode | New Port Pin mode to be set on port pin
 * Return value: None
 * Description: Function to  set the port pin mode of the referenced pin during runtime.
 ************************************************************************************/
void Port_SetPinMode (
        Port_PinType Pin,
        Port_PinModeType Mode
);

/************************************************************************************
 *                          Variable to use it in other files                       *
 ************************************************************************************/
extern Port_ConfigType Port_Pins [NUMBER_OF_PORT_PINS] ;
extern const uint16 Port_PortPinsMode[NUMBER_OF_PORT_PINS];


#endif /* PORT_H_ */
