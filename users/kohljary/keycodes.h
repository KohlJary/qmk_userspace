#pragma once

#include QMK_KEYBOARD_H

enum keyboard_keycodes {
    //User keycodes
    EQ_NEQ = QK_KB_0,  //Equal/not equal comparison
    LTE_GTE, //Less than equal to/greater than equal to
    INC_DEC, //Increment/decrement operator
    AND_OR,  //And/or operator
    LAMBDA,  //Lambda operator
    KC_NULL, //"null" key
    EQ_NULL, //==/!= null key
    KC_TRUE, //"true/false" key
    IF_ELSE, //"if/else/else if" key
    FOR_EAC, //"for/foreach" key
    MK_FLSH, //Make/flash keymap
    T_RSTRT, //Restart terminal process shortcut
    NULL_OP, //??
    UC_STRT, //
    KC_MERC, //☿ key
};

enum unicode_names {
    BANG,
    IRONY,
    SNEK,
    COPY,
    REGT,
    MERCURY
};
