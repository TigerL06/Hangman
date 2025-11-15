#pragma once
#include <string>
#include <fstream>

namespace Messerli::Hangman::Database::FileChecker {
bool IsFileThere(const std::wstring& path);

}