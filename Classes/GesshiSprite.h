//
//  GesshiSprite.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#ifndef __HamuHamu__GesshiSprite__
#define __HamuHamu__GesshiSprite__

#include <iostream>

#include "cocos2d.h"
#include "Config.h"
#include "StoneSprite.h"

class GesshiSprite : public cocos2d::Sprite
{
protected:
    const char* getGesshiImageFileName(kGesshi gesshiType);
    cocos2d::Rect getRect();
    cocos2d::Label* syllableLabel;
    bool isTalking;
    std::vector<std::string> syllabes;
    void setSyllable();
    
public:
    CC_SYNTHESIZE_READONLY(kGesshi, m_gesshiType, GesshiType);
    
    GesshiSprite();
    virtual ~GesshiSprite();
    
    virtual bool initWithGesshiType(kGesshi gesshiType);
    static GesshiSprite* createWithGesshiType(kGesshi gesshiType);
    void runAnimation(kGesshi gesshiType);
    StoneSprite* drawStone(bool direct);
    cocos2d::ActionInterval* generateMove(cocos2d::Rect rect);
    void feelAnimation();
    bool isTouchPoint(cocos2d::Point point);
    int remainLifeDays(kGesshi gesshiType);
    GesshiSprite* drawGesshi();
    void runSetAnimation(bool flipped);
    void talk();
    bool isFlipped;
};

#endif /* defined(__HamuHamu__GesshiSprite__) */


