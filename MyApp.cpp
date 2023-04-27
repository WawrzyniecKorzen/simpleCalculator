#include "MyApp.h"
#include "Calculator.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxString title = "Calculator v0.1";
	Calculator* calculator = new Calculator(title);
	calculator->Show(true);



	return true;
}

