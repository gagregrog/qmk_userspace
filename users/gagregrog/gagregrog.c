#include QMK_KEYBOARD_H
#include "gagregrog.h"


#ifdef POINTING_DEVICE_ENABLE
__attribute__ ((weak))
report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
  return mouse_report;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (mouse_report.x | mouse_report.y | mouse_report.h | mouse_report.v) {
    #ifdef POINTING_DEVICE_INVERT_SCROLL
      mouse_report.h *= -1;
      mouse_report.v *= -1;
    #endif

    #if defined(KB_DILEMMA) || defined(KB_CHARYBDIS)
      #if defined(KB_DILEMMA)
        uint8_t mods = get_mods();
        bool is_snipe_modifier_active = mods & MOD_MASK_CTRL;
        // activate drag scroll on dilemma if any of these mods are active
        bool is_drag_modifier_active = mods & (MOD_MASK_GUI | MOD_MASK_SHIFT | MOD_MASK_ALT);
        bool drag_scroll_enabled = dilemma_get_pointer_dragscroll_enabled();

        if (!drag_scroll_enabled && is_drag_modifier_active) {
          dilemma_set_pointer_dragscroll_enabled(true);
        } else if (drag_scroll_enabled && !is_drag_modifier_active) {
          dilemma_set_pointer_dragscroll_enabled(false);
        }

        bool is_sniping_enabled = dilemma_get_pointer_sniping_enabled();
        if (!is_sniping_enabled && is_snipe_modifier_active) {
          dilemma_set_pointer_sniping_enabled(true);
        } else if (is_sniping_enabled && !is_snipe_modifier_active) {
          dilemma_set_pointer_sniping_enabled(false);
        }
      #elif defined(KB_CHARYBDIS)
        // TODO: enable base charybdis functionalityf
        // bool is_sniping_enabled = charybdis_get_pointer_sniping_enabled();
        // if (!is_sniping_enabled && is_snipe_modifier_active) {
        //   charybdis_set_pointer_sniping_enabled(true);
        // } else if (is_sniping_enabled && !is_snipe_modifier_active) {
        //   charybdis_set_pointer_sniping_enabled(false);
        // }
      #endif
    #endif // defined(KB_DILEMMA) || defined(KB_CHARYBDIS)
  }

  return pointing_device_task_keymap(mouse_report);
}
#endif // POINTING_DEVICE_ENABLE

#ifdef TRACKPOINT_ENABLE
  bool msScrollPress = false;
  bool msScrollLock = false;
  bool msEnabled = true;
  uint8_t mouseReportCount = 0;
  uint8_t mouseDebounce = 3;
  bool hasIgnoredFirstReport = false;

  void rotate_mouse_report(report_mouse_t *mouse_report) {
    // https://doubleroot.in/lessons/coordinate-geometry-basics/rotation-of-axes/
    // theta = -pi/4
    const double cos_theta = 0.7071067811865475;
    const double sin_theta = -0.7071067811865475;
    double x_cos = cos_theta * mouse_report->x;
    double y_cos = cos_theta * mouse_report->y;
    double x_sin = sin_theta * mouse_report->x;
    double y_sin = sin_theta * mouse_report->y;
    double x = x_cos - y_sin;
    double y = x_sin + y_cos;
    mouse_report->x = (mouse_xy_report_t) x;
    mouse_report->y = (mouse_xy_report_t) y;
  }

  void ignoreMouseReport(report_mouse_t *mouse_report) {
    mouse_report->x = 0;
    mouse_report->y = 0;
    mouse_report->h = 0;
    mouse_report->v = 0;
    mouse_report->buttons = 0;
  }

  void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    if (!hasIgnoredFirstReport) {
      // first report always does a right click and jumps the cursor,
      // so let's ignore it
      hasIgnoredFirstReport = true;
      ignoreMouseReport(mouse_report);
      return;
    }

    if (!msEnabled) {
      ignoreMouseReport(mouse_report);
      return;
    }

    // process special mouse mode whether pressed or locked
    bool lockActive = msScrollLock && !msScrollPress;
    bool pressActive = !msScrollLock && msScrollPress;
    bool mouseScrollActive = (lockActive || pressActive);

    // only handle special mouse modes when enabled by press or lock
    if (!mouseScrollActive) {
      return;
    }

    // debounce mouse mode actions so it is more controllable
    if (mouseReportCount > mouseDebounce) {
      mouseReportCount = 0;
    }

    // only register mouse mode behavior once every mouseDebounce times
    if (!mouseReportCount) {
      // reassign normal mouse movement to scroll movement
      mouse_report->h = mouse_report->x / -3;
      mouse_report->v = mouse_report->y / -3;
    }

    // disable normal mouse movement
    // must happen after reassigning the movement above
    mouse_report->x = 0;
    mouse_report->y = 0;

    // increment counter to limit scroll processing
    mouseReportCount++;
  }
