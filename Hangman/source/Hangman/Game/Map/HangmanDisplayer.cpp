#include "Hangman/Game/Map/HangmanDisplayer.h"

namespace Messerli::Hangman::Game::Map {

HangmanDisplayer::HangmanDisplayer(const UI::Output& o, const UI::Input& i) : Output(o), m_input(i)
{

}
    
void HangmanDisplayer::HangmanDisplayer::Print(const int& n)
{
    switch (n) {
        case 0:
            Output.Print(L"\n\n\n\n\n\n");
            break;
        case 1:
            Output.Print(L"\n  \n  \n \n \n\n-------\n");
            break;
        case 2:
            Output.Print(L"\n|  \n|  \n| \n| \n|\n-------\n");
            break;
        case 3:
            Output.Print(L"_____\n|  |\n|  \n| \n| \n|\n-------\n");
            break;
        case 4:
            Output.Print(L"_____\n|  |\n|  o\n| \n|\n|\n-------\n");
            break;
        case 5:
            Output.Print(L"_____\n|  |\n|  o\n| / \n|\n-------\n");
            break;
        case 6:
            Output.Print(L"_____\n|  |\n|  o\n| /| \n|  \n|\n-------\n");
            break;
        case 7:
            Output.Print(L"_____\n|  |\n|  o\n| /|\\ \n|  \n|\n-------\n");
            break;
        case 8:
            Output.Print(L"_____\n|  |\n|  o\n| /|\\ \n| /  \n|\n-------\n");
            break;
        case 9:
            Output.Print(L"_____\n|  |\n|  o\n| /|\\ \n| / \\ \n|\n-------\n");
            break;
    }
}
}