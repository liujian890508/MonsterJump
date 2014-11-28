//
//  GameCenter.m
//  MonsterJump
//
//  Created by 刘健 on 14-11-24.
//
//

#import "GameCenter.h"

@implementation GameCenter

@synthesize gameCenterAvailable;

#pragma mark Initialization

static GameCenter* _instance = nil;
static UIViewController * currentModalViewController = nil;

+(GameCenter*) getInstance{
    if(!_instance)
    {
        _instance = [[GameCenter alloc] init];
    }
    return _instance;
}

-(BOOL) isGameCenterAvailable
{
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    NSString *reqSysVer = @"4.1";
    NSString *curSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([curSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending);
    return (gcClass && osVersionSupported);
}

-(id)init
{
    if((self = [super init])){
        gameCenterAvailable = [self isGameCenterAvailable];
        if( gameCenterAvailable )
        {
            NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
            [nc addObserver:self selector:@selector(authenticationChanged) name:GKPlayerAuthenticationDidChangeNotificationName object:nil];
        }
    }
    return self;
}

-(void) authenticationChanged
{
    if( [GKLocalPlayer localPlayer].isAuthenticated && !userAuthenticated){
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if(![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated){
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
}

#pragma mark User functions

- (void) authenticaticateLocalUser
{
    if(!gameCenterAvailable) return;
    
    [[GKLocalPlayer localPlayer] setAuthenticateHandler:^(UIViewController *viewController, NSError *error){
        if (error == nil) {
            
            //成功处理
            
            NSLog(@"成功");
            
            NSLog(@"1--alias--.%@",[GKLocalPlayer localPlayer].alias);
            
            NSLog(@"2--authenticated--.%d",[GKLocalPlayer localPlayer].authenticated);
            
            NSLog(@"3--isFriend--.%d",[GKLocalPlayer localPlayer].isFriend);
            
            NSLog(@"4--playerID--.%@",[GKLocalPlayer localPlayer].playerID);
            
            NSLog(@"5--underage--.%d",[GKLocalPlayer localPlayer].underage);
            
        }else {
            //错误处理
            
            NSLog(@"失败  %@",error);
        }
    }];
     
}

-(void) showLeaderboard
{
    if(!gameCenterAvailable) return;
    GKLeaderboardViewController *leaderboardViewController = [[GKLeaderboardViewController alloc] init];
    if( leaderboardViewController != nil)
    {
        leaderboardViewController.leaderboardDelegate = self;
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardViewController animated:YES];
    }
}

-(void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    if( currentModalViewController != nil)
    {
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}

@end
