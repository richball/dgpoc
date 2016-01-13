#import "IGGridViewSortingDataSourceHelper.h"
#import "IGGridViewSortingHeaderCell.h"
#import "IGGridViewColumnDefinition+Sort.h"

@implementation IGGridViewSortingDataSourceHelper


-(IGGridViewHeaderCell *)gridView:(IGGridView *)gridView fixedLeftHeaderCellAt:(NSInteger)column {
    IGGridViewSortingHeaderCell *sortingHeaderCell = [gridView dequeueReusableCellWithIdentifier:@"SymbolHeadeCell"];
    
    if (!sortingHeaderCell) {
        sortingHeaderCell = [[IGGridViewSortingHeaderCell alloc] initWithReuseIdentifier:@"SymbolHeadeCell"];
        sortingHeaderCell.delegate = self;
        sortingHeaderCell.fixed = YES;
        [sortingHeaderCell applyTheme:gridView.theme];
    }
    
    sortingHeaderCell.textLabel.text = [[self gridView:gridView titleForHeaderInFixedLeftColumn:column] uppercaseString];
    
    IGGridViewColumnDefinition *col = self.fixedLeftColumns[column];
    IGGridViewSortedColumn *sc = (self.sortedColumns.count == 0) ? nil : self.sortedColumns[0];
    
    if([sc.fieldName isEqualToString:col.sortFieldKey]) {
        [sortingHeaderCell setSortDirection:sc.sortDirection];
    } else {
        [sortingHeaderCell setSortDirection:IGGridViewSortedColumnDirectionNone];
    }
    
    return sortingHeaderCell;

}

- (IGGridViewHeaderCell *)gridView:(IGGridView *)gridView headerCellAt:(NSInteger)column {
    IGGridViewSortingHeaderCell *sortingHeaderCell = [gridView dequeueReusableCellWithIdentifier:@"SortHeadeCell"];
    
    if (!sortingHeaderCell) {
        sortingHeaderCell = [[IGGridViewSortingHeaderCell alloc] initWithReuseIdentifier:@"SortHeadeCell"];
        sortingHeaderCell.delegate = self;
        sortingHeaderCell.fixed = NO;
        [sortingHeaderCell applyTheme:gridView.theme];
    }

    sortingHeaderCell.textLabel.text = [[self gridView:gridView titleForHeaderInColumn:column] uppercaseString];

    IGGridViewColumnDefinition *col = self.columns[column];
    IGGridViewSortedColumn *sc = (self.sortedColumns.count == 0) ? nil : self.sortedColumns[0];

    if([sc.fieldName isEqualToString:col.sortFieldKey]) {
        [sortingHeaderCell setSortDirection:sc.sortDirection];
    } else {
        [sortingHeaderCell setSortDirection:IGGridViewSortedColumnDirectionNone];
    }

    return sortingHeaderCell;
}

#pragma mark - <IGGridViewSortingDelegate>

- (void)gridView:(IGGridView *)gridView toggleColumnSorting:(NSInteger)columnIndex fixedColumn:(BOOL)fixed {
    IGGridViewColumnDefinition* col = fixed ? self.fixedLeftColumns[columnIndex] : self.columns[columnIndex];
    IGGridViewSortedColumn* sc = nil;
    IGGridViewSortedColumnDirection direction = IGGridViewSortedColumnDirectionAscending;

    if(self.sortedColumns.count > 0) {
        sc = self.sortedColumns[0];
        [self.sortedColumns removeAllObjects];
        direction = [self getNextDirection:sc sortFieldPrefix:col.sortFieldKey];
    }
    
    sc = [self createSortedColumn:col direction:direction];
    
    [self.sortedColumns addObject:sc];
    [self invalidateData];
    
    [gridView updateData];
}

- (IGGridViewSortedColumnDirection)getNextDirection:(IGGridViewSortedColumn *) column
                                    sortFieldPrefix:(NSString *)sortFieldPrefix {
    IGGridViewSortedColumnDirection direction = column.sortDirection;
    if ([column.fieldName hasPrefix:sortFieldPrefix]) {
        if(direction == IGGridViewSortedColumnDirectionAscending) {
            direction = IGGridViewSortedColumnDirectionDescending;
        } else if(direction == IGGridViewSortedColumnDirectionDescending) {
            direction = IGGridViewSortedColumnDirectionNone;
        } else {
            direction = IGGridViewSortedColumnDirectionAscending;
        }
    }
    return direction;
}

- (IGGridViewSortedColumn *)createSortedColumn:(IGGridViewColumnDefinition *)column
                                     direction:(IGGridViewSortedColumnDirection)direction {
    NSString* field = column.sortFieldKey;
    if(direction == IGGridViewSortedColumnDirectionAscending && column.sortFieldKeyAscending) {
        field = column.sortFieldKeyAscending;
    } else if(direction == IGGridViewSortedColumnDirectionDescending && column.sortFieldKeyDescending) {
        field = column.sortFieldKeyDescending;
    }
    return [[IGGridViewSortedColumn alloc] initWithField:field forDirection:direction];
}

@end
