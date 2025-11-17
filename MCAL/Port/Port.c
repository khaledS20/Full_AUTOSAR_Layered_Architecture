 /******************************************************************************
 * File Name: Port.c
 *
 * Module: Port
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Khaled Saleh
 ******************************************************************************/
#include "Port.h"
#include "Port_Regs.h"

#if(STD_ON == PORT_DEV_ERROR_DETECT)

#include "Service_Layer\Det_Errors\Det.h"
/* AUTOSAR version checking between the DET and DIO modules */
#if(   (PORT_AR_RELEASE_MAJOR_VERSION != DET_AR_MAJOR_VERSION)\
    || (PORT_AR_RELEASE_MINOR_VERSION != DET_AR_MINOR_VERSION)\
    || (PORT_AR_RELEASE_PATCH_VERSION != DET_AR_PATCH_VERSION))

      #error "The port and DET modules AUTOSAR versions aren't compatible"
#endif
#endif

STATIC boolean PortModule_Initialized= FALSE;
STATIC const Port_ConfigType * Port_Pin = NULL_PTR;

/********************************************************************************
 * Service Name: Port_Init
 * Service Id: 0X00
 * Parameters: ConfigPtr | Pointer to configuration set
 * Service Description: The function Port_Init shall initialize ALL ports and port pins
 *                      with the configuration set pointed to by the parameter
 ********************************************************************************/
