// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#define DEBUG_SERIAL false

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope.h"

#include "LED-Off.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
#include "Kaleidoscope-Model01-TestMode.h"

#define MACRO_VERSION_INFO 1
#define Macro_VersionInfo M(MACRO_VERSION_INFO)
#define MACRO_ANY 2
#define Macro_Any M(MACRO_ANY)
#define MACRO_LED_OFF 3

#define GENERIC_FN2  KEYMAP_STACKED ( \
___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,         \
Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE, \
Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,                   \
Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE, \
                                            Key_LeftControl, Key_Delete, Key_LeftGui, Key_LeftShift,  \
                                                                ___,   \
\
Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                  Key_F9,          Key_F10,          Key_F11, \
Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,   Key_LeftBracket, Key_RightBracket, Key_F12, \
                            Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,             Key_RightArrow,  ___,              ___, \
Key_PcApplication,          Key_Mute,               Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,            Key_Backslash,    Key_Pipe, \
Key_RightShift, Key_RightAlt, Key_Enter, Key_RightControl, \
___ \
)


// Left hand for switching LEDS & keymaps
// Right hand for numpad
#define NUMPAD KEYMAP_STACKED  (\
    ___,          Key_Keymap1, Key_Keymap2, Key_Keymap4, Key_Keymap5, ___, ___, \
    M(4), M(5), M(6), M(7), M(8), M(9), M(MACRO_LED_OFF),       \
    M(10), M(11), M(13), M(14), ___, ___,                       \
    ___, ___, ___, ___, ___, ___, Key_LEDEffectNext,        \
    ___, ___, ___, ___,         \
                          ___,     \
\
\
    Macro_VersionInfo,  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___, \
    ___, ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___, \
         ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote, \
    ___, ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter, \
    ___, ___, ___, ___, \
    Key_Keymap3_Momentary \
)

// Move punctuation for the case when OS is set to Dvorak
#define LINUX_LAPTOP KEYMAP_STACKED ( \
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_Keymap4_Momentary, \
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,           \
    Key_Minus,   Key_A, Key_S, Key_D, Key_F, Key_G,                    \
    Key_Equals, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_RightControl,        \
    Key_Backspace, Key_LeftAlt, Key_LeftGui, Key_LeftShift,         \
                          Key_Keymap3_Momentary,     \
\
    Key_Keymap4_Momentary,       Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_RightBracket, \
    Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_LeftBracket,       \
                   Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,       \
    Key_Escape,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Backslash,       \
    Key_RightShift, Key_PrintScreen, Key_RightAlt, Key_Spacebar,                    \
    Key_Keymap3_Momentary \
)

// When OS is set to Dvorak, and I have mapped mods for emacs
#define MAC_LAPTOP KEYMAP_STACKED ( \
    ___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_Keymap4_Momentary, \
    Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,           \
    Key_Minus,   Key_A, Key_S, Key_D, Key_F, Key_G,                    \
    Key_Equals, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_LeftGui,        \
    Key_Backspace, Key_LeftControl, Key_LeftAlt, Key_LeftShift,         \
                          Key_Keymap3_Momentary,     \
\
    Key_Keymap4_Momentary,       Key_6, Key_7, Key_8,     Key_9,      Key_0,         Key_RightBracket, \
    Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_LeftBracket,       \
                   Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,       \
    Key_Escape,  Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Backslash,       \
    Key_RightShift, Key_RightAlt, Key_RightControl, Key_Spacebar,       \
    Key_Keymap3_Momentary \
)


// When OS is set to Qwerty, say for pairing with someone
#define DVORAK KEYMAP_STACKED ( \
    ___,          ___,___,___,___,___,___, \
    ___, Key_Quote, Key_Comma, Key_Period, Key_P, Key_Y, ___,                   \
    Key_LeftBracket,   Key_A, Key_O, Key_E, Key_U, Key_I,                    \
    Key_RightBracket, Key_Semicolon, Key_Q, Key_J, Key_K, Key_X, Key_LeftGui, \
