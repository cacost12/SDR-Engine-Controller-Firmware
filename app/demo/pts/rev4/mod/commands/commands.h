/*******************************************************************************
*
* FILE: 
* 		commands.c
*
* DESCRIPTION: 
* 		Contains general command functions common to all embedded controllers
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef COMMANDS_H
#define COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif


/*------------------------------------------------------------------------------
 Macros 
------------------------------------------------------------------------------*/
#define PING_OP 	 0x01 /* ping command opcode    */
#define CONNECT_OP	 0x02 /* connect command opcode */
#define IGNITE_OP	 0x20 /* connect command opcode */
#define POWER_OP     0x21 /* power command opcode   */
#define FLASH_OP     0x22 /* flash command opcode   */
#define SENSOR_OP    0x03 /* Sensor command opcode  */

/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/
void ping
	(
	UART_HandleTypeDef *huart /* UART handler */
	); /* ping command */


#endif /* COMMANDS_H */