void Port_Init (
        const Port_ConfigType* ConfigPtr
)
{
    boolean error = FALSE ;
    uint8 portId = 0 ;
    volatile uint32 *Port_Ptr = NULL_PTR;
    uint8 ConfiguredChannelsCounter= 0;

#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /*
     * check if the user send a NULL pointer
     */
    if(NULL_PTR == ConfigPtr)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_INIT_SID,
                PORT_E_PARAM_CONFIG
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }
#endif

    if(FALSE == error)
    {
        Port_Pin= ConfigPtr;
        PortModule_Initialized= TRUE ;
        /****************************************************************************
         *                          No DET errors is detected                       *
         ****************************************************************************/
        for(ConfiguredChannelsCounter= 0 ; ConfiguredChannelsCounter < NUMBER_OF_PORT_PINS ; ConfiguredChannelsCounter++)
        {
            /* Get the id of the port to know which port we are configuring it */
            portId= ConfigPtr->Port_Num ;

            /* Skip the current pin configuration if its C0 C1 C2 C3 (JTAG pins) */
            if((PORT_C_ID == portId))
            {
                /* Increment the configuration pointer to points on the following structure */
                ConfigPtr++ ;
                continue ;
            }

            /* Get the base address of the port */
            switch(portId)
            {
            case 0:     Port_Ptr= PORTA_BASE_ADDERSS;
                        break;
            case 1:     Port_Ptr= PORTB_BASE_ADDRESS;
                        break;
            case 2:     Port_Ptr= PORTC_BASE_ADDRESS;
                        break;
            case 3:     Port_Ptr= PORTD_BASE_ADDRESS;
                        break;
            case 4:     Port_Ptr= PORTE_BASE_ADDRESS;
                        break;
            case 5:     Port_Ptr= PORTF_BASE_ADDRESS;
                        break;
            }
            /*
             * unlock the lock register to be able to change the values of PD7 and PF0
             */
            if( (PORT_D_ID == portId) && (PORT_D_PIN_7 == ConfigPtr->PortPin_Num)
             || ((PORT_F_ID == portId) && (PORT_F_PIN_0 == ConfigPtr->PortPin_Num)))
            {
                PORT_LOCK_REG = 0X4C4F434B ;

                /* Set the port pin bit in the commit register to enable changes */
                SET_BIT(PORT_CR_REG,ConfigPtr->PortPin_Num);
            }

            /************** Configure the port pin to be digital or analog pin **************
             *
             * 1- if the digital signal is enabled -> set the port pin bit in the DEN REG
             *                                      & clear it in the AMSEL REG
             *
             * 2- if the analog signal is enabled -> clear the port pin bit in the DEN REG
             *                                     & set it in the AMSEL REG
             ********************************************************************************/
            switch(ConfigPtr->PortPin_DEN)
            {
            /* If the digital signal is enabled */
            case TRUE:              SET_BIT(PORT_DEN_REG,ConfigPtr->PortPin_Num);
                                    CLEAR_BIT(PORT_AMSEL_REG,ConfigPtr->PortPin_Num);
                                    break;

            /* if the digital signal is disabled */
            case FALSE:             CLEAR_BIT(PORT_DEN_REG,ConfigPtr->PortPin_Num);
                                    SET_BIT(PORT_AMSEL_REG,ConfigPtr->PortPin_Num);
                                    break;
            }

            /************************** Setting the port pin mode ************************
             *
             * 1- If the port pin is configured to be GPIO clear the port pin bit in the
             *    AFSEL REG
             * 2- If the the port pin is configured as special function set its bit in the
             *    AFSEL REG and put its mode value in the PCTRL REG
             *****************************************************************************/
            if(PORT_PIN_DIO_MODE == ConfigPtr->PortPin_Mode)
            {
                /*
                 * the port pin is configured as DIO port pin
                 */

                /* Disable the alternative function of the port pin */
                CLEAR_BIT(PORT_AFSEL_REG,ConfigPtr->PortPin_Num);

                /*clearing the port pin 4 bits in the PCTL register */
                PORT_PCTL_REG &= ~(0X0F << (ConfigPtr->PortPin_Num * 4));
            }
            else
            {
                /* Enable the port pin bit in the alternative function */
                SET_BIT(PORT_AFSEL_REG,ConfigPtr->PortPin_Num);

                /* Set the port pin 4 bits in the PCTL register to the configured mode */
                PORT_PCTL_REG |= (ConfigPtr->PortPin_Mode << (ConfigPtr->PortPin_Num * 4));
            }

            /***** Setting the port pin direction, initial value and pull up resistors ******
             *
             * 1- Get the direction register address
             * 2- Set the direction of the current pin
             * 3- if the pin is output pin then set its initial value
             * 4- if the port pin is input enable/disable the pull up resistor
             ********************************************************************************/
            if(PORT_PIN_OUT == ConfigPtr->PortPin_Direction)
            {
                /* configure the port pin to output channel */
                SET_BIT(PORT_DIR_REG,ConfigPtr->PortPin_Num) ;

                /* Check on the initial value of the port pin */
                if(STD_HIGH == ConfigPtr->PortPin_InitialValue)
                {
                    SET_BIT(PORT_DATA_REG,ConfigPtr->PortPin_Num);
                }
                else
                {
                    CLEAR_BIT(PORT_DATA_REG,ConfigPtr->PortPin_Num);
                }
            }
            else
            {
                /* configure the port pin to input channel */
                CLEAR_BIT(PORT_DIR_REG,ConfigPtr->PortPin_Num) ;

                /* enable/disable the pull up resistor */
                if(TRUE == ConfigPtr->PortPin_EnablePUR)
                {
                    /* Enable the pull up register of the current port pin */
                    SET_BIT(PORT_PUR_REG,ConfigPtr->PortPin_Num);
                }
                else
                {
                    /* Disable the pull up register of the current port pin */
                    CLEAR_BIT(PORT_PUR_REG,ConfigPtr->PortPin_Num);
                }
            }
            /* Increment the configuration pointer to points on the following structure */
            ConfigPtr++ ;
        }
    }
    else
    {
        /* No action */
    }
}

/* Pre-compile option to keep set pin direction API or not */
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
/********************************************************************************
 * Service Name: Port_SetPinDirection
 * Service Id: 0X01
 * Parameters: Pin | Port Pin ID number, Direction | Port Pin Direction
 * Service Description: The function Port_SetPinDirection shall set the port pin
 *                      direction during runtime
 ********************************************************************************/
void Port_SetPinDirection (
        Port_PinType Pin,
        Port_PinDirectionType Direction
)
{
    volatile uint32 * Port_Ptr= NULL_PTR;
    boolean error = FALSE ;

#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /*
     * Check if the port module isn't initialized
     */
    if(FALSE == PortModule_Initialized)
        {
            /* Report a DET error */
            Det_ReportError(
                    PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_UNINIT
            );
            error = TRUE ;
        }
        else
        {
            /* No action */
        }

    /*
     * check if the API received invalid port pin id
     */
    if(NUMBER_OF_PORT_PINS <= Pin)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_SET_PIN_DIRECTION_SID,
                PORT_E_PARAM_PIN
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }

    /*
     * Check if the port pin direction isn't changeable
     */
    if(FALSE == Port_Pin[Pin].PortPin_DirChangeable)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_SET_PIN_DIRECTION_SID,
                PORT_E_DIRECTION_UNCHANGEABLE
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }

