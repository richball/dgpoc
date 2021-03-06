#import "GridViewController.h"
#import "GridColumnsTableViewController.h"

#import "QuoteItem.h"
#import "QuoteItemDataMaker.h"
#import "TDAGridViewTheme.h"

#import "IGGridViewSortingDataSourceHelper.h"
#import "IGGridViewSymbolColumnDefinition.h"
#import "IGGridViewCurrencyColumnDefinition.h"
#import "IGGridViewColumnDefinition+Sort.h"

static const NSUInteger kDecimalCellWidth = 80;
static const NSUInteger kCurrencyCellWidth = 90;

@interface GridViewController ()

@property (nonatomic, strong) NSArray *data;
@property (nonatomic, strong) NSMutableArray *nonVisibleColumns;
@property (nonatomic, strong) TDAGridViewTheme *tdaTheme;
@property (nonatomic, strong) NSTimer *timer;

@end

@implementation GridViewController

#pragma mark - Controller Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self configureChartAndDataSource];
    
    IGGridViewSymbolColumnDefinition *symDef = [[IGGridViewSymbolColumnDefinition alloc] initWithKey:@"symbol"];
    symDef.sortFieldKey = @"symbolSort";
    symDef.sortFieldKeyAscending = @"symbolSortAscending";
    symDef.sortFieldKeyDescending = @"symbolSortDescending";
    symDef.headerText = @"Symbol";
    symDef.backgroundColor = [UIColor whiteColor];
    symDef.width = [[IGColumnWidth alloc] initWithWidth:100];
    [self.ds.fixedLeftColumns addObject:symDef];
    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.gridView updateData];
//    self.timer = [NSTimer timerWithTimeInterval:0.1 target:self selector:@selector(doTimerStuff2:) userInfo:nil repeats:YES];
//    [[NSRunLoop mainRunLoop] addTimer:self.timer forMode:NSRunLoopCommonModes];

}

- (void)viewWillDisappear:(BOOL)animated {
    [self.timer invalidate];
}

- (void)doTimerStuff:(NSTimer *)timer {
    for (QuoteItem *item in self.ds.data) {
        //if([item.symbol isEqualToString:@"SWHC"]) {
        //}
        item.lastTrade = [NSNumber numberWithDouble:item.lastTrade.doubleValue + 0.01];
        item.bid = [NSNumber numberWithDouble:item.bid.doubleValue + 0.01];
        item.ask = [NSNumber numberWithDouble:item.ask.doubleValue + 0.01];
    }
    [self.gridView updateData];
}

- (void)doTimerStuff2:(NSTimer *)timer {

    int index;
    for (int i=0; i<arc4random_uniform(50); i++) {
        index = arc4random_uniform( (unsigned int)[self.data count]);
        [self updateQuoteItem:self.ds.data[index]];
    }
   [self.gridView updateData];
}

- (void)updateQuoteItem:(QuoteItem*)item {
    item.lastTrade = [NSNumber numberWithDouble:item.lastTrade.doubleValue + 0.01];
    item.bid = [NSNumber numberWithDouble:item.bid.doubleValue + 0.01];
    item.ask = [NSNumber numberWithDouble:item.ask.doubleValue + 0.01];
}

- (void)gridEditColumnsControllerReturnedColumns:(NSArray *)editedColumns {
    if (!editedColumns.count) {
        return;
    }
    
    NSMutableArray *columnIndexesToDelete = [NSMutableArray array];
    
    for (NSInteger i=0; i<self.ds.columns.count; i++){
        [columnIndexesToDelete addObject:@(i)];
    }
    
    [self.ds deleteColumns:self.ds.columns];
    [self.gridView deleteColumnsAtIndexes: columnIndexesToDelete];
    
    [self.ds insertColumns:editedColumns atIndex:0];
    
    [self.ds.columnDefinitions removeAllObjects];
    [self.ds.columnDefinitions addObjectsFromArray:editedColumns];
}

#pragma mark - GridView Delegate

- (void)gridView:(IGGridView *)gridView columnMovedAtIndex:(NSInteger)sourceIndex toIndex:(NSInteger)destinationIndex {
    IGGridViewColumnDefinition *column = self.ds.columnDefinitions[sourceIndex];
    [self.ds.columnDefinitions removeObjectAtIndex:sourceIndex];
    [self.ds.columnDefinitions insertObject:column atIndex:destinationIndex];
    // TODO save columns
}

