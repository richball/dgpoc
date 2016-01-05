//
//  IGGridView.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import "IGGridViewCell.h"
#import "IGCellPath.h"
#import "IGColumnWidth.h"
#import "IGGridViewThemeDefinition.h"
#import "IGGridViewStringsDefinition.h"

NS_ASSUME_NONNULL_BEGIN

@class IGGridView;
@protocol IGGridViewDataSource;
@protocol IGGridViewDelegate;

extern int const kSectionHeaderIndex;
extern int const kSectionFooterIndex;
extern int const kFilterRowIndex;
extern int const kPullDownRowIndex;
extern int const kHeaderRowIndex;
extern int const kFixedRowSectionIndex;

typedef NS_ENUM(NSInteger, IGGridViewAnimation)
{
    IGGridViewAnimationFade, 
    IGGridViewAnimationRight, 
    IGGridViewAnimationLeft, 
    IGGridViewAnimationTop,
    IGGridViewAnimationBottom,
    IGGridViewAnimationNone,
    IGGridViewAnimationAutomatic
    
};

typedef NS_ENUM(NSInteger, IGGridViewScrollPosition) 
{
    IGGridViewScrollPositionNone,
    IGGridViewScrollPositionNoneLeft,
    IGGridViewScrollPositionNoneRight,
    IGGridViewScrollPositionNoneMiddle,
    IGGridViewScrollPositionTopLeft,
    IGGridViewScrollPositionTopMiddle,
    IGGridViewScrollPositionTopRight,
    IGGridViewScrollPositionTopNone,
    IGGridViewScrollPositionMiddleLeft,
    IGGridViewScrollPositionMiddle,
    IGGridViewScrollPositionMiddleRight,
    IGGridViewScrollPositionMiddleNone,
    IGGridViewScrollPositionBottomLeft, 
    IGGridViewScrollPositionBottomMiddle,
    IGGridViewScrollPositionBottomRight,
    IGGridViewScrollPositionBottomNone
} ;

typedef NS_ENUM(NSInteger, IGGridViewSelectionType)
{
    IGGridViewSelectionTypeRow,
    IGGridViewSelectionTypeCell,
    IGGridViewSelectionTypeNone
    
};

typedef NS_ENUM(NSInteger, IGGridViewStyle) 
{
    IGGridViewStyleDefault, 
    IGGridViewStyleSingleCellPaging
    
};

typedef NS_ENUM(NSInteger, IGGridViewFilterAction)
{
    IGGridViewFilterActionImmediate,
    IGGridViewFilterActionDoneEditing
}
;

typedef NS_ENUM(NSInteger, IGGridViewSwipeRowAction)
{
    IGGridViewSwipeRowActionNone,
    IGGridViewSwipeRowActionDeleteButton,
    IGGridViewSwipeRowActionSlideRowRight,
    IGGridViewSwipeRowActionSlideRowLeft,
    IGGridViewSwipeRowActionSlideRowBoth,
    IGGridViewSwipeRowActionManualSlideLeft,
    IGGridViewSwipeRowActionManualSlideRight,
    IGGridViewSwipeRowActionManualSlideBoth,
    IGGridViewSwipeRowActionPercentSlideLeft,
    IGGridViewSwipeRowActionPercentSlideRight,
    IGGridViewSwipeRowActionPercentSlideBoth,
    
    
}
;


typedef NS_ENUM(NSInteger, IGGridViewColumnResizeAction)
{
    IGGridViewColumnResizeActionNone,
    IGGridViewColumnResizeActionPinch,
    IGGridViewColumnResizeActionAdorner
}
;

typedef NS_ENUM(NSInteger, IGGridViewInfiniteScrolling)
{
    IGGridViewInfiniteScrollingNone,
    IGGridViewInfiniteScrollingHorizontal,
    IGGridViewInfiniteScrollingVertical,
    IGGridViewInfiniteScrollingBoth
    
};

typedef NS_ENUM(NSInteger, IGGridViewPullDownState)
{
    IGGridViewPullDownStateNone,
    IGGridViewPullDownStatePullDown,
    IGGridViewPullDownStateRelease,
    IGGridViewPullDownStateUpdating
}
;

/*!
 The IGGridViewDataSource protocol is adopted by an object that mediates the application's data model for a IGGridView object. The data source provides the grid view object with the information it needs to construct and modify a grid view. 
 
 As a representative of the data model, the data source supplies minimal information about the grid view's appearance. The grid view object's delegate provides that information. 
 
 The required methods of the protocol provide the cells to be displayed by the grid view as was as the number of rows in each section and number of columns. There are also optional methods for creating other cells such as a header cell or filter cell as well as handling data manipulation such as insertion, deletion and reordering.
 
 */
@protocol IGGridViewDataSource <NSObject>

///---------------------------------------------------------------------------------------
/// @name Configuring a Grid View
///---------------------------------------------------------------------------------------

@required
/** Asks the data source for a cell to place at a particular location in the grid view. (required)
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @param path The path of the cell that is needed
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location. 
 */
- (IGGridViewCell*) gridView:(IGGridView *)gridView cellAt:(IGCellPath*)path;

/** Asks the data source for the number of rows that should be displayed in the specified section. (required)
 
 @param gridView The grid view requesting the information. 
 @param section The index of the section. 
 @return The number of rows in the section.
 */
- (NSInteger) gridView:(IGGridView*)gridView numberOfRowsInSection:(NSInteger)section;

/** Asks the data source for the number of columns that should be displayed. (required)
 
 @param gridView The grid view requesting the information. 
 @return The number of columns in the grid view.
 */
- (NSInteger) numberOfColumnsInGridView:(IGGridView*)gridView;

/** Asks the data source for the number of fixed rows that should be displayed.
 
 @param gridView The grid view requesting the information.
 @return The number of fixed rows in the grid view.
 */
- (NSInteger) numberOfFixedRowsInGridView:(IGGridView*)gridView;


@optional

/** Tells the data source a cell is about to be released.
 
Allows the data source to do any additional clean up it may need to do for a particular cell.
 
 @param gridView The grid view providing the information.
 @param cell The cell that is being queued up to be reused. 
 @param path The path of the cell that is being released.
 */
- (void) gridView:(IGGridView *)gridView didEndDisplayingCell:(IGGridViewCell*)cell forCellAtPath:(IGCellPath*)path;

/** Asks the data source if any rows should be displayed as one cell instead of a cell for each column.
 
 Any rows specified will have a column index of -1 when the gridView:cellAt: method is invoked.
 
 @param gridView The grid view requesting the information. 
 @return An array of IGRowPath objects representing rows that should be stretched.
 */
-(NSArray*)rowPathsOfStretchRowsInGridView:(IGGridView*)gridView;

/** Asks the data source for the number of sections in the grid view.
 
 @param gridView The grid view requesting the information. 
 @return The number of sections in the grid view.
 */
- (NSInteger) numberOfSectionsInGridView:(IGGridView *)gridView;

/** Asks the data source for the text that should be displayed in the header of a section.
 
 @param gridView The grid view requesting the information. 
 @param section The index of the section.
 @return The text that should be displayed in the section header cell.
 */
- (NSString*)gridView:(IGGridView*)gridView titleForHeaderInSection:(NSInteger)section;

/** Asks the data source for the text that should be displayed in the footer of a section.
 
 @param gridView The grid view requesting the information. 
 @param section The index of the section.
 @return The text that should be displayed in the section footer cell.
 */
- (NSString*)gridView:(IGGridView*)gridView titleForFooterInSection:(NSInteger)section;

/** Asks the data source for the text that should be displayed in the header of a column.
 
 @param gridView The grid view requesting the information. 
 @param column The index of the column.
 @return The text that should be displayed in the column header cell.
 */
- (NSString*)gridView:(IGGridView*)gridView titleForHeaderInColumn:(NSInteger)column;


/** Asks the datasource if it's allowed to provide the row heights for the grid.
 
 If not implemented, the answer is assumed yes if the dataSource implements gridView:heightForRowAtPath:.
 
 @param gridView The grid view requesting the information.
 @return Yes if the gridView should ask it for the height of each row.
 */

-(BOOL)dataSourceProvidesRowHeightsForGridView:(IGGridView*)gridView;

/** Asks the datasource for the height of a particular row.
 
 This will be called for every row whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The height for the requested row.
 */
-(CGFloat)gridView:(IGGridView*)gridView heightForRowAtPath:(IGRowPath*)path;


/** Notifies the data source that a section should be expanded.
 
 @param gridView The grid view providing the information.
 @param section The index of the section.
 */
-(void)gridView:(IGGridView*)gridView expandSection:(NSInteger)section;

/** Notifies the data source that a section should be collapsed.
 
 @param gridView The grid view providing the information.
 @param section The index of the section.
 */
-(void)gridView:(IGGridView*)gridView collapseSection:(NSInteger)section;

/** Asks the data source if a particular section should be expanded or collapsed.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return Yes if the specified section should be expanded.
 */
-(BOOL)gridView:(IGGridView*)gridView sectionExpanded:(NSInteger)section;

/** Asks the data source if a particular section's header should be displayed.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return Yes if the section's header should be displayed.
 */
-(BOOL)gridView:(IGGridView*)gridView displayHeaderForSection:(NSInteger)section;

/** Asks the data source if a particular section's footer should be displayed.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return Yes if the section's footer should be displayed.
 */
-(BOOL)gridView:(IGGridView*)gridView displayFooterForSection:(NSInteger)section;

///---------------------------------------------------------------------------------------
/// @name Other Cells
///---------------------------------------------------------------------------------------

/** Deprecated, please use gridView:headerCellAt:
 
 @param gridView The grid view requesting the cell.
 @param column The index of the column
 @return An object inheriting IGGridViewHeaderCell that the grid view can use for the specified location. 
 */
