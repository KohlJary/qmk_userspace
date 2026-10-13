/* Copyright 2022 @ Keychron (https://www.keychron.com)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include <stdbool.h>
#include "KohlJary.h"
#include "tapdance_actions.h"
#include "key_overrides.h"

// clang-format off

/* enum layers{ */
/*     MAC_BASE, */
/*     WIN_BASE, */
/*     _FN1, */
/*     _FN2, */
/*     _FN3 */
/* }; */

#define KC_TASK LCA(KC_DEL)
#define KC_FLXP LGUI(KC_E)
#define KC_WSPR LGUI(KC_P)
#define KC_WSBF LGUI(KC_TAB)
#define KC_WSNX LGUI(KC_N)
#define KC_MAX  LGUI(KC_EQL)
#define KC_TERM LGUI(KC_ENT)
#define KC_PROG LGUI(KC_SPC)

#define KJ_SPC  LT(LY1,KC_SPC)
#define KJ_TAB  LT(LY2,KC_TAB)
#define KJ_ENT  LT(LY1,KC_ENT)
#define KJ_BSPC LT(LY2,KC_BSPC)
#define KJ_QUOT ALT_T(KC_QUOT)

#define CS_HOME RCS_T(KC_HOME)
#define CA_END LCA_T(KC_END)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYB] = LAYOUT_ansi_89(
        KC_MPLY,  QK_BOOT,  KC_WSPR, KC_WSBF, KC_WSNX,  G(KC_DOT), KC_PROG, KC_TERM,  KC_MAX,  LAMBDA,   AT_HASH,  DOL_CIR,  PER_AST,  LAMBDA,   KC_TASK,           T_RSTRT,
        _______,  TD(T_UX), KC_1,    KC_2,    KC_3,     KC_4,      KC_5,    KC_6,     KC_7,    KC_8,     KC_9,     KC_0,     KC_AT,    KC_AMPR,  KC_CAPS,           TD(T_CP),
        _______,  TD(T_GE), KC_Q,    KC_W,    KC_E,     KC_R,      KC_T,    KC_Y,     KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  GUI_T(KC_MINS),    MS_WHLU,
        _______,  TD(T_CE), KC_A,    KC_S,    KC_D,     KC_F,      KC_G,    KC_H,     KC_J,    KC_K,     KC_L,     KC_SCLN,  KJ_QUOT,            QK_LEAD,           MS_WHLD,
        _______,  TD(T_LS), KC_Z,    KC_X,    KC_C,     KC_V,      KC_B,    KJ_ENT,   KC_N,    KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  TD(T_RS),          MS_UP,
        _______,  CS_HOME,  CA_END,           KC_ENT,   KJ_SPC,    KJ_TAB,            KJ_BSPC,           TD(T_MB),                               MS_LEFT, MS_DOWN,  MS_RGHT),

    [LYG] = LAYOUT_ansi_89(
        _______,  KC_CAPS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_ENT,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  MO(LY1),            KC_LALT,  KC_SPC,   KC_SCLN,                       KC_BSPC,            KC_RALT,                      KC_LEFT,  KC_DOWN,  KC_RGHT),

    [LYN] = LAYOUT_ansi_89(
        _______,    _______,  _______, _______, _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  KC_PPLS, KC_7,    KC_8,    KC_9,    KC_0,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  KC_PMNS, KC_4,    KC_5,    KC_6,    KC_PSLS,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  KC_DOT,  KC_1,    KC_2,    KC_3,    KC_EQL,    _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,           _______, _______, _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,          _______, _______, _______,                       _______,            _______,                      _______,  _______,  _______),

    [LYF] = LAYOUT_ansi_89(
        _______,    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [LY1] = LAYOUT_ansi_89(
        RM_TOGG,  KC_CAPS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,   KC_F7,       KC_F8,    KC_F9,     KC_F10,  KC_F11,   KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______, _______,     _______,  _______,   _______, KC_DLR,   KC_PERC,  _______,            _______,
        _______,  _______,  AT_HASH,  KC_7,     KC_8,     KC_9,     KC_0,      KC_WBAK, RCS(KC_TAB), C(KC_T),  C(KC_TAB), KC_WFWD, KC_LPRN,  KC_RPRN,  RCS(KC_P),          _______,
        _______,  _______,  DOL_CIR,  KC_4,     KC_5,     KC_6,     LAMBDA,    KC_LEFT, KC_DOWN,     KC_UP,    KC_RGHT,   C(KC_T), C(KC_W),            _______,            _______,
        _______,  _______,  PER_AST,  KC_1,     KC_2,     KC_3,     LTE_GTE,   KC_HOME, KC_PGDN,     KC_PGUP,  KC_END,    MS_BTN1, MS_BTN2,  _______,            _______,
        _______,  _______,  _______,            _______,  _______,  _______,                         _______,             _______,                     _______,  _______,  _______),

    [LY2] = LAYOUT_ansi_89(
        RM_TOGG,  QK_BOOT,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,   RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  _______,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,   KC_F17,   KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F17,   GUI_T(KC_F18),      _______,
        _______,  _______,  RM_PREV, RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,   KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F5,    KC_F12,              _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F6,    _______,  _______,
        _______,  _______,  _______,            _______,  KC_ENT,   _______,                       _______,            _______,                       _______,  _______,  _______),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LYB] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LY1]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [LYG] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LY2]   = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif // ENCODER_MAP_ENABLE

#ifdef DIP_SWITCH_ENABLE
// The Mac/Win switch selects default layer 0 or 1 (upstream uses 0 or 2)
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 1 : 0));
        return false;
    }
    return true;
}
#endif
