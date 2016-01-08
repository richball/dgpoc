#import <IG/IG.h>
#import "IGGridViewSortingDelegate.h"

@interface IGGridViewSortingHeaderCell : IGGridViewHeaderCell

@property (nonatomic, weak) id <IGGridViewSortingDelegate> delegate;

- (void)setSortDirection:(IGGridViewSortedColumnDirection)direction;

@end
