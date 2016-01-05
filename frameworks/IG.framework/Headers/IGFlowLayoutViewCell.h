
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 The visible representation of an item in the IGFlowLayoutView. Only items currently wihtin the viewport will have a cell, and all cell's should be reused via the flowLayoutView's dequeueReusableCellWithIdentifier: method along with the cell's initWithReuseIdentifier: initializer.
 */
@interface IGFlowLayoutViewCell : UIView


///---------------------------------------------------------------------------------------
/// @name Initializing a Cell object
///---------------------------------------------------------------------------------------

/** Initializes and returns a cell object with the specified reuse identifier.
 
 You must specify the reuse identifier of a cell when you create it and you cannot thereafter modify it.
 
 @param identifier A string which specifies the identifier used for recycling.
 @return Returns an initialized IGGridViewCellBase object or nil if the object could not be successfully initialized.
 */
- (instancetype)initWithReuseIdentifier:(NSString*) identifier;

/** A string which is used by the grid view to determine reuse via an internal recycling engine (readonly)
 
 This property can only be set when the cell is initialized via the initWithReuseIdentifier: selector.
 */
@property(nonatomic,readonly,copy) NSString *reuseIdentifier;

/** The UIEdgeInsets around the contentView of the cell
 
 Use this property to create spacing between item's in the flowLayoutView.
 */
@property(nonatomic, assign)UIEdgeInsets contentInset;

/** The UIView that will be displayed in a particular cell. Simply set this property to the view you want to be displayed, and the cell will autmatically
 set it's frame to be the size of the cell. 
 */
@property(nonatomic, retain, nullable)UIView* contentView;


/** The index of the item that this cell currently represents. (readonly)
 */
@property(nonatomic, readonly)NSInteger index;

/** Notifies the cell, that it is currently not being used by the flowLayout view
 
 This method should not be called directly. It's for use in a derived class to do any cleanup that might be neccessary when the cell is not currently being used.
 */
-(void)cellDetached;

/** Notifies the cell that the flowLayout view has just started using it.
 
 This method should not be called directly. It's for use in a derived class to setup anything that is neccessary for it to display its content
 */
-(void)cellAttached;

/** Notifies the cell, that it is about to be detached, this occurs before the cell loses its frame.
 
 This method should not be called directly. It's for use in a derived class to do any cleanup that might be neccessary when the cell is not currently being used.
 */
-(void)cellWillDetach;

/** Notifies the cell that the flowLayout view will start using it, this occurs before the cell sets its frame.
 
 This method should not be called directly. It's for use in a derived class to setup anything that is neccessary for it to display its content
 */
-(void)cellWillAttach;

@end

NS_ASSUME_NONNULL_END
