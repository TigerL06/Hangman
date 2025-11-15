#pragma once
#include "Hangman/Database/FileChecker.h"
#include "Hangman/Data/ArrayInt.h"
#include <string>
#include <array>

namespace Messerli::Hangman::Database {

class Reader {
public:
    Hangman::Data::ArrayInt GetWords(const std::wstring& path);
};

}