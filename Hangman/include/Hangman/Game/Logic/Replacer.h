#pragma once
#include "Hangman/Data/Word.h"
#include <Hangman/Data/Umlaute.h>
#include <string>

namespace Messerli::Hangman::Game::Logic {

class Replacer {
public:
    std::wstring ReplaceUmlaut(std::wstring&, const int positions[3], int);
private:
    const Data::Umlaut m_umlaute;
    std::wstring MakeReplaceDecision(std::wstring& word, const int i) const;
};

}