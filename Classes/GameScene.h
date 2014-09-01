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
#include "FertilizerSprite.h"

#define PNG_BACKGROUND "BackGround.png"
#define MOVING_TIME 0.2f;

using namespace std;

class GameScene : public cocos2d::Layer
{
protected:
    enum Tag
    {
        kTagBackground = 1,     // 画像のタグ
        kTagHamster    = 10001, // ハムスターの基準タグ
        kTagFertilizer = 20001, // 肥料のタグ
    };
    
    enum kZOrder
    {
        kZOrderBackground, // zオーダー
        kZOrderFertilizer, // 肥料の基準タグ
        kZOrderHamster,    // ハムスターの基準タグ
    };
    
   
    void moveHamster(float frame);
    
    //背景画像
    cocos2d::Sprite* m_background;
    void showBackground();
    
    void showHamster();
    void initForVariables();
    cocos2d::Point getPosition(int posIndexX, int posIndexY);
    int getHamsterTag(int index);
    int m_fertilizer_count;
    
    cocos2d::Vector<FertilizerSprite*> fertilizers;
    
    int getNextFertilizerTag();
    void harvestFertilizer(cocos2d::Ref* pSender);
    void showFertilizer(bool direct);
    long m_score;
    void showScore();
    void showMenuButton();
    bool m_manual_moving_hamster;
    cocos2d::Label* scoreLabel;
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif // __GAMESCENE_SCENE_H__