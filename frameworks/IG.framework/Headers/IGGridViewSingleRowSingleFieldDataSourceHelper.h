//
//  IGGridViewSingleRowSingleFieldDataSourceHelper.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGGridViewDataSourceHelper.h"
#import "IGGridViewColumnDefinition.h"

/** A IGGridViewDataSourceHelper that treats each row as column, and only displays one field in the underlying data. 

 A field must be specified, as this is what will be displayed in each column.
 
 For more information on dataSource helpers, please read the documentation on IGGridViewDataSourceHelper. 
*/
@interface IGGridViewSingleRowSingleFieldDataSourceHelper : IGGridViewDataSourceHelper
{
    NSInteger _fieldIndex;
    IGGridViewColumnDefinition* _field;
}

/** Creates an IGGridViewSingleRowSingleFieldDataSourceHelper to display your data. 
 
 @param field  A IGGridViewColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView.
 @return Returns an initialized IGGridViewSingleRowSingleFieldDataSourceHelper object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithField:(IGGridViewColumnDefinition*)field NS_DESIGNATED_INITIALIZER;

/** A IGGridViewColumnIGGridViewImageColumnDefinition that maps to the one property of your data that will be displayed in the IGGridView (readonly)
 
*/
@property(nonatomic, readonly, retain)IGGridViewColumnDefinition* field;

/** YES if cell reordering is allowed, or NO if it is not. 
 
 */
@property(nonatomic, assign) BOOL allowCellReordering;

@end
