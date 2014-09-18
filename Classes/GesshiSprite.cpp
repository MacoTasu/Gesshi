//
//  GesshiSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "GesshiSprite.h"
#include "StoneSprite.h"

GesshiSprite::GesshiSprite()
{
}

GesshiSprite::~GesshiSprite()
{
}


GesshiSprite* GesshiSprite::createWithGesshiType(kGesshi gesshiType)
{
    GesshiSprite *pRet = new GesshiSprite();
    if (pRet && pRet->initWithGesshiType(gesshiType))
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

bool GesshiSprite::initWithGesshiType(kGesshi gesshiType)
{
    if (!Sprite::initWithFile(getGesshiImageFileName(gesshiType)))
    {
        return false;
    }
    
    m_gesshiType = gesshiType;
    flipped = false;

    return true;
}

const char* GesshiSprite::getGesshiImageFileName(kGesshi gesshiType)
{
    switch (gesshiType) {
        case kTamaGesshi:
                return "Gesshi_1.png";
        default:
            CCAssert(false, "invalid gesshiType");
            return "";
    }
}

int GesshiSprite::remainLifeDays(kGesshi gesshiType)
{
    switch (gesshiType) {
        case kTamaGesshi:
            return rand() % 2 + 1;
        default:
            CCAssert(false, "invalid gesshiType");
            return rand() % 1 + 1;
    }
}

void GesshiSprite::runAnimation(kGesshi gesshiType)
{
    cocos2d::Animation *animation = cocos2d::Animation::create();
    switch (gesshiType) {
        case kTamaGesshi:
            animation->addSpriteFrameWithFile("Gesshi_1.png");
            animation->setRestoreOriginalFrame(true);
            animation->setDelayPerUnit(0.5f / 4.0f);
            
            cocos2d::Animate *animate        = cocos2d::Animate::create(animation);
            cocos2d::RepeatForever *animated = cocos2d::RepeatForever::create(animate);
            this->runAction(animated);
    }
}

StoneSprite* GesshiSprite::drawStone(bool direct)
{
    //タグをランダムに取得する処理
    int posX = this->getPositionX();
    int posY = this->getPositionY();
    kStone stoneType = (kStone)( rand() % kStoneCount);
    StoneSprite* pStone = StoneSprite::createWithStoneType(stoneType);
    pStone->setPosition(cocos2d::Point(posX, posY));
    
    if (direct == true) {
        return pStone;
    }
    
    if (pStone->canSet()) {
        return pStone;
    }
    else {
        return NULL;
    }
}

cocos2d::ActionInterval* GesshiSprite::generateMove(cocos2d::Point point) {
    int posX  = 0;
    int posY  = 0;
    int randX = 0;
    int randY = 0;

    if (point.ZERO == cocos2d::Point::ZERO) {
        if (rand() % 2 == 1) {
            randX = -rand() % 150;
        }
        else {
            randX = rand() % 150;
        }
        
        if (rand() % 2 == 1) {
            randY = -rand() % 150;
        }
        else {
            randY = rand() % 150;
        }
        
        posX = this->getPositionX() + randX;
        posY = this->getPositionY() + randY;
    
        cocos2d::Size winSize = cocos2d::Director::getInstance()->getVisibleSize();
    
        if (winSize.width + (this->getContentSize().width/2)  < posX) {
            posX  = winSize.width - this->getContentSize().width /2;
            randX = 0;
        }
        else if (posX < this->getContentSize().width / 2) {
            posX  = this->getContentSize().width ;
            randX = 0;
        }
    
        if (winSize.height - (this->getContentSize().height * 2) < posY) {
            randY = 0;
            posY  = winSize.height - this->getContentSize().height * 2;
        }
        else if (posY < this->getContentSize().height * 4.0) {
            randY = 0;
            posY  = this->getContentSize().height * 4.0;
        }
    }
    else {
        posX  = point.x;
        posY  = point.y;
        randX = 0;
        randY = 0;
    }
    
    if (this->getPositionX() < posX) {
        flipped = true;
        this->setFlippedX(true);
    }
    
    if (posX < this->getPositionX()) {
        flipped = false;
        this->setFlippedX(false);
    }

    cocos2d::ActionInterval* action = cocos2d::JumpBy::create(0.5, cocos2d::Point(randX ,randY), 10, 2);
    //cocos2d::MoveTo* move = cocos2d::MoveTo::create(0.5, cocos2d::Point( posX, posY ));
    
    return action;
}

void GesshiSprite::feelAnimation() {
    cocos2d::EaseElasticOut* a1 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.1, 1.08));
    cocos2d::EaseElasticOut* a2 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(1, 0.95));
    cocos2d::EaseElasticOut* a3 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.1, 1.03));
    cocos2d::EaseElasticOut* a4 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(1, 1.0));
    cocos2d::Sequence* sq       = cocos2d::Sequence::create(a1, a2, a3, a4, NULL);
    this->runAction(sq);
}

cocos2d::Rect GesshiSprite::getRect()
{
    // スプライトの座標（画像の真ん中の座標のこと）
    cocos2d::Point point = this->getPosition();
    
    // スプライトの幅と高さ
    int w = this->getContentSize().width;
    int h = this->getContentSize().height;
    
    // スプライトの範囲を返す
    return cocos2d::Rect(point.x-(w/2), point.y-(h/2), w, h);
}

bool GesshiSprite::isTouchPoint(cocos2d::Point point)
{
    return this->getRect().containsPoint(point);
}

