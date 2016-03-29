#pragma once


class SoundManager
{
public:


	static SoundManager* getInstance();


	void reset();  


	bool isSoundEnabled();
	void enableSound(bool soundEnabled);


	void playSoundEffect(const char* soundFilePath);
	void playGeneralClickSound();

	void preloadSoundEffectForCannon(unsigned cannonType);

	void startBackgroundMusic();
	void endBackgroundMusic();

private:

	SoundManager();

	static SoundManager* _soundManager;


	bool _soundEnabled; 










};

