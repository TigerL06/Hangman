#include "Hangman/Game/Settings.h"
#include <codecvt>

namespace Messerli::Hangman::Game {
Settings::Settings(const UI::Input& i, const UI::Output& o, const int& l) : m_input(i), m_output(o), m_level(l)
{
    m_grader.GradeWords();
    switch (l) {
        case 1:
            m_path = L"res/Easy.txt";
            break;
        case 2:
            m_path = L"res/Middel.txt";
            break;
        case 3:
            m_path = L"res/Hard.txt";
            break;
    }
    m_word = GetWord();
}
const UI::Output& Settings::Output()const
{
    return m_output;
}
const UI::Input& Settings::Input()const
{
    return m_input;
}
const int& Settings::Level()const
{
    return m_level;
}
const std::wstring& Settings::Word()const
{
    return m_word;
}
std::wstring Settings::GetWord()
{
    Database::Reader reader;
    Data::ArrayInt Count = reader.GetWords(m_path);
    int max = Count.Count;
    int i = RandomNumber(max);
    return Count.Words[i];
}

int Settings::RandomNumber(int max)
{
    srand(time(NULL));
    return rand() % max;
}

}