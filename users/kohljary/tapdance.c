#include QMK_KEYBOARD_H
#include "layers.h"
#include "os_detection.h"
#include "tapdance.h"
#include "keycodes.h"

// Create a global instance of the tapdance state type
static td_state_t altqt_td_state = TD_NONE;
static td_state_t ctrlesc_td_state = TD_NONE;
static td_state_t ctrlshift_td_state = TD_NONE;
static td_state_t guieq_td_state = TD_NONE;
static td_state_t guimin_td_state = TD_NONE;
static td_state_t lshift_td_state = TD_NONE;
static td_state_t lead_td_state = TD_NONE;
static td_state_t mb_td_state = TD_NONE;
static td_state_t ne_td_state = TD_NONE;
static td_state_t nm_td_state = TD_NONE;
static td_state_t rshift_td_state = TD_NONE;
static td_state_t td_state = TD_NONE;
static td_state_t tm_td_state = TD_NONE;
static td_state_t ux_td_state = TD_NONE;
static td_state_t ly1bspc_td_state = TD_NONE;
static td_state_t ly1tab_td_state = TD_NONE;
static td_state_t ly2ent_td_state = TD_NONE;
static td_state_t ly2spc_td_state = TD_NONE;
static bool nm_os_on = false;

uint8_t mod_state;
uint8_t oneshot_mod_state;

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
      if (!state->pressed) return TD_DOUBLE_TAP;
      else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Determine the tapdance state to return
td_state_t cur_dance_interrupt(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) {
      if (!state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
      else return TD_DOUBLE_HOLD;
    }
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

void dance_dir(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("./");
    } else if (state->count == 2) {
      SEND_STRING("../");
    } else if (state->count == 3) {
      SEND_STRING("~/");
    }
    reset_tap_dance(state);
}

void dance_dec_inc(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      SEND_STRING("--");
    } else if (state->count == 2) {
      SEND_STRING("++");
    }
    reset_tap_dance(state);
}

void dance_num_tap(tap_dance_state_t *state, void *user_data) {
    if(state->count == 1) {
        /* set_oneshot_layer(LYN, ONESHOT_START); */
    }
    else {
        layer_off(LYN);
        reset_oneshot_layer();
    }
}

void dance_num_release(tap_dance_state_t *state, void *user_data) {
    if(state->count == 1 && nm_os_on) {
        /* clear_oneshot_layer_state(ONESHOT_PRESSED); */
    }
}

void dance_num_finished(tap_dance_state_t *state, void *user_data) {
    /* if(!is_oneshot_layer_active()) { */
    /*     nm_os_on = false; */
    /* } */
    nm_td_state = cur_dance(state);
    switch (nm_td_state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            /* if (is_oneshot_layer_active()) { */
            /*     layer_off(get_oneshot_layer()); */
            /*     reset_oneshot_layer(); */
            /*     break; */
            /* } else { */
                if (IS_LAYER_ON(LYN)) {
                    /* clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); */
                    if (!nm_os_on) {
                        layer_off(LYN);
                        /* nm_os_on = true; */
                    } else {
                        nm_os_on = false;
                    }
                    break;
                } else {
                    nm_os_on = !nm_os_on;
                    if (!nm_os_on) {
                        nm_os_on = true;
                        set_oneshot_layer(LYN, ONESHOT_START);
                        break;
                    } else {
                        nm_os_on = false;
                    }
                }
            /* } */
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            layer_invert(LYN);
            break;
        default:
            break;
    }
}

void dance_num_reset(tap_dance_state_t *state, void *user_data) {
    switch (nm_td_state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
            if (nm_os_on) {
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            else {
                layer_off(LYN);
                reset_oneshot_layer();
            }
            break;
        default:
            break;
    }
    nm_td_state = TD_NONE;
}

void dance_layer(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
      layer_invert(LYV);
    } else if (state->count == 2) {
      layer_invert(LYF);
    } else if (state->count == 3) {
      layer_invert(LYG);
    }
    reset_tap_dance(state);
}

void altquote_finished(tap_dance_state_t *state, void *user_data) {
    altqt_td_state = cur_dance(state);
    switch (altqt_td_state) {
        case TD_SINGLE_TAP:
            register_code(KC_QUOT);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_F24);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            layer_on(LYN);
            break;
        default:
            break;
    }
}

void altquote_reset(tap_dance_state_t *state, void *user_data) {
    switch (altqt_td_state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_QUOT);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F24);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            layer_off(LYN);
            break;
        default:
            break;
    }
}

