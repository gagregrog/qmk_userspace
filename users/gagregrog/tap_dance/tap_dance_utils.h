#include "quantum.h"
#include <string.h>

#pragma once

typedef void(td_user_fn_t)(void);

typedef struct {
    uint16_t      key;
    uint8_t       unicode_map_index;
    uint8_t       times;
    td_user_fn_t *fn;
    uint8_t       layer;
    char         *string;
    const char   *unicode_string;
} td_actions_gagregrog_t;

typedef struct {
    bool pressed;
    bool has_begun;
} td_data_gagregrog_t;

void tap_dance_begin_gagregrog(td_actions_gagregrog_t actions[], uint8_t num_actions, tap_dance_state_t *state, void *user_data);

void tap_dance_end_gagregrog(td_actions_gagregrog_t actions[], uint8_t num_actions, tap_dance_state_t *state, void *user_data);

void handle_tap_dance_gagregrog(td_actions_gagregrog_t actions[], uint8_t num_actions, tap_dance_state_t *state, void *user_data);

void TD_NOOP(void);
#define TD_NULL "TD_NULL"

#define TD_MAX_LAYER_GAGREGROG 255

#define KEY__TD_ACTION_GAGREGROG(KEY) {.key = KEY, .unicode_map_index = 0, .times = 0, .fn = TD_NOOP, .layer = TD_MAX_LAYER_GAGREGROG, .string = TD_NULL, .unicode_string = TD_NULL}

#ifdef UNICODEMAP_ENABLE
#    define U_TD_A_G_1(UMI) U_TD_A_G_2(UMI, 1)
#    define U_TD_A_G_2(UMI, TIMES) {.key = 0, .unicode_map_index = UMI, .times = TIMES, .fn = TD_NOOP, .layer = TD_MAX_LAYER_GAGREGROG, .string = TD_NULL, .unicode_string = TD_NULL}
#    define U_TD_A_G_X(x, A, B, FUNC, ...) FUNC
#    define UNICODE__TD_ACTION_GAGREGROG(...) U_TD_A_G_X(, ##__VA_ARGS__, U_TD_A_G_2(__VA_ARGS__), U_TD_A_G_1(__VA_ARGS__))
#endif

#ifdef UNICODE_COMMON
#    define UNICODE_STRING__TD_ACTION_GAGREGROG(USTR) {.key = 0, .unicode_map_index = 0, .times = 0, .fn = TD_NOOP, .layer = TD_MAX_LAYER_GAGREGROG, .string = TD_NULL, .unicode_string = USTR}
#endif

#define STRING__TD_ACTION_GAGREGROG(STR) {.key = 0, .unicode_map_index = 0, .times = 0, .fn = TD_NOOP, .layer = TD_MAX_LAYER_GAGREGROG, .string = STR, .unicode_string = TD_NULL}

#define LAYER__TD_ACTION_GAGREGROG(LAYER) {.key = 0, .unicode_map_index = 0, .times = 0, .fn = TD_NOOP, .layer = LAYER, .string = TD_NULL, .unicode_string = TD_NULL}

#define FN__TD_ACTION_GAGREGROG(FN) {.key = 0, .unicode_map_index = 0, .times = 0, .fn = FN, .layer = TD_MAX_LAYER_GAGREGROG, .string = TD_NULL, .unicode_string = TD_NULL}

#define NULL__TD_ACTION_GAGREGROG {.key = 0, .unicode_map_index = 0, .times = 0, .fn = TD_NOOP, .layer = TD_MAX_LAYER_GAGREGROG, .string = TD_NULL, .unicode_string = TD_NULL}

#define BOOT__TD_ACTION_GAGREGROG FN__TD_ACTION_GAGREGROG(reset_keyboard)

#define ACTION_TAP_DANCE_GAGREGROG(user_dance_handler)                                       \
    {                                                                                        \
        .fn        = {NULL, (void *)user_dance_handler, (void *)user_dance_handler},         \
        .user_data = (void *)&((td_data_gagregrog_t){.pressed = false, .has_begun = false}), \
    }

#define TD_ARGS_GAGREGROG tap_dance_state_t *state, void *user_data
#define HANDLE_TAP_DANCE_GAGREGROG(actions) handle_tap_dance_gagregrog(actions, ARRAY_SIZE(actions), state, user_data)
