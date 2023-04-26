/*******************************************************************************
*
* FILE: 
* 		manual.c
*
* DESCRIPTION: 
* 	    Provides manual control over engine valves for troubleshooting 
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
 Public Functions 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		run_manual_state                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Manual valve control                                                   *
*                                                                              *
*******************************************************************************/
FSM_STATE run_manual_state 
    (
    void
    )
{
while ( 1 )
    {
    led_set_color( LED_CYAN );
    }
return FSM_READY_STATE;
} /* run_manual_state */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/