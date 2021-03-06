#include QMK_KEYBOARD_H


#define KB_IDLE_TIME_MS (60000u)


enum layers
{
    _US = 0,
    _SE,
    _DBG,
    _CHAR,
    _NUM,
    _NAV,
    _SYS
};

enum custom_keycodes
{
    PMEMBER = SAFE_RANGE,
    IS_EQUAL,
    NOT_EQUAL,
    GRT_EQUAL,
    LT_EQUAL
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
    rgblight_sethsv_noeeprom_goldenrod();
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
        case IS_EQUAL:
            if (record->event.pressed)
            {
                SEND_STRING("==");
            }
            break;
        case NOT_EQUAL:
            if (record->event.pressed)
            {
                SEND_STRING("!=");
            }
            break;
        case GRT_EQUAL:
            if (record->event.pressed)
            {
                SEND_STRING(">=");
            }
            break;
        case LT_EQUAL:
            if (record->event.pressed)
            {
                SEND_STRING("<=");
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
            rgblight_sethsv_noeeprom_teal();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _CHAR:
            rgblight_sethsv_noeeprom_orange();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _NUM:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            break;
        case _NAV:
            rgblight_sethsv_noeeprom_springgreen();
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
        LT(_NAV, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,

        MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,

        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_SFTENT,

        TG(_SE), KC_LGUI, KC_LGUI, KC_LALT, LT(_NUM, KC_BSPC), KC_SPC, LT(_CHAR, KC_ENT),
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
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
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

    /* Left hand special characters
     * ,-----------------------------------------------------------------------------------.
     * |   `  |  !   |  @   |  {   |  }   |  |   |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |  #   |  $   |  %   |  (   |  )   |  &   |      |      |      |      |      |  \   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |  ^   |  &   |  *   |  [   |  ]   |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
     * `-----------------------------------------------------------------------------------'
     */
    [_CHAR] = LAYOUT_planck_mit(
        KC_GRV, KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______,
        _______, _______, _______,

        KC_HASH, KC_DOLLAR, KC_PERC, KC_LPRN, KC_RPRN, KC_AMPR, _______, _______,
        _______, _______, _______, KC_BSLASH,

        KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, _______, _______, _______,
        LT_EQUAL, GRT_EQUAL, _______, _______,

        KC_EQUAL, IS_EQUAL, NOT_EQUAL, _______, _______, _______, _______, KC_HOME,
        KC_PGDN, KC_PGUP, KC_END
    ),

    /* Right hand numbers
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |  7   |  8   |  9   |  -   |  +   |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |  4   |  5   |  6   |  =   |  =   |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |  1   |  2   |  3   |  *   |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |  0   |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_NUM] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, KC_7,
        KC_8, KC_9, KC_MINUS, KC_PLUS,

        _______, _______, _______, _______, _______, _______, _______, KC_4,
        KC_5, KC_6, KC_EQUAL, KC_EQUAL,

        _______, _______, _______, _______, _______, _______, _______, KC_1,
        KC_2, KC_3, KC_ASTR, _______,

        TG(_SYS), _______, _______, TG(_SE), _______, _______, KC_0, _______,
        _______, _______, _______
    ),

    /* Function layer 2
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |Insert|      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |      |      |      |      |      | Home | PgDn | PgUp | End  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |RCtrl |
     * `-----------------------------------------------------------------------------------'
     */
    [_NAV] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS, _______,
        _______, KC_DEL,

        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN,
        KC_UP, KC_RIGHT, _______, _______,

        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN,
        KC_PGUP, KC_END, _______, _______,

        _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_RCTL
    )
};


