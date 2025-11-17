 /******************************************************************************
 *
 * File Name: Port_Cfg.h
 *
 * Module: Port
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/* The vendors id */
#define PORT_VENDOR_ID                                      (1111U)

/* Port Module Id */
#define PORT_MODULE_ID                                      (125U)

/* Port Instance Id */
#define PORT_INSTANCE_ID                                    (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION                           (1U)
#define PORT_CFG_SW_MINOR_VERSION                           (0U)
#define PORT_CFG_SW_PATCH_VERSION                           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION                   (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION                   (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION                   (3U)

/* pre-compile option to detect the development errors */
#define PORT_DEV_ERROR_DETECT               (STD_ON)

/* pre-compile option to keep the set pin direction API */
#define PORT_SET_PIN_DIRECTION_API          (STD_ON)

/* Pre-compile option to keep get version info API or not */
#define PORT_VERSION_INFO_API               (STD_ON)

/* Number of the port pins on the ECU */
#define NUMBER_OF_PORT_PINS                 (Port_PinType)43

/* The general case for any port pin to be DIO */
#define PORT_PIN_DIO_MODE                   (Port_PinModeType)0
/***********************************************************************************
 *                               Port A Pins Macros                                *
 ***********************************************************************************/
#define PORT_A_ID                           (uint8)0

#define PORT_A_PIN_0                        (Port_PinType)0
#define PORT_A_PIN_1                        (Port_PinType)1
#define PORT_A_PIN_2                        (Port_PinType)2
#define PORT_A_PIN_3                        (Port_PinType)3
#define PORT_A_PIN_4                        (Port_PinType)4
#define PORT_A_PIN_5                        (Port_PinType)5
#define PORT_A_PIN_6                        (Port_PinType)6
#define PORT_A_PIN_7                        (Port_PinType)7

/***********************************************************************************
 *                               Port B Pins Macros                                *
 ***********************************************************************************/
#define PORT_B_ID                           (uint8)1

#define PORT_B_PIN_0                        (Port_PinType)0
#define PORT_B_PIN_1                        (Port_PinType)1
#define PORT_B_PIN_2                        (Port_PinType)2
#define PORT_B_PIN_3                        (Port_PinType)3
#define PORT_B_PIN_4                        (Port_PinType)4
#define PORT_B_PIN_5                        (Port_PinType)5
#define PORT_B_PIN_6                        (Port_PinType)6
#define PORT_B_PIN_7                        (Port_PinType)7

/***********************************************************************************
 *                               Port C Pins Macros                                *
 ***********************************************************************************/
#define PORT_C_ID                           (uint8)2

#define PORT_C_PIN_0                        (Port_PinType)0
#define PORT_C_PIN_1                        (Port_PinType)1
#define PORT_C_PIN_2                        (Port_PinType)2
#define PORT_C_PIN_3                        (Port_PinType)3
#define PORT_C_PIN_4                        (Port_PinType)4
#define PORT_C_PIN_5                        (Port_PinType)5
#define PORT_C_PIN_6                        (Port_PinType)6
#define PORT_C_PIN_7                        (Port_PinType)7

/***********************************************************************************
 *                               Port D Pins Macros                                *
 ***********************************************************************************/
#define PORT_D_ID                           (uint8)3

#define PORT_D_PIN_0                        (Port_PinType)0
#define PORT_D_PIN_1                        (Port_PinType)1
#define PORT_D_PIN_2                        (Port_PinType)2
#define PORT_D_PIN_3                        (Port_PinType)3
#define PORT_D_PIN_4                        (Port_PinType)4
#define PORT_D_PIN_5                        (Port_PinType)5
#define PORT_D_PIN_6                        (Port_PinType)6
#define PORT_D_PIN_7                        (Port_PinType)7

/***********************************************************************************
 *                               Port E Pins Macros                                *
 ***********************************************************************************/
#define PORT_E_ID                           (uint8)4

#define PORT_E_PIN_0                        (Port_PinType)0
#define PORT_E_PIN_1                        (Port_PinType)1
#define PORT_E_PIN_2                        (Port_PinType)2
#define PORT_E_PIN_3                        (Port_PinType)3
#define PORT_E_PIN_4                        (Port_PinType)4
#define PORT_E_PIN_5                        (Port_PinType)5

/***********************************************************************************
 *                               Port F Pins Macros                                *
 ***********************************************************************************/
#define PORT_F_ID                           (uint8)5

