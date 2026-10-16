/*
ファームウェアを書き込むコマンド
```
cd ~/keyboards/keyball61/qmk
make keyball/keyball61:my-keymap:flash
```
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// キーの配置は cline46 の CLine46.keymap とそろえている。

// スクロールキー（マウスレイヤーの U, I, O, K）
// - 短く押すと決まった回数だけスクロールし、長く押すと押している間スクロールし続ける
// - 速さは config.h の SCROLL_* で調整する
enum custom_keycodes {
    SCR_UP = KEYBALL_SAFE_RANGE,
    SCR_DN,
    SCR_LT,
    SCR_RT,
};

// Keyball61 はトラックボールが右手側にあるため、右手側の下段中央3つにはスイッチが無いため XXXXXXX にしている。

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // 文字入力
  //   Q の左: 単押しで Tab、長押しで Option
  //   左右の Shift: 素早く2回押すと Caps Lock
  //   A の左: 単押しで Esc、長押しで Ctrl
  //   左親指の Space の左隣: 単押しで英数、長押しで Option
  //   左親指の Space の右隣: Cmd
  //   C の下: 押している間レイヤー4（設定）
  //   右下の2キー: 音量
  [0] = LAYOUT_universal(
    _______        , KC_1       , KC_2       , KC_3          , KC_4              , KC_5            ,                                   KC_6          , KC_7          , KC_8       , KC_9    , KC_0    , _______ ,
    LALT_T(KC_TAB) , KC_Q       , KC_W     , KC_E          , KC_R              , KC_T            ,                                   KC_Y          , KC_U          , KC_I       , KC_O    , KC_P    , KC_BSPC ,
    LCTL_T(KC_ESC) , KC_A       , KC_S       , KC_D          , KC_F              , KC_G            ,                                   KC_H          , KC_J          , KC_K       , KC_L    , KC_MINS , KC_ENT  ,
    KC_LSFT        , KC_Z       , KC_X       , KC_C          , KC_V              , KC_B            , _______       , _______         , KC_N          , KC_M          , KC_COMM    , KC_DOT  , KC_SLSH , KC_RSFT ,
    _______        , _______    , _______    , MO(4)         , LALT_T(KC_LNG2)   , LT(1,KC_SPC)    , KC_LGUI       , KC_RGUI         , LT(2,KC_LNG1) , XXXXXXX       , XXXXXXX    , XXXXXXX , KC_VOLD , KC_VOLU
  ),
  // 数字と移動
  //   右手: 数字（テンキーと同じ並び）と + -
  //   左手: 矢印
  //   Q: カーソルの左の1単語を削除（Option+Backspace）  T: カーソルの右の1単語を削除（Option+Delete）
  //   右下の2キー: 画面の明るさ
  [1] = LAYOUT_universal(
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , _______       , _______    , _______ , _______ , _______ ,
    _______        , A(KC_BSPC) , A(KC_LEFT) , KC_UP         , A(KC_RGHT)        , A(KC_DEL)       ,                                   _______       , KC_7          , KC_8       , KC_9    , KC_PLUS , _______ ,
    _______        , G(KC_LEFT) , KC_LEFT    , KC_DOWN       , KC_RGHT           , G(KC_RGHT)      ,                                   _______       , KC_4          , KC_5       , KC_6    , KC_MINS , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , KC_0          , KC_1          , KC_2       , KC_3    , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , _______       , XXXXXXX       , XXXXXXX    , XXXXXXX , KC_BRID , KC_BRIU
  ),
  // 記号
  // 英語の呼び名の頭文字などで位置を決めている
  //   Q ' quote         W " w-quote    E = equal      R ^ raised to the power of   T ~ tilde
  //   A @ at            S * star       D $ dollar     G ` grave
  //   X ! eXclamation   C : colon      V | vertical   B \ backslash
  //   H # hash          N & 'n (and)   M % mod        P + plus
  [2] = LAYOUT_universal(
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , _______       , _______    , _______ , _______ , _______ ,
    _______        , KC_QUOT    , KC_DQUO    , KC_EQL        , KC_CIRC           , KC_TILD         ,                                   _______       , KC_LPRN       , KC_RPRN    , _______ , KC_PLUS , _______ ,
    _______        , KC_AT      , KC_ASTR    , KC_DLR        , _______           , KC_GRV          ,                                   KC_HASH       , KC_LBRC       , KC_RBRC    , _______ , _______ , _______ ,
    _______        , _______    , KC_EXLM    , KC_SCLN       , KC_PIPE           , KC_BSLS         , _______       , _______         , KC_AMPR       , KC_PERC       , _______    , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , _______       , XXXXXXX       , XXXXXXX    , XXXXXXX , _______ , _______
  ),
  // マウス（オートマウスレイヤー）
  //   I: 画面が下にスクロール  K: 画面が上にスクロール
  //   U: 画面が右にスクロール  O: 画面が左にスクロール
  //      ※ Mac の「ナチュラルなスクロール」を有効にしていると、スクロール方向と移動する向きが逆になる
  //   J: 左クリック  L: 右クリック
  //   J と K の同時押し: 戻る  K と L の同時押し: 進む（key_combos で設定）
  //   U と I の同時押し: タブを閉じる（Cmd+W）  I と O の同時押し: 新しいタブ（Cmd+T）（key_combos で設定）
  [3] = LAYOUT_universal(
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , _______       , _______    , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , SCR_RT        , SCR_DN     , SCR_LT  , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , KC_BTN1       , SCR_UP     , KC_BTN2 , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , _______       , _______       , _______    , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , _______       , XXXXXXX       , XXXXXXX    , XXXXXXX , _______ , _______
  ),
  // 設定（Keyball の設定。このレイヤーを押している間はスクロールモードになる）
  //   右手: Keyball の設定キー。左手の親指でこのレイヤーに入ったまま、右手で押す
  //     N: 設定を保存  M ,: カーソルの速さ（100 ずつ）  J K: カーソルの速さ（1000 ずつ）
  //     U I: ボールでのスクロールの速さ
  //     ほかの Keyball の設定キーは、押しても働かないか、オートマウスレイヤーを止めてしまうので置いていない
  //   P の右隣: EEPROM を消す
  [4] = LAYOUT_universal(
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , _______       , _______    , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , SCRL_DVI      , SCRL_DVD   , _______ , _______ , EE_CLR  ,
    _______        , _______    , _______    , _______       , _______           , _______         ,                                   _______       , CPI_I1K       , CPI_D1K    , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , KBC_SAVE      , CPI_I100      , CPI_D100   , _______ , _______ , _______ ,
    _______        , _______    , _______    , _______       , _______           , _______         , _______       , _______         , _______       , XXXXXXX       , XXXXXXX    , XXXXXXX , _______ , _______
  ),
};
// clang-format on

// 同時押し（マウスレイヤー）
// - キーの位置ではなく、マウスレイヤーに置いたキーコードの組み合わせで決める
// - 同時に押したと判定する時間は config.h の COMBO_TERM
const uint16_t PROGMEM back_combo[]      = {KC_BTN1, SCR_UP, COMBO_END};  // J + K: 戻る
const uint16_t PROGMEM forward_combo[]   = {SCR_UP, KC_BTN2, COMBO_END};  // K + L: 進む
const uint16_t PROGMEM close_tab_combo[] = {SCR_RT, SCR_DN, COMBO_END};   // U + I: タブを閉じる
const uint16_t PROGMEM new_tab_combo[]   = {SCR_DN, SCR_LT, COMBO_END};   // I + O: 新しいタブ

combo_t key_combos[] = {
    COMBO(back_combo, KC_BTN4),
    COMBO(forward_combo, KC_BTN5),
    COMBO(close_tab_combo, G(KC_W)),
    COMBO(new_tab_combo, G(KC_T)),
};

// A の左の Ctrl/Esc キーは、別のキーを押した時点で Ctrl にする
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return keycode == LCTL_T(KC_ESC);
}

// A の左の Ctrl/Esc キーは、Esc を押した直後に押し直しても Esc を押し続けず、Ctrl にする
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return keycode == LCTL_T(KC_ESC) ? 0 : QUICK_TAP_TERM;
}

// 起動(ケーブルの抜き差し)のたびにオートマウスレイヤーを有効にする
// Kb 10でオートマウスレイヤーをOFFにしてもケーブルを抜き差しするともとに戻る
void keyboard_post_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    set_auto_mouse_enable(true);
    // keyball.c の keyboard_post_init_kb() は EEPROM に保存された値でタイムアウトを上書きする。
    // その保存領域は 5bit(最大 1600ms 相当)しかなく AUTO_MOUSE_TIME の 10000 を保てないので、
    // 後から呼ばれるこの関数で毎回 config.h の値に戻す
    set_auto_mouse_timeout(AUTO_MOUSE_TIME);
#endif
}

// Shift の有無で送る文字を入れ替える共通処理
static bool swap_shift(uint8_t plain, uint16_t shifted, keyrecord_t *record) {
    if (record->event.pressed) {
        uint8_t mods = get_mods();
        if (mods & MOD_MASK_SHIFT) {
            // Shift を一時的に外して、素のキーコードを送る
            del_mods(MOD_MASK_SHIFT);
            send_keyboard_report();
            tap_code(plain);
            set_mods(mods);
            send_keyboard_report();
        } else {
            // Shift なしのときに、Shift 付きの文字を送る
            tap_code16(shifted);
        }
    }
    return false;   // 既定の処理はさせない
}

// Shift を押してから TAPPING_TERM 以内に同じ Shift をもう一度押すと、Caps Lock を切り替える
// cline46 の lshift_caps / rshift_caps と同じ動きにしている
static uint16_t shift_first_keycode    = KC_NO;
static uint16_t shift_first_press_time = 0;
// 1回目の Shift を、ほかのキーを押さずに離したか
static bool     shift_tapped           = false;
// Shift を押してから、ほかのキーを押していないか
static bool     shift_alone            = false;

static void caps_lock_on_double_shift(uint16_t keycode, keyrecord_t *record) {
    if (keycode != KC_LSFT && keycode != KC_RSFT) {
        if (record->event.pressed) {
            shift_tapped = false;
            shift_alone  = false;
        }
        return;
    }
    if (!record->event.pressed) {
        shift_tapped = shift_alone;
        shift_alone  = false;
        return;
    }
    if (shift_tapped && keycode == shift_first_keycode && timer_elapsed(shift_first_press_time) < TAPPING_TERM) {
        // tap_code() は KC_CAPS を TAP_HOLD_CAPS_DELAY（80ms）押してから離す。Mac は短すぎると反応しないため
        tap_code(KC_CAPS);
        shift_tapped = false;
        return;
    }
    shift_first_keycode    = keycode;
    shift_first_press_time = timer_read();
    shift_alone            = true;
}

// スクロールキーの状態
// 押しているスクロールキーの向き。押していないときは両方 0
static int8_t   scroll_hold_h       = 0;
static int8_t   scroll_hold_v       = 0;
static uint16_t scroll_pressed_time = 0;
// 長押しで次にスクロールする時刻
static uint16_t scroll_hold_next    = 0;
// 短く押したときに、まだ送っていないスクロールの回数と向き
static uint8_t  scroll_tap_left     = 0;
static int8_t   scroll_tap_h        = 0;
static int8_t   scroll_tap_v        = 0;
static uint16_t scroll_tap_next     = 0;

static void scroll_key_event(int8_t h, int8_t v, keyrecord_t *record) {
    if (record->event.pressed) {
        scroll_hold_h       = h;
        scroll_hold_v       = v;
        scroll_pressed_time = timer_read();
        // TAPPING_TERM を過ぎてから長押しのスクロールを始める
        scroll_hold_next = scroll_pressed_time + TAPPING_TERM + 1000 / SCROLL_HOLD_COUNT_PER_SEC;
        return;
    }
    // 別のスクロールキーを後から押していたときは、そちらを優先する
    if (h != scroll_hold_h || v != scroll_hold_v) {
        return;
    }
    scroll_hold_h = 0;
    scroll_hold_v = 0;
    if (timer_elapsed(scroll_pressed_time) >= TAPPING_TERM) {
        return;
    }
    // 短く押したとき
    // 前のタップのスクロールが残っていて向きが違うときは、残りを捨てる
    if (scroll_tap_left > 0 && (h != scroll_tap_h || v != scroll_tap_v)) {
        scroll_tap_left = 0;
    }
    // 1回目はすぐにスクロールする
    if (scroll_tap_left == 0) {
        scroll_tap_next = timer_read();
    }
    scroll_tap_h = h;
    scroll_tap_v = v;
    scroll_tap_left += SCROLL_TAP_COUNT;
}

// スクロールキーの分のスクロール量を、トラックボールのレポートに足す
report_mouse_t pointing_device_task_user(report_mouse_t report) {
    uint16_t now = timer_read();
    if (scroll_tap_left > 0 && timer_expired(now, scroll_tap_next)) {
        report.h += scroll_tap_h;
        report.v += scroll_tap_v;
        scroll_tap_left--;
        scroll_tap_next += SCROLL_TAP_INTERVAL;
    }
    if ((scroll_hold_h != 0 || scroll_hold_v != 0) && timer_expired(now, scroll_hold_next)) {
        report.h += scroll_hold_h;
        report.v += scroll_hold_v;
        scroll_hold_next += 1000 / SCROLL_HOLD_COUNT_PER_SEC;
    }
    return report;
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
// スクロールキーを押している間は、オートマウスレイヤーを抜けさせない
bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SCR_UP ... SCR_RT:
            return true;
    }
    return false;
}

// オートマウスレイヤーを抜けさせたくないキーを、今いくつ押しているか
static int8_t aml_held_keys = 0;

// 押している間はオートマウスレイヤーを抜けさせないキーか
// KC_BTN1 でのドラッグ、スクロールキーでのスクロール
static bool is_aml_held_key(uint16_t keycode, keyrecord_t *record) {
    return is_mouse_record_kb(keycode, record) || IS_MOUSEKEY(keycode);
}

// マウスレイヤー（レイヤー3）に割り当てたキー以外を押したら、すぐにオートマウスレイヤーから抜ける。
// QMK のデフォルトでは修飾キーや S(KC_LEFT) のようなキーを押しても抜けないので、それらでも抜けるようにしている。
static void aml_exit_on_other_key(uint16_t keycode, keyrecord_t *record) {
    if (is_aml_held_key(keycode, record)) {
        if (record->event.pressed) {
            aml_held_keys++;
        } else if (aml_held_keys > 0) {
            aml_held_keys--;
        }
        return;
    }
    if (!record->event.pressed || aml_held_keys > 0) {
        return;
    }
    // TG(3) を押したときのレイヤーの切り替えは QMK に任せる
    if (IS_QK_TOGGLE_LAYER(keycode) && QK_TOGGLE_LAYER_GET_LAYER(keycode) == AUTO_MOUSE_DEFAULT_LAYER) {
        return;
    }
    // マウスレイヤーに割り当てたキーでは抜けない
    // 同時押しで出したキーにはキーの位置がないので、この判定はしない。
    // そのため、同時押しの Cmd+W や Cmd+T を押すとマウスレイヤーから抜ける
    if (IS_KEYEVENT(record->event) && layer_switch_get_layer(record->event.key) == AUTO_MOUSE_DEFAULT_LAYER) {
        return;
    }
    // TG(3) で入っているときは、この関数の中で何もしない作りになっている
    auto_mouse_layer_off();
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    aml_exit_on_other_key(keycode, record);
#endif
    caps_lock_on_double_shift(keycode, record);
    switch (keycode) {
        case KC_SCLN:                                  // 単押し ':' / Shift ';'
            return swap_shift(KC_SCLN, KC_COLN, record);
        case SCR_UP:
            scroll_key_event(0, 1, record);
            return false;
        case SCR_DN:
            scroll_key_event(0, -1, record);
            return false;
        case SCR_LT:
            scroll_key_event(-1, 0, record);
            return false;
        case SCR_RT:
            scroll_key_event(1, 0, record);
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // 設定レイヤー（レイヤー4）にいる間はスクロールモードにする。
    // マウスレイヤー（レイヤー3）より上にあるので、マウスレイヤーに同時に入ってもスクロールモードのまま
    keyball_set_scroll_mode(get_highest_layer(state) == 4);
    return state;
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    include <stdlib.h>

// AML_ENTER_THRESHOLD と AML_ENTER_RESET_MS は config.h で定義している

static int16_t  aml_travel    = 0;
static uint16_t aml_last_move = 0;

// レイヤーに入っていない間だけ移動量を足し込み、合計がしきい値に達したときに入る
bool auto_mouse_activation(report_mouse_t mouse_report) {
    // ボタンを押している間は必ずレイヤーを維持する
    if (mouse_report.buttons) {
        aml_travel = 0;
        return true;
    }

    int16_t delta = abs(mouse_report.x) + abs(mouse_report.y) + abs(mouse_report.h) + abs(mouse_report.v);

    // すでにレイヤーに入っているときは QMK の既定と同じ判定にする。
    // ここでもしきい値を課すと、ゆっくり動かしている最中にレイヤーが抜ける。
    if (layer_state_is(get_auto_mouse_layer())) {
        aml_travel = 0;
        return delta > 0;
    }

    if (delta == 0) {
        if (timer_elapsed(aml_last_move) > AML_ENTER_RESET_MS) {
            aml_travel = 0;
        }
        return false;
    }

    aml_last_move = timer_read();
    aml_travel += delta;
    if (aml_travel >= AML_ENTER_THRESHOLD) {
        aml_travel = 0;
        return true;
    }
    return false;
}
#endif

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
