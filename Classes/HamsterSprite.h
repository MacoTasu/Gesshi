//
//  HamsterSprite.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#ifndef __HamuHamu__HamsterSprite__
#define __HamuHamu__HamsterSprite__

#include <iostream>

#include "cocos2d.h"
#include "Config.h"

class HamsterSprite : public cocos2d::Sprite
{
protected:
    const char* getHamsterImageFileName(kHamster hamsterType);
    
public:
    CC_SYNTHESIZE_READONLY(kHamster, m_hamsterType, HamsterType);
    
    HamsterSprite();
    virtual ~HamsterSprite();
    
    virtual bool initWithHamsterType(kHamster hamsterType);
    static HamsterSprite* createWithHamsterType(kHamster hamsterType);
    void runAnimation(kHamster hamsterType);
};

#endif /* defined(__HamuHamu__HamsterSprite__) */
