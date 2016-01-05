
#import <UIKit/UIKit.h>
#import "IGFlowLayoutViewCell.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, IGFlowLayoutType)
{
    IGFlowLayoutTypeVertical,
    IGFlowLayoutTypeHorizontal

};


@class IGFlowLayoutView;

/*!
 The IGFlowLayoutViewDataSource protocol is adopted by an object that mediates the application's data model for a IGFlowLayoutView object. The data source provides the flow layout view object with the information it needs to construct and modify a flow layout view.
 
 */
@protocol IGFlowLayoutViewDataSource <NSObject>

/** Asks the dataSource for the number of blocks both vertical and horizontal that will fit within the viewport of the flowLayoutView. (required)
 
 Blocks are a relative size. For example if your flowLayoutView's frame was 500x500 and you returned a size of 2x5 Then there would be 2 horizontal block each one having a width of 250 pts and there would be 5 vertical blocks each having a height of 100 pts. If the FlowLayoutView was then resized to be 200x200, the size of the blocks would also resize, however the number of blocks would not change.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @return The relative number of blocks that will fit in the viewport.
 */
-(CGSize)numberOfBlocksInViewport:(IGFlowLayoutView*)flowLayoutView;

/** Asks the dataSource for the total number of items that will be displayed in the flow layout view. (required)
 
 For example, if you had an array of objects that you wanted displayed, then you return that array's count in this method.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @return The total number of items that will be displayed.
 */
-(NSInteger)numberOfItemsInFlowLayoutView:(IGFlowLayoutView*)flowLayoutView;

/** Asks the dataSource for the number of blocks both vertical and horizontal that a particular item will use. (required)
 
 Blocks are a relative size, and will be limited by the size returned in numberOfBlocksInViewport: If you want an item to always take the maximum number of vertical or horizontal blocks for the viewport, you can set the width or height to INFINITY.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param index The index of a particular item that will be displayed in the flowLayoutView.
 @return The relative number of blocks that a particular item will use.
 */
-(CGSize)flowLayoutView:(IGFlowLayoutView*)flowLayoutView sizeForItemAtIndex:(NSInteger)index;


/** Asks the dataSource for IGFlowLayoutViewCell that is about to be displayed in the flowLayoutView. (required)
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param index The index of a particular item that will be displayed in the flowLayoutView.
 @return The visible representation of an item that will be displayed in the flowLayoutView.
 */
-(IGFlowLayoutViewCell*)flowLayoutView:(IGFlowLayoutView*)flowLayoutView cellAtIndex:(NSInteger)index;

@optional

/** Tells the dataSource an item is about to be reszied
 
 This method must be implemented in order to support user interactive resizing.
 
 The underlying data should then be updated, or if you do not want to be resized, or would prefer another size, you should return that preferred size.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param size The new proposed size for the specified item.
 @param index The index of a particular item in the flowLayoutView
 @return The size the item should be resized to. Or the newSize if you're not restricting it.
 */
-(CGSize)flowLayoutView:(IGFlowLayoutView*)flowLayoutView newSize:(CGSize)size forItemAtIndex:(NSInteger)index;


/** Tells the dataSource an item is about to be moved to a new index. 
 
 This method must be implemented in order to support user interactive reordering.
 
 The underlying data should then be updated, or if you do not want to be moved to the new index, or would prefer another index, you should return that preferred index.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param index The original index of a particular item in the flowLayoutView
 @param newIndex The new proposed index of a particular item in the flowLayoutView
 @return The index the item should be moved to. Or the newIndex if you're not restricting it.
 */
-(NSInteger)flowLayoutView:(IGFlowLayoutView*)flowLayoutView moveItemAtIndex:(NSInteger)index toIndex:(NSInteger)newIndex;


/** Asks the dataSource if particular item can be resized.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param index The index of a particular item in the flowLayoutView
 @return Yes if the item can be resized.
 */
