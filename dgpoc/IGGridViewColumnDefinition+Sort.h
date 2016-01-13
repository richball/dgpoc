//
//  IGGridViewColumnDefinition+Sort.h
//  dgpoc
//
//  Created by Ball, Richard on 1/12/16.
//  Copyright © 2016 TDA. All rights reserved.
//

#import <IG/IG.h>

@interface IGGridViewColumnDefinition (Sort)

@property (nonatomic, strong) NSString *sortFieldKey;
@property (nonatomic, strong) NSString *sortFieldKeyAscending;
@property (nonatomic, strong) NSString *sortFieldKeyDescending;

@end
