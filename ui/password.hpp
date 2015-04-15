#ifndef REDRES_PASSWORD_PANEL
#define REDRES_PASSWORD_PANEL

#include <wx/wx.h>

using std::string;
using std::vector;
using std::unique_ptr;

enum class State
    { SERVICE
    , USERNAME
    };

class PasswordPanel : public wxPanel {
    public:
    PasswordPanel(wxWindow* window);
    void RenderCompletions(wxPaintDC& dc, string input, vector<string> const& completions);
    virtual void OnPaint(wxPaintEvent& event);
    virtual void OnKeyPress(wxKeyEvent& event);

    protected:
    DECLARE_EVENT_TABLE()

    private:
    // State Components
    State  state = State::SERVICE;
    string service = "";
    string username = "";

    // UI Components
    wxBrush cursor     { wxColour{255, 190, 0} };
    wxBrush suggestion { wxColour{20, 20, 20} };
    wxFont  font
        { 9                         // Pixel Size
        , wxFONTFAMILY_TELETYPE     // Font Family (Monospace)
        , wxFONTSTYLE_NORMAL        // Font Style
        , wxFONTWEIGHT_NORMAL       // Font Weight
        , false                     // Underlined
        , "Inconsolata"                // Font Face
        , wxFONTENCODING_DEFAULT    // Font Encoding
        };
};

#endif
