/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>
#include <drivers/uart.h>
#include <drivers/timer.h>
#include <drivers/led.h>
#include <users/user_cloud.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define UART_ID		0
#define HEADER_LEN	4
#define DATA_OK		0x81
// #define DATA_OK		'1'
#define DATA_FAIL	0xC1
#define KEEPALIVE_OK	0x82
// #define KEEPALIVE_OK	'2'
#define RX_LENGTH	5

#define KEEPALIVE_MS	1000
#define DATA_MS			15000
#define TIMER_COUNT_RST	DATA_MS/KEEPALIVE_MS + 1

#define PISO1_IDX		6
#define PISO2_IDX		8
#define PISO3_IDX		10

enum {IS_OK, IS_FAIL, IS_ERR, IS_DATA, IS_KEEPALIVE};

#define GET_MSBYTE(x)	((uint8_t) ((x) >> 8) )
#define GET_LSBYTE(x)	((uint8_t) (x) )

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
void cloudTimer_IRQ();
void SendData();
void KeepAlive();
void checkRX();
uint8_t handle_RX();

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
*******************************************************************************/
static uint8_t keepalive_msg[] = {0xAA, 0x55, 0xC3, 0x3C, 0x01, 0x02};
// static uint8_t keepalive_msg[] = {'A', '5', '3', '5', '1', '2'};
static uint8_t data_msg[] = {0xAA, 0x55, 0xC3, 0x3C, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// static uint8_t data_msg[] = {'A', '5', '3', '5', '7', '1', '0', '0', '0', '0', '0', '0'};
// static uint16_t piso1 = 0;
// static uint16_t piso2 = 0;
// static uint16_t piso3 = 0;

static tim_id_t cloud_timer;
static uint8_t timer_count = 1;

static bool keepalive_flag = false;
static bool data_flag = false;

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init_cloud (void)
{
    // Inicializo UART
	uart_cfg_t config;
	config.baud_rate = 1200;
	uartInit(0, config);

	// Inicializo LED
	LedInit();

	// Cargo usuarios
	loadDataBase();

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run_cloud (void)
{

}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void SendData(){

	uint16_t piso1 = getFloorCount(1);
	uint16_t piso2 = getFloorCount(2);
	uint16_t piso3 = getFloorCount(3);

	data_msg[PISO1_IDX] = GET_LSBYTE(piso1);
	data_msg[PISO1_IDX + 1] = GET_MSBYTE(piso1);
	data_msg[PISO2_IDX] = GET_LSBYTE(piso2);
	data_msg[PISO2_IDX + 1] = GET_MSBYTE(piso2);
	data_msg[PISO3_IDX] = GET_LSBYTE(piso3);
	data_msg[PISO3_IDX + 1] = GET_MSBYTE(piso3);
	uartWriteMsg(UART_ID, (uint8_t*) &data_msg[0], sizeof(data_msg));
}

void KeepAlive(){

	uartWriteMsg(UART_ID, (uint8_t*) &keepalive_msg[0], sizeof(keepalive_msg));
}

void checkRX(){

	uint8_t check = handle_RX();						// Handle reception

	if (check == IS_KEEPALIVE && keepalive_flag){		// Check KeepAliveOK
		keepalive_flag = false;
		LedBlueOn();
	} else if (check == IS_DATA && data_flag){			// Check SendDataOK
		data_flag = false;
		keepalive_flag = false;
		LedGreenOn();
	} else if (check == IS_FAIL && data_flag){			// Check SendDataFail
		LedRedOn();
		SendData();		// Re-send data
	} else if (keepalive_flag) {						// Check KeepAlive
		LedOff();
	} else if (data_flag){
		if (uartGetRxMsgLength(UART_ID) >= RX_LENGTH){
			checkRX();
		} else {
			SendData();
		}
	}
}



uint8_t handle_RX(){
	
	uint8_t r = false;
	uint8_t header_rx[HEADER_LEN];
	//uint8_t length;
	uint8_t answer;

	uartReadMsg(UART_ID, (uint8_t*) &header_rx[0], 4);
	//uartReadMsg(UART_ID, &length, 1);
	uartReadMsg(UART_ID, &answer, 1);

	if (answer == KEEPALIVE_OK){
		r = IS_KEEPALIVE;
	} else if (answer == DATA_OK){
		r = IS_DATA;
	} else if (answer == DATA_FAIL){
		r = IS_FAIL;
	} else {
		r = IS_ERR;
	}

	return r;
}

void cloudTimer_IRQ(){

	if (!(--timer_count)){
		SendData();
		data_flag = true;
		timer_count = TIMER_COUNT_RST;
	} else {
		KeepAlive();
		keepalive_flag = true;
	}

	checkRX();
}


/*******************************************************************************
 ******************************************************************************/
