/*
 * keypad.h
 *
 *  Created on: Sep 9, 2020
 *      Author: Huseyin Koc
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"


#define KEYPAD_COLUMN_SIZE  4
#define KEYPAD_ROW_SIZE	 	4

typedef struct
{
	volatile uint8_t isPressed;
	volatile uint8_t keyPressed;
	volatile uint8_t pressedRow;

}KeypadTypeDef;

typedef struct
{
	GPIO_TypeDef* KeypadColumn1_Port;
	GPIO_TypeDef* KeypadColumn2_Port;
	GPIO_TypeDef* KeypadColumn3_Port;
	GPIO_TypeDef* KeypadColumn4_Port;

	uint16_t KeypadColumn1_Pin;
	uint16_t KeypadColumn2_Pin;
	uint16_t KeypadColumn3_Pin;
	uint16_t KeypadColumn4_Pin;

	GPIO_TypeDef* KeypadRow1_Port;
	GPIO_TypeDef* KeypadRow2_Port;
	GPIO_TypeDef* KeypadRow3_Port;
	GPIO_TypeDef* KeypadRow4_Port;

	uint16_t KeypadRow1_Pin;
	uint16_t KeypadRow2_Pin;
	uint16_t KeypadRow3_Pin;
	uint16_t KeypadRow4_Pin;

}KeypadGPIO_TypeDef;

enum
{
	ROW1 = 1,
	COL1 = 1,
	ROW2 = 2,
	COL2 = 2,
	ROW3 = 3,
	COL3 = 3,
	ROW4 = 4,
	COL4 = 4,
};



void scanRows();
void getPressedKey(uint8_t row, uint8_t col);
void keypad_init(GPIO_TypeDef** gpio_col, uint16_t* col_pin, GPIO_TypeDef** gpio_row, uint16_t* row_pin );

#endif /* INC_KEYPAD_H_ */
