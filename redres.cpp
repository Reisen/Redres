#include "ui.hpp"

IMPLEMENT_APP(Redres);

Redres::Redres()
{
}

bool
Redres::OnInit()
{ auto window = new Generator();
  window->Show(true);

  return true;
}
