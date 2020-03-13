#include QMK_KEYBOARD_H


#define KB_IDLE_TIME_MS (60000u)


enum layers
{
    _US = 0,
    _SE,
    _DBG,
    _FN1,
    _FN2,
    _FN3,
    _SYS
};

enum custom_keycodes
{
    PMEMBER = SAFE_RANGE
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
    }

exit:
    return continue_proc;
};

layer_state_t layer_state_set_user(layer_state_t state)
{
    switch (get_highest_layer(state))
    {
        case _US:
            rgblight_sethsv_noeeprom_goldenrod();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _SE:
            rgblight_sethsv_noeeprom_blue();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
            break;
        case _FN1:
            rgblight_sethsv_noeeprom_orange();
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

    /* US qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  /   |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl |  GUI | Caps |  Alt | FN2  |    Space    |Layer1| Left | Down |  Up  |Right |
     * `-----------------------------------------------------------------------------------'
     */
    [_US] = LAYOUT_planck_mit(
        LT(_FN3, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,
        KC_P, KC_BSPC,

        MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,
        KC_L, KC_SCLN, KC_QUOT,

        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,
        KC_SLSH, KC_SFTENT,

        KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, MO(_FN2), KC_SPC, LT(_FN1, KC_ENT),
        KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),

    /* Swedish layer
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |   Å  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |   Ö  |   Ä  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_SE] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, RALT(KC_W),

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, RALT(KC_P), RALT(KC_Q),

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /* Debug layer
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |   Å  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |   Ö  |   Ä  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_DBG] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

    /* Function layer 1
     * ,-----------------------------------------------------------------------------------.
     * |   `  |  !   |  @   |  {   |  }   |  |   |  &   |  7   |  8   |  9   |  *   | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |  #   |  $   |  (   |  )   |      |  +   |  4   |  5   |  6   |  -   |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  %   |  ^   |  [   |  ]   |      |  0   |  1   |  2   |  3   |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
     * `-----------------------------------------------------------------------------------'
     */
    [_FN1] = LAYOUT_planck_mit(
        KC_GRV, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, KC_AMPR, KC_7, KC_8,
        KC_9, KC_ASTR, KC_DEL,

        _______, KC_HASH, KC_DOLLAR, KC_LPRN, KC_RPRN, KC_AMPR, KC_PLUS, KC_4,
        KC_5, KC_6, KC_MINUS, KC_BSLASH,

        _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, _______, KC_0, KC_1, KC_2,
        KC_3, _______, _______,

        RESET, _______, _______, _______, _______, _______, _______, KC_HOME,
        KC_PGDN, KC_PGUP, KC_END
    ),

    /* Function layer 2
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Left | Down |  Up  | Right|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_FN2] = LAYOUT_planck_mit(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_7, KC_8, KC_9, KC_MINUS,
        KC_PLUS, KC_F12,

        _______, _______, _______, _______, _______, _______, KC_4, KC_5,
        KC_6,  KC_EQUAL, KC_RIGHT, _______,

        _______, _______, _______, _______, _______, _______, KC_1, KC_2,
        KC_3, KC_3, KC_ASTR, _______,

        _______, _______, _______, TG(_SE), _______, KC_0, _______, _______,
        _______, _______, _______
    ),

    /* Function layer 2
     * ,-----------------------------------------------------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Left | Down |  Up  | Right|      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_FN3] = LAYOUT_planck_mit(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_7, KC_8, KC_9, KC_MINUS,
        KC_PLUS, KC_F12,

        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,
        KC_UP, KC_RIGHT, KC_RIGHT, _______,

        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,
        KC_PGUP, KC_END, KC_ASTR, _______,

        _______, _______, _______, TG(_SE), _______, KC_0, _______, _______,
        _______, _______, _______
    )
};


