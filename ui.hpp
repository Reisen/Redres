#ifndef REDRES_UI
#define REDRES_UI

#include <wx/wx.h>
#include <vector>
#include <string>
#include <memory>
using std::string;
using std::vector;
using std::unique_ptr;

enum class State
{ SERVICE
, USERNAME
};

class Generator : public wxFrame {
  public:
  Generator();
  void RenderCompletions(wxPaintDC& dc, string input, vector<string> const& completions);
  virtual void OnPaint(wxPaintEvent& event);
  virtual void OnKeyPress(wxKeyEvent& event);

  protected:
  DECLARE_EVENT_TABLE()

  private:
  State   state;
  string  service;
  string  username;
  wxBrush cursor {
    wxColour{255, 190, 0}
  };
};

class Redres : public wxApp {
  public:
  Redres();
  virtual bool OnInit();

  private:
  unique_ptr<Generator> generator;
};

#endif
