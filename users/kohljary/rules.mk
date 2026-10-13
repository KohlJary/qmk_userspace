SRC += leader.c
SRC += tapdance.c
SRC += keycodes.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
# MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUTO_SHIFT_ENABLE = no      # Auto Shift
DYNAMIC_MACRO_ENABLE = yes  # Dynamic macro support
CAPS_WORD_ENABLE = yes      # Caps Word support
TAP_DANCE_ENABLE = yes			# Tap dance
LEADER_ENABLE = yes         # Leader key
KEY_OVERRIDE_ENABLE = yes   # Key overrides
UNICODEMAP_ENABLE = yes
UCIS_ENABLE = no
OS_DETECTION_ENABLE = yes
TRI_LAYER_ENABLE = yes

# Userspace RGB matrix effects
RGB_MATRIX_CUSTOM_USER = yes

# Was in the fork's keyboards/zsa/moonlander/rules.mk
REPEAT_KEY_ENABLE = yes
