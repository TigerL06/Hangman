#pragma once
#include <iostream>
#include "Hangman/Data/StringBool.h"
#include "Hangman/Data/IntBool.h"
#include "Hangman/Data/CharBool.h"

namespace Messerli::Hangman::UI {

class Input {
public:
    Messerli::Hangman::Data::StringBool Get() const;
    Messerli::Hangman::Data::CharBool GetLetter() const;
    Messerli::Hangman::Data::IntBool GetNumber() const;
};

}