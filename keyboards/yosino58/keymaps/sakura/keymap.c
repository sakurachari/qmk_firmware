#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                                  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                                  |   Y  |   U  |   I  |   O  |   P  |  =   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |                                  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   Z  |   X  |   C  |   V  |   B  |-------.-------.  ,---------------|   N  |   M  |   ,  |   .  |   /  |  \   |
 * `-----------------------------------------/  Del  /       /   \       \ Bksp \----------------------------------------'
 *                          | LAlt | LGUI | /-------/ Space /     \ Enter \-------\  |   [  |  ]   |
 *                          |      |      |/ LOWER /       /       \       \ RAISE \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_QWERTY] = LAYOUT( \
  KC_GRV,   KC_1, KC_2, KC_3, KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS, \
  KC_TAB,   KC_Q, KC_W, KC_E, KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_EQL,  \
  KC_LSFT,  KC_A, KC_S, KC_D, KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LCTRL, KC_Z, KC_X, KC_C, KC_V,    KC_B,    KC_DEL,    KC_SPC, KC_ENT, KC_BSPC,    KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, \
                              KC_LALT, KC_LGUI, LOWER,                     RAISE,      KC_LBRC, KC_RBRC\
  ),

/* LOWER
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                                  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * | Tab  |   /  |   -  |   7  |   8  |   9  |                                  | PSCR | SLCK | Pause|      |  Å™  |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LShift|   *  |   +  |   4  |   5  |   6  |                                  |Insert| Home |PageUP|      |  Å´  |  Å®  |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |LCTRL |   .  |   0  |   1  |   2  |   3  |-------.-------.  ,---------------|  Del | End  |PageDN|  Å©  | Num  | Caps |
 * `-----------------------------------------/  F11  /       /   \       \  F12  \----------------------------------------'
 *                          | LAlt | LGUI | /-------/ Space /     \ Enter \-------\  |      |      |
 *                          |      |      |/ LOWER /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_LOWER] = LAYOUT( \
  KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, \
  _______, KC_PSLS, KC_PMNS, KC_P7, KC_P8,   KC_P9,                                       KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, KC_UP,   XXXXXXX, \
  _______, KC_PAST, KC_PPLS, KC_P4, KC_P5,   KC_P6,                                       KC_INS,  KC_HOME, KC_PGUP, XXXXXXX, KC_DOWN, KC_RGHT, \
  _______, KC_PDOT, KC_P0,   KC_P1, KC_P2,   KC_P3,   KC_F11,  _______, _______, KC_F12,  KC_DEL,  KC_END,  KC_PGDN, KC_LEFT, KC_NLCK, KC_CLCK, \
                                    _______, _______, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX\
  ),

/* RAISE
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |RESET |      |      |      |      |      |                                  | Mute | Vol+ | Play |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  | Prev | Vol- | Next |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |MS_Bt1| MS_U |MS_Bt2|MS_WhU|MS_WhL|                                  |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      | MS_L | MS_D | MS_R |MS_WhD|MS_WhR|-------.-------.  ,---------------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/ Space /     \ Enter \-------\  |      |      |
 *                          |      |      |/       /       /       \       \ RAISE \ |      |      |
 *                          `-----------------------------'         '------------------------------'
 */
 [_RAISE] = LAYOUT( \
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,                                     KC_MUTE, KC_VOLU, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,                                     KC_MPRV, KC_VOLD, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,    KC_WH_L,                                     XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
  XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,    KC_WH_R, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, RGBRST,  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, \
                                      XXXXXXX,    XXXXXXX, XXXXXXX,                   _______, XXXXXXX, XXXXXXX \
  )

/*   ADJUST
 * ,-----------------------------------------.                                  ,-----------------------------------------.
 * |RESET |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                                  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                                  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.-------.  ,---------------|      |      |      |      |      |      |
 * `-----------------------------------------/       /       /   \       \       \----------------------------------------'
 *                          |      |      | /-------/       /     \       \-------\  |      |      |
 *                          |      |      |/       /       /       \       \       \ |      |      |
 *                          `-----------------------------'         '------------------------------'

 [_ADJUST] = LAYOUT( \
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                      XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX \
  ) 
*/
};


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
      #ifdef SSD1306_128X64
        iota_gfx_init(false);   // turns on the display
      #else
        iota_gfx_init(!has_usb());   // turns on the display
      #endif
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

