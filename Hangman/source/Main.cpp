#include "Hangman/HangmanApp.h"
#include <locale>

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::locale::global(std::locale(""));
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());    
    const Messerli::Hangman::UI::Output m_output;
    const Messerli::Hangman::UI::Input m_input;
    Messerli::Hangman::HangmanApp game(m_output, m_input);
    game.Start();
    return 0;
}


