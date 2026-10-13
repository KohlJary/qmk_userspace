#include QMK_KEYBOARD_H

#pragma once

enum TD_KEYCODES{
  T_1B, //Hold: TL_LOWR (L_1), Tap: Backspace
  T_1T, //Hold: TG(L_1), Tap: Tab, Double Tap: Shift+Tab
  T_2E, //Hold: TL_UPPR (L_2), Tap: Enter
  T_2S, //Hold: TL_UPPR (L_2), Tap: Space
  T_AQ, //Hold: alt, Double hold: alt+Num, 1: quote, Double Hold: Alt+Shift, 2: F24
  T_CB, //Hold: Closed curly, Tap: Closed paran, Double Tap: Closed brace, Double Hold: Closed angle brack
  T_CE, //Hold: Control, 1: Escape, 2: QMK Leader, Double Hold: Control+Alt
  T_CP, //Hold: Paste, 1: Copy, 2: Cut
  T_CS, //Hold: Control + Shift, Double Hold: LY2, 1: @, 2: &
  T_DR, //1: cur dir, 2: up dir
  T_GE, //Hold: GUI, 1: =, 2:==, Double Hold: !=
  T_GM, //Hold: GUI, Double holde: GUI+Num, 1: =, 2:==, Double Hold: !=
  T_IN, //1: --, 2: ++
  T_LS, //Hold: Left Shift, Double Hold: Ctrl+Shift, 1: Open par/bra, 2: Close par/bra
  T_LY, //1: TG(L_M), 2: TG(L_F), 3: TG(L_G), 4: Ctrl+Alt+Del
  T_MB, //Tap/Hold: M1, Double Tap: M2, Double Tap Hold: M3
  T_NE, //1: Enter, 2: Toggle num layer, Hold: Num layer momentary, Double Hold: Fn layermomentary
  T_NM, //1: Oneshot Num, 2: Num Lock
  T_OB, //Hold: Open curly, Tap: Open paran, Double Tap: Open brace, Double Hold: Open angle brack
  T_RS, //Hold: Right Shift, Double Hold: Ctrl+Shift, 1: Oneshot Shft, 2: Caps Word
  T_SC, //1: scln, 2: cln
  T_TM, //Terminal shortcuts 1: new tab, Hold: close tab, 2: rename tab
  T_UX, //Utility
  T_LD, //1: F24, 2: F23, H: LYN
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

extern enum TD_KEYCODES td_keycodes;

void dance_dir(tap_dance_state_t *state, void *user_data);
void dance_dec_inc(tap_dance_state_t *state, void *user_data);
void dance_num_tap(tap_dance_state_t *state, void *user_data);
void dance_num_release(tap_dance_state_t *state, void *user_data);
void dance_num_finished(tap_dance_state_t *state, void *user_data);
void dance_num_reset(tap_dance_state_t *state, void *user_data);
void dance_layer(tap_dance_state_t *state, void *user_data);

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

void altquote_finished(tap_dance_state_t *state, void *user_data);
void altquote_reset(tap_dance_state_t *state, void *user_data);

void leftshift_finished(tap_dance_state_t *state, void *user_data);
void leftshift_reset(tap_dance_state_t *state, void *user_data);

void rightshift_finished(tap_dance_state_t *state, void *user_data);
void rightshift_reset(tap_dance_state_t *state, void *user_data);

void ctrlesc_finished(tap_dance_state_t *state, void *user_data);
void ctrlesc_reset(tap_dance_state_t *state, void *user_data);

void ctrlshift_finished(tap_dance_state_t *state, void *user_data);
void ctrlshift_reset(tap_dance_state_t *state, void *user_data);

void copypaste_finished(tap_dance_state_t *state, void *user_data);
void copypaste_reset(tap_dance_state_t *state, void *user_data);

void openbrace_finished(tap_dance_state_t *state, void *user_data);
void openbrace_reset(tap_dance_state_t *state, void *user_data);

void closebrace_finished(tap_dance_state_t *state, void *user_data);
void closebrace_reset(tap_dance_state_t *state, void *user_data);

void guieq_finished(tap_dance_state_t *state, void *user_data);
void guieq_reset(tap_dance_state_t *state, void *user_data);

void guimin_finished(tap_dance_state_t *state, void *user_data);
void guimin_reset(tap_dance_state_t *state, void *user_data);

void utility_finished(tap_dance_state_t *state, void *user_data);
void utility_reset(tap_dance_state_t *state, void *user_data);

void terminal_finished(tap_dance_state_t *state, void *user_data);
void terminal_reset(tap_dance_state_t *state, void *user_data);

void lead_finished(tap_dance_state_t *state, void *user_data);
void lead_reset(tap_dance_state_t *state, void *user_data);

void mouse_button_finished(tap_dance_state_t *state, void *user_data);
void mouse_button_reset(tap_dance_state_t *state, void *user_data);

void nument_finished(tap_dance_state_t *state, void *user_data);
void nument_reset(tap_dance_state_t *state, void *user_data);

void ly1tab_finished(tap_dance_state_t *state, void *user_data);
void ly1tab_reset(tap_dance_state_t *state, void *user_data);

void ly1bspc_finished(tap_dance_state_t *state, void *user_data);
void ly1bspc_reset(tap_dance_state_t *state, void *user_data);

void ly2ent_finished(tap_dance_state_t *state, void *user_data);
void ly2ent_reset(tap_dance_state_t *state, void *user_data);

void ly2spc_finished(tap_dance_state_t *state, void *user_data);
void ly2spc_reset(tap_dance_state_t *state, void *user_data);
