/*******************************************************************************
*
* FILE: 
*       main.c
*
* DESCRIPTION: 
*		Pings another XBee module and indicates to PC when a ping code has 
*       received. Used to perform range testing and bidirectional communcation
*       testing.	
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/

/* Pin definitions, main prototypes, error codes */
#include "main.h"
#include "init.h"
#include "sdr_pin_defines_L0002.h"
#include "sdr_error.h"

/* SDR Modules */
#include "commands.h"
#include "led.h"
#include "rs485.h"
#include "usb.h"
#include "wireless.h"


/*------------------------------------------------------------------------------
Global Variables                                                                  
------------------------------------------------------------------------------*/

/* MCU Peripheral handles */
ADC_HandleTypeDef  hadc1;  /* Pressure transducer ADC handle   */
ADC_HandleTypeDef  hadc2;  /* Load cell ADC handle             */
ADC_HandleTypeDef  hadc3;  /* Pressure transducer 5 ADC handle */
I2C_HandleTypeDef  hi2c1;  /* Thermocouple I2C handle          */
SPI_HandleTypeDef  hspi2;  /* Flash SPI handle                 */
UART_HandleTypeDef huart1; /* USB UART handler struct          */
UART_HandleTypeDef huart2; /* Valve controller UART handle     */
UART_HandleTypeDef huart4; /* Wireless interface UART handle   */


/*------------------------------------------------------------------------------
Application entry point                                                      
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
 Local Variables 
------------------------------------------------------------------------------*/
uint8_t    rx_byte;            /* Byte recieved from Wireless module  */
#ifdef USE_RS485
	RS485_STATUS rs485_status; /* RS485 return codes                  */
#else
	RF_STATUS    rf_status;    /* Status of wireless module           */
#endif
USB_STATUS usb_status;         /* Status of USB module                */
uint32_t   time;               /* Time for initial ping timeout       */
uint32_t   start_time;         /* Starting time for timeout counter   */
uint32_t   timeout_cnt;        /* Number of times ping has timeed out */


/*------------------------------------------------------------------------------
 Initializations                                                             
------------------------------------------------------------------------------*/
rx_byte     = 0;
timeout_cnt = 0;


/*------------------------------------------------------------------------------
 MCU Initialization                                                             
------------------------------------------------------------------------------*/
HAL_Init                (); /* Reset peripherals, initialize flash interface 
                               and Systick.                                   */
SystemClock_Config      (); /* System clock                                   */
PeriphCommonClock_Config(); /* Shared peripheral clocks                       */
GPIO_Init               (); /* GPIO                                           */
USB_UART_Init           (); /* USB UART                                       */
Valve_UART_Init         (); /* Valve control UART                             */
Wireless_UART_Init      (); /* Wireless interface UART                        */
FLASH_SPI_Init          (); /* Flash SPI Bus                                  */
PRESSURE_ADC_Init       (); /* Pressure transducers ADC                       */
PRESSURE5_ADC_Init      (); /* Pressure transducers ADC                       */
LOADCELL_ADC_Init       (); /* Load Cell ADC                                  */
Thermocouple_I2C_Init   (); /* Thermocouple I2C                               */


/*------------------------------------------------------------------------------
 Initial Setup 
------------------------------------------------------------------------------*/
start_time = HAL_GetTick();
time       = HAL_GetTick() - start_time;

/* Successfuly initialization LED indication */
led_set_color( LED_GREEN );


/*------------------------------------------------------------------------------
 Event Loop                                                                  
------------------------------------------------------------------------------*/
#ifdef USE_RS485
	while (1)
		{
		/* Update timeout counter */
		time = HAL_GetTick() - start_time; 

		/* Poll the wireless module for incoming data */
		rs485_status = rs485_receive_byte( &rx_byte ); 

		/* Received byte */
		if ( ( rs485_status != RS485_TIMEOUT ) && ( rx_byte != 0 ) )
			{
			led_set_color( LED_GREEN );
			HAL_Delay( 100 );

			/* Correct byte? */
			if ( rx_byte != PING_CODE )
				{
				Error_Handler( ERROR_RF_UNRECOGNIZED_PING );
				}

			/* Send a ping to the other wireless module */
			rs485_transmit_byte( PING_CODE );

			} /* if ( rs485_status != RS485_TIMEOUT ) */
		else
			{
			led_set_color( LED_YELLOW );
			}

		/* Error out if timeout count is too large */
		/*
		if ( timeout_cnt > 10 )
			{
			while ( 1 )
				{
				led_set_color( LED_BLUE );
				}
			}
		*/

		}
#else
	while (1)
		{
		/* Update timeout counter */
		time = HAL_GetTick() - start_time; 

		/* Poll the wireless module for incoming data */
		rf_status = rf_xbee_receive_byte( &rx_byte ); 

		/* Received byte */
		if ( rf_status != RF_TIMEOUT )
			{
			led_set_color( LED_GREEN );
			/* Correct byte? */
			/*
			if ( rx_byte != PING_CODE )
				{
				Error_Handler( ERROR_RF_UNRECOGNIZED_PING );
				}
			*/

			/* Send a ping to the other wireless module */
			rf_xbee_transmit_byte( PING_CODE );

			/* Tell PC a ping has been received */
			/*
			usb_status = usb_transmit( &rx_byte         , 
									sizeof( uint8_t ),
									2 );
			if ( usb_status != USB_OK )
				{
				Error_Handler( ERROR_USB_UART_ERROR );
				}
			*/
			} /* if ( rf_status != RF_TIMEOUT ) */
		else
			{
			led_set_color( LED_YELLOW );
			}

		/* Send out a ping if a ping hasn't been receieved recently */
		if ( time >= PING_TIMEOUT )
			{
			rf_status = rf_xbee_transmit_byte( PING_CODE );
			if ( rf_status != RF_OK )
				{
				Error_Handler( ERROR_RF_ERROR );
				}
			start_time = HAL_GetTick();
			timeout_cnt++;
			}

		/* Error out if timeout count is too large */
		/*
		if ( timeout_cnt > 10 )
			{
			while ( 1 )
				{
				led_set_color( LED_BLUE );
				}
			}
		*/

		}
#endif
} /* main */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/