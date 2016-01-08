#import "IGGridViewSortingDataSourceHelper.h"
#import "IGGridViewSortingHeaderCell.h"

@implementation IGGridViewSortingDataSourceHelper

//- (IGGridViewHeaderCell *)gridView:(IGGridView *)gridView fixedLeftHeaderCellAt:(NSInteger)column {
//    IGGridViewSortingHeaderCell *sortingFixedHeaderCell = [gridView dequeueReusableCellWithIdentifier:@"SortFixedHeadeCell"];
//    
//    if (!sortingFixedHeaderCell) {
//        sortingFixedHeaderCell = [[IGGridViewSortingHeaderCell alloc] initWithReuseIdentifier:@"SortFixedHeadeCell"];
//        sortingFixedHeaderCell.delegate = self;
//    }
//    
//    sortingFixedHeaderCell.textLabel.text = [self gridView:gridView titleForHeaderInFixedLeftColumn:column];
//    
//    IGGridViewColumnDefinition *col = self.fixedLeftColumns[column];
//    IGGridViewSortedColumn *sc = (self.sortedColumns.count == 0) ? nil : self.sortedColumns[0];
//    
//    if([sc.fieldName isEqualToString:col.fieldKey]) {
//        [sortingFixedHeaderCell setSortDirection:sc.sortDirection];
//    } else {
//        [sortingFixedHeaderCell setSortDirection:IGGridViewSortedColumnDirectionNone];
//    }
//    
//    return sortingFixedHeaderCell;
//}

- (IGGridViewHeaderCell *)gridView:(IGGridView *)gridView headerCellAt:(NSInteger)column {
    IGGridViewSortingHeaderCell *sortingHeaderCell = [gridView dequeueReusableCellWithIdentifier:@"SortHeadeCell"];
    
    if (!sortingHeaderCell) {
        sortingHeaderCell = [[IGGridViewSortingHeaderCell alloc] initWithReuseIdentifier:@"SortHeadeCell"];
        sortingHeaderCell.delegate = self;
    }

    sortingHeaderCell.textLabel.text = [self gridView:gridView titleForHeaderInColumn:column];

    IGGridViewColumnDefinition *col = self.columns[column];
    IGGridViewSortedColumn *sc = (self.sortedColumns.count == 0) ? nil : self.sortedColumns[0];

    if([sc.fieldName isEqualToString:col.fieldKey]) {
        [sortingHeaderCell setSortDirection:sc.sortDirection];
    } else {
        [sortingHeaderCell setSortDirection:IGGridViewSortedColumnDirectionNone];
    }

    return sortingHeaderCell;
}

#pragma mark - <IGGridViewSortingDelegate>

- (void)gridView:(IGGridView *)gridView toggleColumnSorting:(NSInteger)columnIndex {
    IGGridViewColumnDefinition* col = self.columns[columnIndex];
    
    IGGridViewSortedColumn* sc = nil;
    
    if(self.sortedColumns.count > 0) {
        
        sc = self.sortedColumns[0];
        [self.sortedColumns removeAllObjects];
        if ([sc.fieldName isEqualToString:col.fieldKey]) {
            if(sc.sortDirection == IGGridViewSortedColumnDirectionAscending) {
                sc.sortDirection = IGGridViewSortedColumnDirectionDescending;
            } else {
                sc.sortDirection = IGGridViewSortedColumnDirectionAscending;
            }
        } else {
            sc = [[IGGridViewSortedColumn alloc] initWithField:col.fieldKey forDirection:IGGridViewSortedColumnDirectionAscending];
        }
    } else {
        sc = [[IGGridViewSortedColumn alloc] initWithField:col.fieldKey forDirection:IGGridViewSortedColumnDirectionAscending];
    }
    
    [self.sortedColumns addObject:sc];
    [self invalidateData];
    
    [gridView updateData];
}

@end
