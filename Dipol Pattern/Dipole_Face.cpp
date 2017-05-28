#include "Dipole_Face.h"

using namespace Dipole_Pattern;



[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew Dipole_Face());
	return 0;
}