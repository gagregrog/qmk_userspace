# Tap Dance

When Tap Dances are enabled, these utilities will be automatically included. These utils allow you to define key taps/hold behaviors for `KC_` keycodes, `KC_SECRET_`S, user-defined functions, strings to send, and layer moves/toggles.

## Configuration

In your `keymap.c`, create an enum to hold all of your tap dances. Then, for convenience, create defines for the new keycodes to use in your layout.

```c
enum tap_dance_keys {
  T_MY_DANCE,
};

#define TD_MY_DANCE     TD(T_MY_DANCE)
```

Next, create an array to hold your tap dance actions. Each even index (starting with index 0) will correspond to a tap action, and each odd index will correspond to a hold action. 

Hold actions for regular `KC_` keycodes will remain held until released and as such will continue to register keypresses with the host system. Taps, on the other hand, will only be sent once and cannot be held. 

`KC_SECRET_`s and strings will only be sent once. Functions will also only be called once. Each of these will happen when the tap dance first registers a tap/hold.

Layer actions will act as a layer toggle when mapped to a tap action, and will act as a momentary layer key while held when mapped to a hold action.

The array must not be sparse, but there is a helper if you want to skip items. Use the helper macros to define your functinoality.

For example:

```c
static void myFunc(void) {
  SEND_STRING("hello tap dances!\n");
  wait_ms(500);
  SEND_STRING("goodbye tap dances!");
};

static td_actions_gagregrog_t my_actions[] = {
  KEY__TD_ACTION_GAGREGROG(KC_1), // send 1 when tapped once
  FN__TD_ACTION_GAGREGROG(myFunc), // call the function myFunc when held
  NULL__TD_ACTION_GAGREGROG, // do nothing when double tapped
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_1), // send secret 1 when tapped once and then held
  BOOT__TD_ACTION_GAGREGROG, // put the keyboard into bootloader mode so you can flash new code to it when tapped 3 times
  LAYER__TD_ACTION_GAGREGROG(L2), // since this is a hold action, activate layer L2 while key is held after 2 taps
  LAYER__TD_ACTION_GAGREGROG(L3), // since this is a tap action, toggle layer L3 on or off, depending on its current state, after 4 taps
  STRING__TD_ACTION_GAGREGROG("have a nice day!") // send this nice message when tapped three times and then held
};
```

Next, create the function we will pass to the QMK tap dance macros. These will use some utilities that we expose.

```c
void handle_my_dance(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(my_actions);
}
```

Finally, the last step is to define the global `tap_dance_actions` array.

```c
tap_dance_action_t tap_dance_actions[] = {
  [T_MY_DANCE]  = ACTION_TAP_DANCE_GAGREGROG(handle_my_dance),
  // add as many tapdance configs as you want!
};
```

## Examples

### Basic

Let's create a basic tap dance with some macros, some secrets, a function, and a boot shortcut.

```c
// keymap.c
#include QMK_KEYBOARD_H
#include "gagregrog.h"

// we'll be defining two tap dance keys for our twokey keyboard
enum tap_dance_keys {
  T_L1_K1,
  T_L1_K2,
};
#define TD_L1_K1     TD(T_L1_K1)
#define TD_L1_K2     TD(T_L1_K2)

// example for the handwired/twokey key keyboard, but works similarly for other keyboards
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT_1x2(TD_L1_K1, TD_L1_K2)
};

// Setup for T_L1_K1
static td_actions_gagregrog_t actions_one[] = {
  KEY__TD_ACTION_GAGREGROG(LGUI(KC_C)),    // Send Copy when tapped
  KEY__TD_ACTION_GAGREGROG(LGUI(KC_V)),    // Send Paste when held
  NULL__TD_ACTION_GAGREGROG,               // do nothing when tapped twice
  BOOT__TD_ACTION_GAGREGROG                // reset the board for flashing when tapped then held
};
void handle_dance_one(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_one);
}

// - Setup for T_L1_K2
// this function will allow you to commit a selection in VS Code Source Control
void commit_selected(void) {
  tap_code16(LGUI(KC_K));
  wait_ms(50);
  tap_code16(LGUI(LALT(KC_S)));
};
static td_actions_gagregrog_t actions_two[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_1), // send the first secret when tapped
  FN__TD_ACTION_GAGREGROG(commit_selected) // call this function when held
};
void handle_dance_two(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_two);
}

tap_dance_action_t tap_dance_actions[] = {
  [T_L1_K1] = ACTION_TAP_DANCE_GAGREGROG(handle_dance_one),
  [T_L1_K2] = ACTION_TAP_DANCE_GAGREGROG(handle_dance_two),
};
```

