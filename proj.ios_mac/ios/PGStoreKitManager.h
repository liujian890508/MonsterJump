#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import <StoreKit/StoreKit.h>

@class ViewController;
@interface PGStoreKitManager : NSObject<GKGameCenterControllerDelegate, SKPaymentTransactionObserver, SKProductsRequestDelegate>
{
UIAlertView *_loadingAlert;
BOOL _enableGameCenter;
}

@property (nonatomic, readwrite, strong) ViewController* viewController;
+ (PGStoreKitManager *)getInstance;

// game center ----------------------------------------
/**
登陆gamecenter，请先设置setViewController
*/
- (void)authenticateLocalPlayer;

/**
上传积分
*/
- (void)reportScore : (NSString*)identifier hiScore:(int64_t)score;

/**
上传成就
*/
- (void)reportAchievementIdentifier : (NSString*)identifier percentComplete:(float)percent;

/**
显示排行版
*/
- (void)showLeaderboard : (NSString*)leaderboard;

/**
显示成就
*/
- (void)showAchievements;
// iap ----------------------------------------
/**
初始化内消费
*/
- (void)initStoreKit;

/**
购买产品
*/
- (void)purchaseItem: (NSString*)identifier;
@end