#endif // TRACKPOINT_ENABLE

#if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}

#endif // INCLUDE_SECRETS

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
  #if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
    // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_layer(_LAYER_AUTOMOUSE);
    // always required before the auto mouse feature will work
    set_auto_mouse_enable(true);
    #if defined(POINTING_DEVICE_COMBINED)
      // flash each side so cpi is set for each
      pmw33xx_set_cpi(0, is_keyboard_left() ?  SCROLL_CPI : MOUSE_CPI);
    #endif // POINTING_DEVICE_COMBINED
  #endif  // POINTING_DEVICE_AUTO_MOUSE_ENABLE

  keyboard_post_init_keymap();
}

// CIRQUE defines its own auto_mouse_activation, so skip if in use
#if defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE) && !CIRQUE_PINNACLE_POSITION_MODE
  // require 8 mouse movements in a row to trigger an auto mouse layer
  #define AUTO_MOUSE_BUFFER_TARGET 0b11111111

  uint8_t auto_mouse_buffer = 0;
  bool auto_mouse_activation(report_mouse_t mouse_report) {
    bool has_movement = mouse_report.x != 0 || mouse_report.y != 0;
    // shift the LSB to make space for the latest
    auto_mouse_buffer <<= 1;
    // fill the LSB with 1 or 0 if there was any mouse movement
    auto_mouse_buffer |= (uint8_t)has_movement;
    // only keep the 8 LSBS
    auto_mouse_buffer &= AUTO_MOUSE_BUFFER_TARGET;
    // only count it as a move if the buffer is filled
    bool is_mouse_move = auto_mouse_buffer == AUTO_MOUSE_BUFFER_TARGET;

    return is_mouse_move;
  }
#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE

#if defined(POINTING_DEVICE_COMBINED)
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
  static int8_t scroll_debounce_x = 0;
  static int8_t scroll_debounce_y = 0;

  scroll_debounce_x += left_report.x;
  scroll_debounce_y += left_report.y;

  left_report.x = 0;
  left_report.y = 0;

  if (abs(scroll_debounce_x) > 100) {
    left_report.h = scroll_debounce_x > 0 ? -1 : 1;
    scroll_debounce_x = 0;
  }
  if (abs(scroll_debounce_y) > 100) {
    left_report.v = scroll_debounce_y > 0 ? -1 : 1;
    scroll_debounce_y = 0;
  }

  // disable horizontal scrolling (require shift)
  left_report.h = 0;
  return pointing_device_combine_reports(left_report, right_report);
}
#endif // POINTING_DEVICE_COMBINED

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true; // Process all other keycodes normally
}

