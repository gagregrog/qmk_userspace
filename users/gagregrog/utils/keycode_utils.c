#include "keycode_utils.h"

// ensure that a modifier is activated before sending the keycode
bool process_key_after_mods(uint16_t keycode, uint8_t mods, keyrecord_t *record) {
    if (record->event.pressed) {
        REGISTER_AFTER_MODS(keycode, mods);
    } else {
        UNREGISTER_MODDED_KEY(keycode, mods);
    }
    return false;
}
