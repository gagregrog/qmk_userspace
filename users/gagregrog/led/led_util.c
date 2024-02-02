#include "gagregrog.h"

#ifdef RGBLIGHT_ENABLE
  #ifdef BASIC_BREATH
    const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {60, 40, 20, 10};
  #endif // BASIC_BREATH
#endif // RGBLIGHT_ENABLE

#if defined(DEBUG_RGB_MATRIX)
void debug_rgb_matrix(uint16_t keycode, bool pressed) {
  // only log the events on press to avoid a duplicate log
  if (!pressed) {
    return;
  }

  uint8_t mode = rgb_matrix_get_mode();
  HSV hsv = rgb_matrix_get_hsv();
  char name[40];
  uint8_t normalizedMode = mode;

  // if we have changed the RGB mode, then rgb_matrix_get_mode() returns the
  // mode that we are switching away from, so add 1 to get the new mode
  if (keycode == RGB_MOD) {
    normalizedMode += 1;

    // if we've reached the last mode, loop back to the beginning
    if (normalizedMode == RGB_MATRIX_EFFECT_MAX) {
      normalizedMode = 1;
    }
  }

  switch (normalizedMode)
  {
#   ifdef ENABLE_RGB_MATRIX_NONE
    case RGB_MATRIX_NONE:
      strcpy(name, "RGB_MATRIX_NONE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_COLOR
    case RGB_MATRIX_SOLID_COLOR:     // Static single hue, no speed support
      strcpy(name, "RGB_MATRIX_SOLID_COLOR");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
    case RGB_MATRIX_ALPHAS_MODS:         // Static dual hue, speed is hue for secondary hue
      strcpy(name, "RGB_MATRIX_ALPHAS_MODS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    case RGB_MATRIX_GRADIENT_UP_DOWN:    // Static gradient top to bottom, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    case RGB_MATRIX_GRADIENT_LEFT_RIGHT:    // Static gradient left to right, speed controls how much gradient changes
      strcpy(name, "RGB_MATRIX_GRADIENT_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BREATHING
    case RGB_MATRIX_BREATHING:           // Single hue brightness cycling animation
      strcpy(name, "RGB_MATRIX_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SAT
    case RGB_MATRIX_BAND_SAT:        // Single hue band fading saturation scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_VAL
    case RGB_MATRIX_BAND_VAL:        // Single hue band fading brightness scrolling left to right
      strcpy(name, "RGB_MATRIX_BAND_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    case RGB_MATRIX_BAND_PINWHEEL_SAT:   // Single hue 3 blade spinning pinwheel fades saturation
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    case RGB_MATRIX_BAND_PINWHEEL_VAL:   // Single hue 3 blade spinning pinwheel fades brightness
      strcpy(name, "RGB_MATRIX_BAND_PINWHEEL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    case RGB_MATRIX_BAND_SPIRAL_SAT:     // Single hue spinning spiral fades saturation
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_SAT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    case RGB_MATRIX_BAND_SPIRAL_VAL:     // Single hue spinning spiral fades brightness
      strcpy(name, "RGB_MATRIX_BAND_SPIRAL_VAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
    case RGB_MATRIX_CYCLE_ALL:           // Full keyboard solid hue cycling through full gradient
      strcpy(name, "RGB_MATRIX_CYCLE_ALL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    case RGB_MATRIX_CYCLE_LEFT_RIGHT:    // Full gradient scrolling left to right
      strcpy(name, "RGB_MATRIX_CYCLE_LEFT_RIGHT");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    case RGB_MATRIX_CYCLE_UP_DOWN:       // Full gradient scrolling top to bottom
      strcpy(name, "RGB_MATRIX_CYCLE_UP_DOWN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    case RGB_MATRIX_CYCLE_OUT_IN:        // Full gradient scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    case RGB_MATRIX_CYCLE_OUT_IN_DUAL:   // Full dual gradients scrolling out to in
      strcpy(name, "RGB_MATRIX_CYCLE_OUT_IN_DUAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:  // Full gradient Chevron shapped scrolling left to right
      strcpy(name, "RGB_MATRIX_RAINBOW_MOVING_CHEVRON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    case RGB_MATRIX_CYCLE_PINWHEEL:      // Full gradient spinning pinwheel around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_PINWHEEL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    case RGB_MATRIX_CYCLE_SPIRAL:        // Full gradient spinning spiral around center of keyboard
      strcpy(name, "RGB_MATRIX_CYCLE_SPIRAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
    case RGB_MATRIX_DUAL_BEACON:         // Full gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_DUAL_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    case RGB_MATRIX_RAINBOW_BEACON:      // Full tighter gradient spinning around center of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_BEACON");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    case RGB_MATRIX_RAINBOW_PINWHEELS:   // Full dual gradients spinning two halfs of keyboard
      strcpy(name, "RGB_MATRIX_RAINBOW_PINWHEELS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_RAINDROPS
    case RGB_MATRIX_RAINDROPS:           // Randomly changes a single key's hue
      strcpy(name, "RGB_MATRIX_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    case RGB_MATRIX_JELLYBEAN_RAINDROPS: // Randomly changes a single key's hue and saturation
      strcpy(name, "RGB_MATRIX_JELLYBEAN_RAINDROPS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
    case RGB_MATRIX_HUE_BREATHING:       // Hue shifts up a slight ammount at the same time, then shifts back
      strcpy(name, "RGB_MATRIX_HUE_BREATHING");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
    case RGB_MATRIX_HUE_PENDULUM:        // Hue shifts up a slight ammount in a wave to the right, then back to the left
      strcpy(name, "RGB_MATRIX_HUE_PENDULUM");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_HUE_WAVE
    case RGB_MATRIX_HUE_WAVE:            // Hue shifts up a slight ammount and then back down in a wave to the right
      strcpy(name, "RGB_MATRIX_HUE_WAVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    case RGB_MATRIX_PIXEL_FRACTAL:       // Single hue fractal filled keys pulsing horizontally out to edges
      strcpy(name, "RGB_MATRIX_PIXEL_FRACTAL");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_FLOW
    case RGB_MATRIX_PIXEL_FLOW:          // Pulsing RGB flow along LED wiring with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_FLOW");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
    case RGB_MATRIX_PIXEL_RAIN:          // Randomly light keys with random hues
      strcpy(name, "RGB_MATRIX_PIXEL_RAIN");
      break;
#   endif
#   if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
    case RGB_MATRIX_TYPING_HEATMAP:      // How hot is your WPM!
      strcpy(name, "RGB_MATRIX_TYPING_HEATMAP");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    case RGB_MATRIX_DIGITAL_RAIN:        // That famous computer simulation
      strcpy(name, "RGB_MATRIX_DIGITAL_RAIN");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:   // Pulses keys hit to hue & value then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_SIMPLE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    case RGB_MATRIX_SOLID_REACTIVE:      // Static single hue, pulses keys hit to shifted hue then fades to current hue
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    case RGB_MATRIX_SOLID_REACTIVE_WIDE:        // Hue & value pulse near a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_WIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:   // Hue & value pulse near multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    case RGB_MATRIX_SOLID_REACTIVE_CROSS:       // Hue & value pulse the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_CROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:  // Hue & value pulse the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTICROSS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    case RGB_MATRIX_SOLID_REACTIVE_NEXUS:       // Hue & value pulse away on the same column and row of a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_NEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:  // Hue & value pulse away on the same column and row of multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SPLASH
    case RGB_MATRIX_SPLASH:              // Full gradient & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_MULTISPLASH
    case RGB_MATRIX_MULTISPLASH:         // Full gradient & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_MULTISPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_SPLASH
    case RGB_MATRIX_SOLID_SPLASH:        // Hue & value pulse away from a single key hit then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_SPLASH");
      break;
#   endif
#   ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    case RGB_MATRIX_SOLID_MULTISPLASH:   // Hue & value pulse away from multiple key hits then fades value out
      strcpy(name, "RGB_MATRIX_SOLID_MULTISPLASH");
      break;
#   endif
    case RGB_MATRIX_EFFECT_MAX:
      strcpy(name, "RGB_MATRIX_EFFECT_MAX");
      break;
    default:
      strcpy(name, "UNKNOWN");
      break;
  }

  xprintf("%i. %s - HSV{%i, %i, %i}\n", mode, name, hsv.h, hsv.s, hsv.v);
}
#endif
