#pragma once
/*
*File           : PioneerCarRadio.h
*				: for use with PioneerCarRadio.cpp carDriver.cpp AmFmRadio.h AmFmRadio.cpp
*Project        : PioneerCarRadio
*Programmer     : Colby Taylor
*First version  : 2021-03-25
*Description    : PioneerCarRadio creates its own setting display to allow customization of display
*				: as well as an input handler to accept input and process the button to change settings 
*				: on the radio for an easy experience while driving a vehicle.
*				: The constructor for PioneerCarRadio doesnt have any distinct attributes so its only 
*				: job is to instanitate the Parent class object AmFmRadio with its default OFF and the 
*				: button presets
*/
#include "AmFmRadio.h"

#pragma warning(disable:4996)



class PioneerCarRadio: public AmFmRadio
{
	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:

	PioneerCarRadio(bool power = false);							//PioneerCarRadio Constructor
	PioneerCarRadio(struct Freqs presets[5], bool power = false);	//PioneerCarRadio Constructor with presets for buttons
	virtual ~PioneerCarRadio(void);									//PioneerCarRadio Destructor
	
	void ShowCurrentSettings(void);									//PioneerCarRadio current settings info dump display
	bool KeyPressHandler(void);										//Handles the keys pressed for the radio to function, calls the mutators to manipulate the attributes
};
