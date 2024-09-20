#include "MarketToolApp.h"
#include <wx/artprov.h>  // For wxArtProvider to use built-in icons
#include <wx/mstream.h>   // For memory stream when loading icons
#include <wx/sizer.h>     // For layout management
#include <wx/image.h>     // For image handling
#include <wx/bitmap.h>    // For bitmap handling

// Main application entry point
wxIMPLEMENT_APP(MarketToolApp);

bool MarketToolApp::OnInit() {
    wxInitAllImageHandlers();  // Initialize image handlers to load image formats
    LoginFrame* loginFrame = new LoginFrame("Market Tool - Login");

    // Set a custom icon for the app window
    wxIcon appIcon("C:/Users/Bigmi/CLionProjects/MarketTool/resources/icons/financial_technology_icon.ico", wxBITMAP_TYPE_ICO);  // Load icon from file
    loginFrame->SetIcon(appIcon);

    loginFrame->Show(true);
    return true;
}

// LoginFrame constructor
LoginFrame::LoginFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Load JPEG image from file
    wxImage bgImage("C:/Users/Bigmi/CLionProjects/MarketTool/resources/images/finance_background_image.jpg", wxBITMAP_TYPE_JPEG);
    if (!bgImage.IsOk()) {
        wxLogError("Failed to load JPEG image.");
    }

    // Create a wxBitmap from the wxImage
    wxBitmap bgBitmap(bgImage);  // Initialize bgBitmap from bgImage

    // Create a static bitmap for the background
    wxStaticBitmap* bg = new wxStaticBitmap(panel, wxID_ANY, bgBitmap, wxDefaultPosition, wxSize(400, 300));

    // Transparent panel over the background image
    wxPanel* overlayPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(400, 300), wxTRANSPARENT_WINDOW);
    overlayPanel->SetBackgroundColour(wxColour(0, 0, 0, 0));  // Fully transparent

    // Modern flat color for overlay panel background
    overlayPanel->SetBackgroundColour(wxColour(240, 240, 240, 200));  // Light gray with some transparency

    // Use wxFlexGridSizer for responsive layout
    wxFlexGridSizer* vbox = new wxFlexGridSizer(2, 0, 10);
    vbox->AddGrowableCol(1);

    // Customize the label colors
    wxStaticText* userLabel = new wxStaticText(overlayPanel, wxID_ANY, "Username:");
    userLabel->SetForegroundColour(wxColour(0, 0, 0));  // Set text color
    vbox->Add(userLabel, 0, wxALIGN_LEFT | wxALL, 10);

    usernameField = new wxTextCtrl(overlayPanel, wxID_ANY);
    vbox->Add(usernameField, 0, wxEXPAND | wxALL, 10);

    wxStaticText* passLabel = new wxStaticText(overlayPanel, wxID_ANY, "Password:");
    passLabel->SetForegroundColour(wxColour(0, 0, 0));  // Set text color
    vbox->Add(passLabel, 0, wxALIGN_LEFT | wxALL, 10);

    passwordField = new wxTextCtrl(overlayPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    vbox->Add(passwordField, 0, wxEXPAND | wxALL, 10);

    wxButton* loginButton = new wxButton(overlayPanel, wxID_ANY, "Login");
    vbox->AddStretchSpacer(1);
    vbox->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 10);

    loginButton->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);

    overlayPanel->SetSizer(vbox);

    // Position the overlay panel on top of the background image
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(bg, 1, wxEXPAND);
    panelSizer->Add(overlayPanel, 1, wxEXPAND);

    panel->SetSizer(panelSizer);
}

// Implement the OnLogin function
void LoginFrame::OnLogin(wxCommandEvent& event) {
    wxString username = usernameField->GetValue();
    wxString password = passwordField->GetValue();

    // Simple authentication check (replace with your actual logic)
    if (username == "admin" && password == "password") {
        // Open the main application window
        MainFrame* mainFrame = new MainFrame("Market Tool", "PLACE_API_KEY_HERE"); // Replace "YourAPIKey" with your actual API key
        mainFrame->Show(true);

        // Close the login window
        this->Close();
    } else {
        wxMessageBox("Invalid username or password.", "Login Failed", wxOK | wxICON_ERROR);
    }
}

// MainFrame constructor
MainFrame::MainFrame(const wxString& title, const std::string& apiKey)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), huggingFaceApiKey(apiKey) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Add a custom icon for the main window
    wxIcon appIcon("C:/Users/Bigmi/CLionProjects/MarketTool/resources/icons/financial_technology_icon.ico");
    this->SetIcon(appIcon);

    notebook = new wxNotebook(panel, wxID_ANY);

    wxPanel* graphPanel = CreateGraphPanel(notebook);
    wxPanel* tradePanel = CreateTradePanel(notebook);
    wxPanel* accountPanel = CreateAccountPanel(notebook);
    wxPanel* newsPanel = CreateNewsPanel(notebook);
    wxPanel* huggingFacePanel = CreateHuggingFacePanel(notebook);  // Use the stored API key

    notebook->AddPage(graphPanel, "Graphs");
    notebook->AddPage(tradePanel, "Trade");
    notebook->AddPage(accountPanel, "Account Info");
    notebook->AddPage(newsPanel, "News");
    notebook->AddPage(huggingFacePanel, "Ask Hugging Face");

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(notebook, 1, wxEXPAND | wxALL, 10);

    panel->SetSizer(vbox);
}

// Create Graph panel
wxPanel* MainFrame::CreateGraphPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Live Graphs Here", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

// Create Trade panel
wxPanel* MainFrame::CreateTradePanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Trade Panel", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

// Create Account panel
wxPanel* MainFrame::CreateAccountPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Account Information Here", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

// Create News panel
wxPanel* MainFrame::CreateNewsPanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "News and Updates Here", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    vbox->Add(label, 1, wxALIGN_CENTER | wxALL, 20);

    panel->SetSizer(vbox);
    return panel;
}

// Create Hugging Face panel
wxPanel* MainFrame::CreateHuggingFacePanel(wxNotebook* parent) {
    wxPanel* panel = new wxPanel(parent, wxID_ANY);

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText* promptLabel = new wxStaticText(panel, wxID_ANY, "Ask Hugging Face a question:", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    vbox->Add(promptLabel, 0, wxALIGN_LEFT | wxALL, 10);

    wxTextCtrl* inputField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(600, 25));
    vbox->Add(inputField, 0, wxALIGN_LEFT | wxALL, 10);

    wxButton* askButton = new wxButton(panel, wxID_ANY, "Ask Hugging Face");
    vbox->Add(askButton, 0, wxALIGN_LEFT | wxALL, 10);

    wxTextCtrl* resultField = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(600, 300), wxTE_MULTILINE | wxTE_READONLY);
    vbox->Add(resultField, 1, wxEXPAND | wxALL, 10);

    // Pass the API key into the lambda function for Hugging Face API calls
    askButton->Bind(wxEVT_BUTTON, [inputField, resultField, this](wxCommandEvent&) {
        wxString userInput = inputField->GetValue();
        if (!userInput.IsEmpty()) {
            std::string response = CallHuggingFace(userInput.ToStdString(), huggingFaceApiKey);  // Use member variable for API key
            resultField->SetValue(response);
        }
    });

    panel->SetSizer(vbox);
    return panel;
}
