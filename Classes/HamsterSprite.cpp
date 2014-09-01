//
//  HamsterSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "HamsterSprite.h"
#include "FertilizerSprite.h"

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
    flipped = false;

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

FertilizerSprite* HamsterSprite::drawFertilizer(bool direct)
{
    //タグをランダムに取得する処理
    int posX = this->getPositionX();
    int posY = this->getPositionY();
    kFertilizer fertilizerType = (kFertilizer)( rand() % kFertilizerCount);
    FertilizerSprite* pFertilizer = FertilizerSprite::createWithFertilizerType(fertilizerType);
    pFertilizer->setPosition(cocos2d::Point(posX, posY));
    
    if (direct == true) {
        return pFertilizer;
    }
    
    if (pFertilizer->canSet()) {
        return pFertilizer;
    }
    else {
        return NULL;
    }
}

cocos2d::MoveTo* HamsterSprite::generateMove(cocos2d::Point point) {
    int posX = 0;
    int posY = 0;

    if (point.ZERO == cocos2d::Point::ZERO) {
        int randX = 0;
        if (rand() % 2 == 1) {
            randX = -rand() % 150;
        }
        else {
            randX = rand() % 150;
        }
        
        int randY = 0;
        if (rand() % 2 == 1) {
            randY = -rand() % 150;
        }
        else {
            randY = rand() % 150;
        }
        
        posX = this->getPositionX() + randX;
        posY = this->getPositionY() + randY;
    
        cocos2d::Size winSize = cocos2d::Director::getInstance()->getVisibleSize();
    
        if (winSize.width + (this->getContentSize().width / 2) < posX) {
            posX = winSize.width + (this->getContentSize().width / 2);
        }
        else if (posX < this->getContentSize().width * 1.2) {
            posX = this->getContentSize().width * 1.2;
        }
    
        if (winSize.height - (this->getContentSize().height * 2) < posY) {
            posY = winSize.height - this->getContentSize().height * 2;
        }
        else if (posY < this->getContentSize().height * 4.0) {
            posY = this->getContentSize().height * 4.0;
        }
    }
    else {
        posX = point.x;
        posY = point.y;
    }
    
    if (this->getPositionX() < posX) {
        flipped = true;
        this->setFlippedX(true);
    }
    
    if (posX < this->getPositionX()) {
        flipped = false;
        this->setFlippedX(false);
    }

    cocos2d::MoveTo* move = cocos2d::MoveTo::create(1.0, cocos2d::Point( posX, posY ));
    
    return move;
}

void HamsterSprite::feelAnimation() {
    cocos2d::EaseElasticOut* big    = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.2, 1.1));
    cocos2d::EaseElasticOut* normal = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.2, 1.0));
    cocos2d::Sequence* sq           = cocos2d::Sequence::create(big, normal, NULL);
    this->runAction(sq);
}

cocos2d::Rect HamsterSprite::getRect()
{
    // スプライトの座標（画像の真ん中の座標のこと）
    cocos2d::Point point = this->getPosition();
    
    // スプライトの幅と高さ
    int w = this->getContentSize().width;
    int h = this->getContentSize().height;
    
    // スプライトの範囲を返す
    return cocos2d::Rect(point.x-(w/2), point.y-(h/2), w, h);
}

bool HamsterSprite::isTouchPoint(cocos2d::Point point)
{
    return this->getRect().containsPoint(point);
}

