//
// Keymap for my 8x5 "sideways hands" BFO-9000 keyboard.
//
// "Sideways hands" means your hands come in from the side. This is
// because it hangs around your neck, and rests on your chest as
// you type.
//
// The "Seamless Stenography and Qwerty" feature is something you
// might be interested in copying and pasting into your keymap. If
// so, copy the following variables, and the blocks of code below
// that use them:
//

//
// "Seamless Stenography and Qwerty" feature. These vars (and the
// code below that uses them) let you type in steno and qwerty
// seamlessly at the same time (without having to type a key to
// toggle between them, which would otherwise be necessary). It
// does steno via Plover.
//
// See readme_seamless_steno_and_qwerty.md for more about this
// feature.
//
#include QMK_KEYBOARD_H
static uint16_t steno_key_pressed_timer;
static uint16_t steno_temporarily_disabled_timer;
static uint16_t steno_grace_period_timer;
static bool key_not_yet_released;
static bool steno_was_combo;
static bool exit_steno_flag;
static keyrecord_t *exit_steno_record;

#include "keymap_steno.h"
#include <print.h>

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

//
// "Steno Thumb Modifiers" feature.
// These vars (and the code below that uses them) make the thumb
// keys (control, command, etc) work just like when in qwerty,
// when you are in steno.
//
// The keycode of the key that might be used as a modifier, if
// the user holds it down and uses it like one:
static uint16_t steno_modifier_candidate;
// Whether the modifier was actually sent:
static bool steno_modifier_on;
static bool steno_modifier_combo_typed;

// Utility function > Given a record, return the keycode pressed.
uint16_t lookup_keycode(keyrecord_t *record) {
  keypos_t key = record->event.key;
  uint8_t layer = layer_switch_get_layer(key);
  update_source_layers_cache(key, layer);
  return keymap_key_to_keycode(layer, key);
}

void matrix_scan_user(void) {

  // "Steno Thumb Modifiers" feature.
  // If they've been holding the modifier down for a bit, send the keycode.
  // Only if _candidate and not _on
  if(steno_modifier_candidate && !steno_modifier_on && !steno_was_combo) {
    // Only if timer past .5s
    if (timer_elapsed(steno_key_pressed_timer) > 120) {
      steno_modifier_on = true;
      register_code(steno_modifier_candidate);
    }
  }


  // "Seamless Stenography and Qwerty" feature.
  // Steno is temporarily disabled, so turn it back on
  if(steno_temporarily_disabled_timer && ! key_not_yet_released) {

    // If timer passed pause, enable steno layer
    if(timer_elapsed(steno_temporarily_disabled_timer) > 300) {
      layer_on(_PLOVER);
      // Turn timer off
      steno_temporarily_disabled_timer = 0;
    }
  }

}




bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {
    // Key was pressed, so remember.
    key_not_yet_released = true;
  } else {
    // key was released, so remember.
    key_not_yet_released = false;

    // Steno already temporarily disabled, so disable it a little longer
    if(steno_temporarily_disabled_timer)
      // Extend timer
      steno_temporarily_disabled_timer = timer_read();
  }

  return true;   // Let QMK send the enter press/release events

}


bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed) {

  // This function is called after a key has been processed, but
  // before any decision about whether or not to send a chord.

  int8_t pressed_after = pressed;
  pressed_after += record->event.pressed ? 1 : -1;

  // xprintf("\n    KL: keycode: %u, row: %u, column: %u, event.pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
  // xprintf("--- pressed: %u, pressed_after: %u\n\n", pressed, pressed_after);


  // "Steno Thumb Modifiers" feature.
  if(pressed == 0) {

    steno_modifier_combo_typed = false;

    // First key pressed, so remember it as a potential modifier key
    switch (keycode) {
      case STN_O:
        steno_modifier_candidate = KC_LCTRL;
        break;
      case STN_A:
        steno_modifier_candidate = KC_LGUI;
        break;
      case STN_U:
        steno_modifier_candidate = KC_LSFT;
        break;
      case STN_N1:
        steno_modifier_candidate = KC_LALT;
        break;
      case STN_E:
        // todo set to special code
        print("E - shit > how to use punctuation layer?");
        steno_modifier_candidate = 0;
        break;
      default:
        steno_modifier_candidate = 0;
    }

  } else if(pressed >= 1 && steno_modifier_on && record->event.pressed) {

    // Pressed key when modifier held down
    layer_off(_PLOVER);

    uint16_t qwerty_keycode = lookup_keycode(record);

    register_code(qwerty_keycode);
    unregister_code(qwerty_keycode);
    layer_on(_PLOVER);

    // Just to force cache reloading
    lookup_keycode(record);

    steno_modifier_combo_typed = true;

    return true;
  }


  // "Seamless Stenography and Qwerty" feature.
  if(pressed == 0) {
    // First key pressed in steno combo
    steno_key_pressed_timer = timer_read();
    steno_was_combo = false;

  } else if(pressed_after > 1) {
    // Combo, so never go to qwerty
    steno_was_combo = true;

  } else if(pressed_after == 0 && ! steno_was_combo) {
    // Last key pressed in combo

    if (timer_elapsed(steno_key_pressed_timer) > 150) {
      // slow
    } else {

      // They've typed steno really recently, so assume this isn't qwerty (even if it's a single key)
      if (timer_elapsed(steno_grace_period_timer) < 300) {
        // Just continue as normal steno
        return true;
      }

      // Typed quickly, so treat as qwerty
      exit_steno_flag = true;
      exit_steno_record = record;
    }
  }
  return true;
}

bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]) {

  // "Steno Thumb Modifiers" feature.
  // Stop holding down modifier, if holding it down

  // Only if _candidate and _on are set
  if(steno_modifier_on) {

    // unregister candidate keycode
    unregister_code(steno_modifier_candidate);
    steno_modifier_candidate = 0;
    steno_modifier_on = false;

    // Don't return false if > nothing was typed, and modifier wasn't held down very long, because we want to treat it like a single steno stroke
    if(! steno_modifier_combo_typed && timer_elapsed(steno_key_pressed_timer) < 500) {
      // fine
    } else {
      return false;
    }

  }

  // if just _candidate set > clear _candidate
  if(steno_modifier_candidate) {
    steno_modifier_candidate = 0;
  }

  // They typed a quick single key, so treat it and subsequent keys as qwerty, instead of sending steno chord
  if(exit_steno_flag) {

    // Special handling for certain keys
    if(exit_steno_record->event.key.row == 0 && exit_steno_record->event.key.col == 1) {
      // option tab
      SEND_STRING(SS_LALT("\t"));
      return false;
    }

    layer_off(_PLOVER);

    uint16_t keycode = lookup_keycode(exit_steno_record);

    register_code(keycode);
    unregister_code(keycode);

    exit_steno_flag = false;

    // Start timer that will turn steno back on in half a second
    steno_temporarily_disabled_timer = timer_read();

    return false;
  }


  // Steno stroke is finishing, so treat immediately following keystrokes as steno ( because some of them might be single keystrokes
  steno_grace_period_timer = timer_read();

  return true;
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

