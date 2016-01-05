

#import <Foundation/Foundation.h>

@interface QuoteItem : NSObject

    @property NSString *symbol;
    @property NSString *symbolName;
    @property NSNumber *lastTrade;
    @property NSString *lastTradeDate;
    @property NSString *lastTradeTime;
    @property NSNumber *changePercentChange;
    @property NSNumber *change;
    @property NSNumber *open;
    @property NSNumber *daysHigh;
    @property NSNumber *daysLow;
    @property NSNumber *volume;
    @property NSNumber *ask;
    @property NSNumber *averageDailyVolume;
    @property NSNumber *askSize;
    @property NSNumber *FiftyTwoWeekHigh;
    @property NSNumber *changeFrom52weekHigh;
    @property NSNumber *percentChangeFrom52weeklow;
    @property NSString *FiftyTwoWeekRange;
    @property NSNumber *bid;
    @property NSNumber *bidSize;
    @property NSNumber *FiftyDayMovingAverage;
    @property NSNumber *earningsShare;
@end
