#include "compiler.h"

/* for storing led state */
volatile extern char LED_REG1;
volatile extern char LED_REG2;

//+----------------------------------------------+------------+-------------+
//|                   RPM                        |    GEAR    |     TEMP    |
//|     PORTE 0-7           PORTB 0-7            |  PORTC 0-6 |  PORTA 5-7  |
//|  GRØN   |   GUL   |    RØD     |     Blå     |  7-segment | GRØN GUL RØD|
//| 1 2 3 4 | 5 6 7 8 | 9 10 11 12 | 13 14 15 16 |            |  1    2   3 |
//+----------------------------------------------+------------+-------------+

/* rpm leds */
#define LED1_ON LED_REG1 |= 0x1
#define LED1_OFF LED_REG1 &= 0xE
#define LED1_TOGGLE LED_REG1 ^= 0x1

#define LED2_ON LED_REG1 |= 0x2
#define LED2_OFF LED_REG1 &= 0xD
#define LED2_TOGGLE LED_REG1 ^= 0x2

#define LED3_ON LED_REG1 |= 0x4
#define LED3_OFF LED_REG1 &= 0xB
#define LED3_TOGGLE LED_REG1 ^= 0x4

#define LED4_ON LED_REG1 |= 0x8
#define LED4_OFF LED_REG1 &= 0x7
#define LED4_TOGGLE LED_REG1 ^= 0x8

#define LED5_ON LED_REG1 |= 0x10
#define LED5_OFF LED_REG1 &= 0xEF
#define LED5_TOGGLE LED_REG1 ^= 0x10

#define LED6_ON LED_REG1 |= 0x20
#define LED6_OFF LED_REG1 &= 0xDF
#define LED6_TOGGLE LED_REG1 ^= 0x20

#define LED7_ON LED_REG1 |= 0x40
#define LED7_OFF LED_REG1 &= 0xBF
#define LED7_TOGGLE LED_REG1 ^= 0x40

#define LED8_ON LED_REG1 |= 0x80
#define LED8_OFF LED_REG1 &= 0x7F
#define LED8_TOGGLE LED_REG1 ^= 0x80

#define LED9_ON LED_REG2 |= 0x1
#define LED9_OFF LED_REG2 &= 0xE
#define LED9_TOGGLE LED_REG2 ^= 0x1

#define LED10_ON LED_REG2 |= 0x2
#define LED10_OFF LED_REG2 &= 0xD
#define LED10_TOGGLE LED_REG2 ^= 0x2

#define LED11_ON LED_REG2 |= 0x4
#define LED11_OFF LED_REG2 &= 0xB
#define LED11_TOGGLE LED_REG2 ^= 0x4

#define LED12_ON LED_REG2 |= 0x8
#define LED12_OFF LED_REG2 &= 0x7
#define LED12_TOGGLE LED_REG2 ^= 0x8

#define LED13_ON LED_REG2 |= 0x10
#define LED13_OFF LED_REG2 &= 0xEF
#define LED13_TOGGLE LED_REG2 ^= 0x10

#define LED14_ON LED_REG2 |= 0x20
#define LED14_OFF LED_REG2 &= 0xDF
#define LED14_TOGGLE LED_REG2 ^= 0x20

#define LED15_ON LED_REG2 |= 0x40
#define LED15_OFF LED_REG2 &= 0xBF
#define LED15_TOGGLE LED_REG2 ^= 0x40

#define LED16_ON LED_REG2 |= 0x80
#define LED16_OFF LED_REG2 &= 0x7F
#define LED16_TOGGLE LED_REG2 ^= 0x80

#define BLUE_ON LED13_ON; LED14_ON; LED15_ON; LED16_ON
#define BLUE_OFF LED13_OFF; LED14_OFF; LED15_OFF; LED16_OFF

/* 7-segment */
#define SEG_OFF PORTC = 0b00000000
#define SEG_0 PORTC = 0b00111111
#define SEG_1 PORTC = 0b00001001
#define SEG_2 PORTC = 0b01100111
#define SEG_3 PORTC = 0b01001111
#define SEG_4 PORTC = 0b01011001
#define SEG_5 PORTC = 0b01011110
#define SEG_6 PORTC = 0b01111110
#define SEG_7 PORTC = 0b00001011
#define SEG_8 PORTC = 0b01111111
#define SEG_9 PORTC = 0b01011011
#define SEG_E PORTC = 0b01110110
#define SEG_neutral PORTC = 0b01000000

/* status leds */
#define STATUS_LED_GREEN 64
#define STATUS_LED_GREEN_ON PORTA |= 64
#define STATUS_LED_GREEN_OFF PORTA &=~ 64
#define STATUS_LED_YELLOW 128
#define STATUS_LED_YELLOW_ON PORTA |= 128
#define STATUS_LED_YELLOW_OFF PORTA &=~ 128
#define STATUS_LED_RED 32
#define STATUS_LED_RED_ON PORTA |= 32
#define STATUS_LED_RED_OFF PORTA &=~ 32

/*  init alle porte til at styre display led'er og slå timer til at styre styrken til.
    Interrupt skal være slået til for at dioderne kan lyse. */
void init_display(void);
/* fader rpm led'er ind */
void fade_in(int time_ms, U8 steps);
