#pragma once
#include "Hangman/UI/Input.h"
#include "Hangman/UI/Output.h"
#include "Hangman/Editor/WordsEditor.h"
#include "Hangman/Menu/Menu.h"
#include "Hangman/Game/Settings.h"
#include "Hangman/Game/Logic/Logic.h"
#include "Hangman/Data/IntBool.h"

namespace Messerli::Hangman {

class HangmanApp {
public:
    HangmanApp(const UI::Output& o, const UI::Input& i);
    void Start();
private:
    const UI::Output& m_output;
    const UI::Input& m_input;
    Menu::Menu m_menu;
    void StartGame();
    int LevelOfGame();
    bool EditorChoice(const int number);
    char GetLetter();
    bool AskIfNewGame();
    std::wstring GetWord();
    void ProgramChoice();
    void Editor();

};

}