void ctrlesc_finished(tap_dance_state_t *state, void *user_data) {
    ctrlesc_td_state = cur_dance(state);
    switch (ctrlesc_td_state) {
        case TD_SINGLE_TAP:
            register_code(KC_ESC);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_F23);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void ctrlesc_reset(tap_dance_state_t *state, void *user_data) {
    switch (ctrlesc_td_state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_F23);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void leftshift_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
    lshift_td_state = cur_dance(state);
    switch (lshift_td_state) {
        case TD_SINGLE_TAP:
            if (is_caps_word_on()) {
                caps_word_off();
                clear_oneshot_mods();
            }
            else {
                if (shift_mod) {
                    clear_oneshot_mods();
                } else {
                    add_oneshot_mods(MOD_BIT(KC_LSFT));
                }
            }
            break;
        case TD_DOUBLE_TAP:
            caps_word_toggle();
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            layer_on(LY2);
            break;
        default:
            break;
    }
}

void leftshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (lshift_td_state) {
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(LY2);
            break;
        default:
            break;
    }
}

void rightshift_finished(tap_dance_state_t *state, void *user_data) {
    /* mod_state = get_mods(); */
    /* oneshot_mod_state = get_oneshot_mods(); */
    /* bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT); */
    rshift_td_state = cur_dance(state);
    switch (rshift_td_state) {
        case TD_SINGLE_TAP:
            layer_invert(LYN);
            /* if (shift_mod) { */
            /*   tap_code16(KC_HASH); */
            /* } else { */
            /*   tap_code16(KC_AT); */
            /* } */
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_INS);
            /* if (shift_mod) { */
            /*   tap_code16(KC_PIPE); */
            /* } else { */
            /*   tap_code16(KC_AMPR); */
            /* } */
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            layer_on(LYN);
            break;
        default:
            break;
    }
}

void rightshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (rshift_td_state) {
        case TD_SINGLE_TAP:
            /* clear_oneshot_layer_state(ONESHOT_PRESSED); */
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(LYN);
            break;
        default:
            break;
    }
}

void ctrlshift_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
    ctrlshift_td_state = cur_dance(state);
    switch (ctrlshift_td_state) {
        case TD_SINGLE_TAP:
            if(shift_mod) {
                tap_code16(KC_HASH);
            }
            else {
                tap_code16(KC_AT);
            }
            break;
        case TD_DOUBLE_TAP:
            if(shift_mod) {
                tap_code16(KC_PIPE);
            }
            else {
                tap_code16(KC_AMPR);
            }
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            layer_on(LY2);
            break;
        default:
            break;
    }
}

void ctrlshift_reset(tap_dance_state_t *state, void *user_data) {
    switch (ctrlshift_td_state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            layer_off(LY2);
            break;
        default:
            break;
    }
}

void copypaste_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    bool ly1_on = IS_LAYER_ON(LY1);
    switch (td_state) {
        case TD_SINGLE_TAP:
            if(ly1_on) {
              add_oneshot_mods(MOD_BIT(KC_LCTL));
              tap_code(KC_A);
            }
            else {
              add_oneshot_mods(MOD_BIT(KC_LCTL));
              tap_code(KC_C);
            }
            break;
        case TD_DOUBLE_TAP:
            if(ly1_on) {
              add_oneshot_mods(MOD_BIT(KC_LGUI));
              tap_code(KC_GRV);
            }
            else {
              add_oneshot_mods(MOD_BIT(KC_LCTL));
              tap_code(KC_X);
            }
            break;
        case TD_SINGLE_HOLD:
            if(ly1_on) {
              layer_invert(LYV);
            }
            else {
              add_oneshot_mods(MOD_BIT(KC_LCTL));
              tap_code(KC_V);
            }
            break;
        case TD_DOUBLE_HOLD:
            if(ly1_on) {
              layer_invert(LYF);
            }
            else {
              add_oneshot_mods(MOD_BIT(KC_LSFT));
              add_oneshot_mods(MOD_BIT(KC_LGUI));
              tap_code(KC_S);
            }
            break;
        default:
            break;
    }
}

void copypaste_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void openbrace_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            SEND_STRING("{");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("[");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("(");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING("<");
            break;
        default:
            break;
    }
}

void openbrace_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void closebrace_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            SEND_STRING("}");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("]");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(")");
            break;
        case TD_DOUBLE_HOLD:
            SEND_STRING(">");
            break;
        default:
            break;
    }
}

void closebrace_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        default:
            break;
    }
}

void guieq_finished(tap_dance_state_t *state, void *user_data) {
    guieq_td_state = cur_dance(state);
    switch (guieq_td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_EQL);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_EQL);
            register_code16(KC_EQL);
            break;
        case TD_SINGLE_HOLD:
            if(detected_host_os() == OS_WINDOWS) {
                register_mods(MOD_BIT(KC_LALT));
            } else {
                register_mods(MOD_BIT(KC_LGUI));
            }
            break;
        case TD_DOUBLE_HOLD:
            if(detected_host_os() == OS_WINDOWS) {
                register_mods(MOD_BIT(KC_LALT));
            } else {
                register_mods(MOD_BIT(KC_LGUI));
            }
            register_mods(MOD_BIT(KC_LSFT));
            break;
        default:
            break;
    }
}

