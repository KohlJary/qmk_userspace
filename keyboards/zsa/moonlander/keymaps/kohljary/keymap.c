/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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
#include "version.h"
#include "KohlJary.h"
#include "tapdance_actions.h"
#include "key_overrides.h"

/*
 * Keycode Reference
 * =================
 *
 * G(KC_GRV): Toggle Quake terminal
 * G(KC_1-KC_0): Switch workspaces/applications
 * G(KC_EQL): Fullscreen active window
 * G(KC_P): Previous workspace
 * G(KC_N): Next workspace
 * G(KC_TAB): Workspace back and forth
 * G(KC_SPC): Open application search
 * G(KC_ENT): Open new terminal window
 *
 * TD(T_LS): Single tap; shift next character, Hold; shift modifier, Double tap; home, Double tap + hold; Ctrl+Alt+Shift
 * TD(T_RS): Single tap; caps word toggle, Hold; shift modifier, Double tap; end, Double tap + hold; Ctrl+Alt
 *
 * TD(T_CE): Single tap; Escape, Hold: Ctrl, Double tap; QMK leader, Double tap hold; Ctrl+Shift
 * TD(T_AQ): Single tap; ', Hold; Alt, Double tap; F24 (vim leader), Double tap hold; Alt+Shift
 * TD(T_GE): Single tap; =, Hold; Gui, Double tap hold; Gui+Shift
 * TD(T_UX): Single tap; Quake terminal, Hold; Ctrl+C, Double tap; Fullscreen, Double tap hold; T_RSTRT behavior
 *
 * TD(T_CP): Single tap; Copy, Hold; Paste, Double tap; Cut, Double tap hold; Screen capture tool
 * TD(T_MB): Single tap/hold; M1, Double tap; M2, Double tap hold; M3
 * TD(T_LY): 1; TG(L_M), 2; TG(L_F), 3; TG(L_G), 4; Ctrl+Alt+Del
 *
 * EQ_NEQ: ==, hold for !=
 * INC_DEC: ++, hold for --
 * LTE_GTE: <=, shifted for >=
 * LAMBDA: =>, shifted for ->
 * AT_HASH: tap for @, long press for #
 * DOL_CIR: tap for $, long press for ^
 * PER_AST: tap for %, long press for *
 * T_RSTRT: press for Ctrl+C, release for Up, Enter (restart terminal process)
 * UC_STRT: start unicode character input
 *
 * KC_AMPR: Shift for |, Ctrl for !
 * KC_DOT: Shift for !
 * KC_COMM: Shift for ~
 *
 * KC_BSPC: Shift for Delete
 * MS_WHLU: Shift for wheel down
 *
 * KC_MINS: Ctrl for +
 * KC_SLSH: Ctrl for \
 * KC_QUOT/TD(T_AQ): Ctrl for `
 *
 * KC_LBRC/KC_RBRC: Ctrl for (), Ctrl+Shift for <>
 *
 * KC_MPLY: Ctrl for next track, Ctrl+Shift for prev track, Alt for vol up, Alt+Shift for vol down, Ctrl+Alt for mute
 * QK_LEAD: Shift for F24 (vim leader key)
 * QK_REP: Shift for alternate repeat key
 */

#define KC_TASK LCA(KC_DEL)
#define KC_FLXP LGUI(KC_E)
#define KC_WSPR LGUI(KC_P)
#define KC_WSBF LGUI(KC_TAB)
#define KC_WSNX LGUI(KC_N)
#define KC_WSNM LGUI(KC_DOT)
#define KC_MAX  LGUI(KC_EQL)
#define KC_TERM LGUI(KC_DOT)
#define KC_PROG LGUI(KC_SPC)

// Web Browser Tab Previous
#define KC_WBTP RCS(KC_TAB)
// Web Browser Tab Next
#define KC_WBTN C(KC_TAB)
// Web Browser Tab Open
#define KC_OPTB RCS(KC_T)

#define KJ_SPC  LT(LY2, KC_SPC)
#define KJ_TAB  TD(T_1T)
#define KJ_ENT  TD(T_2E)
#define KJ_BSPC LT(LY1,KC_BSPC)
#define KJ_NVLD TD(T_LD)
#define KJ_SCLN LT(LYN,KC_SCLN)
#define KJ_SLSH LT(LYN,KC_SLSH)
#define KJ_MINS TD(T_GM)
#define KJ_COPY TD(T_CP)
#define KJ_GEQL TD(T_GE)
#define KJ_CESC TD(T_CE)
#define KJ_LSFT TD(T_LS)
#define KJ_RSFT TD(T_RS)
#define KJ_UTIL TD(T_UX)
#define KJ_ALTQ TD(T_AQ)
#define KJ_TERM TD(T_TM)
#define KJ_CDIR TD(T_DR)
#define KJ_MERC UM(MERCURY)

