//
// Created by TBetts on 3/15/13.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

@class IGOverlayView;

/*!
The delegate of a _IGOverlayView_ object must adopt the _IGOverlayDelegate_ protocol.

All methods and properties in this protocol are optional.

 */
@protocol IGOverlayViewDelegate <NSObject>

@optional

/** Requests the custom _CGRect_ frame from which the _IGOverlayView_ will animate from when shown.

**Note:** This delegate method is called when using _IGOverlayAnimationCustomFade_ and _IGOverlayAnimationCustomSlide_ animation types.

@param overlayView The _IGOverlayView_ that is requesting the custom frame.
*/
-(CGRect)customEnterFrameForOverlay:(IGOverlayView *)overlayView;

/** Requests the custom _CGRect_ frame from which the _IGOverlayView_ will animate to when dismissed.

**Note:** This delegate method is called when using _IGOverlayAnimationCustomFade_ and _IGOverlayAnimationCustomSlide_ animation types.

@param overlayView The _IGOverlayView_ that is requesting the custom frame.
*/
-(CGRect)customExitFrameForOverlay:(IGOverlayView *)overlayView;

/** Provide custom animation for views when the _IGOverlayView_ is animating into its enter frame.

**Note:** This delegate method is called when using _IGOverlayAnimationCustomFade_ and _IGOverlayAnimationCustomSlide_ animation types.

@param overlayView The _IGOverlayView_ that is requesting the custom enter animation.
*/
-(void)customEnterAnimationForOverlay:(IGOverlayView *)overlayView;

/** Provide custom animation for views when the _IGOverlayView_ is animating into its exit frame.

**Note:** This delegate method is called when using _IGOverlayAnimationCustomFade_ and _IGOverlayAnimationCustomSlide_ animation types.

@param overlayView The _IGOverlayView_ that is requesting the custom exit animation.
*/
-(void)customExitAnimationForOverlay:(IGOverlayView *)overlayView;

/** Requests a custom _CGRect_ for the _IGOverlayView_ to animate to when showing.
@param overlayView The _IGOverlayView_ that is requesting the custom location.
*/
-(CGRect)displayLocationForOverlayView:(IGOverlayView*)overlayView;

/** Informs the delegate that the _IGOverlayView_ has been dismissed.

@param overlayView The _IGOverlayView_ that was dismissed.
*/
-(void)overlayDismissed:(IGOverlayView *)overlayView;

@end

/*!
The _IGOverlayView_ is a powerful and extremely flexible control for displaying any type of view that will overlay another view, with or without animation, when shown or dismissed. A total of 12 overlay animations are included, with 2 of these animation types allowing for custom animations limited by your imagination.

Adding views to overlay another view is a cinch, but if you require more than a quick and simple solution, the _IGOverlayView_ was also designed to be extended upon. By deriving from the _IGOverlayView_ class, you can tap into your creative psyche while using the _IGOverlayView_ to help push your app to the next level.

 */
@interface IGOverlayView : UIView

/*!
 These specify the overlay view animation when entering or exiting the view.
*/
typedef NS_ENUM(NSInteger, IGOverlayAnimationType)
{
    /** Do not animate in or out. */
    IGOverlayAnimationNone = 0,
    /** Animate from the top down when entering or animate from the bottom up when exiting. */
    IGOverlayAnimationSlideTop,
    /** Animate to complete opacity from the top down when entering or animate to no opacity from the bottom up when exiting. */
    IGOverlayAnimationSlideTopFade,
    /** Animate from the left right when entering or animate from the right left when exiting. */
    IGOverlayAnimationSlideLeft,
    /** Animate to complete opacity from the left right when entering or animate to no opacity from the right left when exiting. */
    IGOverlayAnimationSlideLeftFade,
    /** Animate from the right left when entering or animate from the left right when exiting. */
    IGOverlayAnimationSlideRight,
    /** Animate to complete opacity from the right left when entering or animate to no opacity from the left right when exiting. */
    IGOverlayAnimationSlideRightFade,
    /** Animate from the bottom top when entering or animate from the top bottom when exiting. */
    IGOverlayAnimationSlideBottom,
    /** Animate to complete opacity from the bottom top when entering or animate to no opacity from the top bottom when exiting. */
    IGOverlayAnimationSlideBottomFade,
    /** Animate to complete opacity when entering or animate to no opacity when exiting. */
    IGOverlayAnimationFade,
    /** Animate to complete opacity when entering or animate to no opacity when exiting with the addition of calling implemented animation delegate methods. */
    IGOverlayAnimationCustomFade,
    /** Animate when entering or exiting by calling implemented animation delegate methods. */
    IGOverlayAnimationCustomSlide
} ;

