#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"

@implementation QuoteItemDataMaker

+ (NSArray *)quoteItemsFromCannedData {
    NSMutableArray *dataList = [[NSMutableArray alloc] init];
    QuoteItem *q;
    
    NSURL *url = [[NSBundle mainBundle] URLForResource:@"quotes" withExtension:@"csv"];

    NSData *data = [NSData dataWithContentsOfURL:url];
    NSString *fileContents = [NSString stringWithUTF8String:[data bytes]];
    
    NSMutableArray *rows = [[fileContents componentsSeparatedByString:@"\n"] mutableCopy];
    [rows removeObjectAtIndex:0];
    
    for (NSString *row in rows) {
        q = [[QuoteItem alloc] init];
        int i = 0;

        NSArray *c = [row componentsSeparatedByString:@","];
        q.assetType = c[i++];
        q.symbol = c[i++];
        q.symbolName = c[i++];
        q.underlyingSymbol = c[i++];
        q.lastTrade = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.lastTradeDate = c[i++];
        q.lastTradeTime = c[i++];
        q.changePercentChange = [NSNumber numberWithDouble:[c[i++]  doubleValue]];
        q.change = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.open = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.daysHigh = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.daysLow = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.volume = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.ask = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.averageDailyVolume = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.askSize = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.FiftyTwoWeekHigh = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.changeFrom52weekHigh = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.percentChangeFrom52weeklow = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.FiftyTwoWeekRange = c[i++];
        q.bid = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.bidSize = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.FiftyDayMovingAverage = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        q.earningsShare = [NSNumber numberWithDouble:[c[i++] doubleValue]];
        
        [dataList addObject:q];
    }
    return dataList;
}

@end
