
/*
*File           : ultimateRadio.cpp
*				: for use with AmFMradio.h AmFmRadio.cpp PioneerCarRadio.h PioneerCarRadio.cpp PioneerAM.h PioneerWorld.h
*Project        : PioneerCarRadio
*Programmer     : Colby Taylor
*First version  : 2021-03-25
*Description    : ultimateRadio instaniates the new radio object.  From the command line argument.  The argument is
				: passed to createRadio() for processing.  once the radio object is deleted the user may create a new
				: radio object until that one is delted as well.
*/


#include "AmFmRadio.h"
#include "PioneerCarRadio.h"
#include "PioneerAM.h"
#include "PioneerWorld.h"

using namespace std;
PioneerCarRadio* createRadio(string radio);

int main(int argc, char* argv[])
{
	bool			close = true;
	PioneerCarRadio *pRadio = NULL;
	string radio(argv[1]);
	exception e;

	try
	{
		pRadio = createRadio(radio);
	}
	catch (const char* e)
	{
		printf("Exception Found: %s", e);
		return 0; 
	}
	catch (bad_alloc& ba)
	{
		printf("Exception Found: No More Memory");
		return 0;
	}

	do
	{
		system("CLS"); // Thought this was nicer to deal with when using the radio
		pRadio->ShowCurrentSettings();
		close = pRadio->KeyPressHandler();
	} while (close == true);

	delete pRadio;
	pRadio = NULL;
	int press = 0;

	do
	{
		press = getch();
		if (press == 'c')
		{
			pRadio = new PioneerCarRadio();
			if (pRadio == NULL)
			{
				close = false;
				press = 'exit';
			}
			close = true; 
			press = 'exit';
		}
		if (press == 'a')
		{
			pRadio = new PioneerAM();
			if (pRadio == NULL)
			{
				close = false;
				press = 'exit';
			}
			close = true;
			press = 'exit';
		}
		if (press == 'w')
		{
			pRadio = new PioneerWorld();
			if (pRadio == NULL)
			{
				close = false;
				press = 'exit';
			}
			close = true;
			press = 'exit';
		}
		if (press == 'x')
		{
			close = false;
			press = 'exit';
		}
	} while (press != 'exit');

	while (close == true)
	{
		system("CLS"); // Thought this was nicer to deal with when using the radio
		pRadio->ShowCurrentSettings();
		close = pRadio->KeyPressHandler();
	}

	delete pRadio;
	
	return 0;
}

/*
Function	 : createRadio()
Parameters   : string object
Return Value : Pointer to a class object of PioneerCarRadio
Description  : process the string and create the appropriate object. if 
			 : the string does not match any of the 3 string an exception is thrown
			 
*/
PioneerCarRadio* createRadio(string radio)
{
	PioneerWorld* wrld = NULL;
	PioneerAM* pioneerAM = NULL;
	PioneerCarRadio* pioneerCarRadio = NULL;
	string car("-car");
	string am("-am");
	string world("-world");
	if (radio == car)
	{
		pioneerCarRadio = new PioneerCarRadio();
		return pioneerCarRadio;
	}
	if (radio == am)
	{
		pioneerAM = new PioneerAM();
		return pioneerAM;
	}
	if (radio == world)
	{
		wrld = new PioneerWorld();
		return wrld;
	}

	throw "Error Creating the Radio";
}