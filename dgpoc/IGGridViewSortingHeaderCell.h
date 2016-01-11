#import <IG/IG.h>
#import "IGGridViewSortingDelegate.h"
#import "TDAGridViewTheme.h"

@interface IGGridViewSortingHeaderCell : IGGridViewHeaderCell

@property (nonatomic, weak) id <IGGridViewSortingDelegate> delegate;

- (void)setSortDirection:(IGGridViewSortedColumnDirection)direction;
- (void)applyTheme:(TDAGridViewTheme *)theme;

    
@end
