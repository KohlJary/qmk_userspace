/* Copyright 2022 @ Keychron (https://www.keychron.com)
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
#include "KohlJary.h"
#include "tapdance_actions.h"
#include "key_overrides.h"

#define KJ_PMNS GUI_T(KC_PMNS)
#define KJ_PEQL CTL_T(KC_PEQL)
#define KJ_PDOT ALT_T(KC_PDOT)

// Web Browser Tab Previous
#define KC_WBTP RCS(KC_TAB)
// Web Browser Tab Next
#define KC_WBTN C(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYB] = LAYOUT_numpad_6x4(
        KJ_PEQL, KC_PPLS, TG(LYN),  LT(LY1, KC_ESC),
        KJ_PDOT, KC_PMNS, TG(LYV),  TG(LYF),
        KC_P1,   KC_P4,   KC_P7,
        KC_P2,   KC_P5,   KC_P8,    KC_TAB,
        KC_P3,   KC_P6,   KC_P9,
        SFT_T(KC_PENT),   KC_P0,    KC_BSPC),

    [LYG] = LAYOUT_numpad_6x4(
        KC_LCTL, KC_G, KC_Y,   _______,
        KC_LSFT, KC_F, KC_T,   KC_TAB,
        KC_Z,    KC_A, KC_Q,
        KC_X,    KC_S, KC_W,   KC_1,
        KC_C,    KC_D, KC_E,
        KC_SPC,        KC_R,   KC_2),

    [LYN] = LAYOUT_numpad_6x4(
        KC_F5,    C(KC_T), _______, TO(LYB),
        KC_WBTP,  C(KC_W), C(KC_L), C(KC_F),
        KC_WBAK,  MS_LEFT, MS_WHLU,
        KC_WFWD,  MS_DOWN, MS_UP, KC_WBAK,
        KC_WBTN,  MS_RGHT, MS_WHLD,
        MS_BTN1,           MS_BTN2, KC_WFWD),

    [LYV] = LAYOUT_numpad_6x4(
        G(KC_DOT), G(KC_SPC), _______,    TO(LYB),
        G(KC_A),   G(KC_H),   _______,    _______,
        G(KC_S),   G(KC_J),   G(KC_P),
        G(KC_D),   G(KC_K),   G(KC_SCLN), KC_F5,
        G(KC_F),   G(KC_L),   G(KC_N),
        KC_SPC,               _______,    KC_DEL),

    [LYF] = LAYOUT_numpad_6x4(
        KC_WBTP, KC_MPRV, KC_MPLY,   TO(LYB),
        KC_WBTN, KC_MNXT, KC_MSTP,   KC_MUTE,
        G(KC_1), G(KC_4), G(KC_7),
        G(KC_2), G(KC_5), G(KC_8),   G(KC_P),
        G(KC_3), G(KC_6), G(KC_9),
        G(KC_SPC),        G(KC_DOT), G(KC_N)),

    [LY1] = LAYOUT_numpad_6x4(
        _______,  _______, TG(LY2), _______,
        _______,  _______, TG(LYG), KC_NUM,
        KC_F1,    KC_F4,   KC_F7,
        KC_F2,    KC_F5,   KC_F8,   KC_F11,
        KC_F3,    KC_F6,   KC_F9,
        QK_BOOT,           KC_F10,  KC_F12),

    [LY2] = LAYOUT_numpad_6x4(
        _______, _______,  _______,  TO(LYB),
        _______, _______,  _______,  _______,
        RM_VALD, RM_PREV, RM_VALU,
        RM_HUED, RM_TOGG,  RM_HUEU,  _______,
        RM_SATD, RM_NEXT,  RM_SATU,
        RM_SPDD,           RM_SPDU,  _______),

    [LY3] = LAYOUT_numpad_6x4(
        _______,    _______, _______,   _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,             _______,   _______)//,

    /* [_RESERVED2] = LAYOUT_numpad_6x4( */
    /*     _______,    _______, _______,   _______, */
    /*     _______,    _______, _______,   _______, */
    /*     _______,    _______, _______, */
    /*     _______,    _______, _______,   _______, */
    /*     _______,    _______, _______, */
    /*     _______,             _______,   _______) */
};
