#pragma once
#include "Hangman/UI/Input.h"
#include "Hangman/UI/Output.h"
#include <Hangman/Data/Word.h>
#include <Hangman/Game/Map/PlayField.h>
#include <Hangman/Game/Logic/Linguist.h>
#include <Hangman/Game/Logic/Replacer.h>
#include <Hangman/Game/Logic/WordChecker.h>
#include <Hangman/Game/Settings.h>

namespace Messerli::Hangman::Game::Logic {

class Logic {
public:
    Logic(Settings&);
    void Game();
private:
    const UI::Input& m_input;
    const UI::Output& m_output;
    const std::wstring m_word;
    const int m_level;
    Data::Word m_words;
    const Game::Map::PlayField field;
    void PrintNote();
    int MultipleLevel(int numberMistakes);
    Data::Word PutWordInStructure();
    bool HasLostOrHasGuessed(int count, int length, int numberMistakes);
    void CheckInput(int& count, int& numberMistakes, int& mistakes, int& guessedLetter, Data::CharBool answer, wchar_t(&lettersOfWordThatAreGuessed)[30]);
    bool IsLetterAlreadySet(wchar_t letter, const wchar_t(&lettersOfWordThatAreGuessed)[30], const int& count);
};

}