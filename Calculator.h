#pragma once
#include <wx/wx.h>

class Calculator : public wxFrame
{
public:
	Calculator(wxString title);

	wxString buffer;
	wxString displayedText;

	wxTextCtrl* display;
	wxBoxSizer* sizer;
	wxGridSizer* grid;

	void DigitClicked(wxString digit);

	void OnClear(wxCommandEvent& event);
	void OnInverse(wxCommandEvent& event);
	void OnPower(wxCommandEvent& event);
	void OnSqrt(wxCommandEvent& event);
	void OnMultiplication(wxCommandEvent& event);
	void OnSeven(wxCommandEvent& event);
	void OnEight(wxCommandEvent& event);
	void OnNine(wxCommandEvent& event);
	void OnDivision(wxCommandEvent& event);
	void OnFour(wxCommandEvent& event);
	void OnFive(wxCommandEvent& event);
	void OnSix(wxCommandEvent& event);
	void OnAddition(wxCommandEvent& event);
	void OnOne(wxCommandEvent& event);
	void OnTwo(wxCommandEvent& event);
	void OnThree(wxCommandEvent& event);
	void OnSubtraction(wxCommandEvent& event);
	void OnSign(wxCommandEvent& event);
	void OnZero(wxCommandEvent& event);
	void OnDecimal(wxCommandEvent& event);
	void OnEqual(wxCommandEvent& event);

};

