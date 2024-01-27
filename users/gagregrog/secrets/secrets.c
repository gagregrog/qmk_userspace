#include QMK_KEYBOARD_H
#include "gagregrog.h"

#define MACRO_TIMER 5

/*
To include secrets, add the rule "INCLUDE_SECRETS = yes" to rules.mk and create users/gagregrog/secrets/secrets.h as follows:

static const char * secrets[] = {
  "real_secret_1",
  "real_secret_2",
  "real_secret_3",
  "real_secret_4",
  "real_secret_5"
};

*/

#if (__has_include(SECRETS_PATH) && !defined(NO_SECRETS))
#include SECRETS_PATH
#else
static const char * const secrets[] = {
  "default_secret_1",
  "default_secret_2",
  "default_secret_3",
  "default_secret_4",
  "default_secret_5"
};
#endif

#pragma message "\n\n\n[WARN] Including Secrets in build!\n\n"

void send_secret(uint16_t keycode) {
  clear_mods();
  clear_oneshot_mods();
  send_string_with_delay(secrets[keycode - KC_SECRET_1], MACRO_TIMER);
};

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_SECRET_1 ... KC_SECRET_5: // Secrets!  Externally defined strings, not stored in repo
      if (record->event.pressed) {
        send_secret(keycode);
      }
      return false;
      break;
  }
  return true;
}

