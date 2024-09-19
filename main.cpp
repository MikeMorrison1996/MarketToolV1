#include <wx/wx.h>
#include <wx/notebook.h>
#include "ChatGPTApi.h"  // Include the ChatGPT API integration

class MarketToolApp : public wxApp {
public:
    virtual bool OnInit();
};

class LoginFrame : public wxFrame {
public:
    LoginFrame(const wxString& title);

private:
    wxTextCtrl* usernameField;
    wxTextCtrl* passwordField;
    const wxString validUsername = "devuser";
    const wxString validPassword = "password123";

    void OnLogin(wxCommandEvent& event);
};

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title);

private:
    wxNotebook* notebook;
    wxPanel* CreateGraphPanel(wxNotebook* parent);
    wxPanel* CreateAccountPanel(wxNotebook* parent);
    wxPanel* CreateNewsPanel(wxNotebook* parent);
    wxPanel* CreateTradePanel(wxNotebook* parent);
    wxPanel* CreateChatGPTPanel(wxNotebook* parent);  // Add ChatGPT panel
};

wxIMPLEMENT_APP(MarketToolApp);

bool MarketToolApp::OnInit() {
    LoginFrame *loginFrame = new LoginFrame("Market Tool - Login");
    loginFrame->Show(true);
    return true;
}

LoginFrame::LoginFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText* userLabel = new wxStaticText(panel, wxID_ANY, "Username:");
    vbox->Add(userLabel, 0, wxEXPAND | wxALL, 10);

    usernameField = new wxTextCtrl(panel, wxID_ANY);
    vbox->Add(usernameField, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    wxStaticText* passLabel = new wxStaticText(panel, wxID_ANY, "Password:");
    vbox->Add(passLabel, 0, wxEXPAND | wxALL, 10);

    passwordField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    vbox->Add(passwordField, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

    wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
    vbox->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 10);

    loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);

    panel->SetSizer(vbox);
}

void LoginFrame::OnLogin(wxCommandEvent& event) {
    MainFrame* mainFrame = new MainFrame("Market Tool - Main");
    mainFrame->Show(true);
    this->Close(true);
}

MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    notebook = new wxNotebook(panel, wxID_ANY);

    wxPanel* graphPanel = CreateGraphPanel(notebook);
    wxPanel* tradePanel = CreateTradePanel(notebook);
    wxPanel* accountPanel = CreateAccountPanel(notebook);
    wxPanel* newsPanel = CreateNewsPanel(notebook);
    wxPanel* chatGPTPanel = CreateChatGPTPanel(notebook);  // Add ChatGPT panel

    notebook->AddPage(graphPanel, "Graphs");
    notebook->AddPage(tradePanel, "Trade");
    notebook->AddPage(accountPanel, "Account Info");
    notebook->AddPage(newsPanel, "News");
    notebook->AddPage(chatGPTPanel, "Ask ChatGPT");  // Add ChatGPT page

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(notebook, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);
}

wxPanel* MainFrame::CreateGraphPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Live Graphs Here");

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

wxPanel* MainFrame::CreateTradePanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxButton* buyButton = new wxButton(panel, wxID_ANY, "Buy");
    wxButton* sellButton = new wxButton(panel, wxID_ANY, "Sell");
    wxButton* holdButton = new wxButton(panel, wxID_ANY, "Hold");

    vbox->Add(buyButton, 0, wxALIGN_CENTER | wxALL, 10);
    vbox->Add(sellButton, 0, wxALIGN_CENTER | wxALL, 10);
    vbox->Add(holdButton, 0, wxALIGN_CENTER | wxALL, 10);

    panel->SetSizer(vbox);
    return panel;
}

wxPanel* MainFrame::CreateAccountPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Account Information Here");

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

wxPanel* MainFrame::CreateNewsPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "News and Updates Here");

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

// New ChatGPT panel
wxPanel* MainFrame::CreateChatGPTPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText* promptLabel = new wxStaticText(panel, wxID_ANY, "Ask ChatGPT a question:");
    vbox->Add(promptLabel, 0, wxALIGN_LEFT | wxALL, 10);

    wxTextCtrl* inputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(600, 25));
    vbox->Add(inputField, 0, wxALIGN_LEFT | wxALL, 10);

    wxButton* askButton = new wxButton(panel, wxID_ANY, "Ask ChatGPT");
    vbox->Add(askButton, 0, wxALIGN_LEFT | wxALL, 10);

    wxTextCtrl* resultField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(600, 300), wxTE_MULTILINE | wxTE_READONLY);
    vbox->Add(resultField, 1, wxEXPAND | wxALL, 10);

    askButton->Bind(wxEVT_BUTTON, [inputField, resultField](wxCommandEvent&) {
        wxString userInput = inputField->GetValue();
        if (!userInput.IsEmpty()) {
            std::string response = CallChatGPT(userInput.ToStdString());
            resultField->SetValue(response);
        }
    });

    panel->SetSizer(vbox);
    return panel;
}
