//
//  IGGridViewCell.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, IGGridViewGestureAction)
{
    IGGridViewGestureActionToggleSort,
    IGGridViewGestureActionSelect,
    IGGridViewGestureActionContextMenu,
    IGGridVIewGestureActionDeleteButton
    
} ;

@class IGCellPath;
@class IGGridView;

/*!
 An IGGridViewCellBase is the base class used for all cells in the IGGridView. It's a visual that maps to a coordinate system (IGCellPath) of Section, Row and Column.
 
 The cells of the IGGridView are meant to be inherited and customized. To do this, you simply derive from the appropriate cell. For example, for standard data cells, you should derive from IGGridViewCell.
 @interface ButtonCell : IGGridViewCell
 {
 UIButton* _button;
 }
 @end
 
 Then initialize the views you want to display in the cell and add them to them as subviews when the cell is intialized.
 -(id)init
 {
 self = [super init];
 if(self)
 {
 _button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
 [_button setTitle:@"Click Me" forState:UIControlStateNormal];
 [self.view addSubview:button];
 }
 return self;
 }
 
 Then override the setupSize method. You can use this method to set the frame of your subviews.
 -(void)setupSize:(CGSize)size
 {
 _button.frame = CGRectMake(0, 0, size.width, size.height);
 }
 
 If you need to do setup or clean when the cell is added to the grid view, or removed from the grid view, you can override the cell's cellAttached and celDetached methods.
 
 -(void)cellAttached
 {
 [_button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
 }
 
 -(void)cellDetached
 {
 [_button removeTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
 }
 
 All cells also support the use of custom gestures. For example if you wanted to add a double tap gesture to a cell, you would first need to decide if you wanted the gesture added to every cell, or a specific cell. If you wanted it on a specific cell, you would use the registerTemporaryGestures: selector, as it would be removed as soon as the cell was out of view. However, if you wanted it on every cell, then you can use the registerGestures: selector.  Once  you've decided on what cell you want to apply a gesture, you can simply create your gestures and pass them in as an array to the the formerly mention selectors. After that, the cell will take care of the rest and attach your gestures for you.
 */
@interface IGGridViewCellBase : UIView<UIGestureRecognizerDelegate>
{
    NSString *_reuseIdentifier;
    CGPoint _orignPoint;
    NSDate* _touchBeganTime;
    UIPanGestureRecognizer* _panGesture;
    BOOL _canMoveCell;
    NSArray *_tempGestures, *_registeredGestures;
}

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
@property(nonatomic,readonly,copy) NSString       *reuseIdentifier;

///---------------------------------------------------------------------------------------
/// @name Custom Gestures
///---------------------------------------------------------------------------------------

/** Applies UIGestureRecognizer objects to the cell
 
 Takes the array of gestures and applies them to the cell. The gestures will remain applied to the cell until they unregisterGestures selector is called. This method should be used when the cell is first created or initialized.
 
 @param gestures An array of UIGestureRecognizer objects.
 */
-(void)registerGestures:(NSArray<__kindof UIGestureRecognizer*>*)gestures;

/** Unregisters all gestures specified by the registerGestures: selector
 */
-(void)unregisterGestures;

/** Applies UIGestureRecognizer objects to the cell
 
 Takes the array of gestures and applies them to the cell. The gestures will remain applied to the cell while it's in view. As soon as it's out of view the gestures will be removed. You can then add gestures again when the cell comes back in view.
 
 @param gestures An array of UIGestureRecognizer objects.
 */
-(void)registerTemporaryGestures:(NSArray<__kindof UIGestureRecognizer*>*)gestures;

///---------------------------------------------------------------------------------------
/// @name Protected Members
///---------------------------------------------------------------------------------------

/** The inset of the content of a cell.
 
 This property should not be set directly, as the grid view will set this property based on it's cellContentInset property.
 */
@property(nonatomic, assign) UIEdgeInsets contentInset;

/** Tells the cell to setup the size of it's content
 
 This method should not be called directly. It's for use in a derived class, and should be used for setting up and laying out the frames of the contents of the cell.
 
 @param size The size of the cell view.
 */
-(void)setupSize:(CGSize)size;

/** Notifies the cell, that it is currently not being used by the grid view
 
 This method should not be called directly. It's for use in a derived class to do any cleanup that might be neccessary when the cell is not currently being used.
 */
-(void)cellDetached;

/** Notifies the cell that the grid view has just started using it.
 
 This method should not be called directly. It's for use in a derived class to setup anything that is neccessary for it to display its content
 */
