//
//  IOSUtil.cpp
//  MonsterJump
//
//  Created by abc on 14-4-13.
//
//

#include "IOSUtil.h"

#include <AdSupport/AdSupport.h>
#include "GameCenter.h"
#include "InterfaceUtil.h"

void IOSUtil::disableScreenAutoLock(bool flag)
{
    if(flag){
        [UIApplication sharedApplication].idleTimerDisabled = YES;
    }else{
        [UIApplication sharedApplication].idleTimerDisabled = NO;
    }
}

void IOSUtil::showLeaderboard()
{
    [[GameCenter getInstance] showLeaderboard];
}

void IOSUtil::retrieveTopTenScores(std::string &category)
{
    NSString *nsCategroy = [NSString stringWithUTF8String:category.c_str()];
    [[GameCenter getInstance]retrieveTopTenScores: nsCategroy];
}

void IOSUtil::reportScore(int score, std::string &category)
{
    NSString *nsCategory = [NSString stringWithUTF8String:category.c_str()];
    [[GameCenter getInstance] reportScore:score forCategory:nsCategory];
}

void IOSUtil::showCommentary()
{
	[[InterfaceUtil getInstance] showCommentary];
}

