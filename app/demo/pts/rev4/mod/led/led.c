/*******************************************************************************
*
* FILE: 
* 		led.c
*
* DESCRIPTION: 
* 		Contains API functions to set the behavior of the on-board rgb led
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                                     
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                                     
------------------------------------------------------------------------------*/
#include "main.h"
#include "led.h"


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		led_error_assert                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Sets the RGB LED to red to indicate a software exception               *
*                                                                              *
*******************************************************************************/
void led_error_assert
	(
	void
	)
{
/* Reset RGB LED */
led_reset();

/* Set the RGB LED to red */
HAL_GPIO_WritePin(STATUS_GPIO_PORT, STATUS_R_PIN, GPIO_PIN_RESET);

} /* led_error_assert */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		led_debug_assert                                                       *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Sets the RGB LED to blue to be triggered during debugging              *
*                                                                              *
*******************************************************************************/
void led_debug_assert
	(
	void
	)
{
/* Reset RGB LED */
led_reset();

/* Set the RGB LED to red */
HAL_GPIO_WritePin(STATUS_GPIO_PORT, STATUS_B_PIN, GPIO_PIN_RESET);

} /* led_debug_assert */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		led_reset                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Resets the RGB led                                                     *
*                                                                              *
*******************************************************************************/
void led_reset
	(
	void
	)
{

/* Set all MCU RGB led pins to high */
HAL_GPIO_WritePin(
                 STATUS_GPIO_PORT, 
                 STATUS_R_PIN |
                 STATUS_G_PIN |
                 STATUS_B_PIN,
                 GPIO_PIN_SET
                 );

} /* led_reset */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		led_error_flash                                                        *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Flashes the RGB led red to indicate the code hit a block of code not   *
*       intended to be hit under normal conditions                             *
*                                                                              *
*******************************************************************************/
void led_error_flash
	(
	void
	)
{

/* Flash led red */
led_reset();
HAL_GPIO_WritePin(STATUS_GPIO_PORT, STATUS_R_PIN, GPIO_PIN_RESET); 
HAL_Delay(100);
HAL_GPIO_WritePin(STATUS_GPIO_PORT, STATUS_R_PIN, GPIO_PIN_SET); 

} /* led_error_flash */

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
* 		led_flash                                                              *
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		Flashes the RGB led                                                    *
*                                                                              *
*******************************************************************************/
void led_flash
	(
	void
	)
{

/* Flash led */
led_reset();
HAL_GPIO_WritePin(STATUS_GPIO_PORT, 
                  STATUS_R_PIN | STATUS_G_PIN | STATUS_B_PIN, 
                  GPIO_PIN_RESET); 
HAL_Delay(100);
HAL_GPIO_WritePin(STATUS_GPIO_PORT, 
                  STATUS_R_PIN | STATUS_G_PIN | STATUS_B_PIN, 
                  GPIO_PIN_SET); 

} /* led_flash */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