void guieq_reset(tap_dance_state_t *state, void *user_data) {
    switch (guieq_td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            unregister_code16(KC_EQL);
            break;
        case TD_SINGLE_HOLD:
            if(detected_host_os() == OS_WINDOWS) {
                unregister_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            break;
        case TD_DOUBLE_HOLD:
            if(detected_host_os() == OS_WINDOWS) {
                unregister_mods(MOD_BIT(KC_LALT));
            } else {
                unregister_mods(MOD_BIT(KC_LGUI));
            }
            unregister_mods(MOD_BIT(KC_LSFT));
            break;
        default:
            break;
    }
}

void guimin_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
    guimin_td_state = cur_dance(state);
    switch (guimin_td_state) {
        case TD_SINGLE_TAP:
            if(shift_mod || is_caps_word_on()) {
                tap_code16(KC_UNDS);
            }
            else {
                tap_code16(KC_MINS);
            }
            break;
        case TD_DOUBLE_TAP:
            if(shift_mod || is_caps_word_on()) {
                tap_code16(KC_UNDS);
                tap_code16(KC_UNDS);
            }
            else {
                tap_code16(KC_MINS);
                tap_code16(KC_MINS);
            }
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            layer_on(LYN);
            break;
        default:
            break;
    }
}

void guimin_reset(tap_dance_state_t *state, void *user_data) {
    switch (guimin_td_state) {
        case TD_SINGLE_TAP:
        case TD_DOUBLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case TD_DOUBLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            layer_off(LYN);
            break;
        default:
            break;
    }
}

void utility_finished(tap_dance_state_t *state, void *user_data) {
    ux_td_state = cur_dance(state);
    bool ly2_on = IS_LAYER_ON(LY2);
    switch (ux_td_state) {
        case TD_SINGLE_TAP:
            if(ly2_on) {
                tap_code(KC_INS);
            }
            else {
                tap_code(KC_F24);
            }
            break;
        case TD_DOUBLE_TAP:
            if(ly2_on) {
                add_oneshot_mods(MOD_BIT(KC_LGUI));
                tap_code(KC_SPC);
            }
            else {
                tap_code(KC_F23);
            }
            break;
        case TD_SINGLE_HOLD:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            tap_code(KC_C);
            break;
        case TD_DOUBLE_HOLD:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            add_oneshot_mods(MOD_BIT(KC_LALT));
            tap_code(KC_DEL);
            break;
        default:
            break;
    }
}

void utility_reset(tap_dance_state_t *state, void *user_data) {
    switch (ux_td_state) {
        case TD_SINGLE_HOLD:
            tap_code(KC_UP);
            tap_code(KC_ENT);
            break;
        default:
            break;
    }
}

void nument_finished(tap_dance_state_t *state, void *user_data) {
    ne_td_state = cur_dance(state);
    switch (ne_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_DOUBLE_TAP:
            layer_invert(LYN);
            break;
        case TD_SINGLE_HOLD:
            layer_on(LYN);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(LYF);
            break;
        default:
            break;
    }
}

void nument_reset(tap_dance_state_t *state, void *user_data) {
    switch (ne_td_state) {
        case TD_SINGLE_HOLD:
            layer_off(LYN);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(LYF);
            break;
        default:
            break;
    }
}

void terminal_finished(tap_dance_state_t *state, void *user_data) {
    tm_td_state = cur_dance(state);
    switch (tm_td_state) {
        case TD_SINGLE_TAP:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_T);
            break;
        case TD_DOUBLE_TAP:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_R);
            break;
        case TD_SINGLE_HOLD:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            tap_code(KC_C);
            break;
        case TD_DOUBLE_HOLD:
            add_oneshot_mods(MOD_BIT(KC_LCTL));
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_Q);
            break;
        default:
            break;
    }
}

void terminal_reset(tap_dance_state_t *state, void *user_data) {
    switch (tm_td_state) {
        case TD_SINGLE_HOLD:
            tap_code(KC_UP);
            tap_code(KC_ENT);
            break;
        default:
            break;
    }
}

void mouse_button_finished(tap_dance_state_t *state, void *user_data) {
    mb_td_state = cur_dance(state);
    switch (mb_td_state) {
        case TD_SINGLE_TAP:
            tap_code(MS_BTN1);
            break;
        case TD_DOUBLE_TAP:
            tap_code(MS_BTN2);
            break;
        case TD_SINGLE_HOLD:
            register_code(MS_BTN1);
            break;
        case TD_DOUBLE_HOLD:
            register_code(MS_BTN3);
            break;
        default:
            break;
    }
}