bool process_record_hrm(uint16_t keycode, keyrecord_t *record) {
  // only trigger the keycode on tap, not on hold
  if (record->event.pressed && record->tap.count) {
    tap_code16(keycode);
    return false;
  }
  // process the hold mod as normal, but don't process taps further
  return !record->tap.count;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef DEBUG_MATRIX
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
  #endif

  #ifdef MOUSE_TURBO_CLICK
    if (!process_mouse_turbo_click(keycode, record, MS_TURBO)) { return false; }
  #endif // MOUSE_TURBO_CLICK

  static bool is_colemak_enabled = true;
  static bool is_hrm_enabled = true;

  switch (keycode) {
#if defined(KARABINER)
    // For karabiner we use space and backspace to activate built in layers,
    // so we need to ensure that HRMs are disabled when space is activated
    // so that we are able to activate sublayers while space/backspace is held
    case KC_BSPC:
    case KC_SPC:
      if (!is_hrm_enabled) {
        return true;
      }

      if (record->event.pressed) {
        if (is_colemak_enabled) {
          layer_on(_LAYER_COLEMAK_DH);
        } else {
          layer_on(_LAYER_QWERTY);
        }
      } else {
        if (is_colemak_enabled) {
          layer_off(_LAYER_COLEMAK_DH);
        } else {
          layer_off(_LAYER_QWERTY);
        }
      }

      return true;
#endif // KARABINER
#if defined(DEBUG_RGB_MATRIX)
    case RM_NEXT:
    case RM_TOGG:
        debug_rgb_matrix(keycode, record->event.pressed);
        return true;
#endif // DEBUG_RGB_MATRIX
    // TODO: replace with better ifdef
    #if defined(LAYOUT_split_3x5_3_h) || defined(LAYOUT_split_4x6_6)
      case TG_BASE:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            is_colemak_enabled = true;
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            is_colemak_enabled = true;
            layer_on(_LAYER_COLEMAK_DH);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            is_colemak_enabled = false;
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_COLEMAK_DH);
          } else {
            is_colemak_enabled = false;
            layer_on(_LAYER_QWERTY_HRM);
          }
        }
        return false;
      case TG_HRM:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            is_hrm_enabled = false;
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            is_hrm_enabled = true;
            layer_on(_LAYER_QWERTY_HRM);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            is_hrm_enabled = true;
            layer_off(_LAYER_COLEMAK_DH);
          } else {
            is_hrm_enabled = false;
            layer_on(_LAYER_COLEMAK_DH);
          }
        }
        return false;
    #endif // LAYOUT_split_3x5_3_h || LAYOUT_split_4x6_6
    #ifdef TRACKPOINT_ENABLE
      case MOUSE_SCROLL_PRESS:
        msScrollPress = record->event.pressed;
        return false; // Skip all further processing of this key
      case MOUSE_SCROLL_LOCK:
        if (record->event.pressed) {
          msScrollLock = !msScrollLock;
        }
        return false;
      case MOUSE_TOGGLE:
        if (record->event.pressed) {
          msEnabled = !msEnabled;
        }
        return false;
    #endif // TRACKPOINT_ENABLE
    #ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
      case AM_TOGGLE:
        if(record->event.pressed) {
            auto_mouse_layer_off(); // disable target layer if needed
            set_auto_mouse_enable((AUTO_MOUSE_ENABLED) ^ 1);
            #ifdef CONSOLE_ENABLE
            xprintf("Toggling Auto Mouse: %d\n", AUTO_MOUSE_ENABLED);
            #endif
        }
        return false;
      case AM_KILL:
        if(record->event.pressed) {
            auto_mouse_layer_off();
        }
        return false;
      case MS_BTN1:
      case MS_BTN2:
        if(get_mods() & MOD_MASK_SHIFT) {
          // runs on both press and release since otherwise this is treated
          // as a mouse key and reactivates the mouse layer
          auto_mouse_layer_off();
          return false;
        }
        return true;
    #endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE

    // [START] SHIFTED KEYCODES
    // Automatically shifted keycodes such as () and {}
    // inconsistently register when Karabiner is enabled
    // so we add a slight delay after registering the mod
    // before we send the key to ensure the shift is registered
    case PR_LPRN:
        // "9" maps to "(" when shifted
        return process_key_after_mods(KC_9, MOD_LSFT, record);
    case PR_RPRN:
        // "0" maps to ")" when shifted
        return process_key_after_mods(KC_0, MOD_LSFT, record);
    case PR_LCBR:
        // "[" maps to "{" when shifted
        return process_key_after_mods(KC_LBRC, MOD_LSFT, record);
    case PR_RCBR:
        // "]" maps to "}" when shifted
        return process_key_after_mods(KC_RBRC, MOD_LSFT, record);
    // [END] SHIFTED KEYCODES

    // [START] HRM ADVANCED KEYCODES
    // for any advanced keycodes used with HRM we
    // create a custom keycode and then manually
    // manage the desired outcome here
    case RSFT_T(KC_HRM_MAC_LOCK):
      return process_record_hrm(KC_MAC_LOCK, record);
    case RSFT_T(KC_HRM_MV_L):
      return process_record_hrm(KC_MV_L, record);
    case RGUI_T(KC_HRM_MV_C):
      return process_record_hrm(KC_MV_C, record);
    case LALT_T(KC_HRM_MV_R):
      return process_record_hrm(KC_MV_R, record);
    case RSFT_T(KC_HRM_MV_DL):
      return process_record_hrm(KC_MV_DL, record);
    case RGUI_T(KC_HRM_MV_D):
      return process_record_hrm(KC_MV_D, record);
    case LALT_T(KC_HRM_MV_DR):
      return process_record_hrm(KC_MV_DR, record);
    // [END] HRM ADVANCED KEYCODES

    default:
    #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
      return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
    #else
      return process_record_keymap(keycode, record);
    #endif
  }
}

