#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

/*!

The _IGProgressView_ is a multifaceted progress control capable of rendering standard, radial, or even custom progress shapes. In addition, to the _IGProgressView_ looking great out of the box, nearly every part _IGProgressView_ can be styled to look great in your app. Properties such as progressTintColor and progressTrackTintColor make it simple to adjust the color of the _IGProgressView_. Although, if you require finer tuning; progressShapeLayer, progressTrackShapeLayer, and radialInsertShapeLayer are exposed to give you complete control over the progress appearance all the way down to the stroke used. The styling doesn't stop at only visual appearance, the properties progressAnimationDuration and progressAnimationTimingFunction allow for polishing the animation that occurs when the progress changes value.

 */
@interface IGProgressView : UIView

/*!
 These specify the progress visual style.
*/
typedef NS_ENUM(NSInteger, IGProgressViewStyle)
{
    /** A rectangular progress bar that continously animates an indeterminate state. */
    IGProgressViewStyleStandardIndeterminate = 0,
    /** A rectangular progress bar. */
    IGProgressViewStyleStandard,
    /** A circular progress that animates a continuous indeterminate state. */
    IGProgressViewStyleRadialIndeterminate,
    /** A circular progress. */
    IGProgressViewStyleRadial,
    /** A progress drawn from a specified shape path. */
    IGProgressViewStyleCustom
} ;

///---------------------------------------------------------------------------------------
/// @name Initialization and Configuration
///---------------------------------------------------------------------------------------

/** The current progress shown by the _IGProgressView_.

The current progress is represented by a floating-point value between 0.0 and 1.0. A value of 1.0 indicates the completion of the task. The default value is 0.0. Values less than 0.0 and greater than 1.0 are pinned to those limits.

*/
@property (nonatomic, assign) CGFloat progress;

/** The animation duration when animating the progress to a new value. Type: _CGFloat_ Default: _0.25_

The animation duration is measured in seconds. This property is used with the __IGProgressViewStyleRadial__ and __IGProgressViewStyleStandard__ progress styles.

*/
@property (nonatomic, assign) CGFloat progressAnimationDuration;

/** The constant used to specify one of the predefined Core Animation timing functions. Type: _NSString *_ Default: _kCAMediaTimingFunctionDefault_

This property is used with the __IGProgressViewStyleRadial__ and __IGProgressViewStyleStandard__ progress styles.

*/
@property (nonatomic, assign) NSString *progressAnimationTimingFunction;

/** Returns the style of the _IGProgressView_. (read-only)

 Supported styles:
 
 - **IGProgressViewStyleStandardIndeterminate**
 - **IGProgressViewStyleStandard**
 - **IGProgressViewStyleRadialIndeterminate**
 - **IGProgressViewStyleRadial**
 - **IGProgressViewStyleCustom**
 */
@property (nonatomic, readonly) IGProgressViewStyle progressViewStyle;

/** Adjusts the current progress shown by the _IGProgressView_, optionally animating the change.

The current progress is represented by a floating-point value between 0.0 and 1.0. A value of 1.0 indicates the completion of the task. The default value is 0.0. Values less than 0.0 and greater than 1.0 are pinned to those limits.

@param progress The new progress value.
@param animated _YES_ if the change should be animated, _NO_ if the change should happen immediately.
*/
-(void)setProgress:(CGFloat)progress animated:(BOOL)animated;

/** Initializes and returns an _IGProgressView_ object.

The initialized _IGProgressView_ will have a frame of _CGRectZero_ and will need set through the frame property.

@param customShape The _CGPathRef_ to use as the custom progress shape.
@return An initialized _IGProgressView_ object or _nil_ if the object couldn't be created.
*/
-(instancetype)initWithCustomShape:(CGPathRef)customShape NS_DESIGNATED_INITIALIZER;

/** Initializes and returns an _IGProgressView_ object.

@param frame The frame rectangle for the view, measured in points. The origin of the frame is relative to the superview in which you plan to add it. This method uses the frame rectangle to set the center and bounds properties accordingly.
@param customShape The _CGPathRef_ to use as the custom progress shape.
@return An initialized _IGProgressView_ object or _nil_ if the object couldn't be created.
*/
-(instancetype)initWithFrame:(CGRect)frame customShape:(CGPathRef)customShape NS_DESIGNATED_INITIALIZER;

