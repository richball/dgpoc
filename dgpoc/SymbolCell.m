
#import "SymbolCell.h"

@implementation SymbolCell

- (instancetype)initWithReuseIdentifier:(NSString *)identifier {
    self = [super initWithReuseIdentifier:identifier];
    if (self) {
        NSArray *nibArray = [[NSBundle mainBundle] loadNibNamed:@"SymbolCell" owner:nil options:nil];
        [self.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
        
        UIView *contents = [nibArray lastObject];
        contents.frame = self.bounds;
        [self addSubview:contents];
        
        self.labelSymbol = [self viewWithTag:101];
        self.labelSymbolDescription = [self viewWithTag:102];
        
    }
    return self;
}

@end
