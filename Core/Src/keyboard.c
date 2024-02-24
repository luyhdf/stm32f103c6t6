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

char keyboard_process(KeyMode keymode,KeyMap key)
{
	char keyvalue;
	static char tempvalue;
	static uint8_t letter_index = 0; //字母模式下字母索引
	if (key.isFuncKey) { 
		// 功能键
	}
	else{
		// 普通按键
		switch (keymode)
			{
			case Numeric:
				keyvalue = key.name;
				break;
			case Alphabetic:
				keyvalue = key.letter[letter_index];
				break;
			default:
				break;
			}
		return keyvalue;
	}
	

}
