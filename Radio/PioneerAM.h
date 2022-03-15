#pragma once
/*
*File           : PioneerAM.h
*				: for use with PionnerCarRadio.h ultimateRadio.cpp AmFmRadio.cpp AmFmRadio.cpp
*Project        : AmFmRadio
*Programmer     : Colby Taylor
*First version  : 2021-04-07
*Description    : This object creates a child of PioneerCarRadio with the ability to only 
*				: use the AM band width. It does not dispaly FM band or FM button presets
*/

#include "PioneerCarRadio.h"

#pragma warning(disable:4996)


// struct to hold the AM and FM frequency for 
// the purpose of preset radio stations


class PioneerAM : public PioneerCarRadio
{
	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:
	/*
CONSTRUCTOR  : PioneerAM()
Parameters   : struct of Freqs for the preset button frequencies
			 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440-AM"
Return Value : none
Description  : Instantiate the PioneerAM object while linking the Parent Class object PioneerCarRadio
			 : and AmFMRadio to be instantiated first with power OFF and the preset button frequencies
*/
	PioneerAM(bool power = false): PioneerCarRadio(power)
	{
		SetID((char*)"XS440-AM");
	}

	/*
CONSTRUCTOR  : PioneerAM()
Parameters   : struct of Freqs for the preset button frequencies
			 : bool power = false sets the bool power to false to ensure that the radio starts in the OFF position
Attributes	 : Atrributes are inherited from the Parent class AmFmRadio
			 : The only attribute needed to inistialize is the identification which is set to "XS440-AM"
Return Value : none
Description  : Instantiate the PioneerWorld object while linking the Parent Class object PioneerAM, PioneerCarRadio
			 : and AmFMRadio to be instantiated first with power OFF and the preset button frequencies
*/
	PioneerAM(struct Freqs presets[5], bool power = false): PioneerCarRadio(presets, power)
	{
		SetID((char*)"XS440-AM");
	}

	/*
DESTRUCTOR   : ~PioneerAM()
Parameters   : void
Return Value : none
Description  : displays a message to show the PioneerAM object has been destroyed
*/
	virtual ~PioneerAM(void)
	{
		char myID[MAX_ID_SIZE] = { 0 };
		GetID(myID);
		if (strcmp(myID, "XS440-AM") == 0)
		{
			printf("Destroying Pioneer XS440-AM Radio\n");
		}
	}
	/*
METHOD		 : ToggleFrequency()
Parameters   : void
Return Value : void
Description  : do nothing because the funtionality of PioneerAM called
			 : for the radio not to use FM band at all. so the object is instantiated
			 : in AM band and remains in the band
*/
	virtual void ToggleFrequency(void)
	{
	}
};

