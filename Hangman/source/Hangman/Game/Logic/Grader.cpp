#include "Hangman/Game/Logic/Grader.h"

namespace Messerli::Hangman::Game::Logic {

bool Grader::GradeWords()
{
    Database::Reader reader;
    auto words = reader.GetWords(m_path);
    Data::ArrayInt listWithChanges = UpdateListWithWordChanges(words);
    bool firstHard = false;
    bool firstMiddel = false;
    bool firstEasy = false;
    for (int i = 0; i < listWithChanges.Count; i++) {
        if (listWithChanges.Words[i].length() > 6) {
            Database::Writer writer(m_pathHard);
            if (!Add(writer, firstHard, listWithChanges, i)) {
                return false;
            }
        } else if (listWithChanges.Words[i].length() > 4) {
            Database::Writer writer(m_pathMiddel);
            if (!Add(writer, firstMiddel, listWithChanges, i)) {
                return false;
            }
        } else {
            Database::Writer writer(m_pathEasy);
            if (!Add(writer, firstEasy, listWithChanges, i)) {
                return false;
            }
        }
    }
}

const Data::ArrayInt Grader::UpdateListWithWordChanges(Data::ArrayInt list)
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


Data::ArrayInt Grader::OverrideLocation(Data::ArrayInt array, int position)
{
    for (int i = position; i < array.Count; i++) {
        array.Words[i] = array.Words[i + 1];
    }
    return array;
}

bool Grader::Add(Database::Writer& writer, bool& firstWord, Data::ArrayInt list, const int i)
{
    if (!firstWord) {
        firstWord = true;
        if (!writer.AddWords(list.Words[i])) {
            return false;
        }
    } else {
        if (!writer.AddWord(list.Words[i])) {
            return false;
        }
    }
}

}