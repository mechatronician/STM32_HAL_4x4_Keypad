/*
 * keypad_gpio.h
 *
 *  Created on: Sep 9, 2020
 *      Author: Huseyink
 */

#ifndef INC_KEYPAD_GPIO_H_
#define INC_KEYPAD_GPIO_H_


// Keypad columns GPIO Ports.
GPIO_TypeDef* ColumnPort[] =
{
	GPIOB,
	GPIOB,
	GPIOB,
	GPIOB,
};

// Keypad columns GPIO Pins.
uint16_t ColumnPin[] =
{
	GPIO_PIN_15,
	GPIO_PIN_14,
	GPIO_PIN_13,
	GPIO_PIN_12
};

// Keypad rows GPIO Ports.
GPIO_TypeDef* RowPort[] =
{
	GPIOA,
	GPIOA,
	GPIOA,
	GPIOA,
};

// Keypad rows GPIO Pins
uint16_t RowPin[] =
{
	GPIO_PIN_11,
	GPIO_PIN_10,
	GPIO_PIN_9,
	GPIO_PIN_8
};

#endif /* INC_KEYPAD_GPIO_H_ */
