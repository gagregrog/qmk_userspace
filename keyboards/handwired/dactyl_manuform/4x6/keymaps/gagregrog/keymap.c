#include QMK_KEYBOARD_H
#include "gagregrog.h"

enum layers {
  _BASE,
  _NUMPAD,
  _MEDIA,
  _WINDOW,
  _MOUSE,
  _GAME,
  _RESET,
};

// layer switches
#define NUMPAD    TT(_NUMPAD)
#define MEDIA     TT(_MEDIA)
#define BASE      TT(_BASE)
#define TO_BASE   TO(_BASE)
#define WINDOW    TT(_WINDOW)
#define GAME      TO(_GAME)
#define MS_GRV    LT(_MOUSE, KC_GRV)
#define MO_RST    MO(_RESET)

#define CMD_ESC   LGUI_T(KC_ESC)
#define VOICE     LGUI(KC_F5)

#define DUP       LGUI(LSFT(KC_D))
#define ROW       LGUI(LSFT(KC_ENTER))

#define COPY      LGUI(KC_C)
#define PASTE     LGUI(KC_V)
#define CUT       LGUI(KC_X)
#define UNDO      LGUI(KC_Z)
#define NEXT      LGUI(KC_D)
#define SAVE      LGUI(KC_S)

// Left-hand home row mods - _BASE layer
#define CTRL_A    LCTL_T(KC_A)
#define ALT_R     LALT_T(KC_R)
#define GUI_S     LGUI_T(KC_S)
#define SHFT_T    LSFT_T(KC_T)

// Right-hand home row mods - _BASE layer
#define SHFT_N    RSFT_T(KC_N)
#define GUI_E     RGUI_T(KC_E)
#define ALT_I     LALT_T(KC_I)
#define CTRL_O    RCTL_T(KC_O)

// Left-hand home row mods - _NUMPAD layer
// #define CTRL_A    LCTL_T(KC_A)
#define ALT_LEFT  LALT_T(KC_LEFT)
#define GUI_DOWN  LGUI_T(KC_DOWN)
#define SHFT_RGT  LSFT_T(KC_RIGHT)

// Right-hand home row mods - _NUMPAD layer
#define SHFT_4    RSFT_T(KC_4)
#define GUI_5     RGUI_T(KC_5)
#define ALT_6     LALT_T(KC_6)
#define CTRL_PLS  RCTL_T(KC_PMNS)

