//
//  GameScene.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#include "GameScene.h"
#include "GesshiSprite.h"
#include "StoneSprite.h"
#include "GoogleAnalyticsTracker.h"
#include "AudioManager.h"
#include "ModalLayer.h"
#include "MenuSound.h"

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

void GameScene::onEnter()
{
    Layer::onEnter();
    
    GoogleAnalyticsTracker::sendScreen("GameScene");
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
    
    showGesshi();
    
    showHeader();
    
    //showMenuButton();
    
    //createIconBanner();
    
    createButtomBanner();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GameScene::createIconBanner() {
    //Test用のID
    char iconApiKey[] = "2349edefe7c2742dfb9f434de23bc3c7ca55ad22";
    char iconSpotID[] = "101281";
    NendIconModule::createNADIconLoader(iconApiKey, iconSpotID);
    NendIconModule::createNADIconViewTop();
}

void GameScene::createButtomBanner() {
    char bannerApiKey[] = "a6eca9dd074372c898dd1df549301f277c53f2b9";
    char bannerApiId[]  = "3172";
    NendModule::createNADViewBottom(bannerApiKey, bannerApiId);
    NendIconModule::load();
}

//　変数初期化
void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    // 前回の時間をとる
    time_t previousTime = (time_t)CCUserDefault::getInstance()->getIntegerForKey(PREVIOUS_TIME);
    
    int diff = diffDays(previousTime);
    if (diff >= 0) {
        // 一日経過してたなら現在時刻をセット(初回時も)
        CCUserDefault::getInstance()->setIntegerForKey(PREVIOUS_TIME, (int)time(NULL));

        int previous_life_days = CCUserDefault::getInstance()->getIntegerForKey(LIFE_DAYS);
        CCUserDefault::getInstance()->setIntegerForKey(LIFE_DAYS,diff + previous_life_days);
    }
    
    if (CCUserDefault::getInstance()->getIntegerForKey(LIFE_DAYS) <= 0) {
        m_life_days = 1;
        CCUserDefault::getInstance()->setIntegerForKey(LIFE_DAYS,m_life_days);
    }
    else {
        m_life_days = CCUserDefault::getInstance()->getIntegerForKey(LIFE_DAYS);
    }
    
    m_gp                   = CCUserDefault::getInstance()->getFloatForKey(GESSHI_POINT);
    m_manual_moving_gesshi = false;
    
    CCUserDefault::getInstance()->flush();
}

Point GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width / 2;
    float offsetY = m_background->getContentSize().height / 2;
    return Point(posIndexX + offsetX, posIndexY + offsetY);
}

// ボタンを並べる
void GameScene::showMenuButton() {
    //Size winSize = Director::getInstance()->getVisibleSize();
    //auto pHarvestItem = MenuItemImage::create("Btn_1.png","Btn_1.png",CC_CALLBACK_1(GameScene::harvestStone, this));

    //auto pFoodItem = MenuItemImage::create("Btn_1.png","Btn_1.png",CC_CALLBACK_1(GameScene::harvestStone, this));
    //auto pShopItem = MenuItemImage::create("Btn_1.png","Btn_1.png",CC_CALLBACK_1(GameScene::harvestStone, this));
    //auto pAdvertisementItem = MenuItemImage::create("Btn_1.png","Btn_1.png",CC_CALLBACK_1(GameScene::harvestStone, this));
    //Menu*  pMenu = Menu::create(pHarvestItem,pFoodItem,pShopItem,pAdvertisementItem,NULL);
    //pMenu->setPosition(Point(winSize.width / 2, 200));
    //pMenu->alignItemsHorizontallyWithPadding(10.0f);
    //this->addChild(pMenu, 1);
}

