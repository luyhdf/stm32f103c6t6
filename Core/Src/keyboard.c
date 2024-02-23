/*
 * keyboard.c
 *
 *  Created on: Feb 23, 2024
 *      Author: luyh
 */

#include "keyboard.h"
#include "main.h"
#include "stm32f1xx_hal.h"

uint16_t Row_Pin_Out[4] = {KEY_R1_Pin, KEY_R2_Pin, KEY_R3_Pin, KEY_R4_Pin};

uint16_t Col_Pin_In[4] = {KEY_C1_Pin, KEY_C2_Pin, KEY_C3_Pin, KEY_C4_Pin};

const uint8_t keymap[4][4] = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 10, 11, 12},
	{13, 14, 15, 16}};

uint8_t keyboard_scan()
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
	return 0;
}
