#include "gagregrog.h"
#include "default_tap_dances.h"

// TODO: These tapdances don't do anything useful, but leaving this feature here for now
// so that it can be hydrated with useful tap dances later ;-)

// - All Tap Dances

tap_dance_action_t tap_dance_actions[] = {
  [T_MO_SPC]   = ACTION_TAP_DANCE_GAGREGROG(td_handle_MO_SPC),
  [T_MO_BSPC]  = ACTION_TAP_DANCE_GAGREGROG(td_handle_MO_BSPC),
};

static td_actions_gagregrog_t actions_MO_SPC[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SPC),
  KEY__TD_ACTION_GAGREGROG(KC_R),
};
void td_handle_MO_SPC(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_MO_SPC);
}

static td_actions_gagregrog_t actions_MO_BSPC[] = {
  KEY__TD_ACTION_GAGREGROG(KC_BSPC),
  KEY__TD_ACTION_GAGREGROG(KC_S),
};
void td_handle_MO_BSPC(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_MO_BSPC);
}

