#include "Hangman/Game/Map/PlayField.h"
#include <Hangman/Game/Map/HangmanDisplayer.h>
#include <Hangman/Game/Map/WordTransformerUnderline.h>

namespace Messerli::Hangman::Game::Map {

PlayField::PlayField(const UI::Output& o, const UI::Input& i) : Output(o), m_input(i)
{

}
void PlayField::Print(const std::wstring& original_word, const std::wstring& m_word, const int& n, const wchar_t (&letterIsVisibale)[], const int& lengthArray, const int(&Positions)[3], const int Count)const
{
    HangmanDisplayer displayer(Output, m_input);
    displayer.Print(n);
    WordTransformerUnderline Words(Output, m_input, lengthArray, original_word,m_word);
    Words.Print(letterIsVisibale, Positions, Count);
}

}