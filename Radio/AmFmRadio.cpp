
/*
*File           : AmFmRadio.cpp
*				: for use with AmFMradio.h and ultiamteRadio.cpp
*Project        : AmFmRadio
*Programmer     : Colby Taylor
*First version  : 2021-02-24
*Description    : Creates a Radio object to be used with a user interface.  This object allows for the radio to scanUP and DOWN, toggle power
*				: change volume, toggle frequency band and to set preset buttons for frequencies.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"



/*
CONSTRUCTOR  : AmFmRadio()
Parameters   : bool on = false	sets the bool on to false
Attributes	 :
			 : current_station = prevStation.AMFreq = 530
			 : frequency = frequencyCopy = AM
			 : volume = prevVolume = 0
			 : displayOutput = false
Return Value :
Description  : Instantiate the object AmFMradio
*/
AmFmRadio::AmFmRadio(bool power)
{
	for (int i = 0; i < 5; ++i)
	{
		buttonCopy[i].AMFreq = button[i].AMFreq = kAmMin;
	}
	for (int j = 0; j < 5; ++j)
	{
		buttonCopy[j].FMFreq = button[j].FMFreq = kFmMin;
	}
	on = power;
	current_station = prevStation.AMFreq = kAmMin;
	prevStation.FMFreq = kFmMin;
	strcpy(frequency, "AM");
	strcpy(frequencyCopy, "AM");
	strcpy(identification, "AMFMRadio");
	volume = prevVolume = 0;
	displayOutput = false;
}

/*
CONSTRUCTOR  : AmFmRadio()
Parameters   : bool on
			 : struct Freqs preset[5] array of 5 structs for the preset values
Attributes	 : bool on
			 : current_station = prevStation.AMFreq = 530
			 : frequency = frequencyCopy = AM
			 : volume = prevVolume = 0
			 : displayOutput = false
Return Value :
Description  : instantiate AmFmRadio and enter the button presets to previous values
*/

AmFmRadio::AmFmRadio(bool power, struct Freqs preset[5])
{

	for (int i = 0; i < 5; ++i)
	{
		if (preset[i].AMFreq >= kAmMin && preset[i].AMFreq <= kAmMax) //if preset value is within range then set to button
		{
			buttonCopy[i].AMFreq = button[i].AMFreq = preset[i].AMFreq;
		}
		else // if preset isnt within range set to lowest 
		{
			buttonCopy[i].AMFreq = button[i].AMFreq = kAmMin;
		}
	}
	for (int j = 0; j < 5; ++j)
	{
		if (preset[j].FMFreq >= kFmMin && preset[j].FMFreq <= kFmMax) //if preset value is within range then set to button
		{
			buttonCopy[j].FMFreq = button[j].FMFreq = preset[j].FMFreq;
		}
		else // if preset isnt within range set to lowest 
		{
			buttonCopy[j].FMFreq = button[j].FMFreq = kFmMin;
		}
	}
	current_station = prevStation.AMFreq = kAmMin;
	prevStation.FMFreq = kFmMin;
	strcpy(frequency, "AM");
	strcpy(frequencyCopy, "AM");
	strcpy(identification, "AMFMRadio");
	volume = prevVolume = 0;
	on = false;
	displayOutput = false;
}
/*
MUTATOR		 : SetCurrentStation()
Parameters   : double station	the radio station wanting to be set
Return Value : bool true or false to indicate successful set
Description  : take the station and do some validity checks and enter the station into the object
			 : if correct
*/
bool AmFmRadio::SetCurrentStation(double station)
{
	bool set = false;
	if (strcmp("AM", frequency) == 0)
	{
		if ((int)station >= kAmMin && (int)station <= kAmMax)
		{//casting station as int to avoid errors
			current_station = station;
			prevStation.AMFreq = (int)station;
			set = true;
		}
	}
	else
	{
		if (station >= kFmMin && station <= kFmMax)
		{
			current_station = station;
			prevStation.FMFreq = station;
			set = true;
		}
	}
	return set;
}

/*
Method		 : PowerToggle()
Parameters   : void
			 :
Return Value : void
Description  : toggles the power of the radio
			 : if on then set to off
			 : if off then set to on
*/
void AmFmRadio::PowerToggle(void)
{
	if (on == false)
	{
		on = true;
		if (strcmp(frequency, "AM") == 0)
		{
			current_station = prevStation.AMFreq;
		}
		else
		{
			current_station = prevStation.FMFreq;
		}
		volume = prevVolume;
	}
	else
	{
		on = false;
		prevVolume = volume;
		volume = 0;
	}
}