-(void)cellAttached;

/** Notifies the cell that its location within the viewport of the grid has changed.
 
 This method should not be called directly. It's for use in a derived class to setup anything that is neccessary for it to adjust its content.
 
 @param location A CGPoint where x represents the horizontal location of the center of the cell from 0 - 1. Where zero is the left edge of the viewport and 1 is the right edge of the viewport. Likewise, y represents the vertical location of the center of the cell from 0 - 1. Where zero is the top edge of the viewport and 1 is the bottom edge of the viewport.
 
 */
-(void)cellLocationInViewportChanged:(CGPoint)location;

/** The path of the cell that this IGGridViewCellBase represents.
 
 */
@property(nonatomic, readonly)IGCellPath* path;


/** The IGGridView that is curently displaying this cell.
 
 */
@property(nonatomic, readonly)IGGridView* gridView;


@end

/*!
 IGGridViewCell is the base class for all display cells in the IGGridView. It's a visual that maps to a coordinate system (IGCellPath) of Section, Row and Column.
 
 Thie IGGridViewCell can be selected, and you can control the selection appearance for a cell using it's selectedView and selectedColor properties.
 
 The main display element of an IGGridViewCell is the textLabel which can be used to display text for the cell.
 
 */
@interface IGGridViewCell : IGGridViewCellBase
{
    UILabel *_textLabel;
    UIColor *_notSelectedColor, *_notSelectedTextColor;
    UIView *_selectedView;
    BOOL _isSelected;
    BOOL _selectionColorSet;
    UILongPressGestureRecognizer* _contextMenuGesture;
    BOOL _initialized;
    UIView* _currrentSelectedView;
    UITapGestureRecognizer* _selectGesture;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** Returns the label used for the main textual content of the grid cell.
 
 You can use this property to change styling options such as text color and text alignment
 */
@property(nonatomic,readonly,retain) UILabel      *textLabel;

///---------------------------------------------------------------------------------------
/// @name Selection
///---------------------------------------------------------------------------------------

/** A view that will be displayed on top of the cell, when it is selected.
 
 The view provided will be sized to the frame of the cell.
 */
@property(nonatomic, retain, nullable)    UIView* selectedView;

/** A color that will be used as the background color of the cell when it is selected.
 
 If you would like no background color, you can set this property to clearColor.
 */
@property(nonatomic, retain)    UIColor* selectedColor;

/** Returns whether the current cell is selected
 */
@property(nonatomic, readonly)BOOL isSelected;

/** Returns the gesture used for selection.
 */
@property(nonatomic, readonly)UIGestureRecognizer* selectionGesture;

/** This method gets invoked everytime a cell is selected, or when a cell comes back into view that was selected.
 
If you want a custom way to make your cell look when its selected. This is the place to do it.
 */
-(void)updateSelected;

/** This method gets invoked everytime a cell is unselected, or when a cell comes back into view that was not selected.
 
 If you want a custom way to make your cell look when its selected. This is the place to do it.
 */
-(void)updateNotSelected;

@end

/*!
 IGGridViewHeaderCell is the visual used to diplay cells in the header of the IGGridView.
 
 The main display element of the header cell is the textLabel which can be used to display text for the cell.
 
 To place other visuals in the header cell, you can derive from this class, and add custom display elements. You can then use the following selector of the  IGGridViewDataSource  to display your new cell.
 -(IGGridViewHeaderCell *) gridView:(IGGridView *)gridView headerCellForRowAt:(int)column
 */
@interface IGGridViewHeaderCell : IGGridViewCellBase
{
    UILabel *_textLabel;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** Returns the label used for the main textual content of the header cell.
 
 You can use this property to change styling options such as text color and text alignment
 */
@property(nonatomic,readonly,retain) UILabel      *textLabel;

/** Helper method for creating a IGGridViewHeaderCell. Also applies the theme.
 
 @param gridView The IGGridView that the cell will be displayed in.
 
 */
+(IGGridViewHeaderCell*)createHeaderCell:(IGGridView*)gridView;

@end


/*!
 IGGridViewSectionCell is the visual used to diplay cells for section headers and footers in the IGGridView.
 
 The main display element of an IGGridViewCell is the textLabel which can be used to display text for the cell.
 
 To place other visuals in the header or footer of a secion, you can use the IGGridViewDelegate's
 -(UIView*)gridView:(IGGridView*)gridView viewForSectionHeader:(int)section;
 and
 -(UIView*)gridView:(IGGridView*)gridView viewForFooterInSection:(int)section;
 
 */
@interface IGGridViewSectionCell : IGGridViewCellBase
{
    CAGradientLayer *_gradLayer;
    UIView* _customView;
    UILabel *_textLabel;
    BOOL _hideGradient;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** Returns the label used for the main textual content of the section cell.
 
