#pragma once
namespace Messerli::Hangman::Data {

struct Umlaut {
    const int NumberUmlaute = 3;
    const wchar_t Umlaute[3] {
        L'ä', L'ö', L'ü'
    };
    const std::wstring UmlauteReplacer[3] {
        L"ae", L"oe", L"ue"
    };

};

}