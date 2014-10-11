//
//  ModalLayer.h
//  Gesshi
//
//  Created by Makoto Shiga on 2014/09/21.
//
//

#ifndef __Gesshi__ModalLayer__
#define __Gesshi__ModalLayer__

#include <stdio.h>
#include "cocos2d.h"

class ModalLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool TouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    CREATE_FUNC(ModalLayer);
};

#endif /* defined(__Gesshi__ModalLayer__) */
