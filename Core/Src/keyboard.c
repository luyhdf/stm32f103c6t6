/*
 * keyboard.c
 *
 *  Created on: Feb 23, 2024
 *      Author: luyh
 */

#include "keyboard.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include <string.h>

// 按键行列IO映射
uint16_t Col_Pin_In[4] = {KEY_C1_Pin, KEY_C2_Pin, KEY_C3_Pin, KEY_C4_Pin};	// 行选择输入
uint16_t Row_Pin_Out[4] = {KEY_R1_Pin, KEY_R2_Pin, KEY_R3_Pin, KEY_R4_Pin}; // 列选择输出

// 按键功能映射
const KeyMap keymap[4][4] = {
	{{1, "1", false, ""},
	 {2, "2", false, "abc"},
	 {3, "3", false, "def"},
	 {4, "up", true, ""}},
	{{5, "4", false, "ghi"},
	 {6, "5", false, "jkl"},
	 {7, "6", false, "mno"},
	 {8, "delete", true, ""}},
	{{9, "7", false, "pqrs"},
	 {10, "8", false, "tuv"},
	 {11, "9", false, "wxyz"},
	 {12, "down", true, ""}},
	{{13, "left", true, ""},
	 {14, "0", false, ""},
	 {15, "right", true, ""},
	 {16, "enter", true, ""}}};

// 无按键
const KeyMap keyNULL = {0, "keyNULL",false, ""};

KeyMap* keyboard_scan()
{
	// 遍历行
	for (int row = 0; row < 4; row++)
	{
		// 将当前行拉低
		HAL_GPIO_WritePin(MatrixKeyPort, Row_Pin_Out[row], GPIO_PIN_RESET);
		HAL_Delay(5);
		// 检测列
		for (int col = 0; col < 4; col++)
		{
			if (HAL_GPIO_ReadPin(MatrixKeyPort, Col_Pin_In[col]) == GPIO_PIN_RESET)
			{
				// 延时一段时间进行按键消抖
				HAL_Delay(5);

				// 再次检测按键状态
				if (HAL_GPIO_ReadPin(MatrixKeyPort, Col_Pin_In[col]) == GPIO_PIN_RESET)
				{
					// 返回对应的按键值
					return &keymap[row][col];
				}
			}
		}
		// 将当前行恢复高电平
		HAL_GPIO_WritePin(MatrixKeyPort, Row_Pin_Out[row], GPIO_PIN_SET);
	}
	// 没有按键按下
	return &keyNULL;
}

void numeric_process(KeyMethod *keyMethod){
	size_t len = strlen(keyMethod->keyValue);
	char keyName = keyMethod->lastKey->name;
	if(len < MaxKeyValueNumberic-1){
		// 将key值新增至value
		keyMethod->keyValue[len] = keyName;
		keyMethod->keyValue[len + 1] = '\0';
	}
	else{
		// 替换最后一位字符
		keyMethod->keyValue[len-1] = keyName;
		keyMethod->keyValue[len] = '\0';
	}
}

void alphabetic_process(KeyMethod *keyMethod){
	// todo: 未实现
	static KeyMap* lastKeyTemp = NULL;  // 缓存上次按键
	KeyMap* lastKey = keyMethod->lastKey; // 获取当前按键
	char* letter = lastKey->letter; // 当前按键字母串
	static uint8_t alphabetic_index = 0; // 字母索引

	static uint32_t previousTime = 0; // 静态变量用于保存时间戳
	uint32_t elapsedTime = 0; // 用于保存时间间隔

	uint32_t currentTime = HAL_GetTick(); // 获取当前时间戳

    if (previousTime != 0) {
        elapsedTime = currentTime - previousTime; // 计算时间间隔，单位为毫秒
        printf("Time elapsed: %lu milliseconds\n", elapsedTime);
    }

	size_t len = strlen(keyMethod->keyValue);
	if(elapsedTime!=0 && elapsedTime<NextAlphabeticTimeout && lastKeyTemp == lastKey){
		//非第1次按键,按键间隔< 500ms,相同键值
		alphabetic_index++;  // 更新字母索引
	}
	else{
		alphabetic_index = 0;
	}
 	previousTime = currentTime; // 更新上一次时间戳
	lastKeyTemp = lastKey;  // 更新上一次按键

	if(len < MaxKeyValueAlphabetic-1 && alphabetic_index == 0){
		// 将key值新增至value
		keyMethod->keyValue[len] = *letter;
		keyMethod->keyValue[len + 1] = '\0';
	}
	else{
		// 替换最后一位字符
		keyMethod->keyValue[len-1] = *(letter + alphabetic_index%strlen(letter));
		keyMethod->keyValue[len] = '\0';
	}
}

void delete_process(KeyMethod *keyMethod){
    size_t len = strlen(keyMethod->keyValue);
	if(len > 0){
		keyMethod->keyValue[len-1] = '\0';
	}
}

void keyboard_process(KeyMethod *keyMethod)
{
	KeyMap* lastKey = keyMethod->lastKey;
	if (lastKey->isFuncKey) { 
		// 功能键
		switch (lastKey->id)
		{
		case FKEY_DELETE:
			delete_process(keyMethod);
			break;
		default:
			keyMethod->fKeyMode = lastKey->id;
			break;
		}
		
	}
	else{
		// 普通按键
		switch (keyMethod->keyMode)
			{
			// 数字模式
			case Numeric:
				numeric_process(keyMethod);
				break;
			// 字母模式
			case Alphabetic:
				alphabetic_process(keyMethod);
				break;
			default:
				break;
			}
	}
}
