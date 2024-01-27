# these rules are automatically included when the firmware is built with a gagregrog keymap

SRC += gagregrog.c

# Always Features

CAPS_WORD_ENABLE = yes

# Utilities to add automatically when certain features are enabled

ifeq ($(strip $(OLED_ENABLE)), yes)
    SRC += $(USER_PATH)/oled/oled_util.c
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    SRC += $(USER_PATH)/led/led_util.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += $(USER_PATH)/tap_dance/tap_dance_utils.c
endif

# Custom Features that can be added

ifeq ($(strip $(POINTING_DEVICE_INVERT_SCROLL)), yes)
    OPT_DEFS += -DPOINTING_DEVICE_INVERT_SCROLL
endif

ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_spi)
    OPT_DEFS += -DIS_CIRQUE
else ifeq ($(strip $(POINTING_DEVICE_DRIVER)), cirque_pinnacle_i2c)
    OPT_DEFS += -DIS_CIRQUE
endif

ifeq ($(strip $(TRACKPOINT_ENABLE)), yes)
    OPT_DEFS += -DTRACKPOINT_ENABLE
    ifneq ($(strip $(PS2_MOUSE_ENABLE)), yes)
        PS2_MOUSE_ENABLE = yes
    endif
    ifneq ($(strip $(PS2_ENABLE)), yes)
        PS2_ENABLE = yes
    endif
    ifneq ($(strip $(PS2_DRIVER)), usart)
        PS2_DRIVER = usart
    endif
endif

ifeq ($(strip $(MOUSE_TURBO_CLICK)), yes)
    OPT_DEFS += -DMOUSE_TURBO_CLICK
    # https://getreuer.info/posts/keyboards/mouse-turbo-click/index.html
    SRC += $(USER_PATH)/mouse_turbo_click/mouse_turbo_click.c
    ifneq ($(strip $(DEFERRED_EXEC_ENABLE)), yes)
        DEFERRED_EXEC_ENABLE = yes
    endif
    ifneq ($(strip $(MOUSEKEY_ENABLE)), yes)
        MOUSEKEY_ENABLE = yes
    endif
endif

ifeq ($(strip $(USE_DEFAULT_TD_ACTIONS)), yes)
    OPT_DEFS += -DUSE_DEFAULT_TD_ACTIONS
endif


# support secrets cascading in order of precedence from:
#   - keyboards/:keyboard/:keymap/secrets.h
#   - keyboards/:keyboard/secrets.h
#   - users/gagregrog/secrets/secrets.h
ifeq ($(strip $(INCLUDE_SECRETS)), yes)
    ifneq ($(strip $(NO_SECRETS)), yes)
        OPT_DEFS += -DINCLUDE_SECRETS
        SRC += $(USER_PATH)/secrets/secrets.c
        ifneq ("$(wildcard $(KEYMAP_PATH)/secrets.h)","")
            OPT_DEFS += -DSECRETS_PATH=\"$(KEYMAP_PATH)/secrets.h\"
        else ifneq ("$(wildcard keyboards/$(KEYBOARD)/secrets.h)","")
            OPT_DEFS += -DSECRETS_PATH=\"keyboards/$(KEYBOARD)/secrets.h\"
        else
            OPT_DEFS += -DSECRETS_PATH=\"$(USER_PATH)/secrets/secrets.h\"
        endif
    endif
endif

ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