- (CGFloat)gridView:(IGGridView *)gridView heightForRowAtPath:(IGRowPath *)path {
    QuoteItem *item = [self.ds resolveDataObjectForRow:path];
    if ([item.assetType isEqualToString:@"O"]) {
        return 80;
    }
    return gridView.rowHeight;
}


#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"SegueEditColumns"]) {
        UINavigationController *navController = segue.destinationViewController;
        GridColumnsTableViewController *gridEditColumnsVC = (GridColumnsTableViewController *)navController.topViewController;
        [gridEditColumnsVC configureWithCurrentVisibleColumns:[self.ds.columns copy] nonVisibleColumns:self.nonVisibleColumns];
        [gridEditColumnsVC.tableView reloadData];
    }
}

- (IBAction)unwindEditColumnsViewControllerUsingUnwindSegue:(UIStoryboardSegue *)unwindSegue {
    GridColumnsTableViewController *gridEditColumnsVC = unwindSegue.sourceViewController;
    [self gridEditColumnsControllerReturnedColumns:gridEditColumnsVC.editedColumns];
}

#pragma mark - Private

- (void)configureChartAndDataSource {
    self.tdaTheme = [[TDAGridViewTheme alloc] init];
    
    self.gridView.rowSeparatorHeight = 1.f;
    self.gridView.headerBackgroundColor = [UIColor lightGrayColor];
    self.gridView.selectionType = IGGridViewSelectionTypeNone;
    self.gridView.rowHeight = 50;
    self.gridView.theme = self.tdaTheme;
    self.gridView.delegate = self;
    
    self.ds = [[IGGridViewSortingDataSourceHelper alloc] init];
    self.data = [QuoteItemDataMaker quoteItemsFromCannedData];
    self.nonVisibleColumns = [self createAllColumnDefinitions];

    NSArray *defaultColumnsHeaderKeys = @[@"lastTrade", @"bid", @"ask", @"open", @"daysHigh", @"daysLow"];
    NSArray *defaultColumns = [self columnsWithHeaderKeys:defaultColumnsHeaderKeys];
    [self.ds.columnDefinitions addObjectsFromArray:defaultColumns];

    self.ds.autoGenerateColumns = NO;
    self.ds.allowColumnReordering = NO;
    self.ds.data = self.data;
    
    self.gridView.dataSource = self.ds;
}

- (NSMutableArray *)createAllColumnDefinitions {
    NSMutableArray *columns = [NSMutableArray array];
    
    IGGridViewCurrencyColumnDefinition *curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"lastTrade"];
    curDef.headerText = @"Last";
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"ask"];
    curDef.headerText = @"Ask";
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"bid"];
    curDef.headerText = @"Bid";
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"open"];
    curDef.headerText = @"Open";
    
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"daysHigh"];
    curDef.headerText = @"High";
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    curDef = [[IGGridViewCurrencyColumnDefinition alloc] initWithKey:@"daysLow"];
    curDef.headerText = @"Low";
    curDef.width = [[IGColumnWidth alloc] initWithWidth:kCurrencyCellWidth];
    [columns addObject:curDef];
    
    IGGridViewColumnDefinition *colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"FiftyTwoWeekRange"];
    colDef.headerText = @"52-Week";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:150];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"askSize"];
    colDef.headerText = @"AskSize";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"bidSize"];
    colDef.headerText = @"BidSize";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"change"];
    colDef.headerText = @"Change";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"changePercentChange"];
    colDef.headerText = @"Chnge%";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"volume"];
    colDef.headerText = @"Volume";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"earningsShare"];
    colDef.headerText = @"Earnings";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbolName"];
    colDef.headerText = @"Name";
    colDef.width = [[IGColumnWidth alloc]initWithWidth:160];
    [columns addObject:colDef];

    return columns;
}

- (NSMutableArray *)columnsWithHeaderKeys:(NSArray *)columnHeaderKeys {
    NSMutableArray *columns = [NSMutableArray array];
    for (NSString *colHeaderKey in columnHeaderKeys) {
        for (IGGridViewColumnDefinition *columnDefinition in self.nonVisibleColumns) {
            if ([columnDefinition.fieldKey isEqualToString:colHeaderKey]) {
                [columns addObject:columnDefinition];
                [self.nonVisibleColumns removeObject:columnDefinition];
                break;
            }
        }
    }
    return columns;
}

@end
