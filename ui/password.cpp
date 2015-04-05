#include "ui.hpp"
using std::find;
using std::all_of;

PasswordPanel::PasswordPanel(wxWindow* window)
    : wxPanel
        { window
        , wxID_ANY
        , wxDefaultPosition
        , wxDefaultSize
        , wxTAB_TRAVERSAL
        }
{
}

void
PasswordPanel::RenderCompletions(wxPaintDC& dc, string input, vector<string> const& completions) {
    const auto char_width = 13;

    // Render the cursor position.
    dc.SetBrush(this->cursor);
    dc.DrawRectangle(
        wxRect
            { static_cast<int>(5 + char_width * input.length())
            , 5
            , char_width
            , 22
            }
    );

    // Render the input string.
    for(unsigned i = 0; i < input.length(); ++i) {
        dc.DrawText
            ( string{input[i]}
            , static_cast<int>(5 + (char_width * i))
            , 5
            );
    }

    // Render first matching completion.
    for(auto &completion : completions) {
        auto position = completion.begin();
        bool matching = all_of(input.begin(), input.end(), [&](char c) {
            position = find(completion.begin(), completion.end(), c);
            return !(position == completion.end());
        });

        if(matching) {
            printf("Matched: %s\n", completion.c_str());
        }
    }
}

void
PasswordPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc{this};
    vector<string> completions
        { "Foobarbaz"
        , "What the hell man"
        , "Amazingly Amazing"
        };

    auto input = (state == State::SERVICE)
        ? this->service
        : this->username;

    __builtin_printf("Nice");
    this->RenderCompletions(dc, input, completions);
}

void
PasswordPanel::OnKeyPress(wxKeyEvent& event) {
    // Get Typed Key. See GetUnicodeKey docs on wxWidgets docs for why this is
    // used instead of GetKeyCode.
    auto key = event.GetUnicodeKey();
    if(key == WXK_NONE) {
        return;
    }

    // Choose the right string to append to.
    auto &target = (state == State::SERVICE)
        ? this->service
        : this->username;

    // Switch States if enter is pressed.
    if(key == WXK_RETURN) {
        this->state = State::USERNAME;
    } else if(key == WXK_BACK) {
        target.pop_back();
    } else {
        // Append Character
        target.push_back(key);
        __builtin_printf("Keydown %c!\n", key);
    }

    // Refresh UI to display the current state.
    this->Refresh();
}

BEGIN_EVENT_TABLE(PasswordPanel, wxPanel)
    EVT_PAINT(PasswordPanel::OnPaint)
    EVT_CHAR(PasswordPanel::OnKeyPress)
END_EVENT_TABLE()