#define PORT_F_PIN_0                        (Port_PinType)0
#define PORT_F_PIN_1                        (Port_PinType)1
#define PORT_F_PIN_2                        (Port_PinType)2
#define PORT_F_PIN_3                        (Port_PinType)3
#define PORT_F_PIN_4                        (Port_PinType)4

/***********************************************************************************
 *                  Port pins index macros in the post build array                 *
 ***********************************************************************************/

#define PORT_A_PIN_0_INDEX                        (Port_PinType)0
#define PORT_A_PIN_1_INDEX                        (Port_PinType)1
#define PORT_A_PIN_2_INDEX                        (Port_PinType)2
#define PORT_A_PIN_3_INDEX                        (Port_PinType)3
#define PORT_A_PIN_4_INDEX                        (Port_PinType)4
#define PORT_A_PIN_5_INDEX                        (Port_PinType)5
#define PORT_A_PIN_6_INDEX                        (Port_PinType)6
#define PORT_A_PIN_7_INDEX                        (Port_PinType)7

#define PORT_B_PIN_0_INDEX                        (Port_PinType)8
#define PORT_B_PIN_1_INDEX                        (Port_PinType)9
#define PORT_B_PIN_2_INDEX                        (Port_PinType)10
#define PORT_B_PIN_3_INDEX                        (Port_PinType)11
#define PORT_B_PIN_4_INDEX                        (Port_PinType)12
#define PORT_B_PIN_5_INDEX                        (Port_PinType)13
#define PORT_B_PIN_6_INDEX                        (Port_PinType)14
#define PORT_B_PIN_7_INDEX                        (Port_PinType)15

#define PORT_C_PIN_0_INDEX                        (Port_PinType)16
#define PORT_C_PIN_1_INDEX                        (Port_PinType)17
#define PORT_C_PIN_2_INDEX                        (Port_PinType)18
#define PORT_C_PIN_3_INDEX                        (Port_PinType)19
#define PORT_C_PIN_4_INDEX                        (Port_PinType)20
#define PORT_C_PIN_5_INDEX                        (Port_PinType)21
#define PORT_C_PIN_6_INDEX                        (Port_PinType)22
#define PORT_C_PIN_7_INDEX                        (Port_PinType)23

#define PORT_D_PIN_0_INDEX                        (Port_PinType)24
#define PORT_D_PIN_1_INDEX                        (Port_PinType)25
#define PORT_D_PIN_2_INDEX                        (Port_PinType)26
#define PORT_D_PIN_3_INDEX                        (Port_PinType)27
#define PORT_D_PIN_4_INDEX                        (Port_PinType)28
#define PORT_D_PIN_5_INDEX                        (Port_PinType)29
#define PORT_D_PIN_6_INDEX                        (Port_PinType)30
#define PORT_D_PIN_7_INDEX                        (Port_PinType)31

#define PORT_E_PIN_0_INDEX                        (Port_PinType)32
#define PORT_E_PIN_1_INDEX                        (Port_PinType)33
#define PORT_E_PIN_2_INDEX                        (Port_PinType)34
#define PORT_E_PIN_3_INDEX                        (Port_PinType)35
#define PORT_E_PIN_4_INDEX                        (Port_PinType)36
#define PORT_E_PIN_5_INDEX                        (Port_PinType)37

#define PORT_F_PIN_0_INDEX                        (Port_PinType)38
#define PORT_F_PIN_1_INDEX                        (Port_PinType)39
#define PORT_F_PIN_2_INDEX                        (Port_PinType)40
#define PORT_F_PIN_3_INDEX                        (Port_PinType)41
#define PORT_F_PIN_4_INDEX                        (Port_PinType)42

/******************************************************************************
 *                      Typedef for the port pins modes                       *
 ******************************************************************************/

/*********************************************************
 *                      Port A Modes                     *
 *********************************************************/
/*
 * PA0 Modes
 */
typedef enum {
    PORT_A0_DIO_MODE, PORT_A0_UART0_RX, PORT_A0_CAN1= 8
}Port_A0_Modes;

/*
 * PA1 Modes
 */
typedef enum {
    PORT_A1_DIO_MODE, PORT_A1_UART0_TX, PORT_A1_CAN1= 8
}Port_A1_Modes;

/*
 * PA2 Modes
 */
typedef enum {
    PORT_A2_DIO_MODE, PORT_A2_SSI0CLK= 2
}Port_2_Modes;

/*
 * PA3 Modes
 */
