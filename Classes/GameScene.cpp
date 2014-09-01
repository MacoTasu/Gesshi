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
    auto layer = GameScene:: create();
    
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
    
    showScore();
    
    showMenuButton();
    
    //定期的に呼び出す
    this->schedule(schedule_selector(GameScene::moveHamster), 1.0f);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

//　変数初期化
void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    m_fertilizer_count      = kTagFertilizer;
    m_score                 = 0;
    m_manual_moving_hamster = false;
}

Point GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width / 2;
    float offsetY = m_background->getContentSize().height / 2;
    return Point(posIndexX + offsetX, posIndexY + offsetY);
}

// ボタンを並べる
void GameScene::showMenuButton() {
    Size winSize = Director::getInstance()->getVisibleSize();
    auto pHarvestItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(GameScene::harvestFertilizer, this));
    auto pFoodItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(GameScene::harvestFertilizer, this));
    auto pShopItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(GameScene::harvestFertilizer, this));
    auto pAdvertisementItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(GameScene::harvestFertilizer, this));
    Menu*  pMenu = Menu::create(pHarvestItem,pFoodItem,pShopItem,pAdvertisementItem,NULL);
    pMenu->setPosition(Point(winSize.width / 2, 50));
    pMenu->alignItemsHorizontallyWithPadding(30.0f);
    this->addChild(pMenu, 1);
}

// スコアを表示
void GameScene::showScore() {
    Size winSize = Director::getInstance()->getVisibleSize();
    auto str = CCString::createWithFormat("%ld", m_score);
    scoreLabel = Label::create(str->getCString(), "Arial", 24);
    scoreLabel->setColor(cocos2d::Color3B::GRAY);
    scoreLabel->setPosition(Point(winSize.width - scoreLabel->getContentSize().width,
                             winSize.height - scoreLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(scoreLabel, 1);
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
    
    MoveTo* move = hamsterSprite->generateMove(Point::ZERO);
    
    auto finish = CallFunc::create([hamsterSprite,this](){
        GameScene::showFertilizer(false);
    });
    
    Spawn* spawn = Spawn::create(move, finish, NULL);
    
    hamsterSprite->runAction(spawn);
}

void GameScene::showFertilizer(bool direct) {
    if (fertilizers.size() >= 300) {
        return;
    }
    
    HamsterSprite* hamsterSprite = (HamsterSprite*)m_background->getChildByTag(kTagHamster);
    
    FertilizerSprite* pFertilizer = hamsterSprite->drawFertilizer(direct);
    if (pFertilizer != NULL) {
        int nextTag = getNextFertilizerTag();
        GameScene::m_background->addChild(pFertilizer, kZOrderFertilizer, nextTag);
        
        pFertilizer->runSetAnimation(hamsterSprite->flipped);
        fertilizers.pushBack(pFertilizer);
    }
}

int GameScene::getNextFertilizerTag() {
    return  m_fertilizer_count += 1;
}

void GameScene::harvestFertilizer(cocos2d::Ref* pSender) {
    CCLOG("Clean");
    
    for (auto &pFertilizer : fertilizers) {
        m_score += pFertilizer->getScore();
        pFertilizer->removeAnimation();
        //pFertilizer->removeFromParentAndCleanup(true);
    }
    m_fertilizer_count = kTagFertilizer;
    auto str = CCString::createWithFormat("%ld", m_score);
    scoreLabel->setString(str->getCString());
    Size winSize = Director::getInstance()->getVisibleSize();
    scoreLabel->setPosition(Point(winSize.width - scoreLabel->getContentSize().width,
                                  winSize.height - scoreLabel->getContentSize().height));
    fertilizers.clear();
    // add the label as a child to this layer
}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
    Point touchPoint = m_background->convertTouchToNodeSpace(pTouch);
    
    HamsterSprite* hamsterSprite = (HamsterSprite*)m_background->getChildByTag(kTagHamster);

    if (hamsterSprite->isTouchPoint(touchPoint)) {
        GameScene::showFertilizer(true);
        hamsterSprite->feelAnimation();
        CCLOG("Touch!!!");
    }
    
    return true;
}

void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
}

