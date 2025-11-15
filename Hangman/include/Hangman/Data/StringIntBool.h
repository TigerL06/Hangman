#pragma once
#include <string>

namespace Messerli::Hangman::Data {

struct StringIntBool {
    std::wstring Text;
    int Count;
    bool IsNull;
};

}