uint32_t last_light_mode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base (colmak dh mod)
     * +-----------------------------------------+                             +-----------------------------------------+
     * | TAB  |   q  |   w  |   f  |   p  |   b  |                             |   j  |   l  |   u  |   y  |   p  |  ;   |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * |CMDESC|   a  |   r  |   s  |   t  |   g  |                             |   m  |   n  |   e  |   i  |   o  |CMD/' |
     * |------+------+------+------+------+------|                             |------+------+------+------+------+------|
     * | SHFT |   z  |   x  |   c  |   d  |   v  |                             |   k  |   h  |   ,  |   .  |   /  | SHFT |
     * +------+------+------+------+-------------+                             +-------------+------+------+------+------+
     *               |  [   |   ]  |                                                         |   {  |  }   |
     *               +-------------+-------------+                             +-------------+-------------+
     *                             | SPACE|BCKSPC|                             |  =/+ |  ENT |
     *                             +-------------+                             +-------------+
     *                                           +-------------+ +-------------+
     *                                           |   `~ |NUMPAD | |MEDIA |   -  |
     *                                           |------+------| |------+------|
     *                                           | LEFT |RIGHT | |  UP  |DOWN  |
     *                                           +-------------+ +-------------+
     */
    [_BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_NO,
        CMD_ESC, CTRL_A,  ALT_R,   GUI_S,   SHFT_T,  KC_G,                KC_M,    SHFT_N,  GUI_E,   ALT_I,   CTRL_O,  KC_SCLN,
        SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
                          KC_LBRC, KC_RBRC,                                                 KC_LCBR, KC_RCBR,
                                            KC_SPC,  KC_BSPC,             TRACKPT, KC_ENT,
                                            MS_GRV,  NUMPAD,              KC_EQL,  KC_MINS,
                                            MS_SCL_P,MS_SCL_L,            MEDIA,   KC_DLR
    ),

    [_NUMPAD] = LAYOUT(
        RGB_VAD, RGB_VAI, RGB_RMOD,KC_UP,   RGB_MOD, RGB_TOG,             VOICE,   KC_7,    KC_8,    KC_9,    KC_PSLS, KC_PAST,
        _______, KC_LCTL, ALT_LEFT,GUI_DOWN,SHFT_RGT,KC_NO,               KC_NO,   SHFT_4,  GUI_5,   ALT_6,   CTRL_PLS,KC_PPLS,
        _______, UNDO,    CUT,     COPY,    NEXT,    PASTE,               KC_NO,   KC_1,    KC_2,    KC_3,    KC_BSLS, KC_PIPE,
                          KC_NO,   KC_NO,                                                   KC_0,    KC_PDOT,
                                            _______, _______,             TRACKPT, ROW,
                                            _______, _______,             DUP,     KC_RALT,
                                            _______, _______,             WINDOW,  KC_HASH
    ),

    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, MS_TGGL,             _______, _______, KC_WH_D, _______, _______, _______,
        _______, _______, KC_BTN1, KC_BTN3, KC_BTN2, _______,             _______, KC_WH_L, KC_WH_U, KC_WH_R, _______, _______,
        _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______,
                          _______, _______,                                                 _______, _______,
                                            _______, _______,             TRACKPT, _______,
                                            _______, _______,             _______, GAME,
                                            _______, _______,             _______, _______
    ),

    [_GAME] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_GRV,  KC_ESC,
        KC_J,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                KC_NO,   KC_BTN1, KC_BTN3, KC_BTN2, KC_NO,   KC_NO,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                KC_NO,   KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO,
                          KC_ESC,  KC_ESC,                                                  KC_NO,   KC_NO,
                                            KC_SPC,  MS_TURBO,            TRACKPT, KC_ENT,
                                            KC_COMM, KC_NO,               KC_EQL,  KC_MINS,
                                            KC_SLSH, KC_MINS,             KC_NO,   TO_BASE
    ),

    [_MEDIA] = LAYOUT(
        KC_NO,   KC_NO,   KC_MV_UL,KC_MV_U, KC_MV_UR,KC_WH_U,             KC_NO,   KC_VOLD, KC_MUTE, KC_VOLU, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_MV_L, KC_MV_C, KC_MV_R, KC_WH_D,             KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_MV_DL,KC_MV_D, KC_MV_DR,KC_NO,               KC_NO,   KC_NO,   KC_MSTP, KC_NO,   KC_NO,   KC_NO,
                          KC_NO,   KC_NO,                                                   KC_NO,   KC_NO,
                                            _______, CW_TOGG,             TRACKPT, _______,
                                            KC_NO,   WINDOW,              KC_NO,   KC_NO,
                                            _______, _______,             _______, MO_RST
    ),

    [_WINDOW] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_MV_UL,KC_MV_U,  KC_MV_UR,KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_MV_L, KC_MV_C,  KC_MV_R, KC_NO,   KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_MV_DL,KC_MV_D,  KC_MV_DR,KC_NO,   KC_NO,
                          KC_NO,   KC_NO,                                                   KC_NO,    KC_NO,
                                            KC_NO,   KC_NO,               TRACKPT, KC_NO,
                                            KC_NO,   _______,             KC_NO,   KC_NO,
                                            KC_NO,   BASE,                _______, KC_NO
    ),

    [_RESET] = LAYOUT(
        QK_BOOT, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
                          KC_NO,   KC_NO,                                                   KC_NO,   KC_NO,  
                                            KC_NO,   KC_NO,               TRACKPT, KC_NO,  
                                            KC_NO,   KC_NO,               KC_NO,   KC_NO,  
                                            KC_NO,   KC_NO,               KC_NO,   _______
    )
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

void matrix_init_user(void) {
  rgblight_enable();
};

layer_state_t layer_state_set_user(layer_state_t state) {
  uint32_t current_light_mode = rgblight_get_mode();

  // if we're switching away from a color mode, store it
  if (current_light_mode != RGBLIGHT_MODE_STATIC_LIGHT) {
    last_light_mode = current_light_mode;
  }

  switch (biton32(state)) {
    case _BASE:
      rgblight_mode_noeeprom(last_light_mode);
      break;
    case _MEDIA:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_PURPLE);
      break;
    case _NUMPAD:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_GREEN);
      break;
    case _WINDOW:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_MAGENTA);
      break;
    case _MOUSE:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_TEAL);
      break;
    case _GAME:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_CHARTREUSE);
      break;
    case _RESET:
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_RED);
      break;
    default: //  for any other layers, or the default layer
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      rgblight_sethsv(HSV_ORANGE);
      break;
  }
  return state;
}

void keyboard_post_init_keymap(void) {
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv(HSV_ORANGE);
  last_light_mode = RGBLIGHT_MODE_RAINBOW_SWIRL;
}
