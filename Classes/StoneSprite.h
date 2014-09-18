//
//  StoneSprite.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/13.
//
//

#ifndef __HamuHamu__StoneSprite__
#define __HamuHamu__StoneSprite__

#include <iostream>
#include "Config.h"
#include "cocos2d.h"

class StoneSprite : public cocos2d::Sprite
{
protected:
    const char* getStoneImageFileName(kStone stoneType);
    
public:
    CC_SYNTHESIZE_READONLY(kStone, m_stoneType, StoneType);
    
    StoneSprite();
    virtual ~StoneSprite();

    virtual bool initWithStoneType(kStone stoneType);
    static StoneSprite* createWithStoneType(kStone stoneType);
    bool canSet();
    int getScore();
    kStone getType();
    void runSetAnimation(bool flipped);
    void removeAnimation();
    void setShadow();
};

#endif /* defined(__HamuHamu__Stone__) */