#endif

    if(FALSE == error)
    {
        /****************************************************************************
         *                          No DET errors is detected                       *
         ****************************************************************************/

        /* Get the base address of the port */
        switch(Port_Pins[Pin].Port_Num)
        {
        case 0:     Port_Ptr= PORTA_BASE_ADDERSS;
                    break;
        case 1:     Port_Ptr= PORTB_BASE_ADDRESS;
                    break;
        case 2:     Port_Ptr= PORTC_BASE_ADDRESS;
                    break;
        case 3:     Port_Ptr= PORTD_BASE_ADDRESS;
                    break;
        case 4:     Port_Ptr= PORTE_BASE_ADDRESS;
                    break;
        case 5:     Port_Ptr= PORTF_BASE_ADDRESS;
                    break;
        }

        /* Now set the new direction of the port pin */
        if(PORT_PIN_IN == Direction)
        {
            /* Configure the port pin to input */
            CLEAR_BIT(PORT_DIR_REG,Port_Pin[Pin].PortPin_Num);
        }
        else
        {
            /* Configure the port pin to input */
            SET_BIT(PORT_DIR_REG,Port_Pin[Pin].PortPin_Num);
        }
    }
    else
    {
        /* No action */
    }
}
#endif

/********************************************************************************
 * Service Name: Port_RefreshPortDirection
 * Service Id: 0X02
 * Parameters: none
 * Service Description: shall refresh the direction of all configured ports to the
 *                      configured direction
 ********************************************************************************/
void Port_RefreshPortDirection(void)
{
    boolean error = FALSE ;
    volatile uint32 *Port_Ptr = NULL_PTR;
    uint8 index= 0;

#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /*
     * check if port module is not initialized
     */
    if(FALSE == PortModule_Initialized)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_REFRESH_PORT_DIRECTION_SID,
                PORT_E_UNINIT
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }

#endif

    if(FALSE == error)
    {
        /****************************************************************************
         *                          No DET errors is detected                       *
         ****************************************************************************/
        for(index= 0 ; index < NUMBER_OF_PORT_PINS ; index++)
        {

            /* Skip the current pin configuration if its C0 C1 C2 C3 (JTAG pins) */
            if((PORT_C_ID == Port_Pin[index].PortPin_Num))
            {
                continue ;
            }

            /* Get the base address of the port */
            switch(Port_Pin[index].Port_Num)
            {
            case 0:     Port_Ptr= PORTA_BASE_ADDERSS;
                        break;
            case 1:     Port_Ptr= PORTB_BASE_ADDRESS;
                        break;
            case 2:     Port_Ptr= PORTC_BASE_ADDRESS;
                        break;
            case 3:     Port_Ptr= PORTD_BASE_ADDRESS;
                        break;
            case 4:     Port_Ptr= PORTE_BASE_ADDRESS;
                        break;
            case 5:     Port_Ptr= PORTF_BASE_ADDRESS;
                        break;
            }
            /* If the direction is not changeable during runtime refresh the direction */
            if(FALSE == Port_Pin[index].PortPin_DirChangeable)
            {
                /*
                 * Refresh the direction of the port pin by the direction mentioned during
                 * the post build time
                 */
                CLEAR_BIT(PORT_DIR_REG,Port_Pin[index].PortPin_Num) ;
                PORT_DIR_REG |= (Port_Pin[index].PortPin_Direction<<Port_Pin[index].PortPin_Num);
            }
            else
            {
                /* No action */
            }
        }
    }
}

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
)
{
    volatile uint32 * Port_Ptr= NULL_PTR;
    boolean error = FALSE ;

#if(STD_ON == PORT_DEV_ERROR_DETECT)

    /*
     * Check if the port module isn't initialized
     */
    if(FALSE == PortModule_Initialized)
        {
            /* Report a DET error */
            Det_ReportError(
                    PORT_MODULE_ID,
                    PORT_INSTANCE_ID,
                    PORT_SET_PIN_MODE_SID,
                    PORT_E_UNINIT
            );
            error = TRUE ;
        }
        else
        {
            /* No action */
        }

    /*
     * check if the API received invalid port pin id
     */
    if(NUMBER_OF_PORT_PINS <= Pin)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_SET_PIN_MODE_SID,
                PORT_E_PARAM_PIN
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }

    /*
     * Check if the port pin direction isn't changeable
     */
    if(FALSE == Port_Pin[Pin].PortPin_ModeChangeable)
    {
        /* Report a DET error */
        Det_ReportError(
                PORT_MODULE_ID,
                PORT_INSTANCE_ID,
                PORT_SET_PIN_MODE_SID,
                PORT_E_MODE_UNCHANGEABLE
        );
        error = TRUE ;
    }
    else
    {
        /* No action */
    }

