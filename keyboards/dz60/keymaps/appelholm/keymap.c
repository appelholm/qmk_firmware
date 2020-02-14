#include QMK_KEYBOARD_H


#define KB_IDLE_TIME_MS (60000u)


enum layers
{
    _US = 0,
    _SE,
    _FN1,
    _FN2,
    _SYS
};

enum custom_keycodes
{
    PMEMBER = SAFE_RANGE,
    CLEAR
};

enum macros
{
    VI_QUIT = 0,
    VI_WRITE
};


static struct
{
    bool leds_on;
    uint16_t idle_timer;
} internal;


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    const macro_t *retval = MACRO_NONE;

    switch (id)
    {
        case VI_QUIT:
            retval = MACRODOWN(TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN),
                    UP(KC_LSFT), TYPE(KC_Q), TYPE(KC_ENT), END);
            break;
        case VI_WRITE:
            retval = MACRODOWN(TYPE(KC_ESC), DOWN(KC_LSFT), TYPE(KC_SCLN),
                    UP(KC_LSFT), TYPE(KC_W), TYPE(KC_ENT), END);
            break;
        default:
            break;
    }

    return retval;
}

void keyboard_post_init_user(void)
{
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom_gold();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    internal.idle_timer = timer_read();
    internal.leds_on = true;
}