-(BOOL)flowLayoutView:(IGFlowLayoutView*)flowLayoutView itemAtIndexResizable:(NSInteger)index;


/** Asks the dataSource if particular item can be dragged.
 
 @param flowLayoutView The flowLayouView requestiong the information.
 @param index The index of a particular item in the flowLayoutView
 @return Yes if the item can be dragged.
 */
-(BOOL)flowLayoutView:(IGFlowLayoutView*)flowLayoutView itemAtIndexDraggable:(NSInteger)index;

@end

/*! The protocol for the IGFlowLayoutView's delegate proerty. All methods on this protocol are optional, and provide additional information for selection, resizing and reordering.*/
@protocol IGFlowLayoutViewDelegate <UIScrollViewDelegate>

@optional

/** Tells the delegate that the user has just selected a new item in flow layout view.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param index The index of the item selected.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView editItemSelectedAtIndex:(NSInteger)index;

/** Tells the delegate that an item was unselected.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param index The index of the item that was previously selected.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView editItemDeselectedAtIndex:(NSInteger)index;

/** Tells the delegate that the user has just resized an item in the flow layout view.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param oldSize The size prior to resizing.
 @param newSize The new size of the item.
 @param index The index of the item reszied.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView itemSizeChangedFrom:(CGSize)oldSize to:(CGSize)newSize at:(NSInteger)index;

/** Tells the delegate that the user has just moved an item in the flow layout view.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param oldIndex The original index of the item.
 @param newIndex The new index of the item.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView itemIndexChangedFrom:(NSInteger)oldIndex to:(NSInteger)newIndex;

/** Tells the delegate that the user has finished a drag operation.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param index The new index of the item dragged.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView dragCompleteForItemAt:(NSInteger)index;

/** Tells the delegate that the user has finished moving an item from a position to a new position
 
 This method is invoked after the drag operation has completed and doesn't get invoked constantly during the drag operation.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param from The original index of the item dragged.
 @param to The new index of the item dragged.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView finishedDraggingItemFrom:(NSInteger)from to:(NSInteger)to;


/** Tells the delegate that the user has finished a resize operation.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param index The index of the item reszied.
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView resizeCompleteForItemAt:(NSInteger)index;

/** Tells the delegate that the user has finished a resize operation and shows the size change.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param index The index of the item reszied.
 @param from The original size of the item.
 @param to The new size of the item.
 
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView finishedResizingItem:(NSInteger)index from:(CGSize)from to:(CGSize)to;


/** Tells the delegate that the frame of the edit selection view had changed.
 
 @param flowLayoutView The flowLayoutView providing the information.
 @param frame The frame releative to the flowlayoutView of the  edit selection view.
 
 */
-(void)flowLayoutView:(IGFlowLayoutView*)flowLayoutView editViewFrameChanged:(CGRect)frame;

@end
/*!
 A flow layout view allows users to scroll through a list of items horizontally or vertically. The item's are provided to the view via the IGFlowViewDataSource protocol. All items are relatively sized instead of absolutely, which allows for dynamic layouts when the view is resized.
 
 */
@interface IGFlowLayoutView : UIScrollView

///---------------------------------------------------------------------------------------
/// @name Configuring a Flow Layout View
///---------------------------------------------------------------------------------------

/** Returns a reusable IGFlowLayoutViewCell object located by its identifier

For performance reasons, a flow layout view's data source should generally reuse IGFlowLayoutViewCell objects. A flow layout view maintains a queue or list of IGFlowLayoutViewCell objects that the view's dataSource has marked for reuse. It marks a cell for reuse by assigning it a reuse identifier when it creates it (that is, in the initWithReuseIdentifier: method of IGFlowLayoutViewCell). The data source can access specific template cell objects in this queue by invoking this method. You can access a cell's reuse identifier through it's reuseIdentifier property, which is defined by IGFlowLayoutViewCell.

@param identifier A string identifying the cell object to be reused. By default, a reusable cell's identifier is it's class name, but you can change it to any arbitrary value.
@return A IGFlowLayoutViewCell object with the associated identifier or nil if no such object exists in the reusable-cell queue.
*/
- (id)dequeueReusableCellWithIdentifier:(NSString *)identifier;

