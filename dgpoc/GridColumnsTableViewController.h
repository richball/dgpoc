#import <UIKit/UIKit.h>

@interface GridColumnsTableViewController : UITableViewController

@property (nonatomic, strong) NSArray *editedColumns;

- (void)configureWithCurrentVisibleColumns:(NSArray *)currentVisibleColumns nonVisibleColumns:(NSMutableArray *)nonVisibleColumns;

@end
