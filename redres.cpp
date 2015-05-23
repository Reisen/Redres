#include "redres.hpp"

IMPLEMENT_APP(Redres)

Redres::Redres() {
}

bool
Redres::OnInit() {
    // El generador es la ventana principal de la aplicacion.
    unique_ptr<Generator> generator{new Generator()};
    this->generator = std::move(generator);
    this->generator->Show(true);

    return true;
}
