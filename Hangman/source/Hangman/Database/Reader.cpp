#include "Hangman/Database/Reader.h"
#include <codecvt>

namespace Messerli::Hangman::Database {

Data::ArrayInt Reader::GetWords(const std::wstring& path)
{    
    Data::ArrayInt Words {};
    if (!FileChecker::IsFileThere(path)) {
        return Words;
    }
    std::wifstream file(path);
    int i = 0;
    for (;i < 500; i++) {
        if (!std::getline(file, Words.Words[i])) break;
    }
    Words.Count = i;


    return Words;
}

}