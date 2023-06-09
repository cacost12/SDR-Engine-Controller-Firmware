/*******************************************************************************
*
* FILE: 
* 		abort_hotfire.c
*
* DESCRIPTION: 
* 	    Aborts the hotfire in case of emergency 
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                              
------------------------------------------------------------------------------*/
#include "main.h"
#include "valve_control.h"
#include "led.h"


/*------------------------------------------------------------------------------
 Public Functions 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		run_abort_state                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Abort the engine hotfire                                               *
*                                                                              *
*******************************************************************************/
void run_abort_state 
    (
    void
    )
{
/* Purge */
vc_close_main_valves( MAIN_VALVE_BOTH_MAINS );
vc_close_solenoids( SOLENOID_LOX_PRESS | SOLENOID_FUEL_PRESS );
vc_open_solenoids( SOLENOID_LOX_VENT | SOLENOID_FUEL_VENT );
vc_open_solenoids( SOLENOID_LOX_PURGE | SOLENOID_FUEL_PURGE );
HAL_Delay( POSTFIRE_PURGE_DURATION );

/* Safe State */
vc_close_solenoids( SOLENOID_LOX_PURGE | SOLENOID_FUEL_PURGE );
led_set_color( LED_RED );
while ( 1 ) 
    {
     /* Idle */
    };
} /* run_abort_state */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/