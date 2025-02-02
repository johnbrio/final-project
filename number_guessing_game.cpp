#include <wx/wx.h>
#include <cstdlib>
#include <ctime>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 250)) {

        srand(time(0));
        secretNumber = rand() % 100 + 1;
        attempts = 0;

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        promptText = new wxStaticText(this, wxID_ANY, "Guess a number between 1 and 100", wxPoint(10, 10));
        sizer->Add(promptText, 0, wxALL | wxCENTER, 10);

        guessInput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 40));
        sizer->Add(guessInput, 0, wxALL | wxCENTER, 10);

        guessButton = new wxButton(this, wxID_ANY, "Guess", wxPoint(10, 70));
        sizer->Add(guessButton, 0, wxALL | wxCENTER, 10);

        resultText = new wxStaticText(this, wxID_ANY, "", wxPoint(10, 100));
        sizer->Add(resultText, 0, wxALL | wxCENTER, 10);

        Bind(wxEVT_BUTTON, &MyFrame::OnGuess, this, guessButton->GetId());

        this->SetSizerAndFit(sizer);
        this->Center();
    }

private:
    void OnGuess(wxCommandEvent& event) {
        int userGuess = wxAtoi(guessInput->GetValue());
        attempts++;

        if (userGuess < secretNumber) {
            resultText->SetLabel("Too low! Try again.");
        }
        else if (userGuess > secretNumber) {
            resultText->SetLabel("Too high! Try again.");
        }
        else {
            resultText->SetLabel("Congratulations! You guessed the number in " + wxString::Format(wxT("%d"), attempts) + " attempts.");
        }
    }

    wxStaticText* promptText;
    wxTextCtrl* guessInput;
    wxButton* guessButton;
    wxStaticText* resultText;

    int secretNumber;
    int attempts;
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame("Number Guessing Game");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
