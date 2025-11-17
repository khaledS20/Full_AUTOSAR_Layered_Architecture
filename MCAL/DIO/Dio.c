/******************************************************************************
 * File Name: dio.c
 *
 * Module: Dio
 *
 * File Description: A source file that contain the functions implementations
 *
 * Author: Khaled Saleh
 ******************************************************************************/
#include "dio.h"
#include "Dio_Regs.h"

/*
 * if the DET errors is enabled
 */
#if(DIO_DEV_ERROR_DETECT == STD_ON)
#include "Service_Layer\Det_Errors\Det.h"
/* AUTOSAR version checking between the DET and DIO modules */
#if((DIO_AR_RELEASE_MAJOR_VERSION != DET_AR_MAJOR_VERSION)\
        || (DIO_AR_RELEASE_MINOR_VERSION != DET_AR_MINOR_VERSION)\
        || (DIO_AR_RELEASE_PATCH_VERSION != DET_AR_PATCH_VERSION))
#endif
#endif

/*
 * Pointer to the configuration structure to be passed to the DIO init API
 */
STATIC const Dio_ConfigChannel* Dio_PortChannels = NULL_PTR ;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED ;

/********************************************************************************
 * Service Name: Dio_Init
 * Service Id: 0X10
 * Parameters: pointer to the post build configuration data
 * Service Description: Function that initialize all the global variables and
 *                      channels of used in the DIO module
 ********************************************************************************/
void Dio_Init
(
        const Dio_ConfigType * ConfigPtr
)
{
    /* check on if the pointer passed by the user is not NULL */
#if(DIO_DEV_ERROR_DETECT == STD_ON)
    if(ConfigPtr == NULL_PTR)
    {
        Det_ReportError(
                DIO_MODULE_ID,
                DIO_INSTANCE_ID,
                DIO_INIT_SID,
                DIO_E_PARAM_CONFIG
        ) ;
    }
    else
#endif
    {
        /* Set the status of the dio to initialized */
        Dio_Status= DIO_INITIALIZED;

        /* set the pointer of the Struct */
        Dio_PortChannels = ConfigPtr->Channels ;
    }
}

/*********************************************************************************
 * Service Name: Dio_ReadChannel
 * Service Id: 0X00
 * Parameters: Dio_ChannelType ChannelId
 * Service Description: Function That read the value of the channel passed to it
 *********************************************************************************/
Dio_LevelType Dio_ReadChannel
(
        Dio_ChannelType ChannelId
)
{
    volatile uint32 * Port_Ptr = NULL_PTR ;
    uint8 ch_level = STD_LOW ;
    boolean error = FALSE ;
    /*******************************************************
     *              If DET error is enabled                *
     *******************************************************/
#if(DIO_DEV_ERROR_DETECT == STD_ON)
    /*
     * If the DIO module is not initialized
     */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_READ_CHANNEL_SID, DIO_E_UNINIT);
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }

    /*
     * if the parameter received is unused channel id
     */
    if(ChannelId >= DIO_CONFIGURED_CHANNELS)
    {
        Det_ReportError(
                DIO_MODULE_ID,
                DIO_INSTANCE_ID,
                DIO_READ_CHANNEL_SID,
                DIO_E_PARAM_INVALID_CHANNEL_ID
        ) ;
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /**************************************************
     *          If no DET error is detected           *
     **************************************************/
    if(FALSE == error)
    {
        /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
        switch(Dio_PortChannels[ChannelId].portNum)
        {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
                       break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
                       break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
                       break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
                       break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
                       break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
                       break;
        }
        if((*Port_Ptr) & (1<<Dio_PortChannels[ChannelId].channelNum))
        {
            ch_level = STD_HIGH ;
        }
        else
        {
            ch_level = STD_LOW ;
        }
    }
    return ch_level ;
}

/*********************************************************************************
 * Service Name:  Dio_WriteChannel
 * Service Id: 0x01
 * Parameters: ID of DIO Channel, Level of the channel
 * Service Description: Function That writes the value to the channel passed to it
 *********************************************************************************/
void Dio_WriteChannel(
        Dio_ChannelType ChannelId,
        Dio_LevelType Level )
{
    volatile uint32 * Port_Ptr = NULL_PTR ;
    boolean error= FALSE ;

    /*******************************************************
     *              If DET error is enabled                *
     *******************************************************/
#if(DIO_DEV_ERROR_DETECT == STD_ON)
    /*
     * If the DIO module is not initialized
     */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_WRITE_CHANNEL_SID, DIO_E_UNINIT);
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }

    /*
     * if the parameter received is unused channel id
     */
    if(ChannelId >= DIO_CONFIGURED_CHANNELS)
    {
        Det_ReportError(
                DIO_MODULE_ID,
                DIO_INSTANCE_ID,
                DIO_WRITE_CHANNEL_SID,
                DIO_E_PARAM_INVALID_CHANNEL_ID
        ) ;
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /**************************************************
     *          If no DET error is detected           *
     **************************************************/
    {
        if(FALSE == error)
        {
            /* Get the Port address */
            switch (Dio_PortChannels[ChannelId].portNum)
            {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
            }
            /* check on the direction of the channel */
            /*
             * To get the address of the direction register: cast the port pointer to pointer to unsigned
             * char to increment or decrement it by 1 byte only not by the size of the pointer(4 bytes)
             */
            if((1<<Dio_PortChannels[ChannelId].channelNum) & PORT_DIRECTION_REGISTER)
            {
                /*
                 * If the channel is output: check on the level passed to the API
                 */
                if(Level == STD_HIGH)
                {
                    /* If the level is logic high */
                    SET_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].channelNum) ;
                }
                else if(STD_LOW == Level)
                {
                    /* If the level is logic low */
                    CLEAR_BIT(*Port_Ptr,Dio_PortChannels[ChannelId].channelNum) ;
                }
            }
            else
            {
                /* the channel is input no write is required */
            }
        }
    }
}
/*********************************************************************************
 * Service Name:  Dio_ReadPort
 * Service Id: 0x02
 * Parameters: ID of DIO Port
 * Service Description: Function That reads the value to the port passed to it
 *********************************************************************************/