- (IGGridViewHeaderCell *) gridView:(IGGridView *)gridView headerCellForRowAt:(NSInteger)column;

/** Asks the data source for a header cell to place at a particular location in the header of the grid view.
 
 The returned IGGridViewHeaderCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase.
 
 @param gridView The grid view requesting the cell.
 @param column The index of the column
 @return An object inheriting IGGridViewHeaderCell that the grid view can use for the specified location.
 */
- (IGGridViewHeaderCell *) gridView:(IGGridView *)gridView headerCellAt:(NSInteger)column;

/** Asks the data source for a header section cell to place at a particular location as the header of a section in the grid view.
 
 The returned IGGridViewSectionCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @param section The index of the section
 @return An object inheriting IGGridViewSectionCell that the grid view can use for the specified location. 
 */
- (IGGridViewSectionCell *) gridView:(IGGridView *)gridView cellForSectionHeader:(NSInteger)section;

/** Asks the data source for a footer section cell to place at a particular location as the footer of a section in the grid view.
 
 The returned IGGridViewSectionCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @param section The index of the section
 @return An object inheriting IGGridViewSectionCell that the grid view can use for the specified location. 
 */
- (IGGridViewSectionCell *) gridView:(IGGridView *)gridView cellForSectionFooter:(NSInteger)section;

/** Asks the data source for a row reordering indicator cell to place at a particular location in the grid view.
 
 The returned IGGridViewReorderCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @param path The path of the cell that is needed
 @return An object inheriting IGGridViewReorderCell that the grid view can use for the specified location. 
 */
- (IGGridViewReorderCell *) gridView:(IGGridView *)gridView cellForReorderingAtPath:(IGCellPath*)path;

/** Asks the data source for a pull down cell to place that will be used when pulling the grid view down further than its bounds.
 
 The returned IGGridViewPullDownCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @return An object inheriting IGGridViewPullDownCell that the grid view can use for the specified location. 
 */
- (IGGridViewPullDownCell *) pullDownCellForGridView:(IGGridView*)gridView;

///---------------------------------------------------------------------------------------
/// @name Filtering
///---------------------------------------------------------------------------------------

/** Asks the data source if filtering is supported
 
 @param gridView The grid view requesting the information.
 @return YES if filtering is supported
 */
- (BOOL)supportsFilteringInGridView:(IGGridView*)gridView;

/** Asks the data source to apply a filter.
 
 @param gridView The grid view requesting the information.
 @param filterText The text to perform the filter with.
 */
- (void)gridView:(IGGridView*)gridView applyFilterWithText:(NSString*)filterText;

/** Asks the data source for a filter cell to place at a particular location in the grid view.
 
 The returned IGGridViewFilterCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase. 
 
 @param gridView The grid view requesting the cell.
 @return An object inheriting IGGridViewFilterCell that the grid view can use for the specified location. 
 */
- (IGGridViewFilterCell *) filterCellForGridView:(IGGridView *)gridView;


///---------------------------------------------------------------------------------------
/// @name Shortcut Bar
///---------------------------------------------------------------------------------------

/** Asks the data source for a title for each section to be displayed in the shortcut bar.
 
 @param gridView The grid view requesting the information.
 @return An array of strings that serve as the title of sections in the grid view and appear in the shortcut bar on the right side of the grid view. The style of the grid view must be IGGridViewStyleDefault.
 */
- (NSArray *)sectionIndexTitlesForGridView:(IGGridView *)gridView;


/** Asks the data source for the index of a section given a title.
 
 @param gridView The grid view requesting the information.
 @param title The tile displayed in the shortcut bar.
 @param index The index of number of the title specified in the array returned by sectionIndexTitlesForGridView:
 @return An index number indetifying a section.
 */
- (NSInteger)gridView:(IGGridView *)gridView sectionForSectionIndexTitle:(NSString *)title atIndex:(NSInteger)index;

///---------------------------------------------------------------------------------------
/// @name Row Reordering
///---------------------------------------------------------------------------------------

/** Asks the data source if row reordering is allowed.
 
 @param gridView The grid view requesting the information.
 @return YES if reordering is allowed.
 */
-(BOOL)canReorderRows:(IGGridView*)gridView;


/** Asks the data source if a particular row can be moved.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row requesting to be moved.
 @return YES if the row can be moved.
 */
-(BOOL)gridView:(IGGridView*)gridView canMoveRowAtPath:(IGRowPath*)path;

/** Tells the data source to move a row.
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGRowPath of the row being moved
 @param destinationPath The IGRowPath where the source row should be moved to.
 */
-(void)gridView:(IGGridView*)gridView moveRowAtPath:(IGRowPath*)sourcePath toPath:(IGRowPath*)destinationPath;

///---------------------------------------------------------------------------------------
/// @name Cell Reordering
///---------------------------------------------------------------------------------------

/** Asks the data source if a particular cell can be moved.
 
 @param gridView The grid view requesting the information.
 @param path The IGCellPath of the cell requesting to be moved.
 @return YES if the cell can be moved.
 */
-(BOOL)gridView:(IGGridView *)gridView canMoveCellAtPath:(IGCellPath *)path;

/** Tells the data source to move a cell.
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGCellPath of the cell being moved
 @param destinationPath The IGCellPath where the source cell should be moved to.
 */
-(BOOL)gridView:(IGGridView *)gridView moveCellAtPath:(IGCellPath*) sourcePath toPath:(IGCellPath*)destinationPath;


///---------------------------------------------------------------------------------------
/// @name Column Reordering
///---------------------------------------------------------------------------------------

/** Asks the data source if a particular column can be moved.
 
 @param gridView The grid view requesting the information.
 @param index The index of the column requesting to be moved.
 @return YES if the column can be moved.
 */
-(BOOL)gridView:(IGGridView *)gridView canMoveColumnAtIndex:(NSInteger)index;

/** Tells the data source to move a column.
 
 @param gridView The grid view providing the information.
 @param sourceIndex The index of the column being moved
 @param destinationIndex The index where the source column should be moved to.
 */
-(void)gridView:(IGGridView *)gridView moveColumnAtIndex:(NSInteger) sourceIndex toIndex:(NSInteger)destinationIndex;

///---------------------------------------------------------------------------------------
/// @name Column Resizing
///---------------------------------------------------------------------------------------

/** Asks the datasource for the width of a specific column.
 
 This method has a lower priority than the method on the delegate.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column.
 @return The width of the column. Or nil if should fall back on to the grid column width property.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForColumnAtIndex:(NSInteger)column;

/** Asks the datasource for the width of a particular column pinned to the left of the grid view.
 
 This method has a lower priority than the method on the delegate.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column
 @return The IGColumnWidth of the requested column.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForFixedLeftColumnAtIndex:(NSInteger)column;

/** Asks the datasource for the width of a particular column pinned to the right of the grid view.
 
 This method has a lower priority than the method on the delegate.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column
 @return The IGColumnWidth of the requested column.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForFixedRightColumnAtIndex:(NSInteger)column;


/** Asks the data source if a particular column can be resized.
 
 @param gridView The grid view requesting the information.
 @param index The index of the column requesting to be resized.
 @return YES if the column can be resized.
 */
-(BOOL)gridView:(IGGridView *)gridView canResizeColumnAtIndex:(NSInteger)index;

/** Asks the data source if a particular column can be resized.
 
 @param gridView The grid view requesting the information.
 @param index The index of the column requesting to be resized.
 @return YES if the column can be resized.
 */
-(BOOL)gridView:(IGGridView *)gridView canResizeFixedLeftColumnAtIndex:(NSInteger)index;

/** Asks the data source if a particular column can be resized.
 
 @param gridView The grid view requesting the information.
 @param index The index of the column requesting to be resized.
 @return YES if the column can be resized.
 */
-(BOOL)gridView:(IGGridView *)gridView canResizeFixedRightColumnAtIndex:(NSInteger)index;

/** Tells the data source to resize a column.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;

/** Tells the data source to resize a column fixed to the left of the grid view.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeFixedLeftColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;

/** Tells the data source to resize a column fixed to the right of the grid view.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeFixedRightColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;

///---------------------------------------------------------------------------------------
/// @name Deleting Rows
///---------------------------------------------------------------------------------------

/** Asks the data source to commit the deletion of a specified row in the receiver.
 
 The data source commits the deletion by invoking the IGGridView method deleteRowsAtPaths:withAnimation:.
 
 @param gridView The grid view requesting the deletion.
 @param path The path locating the row in grid view.
 */
- (void)gridView:(IGGridView *)gridView deleteRowAtPath:(IGRowPath *)path;

/** Asks the data source to verify that the given row is deletable.
 
 If this method is not implemented, all rows are assumed to be deletable. 
 
 @param gridView The grid view requesting the information.
 @param path The path locating the row in grid view.
 @return YES if a row can be deleted.
 */
- (BOOL)gridView:(IGGridView *)gridView canDeleteRowAtPath:(IGRowPath *)path;

///---------------------------------------------------------------------------------------
/// @name Fixed Columns
///---------------------------------------------------------------------------------------

/** Asks the data source for the number of columns that should be pinned to the left of the grid view.
 
 @param gridView The grid view requesting the information.
 @return The number of columns pinned to the left of the grid view.
 */
- (NSInteger) numberOfFixedLeftColumnsInGridView:(IGGridView*)gridView;

/** Asks the data source for the number of columns that should be pinned to the right of the grid view.
 
 @param gridView The grid view requesting the information.
 @return The number of columns pinned to the right of the grid view.
 */
- (NSInteger) numberOfFixedRightColumnsInGridView:(IGGridView*)gridView;

/** Asks the data source for the text that should be displayed in the header of a column pinned to the left.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column.
 @return The text that should be displayed in the column header cell.
 */
- (NSString*)gridView:(IGGridView*)gridView titleForHeaderInFixedLeftColumn:(NSInteger)column;

