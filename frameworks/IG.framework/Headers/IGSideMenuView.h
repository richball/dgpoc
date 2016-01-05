#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 These specify the side menu's location.
*/
typedef NS_ENUM(NSInteger, IGSideMenuLocation)
{
    /** The side menu is on the left of the view. */
    IGSideMenuLocationLeft = 0,
    /** The side menu is on the right of the view. */
    IGSideMenuLocationRight
} ;

@class IGSideMenuView;

/*!
The IGSideMenuViewDelegate protocol allows the adopter to receive calls for the open and close events as well as the location of the contentView when a user drags to reveal a side menu.
*/
@protocol IGSideMenuViewDelegate <NSObject>
@optional
/** Provides the current location of the contentView.

As a user longPresses and drags to reveal a side menu this delegate method is called to update the receiver of the contentView location.

@param sideMenuView Reference to the IGSideMenuView.
@param location The X, Y location of the IGSideMenuView's contentView.
*/
- (void)sideMenuView:(IGSideMenuView *)sideMenuView contentViewLocationDidChange:(CGPoint)location;

/** Informs the receiver that a side menu has closed.

@param sideMenuView Reference to the IGSideMenuView.
@param side The side of the IGSideMenuView that closed. (IGSideMenuLocationLeft or IGSideMenuLocationRight)
*/
- (void)sideMenuView:(IGSideMenuView *)sideMenuView sideDidClose:(IGSideMenuLocation)side;

/** Informs the receiver that a side menu will close.

@param sideMenuView Reference to the IGSideMenuView.
@param side The side of the IGSideMenuView that will close. (IGSideMenuLocationLeft or IGSideMenuLocationRight)
*/
- (void)sideMenuView:(IGSideMenuView *)sideMenuView sideWillClose:(IGSideMenuLocation)side;

/** Informs the receiver that a side menu has opened.

@param sideMenuView Reference to the IGSideMenuView.
@param side The side of the IGSideMenuView that has opened. (IGSideMenuLocationLeft or IGSideMenuLocationRight)
*/
- (void)sideMenuView:(IGSideMenuView *)sideMenuView sideDidOpen:(IGSideMenuLocation)side;

/** Informs the receiver that a side menu will open.

@param sideMenuView Reference to the IGSideMenuView.
@param side The side of the IGSideMenuView that will open. (IGSideMenuLocationLeft or IGSideMenuLocationRight)
*/
- (void)sideMenuView:(IGSideMenuView *)sideMenuView sideWillOpen:(IGSideMenuLocation)side;
@end

/*!
The IGSideMenuView allows for a view to be exposed or hidden programmatically or through user interaction on the left or right side of the IGSideMenuView.
*/
@interface IGSideMenuView : UIView

/** Allows or disallows user interaction on views contained in the contentView when a side menu is exposed.
*/
@property (nonatomic, assign) BOOL allowContentUserInteraction;

/** The main content area that covers the left and right menu views.
Views that you wish to be presented as content inside of the IGSideMenuView should be added to the contentView.

Note: If by accident content is added to the IGSideMenuView, the view will be automatically added to the contentView.
*/
@property (nonatomic, readonly) UIView *contentView;

/** Sets the IGSideMenuViewDelegate for the IGSideMenuView.
 */
@property (nonatomic, assign, nullable) id<IGSideMenuViewDelegate> delegate;

/** Returns whether or not a side menu is exposed.
 */
@property (nonatomic, readonly) BOOL isMenuOpen;

/** The view that can be exposed programmatically or through interaction on the left side of the view.
*/
@property (nonatomic, retain, nullable) UIView *leftMenuView;

/** The view that covers and prevents interaction on the contentView when a menu on either side has been exposed.
*/
@property (nonatomic, readonly) UIView *lockView;

/** The long press gesture instance that is used on the contentView for exposing a side.
Note: When presentsWithGesture is set to NO, this gesture is not used on the contentView.
*/
@property (nonatomic, readonly) UILongPressGestureRecognizer *longPressGesture;

/** The minimum long press duration, the default is 0.02.
*/
@property (nonatomic, assign) CGFloat minimumPressDuration;

/** The view that can be exposed programmatically or through interaction on the right side of the view.
*/
@property (nonatomic, retain, nullable) UIView *rightMenuView;

/** A value that represents time in seconds it will take for the contentView to animation.
Note: When a long press gesture is used to expose a side, the transitionDuration is not used for animation.
*/
@property (nonatomic, assign) CGFloat transitionDuration;

/** Determines whether or not to allow the exposing of a side through a long press gesture.
*/
@property (nonatomic, assign) BOOL presentsWithGesture;

/** Closes the exposed side.
 */
- (void)closeSideMenu;

/** Exposes the specified side.
@param side The side of the IGSideMenuView to expose.
 */
- (void)openSideMenu:(IGSideMenuLocation)side;

@end

NS_ASSUME_NONNULL_END