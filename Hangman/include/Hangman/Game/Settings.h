#pragma once
#include <Hangman/UI/Input.h>
#include <Hangman/UI/Output.h>
#include "Hangman/Database/Reader.h"
#include <Hangman/Game/Logic/Grader.h>
#include <Hangman/Data/Umlaute.h>
#include <cstdlib>
#include <ctime>

namespace Messerli::Hangman::Game {

class Settings {
public:
    Settings(const UI::Input& i, const UI::Output& o, const int& l);
    const UI::Output& Output()const;
    const UI::Input&  Input()const;
    const int& Level()const;
    const std::wstring& Word() const;
private:
    const UI::Input& m_input;
    const UI::Output& m_output;
    const int& m_level;
    std::wstring m_word;    
    std::wstring GetWord();
    int RandomNumber(int max);
    std::wstring m_path;
    Game::Logic::Grader m_grader;
};

}