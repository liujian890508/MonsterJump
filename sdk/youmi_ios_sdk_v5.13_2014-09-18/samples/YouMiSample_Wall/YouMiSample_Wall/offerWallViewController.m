//
//  offerWallViewController.m
//  YouMiSample_Wall
//
//  Created by 陈建峰 on 13-9-11.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import "offerWallViewController.h"
#import "SourceADViewController.h"
#import "SpotViewController.h"

@interface offerWallViewController ()
@property (retain,nonatomic) SourceADViewController *tableviewController;
@property (retain,nonatomic) SpotViewController *spotViewController;
@end

@implementation offerWallViewController
@synthesize tableviewController = _tableviewController;
@synthesize spotViewController = _spotViewController;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
#ifdef __IPHONE_7_0
        if ([[[UIDevice currentDevice] systemVersion] intValue] >= 7) {
            [self setEdgesForExtendedLayout:UIRectEdgeNone];
        }
#endif
        _tableviewController = [[SourceADViewController alloc]initWithNibName:@"sourceADViewController" bundle:nil];
        _spotViewController = [[SpotViewController alloc] initWithNibName:@"SpotViewController" bundle:nil];
        // 监听获得积分的消息，需要在启动时[YouMiPointsManager enable]或者[YouMiPointsManager enableManually]
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(pointsGotted:) name:kYouMiPointsManagerRecivedPointsNotification object:nil];
        
        [self.inAppStoreSwitch setOn:[YouMiConfig useInAppStore] animated:NO];
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
     self.currentPointsTitle.text = @"当前积分：0";
    // Do any additional setup after loading the view from its nib.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setHidden:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)adCountsValueChanged:(id)sender {
    self.adCounts.text = [NSString stringWithFormat:@"%d",(int)self.adCountStepper.value];
}

- (IBAction)pointWallButtonPressed:(id)sender {
    [YouMiWall showOffers:YES didShowBlock:^{
        NSLog(@"有米积分墙已显示");
    } didDismissBlock:^{
        NSLog(@"有米积分墙已退出");
    }];
}

- (IBAction)recWallButtonPressed:(id)sender {
    [YouMiWall showOffers:NO didShowBlock:^{
        NSLog(@"有米推荐墙已显示");
    } didDismissBlock:^{
        NSLog(@"有米推荐墙已退出");
    }];
}

- (IBAction)requestSourceADPressed:(id)sender {
    [YouMiWall requestOffersOpenData:YES page:[self.adPageLabel.text intValue] count:[self.adCounts.text intValue] revievedBlock:^(NSArray *theApps, NSError *error) {
        // theApps 是 YouMiWallAppModel 的对象列表
        if (!error) {
            _tableviewController.apps = theApps;
            [self.navigationController pushViewController:_tableviewController animated:YES];
        }
    }];
}

- (IBAction)switchValueChanged:(id)sender {
    [YouMiConfig setUseInAppStore:self.inAppStoreSwitch.on];
}

- (IBAction)adPageChanged:(id)sender {
    self.adPageLabel.text = [NSString stringWithFormat:@"%d",(int)self.adPageStepper.value];
}

- (IBAction)requestRewardSpotData:(id)sender {
    [self.navigationController pushViewController:_spotViewController animated:YES];
}

- (IBAction)onLineButtonPressed:(id)sender {
    _onLineLabel.text = [YouMiConfig onlineValueForKey:@"testCh"];
    if ([_onLineLabel isEqual:@"(NULL)"]) {
        _onLineLabel.text = @"key错误或者无网络连接";
    }
}

// 获得积分
- (void)pointsGotted:(NSNotification *)notification {
    NSDictionary *dict = [notification userInfo];
    NSNumber *freshPoints = [dict objectForKey:kYouMiPointsManagerFreshPointsKey];
    NSLog(@"积分信息：%@", dict);
    
    // 这里的积分不应该拿来使用, 只是用于告诉一下用户, 可以通过 [YouMiPointsManager spendPoints:]来使用积分
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"通知" message:[NSString stringWithFormat:@"获得%@积分", freshPoints] delegate:nil cancelButtonTitle:@"好的" otherButtonTitles:nil];
    [alert show];
    [alert release];
    int *points = [YouMiPointsManager pointsRemained];
    self.currentPointsTitle.text = [NSString stringWithFormat:@"当前积分: %d", *points];
    
    
    // 手动积分管理可以通过下面这种方法获得每份积分的信息。
    NSArray *pointInfos = dict[kYouMiPointsManagerPointInfosKey];
    for (NSDictionary *aPointInfo in pointInfos) {
        // aPointInfo 是每份积分的信息，包括积分数，userID，下载的APP的名字
        NSLog(@"积分数：%@", aPointInfo[kYouMiPointsManagerPointAmountKey]);
        NSLog(@"userID：%@", aPointInfo[kYouMiPointsManagerPointUserIDKey]);
        NSLog(@"产品名字：%@", aPointInfo[kYouMiPointsManagerPointProductNameKey]);
        
        // TODO 按需要处理
    }
}


- (void)dealloc {
    [_adCounts release];
    [_inAppStoreSwitch release];
    [_adCountStepper release];
    [_tableviewController release];
    [_currentPointsTitle release];
    [_adPageStepper release];
    [_adPageLabel release];
    [_onLineLabel release];
    [super dealloc];
}

- (void)viewDidUnload {
    [self setAdCounts:nil];
    [self setInAppStoreSwitch:nil];
    [self setAdCountStepper:nil];
    [self setCurrentPointsTitle:nil];
    [self setAdPageStepper:nil];
    [self setAdPageLabel:nil];
    [self setOnLineLabel:nil];
    [super viewDidUnload];
}
@end
