#include "Hangman/Game/Logic/Linguist.h"
#include <cwctype>

namespace Messerli::Hangman::Game::Logic {

Data::Word Linguist::CreateWordStructure(const std::wstring& word) const
{
    std::wstring s = word;
    std::transform(s.begin(), s.end(), s.begin(),
        [](wchar_t c) { return std::towlower(c); });

    int Positions[3] {};
    bool HasUmlaut = false;
    int Count = 0;

    for (int i = 0; i < (int)s.length(); ++i) {
        for (int ii = 0; ii < m_umlaute.NumberUmlaute; ++ii) {
            if (s[i] == m_umlaute.Umlaute[ii]) {
                Positions[Count++] = i;
                HasUmlaut = true;
            }
        }
    }
    return Data::Word {s, {Positions[0], Positions[1], Positions[2]}, Count, HasUmlaut};
}

}