 You can use this property to change styling options such as text color and text alignment
 */
@property(nonatomic,readonly,retain) UILabel      *textLabel;

@end

/*!
 IGGridViewSectionHeaderCell is the visual used to diplay cells for section headers in the IGGridView.
 
 The main display element of an IGGridViewCell is the textLabel which can be used to display text for the cell.
 
 There is also a UIButton which is used when the cell is marked as expandable, so the user can interact by click the section header to expand or colapse.
 
 To place other visuals in the header of a secion, you can use the IGGridViewDelegate's
 -(UIView*)gridView:(IGGridView*)gridView viewForSectionHeader:(int)section;
 
 */
@interface IGGridViewSectionHeaderCell : IGGridViewSectionCell

/** Determines if the section is currently expanded or collapsed (readOnly)
 
 */
@property(nonatomic, readonly)BOOL expanded;

/** When set to YES, the section header can be clicked to toggle expansion the section.
 
 Note: the datasource must support expansion for anything to actually occur.
 */
@property(nonatomic, assign)BOOL expandable;

/** The UIButton in the section header that is used for toggling expansion
 
 */
@property(nonatomic, readonly)UIButton* expandButton;

/** A UIColor that determines the pressed color used when the expandButton is in it's pressed state.
 
 */
@property(nonatomic, retain)UIColor* pressedBackgroundColor;

/** Invoke this method to collapse a section
 
 */
-(void)collapse;

/** Invoke this method to expand a section
 
 */
-(void)expand;


/** Helper method for creating a IGGridViewSectionHeaderCell. Also sets the theme information and calls the appropriate delegate/datasource methods.
 
 @param gridView The IGGridView that the cell will be displayed in.
 @param section The index of the section that this cell will represent.
 
 */
+(IGGridViewSectionHeaderCell *)gridView:(IGGridView *)gridView cellForSectionHeader:(NSInteger)section;


@end


/*!
 IGGridViewImageCell is a cell that can be used for displaying images.  It has an optional feature for zooming, where you can you pinch to zoom on an image, and double tap to zoom or unzoom. You can set the image to be displayed by using the imageView property, as well as change how the image should be displayed such as using it's contentMode property.  To control zoom level features you can use the scrollView property.  This cell like IGGridViewCell supports selection.
 
 */
@interface IGGridViewImageCell : IGGridViewCell<UIScrollViewDelegate>
{
    UIScrollView* _scrollView;
    UIImageView* _imageView;
    BOOL _enableZooming;
    NSString* _currentRequestID;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** The UIScrollView used for zooming.
 
 The imageView for this cell is wrapped in a scroll view. You can use this property to change any zoom features such as maximumZoomScale and minimumZoomScale.
 */
@property(nonatomic,readonly,retain) UIScrollView     *scrollView;

/** The main display element of this cell. Displays an image.
 
 You can use this property to change styling options such as contentMode.
 */
@property(nonatomic,readonly,retain) UIImageView      *imageView;

/** The ammount of space between the text field and the imageview
 */
@property(nonatomic, assign) CGFloat textPadding;

///---------------------------------------------------------------------------------------
/// @name Features
///---------------------------------------------------------------------------------------

/** Sets whether zooming allowed on the image.
 
 This property controls whether a built in zooming mechanism for this cell is turned on. When set to YES you can pinch to zoom, and double tap zoom or unzoom the image cell. When the cell leaves view, the zooming will be rest automatically.
 */
@property(nonatomic, assign)BOOL enableZooming;

@end

/*! This is the cell that is used for search box in the IGGridView
 
 You can use the textField property to change such values as the placeholder text.
 
 To apply a derived version of this cell in the IGGridView, you can use the following selector from the IGGridViewDataSource:
 - (IGGridViewFilterCell *) filterCellForGridView:(IGGridView *)gridView;
 */
@interface IGGridViewFilterCell : IGGridViewCellBase<UITextFieldDelegate>
{
    UITextField* _textField;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** The UITextField that is used for searching through the IGGridView.
 
