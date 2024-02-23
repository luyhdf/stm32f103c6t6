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

// 按键映射定义
typedef struct {
	const uint8_t id;
    const char* name;
    const char* letter;
} KeyMap;

// 输入法模式
typedef enum {
    Numeric,
    Alphabetic
} KeyMode;

extern KeyMode keymode;

KeyMap keyboard_scan();

#endif /* INC_KEYBOARD_H_ */
