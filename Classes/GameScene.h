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

#define PNG_BACKGROUND "BackGround.png"
#define MOVING_TIME 0.2f;

class GameScene : public cocos2d::Layer
{
protected:
    enum Tag
    {
        kTagBackground = 1,     // 画像のタグ
        kTagHamster    = 10000, // ハムスターの基準タグ
    };
    
    enum kZOrder
    {
        kZOrderBackground, // zオーダー
        kZOrderHamster,    // ハムスターの基準タグ
    };
    
   
    void moveHamster(float frame);
    
    //背景画像
    cocos2d::Sprite* m_background;
    void showBackground();
    
    float m_hamsterSize;
    void showHamster();
    void initForVariables();
    cocos2d::Point getPosition(int posIndexX, int posIndexY);
    int getTag(int index);
    

public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__