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
    // Constants
    const auto font_size = this->font.GetPixelSize();
    const auto char_width = 12;
    const auto char_height = 22;
    const auto offset_x = (char_width - font_size.GetWidth()) / 2;
    const auto offset_y = (char_height - font_size.GetHeight()) / 2;

    // Set DC features.
    wxPen highlight { wxColour{50, 150, 255} };
    dc.SetBrush(this->suggestion);
    dc.SetFont(this->font);
    dc.SetPen(highlight);
    dc.SetTextForeground(*wxLIGHT_GREY);

    // Render the cursor position.
    dc.DrawRectangle(
        wxRect
            { static_cast<int>(5 + input.length() * (char_width + 2))
            , 5
            , char_width
            , char_height
            }
    );

    // Render the input string.
    dc.SetPen(wxNullPen);
    dc.SetBrush(this->suggestion);
    for(unsigned i = 0; i < input.length(); ++i) {
        // Render a box around each character.
        dc.DrawRectangle(
            wxRect
                { static_cast<int>(5 + i * (char_width + 2))
                , 5
                , char_width
                , char_height
                }
        );

        // Render the character itself.
        dc.DrawText
            ( string{input[i]}
            , static_cast<int>(5 + offset_x + i * (char_width + 2))
            , 5 + offset_y
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
            break;
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
        // Switch States.
        this->state = State::USERNAME;
    } else if(key == WXK_BACK) {
        // Remove Character.
        if(target.length() > 0) {
            target.pop_back();
        }
    } else {
        // Append Character.
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
