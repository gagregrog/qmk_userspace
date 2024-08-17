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
  STRING__TD_ACTION_GAGREGROG(":skull:"),
  STRING__TD_ACTION_GAGREGROG(":fire:"),
  STRING__TD_ACTION_GAGREGROG(":skull::skull:"),
  STRING__TD_ACTION_GAGREGROG(":fire::fire:"),
  STRING__TD_ACTION_GAGREGROG(":skull::skull::skull:"),
  STRING__TD_ACTION_GAGREGROG(":fire::fire::fire:"),
  STRING__TD_ACTION_GAGREGROG(":skull::skull::skull::skull:"),
  STRING__TD_ACTION_GAGREGROG(":fire::fire::fire::fire:"),
  STRING__TD_ACTION_GAGREGROG(":skull:skull:::skull::skull::skull:"),
  STRING__TD_ACTION_GAGREGROG(":fire::fire::fire::fire::fire:"),
};
void td_handle_L1_K1(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K1);
}

// L1_K2
static td_actions_gagregrog_t actions_L1_K2[] = {
  STRING__TD_ACTION_GAGREGROG(":pregnant_man:"),
  STRING__TD_ACTION_GAGREGROG(":middle_finger:"),
  STRING__TD_ACTION_GAGREGROG(":pregnant_man::pregnant_man:"),
  STRING__TD_ACTION_GAGREGROG(":middle_finger::middle_finger:"),
  STRING__TD_ACTION_GAGREGROG(":pregnant_man::pregnant_man::pregnant_man:"),
  STRING__TD_ACTION_GAGREGROG(":middle_finger::middle_finger::middle_finger:"),
  STRING__TD_ACTION_GAGREGROG(":pregnant_man::pregnant_man::pregnant_man::pregnant_man:"),
  STRING__TD_ACTION_GAGREGROG(":middle_finger::middle_finger::middle_finger::middle_finger:"),
  STRING__TD_ACTION_GAGREGROG(":pregnant_man:pregnant_man:::pregnant_man::pregnant_man::pregnant_man:"),
  STRING__TD_ACTION_GAGREGROG(":middle_finger::middle_finger::middle_finger::middle_finger::middle_finger:"),
};
void td_handle_L1_K2(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L1_K2);
}

// L2_K2
static td_actions_gagregrog_t actions_L2_K2[] = {
  NULL__TD_ACTION_GAGREGROG,
};

void td_handle_L2_K2(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_L2_K2);
}
