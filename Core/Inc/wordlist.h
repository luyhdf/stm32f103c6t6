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
#include "wordlist_slip39.h"
#endif

#ifdef WORDLIST_BIP39
#include "wordlist_bip39.h"
#endif


#endif /* INC_WORDLIST_H_ */
