#pragma once

#include QMK_KEYBOARD_H

// add a slight delay before tapping the modified keycode
#define TAP_AFTER_MODS(KEY, MOD) \
    register_mods(MOD);          \
    wait_ms(10);                 \
    tap_code(KEY);               \
    unregister_mods(MOD)

// add a slight delay before holding the modified keycode
#define REGISTER_AFTER_MODS(KEY, MOD) \
    register_mods(MOD);               \
    wait_ms(10);                      \
    register_code(KEY)

// unregister a mod and key concurrently
#define UNREGISTER_MODDED_KEY(KEY, MOD) \
    unregister_code(KEY);               \
    unregister_mods(MOD)

// ensure that a modifier is activated before sending the keycode
bool process_key_after_mods(uint16_t keycode, uint8_t mods, keyrecord_t *record);
