/*
 * keyboard.h
 *
 *  Created on: Feb 23, 2024
 *      Author: luyh
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "main.h"

#define MatrixKeyPort GPIOB


uint8_t keyboard_scan();

#endif /* INC_KEYBOARD_H_ */
