#include "Audio.hh"

Audio::Audio()
{
	InitAudioDevice();

	if(IsAudioDeviceReady())
	{
		SetMasterVolume((float)MASTER_VOLUME / 10);
		
		soundFiles.push_back(glb::assetsPath + "gunshow.mp3");

		for(auto& str : soundFiles)
			sounds.push_back(LoadSound(str.c_str()));
	}
}

void Audio::playSound(std::string name)
{
	for(size_t i = 0; i < (size_t)soundFiles.size(); i++)
		if(soundFiles[i] == glb::assetsPath + name)
			PlaySound(sounds.at(i));	
}

Audio::~Audio()
{
	for(auto& sound : sounds)
		UnloadSound(sound);	

	CloseAudioDevice();
}
