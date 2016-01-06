#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"

@implementation QuoteItemDataMaker

+ (NSArray *)quoteItemsFromCannedData {
    NSMutableArray *dataList = [[NSMutableArray alloc] init];
    QuoteItem *q;
    
    NSURL *url = [[NSBundle mainBundle] URLForResource:@"quotes" withExtension:@"csv"];

    NSData *data = [NSData dataWithContentsOfURL:url];
    NSString *fileContents = [NSString stringWithUTF8String:[data bytes]];
    
    NSArray* rows = [fileContents componentsSeparatedByString:@"\n"];
    for (NSString* row in rows) {
        q = [[QuoteItem alloc] init];

        NSArray *c = [row componentsSeparatedByString:@","];
        q.symbol = c[0];
        q.symbolName = c[1];
        q.lastTrade = [NSNumber numberWithDouble:[c[2] doubleValue]];
        q.lastTradeDate = c[3];
        q.lastTradeTime = c[4];
        q.changePercentChange = [NSNumber numberWithDouble:[c[5]  doubleValue]];
        q.change = [NSNumber numberWithDouble:[c[6] doubleValue]];
        q.open = [NSNumber numberWithDouble:[c[7] doubleValue]];
        q.daysHigh = [NSNumber numberWithDouble:[c[8] doubleValue]];
        q.daysLow = [NSNumber numberWithDouble:[c[9] doubleValue]];
        q.volume = [NSNumber numberWithDouble:[c[10] doubleValue]];
        q.ask = [NSNumber numberWithDouble:[c[11] doubleValue]];
        q.averageDailyVolume = [NSNumber numberWithDouble:[c[12] doubleValue]];
        q.askSize = [NSNumber numberWithDouble:[c[13] doubleValue]];
        q.FiftyTwoWeekHigh = [NSNumber numberWithDouble:[c[14] doubleValue]];
        q.changeFrom52weekHigh = [NSNumber numberWithDouble:[c[15] doubleValue]];
        q.percentChangeFrom52weeklow = [NSNumber numberWithDouble:[c[16] doubleValue]];
        q.FiftyTwoWeekRange = c[17];
        q.bid = [NSNumber numberWithDouble:[c[18] doubleValue]];
        q.bidSize = [NSNumber numberWithDouble:[c[19] doubleValue]];
        q.FiftyDayMovingAverage = [NSNumber numberWithDouble:[c[20] doubleValue]];
        q.earningsShare = [NSNumber numberWithDouble:[c[21] doubleValue]];
        
        [dataList addObject:q];
    }
    return dataList;
}

@end
