#include QMK_KEYBOARD_H
#include "gagregrog.h"
#include "tap_dance_utils.h"

void TD_NOOP(void) {};

uint8_t get_action_index(tap_dance_state_t *state, bool pressed) {
  uint8_t is_pressed = pressed ? 1 : 0;
  uint8_t index = (state->count - 1) * 2 + is_pressed;
  return index;
}

void handle_tap_dance_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
) {
  td_data_gagregrog_t *td_data = (td_data_gagregrog_t *)user_data;
  if (!td_data->has_begun) {
    td_data->has_begun = true;
    tap_dance_begin_gagregrog(
      actions,
      num_actions,
      state,
      user_data
    );
  } else {
    td_data->has_begun = false;
    tap_dance_end_gagregrog(
      actions,
      num_actions,
      state,
      user_data
    );
  }
}

void tap_dance_begin_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
) {
  td_data_gagregrog_t *td_data = (td_data_gagregrog_t *)user_data;
  td_data->pressed = state->pressed;
  uint8_t action_index = get_action_index(state, td_data->pressed);
  if (action_index >= num_actions) { return; }
  td_actions_gagregrog_t action = actions[action_index];

  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: 
          send_secret(action.key);
          break;
      #endif
      default:
        if (td_data->pressed) {
          register_code16(action.key);
        } else {
          tap_code16(action.key);
        }
        break;
    }
  } else if (strcmp(action.string, TD_NULL) != 0) {
      send_string(action.string);
  } else if (action.layer < TD_MAX_LAYER_GAGREGROG) {
    // if a layer action is used on a tap action, it will activate the layer indefinitely
    // if a layer action is used on a hold action, it will activate the layer until the hold is released
    if (td_data->pressed) {
      layer_on(action.layer);
    } else {
      layer_invert(action.layer);
    }
  } else if (action.fn != TD_NOOP) {
    action.fn();
  }
}

void tap_dance_end_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
) {
  td_data_gagregrog_t *td_data = (td_data_gagregrog_t *)user_data;
  uint8_t action_index = get_action_index(state, td_data->pressed);
  if (action_index >= num_actions) { return; }
  td_actions_gagregrog_t action = actions[action_index];
  if (action.key > 0) {
    switch (action.key) {
      #if defined(INCLUDE_SECRETS) && !defined(NO_SECRETS)
        case KC_SECRET_1 ... KC_SECRET_5: break;
      #endif
      default: {
        if (td_data->pressed) {
          unregister_code16(action.key);
        }
      }
    }
  } else if (action.layer < TD_MAX_LAYER_GAGREGROG && td_data->pressed) {
    // if the aciton is a hold, deactivate the layer now that the td key is released
    layer_off(action.layer);
  } // no other layers get triggered when the key is released
}
