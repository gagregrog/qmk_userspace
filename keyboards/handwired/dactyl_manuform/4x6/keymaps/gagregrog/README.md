# Helpful Commands

## First Time Flash

First time Flashing you need to set the handedness of the board.

_Note:_ At this point in time running `make` from within `qmk_firmware` doesn't take external userspaces into account, so make sure to run this command from within the `qmk_userspace` repo.

### Pro Micro

Use the following to set in EEPROM:

```bash
make handwired/dactyl_manuform/4x6/pro_micro:gagregrog:avrdude-split-left

# or

make handwired/dactyl_manuform/4x6/pro_micro:gagregrog:avrdude-split-right
```

### Elite-C

Use the following to set in EEPROM:

```bash
make handwired/dactyl_manuform/4x6/elite_c:gagregrog:dfu-split-right

# or

make handwired/dactyl_manuform/4x6/elite_c:gagregrog:dfu-split-left
```

After the first time, to flash in the future use:

```bash
qmk flash -kb handwired/dactyl_manuform/4x6 -km gagregrog
```
