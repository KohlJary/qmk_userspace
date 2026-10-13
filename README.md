# KohlJary QMK userspace

My keymaps and shared user code, built as a QMK external userspace (overlay) on top of an
unmodified upstream qmk_firmware. Nothing here needs a fork of QMK.

## Layout

    qmk.json                                build targets for 'qmk userspace-compile'
    users/kohljary/                         shared code (QMK picks it up because the keymap is named kohljary)
        KohlJary.h                          include this from every keymap.c
        tapdance_actions.h, key_overrides.h include these from every keymap.c too (see below)
        tapdance.c, keycodes.c, leader.c    the handlers
        secrets.h                           git-ignored personal details (copy secrets.h.example)
    keyboards/<board>/keymaps/kohljary/     one keymap per board

The keymap is 'kohljary', lowercase: qmk.json only accepts lowercase keymap names.

Every keymap.c starts with:

    #include "KohlJary.h"
    #include "tapdance_actions.h"
    #include "key_overrides.h"

QMK's keymap introspection sizes tap_dance_actions[] and key_overrides[] from the keymap.c translation
unit, so those two tables are defined in headers that only keymap.c includes. Including them from any
other .c file gives duplicate definitions.

## Boards

Built and in qmk.json: zsa/moonlander (main), keychron/q0/base, keychron/q9_plus/ansi_encoder.

Kept but not building (they already failed in the old fork, as of 2026-10-13):
- keychron/q8/ansi_encoder, keychron/q10/ansi_encoder: use AT_HASH, DOL_CIR, PER_AST, which are no longer
  in keycodes.h, and their encoder maps have fewer layers than the keymap.
- keychron/q8/iso: a 2023 keymap using MAC_BASE/WIN_BASE layer names.
- massdrop/alt: QMK moved it to keyboards/drop/alt; the keymap needs moving to match.

Add a board back to qmk.json once it builds.

## Setting up from scratch

1. Install the QMK CLI (Arch: 'sudo pacman -S qmk', anywhere else: 'pipx install qmk').
2. Get upstream QMK. 'qmk setup' clones it to ~/qmk_firmware and installs the toolchain:

       qmk setup -y

   On Linux, install the udev rules so flashing works without root:

       sudo cp ~/qmk_firmware/util/udev/50-qmk.rules /etc/udev/rules.d/
       sudo udevadm control --reload-rules && sudo udevadm trigger

3. Clone this repo and point QMK at it:

       git clone https://github.com/KohlJary/qmk_userspace ~/qmk_userspace
       qmk config user.overlay_dir="$(realpath ~/qmk_userspace)"
       qmk userspace-doctor          # should say 'Userspace enabled: True'

4. Personal details for the leader sequences (name, phone, address, email):

       cp ~/qmk_userspace/users/kohljary/secrets.h.example ~/qmk_userspace/users/kohljary/secrets.h

   and fill it in. secrets.h is git-ignored. Without it everything still builds; those sequences
   just type nothing.

5. Build:

       qmk userspace-compile                          # every target in qmk.json
       qmk compile -kb zsa/moonlander -km kohljary    # one board

   Firmware files land in the userspace root (git-ignored). They contain the secrets.h strings, so
   don't share them.

To try a different QMK checkout without changing the config: 'QMK_HOME=<checkout> QMK_USERSPACE=~/qmk_userspace qmk compile ...'.

## Flashing

- Moonlander: flash the .bin with ZSA's Keymapp, or 'qmk flash -kb zsa/moonlander -km kohljary' and
  press the reset button. MK_FLSH and QK_BOOT on the layers also enter the bootloader.
- Keychron: 'qmk flash -kb <board> -km kohljary', then unplug, hold Esc (or the reset button under the
  spacebar) and plug back in.
- From WSL, USB devices aren't visible by default: either attach the board with usbipd-win, or build in
  WSL and flash from Windows (Keymapp or QMK Toolbox) using the .bin.

## Adding a board

    qmk new-keymap -kb <board> -km kohljary     # move it under keyboards/ here if it landed in qmk_firmware
    qmk userspace-add -kb <board> -km kohljary  # adds it to qmk.json

Add the three includes above to its keymap.c.

## The Moonlander startup jingle

The Moonlander has a speaker (audio is on in its keyboard.json). Set the songs in the Moonlander keymap's
config.h:

    #define STARTUP_SONG SONG(ZELDA_TREASURE)     // any name from quantum/audio/song_list.h
    #define GOODBYE_SONG SONG(MARIO_GAMEOVER)     // plays when jumping to the bootloader

or write one with the note macros from quantum/audio/musical_notes.h:

    #define STARTUP_SONG SONG(E__NOTE(_E6), E__NOTE(_G6), Q__NOTE(_C7))

## What moved out of the old fork (KohlJary/qmk_firmware)

The old fork patched a few upstream files and was based on QMK from July 2024. Each patch now lives here:

| Old patch | Now |
|---|---|
| quantum/process_keycode/process_repeat_key.c: ALT_REPEAT_MASK | pre_process_record_user in users/kohljary/keycodes.c |
| keyboards/zsa/moonlander/moonlander.c: LED flags | kj_led_flags, applied in keyboard_post_init_user (Moonlander keymap) |
| keyboards/zsa/moonlander/rules.mk: caps word, repeat key, leader | users/kohljary/rules.mk |
| keyboards/keychron/q10/q10.c: DIP switch picks layer 1 | dip_switch_update_user (Q10 keymap) |
| keyboards/keychron/q9_plus/info.json: 12 dynamic layers | DYNAMIC_KEYMAP_LAYER_COUNT (Q9 Plus keymap config.h) |
| keyboards/keychron/q8/ansi_encoder/rules.mk | Q8 ansi_encoder keymap rules.mk |

Changes needed for current QMK:
- Mouse keycodes renamed: KC_BTN1-3 -> MS_BTN1-3, KC_MS_U/D/L/R -> MS_UP/MS_DOWN/MS_LEFT/MS_RGHT,
  KC_WH_U/D -> MS_WHLU/MS_WHLD.
- RGB keycodes: the old RGB_* keys drove both underglow and the RGB matrix; upstream now maps them to
  underglow-only UG_*. These boards use the matrix, so they became RM_* (RM_TOGG, RM_NEXT, RM_HUEU, ...).
- tap_dance_actions[] and key_overrides[] moved into headers included by keymap.c; key_overrides[] is a
  plain array with no NULL terminator.

If QMK changes one of these hooks or the Moonlander's LED count, the build fails (the LED table has a
static assert) rather than misbehaving.