/** Asks the data source for the text that should be displayed in the header of a column pinned to the right.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column.
 @return The text that should be displayed in the column header cell.
 */
- (NSString*)gridView:(IGGridView*)gridView titleForHeaderInFixedRightColumn:(NSInteger)column;


/** Asks the data source for a cell pinned to the left of the grid view.
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase.
 
 @param gridView The grid view requesting the cell.
 @param path The path of the cell that is needed
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location.
 */
- (IGGridViewCell*) gridView:(IGGridView *)gridView fixedLeftCellAt:(IGCellPath*)path;

/** Asks the data source for a cell pinned to the right of the grid view.
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase.
 
 @param gridView The grid view requesting the cell.
 @param path The path of the cell that is needed
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location.
 */
- (IGGridViewCell*) gridView:(IGGridView *)gridView fixedRightCellAt:(IGCellPath*)path;


/** Asks the data source for a header cell pinned to the left of the grid view.
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase.
 
 @param gridView The grid view requesting the cell.
 @param column The index of the cell that is needed
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location.
 */
- (IGGridViewHeaderCell*) gridView:(IGGridView *)gridView fixedLeftHeaderCellAt:(NSInteger)column;

/** Asks the data source for a header cell pinned to the right of the grid view.
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCellBase.
 
 @param gridView The grid view requesting the cell.
 @param column The index of the cell that is needed
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location.
 */
- (IGGridViewHeaderCell*) gridView:(IGGridView *)gridView fixedRightHeaderCellAt:(NSInteger)column;

///---------------------------------------------------------------------------------------
/// @name React to UI Changes
///---------------------------------------------------------------------------------------

/** Notifies the data source that the gridView's size has changed.
 
 @param gridView The grid view whose size has changed.
 @param previousSize The previous size of the grid
 @param newSize The new size of the grid.
 */
- (void)gridView:(IGGridView *)gridView sizeChangingFrom:(CGSize)previousSize toSize:(CGSize)newSize;

@end

/*!
 The delegate of a IGGridView object must adopt the IGGridViewDelegate protocol. Optional methods of the protocol allow the delegate to manage selection, configuration of heights and widths, and other various actions such as displaying custom views.
 
 */
@protocol IGGridViewDelegate <NSObject, UIScrollViewDelegate>

@optional

///---------------------------------------------------------------------------------------
/// @name Configuration and Initialization
///---------------------------------------------------------------------------------------

/** Asks the delegate for the height of a particular row.
 
 This will be called for every row whenever the grid view is reloaded. 
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The height for the requested row.
 */
-(CGFloat)gridView:(IGGridView*)gridView heightForRowAtPath:(IGRowPath*)path;


/** Tells the delegate that a cell is about to be displayed in the viewport.
 
 This will be called every time a cell that was previously out of view has come back into view.
 
 @param gridView The grid view providing the information.
 @param cell The IGGridViewCell coming into view.
 @param path The path of the cell coming into view.
 */
-(void)gridView:(IGGridView*)gridView willDisplayCell:(IGGridViewCell*)cell forPath:(IGCellPath*)path;

/** Tells the delegate that a cell is about to be created for the first time.
 
 This will be called only the first time a cell is being created.
 
 @param gridView The grid view providing the information.
 @param cell The IGGridViewCell being initialized.
 */
-(void)gridView:(IGGridView*)gridView initializeCell:(IGGridViewCell*)cell;

///---------------------------------------------------------------------------------------
/// @name Sections
///---------------------------------------------------------------------------------------

/** Asks the delegate for a custom view for a section
 
 This will be called for every section whenever the grid view is reloaded. The view provided will be displayed in a fixed column that will be displayed whenever that section is currently in view.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return The custom view that will be displayed or nil if nothing should be displayed for a particular section.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForSectionColumn:(NSInteger)section;

/** Asks the delegate for a custom view for a section header
 
 This will be called for every section whenever the grid view is reloaded. The view provided will be displayed in the section's header.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return The custom view that will be displayed or nil if nothing should be displayed for a particular section.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForSectionHeader:(NSInteger)section;

/** Asks the delegate for a custom view for a section footer
 
 This will be called for every section whenever the grid view is reloaded. The view provided will be displayed in the section's footer.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return The custom view that will be displayed or nil if nothing should be displayed for a particular section.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForFooterInSection:(NSInteger)section;

/** Asks the delegate for the height of the header of a section
 
 This will be called for every section whenever the grid view is reloaded. 
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return The height of the header or zero if the header should not be displayed.
 */
-(CGFloat)gridView:(IGGridView*)gridView heightForSectionHeader:(NSInteger)section;

/** Asks the delegate for the height of the footer of a section
 
 This will be called for every section whenever the grid view is reloaded. 
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return The height of the footer or zero if the footer should not be displayed.
 */
-(CGFloat)gridView:(IGGridView*)gridView heightForFooterInSection:(NSInteger)section;
    
/** Asks the delegate if the header should be displayed for a particular section.
 
 This will be called for every section whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return YES if the header should be displayed.
 */
-(BOOL)gridView:(IGGridView*)gridView displayHeaderForSection:(NSInteger)section;

/** Asks the delegate if the footer should be displayed for a particular section.
 
 This will be called for every section whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param section The index of the section.
 @return YES if the footer should be displayed.
 */
-(BOOL)gridView:(IGGridView*)gridView displayFooterForSection:(NSInteger)section;

///---------------------------------------------------------------------------------------
/// @name Rows
///---------------------------------------------------------------------------------------

/** Asks the delegate for a UIView that will be displayed as the separator of a row.
 
 This will be called for every row that has just become visible.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The view of the separator that should be displayed.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForRowSeparatorAtPath:(IGRowPath*)path;

/** Asks the delegate for a UIView that will be displayed as the background of a row.
 
 This will be called for every row that has just become visible.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The view of the background that should be displayed.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForRowBackgroundAtPath:(IGRowPath*)path;


/** Asks the delegate for a UIView that will be displayed under a row, when the swipeRowAction property of the IGGridView is set to IGGridViewSwipeRowActionSlideRowRight or IGGridViewSwipeRowActionManualSlideRight.

 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The view that should be displayed.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForSlideRowRight:(IGRowPath*)path;

/** Asks the delegate for a UIView that will be displayed under a row, when the swipeRowAction property of the IGGridView is set to IGGridViewSwipeRowActionSlideRowLeft or IGGridViewSwipeRowActionManualSlideLeft.
 
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The view that should be displayed.
 */
-(UIView*)gridView:(IGGridView*)gridView viewForSlideRowLeft:(IGRowPath*)path;


/** Asks the delegate for a particular row, to see if it should be allowed to slide left.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The YES if the row can slide left.
 */
-(BOOL)gridView:(IGGridView*)gridView canSlideRowLeft:(IGRowPath*)path;


/** Asks the delegate for a particular row, to see if it should be allowed to slide right.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @return The YES if the row can slide right.
 */
-(BOOL)gridView:(IGGridView*)gridView canSlideRowRight:(IGRowPath*)path;


/** Asks the delegate for a UIView that will be displayed under a row, when the swipeRowAction property of the IGGridView is set to IGGridViewSwipeRowActionPercentSlideLeft.
 
 This method will be invoked constantly while sliding a row. Even after it's released, so that you can properly update the content that is being displayed while it's sliding.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row has been slid from it's original location relative to the width of the grid. 
 @param finishPercent The percentage the row was at when the user finished sliding the row. The value of this parameter is NAN while the row is still being slid by the user. 
 @return The view that should be displayed.
 */
-(UIView*)gridView:(IGGridView *)gridView viewForSlideRowLeft:(IGRowPath*)path atPercentage:(CGFloat)percent withFinishingPercentange:(CGFloat)finishPercent;

/** Asks the delegate for a UIView that will be displayed under a row, when the swipeRowAction property of the IGGridView is set to IGGridViewSwipeRowActionPercentSlideRight.
 
 This method will be invoked constantly while sliding a row. Even after it's released, so that you can properly update the content that is being displayed while it's sliding.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row has been slid from it's original location relative to the width of the grid.
 @param finishPercent The percentage the row was at when the user finished sliding the row. The value of this parameter is NAN while the row is still being slid by the user.
 @return The view that should be displayed.
 */
-(UIView*)gridView:(IGGridView *)gridView viewForSlideRowRight:(IGRowPath*)path atPercentage:(CGFloat)percent withFinishingPercentange:(CGFloat)finishPercent;

/** Asks the delegate whether it should cancel the slide or accept it. 
 
 This method will be invoked immediately after the user lifts their finger from the row. If not implemented, the gridView assumes that it should always accept the slide.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row has been slid from it's original location relative to the width of the grid.
 @return Whether the action should cancel (slide back to position) or continue (slide completely out of view).
 */
-(BOOL)gridView:(IGGridView *)gridView acceptSlideRowLeftForRow:(IGRowPath*)path atPercentage:(CGFloat)percent;

/** Asks the delegate whether it should cancel the slide or accept it.
 
 This method will be invoked immediately after the user lifts their finger from the row. If not implemented, the gridView assumes that it should always accept the slide.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row has been slid from it's original location relative to the width of the grid.
 @return Whether the action should cancel (slide back to position) or continue (slide completely out of view).
 */
-(BOOL)gridView:(IGGridView *)gridView acceptSlideRowRightForRow:(IGRowPath*)path atPercentage:(CGFloat)percent;

/** Notifies the delegate that the row has finished sliding out of view.
 
 This method will only be invoked if the row was accepted, and slid completely of view. 
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row was released at.
 */
-(void)gridView:(IGGridView *)gridView slideRowLeftFinished:(IGRowPath*)path atPercentage:(CGFloat)percent;

/** Notifies the delegate that the row has finished sliding out of view.
 
 This method will only be invoked if the row was accepted, and slid completely of view.
 
 @param gridView The grid view requesting the information.
 @param path The IGRowPath of the row.
 @param percent The percentage the row was released at.
 */