#endif

    if(FALSE == error)
    {
        /****************************************************************************
         *                          No DET errors is detected                       *
         ****************************************************************************/

        /* Get the base address of the port */
        switch(Port_Pin[Pin].Port_Num)
        {
        case 0:     Port_Ptr= PORTA_BASE_ADDERSS;
                    break;
        case 1:     Port_Ptr= PORTB_BASE_ADDRESS;
                    break;
        case 2:     Port_Ptr= PORTC_BASE_ADDRESS;
                    break;
        case 3:     Port_Ptr= PORTD_BASE_ADDRESS;
                    break;
        case 4:     Port_Ptr= PORTE_BASE_ADDRESS;
                    break;
        case 5:     Port_Ptr= PORTF_BASE_ADDRESS;
                    break;
        }
        /* Only if the port mode is changeable during the run time change the mode */
        if(TRUE == Port_Pin[Pin].PortPin_ModeChangeable)
        {
            /* Case the configuration mode is DIO */
            if(PORT_PIN_DIO_MODE == Mode)
            {
                /* Clear its Alternative function bit */
                CLEAR_BIT(PORT_AFSEL_REG,Port_Pin[Pin].PortPin_Num);

                /* Clear the port pin's 4 bits in the PCTRL register */
                PORT_PCTL_REG &= ~(0X0F << (Port_Pin[Pin].PortPin_Num * 4));
            }
            else
            {
                /**************************************************************
                 * If the mode is not DIO then we have to check if the mode
                 * is valid for the current port pin or not
                 **************************************************************/

                /*
                 * As explained in the Port_Cfg.c:
                 * If we shifted 1 by the mode sent by the user and do a logical AND with the
                 * content in the index of the pin in the Port_PortPinsMode array  of this
                 * operation  is 0 then this mode is not supported by the current pin
                 *
                 * Because we set each bit correspond to a mode number supported by the pin to 1
                 * so if the the operation result is zero --> mode is not supported
                 */
                if((Port_PortPinsMode[Pin] & (1<<Mode)))
                {
                    /* Set the port pin bit in the AFSEL register */
                    SET_BIT(PORT_AFSEL_REG,Port_Pin[Pin].PortPin_Num);

                    /* Clear the port pins 4 bits in the PCTL register then set the new mode value */
                    PORT_PCTL_REG &= ~(0X0F << Port_Pin[Pin].PortPin_Num *4) ;
                    PORT_PCTL_REG |= (Mode << Port_Pin[Pin].PortPin_Num*4) ;
                }

                /*
                 * if the mode is not supported by the pin we had to check first if the development
                 * errors is enabled or no not
                 *
                 * if enabled -> Report a DET error
                 * if not enabled -> clear this code segment in the compile time
                 */
#if(STD_ON == PORT_DEV_ERROR_DETECT)
                else
                {
                    Det_ReportError(
                                    PORT_MODULE_ID,
                                    PORT_INSTANCE_ID,
                                    PORT_SET_PIN_MODE_SID,
                                    PORT_E_PARAM_INVALID_MODE
                            );
                }
#endif
            }
        }
        else
        {
            /* No action */
        }
    }
    else
    {
        /* No action */
    }
}

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
)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}

#endif

