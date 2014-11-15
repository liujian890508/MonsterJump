//
//  SpotViewController.m
//  YouMiSample_Wall
//
//  Created by 陈建峰 on 13-9-16.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import "SpotViewController.h"
#import "YouMiWallSpot.h"
#import "YouMiWallSpotView.h"

@interface SpotViewController ()

@end

@implementation SpotViewController

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
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setHidden:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)showSpot:(id)sender {
    if ([YouMiWallSpot isReady]) {
        [YouMiWallSpot showSpotViewWithBlock:^{
            NSLog(@"积分插播退出");
        }];
    }
}

- (IBAction)showMySpot:(id)sender {
    UIView *subview = [[UIView alloc] initWithFrame:self.view.bounds];
    subview.userInteractionEnabled = YES;
    subview.backgroundColor = [UIColor colorWithWhite:0.5 alpha:0.5];
    subview.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button setTitleColor:[UIColor blueColor] forState:UIControlStateHighlighted];
    [button setTitle:@"返回" forState:UIControlStateNormal];
    [button.titleLabel setFont:[UIFont systemFontOfSize:28]];
    button.frame =CGRectMake(0.0, 0, 100, 60);
    [button addTarget:self action:@selector(cancle:) forControlEvents:UIControlEventTouchUpInside];
    button.userInteractionEnabled = YES;
    button.center = CGPointMake(self.view.bounds.size.width/2, (self.view.bounds.size.height - 280)/2  +250);
    
    YouMiWallSpotView  *wallSpotView = [[[YouMiWallSpotView alloc] init] autorelease];
    wallSpotView.center = CGPointMake(self.view.bounds.size.width/2, self.view.bounds.size.height/2);
    if ([wallSpotView isReady]) {
        [subview addSubview:wallSpotView];
        [self.view addSubview:subview];
        [subview addSubview:button];
    }
}

-(void)cancle:(id)sender{
    UIButton *button = (UIButton *)sender;
    UIView *superView = [button superview];
    [superView removeFromSuperview];
}
@end
