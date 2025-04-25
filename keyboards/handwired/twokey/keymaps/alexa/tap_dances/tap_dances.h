#include "gagregrog.h"

void td_handle_L1_K1(TD_ARGS_GAGREGROG);
void td_handle_L1_K2(TD_ARGS_GAGREGROG);

enum tap_dance_keys {
    T_L1_K1,
    T_L1_K2,
    TAP_DANCE_COUNT, // must keep this final member for tap dance introspection to work
};

#define TD_L1_K1 TD(T_L1_K1)
#define TD_L1_K2 TD(T_L1_K2)

extern tap_dance_action_t tap_dance_actions[TAP_DANCE_COUNT];
