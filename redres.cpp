#include "ui.hpp"

IMPLEMENT_APP(Redres);

Redres::Redres()
{
}

bool
Redres::OnInit() {
  unique_ptr<Generator> generator{new Generator()};
  this->generator = std::move(generator);
  this->generator->Show(true);

  return true;
}
