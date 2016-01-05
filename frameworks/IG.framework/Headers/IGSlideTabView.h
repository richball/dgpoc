
#import <Foundation/Foundation.h>
#import "IGSlideTabBase.h"

NS_ASSUME_NONNULL_BEGIN

@class IGSlideTabView;
@class IGSlideTabItem;

/*! The delegate of a _IGSlideTabView_ object must adopt the _IGSlideTabDelegate_ protocol. The optional methods of the protocol allow the delegate receiver to manage the interaction and layout events of the _IGSlideTabView_ and all added tabs.
 */
@protocol IGSlideTabDelegate <NSObject>

@optional
/** Informs the delegate receiver that the tab item's content size has changed.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item whose content size changed.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabContentSizeDidChange:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the bounds of the _IGSlideTabView_ has changed. This delegate method will be called for each tab item contained in the _IGSlideTabView_.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item contained in the _IGSlideTabView_ whose bounds have changed.
@param bounds The new bounds.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tab:(IGSlideTabItem *)tab layoutForBounds:(CGRect)bounds;

/** Informs the delegate receiver that the default tab label of the _IGSlideTabItem_ needs layout.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item contained in the _IGSlideTabView_ whose label needs layout.
@param label The label needing layout.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tab:(IGSlideTabItem *)tab layoutTabLabel:(UILabel *)label;

/** Informs the delegate receiver that the tab item is being dragged.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item being dragged.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidDrag:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent the tab drag.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting the drag.
@return A BOOL value to allow or prevent the dragging.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillDrag:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has collapsed.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has collapsed.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidCollapse:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent the tab collapsing.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to collapse.
@return A BOOL value to allow or prevent the collapse.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillCollapse:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has expanded.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has expanded.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidExpand:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent the tab expanding.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to expanding.
@return A BOOL value to allow or prevent the expanding.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillExpand:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has been hidden.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has hid.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidHide:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent the tab hiding.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to hide.
@return A BOOL value to allow or prevent the hiding.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillHide:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has changed its location.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has changed its location.
@param location The previous tab item location.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabLocationDidChange:(IGSlideTabItem *)tab fromLocation:(IGSlideTabLocation)location;

/** Requests information from the delegate receiver to allow or prevent the tab from changing its location.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to hide.
@param location The tab item's target location.
@return A BOOL value to allow or prevent the location change.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabLocationWillChange:(IGSlideTabItem *)tab toLocation:(IGSlideTabLocation)location;

/** Requests information from the delegate receiver to allow or prevent the tab pulsing.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to pulse.
@return A BOOL value to allow or prevent the pulse.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillPulse:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has been shown. This method is called when the __isHidden__ property of the _IGSlideTabItem_ has been set to __NO__.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has been shown.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidShow:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent from showing. This method is called when the __isHidden__ property of the _IGSlideTabItem_ has been set to __NO__.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to be shown.
@return A BOOL value to allow or prevent the tab from showing.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillShow:(IGSlideTabItem *)tab;

/** Informs the delegate receiver that the tab item has been swiped.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has been swiped.
@param direction The direction of the swipe.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidSwipe:(IGSlideTabItem *)tab withDirection:(UISwipeGestureRecognizerDirection)direction;

/** Requests information from the delegate receiver to allow or prevent a swipe.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting to swipe.
@param direction The direction of the swipe.
@return A BOOL value to allow or prevent the swipe.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillSwipe:(IGSlideTabItem *)tab withDirection:(UISwipeGestureRecognizerDirection)direction;

/** Informs the delegate receiver that the tab item has been tapped.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item that has been tapped.

*/
- (void)slideTabView:(IGSlideTabView *)slideTabView tabDidTap:(IGSlideTabItem *)tab;

/** Requests information from the delegate receiver to allow or prevent the tapping.

@param slideTabView The _IGSlideTabView_ containing the tab item.
@param tab The tab item requesting the tap.
@return A BOOL value to allow or prevent the tapping.

*/
- (BOOL)slideTabView:(IGSlideTabView *)slideTabView tabWillTap:(IGSlideTabItem *)tab;

@end

/*!
The _IGSlideTabView_ allows you to easily create a tab item on any side of the contained view that slides out content when tapped or swiped. Customization options include a property named __useTabPadding__ that allows you to provide padding around the __contentAreaView__ so that your views are not overlapped by tabs, pulsing a tab item to draw attention and full flexibility to create your own tab view and tab content view.
 */
@interface IGSlideTabView : UIView

///---------------------------------------------------------------------------------------
/// @name Initialization and Configuration
///---------------------------------------------------------------------------------------

/** The content area of the _IGSlideTabView_.

Adding views to this content area ensures correct positioning when __useTabPadding__ is enabled.

*/
@property (nonatomic, readonly) UIView *contentAreaView;

/** The object that acts as the delegate of the _IGSlideTabView_.

The class must adopt the _IGSlideTabDelegate_ protocol.

*/
@property (nonatomic, assign, nullable) id<IGSlideTabDelegate> delegate;

/** Provides padding on each side of the content area to not overlap views with the tab items.
*/
@property (nonatomic, assign) BOOL useTabPadding;

///---------------------------------------------------------------------------------------
/// @name Tabs
///---------------------------------------------------------------------------------------

/** Adds a single tab item to the _IGSlideTabView_.

@param tab The tab item to add to the _IGSlideTabView_.
*/
- (void)addTab:(IGSlideTabItem *)tab;

/** Adds an array of tab items to the _IGSlideTabView_.

@param tabs The _NSArray_ of tab items to add to the _IGSlideTabView_.
*/
- (void)addTabs:(NSArray<__kindof IGSlideTabItem *> *)tabs;

/** Hide all visible tab items.
*/
- (void)hideAllTabs;

/** Pulses a tab to draw attention.

A tab pulse will occur on the default __tabView__ of your _IGSlideTabItem_, should you assign your own _tabView_ use the _slideTabView:tabPulsing:_ _IGSlideTabDelegate_ method to create a custom pulse effect.

@param tab The tab item to pulse.
*/
- (void)pulseTab:(IGSlideTabItem *)tab;

/** Remove a tab item from the _IGSlideTabView_.

@param tab The tab item to remove.
*/
- (void)removeTab:(IGSlideTabItem *)tab;

/** Remove tab items from the _IGSlideTabView_.

@param tabs An _NSArray_ of tab items to remove.
*/
- (void)removeTabs:(NSArray<__kindof IGSlideTabItem *> *)tabs;

/** Show all visible tab items.
*/
- (void)showAllTabs;

/** Checks for and returns a tab item at a specific point. Returns nil if no tab item was found at that point.

@param point The _CGPoint_ to check for a tab item.
@return The _IGSlideTabItem_ or __nil__ if no tab item was found at that point.
*/
- (IGSlideTabItem *)tabAtPoint:(CGPoint)point;

/** An _NSArray_ containing all tab items.
*/
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray *tabs;

@end

NS_ASSUME_NONNULL_END