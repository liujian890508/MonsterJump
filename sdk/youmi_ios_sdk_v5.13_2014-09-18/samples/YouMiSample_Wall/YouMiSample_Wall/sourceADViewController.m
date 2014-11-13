//
//  SourceADViewController.m
//  YouMiSample_Wall
//
//  Created by 陈建峰 on 13-9-11.
//  Copyright (c) 2013年 YouMi Mobile Co. Ltd. All rights reserved.
//

#import "SourceADViewController.h"
#import "UIImageView+WebCache.h"

@interface SourceADViewController ()

@end

@implementation SourceADViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
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

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.navigationController.navigationBar setHidden:NO];
    [self.tableView reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source
#pragma mark -
#pragma mark TableView

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return @"源数据列表";
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (!self.apps) return 0;
    return [self.apps count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellID = @"c";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
    if (!cell) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellID] autorelease];
    }
    // 获得一个App的信息
    YouMiWallAppModel *model = self.apps[indexPath.row];
    [cell.imageView setImageWithURL:[NSURL URLWithString:model.smallIconURL] placeholderImage:[UIImage imageNamed:@"Icon.png"]];
    [cell.textLabel setText:[NSString stringWithFormat:@"%d分:%@", model.points, model.name]];
    [cell.detailTextLabel setText:model.adText];
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    // 安装一个APP
    YouMiWallAppModel *model = self.apps[indexPath.row];
    [YouMiWall userInstallApp:model];
}

@end
