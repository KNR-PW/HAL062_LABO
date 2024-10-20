/**
 ******************************************************************************
 * @file           : can.c
 * @author         : A. Rybojad
 * @brief          : Communication threw CAN
 ******************************************************************************
 */

#include "can/can.h"
#include <stdint.h>
#include "motor/motor.h"

static uint32_t CAN_TxMailbox;
static uint8_t CAN_RxMsg[8];

static CAN_RxHeaderTypeDef CAN_RxHeader;
static CAN_TxHeaderTypeDef CAN_TxHeader;

CAN_HandleTypeDef hcan1;

void CAN_Init(void) {
	CAN_FilterTypeDef sFilterConfig;

	hcan1.Instance = CAN1;
	hcan1.Init.Prescaler = 40u;
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
	hcan1.Init.TimeSeg2 = CAN_BS2_8TQ;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.AutoRetransmission = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan1) != HAL_OK) {
		volatile uint32_t b = 0;
		b++;
	}
	sFilterConfig.FilterBank = 0u;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	sFilterConfig.FilterIdHigh = (0x14 << 5);  // Pierwszy filtr na ID 0x14 (przesunięcie o 5 bitów)
	sFilterConfig.FilterIdLow = (0x16 << 5);   // Drugi filtr na ID 0x15 (przesunięcie o 5 bitów)
	sFilterConfig.FilterMaskIdHigh = (0xFE << 5); // Maska dla obu filtrów (ignoruje ostatni bit)
	sFilterConfig.FilterMaskIdLow = (0xFE << 5);
	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 0;
	if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK) {
		volatile uint32_t b = 0;
		b++;
	}

	if (HAL_CAN_Start(&hcan1) != HAL_OK) {
		volatile uint32_t b = 0;
		b++;
	}

	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)
			!= HAL_OK) {
		volatile uint32_t b = 0;
		b++;
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {

	HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CAN_RxHeader, CAN_RxMsg);

	int8_t refValue = 0;
	if (CAN_RxHeader.StdId == 200) // startup lab module
		 ; // TODO
	else if(CAN_RxHeader.StdId == 210){ // move main frame up

	}


}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {

}

void Can_sendMessage(uint8_t *msg, uint8_t ID) {
	CAN_TxHeader.StdId = ID;
	CAN_TxHeader.ExtId = 0;
	CAN_TxHeader.IDE = CAN_ID_STD;
	CAN_TxHeader.RTR = CAN_RTR_DATA;
	CAN_TxHeader.DLC = 8;
	uint8_t dane[8];
	for (uint8_t i = 0; i < 8; i++) {
		dane[i] = msg[i];

	HAL_CAN_AddTxMessage(&hcan1, &CAN_TxHeader, dane, &CAN_TxMailbox);

}
}

void Can_testMessage(void) {
	CAN_TxHeader.StdId = 20;
	CAN_TxHeader.ExtId = 20;
	CAN_TxHeader.IDE = CAN_ID_STD;
	CAN_TxHeader.RTR = CAN_RTR_DATA;
	CAN_TxHeader.DLC = 8;
	uint8_t dane[8];
	dane[0] = 0xAAu;
	dane[1] = 0xAAu;
	for (int i = 2; i < 8; i++) {
		dane[i] = 0;
	}
	HAL_CAN_AddTxMessage(&hcan1, &CAN_TxHeader, dane, &CAN_TxMailbox);
}

void CAN1_TX_IRQHandler(void) {
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_RX0_IRQHandler(void) {
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_RX1_IRQHandler(void) {
	HAL_CAN_IRQHandler(&hcan1);
}