### TD With Layers

With this next one let's use tap dances with layer switches.

```c
// keymap.c
#include QMK_KEYBOARD_H
#include "gagregrog.h"

enum layers {
  L1,
  L2,
  L3
};

// we'll be defining three tap dance keys for this layout
enum tap_dance_keys {
  T_L1_K1,
  T_L2_K2,
  T_L3_K2,
};
#define TD_L1_K1     TD(T_L1_K1)
#define TD_L2_K2     TD(T_L2_K2)
#define TD_L3_K2     TD(T_L3_K2)

// example for the handwired/twokey key keyboard, but applies similarly for other keyboards
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // first key is our first tap dance
  // we will be setting a hold action to move to layer 2 while the key is held
  // second key will activate layer 3
  [L1] = LAYOUT_1x2(TD_L1_K1, TG(L3)),
  
  // first key is transparent
  // since we will be using a momentary layer hold on key 1 in layer 1 to activate layer 2, we must define key 1 as transparent in layer 2
  // this ensures that the release of the key 1 (aka the deactivation of the layer 2) can be properly processed by layer 1
  // second key is our second tap dance
  [L2] = LAYOUT_1x2(KC_TRNS, TD_L2_K2),
  
  // no functionality mapped to the first key here
  // third tap dance mapped to the second key
  [L3] = LAYOUT_1x2(KC_NO,    TD_L3_K2)
};

// Setup for T_L1_K1
static td_actions_gagregrog_t actions_one[] = {
  KEY__TD_ACTION_GAGREGROG(KC_A),          // Send A when tapped
  KEY__TD_ACTION_GAGREGROG(KC_B),          // Send B when held
  LAYER__TD_ACTION_GAGREGROG(L3),          // activate layer 3 when tapped twice
  LAYER__TD_ACTION_GAGREGROG(L2),          // activate layer 2 while held when tapped and held
};
void handle_dance_one(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_one);
}

// - Setup for T_L2_K2
// layer 2 is only accessible if you tap and hold key 1 on layer 1
// that means these secrets are only accessible while that tap is active -- nice!
static td_actions_gagregrog_t actions_two[] = {
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_1), // send the first secret when tapped
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_2), // send the second secret when held
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_3), // send the third secret when double tapped
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_4), // send the fourth secret when tapped and then held
  KEY__TD_ACTION_GAGREGROG(KC_SECRET_5), // send the fifth secret when triple tapped
  STRING__TD_ACTION_GAGREGROG("Have a nice day!\n"), // send this message when tapped twice and then held
};
void handle_dance_two(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_two);
}

// - Setup for T_L3_K2
// layer 3 can be activated after pressing key 2 on layer 1,
// or by double tapping key 1 on layer 1
// you could use additional layer actions here to activate higher layers
static td_actions_gagregrog_t actions_three[] = {
  KEY__TD_ACTION_GAGREGROG(KC_1),        // send 1 when tapped
  NULL__TD_ACTION_GAGREGROG,             // do nothing when held
  LAYER__TD_ACTION_GAGREGROG(L3),        // deactivate this layer when double tapped
  NULL__TD_ACTION_GAGREGROG,             // do nothing when tapped and then held
  NULL__TD_ACTION_GAGREGROG,             // do nothing when triple tapped
  BOOT__TD_ACTION_GAGREGROG,             // enter bootloader when double tapped and held
};
void handle_dance_three(TD_ARGS_GAGREGROG) {
  HANDLE_TAP_DANCE_GAGREGROG(actions_three);
}

tap_dance_action_t tap_dance_actions[] = {
  [T_L1_K1] = ACTION_TAP_DANCE_GAGREGROG(handle_dance_one),
  [T_L2_K2] = ACTION_TAP_DANCE_GAGREGROG(handle_dance_two),
  [T_L3_K2] = ACTION_TAP_DANCE_GAGREGROG(handle_dance_three),
};
```