//assign the right code to your layers for OLED display
#define L_QWERTY 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

// When add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    static char indctr[2][20][5]=
    {
      // white icon
      {
        {0x0C,0x2C,0x4C,0x6C,0},
        {0x0D,0x2D,0x4D,0x6D,0},
        {0x0E,0x2E,0x4E,0x6E,0},
        {0x0F,0x2F,0x4F,0x6F,0},
        {0x10,0x30,0x50,0x70,0},
        {0x11,0x31,0x51,0x71,0},
        {0x12,0x32,0x52,0x72,0},
        {0x20,0x33,0x53,0x73,0},
        {0x14,0x34,0x54,0x74,0},
        {0x15,0x35,0x55,0x75,0},
        {0x16,0x36,0x56,0x76,0},
        {0x17,0x37,0x57,0x77,0},
        {0x18,0x38,0x58,0x78,0},
        {0x19,0x39,0x59,0x79,0},
        {0x1A,0x3A,0x5A,0x7A,0},
        {0x1B,0x3B,0x5B,0x7B,0},
        {0x1C,0x3C,0x5C,0x7C,0},
        {0x1D,0x3D,0x5D,0x7D,0},
        {0x1E,0x3E,0x5E,0x7E,0},
        {0x1F,0x3F,0x5F,0x7F,0}
      },
      // Black icon
      {
        {0x8C,0xAC,0xCC,0xEC,0},
        {0x8D,0xAD,0xCD,0xED,0},
        {0x8E,0xAE,0xCE,0xEE,0},
        {0x8F,0xAF,0xCF,0xEF,0},
        {0x90,0xB0,0xD0,0xF0,0},
        {0x91,0xB1,0xD1,0xF1,0},
        {0x92,0xB2,0xD2,0xF2,0},
        {0x93,0xB3,0xD3,0xF3,0},
        {0x94,0xB4,0xD4,0xF4,0},
        {0x95,0xB5,0xD5,0xF5,0},
        {0x96,0xB6,0xD6,0xF6,0},
        {0x97,0xB7,0xD7,0xF7,0},
        {0x98,0xB8,0xD8,0xF8,0},
        {0x99,0xB9,0xD9,0xF9,0},
        {0x9A,0xBA,0xDA,0xFA,0},
        {0x9B,0xBB,0xDB,0xFB,0},
        {0x9C,0xBC,0xDC,0xFC,0},
        {0x9D,0xBD,0xDD,0xFD,0},
        {0x9E,0xBE,0xDE,0xFE,0},
        {0x9F,0xBF,0xDF,0xFF,0}
      }
    };

    int rown = 0;
    int rowc = 0;
    int rowl = 0;
    int rowr = 0;
    int rowa = 0;

    //Set Indicator icon
    if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) { rown = 1; } else { rown = 0; }
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) { rowc = 1; } else { rowc = 0; }
    if (layer_state == L_LOWER) { rowl = 1; }
    if (layer_state == L_RAISE) { rowr = 1; }
    if (layer_state == L_ADJUST) { rowa = 1; }

    matrix_write(matrix, indctr[rowl]  [0]);
    matrix_write(matrix, indctr[rowr]  [1]);
    matrix_write(matrix, indctr[rowa]  [2]);
    matrix_write(matrix, indctr[rowc]  [3]);
    matrix_write(matrix, indctr[rown]  [4]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [5]);
    matrix_write(matrix, indctr[rowr]  [6]);
    matrix_write(matrix, indctr[rowa]  [7]);
    matrix_write(matrix, indctr[rowc]  [8]);
    matrix_write(matrix, indctr[rown]  [9]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [10]);
    matrix_write(matrix, indctr[rowr]  [11]);
    matrix_write(matrix, indctr[rowa]  [12]);
    matrix_write(matrix, indctr[rowc]  [13]);
    matrix_write(matrix, indctr[rown]  [14]);
    matrix_write_char(matrix, 0x13);
    matrix_write(matrix, indctr[rowl]  [15]);
    matrix_write(matrix, indctr[rowr]  [16]);
    matrix_write(matrix, indctr[rowa]  [17]);
    matrix_write(matrix, indctr[rowc]  [18]);
    matrix_write(matrix, indctr[rown]  [19]);

  }else{
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);  
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
      } else {
        layer_off(_LOWER);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

