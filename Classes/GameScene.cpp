//
//  GameScene.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "GameScene.h"
#include "HamsterSprite.h"

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
    
    return true;
}

//　変数初期化
void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    HamsterSprite* pHamster = HamsterSprite::createWithHamsterType(kDjungarian);
    m_hamsterSize = pHamster->getContentSize().height;
}

Point GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width / 2;
    float offsetY = m_background->getContentSize().height / 2;
    return Point(posIndexX + offsetX, posIndexY + offsetY);
}


// ハムスターのタグを取得
int GameScene::getTag(int index)
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
    HamsterSprite * hamsterSprite = (HamsterSprite*)m_background->getChildByTag(kTagHamster);

    int randX = 0;
    if (rand() % 2 == 1) {
        randX = -rand() % 100;
    }
    else {
        randX = rand() % 100;
    }
    
    int randY = 0;
    if (rand() % 2 == 1) {
        randY = -rand() % 100;
    }
    else {
        randY = rand() % 100;
    }
    
    int posX = hamsterSprite->getPositionX() + randX;
    int posY = hamsterSprite->getPositionY() + randY;

    Size winSize = Director::getInstance()->getVisibleSize();
    
    if (winSize.width < posX) {
        posX = winSize.width - hamsterSprite->getContentSize().width;
    }
    
    if (m_background->getContentSize().width < posY) {
        posY = winSize.height  - hamsterSprite->getContentSize().height;
    }
    
    if (posY < 0) {
        posY = hamsterSprite->getContentSize().height;
    }
    
    if (posX < 0) {
        posX = hamsterSprite->getContentSize().width;
    }
    
    if (hamsterSprite->getPositionX() < posX) {
        hamsterSprite->setFlippedX(true);
    }
    
    if (posX < hamsterSprite->getPositionX()) {
        hamsterSprite->setFlippedX(false);
    }
    
    CCLOG("posX: %d",posX);
    CCLOG("posY: %d",posY);
    
    MoveTo* move = MoveTo::create(1.0, Point( posX, posY ));
    
    hamsterSprite->runAction(move);
}