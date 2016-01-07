#import "GridColumnsTableViewController.h"
#import "GridViewController.h"

#import <IG/IG.h>

@interface GridColumnsTableViewController ()

@property (nonatomic, strong) NSMutableArray *currentColumns;
@property (nonatomic, strong) NSMutableArray *nonVisibleColumns;

@end

@implementation GridColumnsTableViewController

#pragma mark - Controller Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    UIBarButtonItem *doneButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStylePlain target:self action:@selector(btnDoneTapped:)];
//    doneButtonItem.tintColor = [UIColor whiteColor];
//    self.navigationItem.rightBarButtonItem = doneButtonItem;
}

- (void)configureWithCurrentVisibleColumns:(NSArray *)currentVisibleColumns nonVisibleColumns:(NSMutableArray *)nonVisibleColumns {
    self.currentColumns = [currentVisibleColumns mutableCopy];
    self.nonVisibleColumns = nonVisibleColumns;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    self.editedColumns = [self.currentColumns copy];
}

#pragma mark - Target/Action

- (void)btnDoneTapped:(UIBarButtonItem *)sender {
    
   // [self performSegueWithIdentifier:@"unwindSegueGridViewController" sender:self];
    //[self dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark - <UITableViewDataSource>

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return !self.nonVisibleColumns.count ? 1 : 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return self.currentColumns.count;
    }
    return self.nonVisibleColumns.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = nil;
    IGGridViewColumnDefinition *columnDefinition = nil;
    
    switch (indexPath.section) {
        case 0:
            cell = [tableView dequeueReusableCellWithIdentifier:@"RemoveColumnCell" forIndexPath:indexPath];
            columnDefinition = self.currentColumns[indexPath.row];
            break;
        case 1:
            cell = [tableView dequeueReusableCellWithIdentifier:@"AddColumnCell" forIndexPath:indexPath];
            columnDefinition = self.nonVisibleColumns[indexPath.row];
            break;
        default:
            break;
    }
    
    UILabel *columnNameLabel = [cell viewWithTag:101];
    columnNameLabel.text = columnDefinition.headerText;
    
    return cell;
}

#pragma mark - <UITableViewDelegate>

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    IGGridViewColumnDefinition *columnDefinition = nil;
    
    if (indexPath.section == 0) {
        columnDefinition = self.currentColumns[indexPath.row];
        [self.currentColumns removeObject:columnDefinition];
        [self.nonVisibleColumns addObject:columnDefinition];
    } else {
        columnDefinition = self.nonVisibleColumns[indexPath.row];
        [self.nonVisibleColumns removeObject:columnDefinition];
        [self.currentColumns addObject:columnDefinition];
    }
    
    [self.tableView reloadData];
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    return section == 0 ? @"Visible Columns" : @"Non-visible Columns";
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}


@end