Dio_PortLevelType Dio_ReadPort(
        Dio_PortType PortId )
{
    volatile uint32 * Port_Ptr = NULL_PTR ;
    uint8 port_level = STD_LOW ;
    boolean error = FALSE ;
    /*******************************************************
     *              If DET error is enabled                *
     *******************************************************/
#if( STD_ON == DIO_DEV_ERROR_DETECT )
    /*
     * If the DIO module is not initialized
     */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_READ_PORT_SID, DIO_E_UNINIT);
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }

    /*
     * if the parameter received is unused channel id
     */
    if(Dio_PortChannels[PortId].portNum >= DIO_NUMBER_OF_PORTS)
    {
        Det_ReportError(
                DIO_MODULE_ID,
                DIO_INSTANCE_ID,
                DIO_READ_PORT_SID,
                DIO_E_PARAM_INVALID_PORT_ID
        ) ;
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /**************************************************
     *          If no DET error is detected           *
     **************************************************/
    {
        if(FALSE == error)
        {
            /* Get the Port address */
            switch (Dio_PortChannels[PortId].portNum)
            {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
            }
            /* Save the value of the data register then return it */
            port_level= *Port_Ptr ;
        }
        return port_level ;
    }
}
/************************************************************************************
 * Service Name: Dio_WritePort
 * Service ID: 0x11
 * Parameters (in): ID of port.
 * Return value: None
 * Description: Function to write the whole port.
 ************************************************************************************/
void Dio_WritePort(
        Dio_PortType PortId,
        Dio_PortLevelType Level )
{
    volatile uint32 * Port_Ptr = NULL_PTR ;
    uint8 Input_Mask= 0XFF ;
    boolean error = FALSE ;
    /*******************************************************
     *              If DET error is enabled                *
     *******************************************************/
#if( STD_ON == DIO_DEV_ERROR_DETECT )
    /*
     * If the DIO module is not initialized
     */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_WRITE_PORT_SID, DIO_E_UNINIT);
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }

    /*
     * if the port id is larger than the number of ports in the MCU
     */
    if(Dio_PortChannels[PortId].portNum > DIO_NUMBER_OF_PORTS)
    {
        Det_ReportError(
                DIO_MODULE_ID,
                DIO_INSTANCE_ID,
                DIO_WRITE_PORT_SID,
                DIO_E_PARAM_INVALID_PORT_ID
        ) ;
        error= TRUE ;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /**************************************************
     *          If no DET error is detected           *
     **************************************************/
    {
        if( FALSE == error )
        {
            /* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
            switch(Dio_PortChannels[PortId].portNum)
            {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
            }
            /* Get the input channels first before writing */
            Input_Mask = PORT_DIRECTION_REGISTER ;
            /*
             * Logical and between the Level value and the mask to clear the input bits values
             */
            Level &= Input_Mask ;
            /*
             * setting now the input bits in the level passed to the API to their original values
             */
            Level |= (~Input_Mask & *Port_Ptr) ;
            /*
             * write the value to the data register
             */
            *Port_Ptr= Level ;
        }
    }
}
/************************************************************************************
 * Service Name: Dio_ReadChannelGroup
 * Service ID: 0x04
 * Parameters: ChannelGroupIdPtr - Pointer to ChannelGroup
 * Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
 * Description: Function that reads a subset of adjoining bits of a port
 ************************************************************************************/
Dio_PortLevelType Dio_ReadChannelGroup(
        const Dio_ChannelGroupType* ChannelGroupIdPtr )
{
    volatile uint32* Port_Ptr = NULL_PTR ;
    uint8 error = FALSE ;
    uint8 group_level = STD_LOW ;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == ChannelGroupIdPtr)
    {
        /* Report to DET */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
        error= TRUE ;
    }
    else
    {
        /* No action */
    }

    /* If the pointer points to invalid group */
    if(DIO_NUMBER_OF_PORTS <= ChannelGroupIdPtr->port)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_READ_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP );
        error= TRUE ;
    }
    else
    {
        /* No Actions */
    }