___,___,___,___,         \
                          ___,     \
\
    ___,       ___, ___, ___,     ___,      ___,         Key_Equals, \
    ___,     Key_F, Key_G, Key_C,     Key_R,      Key_L,         Key_Slash,       \
                   Key_D, Key_H, Key_T,     Key_N,      Key_S, Key_Minus,       \
    ___,  Key_B, Key_M, Key_W, Key_V, Key_Z,     ___,       \
    ___, ___, ___, ___,       \
    ___ \
)

// Move punctuation back for the case when OS is set to Qwerty
#define QWERTY_PUNCTUATION KEYMAP_STACKED ( \
    ___,          ___, ___, ___, ___, ___, ___, \
    ___, ___, ___, ___, ___, ___, ___,           \
    Key_PageUp,   ___, ___, ___, ___, ___,                    \
    Key_PageDown, ___, ___, ___, ___, ___, ___,        \
    ___, ___, ___, ___,         \
                          ___,     \
\
    ___,       ___, ___, ___,     ___,      ___,         Key_Keymap4, \
    ___,     ___, ___, ___,     ___,      ___,         Key_Equals,       \
                   ___, ___, ___,     ___,      ___, ___,       \
    ___,  ___, ___, ___, ___, ___,     Key_Minus,       \
    ___, ___, ___, ___,                   \
    ___ \
)

// Move mods back to default layout
#define STOCK_MODS KEYMAP_STACKED ( \
    ___,          ___, ___, ___, ___, ___, ___, \
    ___, ___, ___, ___, ___, ___, ___,           \
    ___,   ___, ___, ___, ___, ___,                    \
    ___, ___, ___, ___, ___, ___, Key_Escape,        \
    Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,         \
                          ___,     \
\
    ___,       ___, ___, ___,     ___,      ___,         ___, \
    ___,     ___, ___, ___,     ___,      ___,         ___,       \
                   ___, ___, ___,     ___,      ___, ___,       \
    Key_RightAlt,  ___, ___, ___, ___, ___,     ___,       \
    Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,                   \
    ___ \
)

const Key keymaps[][ROWS][COLS] PROGMEM = {
  LINUX_LAPTOP,
  QWERTY_PUNCTUATION,
  STOCK_MODS,
  GENERIC_FN2,
  NUMPAD,
  DVORAK
};

static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  if (macroIndex == 1 && keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  } else if (macroIndex == MACRO_ANY) {
    static Key lastKey;
    if (keyToggledOn(keyState))
      lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

    if (keyIsPressed(keyState))
      kaleidoscope::hid::pressKey(lastKey);
  } else if (macroIndex == MACRO_LED_OFF &&keyToggledOn(keyState)) {
       LEDOff.activate();
  } else if (keyToggledOn(keyState)) {
       LEDControl.set_mode(macroIndex - MACRO_LED_OFF - 1);
  }
  return MACRO_NONE;
}

void setup() {
  Kaleidoscope.setup(KEYMAP_SIZE);
  BootKeyboard.begin();
  Kaleidoscope.use(
    &BootGreetingEffect,
    &TestMode,
    &LEDControl, &LEDOff,
    &LEDRainbowEffect, &LEDRainbowWaveEffect, &LEDChaseEffect,
    &solidRed, &solidOrange, &solidYellow, &solidGreen, &solidBlue, &solidIndigo, &solidViolet,
    &LEDBreatheEffect,
    &AlphaSquareEffect,
    &StalkerEffect,
    &Macros,
    &MouseKeys,
    NULL);

  AlphaSquare.color = { 255, 0, 0 };
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);
  StalkerEffect.variant = STALKER(BlazingTrail);
  LEDOff.activate();
}


void loop() {
  Kaleidoscope.loop();
}
