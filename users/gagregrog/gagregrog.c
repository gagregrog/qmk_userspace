#include QMK_KEYBOARD_H
#include "gagregrog.h"

#if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
  void debug_rgb_matrix(bool useNextMode);
#endif

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

// Initialize variable holding the binary
// representation of active modifiers.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef MOUSE_TURBO_CLICK
    if (!process_mouse_turbo_click(keycode, record, MS_TURBO)) { return false; }
  #endif // MOUSE_TURBO_CLICK

  switch (keycode) {
    #if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
      case RGB_MOD:
      case RGB_TOG:
      if (record->event.pressed) {
        debug_rgb_matrix(keycode == RGB_MOD);
      }
      return true;
    #endif
    // replace with better ifdef
    #if defined(LAYOUT_split_3x5_3_h) || defined(LAYOUT_split_4x6_6)
      case TG_BASE:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            layer_on(_LAYER_COLEMAK_DH);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_COLEMAK_DH);
          } else {
            layer_on(_LAYER_QWERTY_HRM);
          }
        }
        return false;
      case TG_HRM:
        if (record->event.pressed) {
          if (IS_LAYER_ON(_LAYER_QWERTY_HRM)) {
            layer_on(_LAYER_QWERTY);
            layer_off(_LAYER_QWERTY_HRM);
          } else if (IS_LAYER_ON(_LAYER_QWERTY)) {
            layer_on(_LAYER_QWERTY_HRM);
            layer_off(_LAYER_QWERTY);
          } else if (IS_LAYER_ON(_LAYER_COLEMAK_DH)) {
            layer_off(_LAYER_COLEMAK_DH);
          } else {
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
      case KC_BTN1:
      case KC_BTN2:
        if(get_mods() & MOD_MASK_SHIFT) {
          // runs on both press and release since otherwise this is treated
          // as a mouse key and reactivates the mouse layer
          auto_mouse_layer_off();
          return false;
        }
        return true;
    #endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE
    // for any advanced keycodes with HRM we must check for the matched key
    // and then manually send the advanced keycode
    case RSFT_T(KC_HRM_MAC_LOCK):
      return process_record_hrm(KC_MAC_LOCK, record);
    case RSFT_T(KC_HRM_MV_L):
      return process_record_hrm(KC_MV_L, record);
    case RGUI_T(KC_HRM_MV_C):
      return process_record_hrm(KC_MV_C, record);
    case LALT_T(KC_HRM_MV_R):
      return process_record_hrm(KC_MV_R, record);
    default:
    #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
      return process_record_keymap(keycode, record) && process_record_secrets(keycode, record);
    #else
      return process_record_keymap(keycode, record);
    #endif
  }
}

#if defined(KEY_OVERRIDE_ENABLE) && defined(USE_BRACKET_OVERRIDE)
const key_override_t lcbr_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);
const key_override_t lbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
const key_override_t lprn_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
const key_override_t spc_gui_key_override = ko_make_basic(MOD_BIT_RGUI, KC_SPC, LGUI(KC_BSPC));
const key_override_t spc_alt_key_override = ko_make_basic(MOD_MASK_ALT, KC_SPC, LALT(KC_BSPC));
const key_override_t spc_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_BSPC);
const key_override_t vol_up_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLU, KC_MPLY);
const key_override_t vol_down_shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_VOLD, KC_MUTE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&lcbr_key_override,
  &lbrc_key_override,
  &lprn_key_override,
  &spc_gui_key_override,
  &spc_alt_key_override,
  &spc_shift_key_override,
  &vol_up_shift_key_override,
  &vol_down_shift_key_override,
	NULL // Null terminate the array of overrides!
};
#endif

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LGUI_T(KC_S):
    case RGUI_T(KC_E):
    case LSFT_T(KC_T):
    case RSFT_T(KC_N):
        return 130;
    default:
        return TAPPING_TERM;
  }
}

