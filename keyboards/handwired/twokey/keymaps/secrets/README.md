# Two Key Keyboard

This is a cute little two key keyboard with all sorts of funky mod taps.

Add a file [secrets.h](./secrets.h) that looks like this:

```h
static const char * secrets[] = {
  "one",
  "two",
  "three",
  "four",
  "five",
  "six"
};
```

and replace each value with whatever secret you want to store.

You can then access the secrets as `KC_SECRET_NUM(N)` where `N` is the one-based index of the secret.

Map to a tap dance key by updating the tap dance definitions in [tap_dances.c](./tap_dances/tap_dances.c).

## Building

```bash
qmk compile -kb handwired/twokey -km secrets
```

### Flashing

```bash
qmk flash -kb handwired/twokey -km secrets
```

