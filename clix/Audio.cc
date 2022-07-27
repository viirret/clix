#include "Audio.hh"

Audio::Audio()
{
	InitAudioDevice();

	if(IsAudioDeviceReady())
		SetMasterVolume((float)Config::MASTER_VOLUME / 10);
}

void Audio::addSound(std::string name)
{
	soundFiles.push_back(name);
	Sound s = LoadSound(soundFiles.back().c_str());
	sounds.push_back(s);
	PlaySound(s);
}

void Audio::playSound(std::string name)
{
	std::string p = Config::ASSETSPATH + name;

	if(soundFiles.empty())
		addSound(p);
	else
	{
		for(size_t i = 0; i < (size_t)soundFiles.size(); i++)
		{
			if(soundFiles[i] == p)
				PlaySound(sounds.at(i));
			return;
		}
		addSound(p);
	}
}

Audio::~Audio()
{
	for(auto& sound : sounds)
		UnloadSound(sound);	

	CloseAudioDevice();
}
