#include "MyApp.h"
#include "Calculator.h"


IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxString title = "Simple Calculator";
	Calculator* calculator = new Calculator(title);
	calculator->Show(true);


	calculator->display->HideNativeCaret();
	return true;
}