 */
@property(nonatomic,readonly,retain) UITextField      *textField;

@end


/*! This is the cell that is used for the row reordering indicator in the IGGridView
 
 You can use the reorderView property to change what the indicator looks like.
 
 To apply a derived version of this cell in the IGGridView, you can use the following selector from the IGGridViewDataSource:
 - (IGGridViewReorderCell *) gridView:(IGGridView *)gridView cellForReorderingAtPath:(IGCellPath*)path;
 */
@interface IGGridViewReorderCell : IGGridViewCellBase<UIGestureRecognizerDelegate>
{
    UIView* _reorderView;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** The UIView that is used as the visual indicator for reordering rows.
 
 Note: this view will only be displayed if that particular row supports reordering.
 */
@property(nonatomic, retain, nullable)UIView* reorderView;

@end

/*! This is the cell that is used to indicate that not all the rows were loaded, and more were requested.
 
 This cell will only appear when you're using a IGGridViewDataSourceHelper, and you've set the loadMoreDelegate property.
 
 To apply a derived version of this cell, you can use the following selector from the IGGridViewDataSourceHelperLoadMoreDelegate:
 - (IGGridViewLoadMoreCell *) cellForLoadingMore:(IGGridView *)gridView;
 */
@interface IGGridViewLoadMoreCell :IGGridViewCell
@end


/** The IGGridViewPullDownCell is a cell that is used to simulate a feature similar to facebook and twitter, where a user can pull the grid view past it's extent, and release to refresh. This cell can be used to customize what is displayed in it's three modes.
 
 The three modes are as follows:
 
 PullDown:
 This is the intial state. It occurs when the user firsts starts to pull down the grid view past its extent.
 An example of what it would display is "Pull down to refresh..."
 
 Release:
 This state occurs when the user pulls the grid view past its extent the distance of the grid view's pullDownRowHeight property.
 An example of what it would display is "Release to refresh..."
 
 Updating:
 This is the final state. It occurs when the user releases the grid view while it's in the Release state.
 At this point the grid view's delegate will notify the developer that it is in it's update state, and that they should perform an action to refresh their content.
 When the developer has done this, then can then invoke the grid view's finishedUpdating method.
 
 Deriving from this cell, you can actually control what gets displayed in each state, and even supply a transition by using the following methods:
 changeStateToPullDownMode
 changeStateToReleaseMode
 changeStateToUpdatingMode
 
 If all you desire is to change the text that is used in each state, you can use the following properties:
 pullDownText
 releaseText
 updatingText
 
 To use a custom IGGridViewPullDownCell in the IGGridView, simply use the following selector on the IGGridViewDataSource
 - (IGGridViewPullDownCell *) pullDownCellForGridView:(IGGridView*)gridView;
 */
@interface IGGridViewPullDownCell : IGGridViewCellBase
{
    UILabel* _pullDownLabel;
    UIActivityIndicatorView* _updatingIndicator;
}

///---------------------------------------------------------------------------------------
/// @name Display
///---------------------------------------------------------------------------------------

/** This is the main display element of the cell. You should not set the text property directly, instaed use the pullDownText, releaseText, and updatingText properties.
 
 */
@property(nonatomic, readonly)UILabel* displayLabel;

/** This is a UIActivityIndicatorView that will be displayed when the cell is in it's Updating state.
 
 To disable the indicator set the displayUpdatingIndicator to NO.
 */
@property(nonatomic, readonly)UIActivityIndicatorView* updatingIndicator;

/** Controls whether the updatingIndicator will be displayed in the cell when its in it's Updating state.
 
 */
@property(nonatomic, assign)BOOL displayUpdatingIndicator;

///---------------------------------------------------------------------------------------
/// @name Display Text
///---------------------------------------------------------------------------------------

/** The text that is used in the displayLabel when the cell is in it's PullDown state
 
 */
@property(nonatomic, retain, nullable)NSString* pullDownText;

/** The text that is used in the displayLabel when the cell is in it's Release state
 
 */
@property(nonatomic, retain, nullable)NSString* releaseText;

/** The text that is used in the displayLabel when the cell is in it's Updating state
 
 */
@property(nonatomic, retain, nullable)NSString* updatingText;

///---------------------------------------------------------------------------------------
/// @name Protected Overrides
///---------------------------------------------------------------------------------------

/** This method is invoked when the cell is going into it's pull down mode.
 
 Use this method to transition your content into the pull down mode.
 */
-(void)changeStateToPullDownMode;

/** This method is invoked when the cell is going into it's release mode.
 
 Use this method to transition your content into the release mode.
 */
-(void)changeStateToReleaseMode;

/** This method is invoked when the cell is going into it's updating mode.
 
 Use this method to transition your content into the updating mode.
 */
-(void)changeStateToUpdatingMode;


@end

NS_ASSUME_NONNULL_END

