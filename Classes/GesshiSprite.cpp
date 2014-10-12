//
//  GesshiSprite.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "GesshiSprite.h"
#include "AudioManager.h"

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
    isFlipped = false;
    isTalking = false;
    
    setSyllable();
    
    this->schedule(schedule_selector(GesshiSprite::generateMove), 2.0);

    return true;
}

void GesshiSprite::setSyllable() {
    syllabes.push_back(std::string("ボーナスほしい"));
    syllabes.push_back(std::string("明日も会社か...(ﾟＡﾟ;)ｺﾞｸﾘ"));
    syllabes.push_back(std::string("有給取れるかな..."));
    syllabes.push_back(std::string("台風なのに出社か〜"));
    syllabes.push_back(std::string("転職しようかな"));
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

int GesshiSprite::remainLifeDays()
{
    switch (m_gesshiType) {
        case kTamaGesshi:
            return rand() % 2 + 1;
        default:
            CCAssert(false, "invalid gesshiType");
            return rand() % 1 + 1;
    }
}

void GesshiSprite::runAnimation()
{
    cocos2d::Animation *animation = cocos2d::Animation::create();
    switch (m_gesshiType) {
        case kTamaGesshi:
            animation->addSpriteFrameWithFile("Gesshi_1.png");
            animation->setRestoreOriginalFrame(true);
            animation->setDelayPerUnit(0.5f / 4.0f);
            
            cocos2d::Animate *animate        = cocos2d::Animate::create(animation);
            cocos2d::RepeatForever *animated = cocos2d::RepeatForever::create(animate);
            this->runAction(animated);
    }
}

GesshiSprite* GesshiSprite::drawGesshi(kGesshi gesshiType)
{
    //タグをランダムに取得する処理
    int posX = this->getPositionX();
    int posY = this->getPositionY();
    GesshiSprite* pGesshi = GesshiSprite::createWithGesshiType(gesshiType);
    pGesshi->setPosition(cocos2d::Point(posX, posY));
    
    return pGesshi;
}

void GesshiSprite::generateMove(float frame) {
    cocos2d::Sprite *parent = (cocos2d::Sprite*)this->getParent();
    cocos2d::Rect rect = parent->boundingBox();
    
    int posX  = 0;
    int posY  = 0;
    int randX = 0;
    int randY = 0;

    cocos2d::Point pPoint = cocos2d::Point(posX,posY);
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
    
    if (winSize.width + (this->getContentSize().width)  < posX) {
        posX  = winSize.width - this->getContentSize().width;
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
    
    if (rect.containsPoint(cocos2d::Point(posX ,posY))) {
        if (this->getPositionX() < posX) {
            isFlipped = true;
            this->setFlippedX(true);
        }
        
        if (posX < this->getPositionX()) {
            isFlipped = false;
            this->setFlippedX(false);
        }
        
        pPoint = cocos2d::Point(randX,randY);
    }
    
    float time = rand() % int(frame + 1);
    if (time < 1.0) {
        time = 1.0;
    }

    cocos2d::ActionInterval* action = cocos2d::JumpBy::create(time, pPoint, 10, 2);
    //cocos2d::MoveTo* move = cocos2d::MoveTo::create(0.5, cocos2d::Point( posX, posY ));
    
    //auto finish = CallFunc::create([gesshiSprite,this](){
        //GameScene::createGesshi();
    //});
    
    cocos2d::Spawn* spawn = cocos2d::Spawn::create(action, NULL);
    this->runAction(spawn);
}

void GesshiSprite::feelAnimation() {
    cocos2d::EaseElasticOut* a1 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.1, 1.08));
    cocos2d::EaseElasticOut* a2 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(1, 0.95));
    cocos2d::EaseElasticOut* a3 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.1, 1.03));
    cocos2d::EaseElasticOut* a4 = cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(1, 1.0));
    cocos2d::Sequence* sq       = cocos2d::Sequence::create(a1, a2, a3, a4, NULL);

    const std::string puyon = "puyon1.mp3";
    AudioManager *sound;
    sound->preloadSE(puyon);
    sound->playSE(puyon);

    this->runAction(sq);
}

cocos2d::Rect GesshiSprite::getRect()
{
    // スプライトの座標（画像の真ん中の座標のこと）
    if (this != NULL) {
        cocos2d::Point point = this->getPosition();
    
        // スプライトの幅と高さ
        int w = this->getContentSize().width;
        int h = this->getContentSize().height;
    
        // スプライトの範囲を返す
        return cocos2d::Rect(point.x-(w/2), point.y-(h/2), w, h);
    }
    return cocos2d::Rect(0,0,0,0);
}

bool GesshiSprite::isTouchPoint(cocos2d::Point point)
{
    return this->getRect().containsPoint(point);
}

void GesshiSprite::runSetAnimation(bool flipped) {
    
    float posX = 0.0;
    if (flipped == false) {
        posX = 75.0;
    }
    else {
        posX = - 75.0;
    }
    
    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(1,cocos2d::Point(posX, rand() % -10) , 30, 1);
    
    this->runAction(cocos2d::Sequence::create(jumpAction, NULL));
}

void GesshiSprite::talk() {
    if(isTalking == true) {
        return;
    }
    isTalking = true;
    
    cocos2d::MoveTo* moveToAction = cocos2d::MoveTo::create(1.0, cocos2d::Point(this->getContentSize().width / 2,this->getContentSize().height + 50));
    cocos2d::FadeTo* fadeToAction = cocos2d::FadeTo::create(1.0, 0.0);
    
    auto finish = cocos2d::CallFunc::create([this](){
        this->isTalking = false;
    });
    
    //アクションを作成
    cocos2d::Sequence * spawn = cocos2d::Sequence::create(moveToAction, fadeToAction,finish, NULL);

    auto index    = rand () % syllabes.size();
    auto syllable = syllabes.at(index);
    syllableLabel = cocos2d::Label::createWithSystemFont(syllable, "Arial", 30);
    syllableLabel->setColor(cocos2d::Color3B::MAGENTA);
    syllableLabel->setPosition(this->getContentSize().width / 2,this->getContentSize().height + syllableLabel->getContentSize().height);
    syllableLabel->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
    
    this->addChild(syllableLabel);

    syllableLabel->runAction(spawn);
}

void GesshiSprite::cloneAnimation() {
    
    float posX = 0.0;
    if (isFlipped == false) {
        posX = 75.0;
    }
    else {
        posX = - 75.0;
    }
    
    cocos2d::ActionInterval* jumpAction = cocos2d::JumpBy::create(1,cocos2d::Point(posX, rand() % -10) , 30, 1);
    
    this->runAction(cocos2d::Sequence::create(jumpAction, NULL));
}