void GameScene::showHeader() {
    int padding = 10;
    Size winSize = Director::getInstance()->getVisibleSize();
    scoreBoard = Sprite::create("BaseGp.png");
    scoreBoard->setPosition(Point(winSize.width - (scoreBoard->getContentSize().width/2 + padding),
                                  winSize.height - scoreBoard->getContentSize().height/2 - padding));
    
    auto sgp   = CCString::createWithFormat("%ld", m_gp);
    scoreLabel = Label::createWithSystemFont(sgp->getCString(), "Arial", 50);
    scoreLabel->setColor(cocos2d::Color3B::BLACK);
    scoreLabel->setPosition(Point(scoreBoard->getContentSize().width - scoreLabel->getContentSize().width - 5,  scoreLabel->getContentSize().height/2 + 5));
    scoreLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    scoreBoard->addChild(scoreLabel, 1, 1);
    
    careBoard = Sprite::create("BaseCare.png");
    careBoard->setPosition(Point(winSize.width - (scoreBoard->getContentSize().width + careBoard->getContentSize().width/2 + padding * 2),winSize.height - careBoard->getContentSize().height/2 - padding));
    
    auto s_life_days = CCString::createWithFormat("%d", m_life_days);
    daysLabel = Label::createWithSystemFont(s_life_days->getCString(), "Arial", 50);
    daysLabel->setColor(cocos2d::Color3B::BLACK);
    daysLabel->setPosition(Point(careBoard->getContentSize().width - daysLabel->getContentSize().width - 50,  daysLabel->getContentSize().height/2 + 5));
    daysLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    careBoard->addChild(daysLabel, 1, 1);
    
    // add the label as a child to this layer
    this->addChild(scoreBoard, 1);
    this->addChild(careBoard, 1);
}

// げっ歯を表示
void GameScene::showGesshi()
{
    // ハムスターを作成
    GesshiSprite* pGesshi = GesshiSprite::createWithGesshiType(kTamaGesshi);
    pGesshi->setPosition(getPosition(0,0));
    m_background->addChild(pGesshi, kZOrderGesshi, kTagGesshi);
    
    pGesshi->runAnimation();
}

void GameScene::createGesshi() {
    if (gesshies.size() >= 5) {
        return;
    }
    
    const std::string drop = "water-drop1.mp3";
    AudioManager *sound;
    sound->preloadSE(drop);
    sound->playSE(drop);
    
    GesshiSprite* gesshiSprite    = (GesshiSprite*)m_background->getChildByTag(kTagGesshi);
    GesshiSprite* newGesshiSprite = gesshiSprite->drawGesshi(kTamaGesshi);
    m_background->addChild(newGesshiSprite,kZOrderGesshi);
    newGesshiSprite->cloneAnimation();
    gesshies.pushBack(newGesshiSprite);
}

bool GameScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
    Point touchPoint = m_background->convertTouchToNodeSpace(pTouch);
    
    GesshiSprite* gesshiSprite = (GesshiSprite*)m_background->getChildByTag(kTagGesshi);

    if (gesshiSprite->isTouchPoint(touchPoint)) {
        gesshiSprite->feelAnimation();
        gesshiSprite->talk();
        this->createGesshi();
        CCLOG("Touch!!!");
    }
    
    return true;
}

void GameScene::onTouchMoved(Touch* pTouch, Event* pEvent) {

}

void GameScene::onTouchEnded(Touch* pTouch, Event* pEvent) {
}

int GameScene::diffDays(time_t time)
{
    // 現在の日付
    struct tm *nowDate;
    time_t now;
    nowDate = localtime(&now);
    int nowDay = nowDate->tm_mday;
    //int nowMon = nowDate->tm_mon;
    //int nowYear = nowDate->tm_year;
    // 前回の日付
    struct tm *previousDate;
    time_t previousTime = time;
    previousDate = localtime(&previousTime);
    int previousDay = previousDate->tm_mday;
    //int previousMon = previousDate->tm_mon;
    //int previousYear = previousDate->tm_year;
    // 差分
    int diffDay = nowDay - previousDay;
    //int diffMon = nowMon - previousMon;
    //int diffYear = nowYear - previousYear;
    
    return diffDay;
}

int GameScene::diffMinutes(time_t time)
{
    // 現在の日付
    struct tm *nowDate;
    time_t now;
    nowDate = localtime(&now);
    struct tm *previousDate;
    time_t previousTime = time;
    previousDate = localtime(&previousTime);
    
    return nowDate->tm_min - previousDate->tm_min;
}

