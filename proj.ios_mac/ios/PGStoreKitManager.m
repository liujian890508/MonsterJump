#import "PGStoreKitManager.h"
 
@implementation PGStoreKitManager
 
+ (PGStoreKitManager *)getInstance
{
    static PGStoreKitManager *mgr = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        mgr = [[self alloc] init];
    });
    return mgr;
}
 
- (id)init
{
    self = [super init];
    if (self) {
        [self initData];
        return self;
    }
    return nil;
}
 
- (void)initData
{
    _enableGameCenter = NO;
    _viewController = nil;
}
 
- (void)showMessage:(NSString *)title Message:(NSString *)msg
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title message:msg delegate:self cancelButtonTitle:@"ȷ��" otherButtonTitles:nil, nil];
    [alert show];
}
 
- (void)showLoadingView:(NSString *)title
{
    _loadingAlert= [[UIAlertView alloc] initWithTitle:title message:@"" delegate:self cancelButtonTitle:nil otherButtonTitles:nil, nil];
    [_loadingAlert show];
}
 
- (void)removeLoadingView
{
    [_loadingAlert dismissWithClickedButtonIndex:0 animated:YES];
}
 
#pragma mark - GameCenter
- (void)authenticateLocalPlayer
{
    GKLocalPlayer* localPlayer = [GKLocalPlayer localPlayer];
    if ([localPlayer isAuthenticated] == NO) {
        localPlayer.authenticateHandler = ^(UIViewController *viewController,
          NSError *error) {
            if (error) {
                _enableGameCenter = NO;
            }else{
                _enableGameCenter = YES;
                if(viewController) {
                    [viewController presentViewController:viewController animated:YES completion:nil];
                }
            }
        };
    }else{
        _enableGameCenter = YES;
    }
}
 
/**
 �ϴ�����
 */
- (void)reportScore : (NSString*)identifier hiScore:(int64_t)score;
{
    if (score < 0 || !_enableGameCenter)
		return;
	GKScore *scoreBoard = [[GKScore alloc] initWithLeaderboardIdentifier:identifier];
    scoreBoard.value = score;
    [GKScore reportScores:@[scoreBoard] withCompletionHandler:^(NSError *error) {
        if (error) {
            // handle error
        }
    }];
}
 
/**
 �ϴ��ɾ�
 */
- (void)reportAchievementIdentifier : (NSString*)identifier percentComplete:(float)percent
{
    if (percent < 0 || !_enableGameCenter)
		return;
	
    GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier: identifier];
    if (achievement){
		achievement.percentComplete = percent;
        [GKAchievement reportAchievements:@[achievement] withCompletionHandler:^(NSError *error) {
            if (error) {
                // handle error
            }
        }];
    }
}
 
/**
 ��ʾ���а�
 */
- (void)showLeaderboard : (NSString*)leaderboard
{
    if (!_enableGameCenter)
		return;
    GKGameCenterViewController *gameCenterViewController = [[GKGameCenterViewController alloc] init];
    gameCenterViewController.viewState = GKGameCenterViewControllerStateLeaderboards;
    gameCenterViewController.gameCenterDelegate = self;
    [_viewController presentViewController:gameCenterViewController animated:YES completion:nil];
}
 
/**
 ��ʾ�ɾ�
 */
- (void)showAchievements
{
    if (!_enableGameCenter)
		return;
 
    GKGameCenterViewController *gameCenterViewController = [[GKGameCenterViewController alloc] init];
    gameCenterViewController.viewState = GKGameCenterViewControllerStateAchievements;
    gameCenterViewController.gameCenterDelegate = self;
    [_viewController presentViewController:gameCenterViewController animated:YES completion:nil];
}
 
#pragma mark gameCenterViewController Close�ص�
- (void)gameCenterViewControllerDidFinish:(GKGameCenterViewController *)gameCenterViewController
{
    [_viewController dismissViewControllerAnimated:YES completion:nil];
}
 
 
 
 
 
//---------------------------------------------------------
#pragma mark - IAP
- (BOOL)canProcessPayments
{
    if ([SKPaymentQueue canMakePayments]) {
        return YES;
    } else {
        return NO;
    }
}
 
 
/**
 ��ʼ��������
 */
- (void)initStoreKit
{
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
}
 
/**
 �����Ʒ
 */
- (void)purchaseItem: (NSString *)identifier
{
    [self showLoadingView:@"Access Store..."];
    
    if (![self canProcessPayments]) {
        NSLog(@"1.ʧ��-->SKPaymentQueue canMakePayments NO");
        [self removeLoadingView];
        return;
    }
    NSLog(@"1.�ɹ�-->�����Ʒ��Ϣ...%@", identifier);
    
    // ʹ��������Ʒ��Ϣʽ����
    SKProductsRequest *request= [[SKProductsRequest alloc]
                                 initWithProductIdentifiers: [NSSet setWithObject: identifier]];
    request.delegate = self;
    [request start];
}
 
// SKProductsRequest �Ļص�
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *myProduct = response.products;
 
    if (myProduct.count == 0) {
        NSLog(@"2.ʧ��-->�޷���ȡ��Ʒ��Ϣ������ʧ�ܡ�invalidProductIdentifiers = %@",response.invalidProductIdentifiers);
        [self removeLoadingView];
        return;
    }
    NSLog(@"2.�ɹ�-->��ȡ��Ʒ��Ϣ�ɹ������ڹ���...");
    SKPayment * payment = [SKPayment paymentWithProduct:myProduct[0]];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
}
 
// SKPayment �Ļص�
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    NSLog(@"3.�ɹ�-->����ƻ���������ݣ����ڴ���...");
    for (SKPaymentTransaction *transaction in transactions){
        switch (transaction.transactionState){
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
                
            default:
                break;
        }
    }
}
 
// ��������
- (void) completeTransaction: (SKPaymentTransaction*)transaction
{
    NSLog(@"4.�ɹ�-->�������� SKPaymentTransactionStatePurchased");
    [self removeLoadingView];
	// ��¼���׺��ṩ��Ʒ �����������봦��
    [self recordTransaction: transaction];
    [self provideContent: transaction.payment.productIdentifier];
	
    // �Ƴ� transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}
 
// ���ý���
- (void) restoreTransaction: (SKPaymentTransaction*)transaction
{
    NSLog(@"4.�ɹ�-->���ý��� SKPaymentTransactionStateRestored");
    [self recordTransaction: transaction];
    [self provideContent: transaction.originalTransaction.payment.productIdentifier];
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}
 
// ����ʧ��
- (void) failedTransaction: (SKPaymentTransaction*)transaction
{
    [self removeLoadingView];
    NSLog(@"4.�ɹ�-->����ʧ�� SKPaymentTransactionStateRestored error.code:%d",(int)transaction.error.code);
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}
 
// ���׼�¼
- (void) recordTransaction: (SKPaymentTransaction*)transacation
{
    NSLog(@"4.�ɹ�-->���׼�¼, �����ڴ˴��洢��¼");
}
 
// �ṩ��Ʒ
- (void) provideContent: (NSString*)identifier
{
    NSLog(@"4.�ɹ�-->���׳ɹ������ṩ��Ʒ identifier = %@", identifier);
    
    [self removeLoadingView];
    [self showMessage:@"Success" Message:@"You have successfully purchased."];
}
 
@end