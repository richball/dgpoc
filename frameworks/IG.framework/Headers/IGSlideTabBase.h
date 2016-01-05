
#import <Foundation/Foundation.h>
#import "IGSlideTabContentSize.h"

NS_ASSUME_NONNULL_BEGIN

/*!
 These specify whether or not and when a tab is draggable.
*/
typedef NS_ENUM(NSInteger, IGSlideTabDrag)
{
    /** The tab is not draggable. */
    IGSlideTabDragNever = 0,
    /** The tab is draggable only when the content has been exposed. */
    IGSlideTabDragOpened,
    /** The tab is draggable only when the content has not been exposed. */
    IGSlideTabDragClosed,
    /** The tab is draggable in all states. */
    IGSlideTabDragOpenedOrClosed
} ;

/*!
 These specify the location of the tab.
*/
typedef NS_ENUM(NSInteger, IGSlideTabLocation)
{
    /** The tab is placed on the top. */
    IGSlideTabLocationTop = 0,
    /** The tab is placed on the bottom. */
    IGSlideTabLocationBottom,
    /** The tab is placed on the left. */
    IGSlideTabLocationLeft,
    /** The tab is placed on the right. */
    IGSlideTabLocationRight
} ;

/*!
The _IGSlideTabItemBase_ is the base class for all tab items in the _IGSlideTabView_. It represents the tab view and content area view.

Upon accessing the view properties of the __tabView__ or __contentView__ property, should either of these be __nil__, they will automatically create a default instance. To use a custom view for the __tabView__ or __contentView__, simply assign a __UIView__ to the respective property.

Tab items can be hidden, pulsed, tapped, swiped, expanded and collapsed all through interaction or programmatically. Properties and events for all features are provided for complete flexibility.

**Note:** If you wish to derive your own tab item, derive from the _IGSlideTabItem_ class.
 */
@interface IGSlideTabBase : NSObject

/** Provides the actual calculated height and width of the tab item content view.
*/
@property (nonatomic, readonly) CGSize actualContentSize;

/** The _IGSlideTabContentSize_ class for manipulating the tab content view size.
*/
@property (nonatomic, retain, nullable) IGSlideTabContentSize *contentSize;

/** The view representing the content view of the tab item.

If accessed while property was previously __nil__ will create a default instance.

*/
@property (nonatomic, retain, nullable) UIView *contentView;

/** Allow or prevent dragging of the tab item's tab view using one of the supported enumerations.

Supported enumeration values:

- **IGSlideTabDragNever**
- **IGSlideTabDragOpened**
- **IGSlideTabDragClosed**
- **IGSlideTabDragOpenedOrClosed**

*/
@property (nonatomic, assign) IGSlideTabDrag isDraggable;

/** Set the tab item as expanded or collapsed, or provides information as to whether the tab item is currently expanded or collapsed.
*/
@property (nonatomic, assign) BOOL isExpanded;

/** Set the tab item as hidden or visible, or provides information as to whether the tab item is currently hidden or visible.
*/
@property (nonatomic, assign) BOOL isHidden;

/** Set the tab item to allow or prevent the tab expanding and collapsing by swiping the tab view.
*/
@property (nonatomic, assign) BOOL isSwipeable;

/** Set the tab item to allow or prevent the tab expanding and collapsing by tapping the tab view.
*/
@property (nonatomic, assign) BOOL isTappable;

/** The default tab view's fill color.

Changes the default tab's background fill color. If a custom view was assigned to __tabView__, then this property is ignored.

*/
@property (nonatomic, retain) UIColor *tabColor;

/** The tab's location in the _IGSlideTabView_.

Supported enumeration values:

- **IGSlideTabLocationTop**
- **IGSlideTabLocationBottom**
- **IGSlideTabLocationLeft**
- **IGSlideTabLocationRight**

*/
@property (nonatomic, assign) IGSlideTabLocation tabLocation;

/** The amount to offset the x and y values of the tab view's position.
*/
@property (nonatomic, assign) CGPoint tabOffset;

/** The tab view's position along the x or y axis.

The tab view's position starts at the left-most or top-most position based on the set __tabLocation__.

*/
@property (nonatomic, assign) CGFloat tabPosition;

/** The height and width of the tab view.
*/
@property (nonatomic, assign) CGSize tabSize;

/** The view representing the tab view of the tab item.

If accessed while property was previously __nil__ will create a default instance.

*/
@property (nonatomic, retain, nullable) UIView *tabView;

/** The total duration of animations when expanding or collapsing, measured in seconds.
*/
@property (nonatomic, assign) NSTimeInterval transitionDuration;

/** Returns the shape layer used as the default tab view's tab shape.

If a custom view was assigned to tabView, then this property is ignored.

*/
@property (nonatomic, readonly) CAShapeLayer *tabShapeLayer;

/** Returns the tab label used with the default tab view.

If a custom view was assigned to __tabView__, then this property is ignored.

*/
@property (nonatomic, readonly) UILabel *tabLabel;

/** The text that appears in the default tab view's tab.

If a custom view was assigned to __tabView__, then this property is ignored.

*/
@property (nonatomic, retain, nullable) NSString *title;

@end

NS_ASSUME_NONNULL_END