-(void)gridView:(IGGridView *)gridView slideRowRightFinished:(IGRowPath*)path atPercentage:(CGFloat)percent;

///---------------------------------------------------------------------------------------
/// @name Managing Selection
///---------------------------------------------------------------------------------------

/** Tells the delegate that a row in the grid view is about to be selected.
 
To cancel the selection return nil.
 
 @param gridView The grid view providing the information.
 @param path The IGRowPath of the row.
 @return The path of the row that should be selected or nil if no row should be selected.
 */
-(IGRowPath*)gridView:(IGGridView*)gridView willSelectRowAtPath:(IGRowPath*)path;

/** Tells the delegate that a row in the grid view was selected.

 @param gridView The grid view providing the information.
 @param path The IGRowPath of the row.
 */
-(void)gridView:(IGGridView*)gridView didSelectRowAtPath:(IGRowPath*)path;

/** Tells the delegate that a cell in the grid view is about to be selected.
 
 To cancel the selection return nil.
 
 @param gridView The grid view providing the information.
 @param path The IGCellPath of the cell.
 @return The path of the cell that should be selected or nil if no cell should be selected.
 */
-(IGCellPath*)gridView:(IGGridView*)gridView willSelectCellAtPath:(IGCellPath*)path;

/** Tells the delegate that a cell in the grid view was selected.
 
 @param gridView The grid view providing the information.
 @param path The IGCellPath of the cell.
 */
-(void)gridView:(IGGridView*)gridView didSelectCellAtPath:(IGCellPath*)path;


/** Tells the delegate that a row in the grid view is about to be deselected.
 
 To cancel the deselection return nil.
 
 @param gridView The grid view providing the information.
 @param path The IGRowPath of the row.
 @return The path of the row that should be deselected or nil if the row should stay selected.
 */
-(IGRowPath*)gridView:(IGGridView*)gridView willDeselectRowAtPath:(IGRowPath*)path;

/** Tells the delegate that a row in the grid view was deselected.
 
 @param gridView The grid view providing the information.
 @param path The IGRowPath of the row.
 */
-(void)gridView:(IGGridView*)gridView didDeselectRowAtPath:(IGRowPath*)path;

/** Tells the delegate that a cell in the grid view is about to be deselected.
 
 To cancel the deselection return nil.
 
 @param gridView The grid view providing the information.
 @param path The IGCellPath of the cell.
 @return The path of the cell that should be deselected or nil if the cell should stay selected.
 */
-(IGCellPath*)gridView:(IGGridView*)gridView willDeselectCellAtPath:(IGCellPath*)path;

/** Tells the delegate that a cell in the grid view was deselected.
 
 @param gridView The grid view providing the information.
 @param path The IGCellPath of the cell.
 */
-(void)gridView:(IGGridView*)gridView didDeselectCellAtPath:(IGCellPath*)path;

///---------------------------------------------------------------------------------------
/// @name Context Menu
///---------------------------------------------------------------------------------------

/** Asks the delegate if a context menu should be displayed for the cell
 
 @param gridView The grid view requesting the information.
 @param path The IGCellPath of the cell.
 @return YES if the context menu should be displayed.
 */
-(BOOL)gridView:(IGGridView*)gridView shouldShowMenuForCellAtPath:(IGCellPath*)path;

/** Asks the delegate if a particular command should appear in the context menu.
 
 This method will be invoked for every possible context menu selector. If you added custom menu items, those selectors will be provided as well.
 
 @param gridView The grid view requesting the information.
 @param action The selector for a menu item.
 @param path The IGCellPath of the cell.
 @param sender The object calling this method. For the editing menu commands this is the shared UIApplication object.
 @return YES if the specified selector is supported.
 */
-(BOOL)gridView:(IGGridView*)gridView canPerformAction:(SEL)action forCellAtPath:(IGCellPath*)path withSender:(id)sender;

/** Tells the delegate that a context menu item was pressed.
 
 @param gridView The grid view providing the information.
 @param action The selector for a menu item.
 @param path The IGCellPath of the cell.
 @param sender The object calling this method. For the editing menu commands this is the shared UIApplication object.
 */
-(void)gridView:(IGGridView*)gridView performAction:(SEL)action forCellAtPath:(IGCellPath*)path withSender:(id)sender;

///---------------------------------------------------------------------------------------
/// @name Pulldown Row
///---------------------------------------------------------------------------------------

/** Tells the delegate that the pull down row has been pulled down and released and that new information should be retreived
 
 When the information is retrieved the finishedUpdating selector of the grid view should be invoked.
 
 @param gridView The grid view providing the information.
 */
-(void)updateRequestedInGridView:(IGGridView*)gridView;

///---------------------------------------------------------------------------------------
/// @name Editing Table Rows
///---------------------------------------------------------------------------------------

/** Changes the default title of the delete-confirmation button.
 
By default, the delete-confirmation button, which appears on the right side of the cell, has the title of “Delete”. The grid view displays this button when the user attempts to delete a row by swiping the row. You can implement this method to return an alternative title, which should be localized.
 
 @param gridView The grid view requesting the information.
 @param path A IGRowPath object locating the row in its section.
 @return A localized string to used as the title of the delete-confirmation button.
 */
- (NSString *)gridView:(IGGridView *)gridView titleForDeleteConfirmationButtonForRowAtPath:(IGRowPath*)path;

/** Tells the delegate that the table view is about to display the delete button on a row.
 
  A swipe motion across a row does not cause the display of a Delete button unless the grid view's data source implements the gridView:deleteRowAtPath: method.
 
 @param gridView The grid view providing the information.
 @param path A IGRowPath object locating the row in its section.
 */
- (void)gridView:(IGGridView *)gridView willBeginDeletingRowAtPath:(IGRowPath *)path;

/** Tells the delegate that the grid view is no longer displaying the delete button.

@param gridView The grid view providing the information.
@param path A IGRowPath object locating the row in its section.
*/
- (void)gridView:(IGGridView *)gridView didEndDeletingRowAtPath:(IGRowPath *)path;

///---------------------------------------------------------------------------------------
/// @name Cell, Row, and Column Reordering
///---------------------------------------------------------------------------------------

/** Tells the delegate that a row is about to be moved to a new position.
 
 This method will be invoked constantly while dragging a row.
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGRowPath of the row being dragged.
 @param proposedPath The new path of the row
 @return The proposed path. If the specified proposed path is invaild, returns a new valid path.
 */
-(IGRowPath*)gridView:(IGGridView*)gridView targetPathForMoveFromRowAtPath:(IGRowPath*)sourcePath toProposedPath:(IGRowPath*)proposedPath;

/** Tells the delegate a row was moved in the UI
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGRowPath of the row being moved
 @param destinationPath The IGRowPath where the source row was moved to.
 */
-(void)gridView:(IGGridView*)gridView rowMovedAtPath:(IGRowPath*)sourcePath toPath:(IGRowPath*)destinationPath;

/** Tells the delegate that a cell is about to be moved to a new position.
 
 This method will be invoked constantly while dragging a cell.
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGCellPath of the cell being dragged.
 @param proposedPath The new path of the cell
 @return The proposed path. If the specified proposed path is invaild, returns a new valid path.
 */
-(IGCellPath*)gridView:(IGGridView*)gridView targetPathForMoveFromCellAtPath:(IGCellPath*)sourcePath toProposedPath:(IGCellPath*)proposedPath;


/** Tells the delegate  a cell was moved in the UI.
 
 @param gridView The grid view providing the information.
 @param sourcePath The IGCellPath of the cell being moved
 @param destinationPath The IGCellPath where the source cell was moved to.
 */
-(void)gridView:(IGGridView *)gridView cellMovedAtPath:(IGCellPath*) sourcePath toPath:(IGCellPath*)destinationPath;

/** Tells the delegate that a column is about to be moved to a new position.
 
 This method will be invoked constantly while dragging a column.
 
 @param gridView The grid view providing the information.
 @param sourceIndex The index of the column being dragged.
 @param proposedIndex The new index of the column
 @return The proposed index. If the specified proposed index is invaild, returns a new valid index.
 */
-(NSInteger)gridView:(IGGridView*)gridView targetPathForMoveFromColumnAtIndex:(NSInteger)sourceIndex toProposedIndex:(NSInteger)proposedIndex;

/** Tells the delegate a column was moved in the UI.
 
 @param gridView The grid view providing the information.
 @param sourceIndex The index of the column being moved
 @param destinationIndex The index where the source column was moved to.
 */
-(void)gridView:(IGGridView *)gridView columnMovedAtIndex:(NSInteger) sourceIndex toIndex:(NSInteger)destinationIndex;



///---------------------------------------------------------------------------------------
/// @name Column Resizing
///---------------------------------------------------------------------------------------

/** Asks the delegate for the width of a particular column.
 
 This will be called for every column whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column
 @return The IGColumnWidth of the requested column.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForColumnAtIndex:(NSInteger)column;


/** Tells the delegate to resize a column.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;

/** Tells the delegate to resize a column fixed to the left of the grid view.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeFixedLeftColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;

/** Tells the delegate to resize a column fixed to the right of the grid view.
 
 @param gridView The grid view providing the information.
 @param index The index of the column being resized
 @param newWidth The new width of the column
 */
-(void)gridView:(IGGridView *)gridView resizeFixedRightColumnAtIndex:(NSInteger) index withWidth:(IGColumnWidth*)newWidth;



///---------------------------------------------------------------------------------------
/// @name Paging
///---------------------------------------------------------------------------------------
/** Tells the delegate that the current page has changed.
 
 This method will only be invoked when the style of the grid view is IGGridViewStyleSingleCellPaging. And will only be invoked when the cell has stopped moving at it's designated position.
 
 @param gridView The grid view providing the information.
 @param path The IGCellPath of the cell.
 */
