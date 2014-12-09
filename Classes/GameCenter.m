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
    
    [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:^(NSError *error){
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

- (void) reportScore: (int64_t) score forCategory: (NSString*) category
{
    GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:category] autorelease];
    scoreReporter.value = score;
    
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if (error != nil)
        {
            // handle the reporting error
            NSLog(@"上传分数出错.");
            //If your application receives a network error, you should not discard the score.
            //Instead, store the score object and attempt to report the player’s process at
            //a later time.
        }else {
            NSLog(@"上传分数成功");
        }
        
    }];
}

- (void) retrieveTopTenScores
{
    GKLeaderboard *leaderboardRequest = [[GKLeaderboard alloc] init];
    if (leaderboardRequest != nil)
    {
        leaderboardRequest.playerScope = GKLeaderboardPlayerScopeGlobal;
        leaderboardRequest.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardRequest.range = NSMakeRange(1,10);
        leaderboardRequest.category = @"TS_LB";
        [leaderboardRequest loadScoresWithCompletionHandler: ^(NSArray *scores, NSError *error) {
            if (error != nil){
                // handle the error.
                NSLog(@"下载失败");
            }
            if (scores != nil){
                // process the score information.
                NSLog(@"下载成功....");
                NSArray *tempScore = [NSArray arrayWithArray:leaderboardRequest.scores];
                for (GKScore *obj in tempScore) {
                    NSLog(@"    playerID            : %@",obj.playerID);
                    NSLog(@"    category            : %@",obj.category);
                    NSLog(@"    date                : %@",obj.date);
                    NSLog(@"    formattedValue    : %@",obj.formattedValue);
                    NSLog(@"    value                : %d",obj.value);
                    NSLog(@"    rank                : %d",obj.rank);
                    NSLog(@"**************************************");
                }
            }
        }];
    }
}

- (void) retrieveFriends
{
    GKLocalPlayer *lp = [GKLocalPlayer localPlayer];
    if (lp.authenticated)
    {
        [lp loadFriendsWithCompletionHandler:^(NSArray *friends, NSError *error) {
            if (error == nil)
            {
                [self loadPlayerData:friends];
            }
            else
            {
                ;// report an error to the user.
            }
        }];
        
    }
}

- (void) loadPlayerData: (NSArray *) identifiers
{
    [GKPlayer loadPlayersForIdentifiers:identifiers withCompletionHandler:^(NSArray *players, NSError *error) {
        if (error != nil)
        {
            // Handle the error.
        }
        if (players != nil)
        {
            NSLog(@"得到好友的alias成功");
            GKPlayer *friend1 = [players objectAtIndex:0];
            NSLog(@"friedns---alias---%@",friend1.alias);
            NSLog(@"friedns---isFriend---%d",friend1.isFriend);
            NSLog(@"friedns---playerID---%@",friend1.playerID);
        }
    }];
}



@end
