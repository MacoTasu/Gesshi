//
//  SplashScene.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/08/23.
//
//

#ifndef __HamuHamu__SplashScene__
#define __HamuHamu__SplashScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"
#include "StoneSprite.h"

#define PNG_SPLASH "Default-568h@2x.png"

class SplashScene : public cocos2d::Layer
{
protected:
    enum Tag
    {
        kTagSplash = 1,     // 画像のタグ
    };
    
    enum kZOrder
    {
        kZOrderSplash, // zオーダー
    };
    cocos2d::Sprite* m_splash;
    void showText();
    void gameStart(float time);
    void onEnter();
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(SplashScene);
};

#endif /* defined(__HamuHamu__SplashScene__) */
