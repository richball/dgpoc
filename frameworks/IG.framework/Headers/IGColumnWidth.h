//
//  IGColumnWidth.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

/*! IGColumnWidth is an object that is used to tell the IGGridView how big a particular column should be. 
 
 There are 2 options. 
 
 The first option is simply a point value. So if you want your column to be 200pts wide, simply create a column width using the following initializers and specify 200:

 `width = [[IGColumnWidth alloc]initWithWidth:200];`
 
 `width = [[IGColumnWidth alloc]initWithWidth:200 and MinWidth:50];`
 
 The second option is to have the column take up a percentage of available space. For example, say you have 5 columns. and your grid is 100pts wide. If every column is given the
 same value for filling available space, lets say 1, then every column will be 20pts wide. 
    
 `width = [[IGColumnWidth alloc]initWithFillAvailableSpacePercent:1];`
 
 `width = [[IGCOlumnWidth alloc]initWithFillAvailableSpacePercent:1 and MinWidth:10];`

 Note the value doesn't actually have to be 1, as long as they're all the same, they'll have the same weight. So the following code will produce the same result:
 
 `width = [[IGColumnWidth alloc]initWithFillAvailableSpacePercent:928283];`
 
 `width = [[IGColumnWidth alloc]initWithFillAvailableSpacePercent:928283 and MinWidth:10];`
 
Now, say your first column has more content, and you want it to take more size, you can simply set it's value to be bigger than the other columns value, and it will take up more space:

 `column1Width = [[IGColumnWidth alloc]initWithFillAvailableSpacePercent:2];`
 
 `allOtherColumnWidths = [[IGColumnWidth alloc]initWithFillAvailableSpacePercent:1];`

 In this example, column 1 would come out to be about 33pts and all the other columns will come out to be about 16pts. 
 
 What exactly is happening here? Well, basically the values you specify when using the fillAvaliableSpace options are weights. And what happens internally is all columns that use this weight system get their values added up. Then the avaialabe space left in the grid is taken and divided by the total value of all the weights. After that each column gets assigned it's actual width size by multiplying its weight value by the amount of space each unit of weight is worth. The key here is that a unit if weight is calculated by the available space in the grid. If you have columns that have a specified point value, they have a higher priority of the space in the grid, which diminishes the actual available space. So if column 5 says I always want to be 50 pts wide, then the other 4 columns have only 50pts left that they can divide up. So, if there is no avaialbe space left, then there is nothing to divide up and all the available space columns will not be shown. However, that is what the MinWidth property is for. You can tell the column that it should fill available space, however, if it's size is smaller than the minimum width, then it should at least be the minimum width. One thing to note about Minimum Widths is that if a column says that it needs to be bigger than it's calculated point size, the points are not recalculated for the other columns. So by using the minWidth property you can get into a state where the total column size is larger than the viewport of the grid view.
 
 The really nice thing about using fillAvailableSpace columns, is that when the grid resizes so do the columns. The thing to note though, is with this option, unless their is a minimum width set, there will never be any horizontal scrolling.
*/
@interface IGColumnWidth : NSObject<NSCoding>
{
    BOOL _fillEmptySpace;
    CGFloat _value, _minWidth;
}

///---------------------------------------------------------------------------------------
/// @name Initializers
///---------------------------------------------------------------------------------------


/** Creates an IGColumnWidth with the specified point value, and a minimum width of 0. 
 
 @param width A float value which represnts the number of points that a column should be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithWidth:(CGFloat)width NS_DESIGNATED_INITIALIZER;

/** Creates an IGColumnWidth with the specified point value, and specified minimum width. 
 
 @param width A float value which represnts the number of points that a column should be.
 @param minWidth A float value that specifies the minimum size that the column can be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithWidth:(CGFloat)width andMinWidth:(CGFloat)minWidth NS_DESIGNATED_INITIALIZER;

/** Creates an IGColumnWidth with that will fill the available space using the specified weight. The minimum width will be zero.
 
 @param value A float value which represnts the weight of the available size of the grid that a column should take up.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithFillAvailableSpacePercent:(CGFloat)value NS_DESIGNATED_INITIALIZER;

/** Creates an IGColumnWidth with that will fill the available space using the specified weight. If there isn't enough available space, the column will be come the specified mimimum width

 @param value A float value which represnts the weight of the available size of the grid that a column should take up.
 @param minWidth A float value that specifies the minimum size that the column can be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithFillAvailableSpacePercent:(CGFloat)value andMinWidth:(CGFloat)minWidth NS_DESIGNATED_INITIALIZER;


/** Creates an IGColumnWidth with the specified point value, and a minimum width of 0.
 
 @param width A float value which represnts the number of points that a column should be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
+(IGColumnWidth*)CreateWithFixedWidth:(CGFloat)width;

/** Creates an IGColumnWidth with the specified point value, and specified minimum width.
 
 @param width A float value which represnts the number of points that a column should be.
 @param minWidth A float value that specifies the minimum size that the column can be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
+(IGColumnWidth*)CreateWithFixedWidth:(CGFloat)width andMinWidth:(CGFloat)minWidth;

/** Creates an IGColumnWidth with that will fill the available space using the specified weight. The minimum width will be zero.
 
 @param value A float value which represnts the weight of the available size of the grid that a column should take up.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
+(IGColumnWidth*)CreateWithPercentWidth:(CGFloat)value;

/** Creates an IGColumnWidth with that will fill the available space using the specified weight. If there isn't enough available space, the column will be come the specified mimimum width
 
 @param value A float value which represnts the weight of the available size of the grid that a column should take up.
 @param minWidth A float value that specifies the minimum size that the column can be.
 @return Returns an initialized IGColumnWidth object or nil if the object could not be successfully initialized.
 */
+(IGColumnWidth*)CreateWithPercentWidth:(CGFloat)value andMinWidth:(CGFloat)minWidth;

///---------------------------------------------------------------------------------------
/// @name Properties
///---------------------------------------------------------------------------------------

/** Gets either the point value of the column width or the weight value of the column width depending ont he initializer that was chosen (readonly)
 
 */
@property(nonatomic, readonly) CGFloat value;

/** Gets whether the column was intialized with a weight value (readonly)
 
 */
@property(nonatomic, readonly) BOOL fillEmptySpace;

/** Gets the minimum width that the column will fall back to. (readonly)
 
 */
@property(nonatomic, readonly) CGFloat minimumWidth;

@end
