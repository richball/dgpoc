#import "GridViewController.h"
#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"
#import "IGGridViewSymbolColumnDefinition.h"
#import "IGGridViewCurrencyColumnDefinition.h"

static const NSUInteger kCurrencyCellWidth = 90;

@interface GridViewController ()
@property (nonatomic,strong) NSArray *data;
@end

@implementation GridViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.ds = [[IGGridViewDataSourceHelper alloc] init];
    
//    IGGridViewColumnDefinition *colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbol"];
//    colDef.headerText = @"Symbol";
//    colDef.backgroundColor = [UIColor whiteColor];
//    colDef.width = [[IGColumnWidth alloc]initWithWidth:75];
//    [self.ds.fixedLeftColumns addObject:colDef];
//    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];
    
    IGGridViewSymbolColumnDefinition *symDef = [[IGGridViewSymbolColumnDefinition alloc] initWithKey:@"symbol"];
    symDef.headerText = @"Symbol";
    symDef.backgroundColor = [UIColor whiteColor];
    symDef.width = [[IGColumnWidth alloc]initWithWidth:100];
    [self.ds.fixedLeftColumns addObject:symDef];
    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];

    IGGridViewCurrencyColumnDefinition *curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"lastTrade"];
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    curDef.headerText = @"Last";
    [self.ds.columnDefinitions addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"ask"];
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    curDef.headerText = @"Ask";
    [self.ds.columnDefinitions addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"bid"];
    curDef.headerText = @"Bid";
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    [self.ds.columnDefinitions addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"open"];
    curDef.headerText = @"Open";
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    [self.ds.columnDefinitions addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"daysHigh"];
    curDef.headerText = @"High";
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    [self.ds.columnDefinitions addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"daysLow"];
    curDef.width = [[IGColumnWidth alloc]initWithWidth:kCurrencyCellWidth];
    curDef.headerText = @"Low";
    [self.ds.columnDefinitions addObject:curDef];
    
    IGGridViewColumnDefinition *colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"FiftyTwoWeekRange"];
    colDef.width = [[IGColumnWidth alloc]initWithWidth:150];
    colDef.headerText = @"52-Week";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbolName"];
    colDef.headerText = @"Name";
    colDef.width = [[IGColumnWidth alloc]initWithWidth:160];
    [self.ds.columnDefinitions addObject:colDef];
    
    self.data = [QuoteItemDataMaker quoteItemsFromCannedData];

    self.gridView.delegate = self;
    self.gridView.selectionType = IGGridViewSelectionTypeNone;
    self.gridView.rowHeight = 60;
    
    self.ds.autoGenerateColumns = NO;
    self.ds.data = self.data;
    self.gridView.dataSource = self.ds;
    self.ds.allowColumnReordering = YES;
    
    
    [self.gridView updateData];
}

@end
