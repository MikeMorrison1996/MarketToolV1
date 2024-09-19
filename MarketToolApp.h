#ifndef MARKETTOOLAPP_H
#define MARKETTOOLAPP_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "MarketToolApi.h"  // Include the Hugging Face API integration

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
    void OnLogin(wxCommandEvent& event);
};

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title, const std::string& huggingFaceApiKey);

private:
    wxNotebook* notebook;
    std::string huggingFaceApiKey;  // Store API key as a member of the class
    wxPanel* CreateGraphPanel(wxNotebook* parent);
    wxPanel* CreateAccountPanel(wxNotebook* parent);
    wxPanel* CreateNewsPanel(wxNotebook* parent);
    wxPanel* CreateTradePanel(wxNotebook* parent);
    wxPanel* CreateHuggingFacePanel(wxNotebook* parent);
};

#endif // MARKETTOOLAPP_H
