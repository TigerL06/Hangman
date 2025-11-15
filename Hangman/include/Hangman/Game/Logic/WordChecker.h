#pragma once
#include "Hangman/Data/Word.h"
#include <Hangman/Data/StringBool.h>
#include <Hangman/Data/Umlaute.h>
#include <Hangman/Data/StringIntBool.h>
#include <Hangman/Game/Logic/IdenticalUmlaut.h>
#include <string>


namespace Messerli::Hangman::Game::Logic {

class WordChecker {
public:
    Data::StringIntBool CheckIfLetterIsInWord(const Data::Word& words, const std::wstring word, const wchar_t letter);

};

}