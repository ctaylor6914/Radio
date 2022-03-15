#pragma once
/*
*File           : PioneerWorld.h
*				: for use with PioneerAM.h PionnerCarRadio.h ultimateRadio.cpp AmFmRadio.cpp AmFmRadio.cpp
*Project        : AmFmRadio
*Programmer     : Colby Taylor
*First version  : 2021-04-07
*Description    : This object creates a child of PioneerAM with the ability to only 
*				: use the AM band width. It does not dispaly FM band or FM button presets
*/

#include "PioneerAM.h"
#define kWorldAmMin 531
#define kWorldAmMax 1602
#pragma warning(disable:4996)



class PioneerWorld : public PioneerAM
{
	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	/*
CONSTRUCTOR  : PioneerWorld()
Parameters   : struct of Freqs for the preset button frequencies
			 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440-WRLD"
Return Value : none
Description  : Instantiate the PioneerWorld object while linking the Parent Class object PioneerAM, PioneerCarRadio 
			 : and AmFMRadio to be instantiated first with power OFF and the preset button frequencies
*/
	PioneerWorld(bool power = false):PioneerAM(power)
	{
		int i = 0;
		SetID((char*)"XS440-WRLD");
		SetCurrentStation(kWorldAmMin);
		for (i = 0; i < 5; i++)
		{
			SetButton(i);
		}
	}

	/*
CONSTRUCTOR  : PioneerWorld()
Parameters   : struct of Freqs for the preset button frequencies
			 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440-WRLD"
Return Value : none
Description  : Instantiate the PioneerWorld object while linking the Parent Class object PioneerAM, PioneerCarRadio
			 : and AmFMRadio to be instantiated first with power OFF and the preset button frequencies
*/
	PioneerWorld(struct Freqs presets[5], bool power = false):PioneerAM(presets, power)
	{
		int i = 0;
		SetID((char*)"XS440-WRLD");
		for (int i = 0; i < 5; ++i)
		{
			if (presets[i].AMFreq <= kWorldAmMin && presets[i].AMFreq >= kWorldAmMax) //if preset value is outside of range then set to button kWorldMin
			{
				SetButton(i);
			}
		}
		SetID((char*)"XS440-WRLD");
	}

	/*
DESTRUCTOR   : ~PioneerWorld()
Parameters   : void
Return Value : none
Description  : displays a message to show the PioneerWorld object has been destroyed
*/
	virtual ~PioneerWorld(void)								
	{
		char myID[MAX_ID_SIZE] = { 0 };
		GetID(myID);
		if (strcmp(myID, "XS440-WRLD") == 0)
		{
			printf("Destroying XS440-WRLD Radio\n");
		}
	}
	/*
METHOD		 : ToggleFrequency()
Parameters   : void
Return Value : void
Description  : do nothing because the funtionality of PioneerWorld called
			 : for the radio not to use FM band at all. so the object is instantiated 
			 : in AM band and remains in the band
*/
	virtual void ToggleFrequency(void)
	{
	}

	/*
MUTATOR		 : ScanUp()
Parameters   : void
Return Value : void
Description  : Scan the station UP by 9
*/
	virtual void ScanUp(void)
	{
		if (strcmp("AM", GetFrequency()) == 0)
		{
			//if current_station is 1602, the current_station becomes 531
			if ((int)GetCurrentStation() >= kWorldAmMax)
			{
				SetCurrentStation(kWorldAmMin);
			}
			else
			{
				SetCurrentStation(GetCurrentStation() + 9);
			}
		}
	}
	/*
MUTATOR		 : ScanUp()
Parameters   : void
Return Value : void
Description  : Scan the station DOWN by 9
*/
	virtual void ScanDown(void)
	{
		if (strcmp("AM", GetFrequency()) == 0)
		{
			//if current_station is 1602, the current_station becomes 531
			if ((int)GetCurrentStation() <= kWorldAmMin)
			{
				SetCurrentStation(kWorldAmMax);
			}
			else
			{
				SetCurrentStation(GetCurrentStation() - 9);
			}
		}
	}
};

