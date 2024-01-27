#include "quantum.h"
#include "oled_driver.h"

#pragma once

#ifdef OLED_SHOW_DOGS
void render_dogs(void);
#endif // OLED_SHOW_DOGS

void render_layer_text(void);
