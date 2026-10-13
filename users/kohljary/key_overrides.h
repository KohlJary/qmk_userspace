#pragma once

// Key overrides. Like tapdance_actions.h, include this from each keymap.c (once): QMK's keymap
// introspection sizes key_overrides[] from the keymap.c translation unit. Current QMK uses a plain
// array, with no NULL terminator.

#include "KohlJary.h"

const key_override_t next_track_override =
    ko_make_with_layers_negmods_and_options(
        MOD_MASK_CTRL,       // Trigger modifiers: ctrl
        KC_MPLY,             // Trigger key: play/pause
        KC_MNXT,             // Replacement key
        ~0,                  // Activate on all layers
        MOD_MASK_SA,         // Do not activate when shift or alt are pressed
        ko_option_no_reregister_trigger); // Specifies that the play key is not registered again after lifting ctrl

const key_override_t prev_track_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CS, KC_MPLY,
                                            KC_MPRV, ~0, MOD_MASK_ALT, ko_option_no_reregister_trigger);

const key_override_t vol_up_override = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT, KC_MPLY,
                                            KC_VOLU, ~0, MOD_MASK_CS, ko_option_no_reregister_trigger);

const key_override_t vol_down_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SA, KC_MPLY,
                                            KC_VOLD, ~0, MOD_MASK_CTRL, ko_option_no_reregister_trigger);

const key_override_t mute_override = ko_make_with_layers_negmods_and_options(MOD_MASK_CA, KC_MPLY,
                                        KC_MUTE, ~0, MOD_MASK_SHIFT, ko_option_no_reregister_trigger);

const key_override_t vlead_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, QK_LEAD,
                                        KC_F24, ~0, MOD_MASK_CA, ko_option_no_reregister_trigger);

const key_override_t bsp_del_1_override = ko_make_basic(MOD_MASK_SHIFT, LT(LY1,KC_BSPC), KC_DEL);

const key_override_t bsp_del_2_override = ko_make_basic(MOD_MASK_SHIFT, LT(LY2,KC_BSPC), KC_DEL);

const key_override_t bsp_del_no_ly_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

const key_override_t slsh_bsls_override = ko_make_basic(MOD_MASK_CTRL, KC_SLSH, KC_BSLS);
const key_override_t lyn_slsh_bsls_override = ko_make_basic(MOD_MASK_CTRL, LT(LYN,KC_SLSH), KC_BSLS);

const key_override_t quot_override = ko_make_basic(MOD_MASK_CTRL, KC_QUOT, KC_GRV);

const key_override_t alt_quot_override = ko_make_basic(MOD_MASK_CTRL, TD(T_AQ), KC_GRV);

const key_override_t ly_quot_override = ko_make_basic(MOD_MASK_CTRL, LT(LY1,KC_QUOT), KC_GRV);

const key_override_t at_hash_override = ko_make_basic(MOD_MASK_SHIFT, KC_AT, KC_HASH);
const key_override_t ast_perc_override = ko_make_basic(MOD_MASK_SHIFT, KC_ASTR, KC_PERC);
const key_override_t perc_ast_override = ko_make_basic(MOD_MASK_SHIFT, KC_PERC, KC_ASTR);

const key_override_t and_or_override = ko_make_basic(MOD_MASK_SHIFT, KC_AMPR, KC_PIPE);

const key_override_t tild_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_TILD);

const key_override_t exlm_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_EXLM);

const key_override_t lprn_labk_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_LABK);
const key_override_t rprn_rabk_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_RABK);

const key_override_t mins_ampr_override = ko_make_with_layers_and_negmods(MOD_MASK_CTRL, GUI_T(KC_MINS), KC_AMPR, ~0, MOD_MASK_SHIFT);
const key_override_t unds_pipe_override = ko_make_basic(MOD_MASK_CS, GUI_T(KC_MINS), KC_PIPE);

const key_override_t kp_mins_override = ko_make_basic(MOD_MASK_SHIFT, KC_PMNS, KC_PSLS);
const key_override_t kp_pls_override = ko_make_basic(MOD_MASK_SHIFT, KC_PPLS, KC_PAST);
const key_override_t kp_dot_override = ko_make_basic(MOD_MASK_SHIFT, KC_PDOT, KC_EQL);
const key_override_t kp_gpls_override = ko_make_basic(MOD_MASK_SHIFT, GUI_T(KC_PPLS), KC_PAST);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &next_track_override,
    &prev_track_override,
    &mute_override,
    &vol_up_override,
    &vol_down_override,
    &vlead_override,
    &bsp_del_1_override,
    &bsp_del_2_override,
    &bsp_del_no_ly_override,
    &slsh_bsls_override,
    &lyn_slsh_bsls_override,
    &quot_override,
    &alt_quot_override,
    &ly_quot_override,
    &at_hash_override,
    &ast_perc_override,
    &perc_ast_override,
    &and_or_override,
    &tild_override,
    &exlm_override,
    &lprn_labk_override,
    &rprn_rabk_override,
    &mins_ampr_override,
    &unds_pipe_override,
    &kp_mins_override,
    &kp_pls_override,
    &kp_dot_override,
    &kp_gpls_override
};
