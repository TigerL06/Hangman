#include "Hangman/Menu/Menu.h"
#include "Hangman/Game/Logic/Logic.h"
#include <Hangman/Game/Settings.h>

namespace Messerli::Hangman::Menu {

Menu::Menu(const UI::Output& o) : m_output(o)
{

}
void Menu::PrintMenu()
{
    m_output.Clear();
    m_output.Print(L"Was wollen Sie ausfuehren?\n");
    m_output.Print(L"1. Editor \n");
    m_output.Print(L"2. Hangman \n");
    m_output.Print(L"Geben Sie 1 oder 2 ein. \n");
}


void Menu::PrintLevels()
{        
    m_output.Print(L"Auf welchem Schwierigkeitsgrad wollen Sie Hangman spielen? \n");
    m_output.Print(L"1.Leicht\n");
    m_output.Print(L"2.Mittel \n");
    m_output.Print(L"3.Schwer \n");
}

void Menu::PrintEditorMenu()
{        
    m_output.Print(L"Was wollen Sie mit den Wörtern machen?\n");
    m_output.Print(L"1. Alle Datenanzeigen.\n");
    m_output.Print(L"2. Worte nach einem Buchstaben suchen.\n");
    m_output.Print(L"3. Ein Wort hinzufügen.\n");
    m_output.Print(L"4. Ein Wort verändern.\n");
    m_output.Print(L"5. Ein Wort löschen.\n");

}


void Menu::DisplayWords(Data::ArrayInt Words)
{
    for (int i = 0; i < Words.Count; i++) {
        m_output.Print(Words.Words[i]);
        m_output.Print(L"\n");
    }
}


}