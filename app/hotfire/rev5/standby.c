/*******************************************************************************
*
* FILE: 
* 		standby.c
*
* DESCRIPTION: 
* 	    Waits for the fire engine signal from ground station 
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                              
------------------------------------------------------------------------------*/
#include "main.h"
#include "flash.h"
#include "data_logger.h"


/*------------------------------------------------------------------------------
 Global Variables 
------------------------------------------------------------------------------*/
extern FSM_STATE fsm_state; /* Hotfire State */


/*------------------------------------------------------------------------------
 Public Functions 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		run_standby_state                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Awaits engine fire signal                                              *
*                                                                              *
*******************************************************************************/
FSM_STATE run_standby_state 
    (
    void
    )
{
/* Erase flash memory */
data_logger_erase_flash();

/* Wait for the fire command */
while ( fsm_state != FSM_FIRE_STATE ){}
return FSM_FIRE_STATE;
} /* run_standby_state */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/