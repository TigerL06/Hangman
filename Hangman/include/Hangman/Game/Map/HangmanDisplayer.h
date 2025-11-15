#pragma once
#include <string>
#include "Hangman/UI/Output.h"
#include "Hangman/UI/Input.h"

namespace Messerli::Hangman::Game::Map {

class HangmanDisplayer {
public:
    HangmanDisplayer(const UI::Output&, const UI::Input&);
    void Print(const int&);
private:
    const UI::Output& Output;
    const UI::Input& m_input;
};

}