-(void)gridView:(IGGridView*)gridView pageChanged:(IGCellPath*)path;

///---------------------------------------------------------------------------------------
/// @name Fixed Columns
///---------------------------------------------------------------------------------------

/** Asks the delegate for the width of a particular column pinned to the left of the grid view.
 
 This will be called for every column whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column
 @return The IGColumnWidth of the requested column.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForFixedLeftColumnAtIndex:(NSInteger)column;

/** Asks the delegate for the width of a particular column pinned to the right of the grid view.
 
 This will be called for every column whenever the grid view is reloaded.
 
 @param gridView The grid view requesting the information.
 @param column The index of the column
 @return The IGColumnWidth of the requested column.
 */
-(IGColumnWidth*)gridView:(IGGridView*)gridView widthForFixedRightColumnAtIndex:(NSInteger)column;

/** Tells the delegate that a cell is about to be displayed in the viewport.
 
 This will be called every time a cell that was previously out of view has come back into view.
 
 @param gridView The grid view providing the information.
 @param cell The IGGridViewCell coming into view.
 @param path The path of the cell coming into view.
 */
-(void)gridView:(IGGridView*)gridView willDisplayFixedLeftCell:(IGGridViewCell*)cell forPath:(IGCellPath*)path;

/** Tells the delegate that a cell is about to be displayed in the viewport.
 
 This will be called every time a cell that was previously out of view has come back into view.
 
 @param gridView The grid view providing the information.
 @param cell The IGGridViewCell coming into view.
 @param path The path of the cell coming into view.
 */
-(void)gridView:(IGGridView*)gridView willDisplayFixedRightCell:(IGGridViewCell*)cell forPath:(IGCellPath*)path;


@end

/*!
 A grid view is a single or multiple column view, which allows users to scroll through rows and cells both vertically and horizontally. The cells comprising the individual items of the grid are IGGridViewCellBase objects. These objects represent a specific column and row that users can insert, delete, and reorder, both on the invdiual cell level or row level. 
 
 A grid view is made up of zero or more sections, each with its own rows. Sections are identified by their index number within the grid view, rows are identified by their index number within a section and columns are identified by their index within a row. Any section can be optionally be preceded by a section header, and optionally followed by a section footer. 
 
 Grid views can have one of two styles, IGGridViewStyleDefault and IGGridViewStyleSingleCellPaging. When you create an IGGridView instance you must specify a grid style, and this style cannot be changed. If no style is chosen, the default style will be used. In the default style, cells and rows size to their column widths and row heights, and sections can display headers and footers. The single cell paging style, will only display a single cell sized to the size of the grid's viewport. This type of style is useful for applications that would want to display one item at a time, such as an image viewer or a document reader.
 
 Many methods of the IGGridView take IGRowPath or IGCellPath objects as parameters and return values. You can use the pathForRow:inSection: static method to create an IGRowPath and the the cellPathForRow:inSection:inColumn: static method to create an IGCellPath.
 
 A IGGridView object must have an object that acts as a data source and an object that acts as a delegate; typically these objects are the application delegate. The data source must adopt the IGGridViewDataSource protocol and the delegate must adopt the IGGridViewDelegate protocol. The data source provides information that the grid view needs to construct tables and manages the data model when rows or cells of a table are inserted, deleted, or reordered. The delegate provides the cells used by the grid and performs other tasks, such as selection. To shorten development time you can take advantage of the IGGridViewDataSourceHelper object which simplifies the creation of cells and data management.  There are a few different implementations of the data source helpers such as IGGridViewSingleRowSingleFieldDataSourceHelper and IGGridViewSingleFieldMultiColumnDataSourceHelper which offer different ways to display your linear data, such as treaing every row as a column. 
 
 IGGridView caches cells only for visible rows, but caches row, header, and footer heights for the entire grid. You can create custom cells by deriving from IGGridViewCellBase. 
 
 IGGridView calls reloadData only when you create a new instance of the IGGridView or when you assign a new data source. Reloading the grid view clears current state, including the current selection. If you would like to keep state, but refresh the current data that is being displayed in the grid view, you can call updateData.
 
 To display a shortcut bar in the grid view, your datasource must implement the following methods:sectionIndexTitlesForGridView:
 gridView:sectionForSectionIndexTitle:atIndex:. You can then customize the appearance of the shortcut bar using the following properties of the grid view: shortcutBarColumnBackgroundView, shortcutBarColumnWidth and shorcutBarColor
 
 To implement a pull down to refresh mechanism similar to apps such as Facebook, your delegate must implement the updateRequestedInGridView: method. When you're done with refreshing you can then invoke the finishedUpdating method on the grid view. To control the height of the pull down you can set the pullDownRowHeight property of the grid view. To customize the content displayed in the pull down view you can implement the pullDownCellForGridView: method on your datasource.

*/
@interface IGGridView : UIScrollView <NSCoding>
{
    
@private
    
    IGColumnWidth* _columnWidth;
    IGGridViewStyle _style;
    UIView* _backgroundView;
    IGCellPath* _contextMenuPath;
    SEL _currentActionMenuItemSelector;
    
    UIColor* _rowSeparatorColor;
    UIColor* _columnSeparatorColor;
    CGFloat _rowSeparatorHeight;
    BOOL _rowReordering;

}

///---------------------------------------------------------------------------------------
/// @name Initializing a IGGridView Object
///---------------------------------------------------------------------------------------

/** Initializes and returns a grid view object having the given frame and style
 
 You must specify the style of a grid view when you create it and you cannot thereafter modify the style. If you initialize the grid view with another method, the IGGridViewStyleDefault is used.
  
 @param frame A rectangle specifying the initial location and size of the grid view in it's superview's coordinates.
 @param style A constant that specifies the style of the grid view. 
 @return Returns an initialized IGGridView object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithFrame:(CGRect)frame style:(IGGridViewStyle)style NS_DESIGNATED_INITIALIZER;

///---------------------------------------------------------------------------------------
/// @name Configuring a Grid View
///---------------------------------------------------------------------------------------

/** Returns a reusable grid view cell object located by its identifier
 
 For performance reasons, a grid view's data source should generally reuse IGGridViewCellBase objects when it assigns cells to rows in it's gridView:cellAt: method. A grid view maintains a queue or list of IGGridViewCellBase objects that the grid view's delegate has marked for reuse. It marks a cell for reuse by assigning it a reuse identifier when it creates it (that is, in the initWithReuseIdentifier: method of IGGridViewCellBase). The data source can access specific template cell objects in this queue by invoking this method. You can access a cell's reuse identifier through it's reuseIdentifier property, which is defined by IGGridViewCellBase.
 
 @param identifier A string identifying the cell object to be reused. By default, a reusable cell's identifier is it's class name, but you can change it to any arbitrary value.
 @return A IGGridViewCellBase object with the associated identifier or nil if no such object exists in the reusable-cell queue.
 */
-(id) dequeueReusableCellWithIdentifier:(NSString *)identifier; 

/** Registers a class for use in creating new grid cells.
 
 Prior to dequeueing any cells, call this method to tell the grid view how to create new cells. If a cell of the specified type is not currently in a reuse queue, the grid view uses the provided information to create a new cell object automatically.
 
 If you previously registered a class file with the same reuse identifier, the class you specify in the cellClass parameter replaces the old entry. You may specify nil for cellClass if you want to unregister the class from the specified reuse identifier.
 
@param cellClass The class of a cell that you want to use in the grid.
@param identifier The reuse identifier for the cell. This parameter must not be nil and must not be an empty string.
 */
-(void)registerClass:(Class)cellClass forCellReuseIdentifier:(NSString*)identifier;

/** Returns the style of the receiver. (read-only)
 
 Two possible options: 
    IGGridViewStyleDefault - Used for standard cell row layouts.
    IGGridViewStyleSingleCellPaging - A single cell will be sized to the viewport of the grid view. 
 */
@property(nonatomic, readonly) IGGridViewStyle          style;

/** Sets the height of the header in the grid view.
 
 The header will only apper if the style of the grid view is set to IGGridViewStyleDefault. 
 To remove the header from the grid view set the height of the header to zero.
 The default value is 50.
 */
@property(nonatomic, assign)   CGFloat                  headerHeight;

/** Sets the UIColor of the background of header cells. 
 
 The default is black. This value is only used when the delegate's gridView:headerCellAt: method is not implemented.
 */
@property(nonatomic, retain)   UIColor*                 headerBackgroundColor;

/** Sets the UIColor of the text of header cells. 
 
 The default is white. This value is only used when the delegate's gridView:headerCellAt: method is not implemented.
 */
@property(nonatomic, retain)   UIColor*                 headerTextColor;

/** Sets the UIFont of the text of header cells.
 
 The default is nil. This value is only used when the delegate's gridView:headerCellAt: method is not implemented.
 */
@property(nonatomic, retain, nullable)   UIFont*                 headerFont;

/** Sets whether the grid view will be allowed to be scrolled outside it's bounds horizontally. 
 
 When a grid view's total column width is wider than the viewport of the grid view the user can be allowed to scroll the columns beyond their bounds. The default value is NO which means that even though the user tries to scroll outside the bounds of the columns, they'll only move to the extent of the viewport.
 */
@property(nonatomic, assign)   BOOL                     allowHorizontalBounce;

/** The background view of the grid view.
 
A grid view's background view is automatically resized to match the size of the grid view. The view is placed as a subview of the grid view behind all cells, header views and footer views.
 */
@property(nonatomic, retain, nullable)   UIView*                  backgroundView;

/** Sets UIEdgeInset for the content of all IGGridViewCell objects in the grid view.
 
 Use this property to set the inset of the content of a cell. This property should not be set when the style of the grid view is set to IGGridViewStyleSingleCellPaging. The default is (5, 5, 10, 10). 
 */
