/**
 *****************************************************

 *****************************************************
 */

#ifndef MODULES_MOTOR_MOTOR_H
#define MODULES_MOTOR_MOTOR_H

/* MACROS ------------------------------------------------------------------*/

void MainBoxMotor_Init(void);

void liftMainBox(uint8_t ifFast);
void lowerMainBox(uint8_t ifFast);

void stopMainBox();

#endif // MODUMODULES_MOTOR_MOTOR_H