#endif
    {
        /*********************************
         *  If no DET errors id detected *
         *********************************/
        if(FALSE == error)
        {
            /* Get the Port address */
            switch(ChannelGroupIdPtr->port)
            {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
            }
            /*
             * 1) Logical and between the data register and the mask in the structure
             *    to get the group level
             *
             * 2) Shift left the result by the offset to move the group to the LSB
             */
            group_level = *Port_Ptr & ChannelGroupIdPtr->mask ;
            group_level = (group_level>>ChannelGroupIdPtr->offset) ;
        }
        return group_level ;
    }
}
/************************************************************************************
 * Service Name: Dio_WriteChannelGroup
 * Service ID: 0x05
 * Parameters: ChannelGroupIdPtr - Pointer to ChannelGroup
 * Return value: Dio_PortLevelType - Level of a subset of the adjoining bits of a port
 *               Level             - value to be written
 * Description: Function that reads a subset of adjoining bits of a port
 ************************************************************************************/
void Dio_WriteChannelGroup(
        const Dio_ChannelGroupType* ChannelGroupIdPtr,
        Dio_PortLevelType Level )
{
    volatile uint32* Port_Ptr = NULL_PTR ;
    uint8 error = FALSE ;
    uint8 Input_Mask = 0XFF ;

#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == ChannelGroupIdPtr)
    {
        /* Report to DET */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_POINTER);
        error= TRUE ;
    }
    else
    {
        /* No action */
    }

    /* If the pointer points to invalid group */
    if(DIO_NUMBER_OF_PORTS <= ChannelGroupIdPtr->port)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                                DIO_WRITE_CHANNEL_GROUP_SID, DIO_E_PARAM_INVALID_GROUP );
        error= TRUE ;
    }
    else
    {
        /* No Actions */
    }
#endif
    {
        /*********************************
         *  If no DET errors id detected *
         *********************************/
        if(FALSE == error)
        {
            /* Get the Port address */
            switch(ChannelGroupIdPtr->port)
            {
            case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
            break;
            case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
            break;
            case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
            break;
            case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
            break;
            case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
            break;
            case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
            break;
            }
            /* Shift left the level value to the position of the group */
            Level = (Level<<ChannelGroupIdPtr->offset) ;
            /*
             * after getting the port data address:
             * 1) logical and between the and the direction register to avoid writing
             *    to input channels that is included in the group
             */
            Input_Mask = PORT_DIRECTION_REGISTER & ChannelGroupIdPtr->mask ;
            /*
             * 2) logical and between the input mask and the level passed to the API
             *    to clear the data sent of the input channel
             */
            Level &= Input_Mask ;
            /*
             * 3) logical and between the inverse of the input mask and data register
             * 4) logical or between the result and the level(after clearing the input channels bits in the level variable)
             *      -> To keep the values of the input channels as its
             */
            Level |= (~Input_Mask & *Port_Ptr) ;

            *Port_Ptr = (*Port_Ptr & ~ChannelGroupIdPtr->mask ) | Level ;
        }
    }
}
/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID: 0x11
 * Parameters (in): ID of DIO channel.
 * Return value: Dio_LevelType
 * Description: Function to flip the level of a channel and return the level of the channel after flip.
 ************************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    volatile uint32 * Port_Ptr = NULL_PTR;
    boolean error = FALSE;
    uint8 ch_level = STD_LOW ;

#if(DIO_DEV_ERROR_DETECT == STD_ON)

    /* Check if the Driver is initialized before using this function */
    if (DIO_NOT_INITIALIZED == Dio_Status)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_FLIP_CHANNEL_SID, DIO_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if (DIO_CONFIGURED_CHANNELS <= ChannelId)
    {
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_FLIP_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID) ;

        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    if(FALSE == error)
    {
        /* Get the Port address */
        switch(Dio_PortChannels[ChannelId].portNum)
        {
        case 0:    Port_Ptr = &GPIO_PORTA_DATA_REG;
        break;
        case 1:    Port_Ptr = &GPIO_PORTB_DATA_REG;
        break;
        case 2:    Port_Ptr = &GPIO_PORTC_DATA_REG;
        break;
        case 3:    Port_Ptr = &GPIO_PORTD_DATA_REG;
        break;
        case 4:    Port_Ptr = &GPIO_PORTE_DATA_REG;
        break;
        case 5:    Port_Ptr = &GPIO_PORTF_DATA_REG;
        break;
        }
        /* Check if the channel to be inverted is output or not */
        if(PORT_DIRECTION_REGISTER & (1<<Dio_PortChannels[ChannelId].channelNum))
        {
            /*
             * XORing the required channel with 1 to flip it
             */
            *Port_Ptr ^= (1<<Dio_PortChannels[ChannelId].channelNum) ;
            if((*Port_Ptr) & (1<<Dio_PortChannels[ChannelId].channelNum))
            {

                ch_level = STD_HIGH ;
            }
            else
            {
                ch_level = STD_LOW ;
            }
        }
        else
        {
            /* if the channel is input do nothing */
        }
    }
    return ch_level ;
}
#endif

/************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Service ID: 0x12
 * Parameters: VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
                        DIO_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)DIO_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
    }
}
#endif



