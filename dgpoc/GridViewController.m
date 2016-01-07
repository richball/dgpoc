#import "GridViewController.h"
#import "GridColumnsTableViewController.h"

#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"
#import "IGGridViewSymbolColumnDefinition.h"
#import "IGGridViewCurrencyColumnDefinition.h"

static const NSUInteger kDecimalCellWidth = 70;
static const NSUInteger kCurrencyCellWidth = 90;

@interface GridViewController ()

@property (nonatomic, strong) NSArray *data;
@property (nonatomic, strong) NSMutableArray *nonVisibleColumns;

@end

@implementation GridViewController

#pragma mark - Controller Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];

    self.ds = [[IGGridViewDataSourceHelper alloc] init];
    
    IGGridViewSymbolColumnDefinition *symDef = [[IGGridViewSymbolColumnDefinition alloc] initWithKey:@"symbol"];
    symDef.headerText = @"Symbol";
    symDef.backgroundColor = [UIColor whiteColor];
    symDef.width = [[IGColumnWidth alloc]initWithWidth:100];
    [self.ds.fixedLeftColumns addObject:symDef];
    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];
    
    self.nonVisibleColumns = [self createAllColumnDefinitions];
    NSArray *defaultColumnsHeaderKeys = @[@"lastTrade", @"bid", @"ask", @"open", @"daysHigh", @"daysLow"];
    [self.ds.columnDefinitions addObjectsFromArray:[self columnsWithHeaderKeys:defaultColumnsHeaderKeys]];
    self.data = [QuoteItemDataMaker quoteItemsFromCannedData];

    self.gridView.delegate = self;
    self.gridView.selectionType = IGGridViewSelectionTypeNone;
    self.gridView.rowHeight = 60;
    
    self.ds.autoGenerateColumns = NO;
    self.ds.data = self.data;
    self.gridView.dataSource = self.ds;
    self.ds.allowColumnReordering = YES;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.gridView reloadData];
//    [self.gridView updateData];
}

- (void)gridEditColumnsControllerReturnedColumns:(NSArray *)editedColumns {
    
    NSMutableArray *columnsToDelete = [NSMutableArray array];
    NSMutableArray *columnIndexesToDelete = [NSMutableArray array];
    
    // Delete Columns
    [self.ds.columnDefinitions enumerateObjectsUsingBlock:^(IGGridViewColumnDefinition * _Nonnull visibleColumnDefinition, NSUInteger idx, BOOL * _Nonnull stop) {
        if (![editedColumns containsObject:visibleColumnDefinition]) {
            [columnsToDelete addObject:visibleColumnDefinition];
            [columnIndexesToDelete addObject:@(idx)];
        }
    }];

    [self.ds deleteColumns:[columnsToDelete copy]];
    [self.gridView deleteColumnsAtIndexes:[columnIndexesToDelete copy]];
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    if ([segue.identifier isEqualToString:@"SegueEditColumns"]) {
        UINavigationController *navController = segue.destinationViewController;
        GridColumnsTableViewController *gridEditColumnsVC = (GridColumnsTableViewController *)navController.topViewController;
        [gridEditColumnsVC configureWithCurrentVisibleColumns:[self.ds.columnDefinitions copy] nonVisibleColumns:self.nonVisibleColumns];
        [gridEditColumnsVC.tableView reloadData];
    }
}

- (IBAction)unwindEditColumnsViewControllerUsingUnwindSegue:(UIStoryboardSegue *)unwindSegue {
    
}

- (IBAction)backToTheStart:(UIStoryboardSegue *)segue {
       
    // access public properties from ViewController2 here
}

#pragma mark - Private

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
    colDef.headerText = @"Ask Size";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"bidSize"];
    colDef.headerText = @"Bid Size";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"change"];
    colDef.headerText = @"Change";
    colDef.width = [[IGColumnWidth alloc] initWithWidth:kDecimalCellWidth];
    [columns addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"changePercentChange"];
    colDef.headerText = @"Change%";
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
