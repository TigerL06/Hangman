#include "Hangman/UI/Output.h"

namespace Messerli::Hangman::UI {

    void Output::Print(const std::wstring& text) const
    {
        std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());
        std::wcout << text << L'\n';
    }

    void Output::Clear() const
    {
        std::wcout << L"\x1b[H\x1b[2J" << std::flush;
    }
}
