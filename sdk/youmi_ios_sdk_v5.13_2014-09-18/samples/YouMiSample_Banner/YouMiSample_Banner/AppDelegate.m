//
//  AppDelegate.m
//  YouMiSample_Banner
//
//  Created by 陈建峰 on 13-3-12.
//  Copyright (c) 2013年 陈建峰. All rights reserved.
//

#import "AppDelegate.h"
#import "YouMiConfig.h"
#import "BannerViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // [YouMiConfig setShouldGetLocation:NO];
#warning 替换下面的appID和appSecret为你的appid和appSecret
    [YouMiConfig launchWithAppID:@"facba183861889b4" appSecret:@"dcab0ef939134692"];
    [YouMiConfig setIsTesting:YES];
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    BannerViewController *bannerViewController = [[[BannerViewController alloc] init] autorelease];
    UINavigationController *nav = [[[UINavigationController alloc] initWithRootViewController:bannerViewController] autorelease];
    self.window.rootViewController = nav;
    
    return YES;
}

- (void)dealloc {
    [_window release];
    [super dealloc];
}

@end
