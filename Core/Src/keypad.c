/*
 * keypad.c
 *
 *  Created on: Sep 9, 2020
 *      Author: Huseyin Koc
 */

#include "keypad.h"

extern KeypadTypeDef keypad;
volatile uint32_t msTick;

KeypadGPIO_TypeDef keypad_gpio;

void EXTI15_10_IRQHandler(void)
{
	/* USER CODE BEGIN EXTI15_10_IRQn 0 */

	if(!keypad.isPressed)
	{
		keypad.isPressed = 1;

		if (__HAL_GPIO_EXTI_GET_IT(keypad_gpio.KeypadColumn1_Pin) != 0x00U)
		{
		  getPressedKey(keypad.pressedRow, COL1);
		  HAL_GPIO_EXTI_IRQHandler(keypad_gpio.KeypadColumn1_Pin);
		}

		if (__HAL_GPIO_EXTI_GET_IT(keypad_gpio.KeypadColumn2_Pin) != 0x00U)
		{
		  getPressedKey(keypad.pressedRow, COL2);
		  HAL_GPIO_EXTI_IRQHandler(keypad_gpio.KeypadColumn2_Pin);
		}

		if (__HAL_GPIO_EXTI_GET_IT(keypad_gpio.KeypadColumn3_Pin) != 0x00U)
		{
		  getPressedKey(keypad.pressedRow, COL3);
		  HAL_GPIO_EXTI_IRQHandler(keypad_gpio.KeypadColumn3_Pin);
		}

		if (__HAL_GPIO_EXTI_GET_IT(keypad_gpio.KeypadColumn4_Pin) != 0x00U)
		{
		  getPressedKey(keypad.pressedRow, COL4);
		  HAL_GPIO_EXTI_IRQHandler(keypad_gpio.KeypadColumn4_Pin);
		}
	}

  /* USER CODE END EXTI15_10_IRQn 0 */

  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}


