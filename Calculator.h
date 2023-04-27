#pragma once
#include <wx/wx.h>

class Calculator : public wxFrame
{
public:
	Calculator(wxString title);


	wxTextCtrl* display;
	wxBoxSizer* sizer;
	wxGridSizer* grid;

};