/** Initializes and returns an _IGProgressView_ object.

 Supported styles:
 
 - **IGProgressViewStyleStandardIndeterminate**
 - **IGProgressViewStyleStandard**
 - **IGProgressViewStyleRadialIndeterminate**
 - **IGProgressViewStyleRadial**

@param frame The frame rectangle for the view, measured in points. The origin of the frame is relative to the superview in which you plan to add it. This method uses the frame rectangle to set the center and bounds properties accordingly.
@param progressStyle A _IGProgressViewStyle_ enumeration value that specifies the style of the progress to be created.
@return An initialized _IGProgressView_ object or _nil_ if the object couldn't be created.
*/
-(instancetype)initWithFrame:(CGRect)frame viewStyle:(IGProgressViewStyle)progressStyle NS_DESIGNATED_INITIALIZER;

/** Initializes and returns an _IGProgressView_ object.

The initialized _IGProgressView_ will have a frame of _CGRectZero_ and will need set through the frame property.

Supported styles:
 
- **IGProgressViewStyleStandardIndeterminate**
- **IGProgressViewStyleStandard**
- **IGProgressViewStyleRadialIndeterminate**
- **IGProgressViewStyleRadial**

@param progressStyle A _IGProgressViewStyle_ enumeration value that specifies the style of the progress to be created.
@return An initialized _IGProgressView_ object or _nil_ if the object couldn't be created.
*/
-(instancetype)initWithStyle:(IGProgressViewStyle)progressStyle NS_DESIGNATED_INITIALIZER;

///---------------------------------------------------------------------------------------
/// @name Progress Styling
///---------------------------------------------------------------------------------------

/** The _UIColor_ shown for the portion of the progress that is filled. Type: _UIColor_ Default: _colorWithRed:0.0 green:174/255.0 blue:239/255.0 alpha:1.0_
*/
@property (nonatomic, retain) UIColor *progressTintColor;

/** The _UIColor_ shown for the portion of the progress that is not filled. Type: _UIColor_ Default: _colorWithRed:88/255.0 green:89/255.0 blue:91/255.0 alpha:1.0_
*/
@property (nonatomic, retain) UIColor *progressTrackTintColor;

/** The _UIView_ placed into the center of the __IGProgressViewStyleRadial__ and __IGProgressViewStyleRadialIndeterminate__ progress styles. Type: _UIView_ Default: _nil_

When the _IGProgressView_ is drawn the _UIView_ will be re-sized to fit within the radial's insert.

*/
@property (nonatomic, retain, nullable) UIView *radialContentView;

/** The size of the __IGProgressViewStyleRadial__ and __IGProgressViewStyleRadialIndeterminate__ progress style's insert. Type: _CGFloat_ Default: _0.80_

The _radialInsertScale_ is represented by a floating-point value between 0.0 and 1.0. A value of 1.0 would completely cover the underlying radial progress. Values less than 0.0 and greater than 1.0 are pinned to those limits.

*/
@property (nonatomic, assign) CGFloat radialInsertScale;

/** The _UIColor_ shown for the insert portion of the __IGProgressViewStyleRadial__ and __IGProgressViewStyleRadialIndeterminate__ progress styles. Type: _UIColor_ Default: _whiteColor_
*/
@property (nonatomic, retain) UIColor *radialInsertTintColor;

/** The start angle for the scale in degrees. Type: _CGFloat_ Default: _270.0_

The angle system used starts at mathematical 0 degrees and sweeps clockwise 360 degrees. Values less than 0.0 or greater than 360.0 are wrapped.

*/
@property (nonatomic, assign) CGFloat radialStartAngle;

/** The end angle for the scale in degrees. Type: _CGFloat_ Default: _270.0_

The angle system used starts at mathematical 0 degrees and sweeps clockwise 360 degrees. Values less than 0.0 or greater than 360.0 are wrapped.

*/
@property (nonatomic, assign) CGFloat radialEndAngle;

/** The radius to use when drawing rounded corners for the _IGProgressViewStyleStandard_ and _IGProgressViewStyleStandardIndeterminate_ progress styles. Type: _CGFloat_ Default: _2.0_
*/
@property (nonatomic, assign) CGFloat standardCornerRadius;

///---------------------------------------------------------------------------------------
/// @name Progress Shape Layers
///---------------------------------------------------------------------------------------

/** Returns the _CAShapeLayer_ of the progress that is filled. (read-only)
*/
@property (nonatomic, readonly) CAShapeLayer *progressShapeLayer;

/** Returns the _CAShapeLayer_ of the progress that is not filled. (read-only)
*/
@property (nonatomic, readonly) CAShapeLayer *progressTrackShapeLayer;

/** Returns the _CAShapeLayer_ of the __IGProgressViewStyleRadial__ and __IGProgressViewStyleRadialIndeterminate__ progress style's insert. (read-only)
*/
@property (nonatomic, readonly) CAShapeLayer *radialInsertShapeLayer;

@end

NS_ASSUME_NONNULL_END
