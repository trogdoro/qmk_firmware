/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#endif

// Makes tap and hold keys work better for fast typers who don't want tapping term set above 500
#define PERMISSIVE_HOLD
// Makes it possible to do rolling combos (zx) with keys that convert to other keys on hold
// #define IGNORE_MOD_TAP_INTERRUPT
// Stores the layer a key press came from so the same layer is used when the key is released, regardless of which layers are enabled
#define PREVENT_STUCK_MODIFIERS

// Tap anyway, even after TAPPING_TERM, if there was no other key interruption between press and release
// (holding command for a long time wouldf still do esc)
// #define RETRO_TAPPING

#define MOUSEKEY_MAX_SPEED 3


// #define MATRIX_COLS 4

// Disable this and see if mouse and steno still work
// #define EXTRAKEY_ENABLE