@property(nonatomic, assign)   UIEdgeInsets             cellContentInset;

/** Sets whether empty rows should be appended to the end of the grid view.
 
 When set to YES the grid view will append empty rows to itself. If the delegate's gridView:heightForRowAtPath: method is implemented the grid view will not display any empty rows, regardless of the value of this property. The default is YES.
 */
@property(nonatomic, assign)   BOOL                     emptyRows;


/** Sets whether the grid can continuously be scrolled without ever hitting an end, as the columns and rows will repeated.

*/
@property(nonatomic, assign)IGGridViewInfiniteScrolling infiniteScrolling;

/** Sets the IGGridViewThemeDefinition that will control the styling of particular elements of the IGGridView. 
 
 When setting this property, you should call the grid's updateData method afterwards to ensure all of the stylable areas are refreshed.
 */
@property(nonatomic, assign, nullable)id<IGGridViewThemeDefinition> theme;

/** Sets the IGGridViewStringsDefinition that will control the default text values of particular elements of the IGGridView.
 
 When setting this property, you should call the grid's updateData method afterwards to ensure all elements are refreshed..
 */
@property(nonatomic, assign, nullable)id<IGGridViewStringsDefinition> strings;

/** Helper property, for when you do not have many cells in your viewport, and you're doing custom cell positioning, where cells can overlap. You can set this property to true to ensure that
 z order is always kept.
 */
@property(nonatomic, assign)BOOL alwaysEnsureCellZorder;


///---------------------------------------------------------------------------------------
/// @name Section Configuration
///---------------------------------------------------------------------------------------

/** Sets the height of the header for all sections in the grid view. 
 
 This value is only used if the delegate's gridView:heightForSectionHeader: is not implemented.
 */
@property(nonatomic, assign)   CGFloat                  sectionHeaderHeight;

/** Sets the height of the footer for all sections in the grid view. 
 
 This value is only used if the delegate's gridView:heightForFooterInSection: is not implemented.
 */
@property(nonatomic, assign)   CGFloat                  sectionFooterHeight;

/** Sets the width of custom section content. 
 
 When the delegate's gridView:viewForSectionColumn: is implemented, another column is exposed to display the specified view's content. This property allows the developer to control the width of this fixed column.
 */
@property(nonatomic, assign)   CGFloat                  sectionColumnWidth;

/** Sets the background view of the fixed column used for displaying a section's custom content.
 
 When the delegate's gridView:viewForSectionColumn: is implemented, this specified view is used as a background for the column used to display the specified content. This background view is sized to the available viewport determined by the frame of the grid view and the sectionColumnWidth 
 */
@property(nonatomic, retain)   UIView*                  sectionColumnBackgroundView;

/** Sets the color of the content area of the Section column.
 
 The content area is the area in which the views specified in viewForSectionColumn: will be displayed. The default value is clear;
 */
@property(nonatomic, retain)   UIColor*                  sectionColumnContentColor;

///---------------------------------------------------------------------------------------
/// @name Row Configuration
///---------------------------------------------------------------------------------------

/** Sets the height of all rows in the grid view.
 
If the delegate's gridView:heightForRowAtPath: method is implemented this property will not be used.
 */
@property(nonatomic, assign)   CGFloat                  rowHeight;

/** Sets the spacing that should be appended to each row. 
 
 Use this property if you need to apply additional spacing between rows. 
 */
@property(nonatomic, assign)   CGFloat                  rowSpacing;

/** Sets the height of the separator for each row. 
 
 To remove row separators set the height to zero. The default value is 2.
 */
@property(nonatomic, assign)   CGFloat                  rowSeparatorHeight;

/** Sets the UIColor of the row separator. 
 
 The default is gray. This value is only used when the delegate's gridView:viewForRowSeparatorAtPath: method is not implemented.
 */
@property(nonatomic, retain)   UIColor*                 rowSeparatorColor;

/** Sets the UIColor for the background of the row.
 
 The default is clear.
 */
@property(nonatomic, retain)   UIColor*                 rowBackgroundColor;

///---------------------------------------------------------------------------------------
/// @name Column Configuration
///---------------------------------------------------------------------------------------

/** Sets IGColumnWidth for every column in the grid view.
 
To set the width of individual columns use the delegate's gridView:widthForColumnAtIndex: method.
 */
@property(nonatomic, retain, nullable)   IGColumnWidth*           columnWidth;

/** Sets the spacing that should be appended to the right of each cell. 
 
 Use this property if you need to apply additional spacing between columns. 
 */
@property(nonatomic, assign)   CGFloat                  columnSpacing;


/** Sets the IGGridViewColumnResizeAction that determines how a column can be resized in the UI
 
 IGGridViewColumnResizeActionNone - No UI interactions for resizing columns
 IGGridViewColumnResizeActionPinch - Pinch gestures on a column will resize it.
 IGGridViewColumnResizeActionAdorner - Tap a column header, and an adorner will appear, so that you can resze the column. Headers must be visible.
 
 */
@property(nonatomic, assign)IGGridViewColumnResizeAction columnResizing;

/** Sets the color of the adorner used for resizing a column when the columnResizing property is set to IGGridViewColumnResizeActionAdorner.
 */
@property(nonatomic, retain)UIColor* columnResizingAdornerColor;


/** Returns whether the Column Resizing Adorder is currently being displayed for a column 
 */
@property(nonatomic, readonly)BOOL isResizngAdornerVisible;


/** Asks the grid for the actual display width of a particular column
 
 @param column The index of the column whose width you're requesting
 @param location The location of the column, i.e. if it's fixed left, fixed right, or not fixed.
 @return The point size of the column's width.
 */
-(CGFloat)resolveActualWidthOfColumn:(NSInteger)column location:(IGGridViewFixedColumnDirection)location;

///---------------------------------------------------------------------------------------
/// @name Managing Selections
///---------------------------------------------------------------------------------------

/** A Boolean value that determines whether users can select more than one row or cell. 
 
When this property is YES rows or cells are selected until that particular row or cell is pressed again. 
 */
@property(nonatomic, assign)   BOOL allowsMultipleSelection;

/** Sets whether selection should be for rows, cells or if there should be no selection at all. 
 
 There are three valid values
    IGGridViewSelectionTypeRow - only rows will be selected. 
    IGGridViewSelectionTypeCell - only cells will be selected.
    IGGridViewSelectionTypeNone - no selection will occur.
 */
@property(nonatomic, assign)   IGGridViewSelectionType selectionType;

/** The IGCellPath of the currently selected cell or nil.
 
 If no cell is selected nil is returned. If more than one cell is selected, the top most selected cell in the grid view is returned. 
 */
@property (NS_NONATOMIC_IOSONLY, readonly, strong) IGCellPath *pathForSelectedCell;

/** The IGRowPath of the currently selected row or nil.
 
 If no row is selected nil is returned. If more than one row is selected, the top most selected row in the grid view is returned. 
 */
@property (NS_NONATOMIC_IOSONLY, readonly, strong) IGRowPath *pathForSelectedRow;

/** An array of selected IGCellPath objects.
 
 If no cell is selected an empty array is returned.
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<__kindof IGCellPath *> *pathsForSelectedCells;

/** An array of selected IGRowPath objects.
 
 If no row is selected an empty array is returned.
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<__kindof IGRowPath *> *pathsForSelectedRows;

/** Selects the cell at the specified path and optionally scrolls that cell into view.
 
 Calling this method does not cause the delegate to receive a gridView:willSelectCellAtPath: or 
 gridView:didSelectCellAtPath: message.
 
 The following positions can be used for scrolling the cell into view:
 
        IGGridViewScrollPositionNone,
        IGGridViewScrollPositionNoneLeft,
        IGGridViewScrollPositionNoneRight,
        IGGridViewScrollPositionNoneMiddle,
        IGGridViewScrollPositionTopLeft,
        IGGridViewScrollPositionTopMiddle,
        IGGridViewScrollPositionTopRight,
        IGGridViewScrollPositionTopNone,
        IGGridViewScrollPositionMiddleLeft,
        IGGridViewScrollPositionMiddle,
        IGGridViewScrollPositionMiddleRight,
        IGGridViewScrollPositionMiddleNone,
        IGGridViewScrollPositionBottomLeft, 
        IGGridViewScrollPositionBottomMiddle,
        IGGridViewScrollPositionBottomRight,
        IGGridViewScrollPositionBottomNone
 
  Passing IGGridViewScrollPositionNone will result in no scrolling, rather than the minimum scrolling described for that constant. To scroll to the newly selected cell with minimum scrolling, select the cell using this method with IGGridViewScrollPositionNone, then call scrollToCellAtCellPath:atScrollPosition:animated: with IGGridViewScrollPositionNone.
 
 @param path The IGCellPath of the cell that should be selected
 @param animated Whether the cell should be animated into it's selected state and any movement in position (YES) or happen immediately(NO). 
 @param scrollPosition The position in which the selected cell should be scrolled to in the grid view. 
 */
-(void)selectCellAtPath:(IGCellPath*)path animated:(BOOL)animated scrollPosition:(IGGridViewScrollPosition)scrollPosition;

/** Selects all of the cells at the specified paths.
 
 Calling this method does not cause the delegate to receive a gridView:willSelectCellAtPath: or
 gridView:didSelectCellAtPath: message.
 
 @param paths An array of IGCellPaths of the cells that should be selected
 @param animated Whether the cells should be animated into their selected state;
*/
-(void)selectCellsAtPaths:(NSArray<__kindof IGCellPath*>*)paths animated:(BOOL)animated;

