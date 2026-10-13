#pragma once

// The tap dance table. QMK's keymap introspection sizes tap_dance_actions[] from the keymap.c translation
// unit, so it has to be defined there: include this from each keymap.c (once), not from other .c files.
// The handlers are declared in tapdance.h and defined in tapdance.c.

#include "tapdance.h"

tap_dance_action_t tap_dance_actions[] = {
  //T_1T Hold: TG(L_1), Tap: Tab, Double Tap: Shift+Tab
  [T_1B] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly1bspc_finished, ly1bspc_reset),
  //T_1T Hold: TG(L_1), Tap: Tab, Double Tap: Shift+Tab
  [T_1T] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly1tab_finished, ly1tab_reset),
  //T_2T Hold: TG(L_2), Tap: Tab, Double Tap: Shift+Tab
  [T_2E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly2ent_finished, ly2ent_reset),
  //T_2T Hold: TG(L_2), Tap: Tab, Double Tap: Shift+Tab
  [T_2S] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly2spc_finished, ly2spc_reset),
  //T_AQ Hold for Alt, tap for quote, double tap for F24, double hold for Alt+Shift
  [T_AQ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altquote_finished, altquote_reset),
  //T_CB Hold for close curly, single tap for close paren, double tap for close brace, double hold for close angle brack
  [T_CB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, closebrace_finished, closebrace_reset),
  //T_CE Hold for Control, single tap for escape, double tap for QMK leader, double tap and hold for Control+Alt
  [T_CE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlesc_finished, ctrlesc_reset),
  //T_CP Hold for paste, single tap for copy, double tap for cut
  [T_CP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, copypaste_finished, copypaste_reset),
  //T_CS Hold: Control + Shift, Double Hold: LY2, 1: @, 2: &
  [T_CS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlshift_finished, ctrlshift_reset),
  //T_DR Tap once for current directory, twice for up a directory
  [T_DR] = ACTION_TAP_DANCE_FN(dance_dir),
  //T_GE Hold for GUI, tap for =, double hold for !=
  [T_GE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guieq_finished, guieq_reset),
  //T_GE Hold for GUI, Double hold for GUI+Num, tap for =, double hold for !=
  [T_GM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, guimin_finished, guimin_reset),
  //T_IN Tap once for decrement, twice for increment
  [T_IN] = ACTION_TAP_DANCE_FN(dance_dec_inc),
  //T_LS Hold for shift, single tap for OSM shift, double tap for open paren
  [T_LS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, leftshift_finished, leftshift_reset),
  //T_LY 1: TG(L_M), 2: TG(L_F), 3: TG(L_G), 4: Ctrl+Alt+Del
  [T_LY] = ACTION_TAP_DANCE_FN(dance_layer),
  //T_MB Tap/Hold for M1, double tap for M2, double hold for M3
  [T_MB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mouse_button_finished, mouse_button_reset),
  //T_NE Tap once for enter, twice for num toggle. Hold for num momentary, Double hold for fn momentary.
  [T_NE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, nument_finished, nument_reset),
  //T_NM Tap once for oneshot num, twice for num toggle
  [T_NM] = ACTION_TAP_DANCE_FN_ADVANCED_WITH_RELEASE(NULL, dance_num_release, dance_num_finished, dance_num_reset),
  //T_OB Hold for open curly, single tap for open paren, double tap for open brace, double hold for open angle brack
  [T_OB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, openbrace_finished, openbrace_reset),
  //T_RS Hold for shift, single tap for Caps Word, double tap for close paren
  [T_RS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rightshift_finished, rightshift_reset),
  //T_SC Tap once for semicolon, twice for colon
  [T_SC] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
  //T_TM Hold for close tab, tap for new tab, double tap for rename tab
  [T_TM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, terminal_finished, utility_reset),
  //T_UX Hold for GUI, tap for =, double hold for !=
  [T_UX] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, utility_finished, utility_reset),
  //T_LD Tap once for nvim leader, twice for nvim local leader
  [T_LD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lead_finished, lead_reset),
};
