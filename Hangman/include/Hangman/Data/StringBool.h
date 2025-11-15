#pragma once
#include <string>

namespace Messerli::Hangman::Data {

// ToDo Struct zu Klasse mit Zugriefsmethoden
struct StringBool {
    std::wstring Text;
    bool IsNull;
};

}