#ifndef IGGridViewSortingDelegate_h
#define IGGridViewSortingDelegate_h

@protocol IGGridViewSortingDelegate <NSObject>
- (void)gridView:(IGGridView *)gridView toggleColumnSorting:(NSInteger)columnIndex fixedColumn:(BOOL)fixed;
@end

#endif /* IGGridViewSortingDelegate_h */