/** Selects the row at the specified path and optionally scrolls that row into view.
 
 Calling this method does not cause the delegate to receive a gridView:willSelectRowAtPath: or 
 gridView:didSelectRowAtPath: message.
 
 The following positions can be used for scrolling the row into view:
 
        IGGridViewScrollPositionNone,
        IGGridViewScrollPositionNoneLeft,
        IGGridViewScrollPositionNoneRight,
        IGGridViewScrollPositionNoneMiddle,
        IGGridViewScrollPositionTopLeft,
        IGGridViewScrollPositionTopMiddle,
        IGGridViewScrollPositionTopRight,
        IGGridViewScrollPositionTopNone,
        IGGridViewScrollPositionMiddleLeft,
        IGGridViewScrollPositionMiddle,
        IGGridViewScrollPositionMiddleRight,
        IGGridViewScrollPositionMiddleNone,
        IGGridViewScrollPositionBottomLeft, 
        IGGridViewScrollPositionBottomMiddle,
        IGGridViewScrollPositionBottomRight,
        IGGridViewScrollPositionBottomNone
 
 Passing IGGridViewScrollPositionNone will result in no scrolling, rather than the minimum scrolling described for that constant. To scroll to the newly selected row with minimum scrolling, select the row using this method with IGGridViewScrollPositionNone, then call scrollToCellAtCellPath:atScrollPosition:animated: with IGGridViewScrollPositionNone.
 
 @param path The IGRowPath of the row that should be selected
 @param animated Whether the row should be animated into it's selected state(YES)  and any movement in position or happen immediately(NO). 
 @param scrollPosition The position in which the selected row should be scrolled to in the grid view. 
 */
-(void)selectRowAtPath:(IGRowPath*)path animated:(BOOL)animated scrollPosition:(IGGridViewScrollPosition)scrollPosition;


/** Selects all of the rows at the specified paths.
 
 Calling this method does not cause the delegate to receive a gridView:willSelectRowAtPath: or
 gridView:didSelectRowAtPath: message.
 
 @param paths An array of IGRowPaths of the rows that should be selected
 @param animated Whether the rows should be animated into their selected state;
 */
-(void)selectRowsAtPaths:(NSArray<__kindof IGRowPath*>*)paths animated:(BOOL)animated;

/** Deselects the cell at the specified path.
 
 Calling this method does not cause the delegate to receive a gridView:willDeselectCellAtPath: or 
 gridView:didDeselectCellAtPath: message.
 
 @param path The IGCellPath of the cell that should be deselected
 @param animated Whether the cell should be animated into it's deselected state (YES) or happen immediately(NO). 
 */
-(void)deselectCellAtPath:(IGCellPath*)path animated:(BOOL)animated;

/** Deselects the row at the specified path.
 
 Calling this method does not cause the delegate to receive a gridView:willDeselectRowAtPath: or 
 gridView:didDeselectRowAtPath: message.
 
 @param path The IGRowPath of the row that should be deselected
 @param animated Whether the row should be animated into it's deselected state (YES) or happen immediately(NO). 
 */
-(void)deselectRowAtPath:(IGRowPath*)path animated:(BOOL)animated;

/** Clears all selection
 */
-(void)deselectAll;

///---------------------------------------------------------------------------------------
/// @name Accessing Cells and Rows
///---------------------------------------------------------------------------------------

/** Returns a IGGridViewCellBase for the specified path. 

 @param path The IGCellPath of the cell that should be returned.
 @return If the specified path is not in view, nil is returned. 
 */
-(id)cellAtPath:(IGCellPath*)path;

/** Returns the IGCellPath of the specified cell.
 
 @param cell A IGGridViewCellBase object.
 */
-(IGCellPath*)pathForCell:(IGGridViewCellBase*)cell;

/** Returns a IGCellPath at the specified point in the grid view.
 
 @param point A valid CGPoint within the content area of the grid view.
 @return A IGCellPath or nil if the point does not correspond with a cell.
 */
-(IGCellPath*)pathForCellAtPoint:(CGPoint)point;

/** Returns a IGRowPath at the specified point in the grid view.
 
 @param point A valid CGPoint within the content area of the grid view.
 @return A IGRowPath or nil if the point does not correspond with a row.
 */
-(IGRowPath*)pathForRowAtPoint:(CGPoint)point;

/** An array of cell paths each representing a cell enclosed by a given rectangle.

 @param frame A rectangle defining an area of the grid view in local coordinates.
 @return An array of IGCellPath objects within the bounds of the frame or an empty array if no cells fall within the frame
 */
-(NSArray*)pathsForCellsInRect:(CGRect)frame;

/** Returns the IGGridViewCell objects that are currently within the visible viewport of the grid view. 
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray *visibleCells;

/** Returns the IGRowPath objects that are currently within the visible viewport of the grid view. 
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray *pathsForVisibleRows;

///---------------------------------------------------------------------------------------
/// @name Scrolling the Grid View
///---------------------------------------------------------------------------------------

/** Scrolls a cell to the specified position in the viewable area of the grid view. 
 
 The following positions can be used for scrolling the row into view:
 
 IGGridViewScrollPositionNone,
 IGGridViewScrollPositionNoneLeft,
 IGGridViewScrollPositionNoneRight,
 IGGridViewScrollPositionNoneMiddle,
 IGGridViewScrollPositionTopLeft,
 IGGridViewScrollPositionTopMiddle,
 IGGridViewScrollPositionTopRight,
 IGGridViewScrollPositionTopNone,
 IGGridViewScrollPositionMiddleLeft,
 IGGridViewScrollPositionMiddle,
 IGGridViewScrollPositionMiddleRight,
 IGGridViewScrollPositionMiddleNone,
 IGGridViewScrollPositionBottomLeft, 
 IGGridViewScrollPositionBottomMiddle,
 IGGridViewScrollPositionBottomRight,
 IGGridViewScrollPositionBottomNone
 
 IGGridViewScrollPositionNone: The grid view scrolls the cell of interest to be fully visible with a minimum of movement. If the cell is already fully visible, no scrolling occurs. 
 
 @param path The IGCellPath of the cell that should be scrolled into view.
 @param position The position in which the cell should be scrolled to in the grid view. 
 @param animate Whether the cell should be animated into position(YES) or if it should just appear into the correct position immediately(NO)
 */
-(void) scrollToCellAtCellPath:(IGCellPath*)path atScrollPosition:(IGGridViewScrollPosition)position animated:(BOOL)animate;

///---------------------------------------------------------------------------------------
/// @name Inserting, Deleting, and Moving: Rows, Cells, and Columns
///---------------------------------------------------------------------------------------

/** A Boolean value that determines if the row reordering indicator is visible in the grid view. 
 
 To animate the indicator into view, use the setRowReordering:animated: method.
 
 The dataSource must implement the following methods in order for this property to be set to YES.
    canReorderRows:gridView; - must return YES
    gridView:canMoveRowAtPath: - if returns now, no indicator will appear for that row.
    gridView:moveRowAtPath:toPath:
 
 */
@property(nonatomic, assign)   BOOL                     rowReordering;


/** A float value that determines the width of the column used to display the row reordering indicators. 
  */
@property(nonatomic, assign)   CGFloat                  rowReorderingColumnWidth;


/** A Boolean value that determines if the row reordering indicator is visible in the grid view. 
 
 The dataSource must implement the following methods in order for this property to be set to YES.
 canReorderRows:gridView; - must return YES
 gridView:canMoveRowAtPath: - if returns now, no indicator will appear for that row.
 gridView:moveRowAtPath:toPath:
 
 @param rowReordering Yes if the row reordering indicator should be visible.
 @param animated The row reordering indicator should animated in or out of view. 
 */
-(void)setRowReordering:(BOOL)rowReordering animated:(BOOL)animated;

/** Moves the specified row in the receiver at the location identified by the new path.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param path An IGRowPath representing the row that hould be moved. 
 @param newPath An IGRowPath representing the new location of the row.
 */
-(void)moveRowAtPath:(IGRowPath *)path toPath:(IGRowPath *)newPath;

/** Inserts rows in the receiver at the location identified by an array of IGRowPath objects, with an option to animate the insertion.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param paths An array of IGRowPath objects each representing a row in the grid view. 
 @param animation A constant that specifies the kind of animation to perform.
 */
-(void)insertRowsAtPaths:(NSArray<__kindof IGRowPath*>*)paths withAnimation:(IGGridViewAnimation)animation;

/** Gets/Sets the action that will occur when swiping a row.
 
 The default is IGGridViewSwipeRowActionNone. Note, this will not have an effect if the grid view allows horizontal scrolling.
 */
@property(nonatomic, assign)   IGGridViewSwipeRowAction                     swipeRowAction;

/** Gets/Sets the width of the view that will be displayed when you swipe a row and the swipRowAction property is set to: IGGridViewSwipeRowActionSlideRowRight, IGGridViewSwipeRowActionSlideRowBoth,IGGridViewSwipeRowActionManualSlideRight or IGGridViewSwipeRowActionManualSlideBoth
 */
@property(nonatomic, assign) CGFloat slideRowRightWidth;

/** Gets/Sets the width of the view that will be displayed when you swipe a row and the swipRowAction property is set to: IGGridViewSwipeRowActionSlideRowLeft, IGGridViewSwipeRowActionSlideRowBoth IGGridViewSwipeRowActionManualSlideLeft or IGGridViewSwipeRowActionManualSlideBoth
 */
@property(nonatomic, assign) CGFloat slideRowLeftWidth;

/** If a slideRow is open, this method will close it */
-(void)closeSlideRow;

/** The gesture used for sliding a row manually. When swipeRowAction equals IGGridViewSwipeRowActionManual both, right or left*/
@property(nonatomic, readonly)UIPanGestureRecognizer* manualSlideRowGesture;

/** The gesture used for sliding a row using the swipeRowAction equals IGGridViewSwipeRowActionPercent both, right or left */
@property(nonatomic, readonly)UIPanGestureRecognizer* percentSlideRowGesture;

/** The gesture used for swiping a row left to right.*/
@property(nonatomic, readonly)UISwipeGestureRecognizer* swipeLeftToRightGesture;

