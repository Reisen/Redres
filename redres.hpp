#ifndef REDRES
#define REDRES

#include "ui.hpp"

class Redres : public wxApp {
    public:
    Redres();
    virtual bool OnInit();

    private:
    unique_ptr<Generator> generator;
};

#endif
