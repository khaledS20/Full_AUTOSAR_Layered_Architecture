 /******************************************************************************
 *
 * File Name: Port_Cfg.c
 *
 * Module: Port
 *
 * Description: Pre-Compile Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Khaled Saleh
 ******************************************************************************/

#include "Port_Cfg.h"
#include "Port.h"
/******************************************************************************
 * This is an array that help us to check on the pin modes in the port driver
 *
 * Description: As each port pin can have modes number from 0-15 (2 bytes) so we
 *              can make an array of uint16 (16 bits) and at each entry set the
 *              bits that only corresponds to the mode number that the port pin
 *              is configured to
 *
 * For Example: PA0 can be configured as DIO by putting (0) in the PCTL register
 *          OR  Configured as UART by putting (1) in the PCTL register
 *          OR  Configured as CAN by putting (8) in the PCTL register
 *
 *          so at PA0 index in the array we will set bit number (0,1,8)
 *
 * This array will consume only 86 bytes from the memory (2 bytes * 43 channel)
 ******************************************************************************/
const uint16 Port_PortPinsMode[NUMBER_OF_PORT_PINS]= {

                                  0x102, /* Set pin 1, 8 */
                                  0X102, /* Set pin 1, 8 */
                                  0X004, /* set pin 2    */
                                  0X004, /* set pin 2    */
                                  0X004, /* set pin 2    */
                                  0X004, /* set pin 2    */
                                  0X028, /* set pin 3, 5 */
                                  0X028, /* set pin 3, 5 */
                                  0X082, /* set pin 1, 7 */
                                  0X082, /* set pin 1, 7 */
                                  0X088, /* set pin 3, 7 */
                                  0X088, /* set pin 3, 7 */
                                  0X194, /* set pin 2, 4, 7, 8 */
                                  0X194, /* set pin 2, 4, 7, 8 */
                                  0X094, /* set pin 2, 4, 7 */
                                  0X094, /* set pin 2, 4, 7 */
                                  0x000, /*JTAG Pins */
                                  0x000, /*JTAG Pins */
                                  0x000, /*JTAG Pins */
                                  0x000, /*JTAG Pins */
                                  0X1D6, /* set pin 1, 2, 4, 6, 7, 8 */
                                  0X1D6, /* set pin 1, 2, 4, 6, 7, 8 */
                                  0X1C2, /* set pin 1, 6, 7, 8 */
                                  0x182, /* set pin 1, 7, 8 */
                                  0x0BE, /* clear pin 0, 6 */
                                  0x0BE, /* clear pin 0, 6 */
                                  0X196, /* set pin 1, 2, 4, 7, 8 */
                                  0X1C6, /* set pin 1, 2, 6, 7, 8 */
                                  0X082, /* set pin 1, 7 */
                                  0X082, /* set pin 1, 7 */
                                  0X0D2, /* set pin 1, 4, 6, 7 */
                                  0X1C2, /* set pin 1, 6, 7, 8 */
                                  0X002, /* set pin 1 */
                                  0X002, /* set pin 1 */
                                  0X000, /* only configured as DIO */
                                  0X000, /* only configured as DIO */
                                  0X13A, /* set pin 1, 3, 4, 5, 8 */
                                  0X13A, /* set pin 1, 3, 4, 5, 8 */
                                  0X3EE, /* clear pin 4 */
                                  0X6E6,
                                  0X4B4,
                                  0X4AC,
                                  0X1E0
};














