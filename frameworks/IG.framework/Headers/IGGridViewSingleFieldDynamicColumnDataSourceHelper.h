//
//  IGGridViewSingleRowSingleFieldDataSourceHelper.h
//
//  Copyright (c) 2015 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGGridViewSingleFieldMultiColumnDataSourceHelper.h"


/** A derivative of IGGridViewSingleFieldMultiColumnDataSourceHelper this class essentially figures out the numberOfColumns automatically, instead of you having to specify. Just set the targetWidth for the column, and it will figure out how many columns can fit in a specific row automatically based on the width of the grid. 
 
 A field must be specified, as this is what will be displayed in each column.
 
 For more information on dataSource helpers, please read the documentation on IGGridViewDataSourceHelper.
 */
@interface IGGridViewSingleFieldDynamicColumnDataSourceHelper : IGGridViewSingleFieldMultiColumnDataSourceHelper


/** Creates an IGGridViewSingleFieldMultiColumnDataSourceHelper to display your data.
 
 @param field  A IGGridViewColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView.
 @param targetWidth  The width that the DataSourceHelper will use to calculate how many columns should be visible.
 @return Returns an initialized IGGridViewSingleFieldDynamicColumnDataSourceHelper object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithField:(IGGridViewColumnDefinition*)field targetColumnWidth:(CGFloat)targetWidth NS_DESIGNATED_INITIALIZER;

/** Creates an IGGridViewSingleFieldMultiColumnDataSourceHelper to display your data.
 
 @param field  A IGGridViewColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView.
 @param targetWidth  The width that the DataSourceHelper will use to calculate how many columns should be visible.
 @param rowHeightAspectRatio  The aspect ratio that will be multipled by the actual column width, to set the height of all rows in the grid.
 @return Returns an initialized IGGridViewSingleFieldDynamicColumnDataSourceHelper object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithField:(IGGridViewColumnDefinition*)field targetColumnWidth:(CGFloat)targetWidth rowHeightAspect:(CGFloat)rowHeightAspectRatio NS_DESIGNATED_INITIALIZER;

/** The width that the DataSourceHelper will use to calculate how many columns should be visible.
 
 */
@property(nonatomic, assign)CGFloat targetColumnWidth;

/** The aspect ratio that will be multipled by the actual column width, to set the height of all rows in the grid.
 
    If you don't want the DSH to set the rowHeight set this to a NAN.
 */
@property(nonatomic, assign)CGFloat rowHeightAspectRatio;

@end