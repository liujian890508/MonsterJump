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
��½gamecenter����������setViewController
*/
- (void)authenticateLocalPlayer;

/**
�ϴ�����
*/
- (void)reportScore : (NSString*)identifier hiScore:(int64_t)score;

/**
�ϴ��ɾ�
*/
- (void)reportAchievementIdentifier : (NSString*)identifier percentComplete:(float)percent;

/**
��ʾ���а�
*/
- (void)showLeaderboard : (NSString*)leaderboard;

/**
��ʾ�ɾ�
*/
- (void)showAchievements;
// iap ----------------------------------------
/**
��ʼ��������
*/
- (void)initStoreKit;

/**
�����Ʒ
*/
- (void)purchaseItem: (NSString*)identifier;
@end