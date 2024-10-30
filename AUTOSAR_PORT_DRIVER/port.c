/******************************************************************************
 *
 * Module: port
 *
 * File Name: port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Zyad Montaser
 ******************************************************************************/

#include "port.h"
#include "tm4c123gh6pm_registers.h"
#include "Common_Macros.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"

/* AUTOSAR Version checking between Det and PORT Module */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

/*global pointer to point to the configuration structure which contain Arr[43]*/
STATIC const pin_configuration* Arr = NULL_PTR;
STATIC volatile uint8 PORT_Status = PORT_NOT_INITIALIZED;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Port_Init( const Port_ConfigType* ConfigPtr )
{
    Arr=ConfigPtr->pins;
    volatile uint32 * Ptr2Port = NULL_PTR;
    boolean error = FALSE;
    uint8 i;

    /*check if the Development error detections is on or off*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)

    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID ,PORT_E_PARAM_CONFIG);
        error =TRUE;
    }
    else
#endif
{
        /* In-case there are no errors */
        if(FALSE == error)
        {
            for(i=0;i<NUMBER_OF_IO_PINS;i++)
            {
#if (PORT_DEV_ERROR_DETECT == STD_ON)
                if(Arr[i].pin_num >=8)
                {
                    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID ,PORT_E_PARAM_PIN);
                }
                else if(Arr[i].mode >=15)
                {
                    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID ,PORT_E_PARAM_INVALID_MODE);
                }
#endif

                uint8 port=Arr[i].port_num;
                switch(port)
                {
                case 0:    Ptr2Port = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                break;
                case 1:    Ptr2Port = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                break;
                case 2:    Ptr2Port = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                break;
                case 3:    Ptr2Port = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                break;
                case 4:    Ptr2Port = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                break;
                case 5:    Ptr2Port = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                break;
                }

                /* PD7 and PF0 both need to unlock the GPIOCR and set the commit register*/
                if( ((Arr[i].port_num == 3) && (Arr[i].pin_num == 7)) || ((Arr[i].port_num == 5) && (Arr[i].pin_num == 0)) )
                {
                    /* Unlock the GPIOCR register */
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;

                    /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_COMMIT_REG_OFFSET) , Arr[i].pin_num);
                }


                if(Arr[i].mode ==ADC_Mode)
                {
                    /* Enable Analog */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Arr[i].pin_num);

                    /* Disable Digital*/
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ANALOG_MODE_SEL_REG_OFFSET),Arr[i].pin_num);
                }
                else/*Any other mode except ADC*/
                {
                    /* Disable Analog */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Arr[i].pin_num);

                    /*Enable Digital*/
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ANALOG_MODE_SEL_REG_OFFSET),Arr[i].pin_num);
                }


                /*JTAG pins PC0,PC1,PC2,PC3*/
                if (Arr[i].port_num == 2 && Arr[i].pin_num <= 3)
                {
                    continue;/*do nothing*/
                }

                /* all the other pins*/
                else if(Arr[i].mode ==GPIO_Mode)
                {
                    /* logic AND with this mask clear the correspoding 4bits
                     *  (pin_num=1 ->clear 1st 4bits)(pin_num=2 ->clear 2nd 4bits)..*/
                    uint32 Clear_4bits_mask= ~(0xF << (Arr[i].pin_num * 4));

                    /*clear the corresponding 4-bits before inserting the mode number*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_CTL_REG_OFFSET) &= Clear_4bits_mask;
                    /* insert the mode number in GPIOPCTL*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_CTL_REG_OFFSET) |= (Arr[i].mode <<(4*Arr[i].pin_num));

                    /*clear the required bit before inserting the direction*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET) &= (1<<Arr[i].pin_num);
                    /*insert the direction in required bit*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET)|= (1<<Arr[i].direction);

                    if(Arr[i].mode ==0)/* Disable alternative function in case of GPIO*/
                    {
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ALT_FUNC_REG_OFFSET),Arr[i].pin_num);
                    }
                    else/*enable alternative function for any mode except GPIO*/
                    {
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_ALT_FUNC_REG_OFFSET),Arr[i].pin_num);
                    }

                    switch(Arr[i].internal_Res)
                    {
                    case PULL_UP:
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_PULL_UP_REG_OFFSET),Arr[i].pin_num);
                        break;
                    case PULL_DOWN:
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_PULL_DOWN_REG_OFFSET),Arr[i].pin_num);
                        break;
                    case 0:
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_PULL_UP_REG_OFFSET),Arr[i].pin_num);
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_PULL_DOWN_REG_OFFSET),Arr[i].pin_num);
                        break;
                    }

                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DATA_REG_OFFSET) = Arr[i].pin_initialValue;
                }
                /* end of the For loop*/
            }
        PORT_Status=PORT_INITIALIZED;/*Set the module state to be initialized */
}
    else/*there is an error*/
    {
        /*No action required*/
    }

}
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
    boolean error = FALSE;
    volatile uint32 * Ptr2Port = NULL_PTR;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    if(PORT_Status == PORT_NOT_INITIALIZED)
    {
        /* Check if the Driver is initialized before using this function */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID ,PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*No action required*/
    }

    if(PORT_SET_PIN_DIRECTION_API == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID ,PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*No action required*/
    }

    if(Pin >=NUMBER_OF_IO_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINDIRECTION_SID ,PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
#endif
    {
        /* In-case there are no errors */
        if(FALSE == error)
        {
            switch(Arr[Pin].port_num)
            {
            case 0:    Ptr2Port = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
            case 1:    Ptr2Port = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
            case 2:    Ptr2Port = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
            case 3:    Ptr2Port = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
            case 4:    Ptr2Port = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
            case 5:    Ptr2Port = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
            }

            /*JTAG pins PC0,PC1,PC2,PC3*/
            if (Arr[Pin].port_num == 2 && Arr[Pin].pin_num <= 3)
            {
                return;/*do nothing*/
            }
            else
            {
                /*No action required*/
            }

            /*clear the required bit before inserting the direction*/
            *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET) &= (1<<Arr[Pin].pin_num);
            /*insert the direction in required bit*/
            *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET)|= (1<<Arr[Pin].direction);
        }

        else
        {
            /*No action required*/
        }
    }
}
#endif


