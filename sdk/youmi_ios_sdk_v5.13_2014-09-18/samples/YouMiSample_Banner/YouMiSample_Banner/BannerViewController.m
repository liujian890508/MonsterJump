//
//  BannerViewController.m
//  YouMiSDK
//
//  Created by 陈建峰 on 13-2-27.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import "BannerViewController.h"
#import "YouMiView.h"

@implementation BannerViewController
@synthesize textView;

- (id)init {
    self = [super init];
    if (self) {
        self.title = @"有米广告条";
#ifdef __IPHONE_7_0
        if ([[[UIDevice currentDevice] systemVersion] intValue] >= 7) {
            [self setEdgesForExtendedLayout:UIRectEdgeNone];
        }
#endif
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 320x50
    YouMiView *adView320x50=[[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier320x50 delegate:self];
    adView320x50.frame = CGRectMake(0, 0, CGRectGetWidth(adView320x50.bounds), CGRectGetHeight(adView320x50.bounds));
    adView320x50.backgroundColor = [UIColor colorWithWhite:0.8 alpha:0.5];
    [adView320x50 start];
    [self.view addSubview:adView320x50];
    [adView320x50 release];
    
    // 结果显示
    self.textView = [[[UITextView alloc] initWithFrame:CGRectMake(self.view.bounds.size.width/2, 90.0f, 120.0f, 200.0f)] autorelease];
    self.textView.center =CGPointMake(self.view.bounds.size.width/2, 190);
    self.textView.editable = NO;
    self.textView.text = @"日志：\n";
    self.textView.backgroundColor = [UIColor colorWithWhite:0.9 alpha:0.05];
    [self.view addSubview:self.textView];
    
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
    {
        
        // 200x200
        YouMiView *adView200x200=[[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier200x200 delegate:self];
        adView200x200.frame = CGRectMake(0, 50, CGRectGetWidth(adView200x200.bounds), CGRectGetHeight(adView200x200.bounds));
        adView200x200.backgroundColor = [UIColor colorWithWhite:0.8 alpha:0.5];
        [adView200x200 start];
        [self.view addSubview:adView200x200];
        [adView200x200 release];
        
        // 300x250
        YouMiView *adView300x250 = [[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier300x250 delegate:self];
        adView300x250.frame = CGRectMake(0, 250, CGRectGetWidth(adView300x250.bounds), CGRectGetHeight(adView300x250.bounds));
        adView300x250.backgroundColor = [UIColor colorWithWhite:0.8 alpha:0.5];
        [adView300x250 start];
        [self.view addSubview:adView300x250];
        [adView300x250 release];
        
        // 468x60
        YouMiView *adView468x60 = [[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier468x60 delegate:self];
        adView468x60.frame = CGRectMake(0, 500, CGRectGetWidth(adView468x60.bounds), CGRectGetHeight(adView468x60.bounds));
        adView468x60.backgroundColor = [UIColor colorWithWhite:0.8 alpha:0.5];
        [adView468x60 start];
        [self.view addSubview:adView468x60];
        [adView468x60 release];
        
        // 728x90
        YouMiView *adView728x90 = [[YouMiView alloc] initWithContentSizeIdentifier:YouMiBannerContentSizeIdentifier728x90 delegate:self];
        adView728x90.frame = CGRectMake(0, 560, CGRectGetWidth(adView728x90.bounds), CGRectGetHeight(adView728x90.bounds));
        adView728x90.backgroundColor = [UIColor colorWithWhite:0.8 alpha:0.5];
        [adView728x90 start];
        [self.view addSubview:adView728x90];
        [adView728x90 release];
    }
}

- (void)viewWillAppear:(BOOL)animated{
    [self.navigationController.navigationBar setHidden:YES];
    [super viewWillAppear:animated];
}

#pragma youmidelegate

- (void)didReceiveAd:(YouMiView *)adView {
    textView.text = [textView.text stringByAppendingFormat:@"%u 获得广告\n",adView.contentSizeIdentifier];
}

- (void)didFailToReceiveAd:(YouMiView *)adView  error:(NSError *)error {
    textView.text = [textView.text stringByAppendingFormat:@"%u 获取广告失败\n",adView.contentSizeIdentifier];
}

- (void)willPresentScreen:(YouMiView *)adView {
    textView.text = [textView.text stringByAppendingFormat:@"%u 将要显示全屏广告\n",adView.contentSizeIdentifier];
}

- (void)didPresentScreen:(YouMiView *)adView {
    textView.text = [textView.text stringByAppendingFormat:@"%u 已显示全屏广告\n",adView.contentSizeIdentifier];
}

- (void)willDismissScreen:(YouMiView *)adView {
    textView.text = [textView.text stringByAppendingFormat:@"%u 将要退出全屏广告\n",adView.contentSizeIdentifier];
}

- (void)didDismissScreen:(YouMiView *)adView {
    textView.text = [textView.text stringByAppendingFormat:@"%u 已退出全屏广告\n",adView.contentSizeIdentifier];
}

- (void)dealloc {
    self.textView = nil;
    [super dealloc];
}


@end
