#include "Hangman/HangmanApp.h"

namespace Messerli::Hangman {

HangmanApp::HangmanApp(const UI::Output& o, const UI::Input& i) : m_output(o), m_input(i), m_menu(m_output)
{

}
void HangmanApp::Start()
{
    ProgramChoice();


    if (!AskIfNewGame()) {
        Start();
    }
}


void HangmanApp::Editor()
{
    bool testIfNewRound = false;
    while (!testIfNewRound) {
        m_menu.PrintEditorMenu();
        Messerli::Hangman::Data::IntBool answer = m_input.GetNumber();
        if (!answer.IsNull) {
            m_output.Print(L"Falsche Eignabe\n");
        } else {
            if (!EditorChoice(answer.Number)) {
                m_output.Print(L"Unbekannte Eingabe.\n");
            } else {
                testIfNewRound = AskIfNewGame();
            }
        }
    }

}


int HangmanApp::LevelOfGame()
{
    while (true) {
        m_menu.PrintLevels();
        Data::IntBool answer = m_input.GetNumber();
        if (!answer.IsNull) {
            m_output.Print(L"Falsche Eignabe\n");
        } else {
            switch (answer.Number) {
                case 1:
                case 2:
                case 3:
                    return answer.Number;
                default:
                    m_output.Print(L"Unbekannte Eingabe.\n");
            }
        }
    }
}
void HangmanApp::ProgramChoice()
{
    while (true) {
        m_menu.PrintMenu();
        Messerli::Hangman::Data::IntBool answer = m_input.GetNumber();
        if (answer.IsNull) {
            switch (answer.Number) {
                case 1:
                    Editor();
                    return;
                case 2:
                    StartGame();
                    return;
                default:
                    const size_t bufferSize = 1000;
                    std::cin.clear();
                    std::cin.ignore(bufferSize, '\n');
                    m_output.Print(L"Falsche Eigabe.\n");
                    break;
            }
        } else {
            m_output.Print(L"Unbekannte Ausgabe\n");
        }
    }
}

void HangmanApp::StartGame()
{
    int m_level = LevelOfGame();
    Messerli::Hangman::Game::Settings setting(m_input, m_output, m_level);
    Messerli::Hangman::Game::Logic::Logic logic(setting);
    logic.Game();
}
bool HangmanApp::EditorChoice(const int number)
{
    bool everythingIsfine = false;

    Messerli::Hangman::Editor::WordsEditor editor;
    switch (number) {
        case 1:
            m_menu.DisplayWords(editor.GetWords());
            break;
        case 2:
            m_output.Print(L"Geben Sie ihr Buchstabe ein:");
            m_menu.DisplayWords(editor.GetWord(GetLetter()));
            break;
        case 3:
            while (!everythingIsfine) {
                m_output.Print(L"Geben Sie ihr Wort ein: ");
                std::wstring m_word = GetWord();
                if (editor.AddWord(m_word)) {
                    everythingIsfine = true;
                }
            }
            break;
        case 4:
            while (!everythingIsfine) {
                m_output.Print(L"Geben Sie das Wort ein, welches Sie verändern wollen: ");
                std::wstring m_word = GetWord();
                m_output.Print(L"Geben Sie das neue Wort ein: ");
                std::wstring newWord = GetWord();
                if (editor.UpdateWord(m_word, newWord)) {
                    everythingIsfine = true;
                }
            }
            break;
        case 5:
            while (!everythingIsfine) {
                m_output.Print(L"Geben Sie das Wort ein, welches Sie löschen wollen: ");
                if (editor.DeletWord(GetWord())) {
                    everythingIsfine = true;
                }
            }
            break;
        default:
            return false;
    }
    return true;
}
std::wstring HangmanApp::GetWord()
{
    while (true) {
        Messerli::Hangman::Data::StringBool answer = m_input.Get();
        if (!answer.IsNull) {
            m_output.Print(L"Falsche Eignabe\n");
        } else {
            return answer.Text;
        }
    }
    return L"";
}
char HangmanApp::GetLetter()
{
    while (true) {
        Messerli::Hangman::Data::CharBool answer = m_input.GetLetter();
        if (!answer.IsNull) {
            m_output.Print(L"Falsche Eignabe\n");
        } else {
            return answer.Letter;
        }
    }
    return '-';

}

bool HangmanApp::AskIfNewGame()
{
    bool correct = false;
    while (!correct) {
        m_output.Print(L"Wollen Sie das Programm nochmals ausführen? Antworten Sie mit j(ja) oder n(nein).\n");
        auto answer = m_input.GetLetter();
        if (answer.IsNull) {
            switch (answer.Letter) {
                case 'j':
                    return false;
                    break;
                case 'n':
                    return true;
                    break;
                default:
                    const size_t bufferSize = 1000;
                    std::cin.clear();
                    std::cin.ignore(bufferSize, '\n');
                    m_output.Print(L"Falsche Eigabe.\n");
                    break;
            }
        } else {
            m_output.Print(L"Unbekannte Ausgabe\n");
        }
    }
}

}