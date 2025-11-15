#pragma once
#include "Hangman/UI/Input.h"
#include "Hangman/UI/Output.h"
#include "Hangman/Editor/WordsEditor.h"
namespace Messerli::Hangman::Menu {

class Menu {
public:
    Menu(const UI::Output& o);
    void PrintMenu();
    void PrintEditorMenu();
    void PrintLevels();
    void DisplayWords(Data::ArrayInt Words);

private:
    const UI::Output& m_output;

};

}