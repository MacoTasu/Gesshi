//
//  MenuSound.h
//  Gesshi
//
//  Created by Makoto Shiga on 2014/09/21.
//
//

#ifndef __Gesshi__MenuSound__
#define __Gesshi__MenuSound__

#include <stdio.h>
#include "cocos2d.h"
#include "AudioManager.h"

class MenuSound : public cocos2d::Menu
{
public:
    MenuSound();
    virtual ~MenuSound();
    
    static MenuSound* create(const char* soundName, cocos2d::MenuItem* item, ...);
    virtual void TouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void setSound(const char* sound);
    
protected:
private:
    const char* m_sound;
    AudioManager *SoundManager;
};

#endif /* defined(__Gesshi__MenuSound__) */
