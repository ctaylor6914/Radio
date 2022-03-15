#pragma once

/*
*File           : AmFmRadio.h
*				: for use with driver.cpp and AmFmRadio.cpp
*Project        : AmFmRadio
*Programmer     : Colby Taylor
*First version  : 2021-02-24
*Description    : Creates a Radio object to be used with a user interface.  This object allows for the radio to scanUP and DOWN, toggle power
*				: change volume, toggle frequency band and to set preset buttons for frequencies. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <new>

#pragma warning(disable:4996)
#ifndef _CARRADIO_H
#define _CARRADIO_H

#define kAmMin 530		//Minimum Am frequency
#define kAmMax 1700		//Maximum Am frequency
#define kFmMin 87.90	//Minimum Fm frequency
#define kFmMax 107.90	//Maximum Fm Frequency

#define MAX_ID_SIZE 20	//Max identification name size

// struct to hold the AM and FM frequency for 
// the purpose of preset radio stations  
struct Freqs
{
	int AMFreq;
	double FMFreq;
};


class AmFmRadio
{
	/* ====================================== */
	/*              PRIVATE                   */
	/* ====================================== */
private:
	/* -------------- CONSTANTS ------------- */
	/* -------------- ATTRIBUTES ------------ */
	Freqs	button[5];						//button presets 
	Freqs	buttonCopy[5];					//copy of presets to send into accessor
	Freqs   prevStation;					// previous station 

	double	current_station;				// frequency the radio is tuned to
	char	identification[MAX_ID_SIZE];	// radio Identification
	char	frequency[3];					// "AM" or "FM"
	char	frequencyCopy[3];				// copy of frequency to send to accessor

	int		volume;							//radio volume
	int		prevVolume;						//previous volume to reset volume when power is toggeld

	bool	on;								// radio power status
	bool    displayOutput;					// display output stauts


	/* ====================================== */
	/*              PUBLIC                    */
	/* ====================================== */
public:

	/* -------------- CONSTRUCTORS ------------- */
								
	AmFmRadio(bool power = false);				//sets the each button to the lowest frequency, sets the current station, sets the
												//frequency to AM, sets the volume to 0 and sets on to false
												
	AmFmRadio(bool on, struct Freqs radio[5]);	//sets each button to the lowest frequency, sets the current station, sets the
												//frequency to AM, sets the volume to 0 and sets on to false.  Sets the presets of
												//the buttons 

												
	void PowerToggle(void);						// toggles power, if on then off. if off then on											 
	bool IsRadioOn(void);						// radio power status accessor.								
	virtual void ToggleFrequency(void);			// toggles AM FM frequency							
	void ToggleOutput(void);					// toggles output display							
	int SetButton(int button_num);				// sets the frequency of a button preset										
	int SelectCurrentStation(int button_num);	// tunes the radio to the preset button frequency										
	bool SetCurrentStation(double station);		// set the station if the frequency is valid--mutator										
	int SetVolume(void);						// sets the volume of the radio if 										
	int SetVolume(int inVolume);				// sets volume										
	void ShowCurrentSettings(void);				//shows power status, frequency, volume, current station and frequency, 
												//AM and FM preset button settings
									
	bool SetID(char* myID);						// sets the identification attribute 
	void GetID(char* myID);						// returns the identification attribute

	virtual void ScanUp(void);					//changes frequency UP in increments of .2 for FM, 10 for AM						
	virtual void ScanDown(void);				//changes frequency DOWN in increments of .2 for FM, 10 for AM

	/* -------------- ACCESSORS ------------- */

	char* GetFrequency(void);					// Access to the Am or Fm
	double GetCurrentStation(void);				// Access to the current radio station
	int GetVolume(void);						// Access to volume
	bool GetDisplayOutput(void);				// Access to the display option
	Freqs* GetButtonPresetSettings(void);		// Access to the struct holding the button presets

	/* -------------- DESTRUCTOR ------------- */
	virtual ~AmFmRadio(void);					// Destructor for AmFmRadio
};
#endif