/** Determines the direction in which items in the flow layout view will be layed out. 
 
 If horizontal, the items will be laid out top to bottom then left to right, so that the view scrolls horizontally.
 If vertical, the items will be laid out left to right then top to bottom, so that the view scrolls vertically.
 */
@property(nonatomic, assign)IGFlowLayoutType layoutType;


///---------------------------------------------------------------------------------------
/// @name Accessing Cells and Items
///---------------------------------------------------------------------------------------

/** Returns the IGFlowLayoutViewCell for a particular index. 
 
 Nil will be returned if an item at that index isn't in the current viewport.

 @param index The index of cell that should be returned.
 @return The IGFlowLayoutViewCell for the specified index or nil if the item isn't in view.
 
 */
-(IGFlowLayoutViewCell*)cellAtIndex:(NSInteger)index;

/** Returns the IGFlowLayoutViewCell located at a particular point.
 
 Nil will be returned if an item at that point doesn't exist.
 
 @param point A point within the flow layout view.
 @return The IGFlowLayoutViewCell located at the specified point or nil if no item exists at that point.
 
 */
-(IGFlowLayoutViewCell*)cellAtPoint:(CGPoint)point;

/** Returns the index of an item located at a particular point.
 
 An index will always be returned. If no particular item is located at that point, then the closest index plus one will be returned instead.
 
 @param point A point within the flow layout view.
 @return The index of an item located at the specified point or the closest index plus one if no item exists at a particular point.
 
 */
-(NSInteger)closestItemAtPoint:(CGPoint)point;

/** Returns the Bounds of an item at the specified index.
 
 This method will always return a valid bounds, even if the item isn't in view. If the index specified is an invalid index, then CGRectZero is returned.
 
 @param index The index of an item within the flow layout view.
 @return The bounds of the item for the specified index.
 
 */
-(CGRect)boundsOfItemAtIndex:(NSInteger)index;

/** Returns the index of an item located at a particular point.
 
 If no item exists at the specified point, -1 will be returned. To always get an index, use closestItemAtPoint:
 
 @param point A point within the flow layout view.
 @return The index of an item located at the specified point or -1 if no item exists at the specified point.
 
 */
-(NSInteger)itemAtPoint:(CGPoint)point;

/* Gets/Sets whether a block sizes should be rounded to the closest pixel size, or if they should be allowed to have sub-pixel sizes
 
 The default is No.
 */
@property(nonatomic, assign)BOOL allowSubPixelBlockSizes;

/** Registers a class for use in creating new flowLayout cells.
 
 Prior to dequeueing any cells, call this method to tell the flowLayout view how to create new cells. If a cell of the specified type is not currently in a reuse queue, the flowLayout view uses the provided information to create a new cell object automatically.
 
 If you previously registered a class file with the same reuse identifier, the class you specify in the cellClass parameter replaces the old entry. You may specify nil for cellClass if you want to unregister the class from the specified reuse identifier.
 
 @param cellClass The class of a cell that you want to use in the flowLayout.
 @param identifier The reuse identifier for the cell. This parameter must not be nil and must not be an empty string.
 */
-(void)registerClass:(Class)cellClass forCellReuseIdentifier:(NSString*)identifier;

///---------------------------------------------------------------------------------------
/// @name Inserting, Deleting, and Resizing Cells
///---------------------------------------------------------------------------------------

/** A value that represents time in seconds it will take for cells to be moved, inserted or deleted
 
 */
@property(nonatomic, assign)CGFloat transitionDuration;

/** Tells the flow layout view that an item was inserted in the underlying data source at a specific index. Which results in the new item and all items after that index being animated to their new location.
 
 The duration of the animation is based off the time specified in the transitionDuration property.
 
 @param index The index the item was inserted at.
*/
-(void)insertItemAtIndex:(NSInteger)index;

