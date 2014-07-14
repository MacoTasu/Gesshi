//
//  FertilizerSprite.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/13.
//
//

#ifndef __HamuHamu__FertilizerSprite__
#define __HamuHamu__FertilizerSprite__

#include <iostream>
#include "Config.h"
#include "cocos2d.h"

class FertilizerSprite : public cocos2d::Sprite
{
protected:
    const char* getFertilizerImageFileName(kFertilizer fertilizerType);
    
public:
    CC_SYNTHESIZE_READONLY(kFertilizer, m_fertilizerType, FertilizerType);
    
    FertilizerSprite();
    virtual ~FertilizerSprite();

    virtual bool initWithFertilizerType(kFertilizer fertilizerType);
    static FertilizerSprite* createWithFertilizerType(kFertilizer fertilizerType);
    bool canSet();
    int getScore();
    kFertilizer getType();
};

#endif /* defined(__HamuHamu__Fertilizer__) */
