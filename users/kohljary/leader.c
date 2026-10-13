#include QMK_KEYBOARD_H
#include <stdbool.h>
#include "os_detection.h"
#include "leader.h"

// Personal details live in secrets.h, which is git-ignored (copy secrets.h.example to start).
// Without it the build still works and these sequences type nothing.
#if __has_include("secrets.h")
#    include "secrets.h"
#else
#    include "secrets.h.example"
#endif

void send_email(bool isWork) {
  if(isWork) {
    SEND_STRING(KJ_EMAIL_WORK);
  }
  else {
    SEND_STRING(KJ_EMAIL_PERSONAL);
  }
}

void leader_end_user(void) {
  //name and contact info
  if(leader_sequence_one_key(KC_N)) {
    SEND_STRING(KJ_FIRST_NAME);
  }
  if(leader_sequence_two_keys(KC_N, KC_N)) {
    SEND_STRING(KJ_LAST_NAME);
  }
  if(leader_sequence_three_keys(KC_N, KC_N, KC_N)) {
    SEND_STRING(KJ_FULL_NAME);
  }
  if(leader_sequence_four_keys(KC_N, KC_N, KC_N, KC_N)) {
    SEND_STRING(KJ_MIDDLE_NAME);
  }
  if(leader_sequence_one_key(KC_B)) {
    SEND_STRING(KJ_BIRTHDATE);
  }
  if(leader_sequence_one_key(KC_P)) {
    SEND_STRING(KJ_PHONE);
  }
  if(leader_sequence_one_key(KC_E)) {
    if(detected_host_os() == OS_WINDOWS) {
        send_email(true);
    }
    else {
        send_email(false);
    }
  }
  if(leader_sequence_two_keys(KC_E, KC_E)) {
    if(detected_host_os() == OS_WINDOWS) {
        send_email(false);
    }
    else {
        send_email(true);
    }
  }

  //address info
  if(leader_sequence_one_key(KC_A)) {
    SEND_STRING(KJ_STREET);
  }
  if(leader_sequence_one_key(KC_U)) {
      SEND_STRING(KJ_UNIT);
  }
  if(leader_sequence_one_key(KC_C)) {
    SEND_STRING(KJ_CITY);
  }
  if(leader_sequence_one_key(KC_S)) {
    SEND_STRING(KJ_STATE);
  }
  if(leader_sequence_one_key(KC_Z)) {
      SEND_STRING(KJ_ZIP);
  }
  if(leader_sequence_one_key(KC_D)) {
      SEND_STRING(KJ_FULL_ADDRESS);
  }
  if(leader_sequence_one_key(KC_L)) {
    SEND_STRING("localhost:");
  }

  //Git quick feature branch stub
  if(leader_sequence_one_key(KC_G))
  {
      SEND_STRING("feature/kj/");
  }

  //test npi number
  if(leader_sequence_two_keys(KC_N, KC_P)) {
    SEND_STRING("1043870686");
  }

  //if/else
  if(leader_sequence_one_key(KC_I)) {
    tap_code(KC_O);
    SEND_STRING("if () {");
    tap_code(KC_ENT);
    tap_code(KC_ESC);
    SEND_STRING("k$F)i");
  }
  if(leader_sequence_three_keys(KC_I, KC_E, KC_I) || leader_sequence_two_keys(KC_I, KC_I)) {
    tap_code(KC_O);
    SEND_STRING("else if () {");
    tap_code(KC_ENT);
    tap_code(KC_ESC);
    SEND_STRING("k$F)i");
  }
  if(leader_sequence_two_keys(KC_I, KC_E) || leader_sequence_three_keys(KC_I, KC_I, KC_I)) {
    tap_code(KC_O);
    SEND_STRING("else {");
    tap_code(KC_ENT);
  }

  //for/foreach
  if(leader_sequence_one_key(KC_F)) {
    tap_code(KC_O);
    SEND_STRING("for () {");
    tap_code(KC_ENT);
    tap_code(KC_ESC);
    SEND_STRING("k$F)i");
  }
  if(leader_sequence_two_keys(KC_F, KC_E) || leader_sequence_two_keys(KC_F, KC_F)) {
    tap_code(KC_O);
    SEND_STRING("foreach () {");
    tap_code(KC_ENT);
    tap_code(KC_ESC);
    SEND_STRING("k$F)i");
  }

  //switch/case
  if(leader_sequence_one_key(KC_W)) {
    tap_code(KC_O);
    SEND_STRING("switch () {");
    tap_code(KC_ENT);
    tap_code(KC_ESC);
    SEND_STRING("k$F)i");
  }
  if(leader_sequence_two_keys(KC_W, KC_C) || leader_sequence_two_keys(KC_W, KC_W)) {
    tap_code(KC_O);
    SEND_STRING("case :");
    tap_code(KC_ENT);
    SEND_STRING("break;");
    tap_code(KC_ESC);
    SEND_STRING("k$F:i");
  }
  if(leader_sequence_two_keys(KC_W, KC_D) || leader_sequence_three_keys(KC_W, KC_W, KC_W)) {
    tap_code(KC_O);
    SEND_STRING("default:");
    tap_code(KC_ENT);
    SEND_STRING("break;");
    tap_code(KC_UP);
    tap_code(KC_END);
    tap_code(KC_ENT);
  }

  //primitive types
  if(leader_sequence_two_keys(KC_T, KC_B)) {
    SEND_STRING("bool");
  }
  if(leader_sequence_three_keys(KC_T, KC_B, KC_B)) {
    SEND_STRING("boolean");
  }
  if(leader_sequence_two_keys(KC_T, KC_C)) {
    SEND_STRING("char");
  }
  if(leader_sequence_two_keys(KC_T, KC_D)) {
    SEND_STRING("decimal");
  }
  if(leader_sequence_two_keys(KC_T, KC_F)) {
    SEND_STRING("float");
  }
  if(leader_sequence_two_keys(KC_T, KC_G)) {
    SEND_STRING("Guid");
  }
  if(leader_sequence_two_keys(KC_T, KC_I)) {
    SEND_STRING("int");
  }
  if(leader_sequence_two_keys(KC_T, KC_N)) {
    SEND_STRING("number");
  }
  if(leader_sequence_two_keys(KC_T, KC_S)) {
    SEND_STRING("string");
  }
  if(leader_sequence_two_keys(KC_T, KC_V)) {
    SEND_STRING("var");
  }
}
