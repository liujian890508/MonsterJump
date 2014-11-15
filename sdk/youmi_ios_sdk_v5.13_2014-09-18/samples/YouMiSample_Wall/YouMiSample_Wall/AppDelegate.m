//
//  AppDelegate.m
//  YouMiSample_Wall
//
//  Created by 陈建峰 on 13-3-12.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import "AppDelegate.h"
#import "YouMiConfig.h"
#import "YouMiPointsManager.h"
#import "offerWallViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // [YouMiConfig setShouldGetLocation:NO];
    // 初始化信息
   // 替换下面的appID和appSecret为你的appid和appSecret
    [YouMiConfig launchWithAppID:@"6191437ca20f2a14" appSecret:@"45e2b6f1f2a6ef2b"];
    // 开启积分管理[本例子使用自动管理];
    [YouMiPointsManager enable];
    // 开启积分墙
    [YouMiWall enable];
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    // 设置显示积分墙的全屏UIWindow
    [YouMiConfig setFullScreenWindow:self.window];
    
    offerWallViewController *wallViewController = [[[offerWallViewController alloc] initWithNibName:@"offerWallViewController" bundle:nil] autorelease];
    UINavigationController *nav = [[[UINavigationController alloc] initWithRootViewController:wallViewController] autorelease];
    [nav.navigationBar setHidden:YES];
    self.window.rootViewController = nav;

    return YES;
}

- (void)dealloc {
    [_window release];
    [super dealloc];
}


@end
