#pragma once

#include "gagregrog.h"
#include "../tap_dance_utils.h"
#include "process_tap_dance.h"

void td_handle_MO_SPC(TD_ARGS_GAGREGROG);
void td_handle_MO_BSPC(TD_ARGS_GAGREGROG);

enum tap_dance_keys {
    T_MO_SPC,
    T_MO_BSPC,
    TAP_DANCE_COUNT, // must keep this final member for tap dance introspection to work
};

// NOTE: make sure to conditionally map these in keycodes.h so they can be safely shared throughout layouts
#define TD_MO_SPC TD(T_MO_SPC)
#define TD_MO_BSPC TD(T_MO_BSPC)

extern tap_dance_action_t tap_dance_actions[TAP_DANCE_COUNT];
