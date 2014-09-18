//
//  SplashScene.cpp
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/08/23.
//
//

#include "SplashScene.h"
#include "GameScene.h"
#include "LabelRPG.h"
#include "GoogleAnalyticsTracker.h"

USING_NS_CC;

Scene* SplashScene::scene()
{
    auto scene = Scene::create();
    
    auto layer = SplashScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

void SplashScene::onEnter()
{
    Layer::onEnter();
    
    GoogleAnalyticsTracker::sendScreen("Splashcene");
}

void SplashScene::showText()
{
    TTFConfig ttfConfig("Hiragino Sans GB W3.otf",
                        30,
                        GlyphCollection::DYNAMIC);
    // 基本はLabelと同じ
    auto textLabel = LabelRPG::createWithTTF(ttfConfig, "");
    textLabel->setVerticalAlignment(cocos2d::TextVAlignment::TOP);
    textLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    textLabel->setColor(Color3B::WHITE);
    
    //setPositionは使っても意味ないです
    //テキスト送りしながらsetPositionで位置を変えてるので、以下でベースの位置を設定してください
    textLabel->setOriginalPosition(Point(30, this->getContentSize().height/2 + textLabel->getContentSize().height + 20));
    
    // テキスト送り開始（1文字 0.05秒で出す）
    textLabel->setStringWithRunText("これはげっ歯族の命を\nかけた戦いである", 0.1f);
    
    this->addChild(textLabel);
}

bool SplashScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    showText();
    
    // 1.5秒後にタイトルに移動する
    this->scheduleOnce(schedule_selector(SplashScene::gameStart), 3.0f);

    return true;
}

void SplashScene::gameStart(float time) {
    auto scene = GameScene::scene();
    // 0.5秒かけてホワイトアウトしてタイトルに移動する
    TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
}