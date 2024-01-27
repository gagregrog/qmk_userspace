# Secrets

Provide a list of 5 secret strings that can be mapped to keycodes and used in tapdances.

## Setup

Add to your `rules.mk`:

```make
INCLUDE_SECRETS = yes
```

Create a `secrets.h` file which consists of:

```c
static const char * secrets[] = {
  "real_secret_1",
  "real_secret_2",
  "real_secret_3",
  "real_secret_4",
  "real_secret_5"
};
```

Secrets files have cascading precedence. You can create a `secrets.h` file in the following locations. The file with the highest specificity will be used (ie keymap > keyboard > userfile).

1. `:keymap/secrets.h`
2. `keyboards/:keyboard/secrets.h`
3. `users/gagregrog/secrets/secrets.h`


You can disable secrets at compile time by passing `-e NO_SECRETS=yes`. For example:

```bash
qmk flash handwired/twokey -e NO_SECRETS=yes
```

### Git Exclusion 

To prevent `git` from seeing, or committing the secret files, you can exclude them. Create a `.gitignore` file in the same folder as your `secrets.h` and add:

```c
secrets.h
```

## How it works

It will expose 5 custom keycodes, `KC_SECRET_1` through `KC_SECRET_5`. You can use these as normal keycodes which will be handled by `process_record_user` automatically in the `gagregrog` userspace. It will also expose a `send_secret` function which you can use like `send_secret(KC_SECRET_1)`. Secrets can also be used in the Tap Dance Utils from this user space.

## Credits

Based off of [Drashna's work](/users/drashna/keyrecords/secrets.md).
