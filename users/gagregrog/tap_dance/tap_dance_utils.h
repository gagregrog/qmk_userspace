#include "quantum.h"
#include <string.h>

#pragma once

typedef void (td_user_fn_t)(void);

typedef struct {
  uint16_t key;
  td_user_fn_t *fn;
  uint8_t layer;
  char *string;
} td_actions_gagregrog_t;

typedef struct {
  bool pressed;
  bool has_begun;
} td_data_gagregrog_t;

void tap_dance_begin_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
);

void tap_dance_end_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
);

void handle_tap_dance_gagregrog(
  td_actions_gagregrog_t actions[],
  uint8_t num_actions,
  tap_dance_state_t *state,
  void *user_data
);

void TD_NOOP(void);
#define TD_NULL "TD_NULL"

#define TD_MAX_LAYER_GAGREGROG 255

#define KEY__TD_ACTION_GAGREGROG(KEY) { \
  .key = KEY, \
  .fn = TD_NOOP, \
  .layer = TD_MAX_LAYER_GAGREGROG, \
  .string = TD_NULL \
}
#define STRING__TD_ACTION_GAGREGROG(STR) { \
 .key = 0, \
 .fn = TD_NOOP, \
 .layer = TD_MAX_LAYER_GAGREGROG, \
 .string = STR \
}
#define LAYER__TD_ACTION_GAGREGROG(LAYER) { \
  .key = 0, \
  .fn = TD_NOOP, \
  .layer = LAYER, \
  .string = TD_NULL \
}
#define FN__TD_ACTION_GAGREGROG(FN) { \
  .key = 0, \
  .fn = FN, \
  .layer = TD_MAX_LAYER_GAGREGROG, \
  .string = TD_NULL \
}
#define NULL__TD_ACTION_GAGREGROG { \
 .key = 0, \
 .fn = TD_NOOP, \
 .layer = TD_MAX_LAYER_GAGREGROG, \
 .string = TD_NULL \
}
#define BOOT__TD_ACTION_GAGREGROG FN__TD_ACTION_GAGREGROG(reset_keyboard)

#define ACTION_TAP_DANCE_GAGREGROG( \
  user_dance_handler \
) { \
  .fn = { \
    NULL, \
    (void *)user_dance_handler, \
    (void *)user_dance_handler \
  }, \
  .user_data = (void *)&((td_data_gagregrog_t) { .pressed = false, .has_begun = false }), \
}

#define TD_ARGS_GAGREGROG tap_dance_state_t *state, void *user_data
#define HANDLE_TAP_DANCE_GAGREGROG(actions) handle_tap_dance_gagregrog(actions, ARRAY_SIZE(actions), state, user_data)
