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

#ifdef WORDLIST_SLIP39
extern const char *wordlist_slip39[1024];
#endif

#ifdef WORDLIST_BIP39
extern const char *wordlist_bip39[2048];
#endif

#define MaxWordBufferSize 5

void wordlist_fit(KeyMethod keyMethod,uint16_t wordListBuffer[]);

#endif /* INC_WORDLIST_H_ */
