//
//  AudioManager.h
//  HamuHamu
//
//  Created by Makoto Shiga on 2014/09/20.
//
//

#ifndef __HamuHamu__AudioManager__
#define __HamuHamu__AudioManager__

#include <stdio.h>
#include <string>

class AudioManager
{
public:
    AudioManager();
    virtual ~AudioManager();
    void preloadSE(const std::string &id);
    unsigned int playSE(const std::string &id);
private:
    std::string ext;
    const char* getFileName(const std::string &id);
};


#endif /* defined(__HamuHamu__AudioManager__) */
