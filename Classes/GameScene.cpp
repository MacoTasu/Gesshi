//
//  GameScene.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "GameScene.h"
#include "HamsterSprite.h"
#include "FertilizerSprite.h"

USING_NS_CC;

Scene* GameScene::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void GameScene::showBackground()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    
    // 背景を生成
    m_background = Sprite::create(PNG_BACKGROUND);
    m_background->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(m_background,kZOrderBackground, kTagBackground);
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    initForVariables();
    
    showBackground();
    
    showHamster();
    
    //定期的に呼び出す
    
    this->schedule(schedule_selector(GameScene::moveHamster), 1.5f);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);

    
    return true;
}

//　変数初期化
void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    HamsterSprite* pHamster = HamsterSprite::createWithHamsterType(kDjungarian);
    m_hamsterSize = pHamster->getContentSize().height;
    
    m_harvesting = false;
}

Point GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width / 2;
    float offsetY = m_background->getContentSize().height / 2;
    return Point(posIndexX + offsetX, posIndexY + offsetY);
}


// ハムスターのタグを取得
int GameScene::getHamsterTag(int index)
{
    return kTagHamster + index;
}

// ハムスターを表示
void GameScene::showHamster()
{
    // TODO : タグの追加処理が必要かも

    // ハムスターを作成
    HamsterSprite* pHamster = HamsterSprite::createWithHamsterType(kDjungarian);
    pHamster->setPosition(getPosition(0,0)); // ハムスターのスタート位置
    m_background->addChild(pHamster, kZOrderHamster, kTagHamster); //ハムスターを増やす時は個々のタグをいじる
    
    pHamster->runAnimation(kDjungarian);
}


void GameScene::moveHamster(float frame)
{
    HamsterSprite* hamsterSprite = (HamsterSprite*)m_background->getChildByTag(kTagHamster);

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
    
    int posX = hamsterSprite->getPositionX() + randX;
    int posY = hamsterSprite->getPositionY() + randY;

    Size winSize = Director::getInstance()->getVisibleSize();
    
    if (winSize.width < posX) {
        posX = winSize.width - (hamsterSprite->getContentSize().width / 2);
    }
    else if (posX < hamsterSprite->getContentSize().width * 1.8) {
        posX = hamsterSprite->getContentSize().width * 1.8;
    }
    
    if (winSize.height - (hamsterSprite->getContentSize().height * 2) < posY) {
        posY = winSize.height - hamsterSprite->getContentSize().height * 2;
    }
    else if (posY < hamsterSprite->getContentSize().height * 4) {
        posY = hamsterSprite->getContentSize().height * 4;
    }
    
    if (hamsterSprite->getPositionX() < posX) {
        hamsterSprite->setFlippedX(true);
    }
    
    if (posX < hamsterSprite->getPositionX()) {
        hamsterSprite->setFlippedX(false);
    }
    
    MoveTo* move = MoveTo::create(1.0, Point( posX, posY ));
    
    auto finish = CallFunc::create([hamsterSprite,this](){
        FertilizerSprite* pFertilizer = hamsterSprite->drawFertilizer();
        if (pFertilizer->canSet()) {
            int nextTag = getCurrentFertilizerTag() + 1;
            GameScene::m_background->addChild(pFertilizer, kZOrderFertilizer, nextTag);
            GameScene::fertilizerTags.push_back(nextTag);
        }
    });
    
    hamsterSprite->runAction(Sequence::create(move,finish,NULL));
}

int GameScene::getCurrentFertilizerTag() {
    int lastIndex = fertilizerTags.size();
    return kTagFertilizer + lastIndex - 1;
}

// ここからはプレイヤーっぽいことをする。なんかクラスで分けられるならそうしたい
void GameScene::harvestFertilizer(float posX, float posY, int index) {
    FertilizerSprite* fertilizerSprite = (FertilizerSprite*)m_background->getChildByTag(index);
    MoveTo* move = MoveTo::create(0.5, Point( posX, posY ));
    FiniteTimeAction* fade = FadeTo::create( 0.5f, 0);
    auto finish = CallFunc::create([this, index](){
        std::vector<int>::iterator it = std::remove(fertilizerTags.begin(), fertilizerTags.end(),index);
        fertilizerTags.erase(it, fertilizerTags.end());
        CCLOG("remove : %d", index);
    });
    
    fertilizerSprite->runAction(Sequence::create(move, fade, finish, NULL));
    // メモリ解放が必要かも
}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
    return !m_harvesting;
}

void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent) {
    Point touchPoint = m_background->convertTouchToNodeSpace(pTouch);
    if (fertilizerTags.size() <= 0) {
        return;
    }
    int index = fertilizerTags.at(0);
    harvestFertilizer(touchPoint.x, touchPoint.y, index);
}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
    m_harvesting = false;
}

