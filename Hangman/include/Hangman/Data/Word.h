#pragma once
#include <string>

namespace Messerli::Hangman::Data {

struct Word {
    std::wstring Text;
    int Positions[3];
    int Count;
    bool HasUmlaut;
};

}