#define KJ_TTY1 LCA(KC_F1)
#define KJ_TTY2 LCA(KC_F2)
#define KJ_TTY3 LCA(KC_F3)
#define KJ_TTY4 LCA(KC_F4)
#define KJ_TTY5 LCA(KC_F5)
#define KJ_TTY6 LCA(KC_F6)
#define KJ_TTY7 LCA(KC_F7)
#define KJ_TTY8 LCA(KC_F8)
#define KJ_TTY9 LCA(KC_F9)
#define KJ_TTY0 LCA(KC_F10)

// Vim binds
#define VIM_TOP S(KC_H)
#define VIM_MID S(KC_M)
#define VIM_BOT S(KC_L)

#define MOD_AS  MOD_LALT | MOD_LSFT
#define MOD_CS  MOD_LCTL | MOD_LSFT
#define OSHT_CS OSM(MOD_CS)
#define OSHT_AS OSM(MOD_AS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LYB] = LAYOUT_moonlander(
        KJ_COPY, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   TL_LOWR,          TL_UPPR, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KJ_UTIL,
        KJ_GEQL, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_AT,            KC_AMPR, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KJ_MINS,
        KJ_CESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_F24,           KC_F23,  KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KJ_ALTQ,
        KJ_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                              KC_N,   KC_M,    KC_COMM, KC_DOT,  KJ_SLSH, KJ_RSFT,
        OSHT_CS, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT,         MS_BTN1,          MS_BTN2,         KC_HOME, KC_PGDN, KC_PGUP, KC_END,  OSHT_AS,
                                            KJ_SPC,  KJ_TAB, QK_LEAD,          KJ_NVLD, KJ_ENT, KJ_BSPC
    ),

    [LYG] = LAYOUT_moonlander(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,             _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,  _______, _______, _______, _______, _______, KC_Y,             _______, _______, _______, _______, _______, _______, _______,
        KC_SCLN, _______, _______, _______, _______, _______, KC_H,             _______, _______, _______, _______, _______, _______, _______,
        KC_LSFT, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        KC_LCTL, KC_7,    KC_8,    KC_9,    KC_0,             KC_GRV,           _______,          _______, _______, _______, _______, _______,
                                            KC_SPC,  KC_BSPC, KC_EQL,           _______, _______, _______
    ),

    [LYV] = LAYOUT_moonlander(
        _______, KC_PROG, KC_WSPR, KC_WSBF, KC_WSNX, KC_TERM, _______,          _______, KC_WBAK, KC_WBTP, KC_OPTB, KC_WBTN, KC_WFWD, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),

    [LYF] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,           KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),

    [LYN] = LAYOUT_moonlander(
        _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, KC_DOT,  KC_PAST, KC_PSLS, KC_PPLS, KC_PMNS,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),

    [LY1] = LAYOUT_moonlander(
        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,          _______, KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    QK_BOOT,
        _______, KC_LABK, KC_RABK, LAMBDA,  KC_LPRN, KC_RPRN, KC_PGUP,          DM_PLY1, KC_LBRC, KC_RBRC, KC_WFWD, KC_WBAK,  KC_WBTP, _______,
        _______, KC_HOME, AND_OR,  LTE_GTE, EQ_NEQ,  KC_END,  KC_PGDN,          DM_REC1, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_DLR,  _______,
        _______, KJ_TERM, INC_DEC, EQ_NULL, KC_NULL, KC_TRUE,                            KC_WBTN, KC_LCBR, KC_RCBR, KJ_TERM,  KJ_CDIR, _______,
        _______, _______, _______, _______, _______,          _______,          _______,          KJ_TTY5, KJ_TTY6, KJ_TTY7,  KJ_TTY8, _______,
                                            _______, _______, _______,          _______, _______, _______
    ),

    [LY2] = LAYOUT_moonlander(
        QK_BOOT, RM_SPDU, RM_HUEU, RM_SATU, RM_VALU, RM_PREV, RM_NEXT,         RM_TOGG, KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_PROG, _______,
        _______, KC_GRV,  KC_PIPE, KC_ASTR, KC_HASH, KJ_MERC,  MS_WHLU,         DM_PLY2, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______,
        _______, KC_CIRC, KC_AMPR, KC_PERC, KC_AT,   KC_DLR,   MS_WHLD,         DM_REC2, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F5,   ALT_T(KC_F12),
        _______, KC_F21,  KC_F22,  KC_F23,  KC_F24,  LAMBDA,                             KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F6,   _______,
        _______, UC_PREV, UC_NEXT, _______, _______,           _______,         _______,          KJ_TTY1, KJ_TTY2, KJ_TTY3, KJ_TTY4, _______,
                                            _______, _______,  _______,         _______, _______, _______
    ),

    [LY3] = LAYOUT_moonlander(
        _______, _______, _______, _______,  _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, DM_REC2, DM_REC1, RM_HUEU,  RM_SATU, RM_VALU, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, DM_PLY2, DM_PLY1, RM_PREV, RM_TOGG, RM_NEXT, _______,          _______, _______, _______, _______, _______, _______, _______,
        _______, RM_SPDD, RM_SPDU, RM_HUED,  RM_SATD, RM_VALD,                            _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,  _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                             _______, _______, _______,          _______, _______, _______
    ),
};

