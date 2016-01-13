

#import <Foundation/Foundation.h>

@interface QuoteItem : NSObject

@property (nonatomic, strong)  NSString *assetType;
@property (nonatomic, strong)  NSString *symbol;
@property (nonatomic, strong)  NSString *symbolName;
@property (nonatomic, strong)  NSString *underlyingSymbol;
@property (nonatomic, strong)  NSNumber *lastTrade;
@property (nonatomic, strong)  NSString *lastTradeDate;
@property (nonatomic, strong)  NSString *lastTradeTime;
@property (nonatomic, strong)  NSNumber *changePercentChange;
@property (nonatomic, strong)  NSNumber *change;
@property (nonatomic, strong)  NSNumber *open;
@property (nonatomic, strong)  NSNumber *daysHigh;
@property (nonatomic, strong)  NSNumber *daysLow;
@property (nonatomic, strong)  NSNumber *volume;
@property (nonatomic, strong)  NSNumber *ask;
@property (nonatomic, strong)  NSNumber *averageDailyVolume;
@property (nonatomic, strong)  NSNumber *askSize;
@property (nonatomic, strong)  NSNumber *FiftyTwoWeekHigh;
@property (nonatomic, strong)  NSNumber *changeFrom52weekHigh;
@property (nonatomic, strong)  NSNumber *percentChangeFrom52weeklow;
@property (nonatomic, strong)  NSString *FiftyTwoWeekRange;
@property (nonatomic, strong)  NSNumber *bid;
@property (nonatomic, strong)  NSNumber *bidSize;
@property (nonatomic, strong)  NSNumber *FiftyDayMovingAverage;
@property (nonatomic, strong)  NSNumber *earningsShare;
@property (nonatomic, strong)  NSString *symbolSortAscending;
@property (nonatomic, strong)  NSString *symbolSortDescending;

@end
