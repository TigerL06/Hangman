#pragma once
#include "Hangman/Data/Word.h"
#include "Hangman/Data/Umlaute.h"
#include <string>
#include <algorithm>
#include <cctype>

namespace Messerli::Hangman::Game::Logic {

class Linguist {
public:
    Data::Word CreateWordStructure(const std::wstring& m_word) const;
private:
    const Data::Umlaut m_umlaute;

};

}