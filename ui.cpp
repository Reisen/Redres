#include "ui.hpp"
#include <algorithm>
using std::find;
using std::all_of;

Generator::Generator()
: wxFrame
{ nullptr
, wxID_ANY
, "Generator"
, wxDefaultPosition
, wxSize{300, 32}
, wxNO_BORDER
}
{ Center();
  SetBackgroundColour(wxColour{30, 30, 30});
  Show();
}

void
Generator::RenderCompletions(wxPaintDC& dc, string input, vector<string> const& completions) {
  const auto char_width = 13;

  /* Render the cursor position. */
  dc.SetBrush(this->cursor);
  dc.DrawRectangle(
    wxRect
    { static_cast<int>(5 + char_width * input.length())
    , 5
    , char_width
    , 22
    }
  );

  /* Render the input string. */
  for(unsigned i = 0; i < input.length(); ++i) {
    dc.DrawText
    ( string{input[i]}
    , static_cast<int>(5 + char_width + i)
    , 5
    );
  }

  /* Render first matching completion. */
  for(auto &completion : completions) {
    auto position = completion.begin();
    bool matching = all_of(input.begin(), input.end(), [&](char c) {
      position = find(completion.begin(), completion.end(), c);
      printf("%c == %c\n", c, *position);
      return !(position == completion.end());
    });

    if(matching) {
      printf("Matched: %s\n", completion.c_str());
    }
  }
}

void
Generator::OnPaint(wxPaintEvent& event) {
  wxPaintDC dc{this};
  string input{"Fbb"};
  vector<string> completions {
    "Foobarbaz",
    "What the hell man",
    "Amazingly Amazing"
  };

  this->RenderCompletions(dc, input, completions);
}

BEGIN_EVENT_TABLE(Generator, wxFrame)
  EVT_PAINT(Generator::OnPaint)
END_EVENT_TABLE()
