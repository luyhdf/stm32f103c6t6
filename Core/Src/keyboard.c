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
#include <time.h>

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
const KeyMap noKey = {0, "noKey",false, ""};

KeyMap keyboard_scan()
{
	// 遍历行
	for (int row = 0; row < 4; row++)
	{
		// 将当前行拉低
		HAL_GPIO_WritePin(MatrixKeyPort, Row_Pin_Out[row], GPIO_PIN_RESET);

		// 检测列
		for (int col = 0; col < 4; col++)
		{
			if (HAL_GPIO_ReadPin(MatrixKeyPort, Col_Pin_In[col]) == GPIO_PIN_RESET)
			{
				// 延时一段时间进行按键消抖
				HAL_Delay(10);

				// 再次检测按键状态
				if (HAL_GPIO_ReadPin(MatrixKeyPort, Col_Pin_In[col]) == GPIO_PIN_RESET)
				{
					// 返回对应的按键值
					return keymap[row][col];
				}
			}
		}
		// 将当前行恢复高电平
		HAL_GPIO_WritePin(MatrixKeyPort, Row_Pin_Out[row], GPIO_PIN_SET);
	}
	// 没有按键按下
	return noKey;
}

void numeric_process(char keyValue[],char keyName){
	size_t len = strlen(keyValue);
	if(len < MaxKeyValueNumberic-1){
		// 将key值新增至value
		keyValue[len] = keyName;
		keyValue[len + 1] = '\0';
	}
	else{
		// 替换最后一位字符
		keyValue[len-1] = keyName;
		keyValue[len] = '\0';
	}
}

void alphabetic_process(char keyValue[],char letter[]){
	// todo: 未实现
	static time_t previousTime = 0; // 静态变量用于保存时间戳
	static uint8_t alphabetic_index = 0; // 字母索引
	
	time_t currentTime = time(NULL); // 获取当前时间戳

    if (previousTime != 0) {
        double elapsedTime = difftime(currentTime, previousTime); // 计算时间间隔，单位为秒
        printf("Time elapsed: %ld seconds\n", elapsedTime);
    }

    previousTime = currentTime; // 更新上一次时间戳

	size_t len = strlen(keyValue);
	if(len < MaxKeyValueAlphabetic-1){
		// 将key值新增至value
		keyValue[len] = letter[alphabetic_index];
		keyValue[len + 1] = '\0';
	}
	else{
		// 替换最后一位字符
		keyValue[len-1] = letter[alphabetic_index];
		keyValue[len] = '\0';
	}
}

void delete_process(KeyMethod *keyMethod){
    size_t len = strlen(keyMethod->keyValue);
	if(len > 0){
		keyMethod->keyValue[len-1] = '\0';
	}
}

void keyboard_process(KeyMap key, KeyMethod *keyMethod)
{
	if (key.isFuncKey) { 
		// 功能键
		switch (key.id)
		{
		case FKEY_DELETE:
			delete_process(keyMethod);
			break;
		default:
			keyMethod->triggerKeyFunc = key.id;
			break;
		}
		
	}
	else{
		// 普通按键
		switch (keyMethod->keyMode)
			{
			// 数字模式
			case Numeric:
				numeric_process(keyMethod->keyValue,key.name[0]);
				break;
			// 字母模式
			case Alphabetic:
				alphabetic_process(keyMethod->keyValue,key.letter);
				break;
			default:
				break;
			}
	}
}
