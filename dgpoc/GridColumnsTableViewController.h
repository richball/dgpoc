//
//  GridColumnsTableViewController.h
//  dgpoc
//
//  Created by Sanchez, Daniel on 1/6/16.
//  Copyright © 2016 TDA. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GridColumnsTableViewController : UITableViewController

- (void)configureWithCurrentColumns:(NSMutableArray *)currentColumns nonVisibleColumns:(NSMutableArray *)nonVisibleColumns;

@end