///---------------------------------------------------------------------------------------
/// @name Initialization and Configuration
///---------------------------------------------------------------------------------------

/** The object that acts as the delegate of the _IGOverlayView_.

The class must adopt the _IGOverlayDelegate_ protocol.

*/
@property (nonatomic, assign, nullable) id<IGOverlayViewDelegate> delegate;

/** The amount of time in seconds that it will take for the _IGOverlayView_ to animate into the enter frame position.

The default value is set for 1.0 second.

*/
@property (nonatomic, assign) NSTimeInterval durationShow;

/** The amount of time in seconds that it will take for the _IGOverlayView_ to animate into the exit frame position.

The default value is set for 1.0 second.

*/
@property (nonatomic, assign) NSTimeInterval durationDismiss;

///---------------------------------------------------------------------------------------
/// @name Overlay Visibility
///---------------------------------------------------------------------------------------

/** Show the _IGOverlayView_ in the specified view.

Supported animation type key enumeration values:

- **IGOverlayAnimationNone** - the _IGOverlayView_ will appear with no animation.
- **IGOverlayAnimationSlideTop** - the _IGOverlayView_ will slide down from the top of the specified view.
- **IGOverlayAnimationSlideTopFade** - the _IGOverlayView_ will fade in and slide down from the top of the specified view.
- **IGOverlayAnimationSlideLeft** - the _IGOverlayView_ will slide into the specified view from the left.
- **IGOverlayAnimationSlideLeftFade** - the _IGOverlayView_ will fade in and slide from the left of the specified view.
- **IGOverlayAnimationSlideRight** - the _IGOverlayView_ will slide into the specified view from the right.
- **IGOverlayAnimationSlideRightFade** - the _IGOverlayView_ will fade in and slide from the right of the specified view.
- **IGOverlayAnimationSlideBottom** - the _IGOverlayView_ will slide up from bottom of the specified view.
- **IGOverlayAnimationSlideBottomFade** - the _IGOverlayView_ will fade in and slide up from the bottom of the specified view.
- **IGOverlayAnimationFade** - the _IGOverlayView_ will fade into the specified view.
- **IGOverlayAnimationCustomFade** - the _IGOverlayView_ will fade into from the specified enter frame returned from the customEnterFrameForOverlay: _IGOverlayDelegate_ method into the specified view. This animation type will also attempt to call the customEnterAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.
- **IGOverlayAnimationCustomSlide** - the _IGOverlayView_ will slide from the specified enter frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method into the specified view. This animation type will also attempt to call the customEnterAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.

@param view The _UIView_ in which the _IGOverlayView_ will be shown.
@param animationType The type of animation to use when the _IGOverlayView_ is shown.
*/
-(void)showInView:(UIView *)view withAnimation:(IGOverlayAnimationType)animationType;

/** Dismiss the _IGOverlayView_ from its superview.

Supported animation type key enumeration values:

- **IGOverlayAnimationNone** - the _IGOverlayView_ will be dismissed with no animation.
- **IGOverlayAnimationSlideTop** - the _IGOverlayView_ will slide up and out of the specified view.
- **IGOverlayAnimationSlideTopFade** - the _IGOverlayView_ will fade out and slide up and out of the specified view.
- **IGOverlayAnimationSlideLeft** - the _IGOverlayView_ will slide out of the specified view to the left.
- **IGOverlayAnimationSlideLeftFade** - the _IGOverlayView_ will fade out and slide left and out of the specified view.
- **IGOverlayAnimationSlideRight** - the _IGOverlayView_ will slide out of the specified view to the right.
- **IGOverlayAnimationSlideRightFade** - the _IGOverlayView_ will fade out and slide right and out of the specified view.
- **IGOverlayAnimationSlideBottom** - the _IGOverlayView_ will slide down and out of the specified view.
- **IGOverlayAnimationSlideBottomFade** - the _IGOverlayView_ will fade out and slide down out and out of the specified view.
- **IGOverlayAnimationFade** - the _IGOverlayView_ will fade out of the specified view.
- **IGOverlayAnimationCustomFade** - the _IGOverlayView_ will fade out of the view to the exit frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method. This animation type will also attempt to call the customExitAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.
- **IGOverlayAnimationCustomSlide** - the _IGOverlayView_ will slide out of the view to the specified exit frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method. This animation type will also attempt to call the customExitAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.

@param animationType The type of animation to use when the _IGOverlayView_ is dismissed.
*/
-(void)dismiss:(IGOverlayAnimationType)animationType;

