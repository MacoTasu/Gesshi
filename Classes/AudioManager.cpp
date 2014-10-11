//
//  AudioManager.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/09/20.
//
//

#include "AudioManager.h"


#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

AudioManager::~AudioManager()
{
    SimpleAudioEngine::end();
}

AudioManager::AudioManager()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //ext = ".mp3";
#else
    //ext = ".mp3";
#endif
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
}

void AudioManager::preloadSE(const std::string &id)
{
    SimpleAudioEngine::getInstance()->preloadEffect(getFileName(id));
}

unsigned int AudioManager::playSE(const std::string &id)
{
    return SimpleAudioEngine::getInstance()->playEffect(getFileName(id), false, 1.0f, 0.0f, 1.0f);
}

const char* AudioManager::getFileName(const std::string &id)
{
    std::string tmp;
    tmp += id;
    //tmp += ext;
    return tmp.data();
}