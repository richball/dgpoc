
#import <Foundation/Foundation.h>

/*!
The _IGSlideTabContentSize_ is used to provide the tab item content view with an exact or dynamic sizing.
 */
@interface IGSlideTabContentSize : NSObject

/** Returns or sets whether or not the instance of _IGSlideTabContentSize_ is using percentage height.
*/
@property (nonatomic, assign) BOOL isPercentageHeight;

/** Returns or sets whether or not the instance of _IGSlideTabContentSize_ is using percentage width.
*/
@property (nonatomic, assign) BOOL isPercentageWidth;

/** Returns the height value of the tab item content view.

This view may also contain a percentage height when not using fixed values. Percent values are from 0.0 to 1.0.

*/
@property (nonatomic, assign) CGFloat height;

/** Returns the width value of the tab item content view.

This view may also contain a percentage width when not using fixed values. Percent values are from 0.0 to 1.0.

*/
@property (nonatomic, assign) CGFloat width;

/** Initializes the _IGSlideTabContentSize_ with a fixed height and width.

@param width The fixed width for the tab item content view.
@param height The fixed height for the tab item content view.
@return The _IGSlideTabContentSize_ instance.
*/
+ (IGSlideTabContentSize *)sizeWithWidth:(CGFloat)width height:(CGFloat)height;

/** Initializes the _IGSlideTabContentSize_ with a fixed width and percentage height. Percent values are from 0.0 to 1.0.

@param width The fixed width for the tab item content view.
@param percentageHeight The percentage height for the tab item content view.
@return The _IGSlideTabContentSize_ instance.
*/
+ (IGSlideTabContentSize *)sizeWithFixedWidth:(CGFloat)width percentageHeight:(CGFloat)percentageHeight;

/** Initializes the _IGSlideTabContentSize_ with a percentage width and fixed height. Percent values are from 0.0 to 1.0.

@param percentageWidth The percentage width for the tab item content view.
@param fixedHeight The fixed height for the tab item content view.
@return The _IGSlideTabContentSize_ instance.
*/
+ (IGSlideTabContentSize *)sizeWithPercentageWidth:(CGFloat)percentageWidth fixedHeight:(CGFloat)fixedHeight;

/** Initializes the _IGSlideTabContentSize_ with a percentage width and percentage height. Percent values are from 0.0 to 1.0.

@param percentageWidth The percentage width for the tab item content view.
@param percentageHeight The percentage height for the tab item content view.
@return The _IGSlideTabContentSize_ instance.
*/
+ (IGSlideTabContentSize *)sizeWithPercentageWidth:(CGFloat)percentageWidth percentageHeight:(CGFloat)percentageHeight;

@end