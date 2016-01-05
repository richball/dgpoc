
#import <Foundation/Foundation.h>
#import "IGSlideTabBase.h"

/*!
The _IGSlideTabItem_ is the base class for all tab items in the _IGSlideTabView_. It represents the tab view and content area view.

Upon accessing the view properties of the __tabView__ or __contentView__ property, should either of these be __nil__, they will automatically create a default instance. To use a custom view for the __tabView__ or __contentView__, simply assign a _UIView_ to the respective property.

Tab items can be hidden, pulsed, tapped, swiped, expanded and collapsed all through interaction or programmatically. Properties and events for all features are provided for complete flexibility.
 */
@interface IGSlideTabItem : IGSlideTabBase <UIGestureRecognizerDelegate>

/** Initializes an _IGSlideTabItem_.

@param location The _IGSlideTabLocation_ to place the tab item.
@param title The title text to place in the tab view.
@param tabView The _UIView_ to use as the __tabView__. May be __nil__ to use the default tab appearance.
@param contentView The _UIView_ to use as the __contentView__. May be __nil__ to use the default content appearance.
@return The initialized _IGSlideTabItem_.
*/
+ (IGSlideTabItem *)tabWithLocation:(IGSlideTabLocation)location title:(NSString *)title tabView:(UIView *)tabView contentView:(UIView *)contentView;

@end