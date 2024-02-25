/*
 * wordlist.h
 *
 *  Created on: Feb 25, 2024
 *      Author: luyh
 */

#ifndef INC_WORDLIST_H_
#define INC_WORDLIST_H_

#include "main.h"
#include "keyboard.h"

extern const char *wordlist_slip39[];
extern const char *wordlist_bip39[];

#define MaxWordListSize 24
#define MaxWordBufferSize 5
#define NullWordIndex -1

typedef enum {
	BIP39,
	SLIP39
} WordListMode;  // 助记词模式 BIP39 或SLIP39

typedef enum {
	S12 = 12,
	S18 = 18,
    S20 = 20,
    S24 = 24
} WordListSize;  // 助记词长度

//typedef struct {
//    WordListMode mode; // 助记词模式 BIP39 或SLIP39
//    WordListSize totalSize;  // 助记词长度
//    int index;  // 匹配助记词列表索引
//    char buffer[MaxWordBufferSize];  // 缓存助记词列表
//    size_t bufferSize;  // 缓存助记词列表长度
//    char wordList[MaxWordListSize]; // 选择的助记词
//    size_t currentSize;  // 当前已选择的助记词长度
//} WordListMethod;

int wordlist_fit(KeyMethod keyMethod);

#endif /* INC_WORDLIST_H_ */
