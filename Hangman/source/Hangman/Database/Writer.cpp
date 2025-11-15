#include "Hangman/Database/Writer.h"
#include <codecvt>

namespace Messerli::Hangman::Database {

Writer::Writer(const std::wstring& p) : m_path(p)
{

}

bool Writer::AddWord(const std::wstring& word)
{
    if (IsFileThere()) {
        std::wofstream file(m_path, std::ios::out | std::ios::app);
        file << word  << "\n";
        if (!IsOfstreamOkay(file)) {
            return false;
        }
        return true;
    }
    return false;

}

bool Writer::AddWords(const std::wstring& word)
{
    std::wofstream file(m_path);
    file << word << "\n";
    if (!IsOfstreamOkay(file)) {
        return false;
    }
    return true;
}

bool Writer::AddWordsChanges(const std::wstring& word, const int i)
{
    std::wofstream file(m_path);
    file << i << ":" << word << "\n";
    if (!IsOfstreamOkay(file)) {
        return false;
    }
    return true;
}

bool Writer::AddWordChanges(const std::wstring& word, const int i)
{
    if (IsFileThere()) {
        std::wofstream file(m_path, std::ios::out | std::ios::app);
        file << i << ":" << word << "\n";
        if (!IsOfstreamOkay(file)) {
            return false;
        }
        return true;
    }
    return false;

}

bool Database::Writer::ClearEverthing()
{
    if (IsFileThere()) {
        std::wofstream file(m_path, std::ios::out | std::ios::trunc);
        if (!IsOfstreamOkay(file)) {
            return false;
        }
        return true;
    }
    return false;
}

bool Writer::IsFileThere()
{
    if (!FileChecker::IsFileThere(m_path)) {
        return false;
    }
    return true;
}

bool Writer::IsOfstreamOkay(std::wofstream& file)
{
    if (file.fail()) {
        return false;
    }
    return true;
}

}