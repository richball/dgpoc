//
//  GridHelper.m
//  dgpoc
//
//  Created by Sanchez, Daniel on 1/6/16.
//  Copyright © 2016 TDA. All rights reserved.
//

#import "GridHelper.h"
#import <UIKit/UIKit.h>

@implementation GridHelper

+ (NSNumberFormatter *)decimalFormatter {
    static NSNumberFormatter *decimalFormatter = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        decimalFormatter = [[NSNumberFormatter alloc] init];
        decimalFormatter.numberStyle = NSNumberFormatterDecimalStyle;
    });
    return decimalFormatter;
}

+ (NSNumberFormatter *)currencyFormatter {
    static NSNumberFormatter *currencyFormatter = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        currencyFormatter = [[NSNumberFormatter alloc] init];
        currencyFormatter.numberStyle = NSNumberFormatterCurrencyStyle;
        currencyFormatter.locale = [NSLocale localeWithLocaleIdentifier:@"en_US"];
    });
    return currencyFormatter;
}

@end
