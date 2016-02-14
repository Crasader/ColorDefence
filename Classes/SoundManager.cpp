#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;


SoundManager* SoundManager::_soundManager= nullptr;



SoundManager::SoundManager()
{

	reset();
}




SoundManager* SoundManager::getInstance()
{
	if (nullptr== _soundManager)
	{

		_soundManager = new SoundManager();

	}

	return _soundManager;
}

void SoundManager::reset()
{

	_soundEnabled = UserDefault::getInstance()->getIntegerForKey("sound_enabled",true);


	preloadSoundEffectForCannon(0);

}

void SoundManager::playSoundEffect(const char* soundFilePath)
{
	if (_soundEnabled)
	{
		SimpleAudioEngine::getInstance()->playEffect(soundFilePath);
	}
	
}

void SoundManager::preloadSoundEffectForCannon( unsigned cannonType )
{
	//SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet/normal_shot.wav");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/BGM.mp3");
}

bool SoundManager::isSoundEnabled()
{
	return _soundEnabled;
}

void SoundManager::enableSound( bool soundEnabled )
{
	_soundEnabled = soundEnabled;
	UserDefault::getInstance()->setIntegerForKey("sound_enabled",_soundEnabled);
	if (!soundEnabled)
	{
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
		}
	}
}

void SoundManager::playGeneralClickSound()
{
	playSoundEffect("sound/UI_general_click.wav");
}

void SoundManager::startBackgroundMusic()
{
	if (_soundEnabled&&!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGM.mp3",true);
	}
}

void SoundManager::endBackgroundMusic()
{
	if (_soundEnabled)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(false);
	}
}











