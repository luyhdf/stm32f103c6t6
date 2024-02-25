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
    const char* name;
    bool isFuncKey; // 是否为功能键
    const char* letter;
} KeyMap;

extern const KeyMap keyNULL; // 无按键编码

// 输入法模式
typedef enum {
    Numeric,  // 数字模式
    Alphabetic // 字母模式
} KeyMode;

// 缓存键盘输入最大输入长度
#define MaxKeyValueNumberic 5 //数字最大长度为4位
#define MaxKeyValueAlphabetic 20 // 字母最大长度为19

// 定义功能键编码
typedef enum {
	FKEY_NULL = 0,  // 非功能键
	FKEY_DELETE = 8,
	FKEY_ENTER = 16,
	FKEY_UP = 4,
	FKEY_DOWN = 12,
	FKEY_LEFT = 13,
	FKEY_RIGHT = 15
} FKeyMode;

#define NextAlphabeticTimeout 500 // 字母切换下一位超时时间ms

typedef struct {
	KeyMode keyMode;
    const KeyMap* lastKey; // 最新按键
    FKeyMode fKeyMode; // 触发功能键
    char keyValue[MaxKeyValueAlphabetic];
} KeyMethod;

KeyMap* keyboard_scan();

void keyboard_process(KeyMethod *keyMethod);

#endif /* INC_KEYBOARD_H_ */
