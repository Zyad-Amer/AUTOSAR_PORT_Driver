 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - port Driver
 *
 * Author: Zyad Montaser
 ******************************************************************************/

#include "port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between port_PBcfg.c and port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between port_PBcfg.c and port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration =
{
    {PortA,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin1,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin4,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin5,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin6,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortA,Pin7,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},

    {PortB,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin1,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin4,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin5,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin6,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortB,Pin7,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},

    {PortC,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin1,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin4,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin5,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin6,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortC,Pin7,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},

    {PortD,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin1,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin4,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin5,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin6,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortD,Pin7,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},

    {PortE,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortE,Pin1,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortE,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortE,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortE,Pin4,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortE,Pin5,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},

    {PortF,Pin0,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortF,Pin1,0,PORT_PIN_OUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortF,Pin2,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortF,Pin3,DEFAULT_PIN_MODE_GPIO,DEFAULT_PIN_DIRECTION_INPUT,STD_LOW,OFF,Mode_Changeable_OFF,PinDirectionChangeable_OFF},
    {PortF,Pin4,0,PORT_PIN_IN,STD_LOW,PULL_UP,Mode_Changeable_OFF,PinDirectionChangeable_OFF}
};



