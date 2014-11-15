//
//  BannerViewController.h
//  YouMiSDK
//
//  Created by 陈建峰 on 13-2-27.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YouMiDelegateProtocol.h"

@interface BannerViewController : UIViewController<YouMiDelegate>

@property (nonatomic,retain) UITextView *textView;

@end