#if defined(CONSOLE_ENABLE) && defined(RGB_MATRIX_ENABLE)
void debug_rgb_matrix(bool useNextMode) {
  uint8_t mode = rgb_matrix_get_mode();
  HSV hsv = rgb_matrix_get_hsv();
  char name[40];
  uint8_t normalizedMode = mode;

  if (useNextMode) {
    normalizedMode += 1;
    if (normalizedMode == RGB_MATRIX_EFFECT_MAX) {
      normalizedMode = 1;
    }
  }

  switch (normalizedMode)
  {
#   ifdef ENABLE_RGB_MATRIX_NONE
    case RGB_MATRIX_NONE:
      strcpy(name, "RGB_MATRIX_NONE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_COLOR
    case RGB_MATRIX_SOLID_COLOR:     // Static single hue, no speed support
      strcpy(name, "RGB_MATRIX_SOLID_COLOR");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
    case RGB_MATRIX_ALPHAS_MODS:         // Static dual hue, speed is hue for secondary hue
      strcpy(name, "RGB_MATRIX_ALPHAS_MODS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    case RGB_MATRIX_GRADIENT_UP_DOWN:    // Static gradient top to bottom, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    case RGB_MATRIX_GRADIENT_LEFT_RIGHT:    // Static gradient left to right, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BREATHING
    case RGB_MATRIX_BREATHING:           // Single hue brightness cycling animation
      strcpy(name, "RGB_MATRIX_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SAT
    case RGB_MATRIX_BAND_SAT:        // Single hue band fading saturation scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_VAL
    case RGB_MATRIX_BAND_VAL:        // Single hue band fading brightness scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    case RGB_MATRIX_BAND_PINWHEEL_SAT:   // Single hue 3 blade spinning pinwheel fades saturation
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    case RGB_MATRIX_BAND_PINWHEEL_VAL:   // Single hue 3 blade spinning pinwheel fades brightness
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    case RGB_MATRIX_BAND_SPIRAL_SAT:     // Single hue spinning spiral fades saturation
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    case RGB_MATRIX_BAND_SPIRAL_VAL:     // Single hue spinning spiral fades brightness
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
    case RGB_MATRIX_CYCLE_ALL:           // Full keyboard solid hue cycling through full gradient
      strcpy(name, "RGB_MATRIX_CYCLE_ALL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    case RGB_MATRIX_CYCLE_LEFT_RIGHT:    // Full gradient scrolling left to right
      strcpy(name, "RGB_MATRIX_CYCLE_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    case RGB_MATRIX_CYCLE_UP_DOWN:       // Full gradient scrolling top to bottom
      strcpy(name, "RGB_MATRIX_CYCLE_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    case RGB_MATRIX_CYCLE_OUT_IN:        // Full gradient scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    case RGB_MATRIX_CYCLE_OUT_IN_DUAL:   // Full dual gradients scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN_DUAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:  // Full gradient Chevron shapped scrolling left to right
      strcpy(name, "RGB_MATRIX_RAINBOW_MOVING_CHEVRON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    case RGB_MATRIX_CYCLE_PINWHEEL:      // Full gradient spinning pinwheel around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_PINWHEEL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    case RGB_MATRIX_CYCLE_SPIRAL:        // Full gradient spinning spiral around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_SPIRAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
    case RGB_MATRIX_DUAL_BEACON:         // Full gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_DUAL_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    case RGB_MATRIX_RAINBOW_BEACON:      // Full tighter gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    case RGB_MATRIX_RAINBOW_PINWHEELS:   // Full dual gradients spinning two halfs of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_PINWHEELS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINDROPS
    case RGB_MATRIX_RAINDROPS:           // Randomly changes a single key's hue
      strcpy(name, "RGB_MATRIX_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    case RGB_MATRIX_JELLYBEAN_RAINDROPS: // Randomly changes a single key's hue and saturation
      strcpy(name, "RGB_MATRIX_JELLYBEAN_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
    case RGB_MATRIX_HUE_BREATHING:       // Hue shifts up a slight ammount at the same time, then shifts back
      strcpy(name, "RGB_MATRIX_HUE_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
    case RGB_MATRIX_HUE_PENDULUM:        // Hue shifts up a slight ammount in a wave to the right, then back to the left
      strcpy(name, "RGB_MATRIX_HUE_PENDULUM");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_WAVE
    case RGB_MATRIX_HUE_WAVE:            // Hue shifts up a slight ammount and then back down in a wave to the right
      strcpy(name, "RGB_MATRIX_HUE_WAVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    case RGB_MATRIX_PIXEL_FRACTAL:       // Single hue fractal filled keys pulsing horizontally out to edges
      strcpy(name, "RGB_MATRIX_PIXEL_FRACTAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FLOW
    case RGB_MATRIX_PIXEL_FLOW:          // Pulsing RGB flow along LED wiring with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_FLOW");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
    case RGB_MATRIX_PIXEL_RAIN:          // Randomly light keys with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_RAIN");
      break;
#   endif
#   if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
    case RGB_MATRIX_TYPING_HEATMAP:      // How hot is your WPM!
      strcpy(name, "RGB_MATRIX_TYPING_HEATMAP");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    case RGB_MATRIX_DIGITAL_RAIN:        // That famous computer simulation
      strcpy(name, "RGB_MATRIX_DIGITAL_RAIN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:   // Pulses keys hit to hue & value then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_SIMPLE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    case RGB_MATRIX_SOLID_REACTIVE:      // Static single hue, pulses keys hit to shifted hue then fades to current hue
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    case RGB_MATRIX_SOLID_REACTIVE_WIDE:        // Hue & value pulse near a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_WIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:   // Hue & value pulse near multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    case RGB_MATRIX_SOLID_REACTIVE_CROSS:       // Hue & value pulse the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_CROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:  // Hue & value pulse the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTICROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    case RGB_MATRIX_SOLID_REACTIVE_NEXUS:       // Hue & value pulse away on the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_NEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SPLASH
    case RGB_MATRIX_SPLASH:              // Full gradient & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_MULTISPLASH
    case RGB_MATRIX_MULTISPLASH:         // Full gradient & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_MULTISPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_SPLASH
    case RGB_MATRIX_SOLID_SPLASH:        // Hue & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    case RGB_MATRIX_SOLID_MULTISPLASH:   // Hue & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_MULTISPLASH");
      break;
#   endif
    case RGB_MATRIX_EFFECT_MAX:
      strcpy(name, "RGB_MATRIX_EFFECT_MAX");
      break;
    default:
      strcpy(name, "UNKNOWN");
      break;
  }

  uprintf("%i. %s - HSV{%i, %i, %i}\n", mode, name, hsv.h, hsv.s, hsv.v);
}
#endif
