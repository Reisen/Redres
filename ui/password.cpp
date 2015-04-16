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
    // Las constantes. Cambia esetos si tu quieres a cambiar el visualizacion
    // del mensaje.
    const auto font_size = this->font.GetPixelSize();
    const auto char_spacing = 2;
    const auto char_width = 14;
    const auto char_height = 26;
    const auto offset_x = (char_width - font_size.GetWidth()) / 2;
    const auto offset_y = (char_height - font_size.GetHeight()) / 2;

    // Aqui nosotros la propiedades de la DC.
    wxPen highlight { wxColour{50, 150, 255} };
    dc.SetBrush(this->suggestion);
    dc.SetFont(this->font);
    dc.SetPen(highlight);
    dc.SetTextForeground(wxColour{255, 100, 100});

    // Mostrar la posicion de la puntero.
    dc.DrawRectangle(
        wxRect
            { static_cast<int>(3 + input.length() * (char_width + char_spacing))
            , 3
            , char_width
            , char_height
            }
    );

    // El mensaje que el usario a entrado debe ser mostrado.
    dc.SetPen(wxNullPen);
    dc.SetBrush(this->suggestion);
    for(unsigned i = 0; i < input.length(); ++i) {
        // Render a box around each character.
        dc.DrawRectangle(
            wxRect
                { static_cast<int>(3 + i * (char_width + char_spacing))
                , 3
                , char_width
                , char_height
                }
        );

        // Mostrar una carta.
        dc.DrawText
            ( string{input[i]}
            , static_cast<int>(3 + offset_x + i * (char_width + char_spacing))
            , 3 + offset_y
            );
    }

    // Encontrar una conclusion, luego mostrarlo.
    for(auto &completion : completions) {
        bool matching = all_of(input.begin(), input.end(), [&](char c) {
            return completion.end() != find_if
                ( completion.begin()
                , completion.end()
                , [&](char d) {
                    return tolower(d) == tolower(c);
                });
        });

        // Si nos encontramos una conclusion que coincide luego mostrarlo.
        if(matching) {
            printf("Matched: %s\n", completion.c_str());

            auto position = input.begin();
            for(unsigned i = 0; i < completion.length(); ++i) {
                // Si una carta esta en la frase, cambiar la color.
                dc.SetTextForeground(*wxLIGHT_GREY);
                if(tolower(*position) == tolower(completion[i])) {
                    position++;
                    dc.SetTextForeground(wxColour{50, 110, 250});
                }

                // Mostrar una caja.
                dc.DrawRectangle(
                    wxRect
                        { static_cast<int>(3 + i * (char_width + char_spacing))
                        , 3
                        , char_width
                        , char_height
                        }
                );

                // Mostrar la carta.
                dc.DrawText
                    ( string{completion[i]}
                    , static_cast<int>(3 + offset_x + i * (char_width + char_spacing))
                    , 3 + offset_y
                    );
            }
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
