//
//  GameScene.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/07/11.
//
//

#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include <iostream>

#include "cocos2d.h"
#include "Config.h"
#include "NendIconModule.h"
#include "NendModule.h"
#include "GesshiSprite.h"

#define PNG_BACKGROUND "BackGround.png"
#define MOVING_TIME 0.2f;

using namespace std;

class GameScene : public cocos2d::Layer
{
protected:
    enum Tag
    {
        kTagBackground = 1,     // 画像のタグ
        kTagGesshi     = 10001, // ハムスターの基準タグ
    };
    
    enum kZOrder
    {
        kZOrderBackground, // zオーダー
        kZOrderGesshi,    // ハムスターの基準タグ
    };
    
    //背景画像
    cocos2d::Sprite* m_background;
    void showBackground();
    
    void showGesshi();
    void initForVariables();
    cocos2d::Point getPosition(int posIndexX, int posIndexY);
    int getGesshiTag(int index);

    cocos2d::Vector<GesshiSprite*> gesshies;
    
    void createGesshi();
    long m_gp;
    int  m_life_days;
    void showHeader();
    void showMenuButton();
    void createIconBanner();
    void createButtomBanner();
    bool m_manual_moving_gesshi;
    cocos2d::Label* scoreLabel;
    cocos2d::Label* daysLabel;
    cocos2d::Sprite* scoreBoard;
    cocos2d::Sprite* careBoard;
    int diffDays(time_t time);
    int diffMinutes(time_t time);
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    void onEnter();
    
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif // __GAMESCENE_SCENE_H__