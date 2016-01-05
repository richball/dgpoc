//
//  IGCellPath.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGRowPath.h"



/** IGCellPath is a coordinate system in the IGGridView for identifying a specific cell with in the IGGridView.
 
 You can get a string representation of the path by using the description property.
 */
@interface IGCellPath : IGRowPath
{
    NSInteger _column;
}

/** Creates a IGCellPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @param column The index of a column within the row
 @return Returns an initialized IGCellPath object or nil if the object could not be successfully initialized.
 */
-(instancetype)initForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column NS_DESIGNATED_INITIALIZER;

/** Creates a IGCellPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @param column The index of a column within the row
 @return Returns an initialized IGCellPath object or nil if the object could not be successfully initialized.
 */
+ (IGCellPath *)pathForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column;

/** Creates a IGCellPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @param column The index of a column within the row
 @param fixed Whether the column is fixed
 @return Returns an initialized IGCellPath object or nil if the object could not be successfully initialized.
 */
-(instancetype)initForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column isFixed:(IGGridViewFixedColumnDirection)fixed NS_DESIGNATED_INITIALIZER;

-(instancetype)initForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column isFixed:(IGGridViewFixedColumnDirection)fixed isRowFixed:(IGGridViewFixedRowDirection)rowFixed;

/** Creates a IGCellPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @param column The index of a column within the row
 @param fixed Whether the column is fixed
 @return Returns an initialized IGCellPath object or nil if the object could not be successfully initialized.
 */
+ (IGCellPath *)pathForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column isFixed:(IGGridViewFixedColumnDirection)fixed;

+ (IGCellPath *)pathForRow:(NSInteger)row inSection:(NSInteger)section inColumn:(NSInteger)column isFixed:(IGGridViewFixedColumnDirection)fixed isRowFixed:(IGGridViewFixedRowDirection)rowFixed;

/** Creates a duplicate instance of the existing path
 */
-(IGCellPath *)cloneCell;

/** The index of a column within the row
 */
@property(nonatomic, readonly) NSInteger columnIndex;

/** Whether the path represents a fixed cell
 */
@property(nonatomic, readonly) IGGridViewFixedColumnDirection isFixed;

@end
