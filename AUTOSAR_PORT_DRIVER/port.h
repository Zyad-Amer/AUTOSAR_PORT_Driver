 /******************************************************************************
 *
 * Module: port
 *
 * File Name: port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Zyad Montaser
 ******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/* Id for the company in the AUTOSAR
 * for example Zyad Montaser's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* port Module Id */
#define PORT_MODULE_ID    (124U)

/* port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and port Module */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "port_Cfg.h"

/* AUTOSAR Version checking between port_Cfg.h and port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between port_Cfg.h and port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of port_Cfg.h does not match the expected version"
#endif

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

#define NUMBER_OF_IO_PINS 43
#define DEFAULT_PIN_MODE_GPIO 0
#define DEFAULT_PIN_DIRECTION_INPUT 0 /*Input*/
#define GPIO_Mode 0
#define ADC_Mode  10 /*temporarly*/

 /* Macros for port Status*/
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/******************************************************************************
 *                               API Service Id Macros                         *
 ******************************************************************************/
#define PORT_INIT_SID                   (uint8)0x00
#define PORT_SETPINDIRECTION_SID        (uint8)0x01
#define PORT_REFRESHPORTDIRECTION_SID   (uint8)0x02
#define PORT_GETVERSIONINFO_SID         (uint8)0x03
#define PORT_SETPINMODE_SID             (uint8)0x04

/*******************************************************************************
 *                               DET Error Codes                               *
 *******************************************************************************/

/*Invalid Pin ID */
#define PORT_E_PARAM_PIN                (uint8)0x0A

/* Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE   (uint8)0x0B

/* port_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG             (uint8)0x0C

/*API Port_SetPinMode service called with wrong mode*/
#define PORT_E_PARAM_INVALID_MODE       (uint8)0x0D

/*API Port_SetPinMode service called when mode is unchangeable*/
#define PORT_E_MODE_UNCHANGEABLE        (uint8)0x0E

/*API service used without module initialization*/
#define PORT_E_UNINIT                   (uint8)0x0F

/*APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER            (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Data type for the symbolic name of a port pin. */
typedef uint8 Port_PinType;

/*Data type for Different port pin modes */
typedef uint8 Port_PinModeType;

typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

typedef enum
{
    Mode_Changeable_OFF,Mode_Changeable_ON
}Port_ModeChangeable;

typedef enum
{
    PinDirectionChangeable_OFF,PinDirectionChangeable_ON
}Port_PinDirectionChangeable;

typedef enum
{
    PortA,PortB,PortC,PortD,PortE,PortF
}TivaC_Ports;

typedef enum
{
    Pin0,Pin1,Pin2,Pin3,Pin4,Pin5,Pin6,Pin7
}TivaC_Pins;

typedef struct
{
    TivaC_Ports port_num;
    TivaC_Pins pin_num;
    Port_PinModeType mode;
    Port_PinDirectionType direction;
    uint8 pin_initialValue; /* STD_HIGH or STD_LOW */
    Port_InternalResistor internal_Res;
    Port_ModeChangeable Mode_Changeable;
    Port_PinDirectionChangeable Direction_Changeable;
}pin_configuration;

/* Data Structure required for initializing the Port Driver */
typedef struct
{
    pin_configuration pins[NUMBER_OF_IO_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                              Function Prototypes                            *
 *******************************************************************************/


/*********************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Function to Initialize the Port Driver module.
**********************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );


/*********************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): pin - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Function to Set the port pin direction.
**********************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif


/*********************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Function to Refreshe port direction.
**********************************************************************/
void Port_RefreshPortDirection( void );


/*********************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out):versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description:Function to Return the version information of this module..
**********************************************************************/
#if (PORT_VERSION_INFO_API ==STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


/*********************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description:Function to Set the port pin mode.
**********************************************************************/
#if (PORT_SET_PIN_MODE_API ==STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by PORT and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H_ */
