#include "Hangman/Database/FileChecker.h"

namespace Messerli::Hangman::Database::FileChecker {

bool IsFileThere(const std::wstring& path)
{
    std::wifstream file(path);
    if (!file) {
        return false;
    }
    return true;
}

}