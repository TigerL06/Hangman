#include "Hangman/Editor/WordsEditor.h"
#include "Hangman/Data/Word.h"

namespace Messerli::Hangman::Editor {
const Data::ArrayInt WordsEditor::GetWords()
{
    Database::Reader reader;
    auto words = reader.GetWords(m_path);
    Data::ArrayInt list = UpdateListWithWordChanges(words);
    return list;
}
const Data::ArrayInt WordsEditor::GetWord(const char letter)
{
    wchar_t s = tolower(letter);
    m_words.Count = 0;
    auto list = GetWords();;
    for (int i = 0; i < list.Count; i++) {
        for (int j = 0; j < list.Words[i].length(); j++) {
            if (s == list.Words[i][j]) {
                m_words.Words[m_words.Count] = list.Words[i];
                m_words.Count++;
            }
        }
    }
    return m_words;
}

const Data::ArrayInt WordsEditor::UpdateListWithWordChanges(Data::ArrayInt list)
{
    Database::Reader reader;
    auto listChanges = reader.GetWords(m_pathChanges);
    if (listChanges.Count <= 0) {
        return list;
    }
    int numberOfDeletedElement = 0;
    for (int i = 0; i < listChanges.Count; i++) {
        int p = listChanges.Words[i].find(':');
        if (p == std::string::npos) continue;

        int number = 0;
        try {
            number = std::stoi(listChanges.Words[i].substr(0, p));
        } catch (...) {
            continue;
        }

        if (number < 0 || number >= 500) continue;

        std::wstring Text = listChanges.Words[i].substr(p + 1);

        if (Text == L"") {
            list = OverrideLocation(list, number);
            numberOfDeletedElement++;
            list.Count--;
        } else {
            int effectiveIndex;
            if (number < list.Count - numberOfDeletedElement) {
                effectiveIndex = number;
                list.Words[effectiveIndex] = Text;
            } else {
                effectiveIndex = number - numberOfDeletedElement;
                list.Words[effectiveIndex] = Text;
            }
            if (effectiveIndex + 1 > list.Count) {
                list.Count = effectiveIndex + 1;
            }
        }
    }
    return list;
}
bool WordsEditor::AddWord(const std::wstring& word)
{
    Database::Writer writer(m_pathChanges);
    Database::Reader reader;
    auto originalList = GetWords();
    int nextAvailableIndex = originalList.Count;

    auto listChanges = reader.GetWords(m_pathChanges);

    if (listChanges.Count == 0) {
        if (writer.AddWordsChanges(word, nextAvailableIndex)) {
            return true;
        }
    } else {
        if (writer.AddWordChanges(word, nextAvailableIndex)) {
            return true;
        }
    }

    return false;
}
bool WordsEditor::UpdateWord(const std::wstring& word, const std::wstring& newWord)
{
    auto list = GetWords();
    Data::ArrayInt listChanges;
    int positions[500];
    int countChanges = 0;
    for (int i = 0; i < list.Count; i++) {
        if (word == list.Words[i]) {
            listChanges.Words[countChanges] = newWord;
            positions[countChanges] = i;
            countChanges++;
        }
    }
    listChanges.Count = countChanges;
    if (AddWords(listChanges, positions)) {
        return true;
    }
    return false;
}
bool WordsEditor::DeletWord(const std::wstring& word)
{    
    Database::Reader reader;
    auto list = GetWords();
    Data::ArrayInt listChanges;
    int Positions[500];
    int countChanges = 0;
    for (int i = 0; i < list.Count; i++) {
        if (word == list.Words[i]) {
            listChanges.Words[countChanges] = L"";
            Positions[countChanges] = i;
            countChanges++;
        }

    }
    listChanges.Count = countChanges;
    if (AddWords(listChanges, Positions)) {
        return true;
    }    
    return false;
}

Data::ArrayInt WordsEditor::OverrideLocation(Data::ArrayInt array, int position)
{
    for (int i = position; i < array.Count; i++) {
        array.Words[i] = array.Words[i+1];
    }
    return array;
}

bool WordsEditor::AddWords(const auto& list, const int (&Positions)[500])
{
    Database::Writer writer(m_pathChanges);
    Database::Reader reader;
    auto listChanges = reader.GetWords(m_pathChanges);
    for (int i = 0; i < list.Count; i++) {
        if (listChanges.Count == 0) {
            if (!writer.AddWordsChanges(list.Words[i], Positions[i])) {
                return false;
            }
        } else {
            if (!writer.AddWordChanges(list.Words[i], Positions[i])) {
                return false;
            }
        }
    }
    return true;

}


}
