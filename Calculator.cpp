#include "Calculator.h"
#include <cmath>

const int NUM_ROWS = 5;
const int NUM_COLUMNS = 5;

Calculator::Calculator(wxString title) : wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(420, 300))
{
	buffer.clear();
	expectingOperand = true;
	equalClicked = false;
	displayedText = "";
	
	SetBackgroundColour(wxColour(*wxWHITE));
	sizer = new wxBoxSizer(wxVERTICAL);

	displayTop = new wxTextCtrl(this, wxID_ANY, displayedText, wxPoint(-1, -1), wxSize(350, -1), wxTE_RIGHT | wxTE_READONLY  | wxTE_NO_VSCROLL | wxNO_BORDER);
	displayTop->SetBackgroundColour(*wxWHITE);
	sizer->Add(displayTop, 0, wxTOP | wxBOTTOM | wxRIGHT, 10);

	display = new wxTextCtrl(this, wxID_ANY, "0", wxPoint(-1, -1), wxSize(400, -1), wxTE_RIGHT | wxTE_READONLY  | wxTE_NO_VSCROLL | wxNO_BORDER);
	display->SetBackgroundColour(*wxWHITE);
	sizer->Add(display, 0, wxTOP | wxBOTTOM | wxRIGHT, 10);

	grid = new wxGridSizer(NUM_ROWS, NUM_COLUMNS, 5, 5);
	
	wxButton* buttonClear = new wxButton(this, wxID_ANY, "Clear");
	grid->Add(buttonClear, 0);
	buttonClear->Bind(wxEVT_BUTTON, &Calculator::OnClear, this);

	wxButton* buttonInverse = new wxButton(this, wxID_ANY, "1/x");
	grid->Add(buttonInverse, 0);
	buttonInverse->Bind(wxEVT_BUTTON, &Calculator::OnInverse, this);

	wxButton* buttonPower = new wxButton(this, wxID_ANY, "x^y");
	grid->Add(buttonPower, 0);
	buttonPower->Bind(wxEVT_BUTTON, &Calculator::OnPower, this);

	wxButton* buttonSqrt = new wxButton(this, wxID_ANY, "Sqrt(x)");
	grid->Add(buttonSqrt, 0);
	buttonSqrt->Bind(wxEVT_BUTTON, &Calculator::OnSqrt, this);

	wxButton* buttonMultiply = new wxButton(this, wxID_ANY, "*");
	grid->Add(buttonMultiply, 0);
	buttonMultiply->Bind(wxEVT_BUTTON, &Calculator::OnMultiplication, this);

	wxButton* buttonClearAll = new wxButton(this, wxID_ANY, "Clear All");
	grid->Add(buttonClearAll, 0);
	buttonClearAll->Bind(wxEVT_BUTTON, &Calculator::OnClear, this);

	wxButton* button7 = new wxButton(this, wxID_ANY, "7");
	grid->Add(button7, 0);
	button7->Bind(wxEVT_BUTTON, &Calculator::OnSeven, this);

	wxButton* button8 = new wxButton(this, wxID_ANY, "8");
	grid->Add(button8, 0);
	button8->Bind(wxEVT_BUTTON, &Calculator::OnEight, this);

	wxButton* button9 = new wxButton(this, wxID_ANY, "9");
	grid->Add(button9, 0);
	button9->Bind(wxEVT_BUTTON, &Calculator::OnNine, this);

	wxButton* buttonDivide = new wxButton(this, wxID_ANY, "/");
	grid->Add(buttonDivide, 0);
	buttonDivide->Bind(wxEVT_BUTTON, &Calculator::OnDivision, this);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* button4 = new wxButton(this, wxID_ANY, "4");
	grid->Add(button4, 0);
	button4->Bind(wxEVT_BUTTON, &Calculator::OnFour, this);

	wxButton* button5 = new wxButton(this, wxID_ANY, "5");
	grid->Add(button5, 0);
	button5->Bind(wxEVT_BUTTON, &Calculator::OnFive, this);

	wxButton* button6 = new wxButton(this, wxID_ANY, "6");
	grid->Add(button6, 0);
	button6->Bind(wxEVT_BUTTON, &Calculator::OnSix, this);

	wxButton* buttonAdd = new wxButton(this, wxID_ANY, "+");
	grid->Add(buttonAdd, 0);
	buttonAdd->Bind(wxEVT_BUTTON, &Calculator::OnAddition, this);

	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* button1 = new wxButton(this, wxID_ANY, "1");
	grid->Add(button1, 0);
	button1->Bind(wxEVT_BUTTON, &Calculator::OnOne, this);

	wxButton* button2 = new wxButton(this, wxID_ANY, "2");
	grid->Add(button2, 0);
	button2->Bind(wxEVT_BUTTON, &Calculator::OnTwo, this);

	wxButton* button3 = new wxButton(this, wxID_ANY, "3");
	grid->Add(button3, 0);
	button3->Bind(wxEVT_BUTTON, &Calculator::OnThree, this);

	wxButton* buttonSubtract = new wxButton(this, wxID_ANY, "-");
	grid->Add(buttonSubtract, 0);
	buttonSubtract->Bind(wxEVT_BUTTON, &Calculator::OnSubtraction, this);


	grid->Add(new wxStaticText(this, -1, ""), 0);

	wxButton* buttonSign = new wxButton(this, wxID_ANY, "+/-");
	grid->Add(buttonSign, 0);
	buttonSign->Bind(wxEVT_BUTTON, &Calculator::OnSign, this);

	wxButton* button0 = new wxButton(this, wxID_ANY, "0");
	grid->Add(button0, 0);
	button0->Bind(wxEVT_BUTTON, &Calculator::OnZero, this);

	wxButton* buttonDot = new wxButton(this, wxID_ANY, ".");
	grid->Add(buttonDot, 0);
	buttonDot->Bind(wxEVT_BUTTON, &Calculator::OnDecimal, this);

	wxButton* buttonEquals = new wxButton(this, wxID_ANY, "=");
	grid->Add(buttonEquals, 0);
	buttonEquals->Bind(wxEVT_BUTTON, &Calculator::OnEqual, this);



	sizer->Add(grid);
	SetSizer(sizer);

	CreateStatusBar(3);
	SetStatusText("Ready", 0);

	SetMinSize(wxSize(420, 300));
	SetMaxSize(wxSize(420, 400));
	Centre();
}