/*
ACCESSOR	 : IsRadioOn()
Parameters   : void
Return Value : void
Description  : returns the powers status of the radio
*/
bool AmFmRadio::IsRadioOn(void)
{
	return on;
}

/*
MUTATOR		 : SetVolume()
Parameters   : void
Return Value : int 0 if volume was to low and sets volume to 0
			 : int 1 if volume set to the entered value
			 : int 2 if volume was over 100, sets volume to 100
Description  : set the volume of the radio
*/
int AmFmRadio::SetVolume(void)
{
	char buf[20] = "";

	printf("\nEnter the volume level (0 - 100). ");
	fgets(buf, sizeof buf, stdin);
	volume = atoi(buf);

	if (volume < 0) //if user enters volume less than 0, volume = 0
	{
		volume = 0;
		return 0;
	}

	if (volume > 100) //if user enters volume greater than 100, volume = 100
	{
		volume = 100;
		return 2;
	}
	return 1;
}

/*
MUTATOR		 : SetVolume()
Parameters   : int inVolume
Return Value : int false if value entered is invalid
			 : int true is volume was valid and set
Description  : set the volume of the radio
*/
int AmFmRadio::SetVolume(int inVolume)
{
	int set = false;
	if (inVolume >= 0 && inVolume <= 100)
	{
		volume = inVolume;
		set = true;
	}
	return set;
}

/*
METHOD		 : ToggleFrequency()
Parameters   : void
Return Value : void
Description  : toggle frequency if AM set to FM
			 : If FM set to AM
*/
void AmFmRadio::ToggleFrequency(void)
{
	if (strcmp(frequency, "AM") == 0)
	{
		strcpy(frequency, "FM");
		current_station = prevStation.FMFreq;
	}
	else
	{
		strcpy(frequency, "AM");
		current_station = prevStation.AMFreq;
	}
}

/*
MUTATOR		 : SetButton()
Parameters   : int button_num	number of button that user wants to set a station
Return Value : int 0 if button was invalid
			 : int 1 if button was valid and set to current station
Description  : set the button preset to current station
*/
int AmFmRadio::SetButton(int button_num)
{
	if ((button_num >= 0) && (button_num <= 4))
	{
		if (strcmp("AM", frequency) == 0)
		{
			button[button_num].AMFreq = (int)current_station;
		}
		else
		{
			button[button_num].FMFreq = current_station;
		}
		return 1;

	}
	return 0;

}

/*
METHOD		 : SelectCurrentStation()
Parameters   : int button_num
Return Value : int 0 if button was invalid and station was not set
			 : int 1 if button was valid and station was set
Description  : set the current station to a button preset
*/
int AmFmRadio::SelectCurrentStation(int button_num)
{
	if ((button_num >= 0) && (button_num < 5))
	{
		if (strcmp("AM", frequency) == 0)
		{
			current_station = button[button_num].AMFreq;
			prevStation.AMFreq = (int)current_station;
		}
		else
		{
			current_station = button[button_num].FMFreq;
			prevStation.FMFreq = current_station;
		}

		return 1;
	}
	return 0;
}

/*
ACCESSOR	 : ShowCurrentSetting()
Parameters   : void
Return Value : void
Description  : show the current settings of the radio
			 : power status on or off
			 : frequency AM or FM
			 : current station
			 : AM and FM button station settings
*/
void AmFmRadio::ShowCurrentSettings(void)
{

	if (on == true)
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", frequency);
	printf("Volume: %d\n", volume);
	printf("Current Station: %.1f %s\n", current_station, frequency);
	printf("AM Button Settings: ");
	for (int i = 0; i < 5; ++i)
	{
		printf("%d) %6d ", i + 1, button[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	for (int j = 0; j < 5; ++j)
	{
		printf("%d) %6.1f ", j + 1, button[j].FMFreq);
	}
}

/*
MUTATOR		 : ScanUp()
Parameters   : void
Return Value : void
Description  : Scan the staion UP by 10 if AM and .2 if FM and roll over if at the
			 : upper limit of the band
*/
void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 1700, the current_station becomes 530
		if (current_station == kAmMax)
		{
			current_station = prevStation.AMFreq = kAmMin;
		}
		else
		{
			current_station = current_station + 10;
			prevStation.AMFreq = (int)current_station;
		}
	}
	else
	{
		//if the current_station is 107.9, the current_station becomes 87.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station >= kFmMax)
		{
			current_station = prevStation.FMFreq = kFmMin;
		}
		else
		{
			current_station = current_station + .2;
			prevStation.FMFreq = current_station;
		}
	}

	if (displayOutput == true)//make it possible for option to not display output
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}
}

