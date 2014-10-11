//
//  MenuSound.cpp
//  Gesshi
//
//  Created by Makoto Shiga on 2014/09/21.
//
//

#include "MenuSound.h"
#include "AudioManager.h"

USING_NS_CC;
using namespace std;

MenuSound::MenuSound()
{
}
MenuSound::~MenuSound()
{
}

MenuSound* MenuSound::create(const char *soundName, MenuItem *item, ...)
{
    va_list args;
    va_start(args,item);
    Vector<MenuItem*> pArray;
    if( item )
    {
        MenuItem *i = va_arg(args, MenuItem*);
        while(i)
        {
            pArray.pushBack(i);
            i = va_arg(args, MenuItem*);
        }
    }
    MenuSound* pRet = new MenuSound();
    pRet->createWithArray(pArray);
    pRet->setSound(soundName);
    va_end(args);
    return pRet;
}

void MenuSound::TouchEnded(Touch* touch, Event* event)
{
    SoundManager->playSE(m_sound);
    TouchEnded(touch, event);
}

void MenuSound::setSound(const char *sound)
{
    m_sound = sound;
    SoundManager->preloadSE(m_sound);
}