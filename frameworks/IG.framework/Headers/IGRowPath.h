//
//  IGRowPath.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

@class IGCellPath;

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, IGGridViewFixedRowDirection)
{
    IGGridViewFixedRowDirectionNone,
    IGGridViewFixedRowDirectionTop
    
};

typedef NS_ENUM(NSInteger, IGGridViewFixedColumnDirection)
{
    IGGridViewFixedColumnDirectionNone,
    IGGridViewFixedColumnDirectionLeft,
    IGGridViewFixedColumnDirectionRight
    
};


/** IGRowPath is a coordinate system in the IGGridView for identifying a specific row with in a specific section of data.
 
 You can get a string representation of the path by using the description property.
 */
@interface IGRowPath : NSObject
{
    NSInteger _row, _section;
    NSString* _key;
    IGGridViewFixedRowDirection _fixedRowDirection;
}

/** The index of a row within a section
 
 */
@property(nonatomic,readonly) NSInteger rowIndex;

/** The index of a section within the IGGridView
 
 */
@property(nonatomic, readonly) NSInteger sectionIndex;

/** Whether the path represents a fixed row.
 */
@property(nonatomic, readonly) IGGridViewFixedRowDirection isRowFixed;


/** Creates a IGRowPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @return Returns an initialized IGRowPath object or nil if the object could not be successfully initialized.
 */
-(instancetype)initForRow:(NSInteger)row inSection:(NSInteger)section NS_DESIGNATED_INITIALIZER;

/** Creates a IGRowPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @param fixed Whether the row is fixed.
 @return Returns an initialized IGRowPath object or nil if the object could not be successfully initialized.
 */
-(instancetype)initForRow:(NSInteger)row inSection:(NSInteger)section isRowFixed:(IGGridViewFixedRowDirection)fixed NS_DESIGNATED_INITIALIZER;

/* Convenience method that converts the IGRowPath to a IGCellPath. 
 
@return Returns an IGCellPath for column 0
 */
-(IGCellPath*)convertToCellPath;

/* Convenience method that converts the IGRowPath to a IGCellPath.
 
 @param column The column that will be used for the IGCellPath
 @return Returns an IGCellPath for the specified column.
 */
-(IGCellPath*)convertToCellPath:(NSInteger)column;

/* Convenience method that converts the IGRowPath to a IGCellPath.
 
 @param column The column that will be used for the IGCellPath
 @param fixedColDir The fixedColumn direction
 @return Returns an IGCellPath for the specified column.
 */
-(IGCellPath *)convertToCellPath:(NSInteger)column fixed:(IGGridViewFixedColumnDirection)fixedColDir;

/** Creates a IGRowPath using the specified coordinates.
 
 @param row The index of a row within a section
 @param section The index of a section within the IGGridView
 @return Returns an initialized IGRowPath object or nil if the object could not be successfully initialized.
 */
+ (IGRowPath *)pathForRow:(NSInteger)row inSection:(NSInteger)section;

/** Creates a fixed top IGRowPath using the specified row index.
 
 @param row The index of the fixed row.
 @return Returns an initialized IGRowPath object or nil if the object could not be successfully initialized.
 */
+ (IGRowPath *)pathForFixedTopRow:(NSInteger)row;

/** Creates a duplicate instance of the existing path
 */
-(IGRowPath*)cloneRow;


@end
