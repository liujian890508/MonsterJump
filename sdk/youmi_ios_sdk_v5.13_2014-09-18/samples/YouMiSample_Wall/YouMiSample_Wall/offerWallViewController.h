//
//  offerWallViewController.h
//  YouMiSample_Wall
//
//  Created by 陈建峰 on 13-9-11.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "YouMiWall.h"

@interface offerWallViewController : UIViewController
@property (retain, nonatomic) IBOutlet UILabel *adCounts;
@property (retain, nonatomic) IBOutlet UISwitch *inAppStoreSwitch;
@property (retain, nonatomic) IBOutlet UIStepper *adCountStepper;
@property (retain, nonatomic) IBOutlet UILabel *currentPointsTitle;
@property (retain, nonatomic) IBOutlet UIStepper *adPageStepper;
@property (retain, nonatomic) IBOutlet UILabel *adPageLabel;
@property (retain, nonatomic) IBOutlet UILabel *onLineLabel;

- (IBAction)adCountsValueChanged:(id)sender;
- (IBAction)pointWallButtonPressed:(id)sender;
- (IBAction)recWallButtonPressed:(id)sender;
- (IBAction)requestSourceADPressed:(id)sender;
- (IBAction)switchValueChanged:(id)sender;
- (IBAction)adPageChanged:(id)sender;
- (IBAction)requestRewardSpotData:(id)sender;
- (IBAction)onLineButtonPressed:(id)sender;
@end
