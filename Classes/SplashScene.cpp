//
//  SplashScene.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/08/23.
//
//

#include "SplashScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* SplashScene::scene()
{
    auto scene = Scene::create();
    
    auto layer = SplashScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

void SplashScene::showSplash()
{
    Size winSize = Director::getInstance()->getVisibleSize();
    
    // 背景を生成
    m_splash = Sprite::create(PNG_SPLASH);
    m_splash->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(m_splash,kZOrderSplash, kTagSplash);
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    showSplash();
    
    // 1.5秒後にタイトルに移動する
    this->scheduleOnce(schedule_selector(SplashScene::gameStart), 1.5f);

    return true;
}

void SplashScene::gameStart(float time) {
    auto scene = GameScene::scene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}