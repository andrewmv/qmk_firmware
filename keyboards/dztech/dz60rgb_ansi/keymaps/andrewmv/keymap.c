#include QMK_KEYBOARD_H

const int FKEY_INDICATOR[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
const int FKEY_IND_COUNT = 12;
const int ARROW_INDICATOR[] = {31, 32, 33, 34};
const int ARROW_IND_COUNT = 4;
const int PAGE_INDICATOR[] = {0, 17, 23, 24, 39, 46};
const int PAGE_IND_COUNT = 6;
const int AUX_INDICATOR[] = {1, 2, 3};
const int AUX_IND_COUNT = 3;
const int MEDIA_INDICATOR[] = {11, 10, 9, 7, 6, 43, 44, 57};
const int MEDIA_IND_COUNT = 9;
const int RGBCTL_INDICATOR[] = {27, 25, 23, 21, 19, 17, 38, 36, 34, 32};
const int RGBCTL_IND_COUNT = 10;

const int GESC_INDICATOR[] = {13};
const int GRV_INDICATOR[] = {14};
const int RESET_INDICATOR[] = {14};

// Key Overrides
const key_override_t esc_key_override = ko_make_basic(MOD_MASK_ALT, KC_GESC, A(KC_GRV));
const key_override_t **key_overrides = (const key_override_t *[]) {
    &esc_key_override,
    NULL
};

#define FKEY_COLOR     RGB_MAGENTA
#define ESC_COLOR      RGB_RED
#define GRV_COLOR      RGB_ORANGE
#define ARROW_COLOR    RGB_GREEN
#define PAGE_COLOR     RGB_YELLOW
#define AUX_COLOR      RGB_WHITE
#define MEDIA_COLOR    RGB_BLUE
#define RESET_COLOR    RGB_RED
#define RGBCTL_COLOR   RGB_PURPLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

/*** RGB STUFF ***/

void rgb_matrix_indicate_function(uint8_t led_min, uint8_t led_max, const int keyset[], const int keycount, int r, int g, int b) {
    for (int i = 0; i < keycount; i++) {
        if ((keyset[i] >= led_min) & (keyset[i] <= led_max)) {
            rgb_matrix_set_color(keyset[i], r, g, b);
        }
    }
}

// Highlight function changes in layers.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is(1)) {    // Navigation Layer
        rgb_matrix_indicate_function(led_min, led_max, FKEY_INDICATOR, FKEY_IND_COUNT, FKEY_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, PAGE_INDICATOR, PAGE_IND_COUNT, PAGE_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, ARROW_INDICATOR, ARROW_IND_COUNT, ARROW_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, GESC_INDICATOR, 1, GRV_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, GRV_INDICATOR, 1, GRV_COLOR);
    } else if (layer_state_is(2)) { // Media and Meta layer
        rgb_matrix_indicate_function(led_min, led_max, MEDIA_INDICATOR, MEDIA_IND_COUNT, MEDIA_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, RGBCTL_INDICATOR, RGBCTL_IND_COUNT, RGBCTL_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, AUX_INDICATOR, AUX_IND_COUNT, AUX_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, RESET_INDICATOR, 1, RESET_COLOR);
        rgb_matrix_indicate_function(led_min, led_max, GESC_INDICATOR, 1, GRV_COLOR);
    }
}

// 0: BASE LAYER
// 1: NAV LAYER
// 2: MEDIA LAYER
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        LT(1, KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   MO(2),   KC_RCTL
    ),
    [1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, KC_END,  KC_INS,  _______, _______, _______, _______,  _______,KC_PGUP, _______, _______, KC_GRV,
        _______, KC_HOME, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, KC_PGDN, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [2] = LAYOUT_60_ansi(
        KC_GRV,  _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_BRID, KC_BRIU, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,
        RGB_TOG, _______, RGB_HUI, _______, RGB_SAI, _______, RGB_VAI, _______, RGB_SPI, _______, RGB_MOD, _______, _______, RESET,
        _______, _______, RGB_HUD, _______, RGB_SAD, _______, RGB_VAD, _______, RGB_SPD, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, _______,          _______,
        _______, _______, _______,                            KC_MPLY,                            _______, _______, _______, _______
    )
};
