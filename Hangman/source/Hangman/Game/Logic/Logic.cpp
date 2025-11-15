#include "Hangman/Game/Logic/Logic.h"
#include "Hangman/Game/Logic/IdenticalUmlaut.h"
#include <cwctype>

namespace Messerli::Hangman::Game::Logic {
Logic::Logic(Settings& setting) : m_input(setting.Input()), m_output(setting.Output()), field(m_output, m_input), m_word(setting.Word()), m_level(setting.Level())
{
}

void Logic::Game()
{    
    const std::wstring original_lowercase_word = m_word;
    m_words = PutWordInStructure();
    const int length = m_words.Text.size();
    int numberMistakes = 0;
    wchar_t lettersOfWordThatAreGuessed[30];
    int count = 0;
    int mistakes = 0;
    int guessedLetter = 0;
    PrintNote();
    while(true){
        field.Print(original_lowercase_word, m_words.Text, mistakes, lettersOfWordThatAreGuessed, count, m_words.Positions, m_words.Count);
        m_output.Print(L"\n");
        m_output.Print(L"Welchen Buchstaben wollen Sie eingeben\n");
        Data::CharBool answer = m_input.GetLetter();
        if (!answer.IsNull) {
            continue;
        }
        if (!IsLetterAlreadySet(std::towlower(answer.Letter), lettersOfWordThatAreGuessed, count)) {
            CheckInput(count, numberMistakes, mistakes, guessedLetter, answer, lettersOfWordThatAreGuessed);

            if (HasLostOrHasGuessed(guessedLetter, length, mistakes)) {
                field.Print(original_lowercase_word, m_words.Text, mistakes, lettersOfWordThatAreGuessed, count, m_words.Positions, m_words.Count);
                return;
            }
        }
    }

}

void Logic::PrintNote()
{
    m_output.Print(L"Ein Wort mit Umlaut wird mit oe, ae oder ue angezeigt. Man kann es aber mit den Umlauten erraten.\n");
    m_output.Print(L"Beispiel:\n");
    m_output.Print(
        L"Das Wort „Löwe“ wird intern als „Loewe“ gespeichert.\n"
        L"So wirkt sich die Eingabe auf die Anzeige aus:\n"
        L"- Eingabe „ö“           -> _oe__\n"
        L"- Eingabe „o“, dann „e“ -> _oe_e\n");
}
bool Logic::IsLetterAlreadySet(wchar_t Letter, const wchar_t(&lettersOfWordThatAreGuessed)[30], const int& count)
{
    for (int i = 0; i < count; i++) {
        if (Letter == lettersOfWordThatAreGuessed[i]) {
            m_output.Print(L"Sie können nicht zweimal die gleiche eingabe machen.\n");
            return true;
        }
    }
    return false;
}
void Logic::CheckInput(int& count, int& numberMistakes, int& mistakes, int& guessedLetter, Data::CharBool answer, wchar_t(&lettersOfWordThatAreGuessed)[30])
{
    wchar_t letterAsWideChar = std::towlower((wchar_t)answer.Letter);

    WordChecker checker;
    auto testedAnswer = checker.CheckIfLetterIsInWord(m_words, m_word, letterAsWideChar);

    if (!testedAnswer.IsNull) {
        numberMistakes++;
        mistakes = MultipleLevel(numberMistakes);

    } else {
        lettersOfWordThatAreGuessed[count] = answer.Letter;
        count++;
        for (int u = 0; u < m_words.Count; ++u) {
            const int pos = m_words.Positions[u];

            // Wurde dieser Umlaut früher (in einem vorherigen Zug) geraten?
            bool umlautBereitsGeraten = false;
            for (int j = 0; j < count - 1; ++j) { // -1: aktuelle Eingabe ausschließen
                if (Messerli::Hangman::Game::Logic::IdenticalUmlaut::IsSameUmlaut(
                    lettersOfWordThatAreGuessed[j], m_word[pos])) { // vergleicht echte Umlaute
                    umlautBereitsGeraten = true;
                    break;
                }
            }
            if (!umlautBereitsGeraten) continue;

            const wchar_t guess = std::towlower(answer.Letter);
            const wchar_t first = m_words.Text[pos];                      // a/o/u
            const wchar_t second = (pos + 1 < (int)m_words.Text.size())
                ? m_words.Text[pos + 1] : L'\0';        // e
            if (guess == first || guess == second) {
                testedAnswer.Count--;
            }
        }
        guessedLetter += testedAnswer.Count;
    }
}

bool Logic::HasLostOrHasGuessed(int count, int length, int numberMistakes)
{
    if (count >= length) {
        m_output.Print(L"Sie haben das Wort erraten. \n");
        m_output.Print(L"Wort: " + m_word + L"\n");
        return true;
    } else if (numberMistakes == 9) {
        m_output.Print(L"Sie haben verloren.\n");
        m_output.Print(L"Das Wort war " + m_word + L".\n");
        return true;
    }
    return false;
}


Data::Word Logic::PutWordInStructure()
{
    Linguist converter;
    Data::Word m_words {converter.CreateWordStructure(m_word)};
    if (m_words.HasUmlaut) {
        Replacer replace;
        m_words.Text = replace.ReplaceUmlaut(m_words.Text, m_words.Positions, m_words.Count);
    }
    return m_words;
}

int Logic::MultipleLevel(int numberMistakes)
{
    int result = m_level * numberMistakes;
    if (result == 10) {
        return 9;
    }
    return result;
}

}