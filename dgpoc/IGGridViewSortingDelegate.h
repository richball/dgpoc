#ifndef IGGridViewSortingDelegate_h
#define IGGridViewSortingDelegate_h

@protocol IGGridViewSortingDelegate <NSObject>
- (void)gridView:(IGGridView *)gridView toggleColumnSorting:(NSInteger)columnIndex;
@end

#endif /* IGGridViewSortingDelegate_h */
