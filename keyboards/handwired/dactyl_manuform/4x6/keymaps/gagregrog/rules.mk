# MCU name
MCU = atmega32u4

# use for right half (with trackpoint)
# Bootloader selection
# elite-c
BOOTLOADER = atmel-dfu

# use for left half (without trackpoint)
# Bootloader selection
# Pro Micro
# BOOTLOADER = caterina

TRACKPOINT_ENABLE = yes
POINTING_DEVICE_INVERT_SCROLL = yes

COMMAND_ENABLE = no
RGBLIGHT_ENABLE = yes
AUTO_SHIFT_ENABLE = no
USE_DEFAULT_TD_ACTIONS = no
LTO_ENABLE = yes
MOUSE_TURBO_CLICK = yes
