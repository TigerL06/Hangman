#pragma once
#include "Hangman/UI/Output.h"
#include "Hangman/UI/Input.h"
#include <string>

namespace Messerli::Hangman::Game::Map {

class PlayField {
public:
    PlayField(const UI::Output&, const UI::Input&);
    void Print(const std::wstring& original_word, const std::wstring&, const int&, const wchar_t(&array)[], const int&, const int(&Positions)[3], const int Count)const;
private:
    const UI::Output& Output;
    const UI::Input& m_input;
};

}