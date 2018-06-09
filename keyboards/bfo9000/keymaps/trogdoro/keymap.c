//
// Keymap for my 8x5 "sideways hands" BFO-9000 keyboard.
//
// "Sideways hands" means your hands come in from the side. This is
// because it hangs around your neck, and rests on your chest as
// you type.
//
#include QMK_KEYBOARD_H
#include "keymap_steno.h"

#define ____ KC_TRNS

enum the_layers {
  _DVORAK,
  _PUNCTUATION,
  _PLOVER,
  _LEFTPALM,
  _QWERTY
};

// Without this, QMK won't enable steno.
void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_DVORAK] = LAYOUT( \
    LT(_LEFTPALM, KC_DOT),           LALT(KC_TAB),  KC_A,   ALT_T(KC_TAB), KC_L,  KC_S,  KC_Z,  KC_F5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    KC_MS_WH_DOWN,  KC_Q,    KC_O,   KC_BSPC,       KC_R,  KC_N,  KC_V,  KC_5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    KC_BTN1,        KC_J,    KC_E,   KC_ENT,        KC_C,  KC_T,  KC_W,  TG(_PLOVER), ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    CTL_T(KC_SPC),  KC_K,    KC_U,   KC_P,          KC_G,  KC_H,  KC_M,  LT(_PUNCTUATION, KC_DOT), ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    GUI_T(KC_ESC),  KC_X,    KC_I,   KC_Y,          KC_F,  KC_D,  KC_B,  KC_LSFT, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
),

[_PUNCTUATION] = LAYOUT( \
    ____,          KC_LBRC,   KC_1,  KC_QUOTE,           KC_0,    KC_0,    ____,    KC_F5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____,          KC_RBRC,   KC_2,  KC_COMMA,           KC_9,    KC_9,    KC_V,    KC_5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____,          KC_MINUS,  KC_3,  KC_DOT,             KC_GRV,  KC_8,    KC_W,    KC_T, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    CTL_T(KC_SPC), KC_EQUAL,  KC_4,  KC_SLASH,           KC_7,    KC_7,    KC_SPC,  ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    KC_LGUI,       KC_SCLN,   KC_5,  KC_BSLS,            KC_6,    KC_6,    KC_B,    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
),

[_PLOVER] = LAYOUT( \
    ____,    STN_S2,  STN_S1, STN_N1,       STN_NA, STN_TR,  STN_SR,    ____,           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____,    STN_KL,  STN_TL, STN_N2,       STN_N9, STN_LR,  STN_GR,    ____,           ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____,    STN_WL,  STN_PL, STN_N3,       STN_N8, STN_PR,  STN_BR,    TG(_PLOVER),    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    STN_O,   STN_RL,  STN_HL, STN_N4,       STN_N7, STN_FR,  STN_RR,    STN_E,          ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    STN_A,   STN_ST2, STN_ST1, STN_N5,      STN_N6, STN_ST3,  STN_ST4,  STN_U,          ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
),

[_LEFTPALM] = LAYOUT( \
    ____,           LALT(KC_TAB),  KC_A,   ALT_T(KC_TAB), KC_L,  KC_S,  KC_Z,  KC_F5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    KC_MS_WH_DOWN,  KC_Q,    KC_O,   KC_BSPC,       RESET,  KC_N,  KC_V,  KC_5, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    KC_BTN1,        KC_J,    KC_E,   KC_ENT,        KC_C,  KC_T,  KC_W,  TG(_PLOVER), ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    CTL_T(KC_SPC),  KC_K,    KC_U,   KC_P,          KC_G,  KC_H,  KC_M,  LT(_PUNCTUATION, KC_DOT), ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    GUI_T(KC_ESC),  KC_X,    KC_I,   KC_Y,          KC_F,  KC_D,  KC_B,  KC_LSFT, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, \
    ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
)

};

