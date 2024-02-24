/*
 * keyboard.h
 *
 *  Created on: Feb 23, 2024
 *      Author: luyh
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include "main.h"
#include <stdbool.h>

#define MatrixKeyPort GPIOB

// 按键映射定义
typedef struct {
	const uint8_t id;
    const char name[20];
    bool isFuncKey; // 是否为功能键
    const char* letter;
} KeyMap;

// 输入法模式
typedef enum {
    Numeric,  // 数字模式
    Alphabetic // 字母模式
} KeyMode;

// 缓存键盘输入最大输入长度
#define MaxKeyValueNumberic 5 //数字最大长度为4位
#define MaxKeyValueAlphabetic 20 // 字母最大长度为19

// 定义功能键编码
#define FKEY_NULL 0 // 无功能
#define FKEY_DELETE 8
#define FKEY_ENTER 16
#define FKEY_UP 4
#define FKEY_DOWN 12
#define FKEY_LEFT 13
#define FKEY_RIGHT 15

typedef struct {
	KeyMode keyMode;
    uint8_t triggerKeyFunc; // 触发功能键
    char keyValue[MaxKeyValueAlphabetic];
} KeyMethod;

KeyMap keyboard_scan();

void keyboard_process(KeyMap key, KeyMethod *keyMethod);

#endif /* INC_KEYBOARD_H_ */
