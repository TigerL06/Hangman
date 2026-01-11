#include "Hangman/UI/Input.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cwctype>
#include <stdexcept>

#define NOMINMAX
#include <Windows.h>

namespace
{
    // Warum so viele Hilfsfunktionen? -> Weil Windows je nach Umgebung (echte Konsole vs. IDE/Redirect), Codepage (CP850/CP1252/UTF-8) und Stream-Typ (wcin/cin) sehr unterschiedlich mit Umlauten umgeht; deshalb kapsele ich Erkennung, Lesen (Console-UTF16 oder Fallback-Bytes) und Konvertierung getrennt, um in beiden Fällen zuverlässig Unicode zu bekommen.

    bool IsRealConsoleInput()
    {
        DWORD mode = 0;
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
        return (hIn != INVALID_HANDLE_VALUE) && (hIn != nullptr) && GetConsoleMode(hIn, &mode);
    }

    std::wstring ReadConsoleLineW()
    {
        HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

        std::wstring out;
        std::vector<wchar_t> buf(256);

        while (true)
        {
            DWORD read = 0;
            BOOL ok = ReadConsoleW(hIn, buf.data(), static_cast<DWORD>(buf.size()), &read, nullptr);
            if (!ok || read == 0)
            {
                return L"";
            }

            out.append(buf.data(), buf.data() + read);

            if (out.find(L'\n') != std::wstring::npos)
                break;

        }

        const size_t cut = out.find_first_of(L"\r\n");
        if (cut != std::wstring::npos)
            out.resize(cut);

        return out;
    }

    std::wstring ConvertBytesToWide(const std::string& s, UINT cp, DWORD flags)
    {
        if (s.empty()) return L"";

        int needed = MultiByteToWideChar(cp, flags, s.data(), static_cast<int>(s.size()), nullptr, 0);
        if (needed <= 0) return L"";

        std::wstring w(static_cast<size_t>(needed), L'\0');
        MultiByteToWideChar(cp, flags, s.data(), static_cast<int>(s.size()), w.data(), needed);
        return w;
    }

    std::wstring ReadLineFallback()
    {
        std::string bytes;
        if (!std::getline(std::cin >> std::ws, bytes))
            return L"";

        std::wstring w = ConvertBytesToWide(bytes, CP_UTF8, MB_ERR_INVALID_CHARS);

        if (w.empty() && !bytes.empty())
            w = ConvertBytesToWide(bytes, GetConsoleCP(), 0);

        if (w.empty() && !bytes.empty())
            w = ConvertBytesToWide(bytes, CP_ACP, 0);

        return w;
    }

    std::wstring ReadLineRobust()
    {
        return IsRealConsoleInput() ? ReadConsoleLineW() : ReadLineFallback();
    }

    wchar_t FirstNonSpaceChar(const std::wstring& s)
    {
        size_t i = 0;
        while (i < s.size() && iswspace(s[i])) ++i;
        return (i < s.size()) ? s[i] : L'\0';
    }
}

namespace Messerli::Hangman::UI
{
    Messerli::Hangman::Data::StringBool Input::Get() const
    {
        std::wstring word = ReadLineRobust();

        if (word.empty())
            return { L"", false };

        return { word, true };
    }

    Data::CharBool Input::GetLetter() const
    {
        std::wstring line = ReadLineRobust();
        if (line.empty())
            return Data::CharBool{ L'-', false };

        wchar_t letter = FirstNonSpaceChar(line);
        if (letter == L'\0')
            return Data::CharBool{ L'-', false };

        return Data::CharBool{ letter, true };
    }

    Data::IntBool Input::GetNumber() const
    {
        std::wstring line = ReadLineRobust();
        if (line.empty())
            return Data::IntBool{ 0, false };

        try
        {
            size_t idx = 0;
            int n = std::stoi(line, &idx, 10);

            for (; idx < line.size(); ++idx)
            {
                if (!iswspace(line[idx]))
                    return Data::IntBool{ 0, false };
            }

            return Data::IntBool{ n, true };
        }
        catch (...)
        {
            return Data::IntBool{ 0, false };
        }
    }
}
