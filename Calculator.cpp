#include "Calculator.h"

const int NUM_ROWS = 5;
const int NUM_COLUMNS = 5;

Calculator::Calculator(wxString title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(480, 400))
{
	
	
	SetBackgroundColour(wxColour(*wxWHITE));
	sizer = new wxBoxSizer(wxVERTICAL);
	display = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1), wxSize(-1, -1), wxTE_RIGHT | wxTE_READONLY | wxTE_MULTILINE | wxTE_NO_VSCROLL | wxNO_BORDER);

	sizer->Add(display, 0, wxTOP | wxBOTTOM | wxRIGHT, 10);

	grid = new wxGridSizer(NUM_ROWS, NUM_COLUMNS, 5, 5);
	
	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* buttonInverse = new wxButton(this, wxID_ANY, "1/x");
	grid->Add(buttonInverse, 0);

	wxButton* buttonPower = new wxButton(this, wxID_ANY, "^x");
	grid->Add(buttonPower, 0);

	wxButton* buttonSqrt = new wxButton(this, wxID_ANY, "Sqrt(x)");
	grid->Add(buttonSqrt, 0);

	wxButton* buttonMultiply = new wxButton(this, wxID_ANY, "*");
	grid->Add(buttonMultiply, 0);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* button7 = new wxButton(this, wxID_ANY, "7");
	grid->Add(button7, 0);

	wxButton* button8 = new wxButton(this, wxID_ANY, "8");
	grid->Add(button8, 0);

	wxButton* button9 = new wxButton(this, wxID_ANY, "9");
	grid->Add(button9, 0);

	wxButton* buttonDivide = new wxButton(this, wxID_ANY, "/");
	grid->Add(buttonDivide, 0);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* button4 = new wxButton(this, wxID_ANY, "4");
	grid->Add(button4, 0);

	wxButton* button5 = new wxButton(this, wxID_ANY, "5");
	grid->Add(button5, 0);

	wxButton* button6 = new wxButton(this, wxID_ANY, "6");
	grid->Add(button6, 0);

	wxButton* buttonAdd = new wxButton(this, wxID_ANY, "+");
	grid->Add(buttonAdd, 0);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* button1 = new wxButton(this, wxID_ANY, "1");
	grid->Add(button1, 0);

	wxButton* button2 = new wxButton(this, wxID_ANY, "2");
	grid->Add(button2, 0);

	wxButton* button3 = new wxButton(this, wxID_ANY, "3");
	grid->Add(button3, 0);

	wxButton* buttonSubtract = new wxButton(this, wxID_ANY, "-");
	grid->Add(buttonSubtract, 0);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* buttonSign = new wxButton(this, wxID_ANY, "+/-");
	grid->Add(buttonSign, 0);

	wxButton* button0 = new wxButton(this, wxID_ANY, "0");
	grid->Add(button0, 0);

	wxButton* buttonDot = new wxButton(this, wxID_ANY, ".");
	grid->Add(buttonDot, 0);

	wxButton* buttonEquals = new wxButton(this, wxID_ANY, "=");
	grid->Add(buttonEquals, 0);



	sizer->Add(grid);
	SetSizer(sizer);

	CreateStatusBar(3);
	SetStatusText("Ready", 0);

	SetMinSize(wxSize(420, 300));
	SetMaxSize(wxSize(420, 300));
	Centre();
}
