#pragma once

enum KeyCode
{
    KEYNULL, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, SPACE, // ABC's
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, // Numbers
    GRAVE, DASH, EQUAL, BACK, SQBRACKO, SQBRACKCL, BACKSLASH, SEMI, QUOTE, COMMA, PERIOD, SLASH, // Util
    LSHIFT, RSHIFT, LCTRL, RCTRL, LALT, RALT, ENTER, RIGHT, LEFT, UP, DOWN, TAB, ESC, CAPSLOCK// Control
};

struct key
{
    KeyCode code;
    bool pressed;
    bool held; 
    bool released;

    constexpr key(KeyCode code) 
        : code(code), pressed(0), held(0), released(0)
    {

    }
};

struct keychar
{
    char lower;
    char upper;
};

class ps2_keyboard
{
    // Stores map of keys, if they are currently pressed or not, and if they have been queried for pressed or released
private:
    static key keys[];
public:
    // Some flags for control
    bool alt;
    bool control;
    bool shift;
    bool caps;

    void input_scancode(uint8_t scancode);
    void update_mods();

    inline bool isPressed(KeyCode code)
    {
        bool retval = keys[(size_t) code].pressed;
        keys[(size_t) code].pressed = 0;
        return retval;
    }

    inline bool isHeld(KeyCode code)
    {
        return keys[(size_t) code].held;
    }

    inline bool isReleased(KeyCode code)
    {
        bool retval = keys[(size_t) code].released;
        keys[(size_t) code].released = 0;
        return retval;
    }
};

extern ps2_keyboard keyboard;
extern keychar key_char[];