void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

	msTick++;

	if(!(msTick % 20))
	{
		scanRows();
	}

  /* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

// Initialize Keypad columns/rows GPIO Ports and GPIO pins.
void keypad_init(GPIO_TypeDef** gpio_col, uint16_t* col_pin, GPIO_TypeDef** gpio_row, uint16_t* row_pin )
{
	keypad_gpio.KeypadColumn1_Port = gpio_col[0];
	keypad_gpio.KeypadColumn2_Port = gpio_col[1];
	keypad_gpio.KeypadColumn3_Port = gpio_col[2];
	keypad_gpio.KeypadColumn4_Port = gpio_col[3];

	keypad_gpio.KeypadColumn1_Pin = col_pin[0];
	keypad_gpio.KeypadColumn2_Pin = col_pin[1];
	keypad_gpio.KeypadColumn3_Pin = col_pin[2];
	keypad_gpio.KeypadColumn4_Pin = col_pin[3];

	keypad_gpio.KeypadRow1_Port = gpio_row[0];
	keypad_gpio.KeypadRow2_Port = gpio_row[1];
	keypad_gpio.KeypadRow3_Port = gpio_row[2];
	keypad_gpio.KeypadRow4_Port = gpio_row[3];

	keypad_gpio.KeypadRow1_Pin = row_pin[0];
	keypad_gpio.KeypadRow2_Pin = row_pin[1];
	keypad_gpio.KeypadRow3_Pin = row_pin[2];
	keypad_gpio.KeypadRow4_Pin = row_pin[3];

}

// All rows set HIGH sequentially so that we can determine which key is pressed.
void scanRows()
{
	static uint8_t rowsNum = 0;

	// If any key is pressed, scanning of rows will stop.
	uint8_t status = HAL_GPIO_ReadPin(keypad_gpio.KeypadColumn1_Port, keypad_gpio.KeypadColumn1_Pin) ||
					 HAL_GPIO_ReadPin(keypad_gpio.KeypadColumn2_Port, keypad_gpio.KeypadColumn2_Pin) ||
					 HAL_GPIO_ReadPin(keypad_gpio.KeypadColumn3_Port, keypad_gpio.KeypadColumn3_Pin) ||
					 HAL_GPIO_ReadPin(keypad_gpio.KeypadColumn4_Port, keypad_gpio.KeypadColumn4_Pin);

	if(!status)
	{
		keypad.isPressed = 0;

		switch (rowsNum) {

			case 0:
				keypad.pressedRow = ROW1;
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow1_Port, keypad_gpio.KeypadRow1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow2_Port, keypad_gpio.KeypadRow2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow3_Port, keypad_gpio.KeypadRow3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow4_Port, keypad_gpio.KeypadRow4_Pin, GPIO_PIN_RESET);
				rowsNum++;
				break;

			case 1:
				keypad.pressedRow = ROW2;
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow1_Port, keypad_gpio.KeypadRow1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow2_Port, keypad_gpio.KeypadRow2_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow3_Port, keypad_gpio.KeypadRow3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow4_Port, keypad_gpio.KeypadRow4_Pin, GPIO_PIN_RESET);
				rowsNum++;
				break;

			case 2:
				keypad.pressedRow = ROW3;
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow1_Port, keypad_gpio.KeypadRow1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow2_Port, keypad_gpio.KeypadRow2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow3_Port, keypad_gpio.KeypadRow3_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow4_Port, keypad_gpio.KeypadRow4_Pin, GPIO_PIN_RESET);
				rowsNum++;
				break;

			case 3:
				keypad.pressedRow = ROW4;
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow1_Port, keypad_gpio.KeypadRow1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow2_Port, keypad_gpio.KeypadRow2_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow3_Port, keypad_gpio.KeypadRow3_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(keypad_gpio.KeypadRow4_Port, keypad_gpio.KeypadRow4_Pin, GPIO_PIN_SET);
				rowsNum++;
				break;

		}

		rowsNum = rowsNum % KEYPAD_ROW_SIZE;
	}

}

// After the row and column are determined, we can find which key was pressed.
void getPressedKey(uint8_t row, uint8_t col)
{
	if(col == COL1)
	{
		switch (row) {

			case ROW1:
			{
				keypad.keyPressed = '1';
				break;
			}

			case ROW2:
			{
				keypad.keyPressed = '4';
				break;
			}

			case ROW3:
			{
				keypad.keyPressed = '7';
				break;
			}

			case ROW4:
			{
				keypad.keyPressed = '*';
				break;
			}

		}
	} /* if(col == COL1) */

	else if(col == COL2)
	{
		switch (row) {

			case ROW1:
			{
				keypad.keyPressed = '2';
				break;
			}

			case ROW2:
			{
				keypad.keyPressed = '5';
				break;
			}

			case ROW3:
			{
				keypad.keyPressed = '8';
				break;
			}

			case ROW4:
			{
				keypad.keyPressed = '0';
				break;
			}

		}
	} /* else if(col == COL2) */

	else if(col == COL3)
	{
		switch (row) {

			case ROW1:
			{
				keypad.keyPressed = '3';
				break;
			}

			case ROW2:
			{
				keypad.keyPressed = '6';
				break;
			}

			case ROW3:
			{
				keypad.keyPressed = '9';
				break;
			}

			case ROW4:
			{
				keypad.keyPressed = '#';
				break;
			}

		}

	} /* else if(col == COL3) */

	else if(col == COL4)
	{
		switch (row) {

			case ROW1:
			{
				keypad.keyPressed = 'A';
				break;
			}

			case ROW2:
			{
				keypad.keyPressed = 'B';
				break;
			}

			case ROW3:
			{
				keypad.keyPressed = 'C';
				break;
			}

			case ROW4:
			{
				keypad.keyPressed = 'D';
				break;
			}

		}
	} /* else if(col == COL4) */

}


