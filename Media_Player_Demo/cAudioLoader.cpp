#include "pch.h"
#include "cAudioLoader.h"

// Function to read from a text file. 
// Reads each line from the text file, identifies "name", "path", "type" text, fetches the rest of the line and stores into mAudioName, mAudioPath and mAudioType member variables.
void cAudioLoader::ReadFromFile()
{
	std::ifstream AudioTextFile("AudioFiles.txt");
	if (AudioTextFile.is_open())
	{
		std::string category = "";
		std::string tempString = "";
		int strLength;

		int line_count = 0;
		int members_index = 0;

		while (std::getline(AudioTextFile, mReadFromFile[line_count]))
		{
			category = mReadFromFile[line_count].substr(0, 4);
			strLength = mReadFromFile[line_count].size() - 7;

			if (category == "path")
			{
				tempString = mReadFromFile[line_count].substr(7, strLength);
				mAudioPath[members_index] = tempString;
			}
			else if (category == "name")
			{
				tempString = mReadFromFile[line_count].substr(7, strLength);
				mAudioName[members_index] = tempString;
			}
			else if (category == "type")
			{
				tempString = mReadFromFile[line_count].substr(7, strLength);
				mAudioType[members_index] = tempString;
				members_index++;
			}
			else
			{
				printf("Error reading the text file");
			}

			line_count++;
		}

		AudioTextFile.close();
	}

	else
		printf("Unable to open 'AudioFiles.txt'");
}

// Function to get the audio name
// [param_1]: Integer is passed as parameter. 
// [return_value]: The passed value is taken as the index number for the member mAudioName, the value of mAudioName is returned.
const char* cAudioLoader::GetAudioName(int id)
{
	return mAudioName[id].c_str();
}

// Function to get the audio path
// [param_1]: Integer is passed as parameter.
// [return_value]: The passed value is taken as the index number for the member mAudioPath, the value of mAudioPath is returned.
const char* cAudioLoader::GetAudioPath(int id)
{
	return mAudioPath[id].c_str();
}

// Function to get the audio type
// [param_1]: Integer is passed as parameter.
// [return_value]: The passed value is taken as the index number for the member mAudioType, the value of mAudioType is returned.
const char* cAudioLoader::GetAudioType(int id)
{
	return mAudioType[id].c_str();
}