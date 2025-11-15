#pragma once
#include <string>
#include "Hangman/UI/Output.h"
#include "Hangman/UI/Input.h"
#include "Hangman/Game/Logic/WordChecker.h"
#include "Hangman/Game/Logic/IdenticalUmlaut.h"
#include <Hangman/Data/Umlaute.h>

namespace Messerli::Hangman::Game::Map {

class WordTransformerUnderline {
public:
    WordTransformerUnderline(const UI::Output& o, const UI::Input& i, const int& lengthArray, const std::wstring& original_w, const std::wstring& replaced_w);
    void Print(const wchar_t(&array)[], const int(&Positions)[3], int Count);
private:
    const UI::Output& Output;
    const UI::Input& m_input;
    std::wstring m_original_word;
    std::wstring m_replaced_word;
    const int& lengthArray;
    Game::Logic::WordChecker checker;
    Data::Umlaut umlautTest;
    std::wstring m_wordDisplay;
};

}