// LED flags per key, read by rgb_matrix_indicators_advanced_user: LED_FLAG_MODIFIER (1, outer column),
// LED_FLAG_UNDERGLOW (2, number row, inner column, upper thumb keys), LED_FLAG_KEYLIGHT (4, alphas) and
// LED_FLAG_INDICATOR (8, lower thumb keys). Upstream marks every key as 1 or 4.
static const uint8_t kj_led_flags[] = {
    2, 2, 2, 2, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4,
    2, 2, 2,
    8, 8, 8, 8,

    2, 2, 2, 2, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4, 2,
    1, 4, 4, 4,
    2, 2, 2,
    8, 8, 8, 8
};
_Static_assert(sizeof(kj_led_flags) == RGB_MATRIX_LED_COUNT, "one flag per LED");

void keyboard_post_init_user(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        g_led_config.flags[i] = kj_led_flags[i];
    }
    /* layer_on(LYV); */
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t mod_state = get_mods();
    uint8_t oneshot_mod_state = get_oneshot_mods();
    bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
    bool ctl_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_CTRL);
    bool alt_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_ALT);
    bool gui_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_GUI);

    bool layersOn[7] = {
        layer_state_is(LYF),
        layer_state_is(LYV),
        layer_state_is(LYG),
        layer_state_is(LYN),
        layer_state_is(LY1),
        layer_state_is(LY2),
        layer_state_is(LY3)
    };
    uint8_t rainbow[7][3] = {
        {RGB_RED},
        {RGB_ORANGE},
        {RGB_YELLOW},
        {RGB_GREEN},
        {RGB_BLUE},
        {RGB_PURPLE},
        {RGB_WHITE}
    };
    uint8_t modColor = (layersOn[0] == true) ? 0 : (layersOn[1] == true) ? 5 : 7;
    uint8_t alphaColor = (layersOn[2] == true) ? 0 : (layersOn[4] == true) ? 4 : (layersOn[5] == true) ? 2 :  (layersOn[6] == true) ? 3 : 7;

    for (uint8_t i = led_min; i < led_max; i++) {
        if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
            rgb_matrix_set_color(i, 0, 0, 0);
            continue;
        }

        if (g_led_config.flags[i] & LED_FLAG_MODIFIER) {
            if (modColor != 7) {
                rgb_matrix_set_color(i, rainbow[modColor][0], rainbow[modColor][1], rainbow[modColor][2]);
                continue;
            }
            continue;
        }

        if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
            if (alphaColor != 7) {
                rgb_matrix_set_color(i, rainbow[alphaColor][0], rainbow[alphaColor][1], rainbow[alphaColor][2]);
                continue;
            }
            continue;
        }

        if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
            if (alt_mod && ctl_mod && gui_mod) {
                rgb_matrix_set_color(i, RGB_WHITE);
                continue;
            } else if (alt_mod && ctl_mod) {
                rgb_matrix_set_color(i, RGB_GREEN);
                continue;
            } else if (alt_mod && gui_mod) {
                rgb_matrix_set_color(i, RGB_PURPLE);
                continue;
            } else if (ctl_mod && gui_mod) {
                rgb_matrix_set_color(i, RGB_ORANGE);
                continue;
            } else if (alt_mod) {
                rgb_matrix_set_color(i, RGB_BLUE);
                continue;
            } else if (ctl_mod) {
                rgb_matrix_set_color(i, RGB_YELLOW);
                continue;
            } else if (gui_mod) {
                rgb_matrix_set_color(i, RGB_RED);
                continue;
            }
            continue;
        }

        if (g_led_config.flags[i] & LED_FLAG_INDICATOR) {
            if (is_caps_word_on()) {
                rgb_matrix_set_color(i, RGB_RED);
                continue;
            } else if (shift_mod) {
                rgb_matrix_set_color(i, RGB_ORANGE);
                continue;
            } else if (leader_sequence_active()) {
                rgb_matrix_set_color(i, RGB_PURPLE);
                continue;
            } else if (layersOn[3]) {
                rgb_matrix_set_color(i, RGB_GREEN);
                continue;
            }
            continue;
        }
    }
    return false;
}

void housekeeping_task_user(void) {
    if (!is_transport_connected()) {
        layer_on(LYG);
        layer_off(LYV);
    } else {
        layer_off(LYG);
    }
}
