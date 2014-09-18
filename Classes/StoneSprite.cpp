//
//  StoneSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/13.
//
//

#include "StoneSprite.h"

#define MYRAND(min, max) ((arc4random()/(float)UINT_MAX)*((max)-(min))+(min))

StoneSprite::StoneSprite()
{
}

StoneSprite::~StoneSprite()
{
}

StoneSprite* StoneSprite::createWithStoneType(kStone StoneType)
{
    StoneSprite *pRet = new StoneSprite();
    if (pRet && pRet->initWithStoneType(StoneType))
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

int StoneSprite::getScore() {
    switch (m_stoneType) {
        case kSmall:
            return 1; //肥料ポイントが貯まる
        case kWater:
            return 5; //肥料ポイントが貯まる
        case kStar:
            return 10; //肥料ポイントが貯まる
        case kHeart:
            return 20; //肥料ポイントが貯まる
        case kStoneCount:
            return 0;
        default:
            CCAssert(false, "invalid StoneType");
            return 0;
    }
};

bool StoneSprite::initWithStoneType(kStone stoneType)
{
    if (!Sprite::initWithFile(getStoneImageFileName(stoneType)))
    {
        return false;
    }
    
    m_stoneType = stoneType;
    
    return true;
}

const char* StoneSprite::getStoneImageFileName(kStone stoneType)
{
    switch (stoneType) {
        case kSmall:
            return "Stone_1.png";
        case kStar:
            return "Stone_2.png";
        case kWater:
            return "Stone_3.png";
        case kHeart:
            return "Stone_4.png";
        default:
            CCAssert(false, "invalid StoneType");
            return "";
    }
}

bool StoneSprite::canSet()
{
    switch (m_stoneType) {
        case kSmall: {
            // 3回動いて１回肥料をセット
            int num = rand() % 4;
            if (num == 1) {
                return true;
            }
            return false;
        }
        case kWater: {
            // 5回動いて１回肥料をセット
            int num = rand() % 6;
            if (num == 1) {
                return true;
            }
            return false;
        }
        case kStar : {
            // 10回動いて１回肥料をセット
            int num = rand() % 11;
            if (num == 1) {
                return true;
            }
            return false;
        }
        case kHeart : {
            // 20回動いて１回肥料をセット
            int num = rand() % 21;
            if (num == 1) {
                return true;
            }
            return false;
        }
        case kStoneCount:
            CCAssert(false, "invalid StoneType");
            return false;
        default:
            CCAssert(false, "invalid StoneType");
            return false;
    }
}

kStone StoneSprite::getType() {
    return m_stoneType;
}

void StoneSprite::runSetAnimation(bool flipped) {
    
    float posX = 0.0;
    if (flipped == false) {
        posX = 75.0;
    }
    else {
        posX = - 75.0;
    }
    
    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(1,cocos2d::Point(posX, rand() % -10) , 30, 1);
    //回転のアクション
    //cocos2d::ActionInterval* rotateAction = cocos2d::RotateBy::create(1, rand() % 360);
    
    //できれば影をつけたい
    //Sprite* pShadow = Sprite::create("Shadow.png");
    //pShadow->setTag(1);
    //pShadow->setOpacity(0);
    //pShadow->setPosition(pShadow->getContentSize().width/2,0);
    //this->addChild(pShadow);
    
    //auto *callback = cocos2d::CallFunc::create([pShadow](){
    //    cocos2d::ActionInterval*fadeIn = cocos2d::FadeIn::create(0);
    //    pShadow->runAction(fadeIn);
    //});
    
    //アクションを作成
    //cocos2d::Spawn* spawn = cocos2d::Spawn::create(jumpAction, NULL);
    
    this->runAction(cocos2d::Sequence::create(jumpAction, NULL));
}


void StoneSprite::removeAnimation() {
   float duration = MYRAND(0.1, 0.5);

    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(duration,cocos2d::Point(0 ,15), 30, 1);
    //回転のアクション
    cocos2d::ActionInterval* rotateAction = cocos2d::RotateBy::create(duration, rand() % 360);
    
    cocos2d::FadeTo* fadeToAction = cocos2d::FadeTo::create(duration, 0.0);
    //アクションを作成
    cocos2d::Spawn* spawn = cocos2d::Spawn::create(jumpAction, rotateAction, fadeToAction, NULL);
    
    this->runAction(spawn);
}

