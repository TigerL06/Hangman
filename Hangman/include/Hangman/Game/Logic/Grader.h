#pragma once
#include <Hangman/Database/Reader.h>
#include <Hangman/Database/Writer.h>
#include <string>

namespace Messerli::Hangman::Game::Logic {
class Grader {
public:
    bool GradeWords();
private:
    const std::wstring m_pathHard = L"res/Hard.txt";
    const std::wstring m_pathMiddel = L"res/Middel.txt";
    const std::wstring m_pathEasy = L"res/Easy.txt";
    const std::wstring m_path = L"res/Words.txt";
    const std::wstring m_pathChanges = L"res/LocalWords.txt";
    bool Add(Database::Writer& writer, bool& firstWord, Data::ArrayInt list, const int i);
    const Data::ArrayInt UpdateListWithWordChanges(Data::ArrayInt list);
    Data::ArrayInt OverrideLocation(Data::ArrayInt array, int position);

};
}