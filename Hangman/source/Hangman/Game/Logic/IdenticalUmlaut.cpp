#include "Hangman/Game/Logic/IdenticalUmlaut.h"
#include <cwctype>

namespace Messerli::Hangman::Game::Logic::IdenticalUmlaut {
bool IsUmlaut(wchar_t c)
{
    c = std::towlower(c);
    return (c == L'ä' || c == L'ö' || c == L'ü');
}

bool IsSameUmlaut(wchar_t c, wchar_t uml)
{
    c = std::towlower(c);
    uml = std::towlower(uml);

    if (!(uml == L'ä' || uml == L'ö' || uml == L'ü')) return false;
    return c == uml;

}
}