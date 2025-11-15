#include "Hangman/Game/Map/WordTransformerUnderline.h"
#include <cwctype>

namespace Messerli::Hangman::Game::Map {

WordTransformerUnderline::WordTransformerUnderline(const UI::Output& o, const UI::Input& i, const int& lengthArray, const std::wstring& original_w, const std::wstring& replaced_w)
    : Output(o), m_input(i), lengthArray(lengthArray), m_original_word(original_w), m_replaced_word(replaced_w)
{
}

void WordTransformerUnderline::Print(const wchar_t(&Letter)[], const int(&Positions)[3], int Count)
{
    const int MAX_WORD_LENGTH = 50;
    bool isVisible[MAX_WORD_LENGTH] = {false};

    if (m_replaced_word.length() >= MAX_WORD_LENGTH) {
        Output.Print(L"Fehler: Wort ist zu lang.\n");
        return;
    }

    for (int i = 0; i < lengthArray; ++i) {
        wchar_t guessed_letter = std::towlower(Letter[i]);

        for (int k = 0; k < m_replaced_word.length(); ++k) {
            if (m_replaced_word[k] == guessed_letter) {
                isVisible[k] = true;
            }
        }

        for (int k = 0; k < Count; ++k) {
            int original_pos = Positions[k];
            wchar_t original_umlaut = m_original_word[original_pos];

            if (Messerli::Hangman::Game::Logic::IdenticalUmlaut::IsSameUmlaut(guessed_letter, original_umlaut)) {
                int replaced_pos = original_pos + k;
                isVisible[replaced_pos] = true;
                isVisible[replaced_pos + 1] = true;
            }
        }
    }

    std::wstring final_output = L"";
    for (int i = 0; i < m_replaced_word.length(); ++i) {
        if (isVisible[i]) {
            final_output += m_replaced_word[i];
        } else {
            final_output += L'_';
        }
    }

    Output.Print(final_output);
    Output.Print(L"\n");
}

}