/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
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

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_WSPR LGUI(KC_P)
#define KC_WSNX LGUI(KC_N)

#define KJ_SPC  LT(LY1,KC_SPC)
#define KJ_TAB  LT(LY2,KC_TAB)
#define KJ_ENT  LT(LYN,KC_ENT)
#define KJ_BSPC LT(LY2,KC_BSPC)
#define KJ_QUOT ALT_T(KC_QUOT)

#define CS_HOME RCS_T(KC_HOME)
#define CA_END LCA_T(KC_END)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYB] = LAYOUT_ansi_69(
        TD(T_UX), KC_1,   KC_2,     KC_3,   KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_LPRN,  KC_RPRN, QK_LEAD,           KC_MPLY,
        TD(T_GE), KC_Q,   KC_W,     KC_E,   KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC, GUI_T(KC_MINS),    MS_WHLU,
        TD(T_CE), KC_A,   KC_S,     KC_D,   KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KJ_QUOT, TD(T_CP),          MS_WHLD,
        TD(T_LS), KC_Z,   KC_X,     KC_C,   KC_V,    KC_B,              KC_AMPR, KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH, TD(T_RS), MS_UP,
        CS_HOME,  CA_END, TG(LYF),          KJ_SPC,  KJ_TAB,            KJ_ENT,  KJ_BSPC,          TD(T_MB),                    MS_LEFT,  MS_DOWN, MS_RGHT),

    [LYG] = LAYOUT_ansi_69(
        KC_ESC,  _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        KC_TAB,  _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        KC_SCLN, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        KC_LSFT, _______,  _______,  _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______, KC_UP,
        KC_LCTL, KC_LALT,  KC_LGUI,           _______,          KC_BSPC,  _______,          _______,           _______,            KC_LEFT, KC_DOWN, KC_RGHT),

    [LYN] = LAYOUT_ansi_69(
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, KC_ASTR, KC_PLUS, KC_7,    KC_8,    KC_9,    _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, KC_SLSH, KC_MINS, KC_4,    KC_5,    KC_6,              _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, KC_DOT,  KC_0,    KC_1,    KC_2,    KC_3,              _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______, _______,          _______,          KC_BSPC,  _______,          _______,           _______,            _______, _______, _______),

    [LYF] = LAYOUT_ansi_69(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,  _______,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          KC_F11,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______,          KC_F12,
        _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______, _______,          _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [LY1] = LAYOUT_ansi_69(
        QK_BOOT, _______,  _______,  _______, _______, _______, _______,     _______, _______, _______, _______,   _______,  _______, _______,          RM_TOGG,
        _______, LAMBDA,   _______,  _______, _______, _______, RCS(KC_TAB), KC_WBAK, C(KC_L), KC_WFWD, C(KC_TAB), KC_WSPR,  KC_WSNX, KC_TASK,          _______,
        _______, EQ_NEQ,   PER_AST,  DOL_CIR, AT_HASH, INC_DEC,              KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,   C(KC_L),  C(KC_F), _______,          _______,
        _______, LTE_GTE,  _______,  _______, _______, _______,              _______, _______, _______, _______,   _______,  _______, _______, _______,
        _______, _______,  _______,           _______,          _______,     _______,          _______,            _______,           _______, _______, _______),

    [LY2] = LAYOUT_ansi_69(
        QK_BOOT, KC_BRID, KC_BRIU, KC_TASK,  KC_FLXP, _______, KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,   _______,          RM_TOGG,
        RM_TOGG, KC_ASTR, RM_SPDU, RM_HUEU,  RM_SATU, RM_VALU, KC_F17,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,  _______,          _______,
        _______, KC_SLSH, KC_MINS, RM_PREV, RM_TOGG, RM_NEXT,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F5,   KC_F12,   _______,          _______,
        _______, KC_DOT,  RM_SPDD, RM_HUED,  RM_SATD, RM_VALD, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F6,   _______,           _______,
        DM_PLY1, DM_REC1, _______,           _______,          T_RSTRT, _______,          _______,          _______,            _______, _______, _______)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LYB] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LYG] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LY1]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU)},
    [LY2]   = {ENCODER_CCW_CW(RM_VALD, RM_VALU)}
};
#endif // ENCODER_MAP_ENABLE
