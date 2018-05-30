#include QMK_KEYBOARD_H

#define TAPPING_TERM 115 //time in microseconds a key is counted as pressed

//Macros for space cadet
#define PROG_LP M(0) // ( when tapped, shift when held
#define PROG_RP M(1) // ) when tapped, shift when held
#define PROG_LC M(2) // { when tapped, shift when held
#define PROG_RC M(3) // } when tapped, shift when held

/* 0: Main layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │▒▒▒▒▒│BKSPC│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │▒▒▒▒▒│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│CAPSL│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │NUHS │ENTER│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LSHFT│  \  │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │▒▒▒▒▒│RSHFT│▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│LCTRL│L_GUI│L_ALT│█████│█████│█████│ SPC │█████│█████│█████│R_ALT│ APP │ FN  │RCTRL│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: ANSI qwerty */
    LAYOUT(KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC, \
           KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_NO,            \
           KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT ,          \
           PROG_LP, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          PROG_RP, KC_NO,   \
           KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                    KC_RALT, KC_RGUI,  MO(1),  KC_RCTL),

/* 1: Fn layer
UG = Underglow = RGB Backlighting
BL = Backlighting = In-Switch LED
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│GRAVE│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │▒▒▒▒▒│     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │ Up  │     │     │     │     │     │PGUP │PGDWN│PRTSC│SCLCK│PAUSE│▒▒▒▒▒│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │Left │Down │Right│     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │UGTOG│UGMOD│UGHUI│UGHUD│UGSAI│UGSAD│     │BLDEC│BLTOG│BLINC│▒▒▒▒▒│     │▒▒▒▒▒│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │     │     │█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
*/
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS,          \
        KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,          \
        PROG_LC, KC_TRNS, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT,          PROG_RC, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                   KC_TRNS, KC_VOLD, KC_TRNS, KC_VOLU),
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

static uint16_t timer; //timer for counting key press times in macros

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch(id) {
		case 0:
			if (record->event.pressed) {
				timer = timer_read();
				register_code (KC_LSFT);
			} else {
				if (timer_elapsed (timer) < TAPPING_TERM) {
					register_code (KC_8);
					unregister_code (KC_8);
				}
				unregister_code (KC_LSFT);
			}
			break;
		case 1:
			if (record->event.pressed) {
				timer = timer_read();
				register_code (KC_RSFT);
			} else {
				if (timer_elapsed (timer) < TAPPING_TERM) {
					register_code (KC_9);
					unregister_code (KC_9);
				}
				unregister_code (KC_RSFT);
			}
			break;
		case 2:
			if (record->event.pressed) {
				timer = timer_read();
				register_code (KC_LSFT);
			} else {
				if (timer_elapsed (timer) < TAPPING_TERM) {
					unregister_code (KC_LSFT);
					register_code (KC_LGUI);
					register_code (KC_8);
					unregister_code (KC_8);
					unregister_code (KC_LGUI);
				}
				unregister_code (KC_LSFT);
			}
			break;
		case 3:
			if (record->event.pressed) {
				timer = timer_read();
				register_code (KC_RSFT);
			} else {
				if (timer_elapsed (timer) < TAPPING_TERM) {
					unregister_code (KC_RSFT);
					register_code (KC_LGUI);
					register_code (KC_9);
					unregister_code (KC_9);
					unregister_code (KC_LGUI);
				}
				unregister_code (KC_RSFT);
			}
			break;
	}
	return MACRO_NONE;
};
