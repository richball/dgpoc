//
//  GridHelper.m
//  dgpoc
//
//  Created by Sanchez, Daniel on 1/6/16.
//  Copyright © 2016 TDA. All rights reserved.
//

#import "GridHelper.h"
#import <UIKit/UIKit.h>

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

@implementation GridHelper

+ (NSNumberFormatter *)currencyFormatter {
    static NSNumberFormatter *currencyFormatter = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        currencyFormatter = [[NSNumberFormatter alloc] init];
        if (SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(@"9.0")) {
            currencyFormatter.numberStyle = NSNumberFormatterCurrencyAccountingStyle;
        } else {
            currencyFormatter.numberStyle = NSNumberFormatterCurrencyStyle;
        }
        currencyFormatter.locale = [NSLocale localeWithLocaleIdentifier:@"en_US"];
    });
    return currencyFormatter;
}

@end
