//
//  IOSUtil.h
//  MonsterJump
//
//  Created by abc on 14-4-13.
//
//

#ifndef __MonsterJump__IOSUtil__
#define __MonsterJump__IOSUtil__

#include "cocos2d.h"
#include <iostream>
USING_NS_CC;

class IOSUtil
{
public:
    static std::string getUniquelyIdentifies();
    
    static void disableScreenAutoLock(bool flag);
    
    static void showLeaderboard();
    
    static void retrieveTopTenScores(std::string &category);
    
    static void reportScore(int score, std::string &category);
};

#endif /* defined(__Shqmm__FMIOSUtil__) */
