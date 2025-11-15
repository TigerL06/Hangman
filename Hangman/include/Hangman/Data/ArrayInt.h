#pragma once
#include <string>

namespace Messerli::Hangman::Data {

struct ArrayInt {
    static const int maxWords = 600;
    std::wstring Words[maxWords];
    int Count;
};

}