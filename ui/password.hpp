#ifndef REDRES_PASSWORD_PANEL
#define REDRES_PASSWORD_PANEL

#include <wx/wx.h>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "../types/password.hpp"

using std::string;
using std::vector;
using std::unique_ptr;
using std::reference_wrapper;

enum class State
    { SERVICE
    , USERNAME
    };

class PasswordPanel : public wxPanel {
    public:
    PasswordPanel(wxWindow* window);
    void RenderCompletions(wxPaintDC& dc, string input, vector<reference_wrapper<const string>> const& completions);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnKeyPress(wxKeyEvent& event);

    protected:
    DECLARE_EVENT_TABLE()

    private:
    // Estado
    State state = State::SERVICE;
    string service = "";
    string username = "";
    vector<Password> passwords;

    // UI Estado
    wxBrush cursor     { wxColour{255, 190, 0} };
    wxBrush suggestion { wxColour{20, 20, 20} };
    wxFont font
        { 9                         // Pixel Size
        , wxFONTFAMILY_TELETYPE     // Font Family (Monospace)
        , wxFONTSTYLE_NORMAL        // Font Style
        , wxFONTWEIGHT_NORMAL       // Font Weight
        , false                     // Underlined
        , "Inconsolata"             // Font Face
        , wxFONTENCODING_DEFAULT    // Font Encoding
        };
};

#endif