void matrix_scan_user(void)
{
    if (internal.leds_on
            && (timer_elapsed(internal.idle_timer) > KB_IDLE_TIME_MS))
    {
        rgblight_disable_noeeprom();
        internal.leds_on = false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    bool continue_proc = true;

    if (!record->event.pressed)
        goto exit;

    internal.idle_timer = timer_read();

    if (!internal.leds_on)
    {
        rgblight_enable_noeeprom();
        internal.leds_on = true;
    }

    switch (keycode)
    {
        case PMEMBER:
            if (record->event.pressed)
            {
                SEND_STRING("->");
            }
            break;
        case CLEAR:
            if (record->event.pressed)
            {
                SEND_STRING(SS_LCTRL("a") SS_TAP(X_DELETE));
            }
            break;
    }

exit:
    return continue_proc;
};

layer_state_t layer_state_set_user(layer_state_t state)
{
    switch (get_highest_layer(state))
    {
        case _US:
            rgblight_sethsv_noeeprom_gold();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _SE:
            rgblight_sethsv_noeeprom_cyan();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
            break;
        case _FN1:
            rgblight_sethsv_noeeprom_purple();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _FN2:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _SYS:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
            break;
        default:
            break;
    }

    return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

    /* US layer
     * .---------------------------------------------------------------------------------------.
     * | Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  Bspace |
     * |---------------------------------------------------------------------------------------+
     * |Tb/FN1|  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  | Bslash |
     * |---------------------------------------------------------------------------------------+
     * | Ctrl  |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |     Enter   |
     * |---------------------------------------------------------------------------------------+
     * |Shift   |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |       Shift      |
     * |---------------------------------------------------------------------------------------+
     * | TL(SE)|ML(FN2)| Alt |                 Space                   | Left| Down|  Up |Right|
     * '---------------------------------------------------------------------------------------'
     */
    [_US] = LAYOUT(
        KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
        KC_MINS, KC_EQL, KC_NO, KC_BSPC,

        LT(_FN1, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,
        KC_P, KC_LBRC, KC_RBRC, KC_BSLS,

        MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,
        KC_L, KC_SCLN, KC_QUOT, KC_ENT,

        KC_LSHIFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,
        KC_DOT, KC_SLSH, KC_RSHIFT, KC_NO,

        TG(_SE), MO(_FN2), KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_LEFT, KC_DOWN,
        KC_DOWN, KC_UP, KC_RGHT),

    /* SWE layer
     * .---------------------------------------------------------------------------------------.
     * |     |     |     |     |     |     |     |     |     |     |     |     |     |         |
     * |---------------------------------------------------------------------------------------+
     * |      |     |     |     |     |     |     |     |     |     |     |  Å  |     |        |
     * |---------------------------------------------------------------------------------------+
     * |       |     |     |     |     |     |     |     |     |     |  Ö  |  Ä  |             |
     * |---------------------------------------------------------------------------------------+
     * |        |     |     |     |     |     |     |     |     |     |     |                  |
     * |---------------------------------------------------------------------------------------+
     * |       |       |     |                                         |     |     |     |     |
     * '---------------------------------------------------------------------------------------'
     */
    [_SE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, RALT(KC_W), _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RALT(KC_P), RALT(KC_Q), _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______),

    /* FN layer 1
     * .---------------------------------------------------------------------------------------.
     * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |   Del   |
     * |---------------------------------------------------------------------------------------+
     * |      |     | VI_W|     |     |     |     |     | Ins |     |     |     |     |        |
     * |---------------------------------------------------------------------------------------+
     * |       |     |     |     |     |     | Left| Down|  Up |Right|     |     |             |
     * |---------------------------------------------------------------------------------------+
     * |        |     |     |     |     |     |     |     |     |  -> |     |                  |
     * |---------------------------------------------------------------------------------------+
     * |       |  Win  |     |                                         |     |     |     |     |
     * '---------------------------------------------------------------------------------------'
     */
    [_FN1] = LAYOUT(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9,
        KC_F10, KC_F11, KC_F12, _______, KC_DEL,

        _______, _______, M(VI_WRITE), _______, _______, _______, _______,
        _______, KC_INS, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,
        KC_UP, KC_RGHT, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, PMEMBER, _______, _______,

        _______, KC_LGUI, _______, _______, _______, _______, _______, _______,
        _______, _______, _______),

    /* FN layer 2
     * .---------------------------------------------------------------------------------------.
     * |  `  |TL(1)|TL(2)|TL(3)|TL(4)|TL(5)|TL(6)|TL(7)|TL(8)|TL(9)|TL(10|TL(11|TL(12|         |
     * |---------------------------------------------------------------------------------------+
     * |      |     |     |     |     |     |     |     |     |     |     |     |     |        |
     * |---------------------------------------------------------------------------------------+
     * |       |     |     |     |     |     | Home| PGDN| PGUP| End |     |     |  Play/Pause |
     * |---------------------------------------------------------------------------------------+
     * |        |     |     |     |     |     |     |     | Prev| Next|     |                  |
     * |---------------------------------------------------------------------------------------+
     * |       |       |     |                                         |Power|Sleep| Wake| Lock|
     * '---------------------------------------------------------------------------------------'
     */
    [_FN2] = LAYOUT(
        _______, TG(1), TG(2), TG(3), TG(4), TG(5), TG(6), TG(7), TG(8), TG(9),
        TG(10), TG(11), TG(12), _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,
        KC_PGUP, KC_END,  _______, _______, KC_MPLY,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_MPRV, KC_MNXT, _______, _______, _______,

        TG(_SYS), _______, _______, _______, _______, _______, KC_PWR, KC_SLEP,
        KC_SLEP, KC_WAKE, LGUI(KC_L)),

    /* System layer
     * .---------------------------------------------------------------------------------------.
     * |     |     |     |     |     |     |     |     |     |     |     |     |     |         |
     * |---------------------------------------------------------------------------------------+
     * |      | RGB | RGB | RGB | RGB | RGB | RGB | RGB | RGB |     |     |     |     |  Reset |
     * |---------------------------------------------------------------------------------------+
     * |       |     |     |     |     |     |     |     |     |     |     |     |             |
     * |---------------------------------------------------------------------------------------+
     * |        |     |     |     |     |     |     |     |     |     |     |                  |
     * |---------------------------------------------------------------------------------------+
     * |       |       |     |                                         |     |     |     |     |
     * '---------------------------------------------------------------------------------------'
     */
    [_SYS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,

        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI,
        RGB_VAD, _______, _______, _______, _______, RESET,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______),
};
