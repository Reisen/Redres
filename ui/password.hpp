#ifndef REDRES_PASSWORD_PANEL
#define REDRES_PASSWORD_PANEL

#include <wx/wx.h>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

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
    State   state = State::SERVICE;
    string  service = "";
    string  username = "";
    wxBrush cursor {
        wxColour{255, 190, 0}
    };
};

#endif
