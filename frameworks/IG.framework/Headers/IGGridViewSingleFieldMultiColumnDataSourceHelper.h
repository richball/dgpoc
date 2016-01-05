//
//  IGGridViewSingleFieldMultiColumnDataSourceHelper.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGGridViewSingleRowSingleFieldDataSourceHelper.h"

/** A IGGridViewDataSourceHelper that treats each row as column. These columns are then divided by the numberOfColumns property, and split into rows. If a row does not have enough columns left over to be displayed, no cell will be created for that spot.
 
 A field must be specified, as this is what will be displayed in each column.
 
 For more information on dataSource helpers, please read the documentation on IGGridViewDataSourceHelper. 
 */
@interface IGGridViewSingleFieldMultiColumnDataSourceHelper : IGGridViewDataSourceHelper
{
    NSInteger _fieldIndex;
    IGGridViewColumnDefinition* _field;
}

/** Creates an IGGridViewSingleFieldMultiColumnDataSourceHelper to display your data. 
 
 @param field  A IGGridViewColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView.
 @return Returns an initialized IGGridViewSingleFieldMultiColumnDataSourceHelper object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithField:(IGGridViewColumnDefinition*)field NS_DESIGNATED_INITIALIZER;

/** A IGGridViewColumnIGGridViewImageColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView (readonly)
 
 */
@property(nonatomic, readonly, retain)IGGridViewColumnDefinition* field;

/** YES if cell reordering is allowed, or NO if it is not. 
 
 */
@property(nonatomic, assign) BOOL allowCellReordering;

/** Gets or sets the number of columns your data should be broken up into
 
 */
@property(nonatomic, assign) NSInteger numberOfColumns;

@end