void Calculator::DigitClicked(wxString digit)
{
	if (equalClicked)
	{
		displayedText.Clear();
		displayTop->SetLabelText(displayedText);
		sum = 0.0;
		equalClicked = false;
	}

	if (expectingOperand)
	{
		buffer.Clear();
		expectingOperand = false;
	}
	buffer.append(digit);
	SetStatusText(buffer, 0);
	display->SetLabelText(buffer);
}

void Calculator::AdditiveOpClicked(wxString op)
{
	if (equalClicked)
	{
		displayedText.Clear();
		buffer = DoubleToString(sum);
		displayTop->SetLabelText(buffer);
		equalClicked = false;
	}
	double temp = 0;
	if (buffer.ToDouble(&temp))
	{
		if (!pendingPowerOperator.IsEmpty())
		{
			if (!calculate(temp, pendingPowerOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			temp = power;
			power = 0;
			pendingPowerOperator.Clear();

		}
		
		if (!pendingMultiplicationOperator.IsEmpty())
		{
			if (!calculate(temp, pendingMultiplicationOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			temp = factor;
			factor = 0;
			pendingMultiplicationOperator.Clear();
		}
		if (!pendingAdditionOperator.IsEmpty())
		{
			if (!calculate(temp, pendingAdditionOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			
		}
		else
		{
			sum = temp;
		}

		pendingAdditionOperator = op;
		if (temp < 0)
			displayedText = displayedText + "(" + buffer + ") " + op + " ";
		else
			displayedText = displayedText + buffer + " " + op + " ";

		displayTop->SetLabelText(displayedText);

		SetStatusText(DoubleToString(sum), 1);
		expectingOperand = true;
	}
	

}

void Calculator::MultiplicativeOpClicked(wxString op)
{
	if (equalClicked)
	{
		displayedText.Clear();
		buffer = DoubleToString(sum);
		displayTop->SetLabelText(buffer);
		equalClicked = false;
	}
	double temp = 0;
	if (buffer.ToDouble(&temp))
	{
		if (!pendingPowerOperator.IsEmpty())
		{
			if (!calculate(temp, pendingPowerOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			temp = power;
			power = 0;
			pendingPowerOperator.Clear();

		}
		
		if (!pendingMultiplicationOperator.IsEmpty()) 
		{
			if (!calculate(temp, pendingMultiplicationOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
		}
		else
			factor = temp;
		pendingMultiplicationOperator = op;
		expectingOperand = true;

		if (temp < 0)
			displayedText = displayedText +"("+ buffer + ") " + op + " ";
		else
			displayedText = displayedText + buffer + " " + op + " ";

		displayTop->SetLabelText(displayedText);
	}
}

bool Calculator::calculate(double rightOperand, wxString& pendingOperator)
{
	if (pendingOperator == "^")
		power = std::pow(power, rightOperand);
	else if (pendingOperator == "+")
		sum += rightOperand;
	else if (pendingOperator == "-")
		sum -= rightOperand;
	else if (pendingOperator == "*")
		factor *= rightOperand;
	else if (pendingOperator == "/")
	{
		if (rightOperand == 0)
			return false;

		factor /= rightOperand;
	}

	return true;
}

wxString Calculator::DoubleToString(double number)
{
	wxString temp;
	temp << number;
	return temp;
}

void Calculator::clearAll()
{
	expectingOperand = true;
	equalClicked = false;
	sum = 0.0;
	factor = 0.0;
	pendingAdditionOperator.Clear();
	pendingMultiplicationOperator.Clear();
	buffer.Clear();
	displayedText.Clear();
	displayTop->SetLabelText("");
	display->SetLabelText("0");
}

void Calculator::OnClear(wxCommandEvent& event)
{
	buffer.clear();
	display->SetLabelText("0");
	expectingOperand = true;
	sum = 0;
}

void Calculator::OnClearAll(wxCommandEvent& event)
{
	clearAll();
}

void Calculator::OnInverse(wxCommandEvent& event)
{
	double result;
	if (equalClicked)
	{
		displayedText.Clear();
		displayTop->SetLabelText(DoubleToString(sum));
		equalClicked = false;
		

		if (sum == 0.0)
		{
			clearAll();
			displayTop->SetLabelText("error: division by 0");
			return;
		}
		else
		{

			sum = 1 / sum;
			display->SetLabelText(DoubleToString(sum));
			buffer = DoubleToString(sum);
		}
	}
	
	else if (buffer.ToDouble(&result))
	{
		if (result == 0.0)
		{
			clearAll();
			displayTop->SetLabelText("error: division by 0");
			return;
		}
		else
		{

			result = 1 / result;
			display->SetLabelText(DoubleToString(result));
			buffer = DoubleToString(result);
		}
	}
}

void Calculator::OnPower(wxCommandEvent& event)
{
	if (equalClicked)
	{
		displayedText.Clear();
		buffer = DoubleToString(sum);
		displayTop->SetLabelText(buffer);
		equalClicked = false;
	}
	double temp = 0;
	if (buffer.ToDouble(&temp) && !expectingOperand)
	{
		if (!pendingPowerOperator.IsEmpty())
		{
			if (!calculate(temp, pendingPowerOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
		}
		else
			power = temp;
		pendingPowerOperator = "^";
		expectingOperand = true;

		if (temp < 0)
			displayedText = displayedText + "(" + buffer + ")^";
		else
			displayedText = displayedText + buffer + "^";

		displayTop->SetLabelText(displayedText);
	}
	
}

void Calculator::OnSqrt(wxCommandEvent& event)
{

	double result;
	if (equalClicked)
	{
		displayedText.Clear();
		displayTop->SetLabelText(DoubleToString(sum));
		equalClicked = false;


		if (sum < 0.0)
		{
			clearAll();
			displayTop->SetLabelText("error: negative number under square root");
			return;
		}
		else
		{

			sum = sqrt(sum);
			display->SetLabelText(DoubleToString(sum));
			buffer = DoubleToString(sum);
		}
	}

	else if (buffer.ToDouble(&result))
	{
		if (result < 0.0)
		{
			clearAll();
			displayTop->SetLabelText("error: negative number under square root");
			return;
		}
		else
		{

			result = sqrt(result);
			display->SetLabelText(DoubleToString(result));
			buffer = DoubleToString(result);
		}
	}
}

void Calculator::OnMultiplication(wxCommandEvent& event)
{
	
	if(!expectingOperand)
		MultiplicativeOpClicked("*");
}

void Calculator::OnSeven(wxCommandEvent& event)
{
	DigitClicked("7");
}

void Calculator::OnEight(wxCommandEvent& event)
{
	DigitClicked("8");
}

void Calculator::OnNine(wxCommandEvent& event)
{
	DigitClicked("9");
}

void Calculator::OnDivision(wxCommandEvent& event)
{
	if (!expectingOperand)
		MultiplicativeOpClicked("/");
}

void Calculator::OnFour(wxCommandEvent& event)
{
	DigitClicked("4");
}

void Calculator::OnFive(wxCommandEvent& event)
{
	DigitClicked("5");
}

void Calculator::OnSix(wxCommandEvent& event)
{
	DigitClicked("6");
}

void Calculator::OnAddition(wxCommandEvent& event)
{
	if (!expectingOperand)
		AdditiveOpClicked("+");
}

void Calculator::OnOne(wxCommandEvent& event)
{
	DigitClicked("1");
}

void Calculator::OnTwo(wxCommandEvent& event)
{
	DigitClicked("2");
}

void Calculator::OnThree(wxCommandEvent& event)
{
	DigitClicked("3");
}

void Calculator::OnSubtraction(wxCommandEvent& event)
{
	if (!expectingOperand)
		AdditiveOpClicked("-");
}

void Calculator::OnSign(wxCommandEvent& event)
{
	double result;
	if (equalClicked)
	{
		displayedText.Clear();
		displayTop->SetLabelText(DoubleToString(sum));
		equalClicked = false;


		if (sum == 0.0)
		{
			return;
		}
		else
		{

			sum *=-1;
			display->SetLabelText(DoubleToString(sum));
			buffer = DoubleToString(sum);
		}
	}

	else if (buffer.ToDouble(&result))
	{
		if (result == 0.0)
		{
			return;
		}
		else
		{

			result *= -1;
			buffer = DoubleToString(result);
			if (result < 0)
				display->SetLabelText("(" + DoubleToString(result) + ")");
			else
				display->SetLabelText(DoubleToString(result));

			
		}
	}
}

void Calculator::OnZero(wxCommandEvent& event)
{
	if (!buffer.IsSameAs("0"))
		DigitClicked("0");
}

void Calculator::OnDecimal(wxCommandEvent& event)
{
	if (buffer.IsEmpty())
		DigitClicked("0.");
	else
		DigitClicked(".");
}

void Calculator::OnEqual(wxCommandEvent& event)
{
	if (equalClicked)
	{
		displayedText.Clear();
		displayTop->SetLabelText(DoubleToString(sum));
	}
	double temp = 0;
	if (buffer.ToDouble(&temp) && !expectingOperand)
	{
		if (!pendingPowerOperator.IsEmpty())
		{
			if (!calculate(temp, pendingPowerOperator))
			{
				return;
			}
			temp = power;
			power = 0;
			pendingPowerOperator.Clear();

		}
		
		if (!pendingMultiplicationOperator.IsEmpty() )
		{
			if (!calculate(temp, pendingMultiplicationOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			temp = factor;
			factor = 0;
			pendingMultiplicationOperator.Clear();
		}

		if (!pendingAdditionOperator.IsEmpty())
		{
			if (!calculate(temp, pendingAdditionOperator))
			{
				clearAll();
				displayTop->SetLabelText("error: wrong operation");
				return;
			}
			pendingAdditionOperator.Clear();
		}
		else
			sum = temp;

		if (temp < 0)
			displayedText = displayedText + "(" + buffer + ") = ";
		else
			displayedText = displayedText + buffer + " = ";


		buffer.Clear();
		
		display->SetLabelText(DoubleToString(sum));
		displayTop->SetLabelText(displayedText);

		equalClicked = true;
	}
}
