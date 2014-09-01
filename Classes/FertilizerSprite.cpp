//
//  FertilizerSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/13.
//
//

#include "FertilizerSprite.h"

#define MYRAND(min, max) ((arc4random()/(float)UINT_MAX)*((max)-(min))+(min))

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
            return 1; //肥料ポイントが貯まる
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

void FertilizerSprite::runSetAnimation(bool flipped) {
    
    float posX = 0.0;
    if (flipped == false) {
        posX = 75.0;
    }
    else {
        posX = - 75.0;
    }
    
    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(1,cocos2d::Point(posX, rand() % -10) , 30, 1);
    //回転のアクション
    cocos2d::ActionInterval* rotateAction = cocos2d::RotateBy::create(1, rand() % 360);
    //アクションを作成
    cocos2d::Spawn* spawn = cocos2d::Spawn::create(jumpAction, rotateAction, NULL);
    
    this->runAction(spawn);
}

void FertilizerSprite::removeAnimation() {
    float duration = MYRAND(0.1, 0.5);

    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(duration,cocos2d::Point(0 ,15), 30, 1);
    //回転のアクション
    cocos2d::ActionInterval* rotateAction = cocos2d::RotateBy::create(duration, rand() % 360);
    
    cocos2d::FadeTo* fadeToAction = cocos2d::FadeTo::create(duration, 0.0);
    //アクションを作成
    cocos2d::Spawn* spawn = cocos2d::Spawn::create(jumpAction, rotateAction, fadeToAction, NULL);
    
    this->runAction(spawn);
}

