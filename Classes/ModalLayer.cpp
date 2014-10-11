//
//  ModalLayer.cpp
//  Gesshi
//
//  Created by Makoto Shiga on 2014/09/21.
//
//

#include "ModalLayer.h"
#include "MenuSound.h"
#define kModalLayerPriority -1

using namespace cocos2d;

bool ModalLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
        return true;
    };
    
    Director* pDirector = Director::getInstance();
    auto dip = pDirector->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    dip->setPriority(listener, kModalLayerPriority);
    
    Size visibleSize = pDirector->getVisibleSize();
    
    Sprite* frame = Sprite::create("Modal.png");
    frame->setPosition(Point(visibleSize.width/2, visibleSize.height/1.75));
    this->addChild(frame);
    
    auto pCloseItem = MenuItemImage::create("ModalButtonEnable.png","ModalButtonDisable.png",CC_CALLBACK_1(ModalLayer::menuCloseCallback,this));
    auto pSelectItem = MenuItemImage::create("ModalButtonEnable.png","ModalButtonDisable.png",CC_CALLBACK_1(ModalLayer::menuCloseCallback,this));
    Menu*  pMenu = Menu::create(pSelectItem,pCloseItem,NULL);
    pMenu->setPosition(Point(frame->getPosition().x, frame->getPosition().y/1.5));
    pMenu->alignItemsHorizontallyWithPadding(10.0f);
    
    this->addChild(pMenu);
    
    return true;
}

bool ModalLayer::TouchBegan(Touch* touch, Event* event) {
    // can not touch on back layers
    return true;
}

void ModalLayer::menuCloseCallback(Ref* pSender)
{
    this->removeFromParentAndCleanup(true);
    
    auto pDirector = Director::getInstance()->getEventDispatcher();
    pDirector->removeEventListenersForTarget(this);
}