void mouse_button_reset(tap_dance_state_t *state, void *user_data) {
    switch (mb_td_state) {
        case TD_SINGLE_HOLD:
            unregister_code(MS_BTN1);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(MS_BTN3);
            break;
        default:
            break;
    }
}

void lead_finished(tap_dance_state_t *state, void *user_data) {
    lead_td_state = cur_dance(state);
    switch (lead_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F24);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_F23);
            break;
        case TD_SINGLE_HOLD:
            layer_on(LY3); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_HOLD:
            layer_on(LYN); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void lead_reset(tap_dance_state_t *state, void *user_data) {
    switch (lead_td_state) {
        case TD_SINGLE_HOLD:
            layer_off(LY3);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(LYN);
            break;
        default:
            break;
    }
}

void ly1tab_finished(tap_dance_state_t *state, void *user_data) {
    ly1tab_td_state = cur_dance(state);
    switch (ly1tab_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_DOUBLE_TAP:
            add_oneshot_mods(MOD_BIT(KC_LSFT));
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY2)) {
                layer_on(LY3);
            }
            else {
                layer_on(TAB_LAYER); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            }
            break;
        default:
            break;
    }
}

void ly1tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (ly1tab_td_state) {
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY3)) {
                layer_off(LY3);
            }
            layer_off(LY1);
            break;
        default:
            break;
    }
}

void ly1bspc_finished(tap_dance_state_t *state, void *user_data) {
    mod_state = get_mods();
    oneshot_mod_state = get_oneshot_mods();
    bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
    ly1bspc_td_state = cur_dance(state);
    switch (ly1bspc_td_state) {
        case TD_SINGLE_TAP:
            if (shift_mod) {
                unregister_mods(mod_state);
                clear_oneshot_mods();
                tap_code(KC_DEL);
                register_mods(mod_state);
            }
            else {
                tap_code(KC_BSPC);
            }
            break;
        case TD_DOUBLE_TAP:
            if (shift_mod) {
                unregister_mods(mod_state);
                clear_oneshot_mods();
                tap_code(KC_DEL);
                tap_code(KC_DEL);
                register_mods(mod_state);
            }
            else {
                tap_code(KC_BSPC);
                tap_code(KC_BSPC);
            }
            break;
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY2)) {
                layer_on(LY3);
            }
            else {
                layer_on(LY1); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            }
            break;
        default:
            break;
    }
}

void ly1bspc_reset(tap_dance_state_t *state, void *user_data) {
    switch (ly1bspc_td_state) {
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY3)) {
                layer_off(LY3);
            }
            layer_off(LY1);
            break;
        default:
            break;
    }
}

void ly2ent_finished(tap_dance_state_t *state, void *user_data) {
    ly2ent_td_state = cur_dance(state);
    switch (ly2ent_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_ENT);
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY1)) {
                layer_on(LY3);
            }
            else {
                layer_on(LY2); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            }
            break;
        default:
            break;
    }
}

void ly2ent_reset(tap_dance_state_t *state, void *user_data) {
    switch (ly2ent_td_state) {
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY3)) {
                layer_off(LY3);
            }
            layer_off(LY2);
            break;
        default:
            break;
    }
}

void ly2spc_finished(tap_dance_state_t *state, void *user_data) {
    ly2spc_td_state = cur_dance(state);
    switch (ly2spc_td_state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_DOUBLE_TAP:
            tap_code(KC_SPC);
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY2)) {
                layer_on(LY3);
            }
            else {
                layer_on(LY2); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            }
            break;
        default:
            break;
    }
}

void ly2spc_reset(tap_dance_state_t *state, void *user_data) {
    switch (ly2spc_td_state) {
        case TD_SINGLE_HOLD:
            if(IS_LAYER_ON(LY3)) {
                layer_off(LY3);
            }
            layer_off(LY2);
            break;
        default:
            break;
    }
}

// tap_dance_actions[] lives in tapdance_actions.h: QMK needs it in the keymap.c translation unit

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(T_AQ):
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(T_AQ):
        case TD(T_OB):
        case TD(T_CB):
        case TD(T_CE):
        case TD(T_CP):
            return TAPPING_TERM - 50;
        case LT(LY2,KC_A):
        case LT(LY1,KC_SCLN):
            return TAPPING_TERM + 250;
        default:
            return TAPPING_TERM;
    }
}

void oneshot_layer_changed_user(uint8_t layer) {
    if (!layer && nm_os_on) {
        nm_os_on = false;
    }
}