/** Gets a value to determine whether or not the _IGOverlayView_ is currently visible. This method will return YES if visible and NO if not visible.
*/
@property (nonatomic, readonly) BOOL visible;

///---------------------------------------------------------------------------------------
/// @name Animation Frame Position
///---------------------------------------------------------------------------------------

/** Returns a _CGRect_ containing the enter position of the _IGOverlayView_ when shown in the specified view with the specified animation type.

Supported animation type key enumeration values:

- **IGOverlayAnimationNone** - the _IGOverlayView_ will appear with no animation.
- **IGOverlayAnimationSlideTop** - the _IGOverlayView_ will slide down from the top of the specified view.
- **IGOverlayAnimationSlideTopFade** - the _IGOverlayView_ will fade in and slide down from the top of the specified view.
- **IGOverlayAnimationSlideLeft** - the _IGOverlayView_ will slide into the specified view from the left.
- **IGOverlayAnimationSlideLeftFade** - the _IGOverlayView_ will fade in and slide from the left of the specified view.
- **IGOverlayAnimationSlideRight** - the _IGOverlayView_ will slide into the specified view from the right.
- **IGOverlayAnimationSlideRightFade** - the _IGOverlayView_ will fade in and slide from the right of the specified view.
- **IGOverlayAnimationSlideBottom** - the _IGOverlayView_ will slide up from bottom of the specified view.
- **IGOverlayAnimationSlideBottomFade** - the _IGOverlayView_ will fade in and slide up from the bottom of the specified view.
- **IGOverlayAnimationFade** - the _IGOverlayView_ will fade into the specified view.
- **IGOverlayAnimationCustomFade** - the _IGOverlayView_ will fade into from the specified enter frame returned from the customEnterFrameForOverlay: _IGOverlayDelegate_ method into the specified view. This animation type will also attempt to call the customEnterAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.
- **IGOverlayAnimationCustomSlide** - the _IGOverlayView_ will slide from the specified enter frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method into the specified view. This animation type will also attempt to call the customEnterAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.

@param view The _UIView_ in which the _IGOverlayView_ will be shown.
@param animationType The type of animation to use when the _IGOverlayView_ is shown.
*/
-(CGRect)enterAnimationFrame:(UIView *)view withAnimation:(IGOverlayAnimationType)animationType;

/** Returns a _CGRect_ containing the exit position of the _IGOverlayView_ when dismissed from the specified view with the specified animation type.

Supported animation type key enumeration values:

- **IGOverlayAnimationNone** - the _IGOverlayView_ will be dismissed with no animation.
- **IGOverlayAnimationSlideTop** - the _IGOverlayView_ will slide up and out of the specified view.
- **IGOverlayAnimationSlideTopFade** - the _IGOverlayView_ will fade out and slide up and out of the specified view.
- **IGOverlayAnimationSlideLeft** - the _IGOverlayView_ will slide out of the specified view to the left.
- **IGOverlayAnimationSlideLeftFade** - the _IGOverlayView_ will fade out and slide left and out of the specified view.
- **IGOverlayAnimationSlideRight** - the _IGOverlayView_ will slide out of the specified view to the right.
- **IGOverlayAnimationSlideRightFade** - the _IGOverlayView_ will fade out and slide right and out of the specified view.
- **IGOverlayAnimationSlideBottom** - the _IGOverlayView_ will slide down and out of the specified view.
- **IGOverlayAnimationSlideBottomFade** - the _IGOverlayView_ will fade out and slide down out and out of the specified view.
- **IGOverlayAnimationFade** - the _IGOverlayView_ will fade out of the specified view.
- **IGOverlayAnimationCustomFade** - the _IGOverlayView_ will fade out of the view to the exit frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method. This animation type will also attempt to call the customExitAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.
- **IGOverlayAnimationCustomSlide** - the _IGOverlayView_ will slide out of the view to the specified exit frame returned from the customExitFrameForOverlay: _IGOverlayDelegate_ method. This animation type will also attempt to call the customExitAnimationForOverlay: _IGOverlayDelegate_ method for any custom UIView property animations.

@param view The _UIView_ in which the _IGOverlayView_ will be shown.
@param animationType The type of animation to use when the _IGOverlayView_ is dismissed.
*/
-(CGRect)exitAnimationFrame:(UIView *)view withAnimation:(IGOverlayAnimationType)animationType;

@end

NS_ASSUME_NONNULL_END