#include "keyboard.h"
#include "stdio.h"

KeyCode scode_to_key[] = 
{
    KeyCode::KEYNULL, KeyCode::ESC, KeyCode::ONE, KeyCode::TWO, KeyCode::THREE, KeyCode::FOUR,
    KeyCode::FIVE, KeyCode::SIX, KeyCode::SEVEN, KeyCode::EIGHT, KeyCode::NINE, 
    KeyCode::ZERO, KeyCode::DASH, KeyCode::EQUAL, KeyCode::BACK, KeyCode::TAB, 
    KeyCode::Q, KeyCode::W, KeyCode::E, KeyCode::R, KeyCode::T, KeyCode::Y, 
    KeyCode::U, KeyCode::I, KeyCode::O, KeyCode::P, KeyCode::SQBRACKO, KeyCode::SQBRACKCL, 
    KeyCode::ENTER, KeyCode::LCTRL, KeyCode::A, KeyCode::S, KeyCode::D, KeyCode::F, 
    KeyCode::G, KeyCode::H, KeyCode::J, KeyCode::K, KeyCode::L, KeyCode::SEMI, 
    KeyCode::QUOTE, KeyCode::GRAVE, KeyCode::LSHIFT, KeyCode::BACKSLASH, KeyCode::Z, KeyCode::X, 
    KeyCode::C, KeyCode::V, KeyCode::B, KeyCode::N, KeyCode::M, KeyCode::COMMA, 
    KeyCode::PERIOD, KeyCode::SLASH, KeyCode::RSHIFT, KeyCode::KEYNULL, KeyCode::LALT, KeyCode::SPACE, 
    KeyCode::CAPSLOCK
};

key ps2_keyboard::keys[] = {
    {KeyCode::KEYNULL},
    {KeyCode::A},
    {KeyCode::B},
    {KeyCode::C},
    {KeyCode::D},
    {KeyCode::E},
    {KeyCode::F},
    {KeyCode::G},
    {KeyCode::H},
    {KeyCode::I},
    {KeyCode::J},
    {KeyCode::K},
    {KeyCode::L},
    {KeyCode::M},
    {KeyCode::N},
    {KeyCode::O},
    {KeyCode::P},
    {KeyCode::Q},
    {KeyCode::R},
    {KeyCode::S},
    {KeyCode::T},
    {KeyCode::U},
    {KeyCode::V},
    {KeyCode::W},
    {KeyCode::X},
    {KeyCode::Y},
    {KeyCode::Z},
    {KeyCode::SPACE},
    {KeyCode::ONE},
    {KeyCode::TWO},
    {KeyCode::THREE},
    {KeyCode::FOUR},
    {KeyCode::FIVE},
    {KeyCode::SIX},
    {KeyCode::SEVEN},
    {KeyCode::EIGHT},
    {KeyCode::NINE},
    {KeyCode::ZERO},
    {KeyCode::GRAVE},
    {KeyCode::DASH},
    {KeyCode::EQUAL},
    {KeyCode::BACK},
    {KeyCode::SQBRACKO},
    {KeyCode::SQBRACKCL},
    {KeyCode::BACKSLASH},
    {KeyCode::SEMI},
    {KeyCode::QUOTE},
    {KeyCode::COMMA},
    {KeyCode::PERIOD},
    {KeyCode::SLASH},
    {KeyCode::LSHIFT},
    {KeyCode::RSHIFT},
    {KeyCode::LCTRL},
    {KeyCode::RCTRL},
    {KeyCode::LALT},
    {KeyCode::RALT},
    {KeyCode::ENTER},
    {KeyCode::RIGHT},
    {KeyCode::LEFT},
    {KeyCode::UP},
    {KeyCode::DOWN},
    {KeyCode::TAB},
    {KeyCode::ESC},
    {KeyCode::CAPSLOCK}
};

keychar key_char[] = 
{
    {0, 0},
    {'a', 'A'},
    {'b', 'B'},
    {'c', 'C'},
    {'d', 'D'},
    {'e', 'E'},
    {'f', 'F'},
    {'g', 'G'},
    {'h', 'H'},
    {'i', 'I'},
    {'j', 'J'},
    {'k', 'K'},
    {'l', 'L'},
    {'m', 'M'},
    {'n', 'N'},
    {'o', 'O'},
    {'p', 'P'},
    {'q', 'Q'},
    {'r', 'R'},
    {'s', 'S'},
    {'t', 'T'},
    {'u', 'U'},
    {'v', 'V'},
    {'w', 'W'},
    {'x', 'X'},
    {'y', 'Y'},
    {'z', 'Z'},
    {' ', ' '},
    {'1', '!'},
    {'2', '@'},
    {'3', '#'},
    {'4', '$'},
    {'5', '%'},
    {'6', '^'},
    {'7', '&'},
    {'8', '*'},
    {'9', '('},
    {'0', ')'},
    {'`', '~'},
    {'-', '_'},
    {'=', '+'},
    {' ', ' '},
    {'[', '{'},
    {']', '}'},
    {'\\', '|'},
    {';', ':'},
    {'\'', '\"'},
    {',', '<'},
    {'.', '>'},
    {'/', '?'},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

void ps2_keyboard::input_scancode(uint8_t scancode)
{
    if ((scancode & 0x7F) >= sizeof(scode_to_key)) return;
    ps2_keyboard::keys[(size_t) scode_to_key[scancode & 0x7F]].pressed = scancode < 0x80;
    ps2_keyboard::keys[(size_t) scode_to_key[scancode & 0x7F]].held = scancode < 0x80;
    ps2_keyboard::keys[(size_t) scode_to_key[scancode & 0x7F]].released = scancode > 0x80; 
    
    update_mods();
}

// Updates control keys such as ctrl, shift, and alt
void ps2_keyboard::update_mods()
{
    if (isHeld(KeyCode::LALT) || isHeld(KeyCode::RALT)) alt = 1;
    else alt = 0;

    if (isHeld(KeyCode::LCTRL) || isHeld(KeyCode::RCTRL)) control = 1;
    else control = 0;
    
    if (isHeld(KeyCode::LSHIFT) || isHeld(KeyCode::RSHIFT)) shift = 1;
    else shift = 0;

    if (isPressed(KeyCode::CAPSLOCK)) caps != caps;
}

ps2_keyboard keyboard;