/** Tells the flow layout view that an item was removed from the underlying data source at a specific index. Which results in the removed item and all items after that index being animated to their new location.
 
 The duration of the animation is based off the time specified in the transitionDuration property.
 
 @param index The index the item was removed at.
 */
-(void)removeItemAtIndex:(NSInteger)index;

/** Tells the flow layout view that an item was reszied in the underlying data source at a specific index. Which results in the resized item and all items after that index being animated to their new location.
 
 The duration of the animation is based off the time specified in the transitionDuration property.
 
 @param index The index the item was resized at.
 */
-(void)updateItemAtIndex:(NSInteger)index;


/** Tells the flow layout view that an item was moved to a new position in the underlying data source at a specific index. Which results in the item animated to the new position.
 
 The duration of the animation is based off the time specified in the transitionDuration property.
 
 @param index The original index of the item.
 @param newIndex The new index of the item.
 */
-(void)moveItemAtIndex:(NSInteger)index toIndex:(NSInteger)newIndex;

///---------------------------------------------------------------------------------------
/// @name Reloading the Flow Layout View
///---------------------------------------------------------------------------------------

/** Triggers a recalculation of the layout of all cells in the FLowLayoutView.
 
 Calling this method invokes all methods from the datasource and delegate used to build content area of the flow layout view. 
 */
-(void)updateData;


///---------------------------------------------------------------------------------------
/// @name Managing the Delegate and the Data Source
///---------------------------------------------------------------------------------------

/** The object that acts as the data source of the flow layout view.
 
 The delegate must adopt the IGFlowLayoutViewDataSource protocol.
 */
@property(nonatomic, weak, nullable)id<IGFlowLayoutViewDataSource> dataSource;

/** The object that acts as the delegate of the flow layout view.
 
 The data source must adopt the IGFlowLayoutViewDelegate protocol.
 */
@property(nonatomic, weak, nullable)id<IGFlowLayoutViewDelegate> delegate;

///---------------------------------------------------------------------------------------
/// @name Editing
///---------------------------------------------------------------------------------------

/** When set to YES, a user can select an item to resize or move it.
 
 In order to have resizing support, the dataSource must implement the following selector:
    flowLayoutView:newSize:forItemAtIndex:
 
 In order to have reordering support, the dataSource must implement the following selector:
    flowLayoutView:moveItemAtIndex:toIndex:
 
 */
@property(nonatomic, assign)BOOL editable;

/** The index of the currently selected item, or -1 if no item is selected.
 
*/
@property(nonatomic, readonly)NSInteger editItem;

/** The color of the select item's border
 */
@property(nonatomic, retain)UIColor* editItemColor;

/** The color of the resize handles for an editable item
 */
@property(nonatomic, retain)UIColor* editItemHandleColor;

/** Whether the editItemHandles are clipped so that they don't exceed past the border of the editItem view
 */
@property(nonatomic, assign)BOOL clipEditItemHandles;

/** The size of the resize handles for an editable item
 */
@property(nonatomic, assign)CGFloat editItemHandleSize;

/** The size of the border on an editable item
 */
@property(nonatomic, assign)CGFloat editItemBorderWidth;

/** Selects the item at the specified index. 
 
 @param index The index of the item to select. If an invalid index such as -1 is passed in, no item will be selected.
 */
-(void)selectItemAtIndex:(NSInteger)index;

///---------------------------------------------------------------------------------------
/// @name Navigation
///---------------------------------------------------------------------------------------

/** Maximizes the item at the specified index.
 
 @param index The index of the item to maximize. If an invalid index such as -1 is passed in, no item will be maximized.
 */
-(void)maximizeItem:(NSInteger)index;

/** If the flowLayout is currently in a maximized state, the control will transtion back to its normal state.

 */
-(void)minimize;

@end

NS_ASSUME_NONNULL_END




