#include "Hangman/Game/Logic/Replacer.h"

namespace Messerli::Hangman::Game::Logic {

std::wstring Replacer::ReplaceUmlaut(std::wstring& word, const int positions[3], int count)
{
    for (int i = count - 1; i >= 0; --i) {
        MakeReplaceDecision(word, positions[i]);
    }
    return word;
}

std::wstring Replacer::MakeReplaceDecision(std::wstring& word, const int i) const
{
    if (word[i] == m_umlaute.Umlaute[0]) {
        return word.replace(i, 1, m_umlaute.UmlauteReplacer[0]);
    } else if (word[i] == m_umlaute.Umlaute[1]) {
        return word.replace(i, 1, m_umlaute.UmlauteReplacer[1]);
    } else if (word[i] == m_umlaute.Umlaute[2]) {
        return word.replace(i, 1, m_umlaute.UmlauteReplacer[2]);
    }
}

}

