#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>

namespace Messerli::Hangman::UI {

class Output {
public:
    void Print(const std::wstring&) const;
    void Clear() const;
};

}