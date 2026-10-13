#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include <stdbool.h>
#include "KohlJary.h"
#include "tapdance_actions.h"
#include "key_overrides.h"

enum alt_keycodes {
    //Massdrop ALT declared keycodes
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR, //USB Toggle Automatic GCR control
    DBG_TOG,  //DEBUG Toggle On / Off
    DBG_MTRX, //DEBUG Toggle Matrix Prints
    DBG_KBD,  //DEBUG Toggle Keyboard Prints
    DBG_MOU,  //DEBUG Toggle Mouse Prints
    MD_BOOT,  //Restart into bootloader after hold timeout
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Base layer
    [LYB] = LAYOUT_65_ansi_blocker(
        TD(T_UX), KC_1,         KC_2,         KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,            KC_LBRC,         KC_RBRC, KC_TAB,          TD(T_LY),
        TD(T_GE), KC_Q,         KC_W,         KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,            KC_BSPC,         KC_AMPR, GUI_T(KC_MINS),  KC_MPLY,
        TD(T_CE), LT(LY1,KC_A), LT(LY2,KC_S), KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   LT(LY2,KC_SCLN), LT(LY1,KC_QUOT), ALT_T(KC_ENT),            TD(T_CP),
        TD(T_LS), KC_Z,         KC_X,         KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,         TD(T_RS),                 KC_UP,           OSM(MOD_LCTL|MOD_LSFT),
        MO(LYS),  TD(T_CP),     KC_HOME,                  KC_SPC,                            KC_END,          TD(T_MB),        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //Gaming/compatibility layer (Keys are explicitly declared to ensure compatibility)
    [LYG] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC, TG(LYG),
        KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, _______,
        KC_LCTL, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,  _______,
        KC_LSFT, KC_Z,    KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,      KC_RSFT,     KC_UP,   KC_VOLD,
        KC_GRV,  KC_LGUI, KC_LALT,                _______,                     TG(LYG), _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //F-key number key layout
    [LYF] = LAYOUT_65_ansi_blocker(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    //Modifier layer 1 (macros, symbols, vim-key arrows, keyboard mouse commands)
    [LY1] = LAYOUT_65_ansi_blocker(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_LPRN, KC_RPRN,  _______,  _______,
        _______, _______, _______, _______, _______, _______, RCS(KC_TAB), KC_WBAK, C(KC_L), KC_WFWD, C(KC_TAB), _______, _______,  _______,  _______,
        _______, EQ_NEQ,  PER_AST, DOL_CIR, AT_HASH, INC_DEC, KC_LEFT,     KC_DOWN, KC_UP,   KC_RGHT, KC_EQL,    S(KC_MINS),        _______,  _______,
        _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,     _______, _______, _______, _______,            _______,  MS_UP,  _______,
        _______, _______, _______,                            KC_TAB,                                 _______,   _______, MS_LEFT,  MS_DOWN,  MS_RGHT
    ),
    //Modifier layer 2 (F-keys, numbers, media controls)
    [LY2] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, KC_F13,  KC_F17,  KC_F18, KC_F19, KC_F20, KC_F21,   KC_F22,        KC_F23,  _______, _______,
        _______, KC_ASTR, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_F7,   KC_F8,  KC_F9,  KC_F10, KC_F11,   _______,       KC_F24,  _______, _______,
        _______, KC_SLSH, KC_MINS, KC_4,    KC_5,    KC_6,    KC_F13,  KC_F14, KC_F15, KC_F16, KC_F5,    ALT_T(KC_F12),          _______, _______,
        _______, KC_DOT,  KC_0,    KC_1,    KC_2,    KC_3,    KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F6,                   _______, KC_PGUP, _______,
        _______, _______, _______,                            KC_ENT,                          _______,  _______,       KC_HOME, KC_END,  KC_PGDN
    ),
    //Settings layer (RGB settings, reflashing commands, debug utilities)
    [LYS] = LAYOUT(
        DBG_TOG,  RM_PREV, RM_NEXT,  RM_VALD, RM_VALU, RM_SPDD, RM_SPDU, RM_HUED, RM_HUEU, RM_SATD, RM_SATU,  RGB_M_B, RM_TOGG, MK_FLSH, DM_REC1,
        U_T_AUTO, _______,  _______,  _______, _______, _______, _______, AND_OR,  EQ_NEQ,  LAMBDA,  _______,  _______, _______, NK_TOGG, DM_PLY1,
        U_T_AGCR, _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,  _______,          MD_BOOT, DM_REC2,
        _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______, TD(T_DR),          _______, KC_PGUP, DM_PLY2,
        _______,  _______,  TG(LYG),                             _______,                            _______,  _______, KC_HOME, KC_PGDN, KC_END
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______
    ),
    */
};

/* bool get_retro_tapping(uint15_t keycode, keyrecord_t *record) { */
/*   switch(keycode) { */
/*     case MT(MOD_LCTL, KC_ESC): */
/*       return true; */
/*     case MT(MOD_RSFT, KC_TAB): */
/*       return true; */
/*     default: */
/*       return false; */
/*   } */
/* } */

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

uint8_t mod_state;
uint8_t oneshot_mod_state;
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RM_TOGG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
