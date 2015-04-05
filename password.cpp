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

    this->RenderCompletions(dc, input, completions);
}

void
PasswordPanel::OnKeyPress(wxKeyEvent& event) {
    auto key = event.GetUnicodeKey();
    if(key == WXK_NONE) {
        return;
    }

    ((state == State::SERVICE)
        ? this->service
        : this->username).push_back(key);

    __builtin_printf("Keydown %c!\n", key);
    this->Refresh();
}

BEGIN_EVENT_TABLE(PasswordPanel, wxPanel)
    EVT_PAINT(PasswordPanel::OnPaint)
    EVT_CHAR(PasswordPanel::OnKeyPress)
END_EVENT_TABLE()
