#import <IG/IG.h>
#import "IGGridViewSortingDelegate.h"
#import "TDAGridViewTheme.h"

@interface IGGridViewSortingHeaderCell : IGGridViewHeaderCell

@property (nonatomic, weak) id <IGGridViewSortingDelegate> delegate;
@property (nonatomic, assign) BOOL fixed;

- (void)setSortDirection:(IGGridViewSortedColumnDirection)direction;
- (void)applyTheme:(TDAGridViewTheme *)theme;

    
@end