typedef enum {
    PORT_A3_DIO_MODE, PORT_A3_SSI0FSS= 2
}Port_A3_Modes;

/*
 * PA4 Modes
 */
typedef enum {
    PORT_A4_DIO_MODE, PORT_A4_SSI0_RX= 2
}Port_A4_Modes;

/*
 * PA5 Modes
 */
typedef enum {
    PORT_A5_DIO_MODE, PORT_A5_SSI0_TX= 2
}Port_A5_Modes;

/*
 * PA6 Modes
 */
typedef enum {
    PORT_A6_DIO_MODE, PORT_A6_I2C1_SCL= 3, PORT_A6_M1PWM2= 5
}Port_A6_Modes;

/*
 * PA7 Modes
 */
typedef enum {
    PORT_A7_DIO_MODE, PORT_A6_I2C1_SDA= 3, PORT_A6_M1PWM3= 5
}Port_A7_Modes;


/*********************************************************
 *                      Port B Modes                     *
 *********************************************************/
/*
 * PB0 Modes
 */
typedef enum {
    PORT_B0_DIO_MODE, PORT_B0_UART1_RX, PORT_B0_T2CCP0= 7
}Port_B0_Modes;

/*
 * PB1 Modes
 */
typedef enum {
    PORT_B1_DIO_MODE, PORT_B1_UART1_RX, PORT_B1_T2CCP1= 7
}Port_B1_Modes;

/*
 * PB2 Modes
 */
typedef enum {
    PORT_B2_DIO_MODE, PORT_B2_I2C0_SCL= 3, PORT_B2_T3CCP0= 7
}Port_B2_Modes;

/*
 * PB3 Modes
 */
typedef enum {
    PORT_B3_DIO_MODE, PORT_B3_I2C0_SDA= 3, PORT_B3_T3CCP1= 7
}Port_B3_Modes;

/*
 * PB4 Modes
 */
typedef enum {
    PORT_B4_DIO_MODE, PORT_B4_SSI2_CLK= 2, PORT_B4_M0PWM2= 4, PORT_B4_T1CCP0= 7, PORT_B4_CAN0_RX
}Port_B4_Modes;

/*
 * PB5 Modes
 */
typedef enum {
    PORT_B5_DIO_MODE, PORT_B5_SSI2_FSS= 2, PORT_B5_M0PWM3= 4, PORT_B5_T1CCP1= 7, PORT_B5_CAN0_TX
}Port_B5_Modes;

/*
 * PB6 Modes
 */
typedef enum {
    PORT_B6_DIO_MODE, PORT_B6_SSI2_RX= 2, PORT_B6_M0PWM0= 4, PORT_B6_T1CCP0= 7
}Port_B6_Modes;

/*
 * PB7 Modes
 */
typedef enum {
    PORT_B7_DIO_MODE, PORT_B7_SSI2_TX= 2, PORT_B6_M0PWM1= 4, PORT_B6_T0CCP1= 7
}Port_B7_Modes;

/*********************************************************
 *                      Port C Modes                     *
 *********************************************************/
/*
 * PC4 Modes
 */
typedef enum {
    PORT_C4_DIO_MODE, PORT_C4_UART4_RX, PORT_C4_UART1_RX, PORT_C4_M0PWM6= 4,
    PORT_C4_IDX1= 6, PORT_C4_WT0CCP0, PORT_C4_U1_RTS
}Port_C4_Modes;

/*
 * PC5 Modes
 */
typedef enum {
    PORT_C5_DIO_MODE, PORT_C5_UART4_TX, PORT_C5_UART1_TX, PORT_C5_M0PWM7= 4,
    PORT_C5_PHA1= 6, PORT_C5_WT0CCP1, PORT_C5_U1_CTS
}Port_C5_Modes;

/*
 * PC6 Modes
 */
typedef enum {
    PORT_C6_DIO_MODE, PORT_C6_UART3_RX, PORT_C6_PHB1= 6, PORT_C6_WT1CCP0,
    PORT_C6_USB0_EPEN
}Port_C6_Modes;

/*
 * PC7 Modes
 */
typedef enum {
    PORT_C7_DIO_MODE, PORT_C7_UART3_TX, PORT_C7_WT1CCP1, PORT_C6_USB0_PFLT
}Port_C7_Modes;


/************************************************************************************
 *                          Variable to use it in other files                       *
 ************************************************************************************/

#endif /* PORT_CFG_H_ */