#if defined(COMBO_ENABLE)
uint32_t combo_homerow_scroll_timer = 0;
void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_HRM_CTL:
            if (pressed) {
                tap_code(KC_F21);
            }
            break;
        case COMBO_HRM_ALT:
            if (pressed) {
                tap_code(KC_F22);
            }
            break;
        case COMBO_HRM_GUI:
            if (pressed) {
                tap_code(KC_F23);
            }
            break;
        case COMBO_HRM_SFT:
            if (pressed) {
                combo_homerow_scroll_timer = timer_read32();
            } else {
                uint32_t duration = timer_read32() - combo_homerow_scroll_timer;
                if (duration < 250) {
                    tap_code(KC_F24);
                } else {
                    caps_word_on();
                }
            }
            break;
    }
}
#endif // COMBO_ENABLE

// exempt all thumb keys from chordal hold rules
#if defined(LAYOUT_split_3x5_3_h)
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3_h(
        '*', '*', '*', '*', '*',  '*', '*', '*', '*', '*',
        'L', 'L', 'L', 'L', '*',  '*', 'R', 'R', 'R', 'R',
        '*', '*', '*', '*', '*',  '*', '*', '*', '*', '*',
                  '*', '*', '*',  '*', '*', '*'
    );
#elif defined(LAYOUT_split_4x6_6)
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_4x6_6(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                            '*', '*',  '*', '*',
                            '*', '*',  '*', '*',
                            '*', '*',  '*', '*'
    );
#endif // LAYOUT_split_3x5_3_h || LAYOUT_split_4x6_6

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    // return *true* to treat as a mod hold
    // return *false* to treat as a tap

    // Exceptionally allow some one-handed chords
    switch (tap_hold_keycode) {
        case RSFT_T(KC_N):
            // allow right hand shift + ' to trigger "
            // allow right hand shift + / to trigger ?
            // allow right hand shift + ; to trigger :
            if (other_keycode == KC_QUOT || other_keycode == KC_SLASH || other_keycode == KC_SCLN) {
                return true;
            }
            break;
    }

    // Otherwise defer to the opposite hands rule.
    return get_chordal_hold_default(tap_hold_record, other_record);
}