/*
MUTATOR		 : ScanDown()
Parameters   : void
Return Value : void
Description  : Scan the staion DOWN by 10 if AM and .2 if FM and roll over if at the
			 : lower limit of the band
*/
void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", frequency) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (current_station == kAmMin)
		{
			current_station = prevStation.AMFreq = kAmMax;
		}
		else
		{// ScanDown() jumps by 10 
			current_station = current_station - 10;
			prevStation.AMFreq = (int)current_station;
		}
	}
	else
	{
		//if the current_station is 87.9, the current_station becomes 107.9
		//Note: car radios jump .2 for the FM. That's how it's modeled here.
		if (current_station <= kFmMin)
		{
			current_station = prevStation.FMFreq = kFmMax;
		}
		else
		{
			current_station = current_station - .2;
			prevStation.FMFreq = current_station;
		}
	}
	if (displayOutput == true)
	{
		printf("\nCurrent station: %f %s\n", current_station, frequency);
	}

}

/*
METHOD		 : ToggleOutput()
Parameters   : void
Return Value : void
Description  : Multiple methods have output, this toggles their output if and when displayed
*/
void AmFmRadio::ToggleOutput(void)
{
	if (displayOutput == false)
	{
		displayOutput = true;
	}
	else
	{
		displayOutput = false;
	}
}

/*
DESTRUCTOR	 : ~AmFmRadio()
Parameters   : void
Return Value :
Description  : when AmFmRadio is destroyed or loses scope the destructor is implicitly called
*/
AmFmRadio::~AmFmRadio(void)
{
	char myID[MAX_ID_SIZE] = { 0 };
	GetID(myID);
	if (strcmp(myID, "AMFMRadio") == 0)
	{
		printf("Destroying AmFmRadio");
	}
}


/* ====================================== */
/*              ACCESSORS                 */
/* ====================================== */

/*
ACCESSOR	 : GetFrequency()
Parameters   : void
Return Value : char*
Description  : return a non-vulnerable string of the frequency
*/
char* AmFmRadio::GetFrequency(void)
{
	memcpy(frequencyCopy, frequency, sizeof(frequency));
	return frequencyCopy;
}

/*
ACCESSOR	 : GetVolume()
Parameters   : void
Return Value : int
Description  : return the volume setting
*/
int AmFmRadio::GetVolume(void)
{
	return volume;
}

/*
ACCESSOR	 : GetCurrentStation()
Parameters   : void
Return Value : double
Description  : return the current station
*/
double AmFmRadio::GetCurrentStation(void)
{
	return current_station;
}

/*
ACCESSOR	 : GetButtonPresetSettings()
Parameters   : void
Return Value : Freqs*
Description  : return a non-vulnerable array of structs for the button values
*/
Freqs* AmFmRadio::GetButtonPresetSettings(void)
{
	memcpy(buttonCopy, button, sizeof(button));
	return button;
}

/*
ACCESSOR	 : GetDisplayOutput()
Parameters   : void
Return Value : bool
Description  : return the displayoutput setting
*/
bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}

/*
MUTATOR		 : SetID()
Parameters   : char * myID - where myID is the identification attribute for the radio
Return Value : bool
Description  : if the incoming myID is one of the 4 acceptable names then it is set
			 : if not then 0 is returned 
*/
bool AmFmRadio::SetID(char* myID)
{
	if ((strcmp(myID, "AMFMRadio") == 0) || (strcmp(myID, "XS440") == 0) || (strcmp(myID, "XS440-AM") == 0) || (strcmp(myID, "XS440-WRLD") == 0))
	{
		strcpy(identification, myID);
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
ACCESSOR	 : GetID()
Parameters   : char * myID - where myID is the identification attribute for the radio
Return Value : void
Description  : makes a copy of the identification into the incoming memory of the sending function. 
*/
void AmFmRadio::GetID(char* myID)
{
	memcpy(myID, identification, sizeof(identification));
}