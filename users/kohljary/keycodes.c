#include QMK_KEYBOARD_H
#include <stdbool.h>
#include "keycodes.h"
#include "tapdance.h"
#include "os_detection.h"
#include "layers.h"

uint8_t mod_state;
uint8_t oneshot_mod_state;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

static bool user_return;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint32_t key_timer;

  user_return = false;
  mod_state = get_mods();
  oneshot_mod_state = get_oneshot_mods();

  bool shift_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_SHIFT);
  bool ctrl_mod = ((mod_state | oneshot_mod_state) & MOD_MASK_CTRL);

  switch (keycode) {
    case EQ_NEQ:
      if (record->event.pressed) {
      clear_mods();
      clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("!=");
        } else {
          SEND_STRING("==");
        }
        return false;
      }
      break;
    case LTE_GTE:
      if (record->event.pressed) {
      clear_mods();
      clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("<=");
        } else {
          SEND_STRING(">=");
        }
        return false;
      }
      break;
    case INC_DEC:
      if (record->event.pressed) {
      clear_mods();
      clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("--");
        } else {
          SEND_STRING("++");
        }
        return false;
      }
      break;
    case AND_OR:
      if (record->event.pressed) {
      clear_mods();
      clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("||");
        } else {
          SEND_STRING("&&");
        }
        return false;
      }
      break;
    case LAMBDA:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("->");
        } else {
          SEND_STRING("=>");
        }
        return false;
      }
      break;
    case KC_NULL:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("undefined");
        } else {
          SEND_STRING("null");
        }
        return false;
      }
      break;
    case EQ_NULL:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (ctrl_mod) {
          if (shift_mod) {
            SEND_STRING("!= undefined");
          } else {
            SEND_STRING("== undefined");
          }
        }
        else {
          if (shift_mod) {
            SEND_STRING("!= null");
          } else {
            SEND_STRING("== null");
          }
        }
        return false;
      }
      break;
    case KC_TRUE:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("false");
        } else {
          SEND_STRING("true");
        }
        return false;
      }
      break;
    case IF_ELSE:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (ctrl_mod) {
          SEND_STRING("else if () {");
          tap_code(KC_ENT);
          tap_code(KC_ESC);
          SEND_STRING("k$F)i");
        }
        else if (shift_mod) {
          SEND_STRING("else () {");
          tap_code(KC_ENT);
          tap_code(KC_ESC);
          SEND_STRING("k$F)i");
        } else {
          SEND_STRING("if () {");
          tap_code(KC_ENT);
          tap_code(KC_ESC);
          SEND_STRING("k$F)i");
        }
        return false;
      }
      break;
    case FOR_EAC:
      if (record->event.pressed) {
        clear_mods();
        clear_oneshot_mods();
        if (shift_mod) {
          SEND_STRING("foreach () {");
          tap_code(KC_ENT);
          tap_code(KC_ESC);
          SEND_STRING("k$F)i");
        } else {
          SEND_STRING("for () {");
          tap_code(KC_ENT);
          tap_code(KC_ESC);
          SEND_STRING("k$F)i");
        }
        return false;
      }
      break;
    case NULL_OP:
      if (record->event.pressed) {
          SEND_STRING("??");
      }
      break;
    case MK_FLSH:
      clear_mods();
      clear_oneshot_mods();
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("`") SS_DELAY(500) SS_LCTL("eu") "qcf");
        key_timer = timer_read32();
        tap_code(KC_ENT);
      } else {
        if (timer_elapsed32(key_timer) >= 500) {
          reset_keyboard();
        }
      }
      set_mods(mod_state);
      break;
    case T_RSTRT:
      clear_mods();
      clear_oneshot_mods();
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c"));
      } else {
        tap_code(KC_UP);
        tap_code(KC_ENT);
      }
      set_mods(mod_state);
      break;
    case UC_STRT:
      if (record->event.pressed) {
        // ucis_start();
      }
      return false;
      break;
    // case KC_MERC:
    //   if (record->event.pressed) {
    //     send_unicode_string("263F");
    //   }
    //   return false;
    //   break;
    case LCA(KC_DEL):
      if (record->event.pressed) {
        if (detected_host_os() == OS_LINUX) {
          add_oneshot_mods(MOD_BIT(KC_LGUI));
          tap_code(KC_ESC);
          return false;
        }
      }
      break;
    case G(KC_SPC):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LGUI));
          tap_code(KC_S);
          return false;
        }
      }
      break;
    case G(KC_DOT):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LGUI));
          add_oneshot_mods(MOD_BIT(KC_LSFT));
          tap_code(KC_3);
          return false;
        }
      }
      break;
    case G(KC_EQL):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_M);
          return false;
        }
      }
      break;
    case G(KC_P):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_P);
          return false;
        }
      }
      break;
    case G(KC_N):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_N);
          return false;
        }
      }
      break;
    case G(KC_H):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_H);
          return false;
        }
      }
      break;
    case G(KC_J):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_J);
          return false;
        }
      }
      break;
    case G(KC_K):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_K);
          return false;
        }
      }
      break;
    case G(KC_L):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_L);
          return false;
        }
      }
      break;
    case G(KC_A):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_A);
          return false;
        }
      }
      break;
    case G(KC_S):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_S);
          return false;
        }
      }
      break;
    case G(KC_D):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_D);
          return false;
        }
      }
      break;
    case G(KC_F):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_F);
          return false;
        }
      }
      break;
    case G(KC_SCLN):
      if (record->event.pressed) {
        if (detected_host_os() == OS_WINDOWS) {
          add_oneshot_mods(MOD_BIT(KC_LALT));
          tap_code(KC_SCLN);
          return false;
        }
      }
      break;
    default:
      if(user_return == true) {
        return false;
      }
      return process_record_keymap(keycode, record);
      break;
  }
  if(user_return == true) {
    return false;
  }
  return process_record_keymap(keycode, record);
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case TD(T_LS):
        case TD(T_GM):
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case TD(T_LS):
        case TD(T_RS):
        case TD(T_GE):
        case TD(T_CE):
            return false;  // Ignore backspace.
    }

    return true;  // Other keys can be repeated.
}

// Key overrides live in key_overrides.h: QMK needs key_overrides[] in the keymap.c translation unit

const uint32_t unicode_map[] PROGMEM = {
  [MERCURY] = 0x263F,
};

// const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
//     UCIS_SYM("poop",     0x1F4A9),                // 💩
//     UCIS_SYM("rofl",     0x1F923),                // 🤣
//     UCIS_SYM("cuba",     0x1F1E8, 0x1F1FA),       // 🇨🇺
//     UCIS_SYM("look",     0x0CA0, 0x005F, 0x0CA0), // ಠ_ಠ
//     UCIS_SYM("copy",     0x00A9),                 // ©
//     UCIS_SYM("reg",      0x00AE),                 // ®
//     UCIS_SYM("mercury",  0x263F)                  // ®
// );

#if defined(REPEAT_KEY_ENABLE) && !defined(NO_ALT_REPEAT_KEY) && defined(ALT_REPEAT_MASK)
// Repeat key held with ALT_REPEAT_MASK (config.h) acts as the alternate repeat key.
// Runs before the repeat key's own processing, so core QMK needs no patch.
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_REPEAT_KEY) {
        uint8_t mods = get_mods();
        if (mods & ALT_REPEAT_MASK) {
            del_mods(ALT_REPEAT_MASK);
            alt_repeat_key_invoke(&record->event);
            set_mods(mods);
            return false;
        }
    }
    return true;
}
#endif
