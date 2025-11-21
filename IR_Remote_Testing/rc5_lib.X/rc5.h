/* 
 * RC5 (36KHz Phillips protocol) Decoding library for AVR
 * Copyright (c) 2011 Filip Sobalski <pinkeen@gmail.com>
 * based on the idea presented by Guy Carpenter
 * on http://www.clearwater.com.au/rc5
 * 
 * Tested on ATmega328P. Designed for 16MHz crystal.
 * Should work on the ATmega{4/8/16/32}8 family 
 * without modification. Uses 16bit timer and an 
 * external interrupt.
 * 
 * I you use a different clock then adjust the timer
 * prescaler and pulse lengths accordingly.
 * 
 * Should be trivial to adapt to other AVRs sporting
 * a 16bit timer and an external interrupt. 
 * 
 */
#ifndef RC5_H
#define RC5_H

#include <stdint.h>
#include <stdint.h>
#include <stdbool.h>

#define RC5_GetStartBits(command) ((command & 0x3000) >> 12)
#define RC5_GetToggleBit(command) ((command & 0x800) >> 11)
#define RC5_GetAddressBits(command) ((command & 0x7C0) >> 6)
#define RC5_GetCommandBits(command) (command & 0x3F)
#define RC5_GetCommandAddressBits(command) (command & 0x7FF)

#define SHORT_MIN 888   /* 444 microseconds */
#define SHORT_MAX 2666  /* 1333 microseconds */
#define LONG_MIN 2668   /* 1334 microseconds */
#define LONG_MAX 4444   /* 2222 microseconds */

typedef enum {
    STATE_START1, 
    STATE_MID1, 
    STATE_MID0, 
    STATE_START0, 
    STATE_ERROR, 
    STATE_BEGIN, 
    STATE_END
} State;

const uint8_t trans[4] = {0x01, 0x91, 0x9b, 0xfb};
volatile uint16_t command;
uint8_t ccounter;
volatile uint8_t has_new;
State state = STATE_BEGIN;


/* Initialize timer and interrupt */
//void RC5_Init();

/* Reset the library back to waiting-for-start state */
void RC5_Reset();

/* Poll the library for new command.
 * 
 * You should call RC5_Reset immediately after
 * reading the new command because it's halted once 
 * receiving a full command to ensure you can read it
 * before it becomes overwritten. If you expect that only 
 * one remote at a time will be used then library
 * should be polled at least once per ~150ms to ensure
 * that no command is missed.
 */
uint8_t RC5_NewCommandReceived(uint16_t *new_command);


#endif