/** The gesture used for swiping a row right to left.*/
@property(nonatomic, readonly)UISwipeGestureRecognizer* swipeRightToLeftGesture;


/** The font that will be used for the swipeToDelete button.
 
 The default is nil.
 */
@property(nonatomic, retain, nullable)   UIFont*                  deleteButtonFont;

/** Deletes rows in the receiver at the location identified by an array of IGRowPath objects, with an option to animate the deletion.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param paths An array of IGRowPath objects each representing a row in the grid view. 
 @param animation A constant that specifies the kind of animation to perform.
 */
-(void)deleteRowsAtPaths:(NSArray<__kindof IGRowPath*>*)paths withAnimation:(IGGridViewAnimation)animation;


/** Moves the specified cell in the receiver at the location identified by the new path.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param path An IGCellPath representing the cell that should be moved. 
 @param newPath An IGCellPath representing the new location of the cell.
 */
-(void)moveCellAtPath:(IGCellPath*)path toPath:(IGCellPath*)newPath;

/** Inserts cells in the receiver at the location identified by an array of IGCellPath objects, with an option to animate the insertion.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param paths An array of IGCellPath objects each representing a cell in the grid view. 
 @param animation A constant that specifies the kind of animation to perform.
 */
-(void)insertCellsAtPaths:(NSArray<__kindof IGCellPath*>*)paths withAnimation:(IGGridViewAnimation)animation;

/** Deletes cells in the receiver at the location identified by an array of IGCellPath objects, with an option to animate the deletion.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param paths An array of IGCellPath objects each representing a cell in the grid view. 
 @param animation A constant that specifies the kind of animation to perform.
 */
-(void)deleteCellsAtPaths:(NSArray<__kindof IGCellPath*>*)paths withAnimation:(IGGridViewAnimation)animation;

/** Moves the specified column in the receiver at the location identified by the new index.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param index An index representing the column that should be moved.
 @param newIndex An index representing the new location of the column.
 */
-(void)moveColumnAtIndex:(NSInteger)index toIndex:(NSInteger)newIndex;

/** Inserts columns in the receiver at the location identified by an array of NSNumbers.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)insertColumnsAtIndexes:(NSArray*)indexes;

/** Deletes columns in the receiver at the location identified by an array of NSNumber objects.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)deleteColumnsAtIndexes:(NSArray*)indexes;


/** A value that represents time in seconds it will take for rows and cell to be moved, inserted or deleted
 
 The default value is .75 seconds.
*/
@property(nonatomic, assign)CGFloat transitionDuration;

///---------------------------------------------------------------------------------------
/// @name Reloading the Grid View
///---------------------------------------------------------------------------------------

/** Reloads the rows and sections of the receiever. 
 
 Calling this method invokes all methods from the datasource and delegate used to build content area of the grid view. All state is lost including selection and scroll position. If you would like to reload the data but do not want to lose state, use the updateData method. 
 
 */
-(void)reloadData;

/** Reloads the rows and sections of the receiever. 
 
 Calling this method invokes all methods from the datasource and delegate used to build content area of the grid view. All state is kept, including selection and scroll position. If data is deleted, inserted, or reordered, the following methods should be used instead:
        moveCellAtPath:toPath:
        insertCellsAtPaths:withAnimation:animation 
        deleteCellsAtPaths:withAnimation:animation
        moveRowAtPath:toPath:
        insertRowsAtPaths:withAnimation:animation 
        deleteRowssAtPaths:withAnimation:animation
 */
-(void)updateData;

///---------------------------------------------------------------------------------------
/// @name Managing the Delegate and the Data Source
///---------------------------------------------------------------------------------------

/** The object that acts as the data source of the grid view.
 
 The delegate must adopt the IGGridViewDataSource protocol.
 */
@property(nonatomic, assign, nullable) id<IGGridViewDataSource> dataSource;

/** The object that acts as the delegate of the grid view.
 
 The data source must adopt the IGGridViewDelegate protocol.
 */
@property(nonatomic, assign, nullable) id <IGGridViewDelegate>  delegate;

///---------------------------------------------------------------------------------------
/// @name Shortcutbar
///---------------------------------------------------------------------------------------

/** Sets the width of the column for the shortcut bar.
 
 When the shortcut bar is visible, this property is uesd to determine how much space should be taken to display the shortcut bar.
 */
@property(nonatomic, assign)   CGFloat                  shortcutBarColumnWidth;

/** Sets the background view of the fixed column used for displaying the shortcut bar.
 
 This background view is sized to the available viewport determined by the frame of the grid view and the shortcutBarColumnWidth 
 */
@property(nonatomic, retain, nullable)   UIView*                  shortcutBarColumnBackgroundView;


/** Sets UIColor of the shortcut bar
 
 The default is white. This is the color of the shortcut bar itself and not the color of the background of the column the shortcut bar is in. 
 */
@property(nonatomic, retain)   UIColor*                 shortcutBarColor;


/** Sets UIColor of the shortcut bar while it's pressed.
 
 The default is light gray. This is the color of the shortcut bar itself and not the color of the background of the column the shortcut bar is in. 
 */
@property(nonatomic, retain)   UIColor*                 shortcutBarPressedColor;

///---------------------------------------------------------------------------------------
/// @name Pulldown Row
///---------------------------------------------------------------------------------------

/** Sets the height of the pull down row. 
 
The pull down row is a row that appears above the grid view, and can be seen when pulling the grid view down beyond its bounds. The height set, determines how far the pull down needs to be pulled before it switch from it's pull down state, to it's release state, and how much space it will take up in it's updating state.
 
 */
@property(nonatomic, assign)   CGFloat                  pullDownRowHeight;


/** Tells the grid view that it no longer needs to be in the update state, and should update it's data and go back to normal. 
 
 This method should be invoked when the pull down row of the grid view is in the upating state. This occurs when the grid view is pulled down beyond it's bounds and is released. This method will automatically invoke the updateData method.
 
 */
-(void)finishedUpdating;

/** Will animate and show the pull down the row without interaction. 
 */
-(void)showPullDownRow;

/** Returns the current state of the pull down row.
 */
-(IGGridViewPullDownState)pullDownState;


///---------------------------------------------------------------------------------------
/// @name Filtering
///---------------------------------------------------------------------------------------

/** Tells the grid view when it should apply the filter. 
 
    IGGridViewFilterActionImmediate - After each key press.
    IGGridViewFilterActionDoneEditing - When the user finishes typing.
 
 The default is IGGridViewFilterActionImmediate.
 */
@property(nonatomic, assign)IGGridViewFilterAction filterAction;

/** Sets the height of the search box in the grid view.
 
 The filter row will only appear if the data source's supportsFilteringInGridView: method returns true.
 */
@property(nonatomic, assign)   CGFloat                  filterRowHeight;

///---------------------------------------------------------------------------------------
/// @name Fixed Columns
///---------------------------------------------------------------------------------------

/** Sets the width of the separator for the left fixed columns.
 
 To this separator set the width to zero. The default value is 4.
 */
@property(nonatomic, assign)   CGFloat                  fixedLeftColumnSeparatorWidth;

/** Sets the width of the separator for the right fixed columns.
 
 To this separator set the width to zero. The default value is 4.
 */
@property(nonatomic, assign)   CGFloat                  fixedRightColumnSeparatorWidth;

/** Sets the UIColor of the separator of the left fixed column.
 
 The default is gray.
 */
@property(nonatomic, retain)   UIColor*                 fixedLeftColumnSeparatorColor;

/** Sets the UIColor of the separator of the right fixed column.
 
 The default is gray.
 */
@property(nonatomic, retain)   UIColor*                 fixedRightColumnSeparatorColor;

/** Inserts fixed columns to the left side of the receiver at the location identified by an array of NSNumbers.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)insertFixedLeftColumnsAtIndexes:(NSArray<__kindof NSNumber*>*)indexes;

/** Deletes fixed columns from the left side of the receiver at the location identified by an array of NSNumber objects.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)deleteFixedLeftColumnsAtIndexes:(NSArray<__kindof NSNumber*>*)indexes;

/** Inserts fixed columns to the right side of the receiver at the location identified by an array of NSNumbers.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)insertFixedRightColumnsAtIndexes:(NSArray<__kindof NSNumber*>*)indexes;

/** Deletes fixed columns from the right side of the receiver at the location identified by an array of NSNumber objects.
 
 UpdateData will automatically be invoked when this method is called. It should not be called before or after this method is invoked.
 
 @param indexes An array of NSNumber objects each representing an index of a column in the grid view.
 */
-(void)deleteFixedRightColumnsAtIndexes:(NSArray<__kindof NSNumber*>*)indexes;


///---------------------------------------------------------------------------------------
/// @name Editing
///---------------------------------------------------------------------------------------


/** Notifies the grid that it should listen for a keyboard and keep the specified Cell above the keyboard.
 
 This will update the contentInset of the grid, so as the last row of the grid is not lower than the keyboard. When the editor is no longer being used, you must call unregisterKeyboard:.
 
 @param cell The cell to auto scroll above th keyboard. If you do not want a particular cell to be kept in view, you can pass in nil.
 */
-(void)registerKeyboardForCell:(IGGridViewCell*)cell;

/** Notifies the grid that it no longer needs to listen to the keyboard changed event.
 
 @param reset Whether the grid should reset the contentInset. You may not want to reset the inset if another editor will gain focus. By saying NO to reset, it stops the grid from animating contentOffset to adjust for the new inset.
 */
-(void)unregisterKeyboard:(BOOL)reset;

/**
 When called will show the column resizing adorner on the column related to the cell corresponding to the path passed in.
 @param path The cell path that the adorner is being rendered for.
 */
-(void)showAdornerForColumnAtPath:(IGCellPath*)path;

@end

NS_ASSUME_NONNULL_END

