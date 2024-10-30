 /******************************************************************************
 *
 * Module: port
 *
 * File Name: port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - port Driver
 *
 * Author: Zyad Montaser
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

 /* Module Version 1.0.0*/
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)



/**************************** PortGeneral container configurations **************************/

/* pre-compile option to Switch the Development Error Detection
 * and Notification on or off. */
#define PORT_DEV_ERROR_DETECT       (STD_ON)

/*Pre-compile option to enable / disable the use of the function Port_SetPinDirection().*/
#define PORT_SET_PIN_DIRECTION_API  (STD_ON)

/*Pre-compile option to enable / disable the use of the function Port_SetPinMode().*/
#define PORT_SET_PIN_MODE_API       (STD_ON)

/*Pre-compile option to enable / disable the API to read out the modules version information*/
#define PORT_VERSION_INFO_API       (STD_ON)

/**************************** PortConfigSet container configurations*************************/

#define PORT_NUMBER_OF_PORT_PINS
#define PORT_PIN_DIRECTION
#define PORT_PIN_DIRECTION_CHANGEABLE
#define PortPinId
#define PORT_PIN_INITIAL_MODE
#define PORT_PIN_LEVEL_VALUE
#define PORT_PIN_MODE
#define PORT_PIN_MODE_CHANGEABLE


#endif /* PORT_CFG_H_ */
