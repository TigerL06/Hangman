#pragma once
#include "Hangman/UI/Output.h"
#include "Hangman/UI/Input.h"
#include "Hangman/Data/ArrayInt.h"
#include "Hangman/Database/FileChecker.h"
#include <Hangman/Database/Reader.h>
#include <Hangman/Database/Writer.h>

namespace Messerli::Hangman::Editor {

class WordsEditor {
public:
    const Data::ArrayInt GetWords();
    const Data::ArrayInt GetWord(const char letter);
    bool AddWord(const std::wstring& word);
    bool UpdateWord(const std::wstring& word, const std::wstring& newWord);
    bool DeletWord(const std::wstring& words);
private:
    const std::wstring m_path = L"res/Words.txt";
    const std::wstring m_pathChanges = L"res/LocalWords.txt";
    Data::ArrayInt m_words;
    bool AddWords(const auto& list, const int(&Positions)[500]);
    const Data::ArrayInt UpdateListWithWordChanges(Data::ArrayInt list);
    Data::ArrayInt OverrideLocation(Data::ArrayInt array, int position);
};

}