#import "TDAGridViewTheme.h"

@implementation TDAGridViewTheme

- (UIColor *) headerCellBackgroundColor {
    return [UIColor lightGrayColor];
}

- (UIColor *) cellBackgroundColor {
    return [UIColor whiteColor];
}

- (UIColor *) headerCellTextColor {
    return [UIColor darkGrayColor];
}

//@property(nonatomic, readonly)UIFont* headerCellTextFont;
//
///** The UITextAlignment used for all header cells in the grid view.
// 
// This property will override the grid level version of this property. If you provide a custom header cell, this property will take no effect, unless implemented manually.
// */

- (NSTextAlignment)headerCellTextAlignment {
    return NSTextAlignmentLeft;
}

- (CGFloat)headerHeight {
    return 30;
}

@end
