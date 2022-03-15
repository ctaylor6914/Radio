/*
*File           : PioneerCarRadio.cpp
*				: for use with PionnerCarRadio.h ultimateRadio.cpp AmFmRadio.cpp AmFmRadio.cpp 
*Project        : AmFmRadio
*Programmer     : Colby Taylor
*First version  : 2021-03-25
*Description    : PioneerCarRadio creates its own setting display to allow customization of display
*				: as well as an input handler to accept input and process the button to change settings 
*				: on the radio for an easy experience while driving a vehicle.
*				: The constructor for PioneerCarRadio doesnt have any distinct attributes so its only 
*				: job is to instanitate the Parent class object AmFmRadio with its default OFF and the 
*				: button presets.
*/

#include "PioneerCarRadio.h"


/*
CONSTRUCTOR  : PioneerCarRadio()
Parameters   : struct of Freqs for the preset button frequencies 
			 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440"
Return Value : none
Description  : Instantiate the PioneerCarRadio object while linking the Parent Class object AmFmRadio to be instantiated 
			 : first with power OFF and the preset button frequencies
*/

PioneerCarRadio::PioneerCarRadio(struct Freqs presets[5], bool power) : AmFmRadio(power, presets)
{
	SetID((char*)"XS440");
}

/*
CONSTRUCTOR  : PioneerCarRadio()
Parameters	 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440"
Return Value : none
Description  : Instantiate the PioneerCarRadio object while linking the Parent Class object AmFmRadio to be instantiated
			 : first with power OFF and the preset button frequencies
*/
PioneerCarRadio::PioneerCarRadio(bool power) : AmFmRadio(power)
{
	SetID((char*)"XS440");
}

/*
METHOD	     : KeyPressHandler()
Parameters   : void
Return Value : bool true - if 'x' is not pressed a true is returned so that the program does not quit
			 : bool false - if 'x' is press so the program quits 
Description  : Instantiate the PioneerCarRadio object while linking the Parent Class object AmFmRadio to be instaniated
			 : first with power OFF and the preset button frequencies
*/

bool PioneerCarRadio::KeyPressHandler(void)
{
	int press = 0;
	int status = false;
	press = getch();


	if (press == 'o') //if key press is to turn the radio on
	{
		PowerToggle();
	}
	if (press == 'x') // if the key press is to quit program
	{
		return false;
	}

	status = IsRadioOn();

	if ( status == false)
	{
		return true;
	}
	else
	{
		
		if (press == '+')
		{
			SetVolume(GetVolume() + 1);
		}
		if (press == '_')
		{
			SetVolume(GetVolume() - 1);
		}
		if (press == '=')
		{
			ScanUp();
		}
		if (press == '-')
		{
			ScanDown();
		}
		if (press == 'b')
		{
			ToggleFrequency();
		}
		if (press <= '5' && press >= '1')
		{
			SelectCurrentStation((int)(press - 49));
		}
		if (press == '!' || press == '@' || press == '#' || press == '$' || press == '%')
		{
			int i = 0;
			char shifts[5] = { '!', '@', '#', '$', '%' };
			for (i = 0; i < 5; i++)
			{
				if (shifts[i] == press)
				{
					SetButton(i);
					break;
				}
			}
		}
	}
	return true;
}

/*
METHOD		 : ShowCurrentSettings()
Parameters   : void
Return Value : void
Description  : shows the current settings of the PioneerCarRadio.  if the radio is off then it prints 
*			 : a simple message saying radio off
*			 : If on it displays radio - on, volume, frequency, band, and Am/Fm button presets. 
*/
void PioneerCarRadio::ShowCurrentSettings(void)
{
	Freqs *sets = NULL;
	char myID[MAX_ID_SIZE] = { 0 };
	GetID(myID);
	sets = GetButtonPresetSettings();
	printf("Pioneer %s\n", myID);
	if (IsRadioOn() == false)
	{
		printf("Radio is off\n");
	}
	else
	{
		printf("Radio is on\n");
		printf("Volume: %d\n", GetVolume());
		if (strcmp(myID, "XS440") == 0)
		{
			if (strcmp(GetFrequency(), "AM") == 0)
			{
				printf("Current Station:%6d %s\n", (int)GetCurrentStation(), GetFrequency());
			}
			else
			{
				printf("Current Station:%6.1lf %s\n", GetCurrentStation(), GetFrequency());
			}

			printf("AM Buttons:\n");
			for (int i = 0; i < 5; ++i)
			{
				printf("%d) %6d ", i + 1, sets[i].AMFreq);
			}
			printf("\nFM Button Settings: \n");
			for (int j = 0; j < 5; ++j)
			{
				printf("%d) %6.1f ", j + 1, sets[j].FMFreq);
			}
			printf("\n");
		}
		else
		{
			printf("Current Station:%6d %s\n", (int)GetCurrentStation(), GetFrequency());
			printf("AM Buttons:\n");
			for (int i = 0; i < 5; ++i)
			{
				printf("%d) %6d ", i + 1, sets[i].AMFreq);
			}
			printf("\n");
		}
	}
	
}

/*
DESTRUCTOR   : PioneerCarRadio()
Parameters   : void
Return Value : none
Description  : displays a message to show the PioneerCarRadio object has been destroyed
*/
PioneerCarRadio::~PioneerCarRadio(void)
{
	char myID[MAX_ID_SIZE] = { 0 };
	GetID(myID);
	if (strcmp(myID, "XS440") == 0)
	{
		printf("Destroying Pioneer XS440 Radio\n");
	}
}

