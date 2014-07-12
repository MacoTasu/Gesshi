//
//  HamsterSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "HamsterSprite.h"

HamsterSprite::HamsterSprite()
{
}

HamsterSprite::~HamsterSprite()
{
}


HamsterSprite* HamsterSprite::createWithHamsterType(kHamster hamsterType)
{
    HamsterSprite *pRet = new HamsterSprite();
    if (pRet && pRet->initWithHamsterType(hamsterType))
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

bool HamsterSprite::initWithHamsterType(kHamster hamsterType)
{
    if (!Sprite::initWithFile(getHamsterImageFileName(hamsterType)))
    {
        return false;
    }
    
    m_hamsterType = hamsterType;

    return true;
}

const char* HamsterSprite::getHamsterImageFileName(kHamster hamsterType)
{
    switch (hamsterType) {
        case kDjungarian:
                return "Hamster_1_1.png";
        default:
            CCAssert(false, "invalid hamsterType");
            return "";
    }
}

void HamsterSprite::runAnimation(kHamster hamsterType)
{
    cocos2d::Animation *animation = cocos2d::Animation::create();
    switch (hamsterType) {
        case kDjungarian:
            animation->addSpriteFrameWithFile("Hamster_1_1.png");
            animation->addSpriteFrameWithFile("Hamster_1_2.png");
            animation->setRestoreOriginalFrame(true);
            animation->setDelayPerUnit(0.5f / 4.0f);
            
            cocos2d::Animate *animate        = cocos2d::Animate::create(animation);
            cocos2d::RepeatForever *animated = cocos2d::RepeatForever::create(animate);
            this->runAction(animated);
    }
}