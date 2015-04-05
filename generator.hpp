#ifndef REDRES_UI_GENERATOR
#define REDRES_UI_GENERATOR

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include "password.hpp"

using std::string;
using std::vector;
using std::unique_ptr;

class Generator : public wxFrame {
    public:
    Generator();

    // UI Components
    unique_ptr<PasswordPanel> panel;
};

#endif
