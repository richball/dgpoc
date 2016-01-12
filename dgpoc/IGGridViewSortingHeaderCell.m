#import "IGGridViewSortingHeaderCell.h"

@interface IGGridViewSortingHeaderCell ()

@property (nonatomic, strong) UIView *sortIndicator;

@end

@implementation IGGridViewSortingHeaderCell

- (instancetype)initWithReuseIdentifier:(NSString *)identifier {
    
    self = [super initWithReuseIdentifier:identifier];
    
    if (self) {
        UITapGestureRecognizer* tap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(sortHeaderTapped:)];
        
        [self registerGestures:@[tap]];
        self.sortIndicator = [[UIView alloc] init];
        [self addSubview:self.sortIndicator];
    }
    return self;
    
}

- (void)applyTheme:(TDAGridViewTheme *)theme {
    
    
    self.backgroundColor = [theme headerCellBackgroundColor];
    self.textLabel.textColor = [theme headerCellTextColor];
}

- (void)setSortDirection:(IGGridViewSortedColumnDirection)direction {
    if(direction == IGGridViewSortedColumnDirectionAscending) {
        self.sortIndicator.backgroundColor = [UIColor greenColor];
    } else if(direction == IGGridViewSortedColumnDirectionDescending) {
        self.sortIndicator.backgroundColor = [UIColor redColor];
    } else {
        self.sortIndicator.backgroundColor = [UIColor clearColor];
    }
}

- (void)sortHeaderTapped:(UITapGestureRecognizer *)sender {
    [self.delegate gridView:self.gridView toggleColumnSorting:self.path.columnIndex fixedColumn:self.fixed];
}

@end
