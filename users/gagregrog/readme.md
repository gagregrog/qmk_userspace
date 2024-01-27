Copyright 2023 Gary Gregory Rogers gagregrog@gmail.com @gagregrog

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

# Gagregrog Userspace

Check out each markdown file in this userspace to see what features are available and always-active.

## How to Use

In your keymap add `#include "gagregrog.h"` in order to use custom keycodes etc.

If you want to use these features in a keymap that is named something other than `gagregrog` then you must add `USER_NAME := gagregrog` to the `rules.mk` inside your keymap folder.

## Features

### Tap Dances

Check out [tap_dance.md](./tap_dance/tap_dance.md) to see all of the great features that are automatically exposed when you enable tap dances.

### Mouse Turbo Click

Add `MOUSE_TURBO_CLICK = yes` to your `rules.mk` to enable turbo click! Use `MS_TURBO` keycode to rapid fire mouse click. This will automatically enable `MOUSEKEY_ENABLE` and `DEFERRED_EXEC_ENABLE` features. This feature was taken from https://getreuer.info/posts/keyboards/mouse-turbo-click/index.html.
