// this config is automatically included when the firmware is built with a gagregrog keymap

#pragma once

#define QMK_USER_H "gagregrog.h"

// this makes it so that quick rolls are treated as taps
#define SMTD_GLOBAL_RELEASE_TERM 15
#define MAX_DEFERRED_EXECUTORS 10

#ifdef TRACKPOINT_ENABLE
#    ifdef PS2_DRIVER_USART
#        ifndef PS2_CLOCK_PIN
#            define PS2_CLOCK_PIN D5
#        endif // PS2_CLOCK_PIN
#        ifndef PS2_DATA_PIN
#            define PS2_DATA_PIN D2
#        endif // PS2_DATA_PIN

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#        define PS2_USART_INIT()                                                                         \
            do {                                                                                         \
                PS2_CLOCK_DDR &= ~(1 << PS2_CLOCK_BIT);                                                  \
                PS2_DATA_DDR &= ~(1 << PS2_DATA_BIT);                                                    \
                UCSR1C = ((1 << UMSEL10) | (3 << UPM10) | (0 << USBS1) | (3 << UCSZ10) | (0 << UCPOL1)); \
                UCSR1A = 0;                                                                              \
                UBRR1H = 0;                                                                              \
                UBRR1L = 0;                                                                              \
            } while (0)
#        define PS2_USART_RX_INT_ON()                    \
            do {                                         \
                UCSR1B = ((1 << RXCIE1) | (1 << RXEN1)); \
            } while (0)
#        define PS2_USART_RX_POLL_ON() \
            do {                       \
                UCSR1B = (1 << RXEN1); \
            } while (0)
#        define PS2_USART_OFF()                           \
            do {                                          \
                UCSR1C = 0;                               \
                UCSR1B &= ~((1 << RXEN1) | (1 << TXEN1)); \
            } while (0)
#        define PS2_USART_RX_READY (UCSR1A & (1 << RXC1))
#        define PS2_USART_RX_DATA UDR1
#        define PS2_USART_ERROR (UCSR1A & ((1 << FE1) | (1 << DOR1) | (1 << UPE1)))
#        define PS2_USART_RX_VECT USART1_RX_vect

#        define PS2_MOUSE_INVERT_X
#        define PS2_MOUSE_INVERT_Y
#        define PS2_MOUSE_X_MULTIPLIER 5
#        define PS2_MOUSE_Y_MULTIPLIER 5
#    endif // PS2_DRIVER_USART
#endif     // TRACKPOINT_ENABLE

// Features that we want to enable automatically

#ifdef OLED_ENABLE
#    define OLED_FONT_H "users/gagregrog/oled/gagregrog_font.h"
#    define OLED_SCROLL_TIMEOUT 2000
#endif // OLED_ENABLE

#ifdef KEY_OVERRIDE_ENABLE
#    define USE_BRACKET_OVERRIDE
#endif // KEY_OVERRIDE_ENABLE

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define ENABLE_COMPILE_KEYCODE

#ifdef POINTING_DEVICE_ENABLE
// #    define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// #    define AUTO_MOUSE_TIME 750
#    define SCROLL_CPI 2000
#    define MOUSE_CPI 2000
#endif // POINTING_DEVICE_ENABLE

#define TAPPING_TERM_PER_KEY
#ifndef TAPPING_TERM
#    define TAPPING_TERM 175
#endif
