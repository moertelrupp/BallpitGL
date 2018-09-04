// Includes
#include "UppIncludes.hpp"
#include "UppWindow.hpp"

using namespace upp;

int main()
{
	UppWindow* window = nullptr;
	try
	{
		window = UppWindow::getInstance();
		window->initialize(false, true, 1200, 800);
		window->startGame();
		window->shutdown();
	}
	catch (UppException ex)
	{
        if (window)
        {
            window->shutdown();
        }
		ex.printMsg();
		std::cin.ignore();
	}
    //std::cout << "Program finished" << std::endl;
    //std::cin.ignore();
}