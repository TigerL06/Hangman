#include "Hangman/Game/Logic/WordChecker.h"
#include <cwctype>

namespace Messerli::Hangman::Game::Logic {

Data::StringIntBool WordChecker::CheckIfLetterIsInWord(const Data::Word& words,
    const std::wstring word,
    const wchar_t letter)
{
    std::wstring outputLetter = L"";
    int count = 0;

    wchar_t lowerCaseLetter = std::towlower(letter);

    for (int i = 0; i < (int)words.Text.length(); ++i) {
        if (words.Text[i] == letter) {
            ++count;
            outputLetter = std::wstring(1, letter);
            continue;
        }
        for (int j = 0; j < words.Count; ++j) {
            const int pos = words.Positions[j];
            if (i != pos) continue;

            if (IdenticalUmlaut::IsSameUmlaut(letter, word[pos])) {
                count += 2;
                outputLetter = letter;
            }
            break;
        }
    }

    if (count > 0) {
        return Data::StringIntBool {outputLetter, count, true};
    }
    return Data::StringIntBool {outputLetter, 0, false};
}


}