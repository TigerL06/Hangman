#include "Hangman/UI/Input.h"
#include <iostream>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include <limits>

namespace Messerli::Hangman::UI{

Messerli::Hangman::Data::StringBool Input::Get() const
{
    std::string word_utf8;
    if (!std::getline(std::cin >> std::ws, word_utf8)) {
        const size_t bufferSize = 1000;
        std::cin.clear();
        std::cin.ignore(bufferSize, '\n');
        return Data::StringBool {L"", false};
    }
    std::wstring word;
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, word_utf8.c_str(), (int)word_utf8.length(), NULL, 0);

    if (size_needed > 0) {
        word.resize(size_needed);
        MultiByteToWideChar(CP_UTF8, 0, word_utf8.c_str(), (int)word_utf8.length(), &word[0], size_needed);
    }

    if (word.empty() && !word_utf8.empty()) {
        return Data::StringBool {L"", false};
    }

    return {word, true};
}
Data::CharBool Input::GetLetter() const
{
    std::string s_utf8;
    if (!std::getline(std::cin >> std::ws, s_utf8)) {
        const size_t bufferSize = 1000;
        std::cin.clear();
        std::cin.ignore(bufferSize, '\n');
        return Data::CharBool {L'-', false};
    }
    std::wstring w;
    int size_needed = MultiByteToWideChar(CP_UTF8, 0,
        s_utf8.c_str(), (int)s_utf8.length(),
        NULL, 0);
    if (size_needed <= 0) {
        return Data::CharBool {L'-', false};
    }
    w.resize(size_needed);
    MultiByteToWideChar(CP_UTF8, 0,
        s_utf8.c_str(), (int)s_utf8.length(),
        &w[0], size_needed);

    if (w.empty()) {
        return Data::CharBool {L'-', false};
    }

    return Data::CharBool {w[0], true};
}
Data::IntBool Input::GetNumber() const
{
    int Number;
    std::cin >> Number;
    if (std::cin.fail()) {
        const size_t bufferSize = 1000;
        std::cin.clear();
        std::cin.ignore(bufferSize, '\n');
        return Data::IntBool {0, false};
    }
    return Data::IntBool {Number, true};
}

}