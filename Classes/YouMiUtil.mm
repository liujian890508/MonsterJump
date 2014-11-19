//
//  YouMiUtil.cpp
//  GameJump
//
//  Created by admin on 14-11-19.
//
//

#include "YouMiUtil.h"
#import "YouMiWall.h"
#import "YouMiPointsManager.h"
#import "YouMiWallSpot.h"
#import "YouMiWallSpotView.h"

void YouMiUtil::showOffers(bool flag)
{
    [YouMiWall showOffers:NO didShowBlock:^{
        NSLog(@"有米积分墙已显示");
    }didDismissBlock:^{
        NSLog(@"有米积分墙已退出");
    }];
}

int YouMiUtil::getYouMiScore()
{
    int *points = [YouMiPointsManager pointsRemained];
    int score = *points;
    free(points);
    return score;
}

void YouMiUtil::spendPoints(int score)
{
    [YouMiPointsManager spendPoints:score];
}

void YouMiUtil::showSpot()
{
    if( [YouMiWallSpot isReady])
    {
        [YouMiWallSpot showSpotViewWithBlock:^{
            NSLog(@"积分插播退出");
        }];
    }
}
