#include "ui.hpp"

Generator::Generator()
    : wxFrame
        { nullptr
        , wxID_ANY
        , "PassPanel"
        , wxDefaultPosition
        , wxSize{498, 32}
        , wxNO_BORDER
        }
{
    // Anadir las componentes.
    unique_ptr<PasswordPanel> panel{new PasswordPanel(this)};
    this->panel = std::move(panel);
    this->panel->SetBackgroundColour(wxColour{30, 30, 30});

    // Mostrar las ventanas.
    this->Center();
    this->Show();
}
