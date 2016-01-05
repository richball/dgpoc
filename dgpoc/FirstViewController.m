
#import "FirstViewController.h"
#import "QuoteItemDataMaker.h"
#import "QuoteItem.h"

@interface FirstViewController ()
@property (nonatomic,strong) NSArray *data;
@end

@implementation FirstViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.ds = [[IGGridViewDataSourceHelper alloc]init];
    
    IGGridViewColumnDefinition *colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbol"];
    colDef.headerText = @"Symbol";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"symbolName"];
    colDef.headerText = @"Symbol Name";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"ask"];
    colDef.headerText = @"Ask";
    [self.ds.columnDefinitions addObject:colDef];
    
    colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"bid"];
    colDef.headerText = @"Bid";
    [self.ds.columnDefinitions addObject:colDef];
    
    
    self.data = [QuoteItemDataMaker quoteItemsFromCannedData];

    self.gridView.delegate = self;
    self.gridView.selectionType = IGGridViewSelectionTypeNone;
    
    self.ds.autoGenerateColumns = NO;
    self.ds.data = self.data;
    self.gridView.dataSource = self.ds;
    self.ds.allowColumnReordering = YES;
    
    
    [_gridView updateData];
    

}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
