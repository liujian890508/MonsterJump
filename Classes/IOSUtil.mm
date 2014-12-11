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

static CGSize calculateStringSize(NSString *str, id font, CGSize *constrainSize)
{
    NSArray *listItems = [str componentsSeparatedByString: @"\n"];
    CGSize dim = CGSizeZero;
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize->width > 0 ? constrainSize->width
    : 0x7fffffff;
    textRect.height = constrainSize->height > 0 ? constrainSize->height
    : 0x7fffffff;
    
    
    for (NSString *s in listItems)
    {
        CGSize tmp = [s sizeWithFont:font constrainedToSize:textRect];
        
        if (tmp.width > dim.width)
        {
            dim.width = tmp.width;
        }
        
        dim.height += tmp.height;
    }
    
    return dim;
}

std::string IOSUtil::getUniquelyIdentifies()
{
//    NSString *uniStr = NULL;
//    if( [[[UIDevice currentDevice] systemVersion] floatValue] >= 6.0)
//    {
//        NSLog(@"device version: 6.0");
//        uniStr = [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString];
//    }
//    else if( [[[UIDevice currentDevice] systemVersion] floatValue] >= 5.0)
//    {
//        NSLog(@"deivce version: 5.0");
//        CFUUIDRef puuid = CFUUIDCreate(nil);
//        CFStringRef uuidString = CFUUIDCreateString(nil, puuid);
//        uniStr = (NSString*)CFStringCreateCopy(NULL, uuidString);
//        CFRelease(puuid);
//        CFRelease(uuidString);
//    }
//    return [uniStr cStringUsingEncoding: NSUTF8StringEncoding];
    return "";
}

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


