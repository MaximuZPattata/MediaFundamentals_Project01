#pragma once
#include "pch.h"

// This class was created to fetch the audio details from a text file, store the details and load the audio through the Audio Manager using audio path
class cAudioLoader
{
private:
	std::string mAudioName[10]; // Array to hold 10 audio name string values
	std::string mAudioPath[10]; // Array to hold 10 audio path string values
	std::string mAudioType[10]; // Array to hold 10 audio type string values
	std::string mReadFromFile[30]; // Array to hold all 30 lines read from text file

public:
	const char* GetAudioName(int id);
	const char* GetAudioPath(int id);
	const char* GetAudioType(int id);

	void ReadFromFile();
};

