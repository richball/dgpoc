
#import "QuoteItem.h"

@implementation QuoteItem


- (NSString *)symbolSortAscending {
    if([_assetType isEqualToString:@"E"]) {
        return [NSString stringWithFormat:@"%@_0", _symbol];
    } else if([_assetType isEqualToString:@"O"]) {
        return [self createOptionSortKey];
    }
    return _symbol;
}

- (NSString *)symbolSortDescending {
    if([_assetType isEqualToString:@"E"]) {
        return [NSString stringWithFormat:@"%@_9", _symbol];
    } else if([_assetType isEqualToString:@"O"]) {
        return [self createOptionSortKey];
    }
    return _symbol;
}

- (NSString *)createOptionSortKey {
    NSRange offset = [_symbol rangeOfString:@"_"];
    offset.location++;
    offset.length = 2;
    NSString* month = [_symbol substringWithRange:offset];
    offset.location += offset.length;
    
    NSString* day = [_symbol substringWithRange:offset];
    offset.location += offset.length;
    
    NSString* year = [_symbol substringWithRange:offset];
    offset.location += offset.length;

    offset.length = 1;
    NSString* type = [_symbol substringWithRange:offset];
    offset.location += offset.length;

    offset.length = _symbol.length - offset.location;
    NSString* strike = [_symbol substringWithRange:offset];
    return [NSString stringWithFormat:@"%@_%@_%@_%@_%@_%@", _underlyingSymbol, year, month, day, strike, type];
}

// symbol
//    underlying (stock)
//    options for underlying (date, strike, call/put)
// account

// acct1 AAPL AAPL_option
// acct2 AAPL AAPL_option

// AAPL        (acct1)
// AAPL_012216C100 (acct1)
// AAPL_022216C100 (acct1)
// AAPL        (acct2)
// AAPL_option (acct2)

// -- ascending
// underlying_acct_0
// underlying_acct_year_month_day_strike_cp

// -- descending
// underlying_acct_999
// underlying_acct_year_month_day_strike_cp

@end
