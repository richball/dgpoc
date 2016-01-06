
#import "FirstViewController.h"
#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"
#import "IGGridViewSymbolColumnDefinition.h"
#import "IGGridViewCurrencyColumnDefinition.h"

@interface FirstViewController ()
@property (nonatomic,strong) NSArray *data;
@end

@implementation FirstViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.ds = [[IGGridViewDataSourceHelper alloc]init];
    
//    IGGridViewColumnDefinition *colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbol"];
//    colDef.headerText = @"Symbol";
//    colDef.backgroundColor = [UIColor whiteColor];
//    colDef.width = [[IGColumnWidth alloc]initWithWidth:75];
//    [self.ds.fixedLeftColumns addObject:colDef];
//    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];
    
    IGGridViewSymbolColumnDefinition *symDef = [[IGGridViewSymbolColumnDefinition alloc] initWithKey:@"symbol"];
    symDef.headerText = @"Symbol";
    symDef.backgroundColor = [UIColor whiteColor];
    symDef.width = [[IGColumnWidth alloc]initWithWidth:75];
    [self.ds.fixedLeftColumns addObject:symDef];
    [self.gridView insertFixedLeftColumnsAtIndexes:@[@0]];

    
    
    
    IGGridViewColumnDefinition *colDef = colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"ask"];
    colDef.width = [[IGColumnWidth alloc]initWithWidth:60];
    colDef.headerText = @"Ask";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"bid"];
    colDef.headerText = @"Bid";
    colDef.width = [[IGColumnWidth alloc]initWithWidth:60];
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"open"];
    colDef.headerText = @"Open";
    colDef.width = [[IGColumnWidth alloc]initWithWidth:60];
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"daysHigh"];
    colDef.headerText = @"High";
    colDef.width = [[IGColumnWidth alloc]initWithWidth:60];
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"daysLow"];
    colDef.width = [[IGColumnWidth alloc]initWithWidth:60];
    colDef.headerText = @"Low";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"FiftyTwoWeekRange"];
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


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
