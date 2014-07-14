//
//  FertilizerSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/13.
//
//

#include "FertilizerSprite.h"

FertilizerSprite::FertilizerSprite()
{
}

FertilizerSprite::~FertilizerSprite()
{
}

FertilizerSprite* FertilizerSprite::createWithFertilizerType(kFertilizer FertilizerType)
{
    FertilizerSprite *pRet = new FertilizerSprite();
    if (pRet && pRet->initWithFertilizerType(FertilizerType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

int FertilizerSprite::getScore() {
    switch (m_fertilizerType) {
        case kSmall:
            return 10; //肥料ポイントが貯まる
        case kFertilizerCount:
            return 0;
        default:
            CCAssert(false, "invalid FertilizerType");
            return 0;
    }
};

bool FertilizerSprite::initWithFertilizerType(kFertilizer FertilizerType)
{
    if (!Sprite::initWithFile(getFertilizerImageFileName(FertilizerType)))
    {
        return false;
    }
    
    m_fertilizerType = FertilizerType;
    
    return true;
}

const char* FertilizerSprite::getFertilizerImageFileName(kFertilizer FertilizerType)
{
    switch (FertilizerType) {
        case kSmall:
            return "Fertilizer_1_1.png";
        default:
            CCAssert(false, "invalid FertilizerType");
            return "";
    }
}

bool FertilizerSprite::canSet()
{
    switch (m_fertilizerType) {
        case kSmall: {
            // 3回動いて１回肥料をセット
            int num = rand() % 4;
            if (num == 1) {
                return true;
            }
            return false;
        }
        case kFertilizerCount:
            CCAssert(false, "invalid FertilizerType");
            return false;
        default:
            CCAssert(false, "invalid FertilizerType");
            return false;
    }
}

kFertilizer FertilizerSprite::getType() {
    return m_fertilizerType;
}