void Port_RefreshPortDirection( void )
{
    volatile uint32 * Ptr2Port = NULL_PTR;
    boolean error = FALSE;
    uint8 i;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    if(PORT_Status == PORT_NOT_INITIALIZED)
    {
        /* Check if the Driver is initialized before using this function */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESHPORTDIRECTION_SID ,PORT_E_UNINIT);
        error = TRUE;
    }
    else
#endif
    {
        /* In-case there are no errors */
        if(FALSE == error)
        {
            for(i=0;i<NUMBER_OF_IO_PINS;i++)
            {
                switch(Arr[i].port_num)
                {
                case 0:    Ptr2Port = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                break;
                case 1:    Ptr2Port = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
                break;
                case 2:    Ptr2Port = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
                break;
                case 3:    Ptr2Port = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
                break;
                case 4:    Ptr2Port = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
                break;
                case 5:    Ptr2Port = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
                break;
                }

                /*JTAG pins PC0,PC1,PC2,PC3*/
                if (Arr[i].port_num == 2 && Arr[i].pin_num <= 3)
                {
                    continue;/*do nothing*/
                }
                else
                {
                    /*do nothing*/
                }

                if(Arr[i].Direction_Changeable==STD_OFF)
                {
                    /*clear the required bit before inserting the direction*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET) &= (1<<Arr[i].pin_num);
                    /*insert the direction in required bit*/
                    *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_DIR_REG_OFFSET)|= (1<<Arr[i].direction);
                }
                else
                {
                    /*do nothing*/
                }
                /*end of the for loop*/
            }
        }

        else
        {
            /*No action required*/
        }
    }

}


#if (PORT_VERSION_INFO_API ==STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_GETVERSIONINFO_SID, PORT_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /*do nothing*/
    }
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    if(error == FALSE)
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
    else
    {
        /*do nothing*/
    }
}
#endif


#if (PORT_SET_PIN_MODE_API ==STD_ON)
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
    /* logic AND with this mask clear the correspoding 4bits
     *  (pin_num=1 ->clear 1st 4bits)(pin_num=2 ->clear 2nd 4bits)..*/
    uint32 Clear_4bits_mask= ~(0xF << (Pin * 4));

    boolean error = FALSE;
    volatile uint32 * Ptr2Port = NULL_PTR;


#if (PORT_DEV_ERROR_DETECT == STD_ON)

    if(PORT_Status == PORT_NOT_INITIALIZED)
    {
        /* Check if the Driver is initialized before using this function */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINMODE_SID ,PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*No action required*/
    }

    if(PORT_SET_PIN_MODE_API == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINMODE_SID ,PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*No action required*/
    }

    if(Pin >=NUMBER_OF_IO_PINS)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINMODE_SID ,PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /*No action required*/
    }

    if(Mode >=15)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SETPINMODE_SID ,PORT_E_PARAM_INVALID_MODE);
        error = TRUE;
    }

    else
#endif
    {
        /* In-case there are no errors */
        if(FALSE == error)
        {
            switch(Arr[Pin].port_num)
            {
            case 0:    Ptr2Port = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
            break;
            case 1:    Ptr2Port = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
            break;
            case 2:    Ptr2Port = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
            break;
            case 3:    Ptr2Port = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
            break;
            case 4:    Ptr2Port = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
            break;
            case 5:    Ptr2Port = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
            break;
            }

            /*JTAG pins PC0,PC1,PC2,PC3*/
            if (Arr[Pin].port_num == 2 && Arr[Pin].pin_num <= 3)
            {
                return;/*do nothing*/
            }
            else
            {
                /*No action required*/
            }

            /*clear the corresponding 4-bits before inserting the mode number*/
            *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_CTL_REG_OFFSET) &= Clear_4bits_mask;
            /* insert the mode number in GPIOPCTL*/
            *(volatile uint32 *)((volatile uint8 *)Ptr2Port + PORT_CTL_REG_OFFSET) |= (Mode <<(4*Pin));
        }

        else
        {
            /*No action required*/
        }
    }
}
#endif

