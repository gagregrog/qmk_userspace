#include "gagregrog.h"
#include "tap_dances.h"
#include "keymap.h"

// - All Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [T_L1_K1]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_L1_K1),
  [T_L1_K2]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_L1_K2),
  [T_L2_K2]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_L2_K2),
};

// L1_K1
static td_actions_gagregrog_t actions_L1_K1[] = {
  KEY__TD_ACTION_GAGREGROG(SCRN_C),
  KEY__TD_ACTION_GAGREGROG(SCRN_S),
  NULL__TD_ACTION_GAGREGROG,
  KEY__TD_ACTION_GAGREGROG(KC_OS_LOCK),
  NULL__TD_ACTION_GAGREGROG,
  LAYER__TD_ACTION_GAGREGROG(L2),
  NULL__TD_ACTION_GAGREGROG,
  NULL__TD_ACTION_GAGREGROG,
  BOOT__TD_ACTION_GAGREGROG,
  BOOT__TD_ACTION_GAGREGROG
};
void td_handle_L1_K1(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K1);
}

// L1_K2
static td_actions_gagregrog_t actions_L1_K2[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_2),
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_3),
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_4),
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_5),
};
void td_handle_L1_K2(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K2);
}

// L2_K2
static td_actions_gagregrog_t actions_L2_K2[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_1),
};

void td_handle_L2_K2(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L2_K2);
}
