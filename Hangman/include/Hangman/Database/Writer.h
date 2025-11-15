#pragma once
#include <Hangman/Database/FileChecker.h>
#include <string>
#include <fstream>

namespace Messerli::Hangman::Database {
class Writer {
public:
    Writer(const std::wstring& path);
    bool AddWord(const std::wstring& word);
    bool AddWords(const std::wstring& word);
    bool AddWordsChanges(const std::wstring & word, const int i);
    bool AddWordChanges(const std::wstring & word, const int i);
    bool ClearEverthing();
private:
    const std::wstring& m_path;
    bool IsFileThere();
    bool IsOfstreamOkay(std::wofstream& file);
};

}