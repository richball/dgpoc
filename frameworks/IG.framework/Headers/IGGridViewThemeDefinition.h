//
//  IGGridViewThemeDefinition.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "IGColumnWidth.h"
#import "IGRowPath.h"

/*!
 The IGGridViewThemeDefinition protocol is adopted by an object that mediates key styling points of a IGGridView object. The theme provides the grid view object with the information it needs to specific areas of the grid view.
 
 The theme has a higher order of precedence than properties specifically on the IGGridView and IGGridViewCell, but a lower order of precedence than properties on the IGGridViewDataSource, IGGridViewDelegate and IGGridViewColumnDefintion objects.
 
 All methods and properties in this protocol are optional.
 
 Some properties will only take effect if certain objects are used. For example, cell related properties must use the IGGridViewDataSourceHelper and IGGridViewColumnDefintion objects that are built into the control, otherwise the creator of the cell is responsible for setting theme definition properties on the cell.
 
 */
@protocol IGGridViewThemeDefinition <NSObject>

@optional

///---------------------------------------------------------------------------------------
/// @name Cells
///---------------------------------------------------------------------------------------

/** The background color of an IGGridViewCell in the IGGridView. 
 
This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects. If you also set the alternateRowCellBackgroundColor, then this property will only apply to cells in even number rows, where the first index is zero.
 */
@property(nonatomic, readonly)UIColor* cellBackgroundColor;


/** The text color of an IGGridViewCell in the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects. If you also set the alternateRowCellTextColor, then this property will only apply to cells in even number rows, where the first index is zero.
 */
@property(nonatomic, readonly)UIColor* cellTextColor;

/** The font of an IGGridViewCell in the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects. 
*/
@property(nonatomic, readonly)UIFont* cellTextFont;


/** The background color of an IGGridViewCell in the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects. This property will only apply to cells in odd number rows, where the first index is zero.
 */
@property(nonatomic, readonly)UIColor* alternateRowCellBackgroundColor;

/** The text color of an IGGridViewCell in the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects. This property will only apply to cells in odd number rows, where the first index is zero.
 */
@property(nonatomic, readonly)UIColor* alternateRowCellTextColor; 

/** The UIEdgeInset for the content of all IGGridViewCell objects in the grid view.
 
 Use this property to set the inset of the content of a cell. This property should not be set when the style of the grid view is set to IGGridViewStyleSingleCellPaging. This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIEdgeInsets cellContentInset; 

///---------------------------------------------------------------------------------------
/// @name Rows
///---------------------------------------------------------------------------------------

/** The amount of space that is appended after each row.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat rowSpacing;

/** The height of every row in the grid view.
 
 This property will override the grid level version of this property, however the IGGridViewDelegate method gridView:heightForRowAtPath: has higher precedence.
 */
@property(nonatomic, readonly)CGFloat rowHeight;

/** The UIColor of every row separator in the grid view.
 
 This property will override the grid level version of this property. 
 
 This value is only used when the delegate's gridView:viewForRowSeparatorAtPath: or the viewForRowSeparatorAtPath: method on theme is not implemented.
 */
@property(nonatomic, readonly)UIColor* rowSeparatorColor;

/** The height of every row separator in the grid View

 This property will override the grid level version of this property.
 
 To remove the row separator, return a height of zero.
 */
@property(nonatomic, readonly)CGFloat rowSeparatorHeight;

/** A view that will be used for a row separator at a specific path.
 
 The IGGridViewDelegate's gridView:viewForRowSeparatorAtPath: has higher precedence.
 
 @param path The IGRowPath that identifes the specific row separator that should be returned */
-(UIView*)viewForRowSeparatorAtPath:(IGRowPath*)path;

/** A view that will be used for a row background at a specific path.
 
 The IGGridViewDelegate's gridView:viewForRowBackgroundAtPath: has higher precedence.
 
 @param path The IGRowPath that identifes the specific row background that should be returned */

-(UIView*)viewForRowBackgroundAtPath:(IGRowPath*)path; 

///---------------------------------------------------------------------------------------
/// @name Columns
///---------------------------------------------------------------------------------------

/** the amount of space that is appended after each column.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat columnSpacing;

/** The width of every column in the grid view.
 
The order of precedence is as follows:
 IGGridViewDataSource,
 IGGridViewDelegate,
 IGGridViewThemeDefintion,
 IGGridView
 */
@property(nonatomic, readonly)IGColumnWidth* columnWidth; // trumps gridLevel prop but delegate trumps this prop and datasource trumps that

///---------------------------------------------------------------------------------------
/// @name Header Row
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of all header cells in the grid view.
 
 This property will override the grid level version of this property. If you provide a custom header cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* headerCellBackgroundColor;

/** The UIColor used for the text of all header cells in the grid view.
 
 This property will override the grid level version of this property. If you provide a custom header cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* headerCellTextColor;

/** The UIFont used for all header cells in the grid view.
 
 This property will override the grid level version of this property. If you provide a custom header cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIFont* headerCellTextFont; 

/** The UITextAlignment used for all header cells in the grid view.
 
 This property will override the grid level version of this property. If you provide a custom header cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)NSTextAlignment headerCellTextAlignment;

/** The height of the header row.
 
 This property will override the grid level version of this property. 
 */
@property(nonatomic, readonly)CGFloat headerHeight; // trumps gridLevel prop


///---------------------------------------------------------------------------------------
/// @name Section Header
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of all section header cells in the grid view.
 
This property will not be used if you provide a custom section header view via the IGGridViewDelegate or a custom section header cell via the IGGridViewDataSource.
 */
@property(nonatomic, readonly)UIColor* sectionHeaderBackgroundColor;

/** The UIColor used for the text of all section header cells in the grid view.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate.
 */
@property(nonatomic, readonly)UIColor* sectionHeaderTextColor;

/** The UIFont used for of all section header cells in the grid view.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate.
 */
@property(nonatomic, readonly)UIFont* sectionHeaderTextFont;

/** The height of every section header row in the grid view.
 
 The order of precedence is as follows:
 IGGridViewDelegate,
 IGGridViewThemeDefintion,
 IGGridView
 */
@property(nonatomic, readonly)CGFloat sectionHeaderHeight;

/** The UIColor used for the background of all section header cells in the grid view, when it's being pressed and expansion is turned on.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate or a custom section header cell via the IGGridViewDataSource.
 */
@property(nonatomic, readonly)UIColor* sectionHeaderPressedBackgroundColor;

///---------------------------------------------------------------------------------------
/// @name Section Footer
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of all section footer cells in the grid view.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate.
 */
@property(nonatomic, readonly)UIColor* sectionFooterBackgroundColor;

/** The UIColor used for the text of all section footer cells in the grid view.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate.
 */
@property(nonatomic, readonly)UIColor* sectionFooterTextColor;

/** The UIFont used for of all section header cells in the grid view.
 
 This property will not be used if you provide a custom section header view via the IGGridViewDelegate.
 */
@property(nonatomic, readonly)UIFont* sectionFooterTextFont;


/** The height of every section footer row in the grid view.
 
 The order of precedence is as follows:
 IGGridViewDelegate,
 IGGridViewThemeDefintion,
 IGGridView
 */
@property(nonatomic, readonly)CGFloat sectionFooterHeight;  

///---------------------------------------------------------------------------------------
/// @name Section Column
///---------------------------------------------------------------------------------------

/** The UIColor of the content area of the Section column.
 
 The content area is the area in which the views specified in viewForSectionColumn: will be displayed. The default value is clear;
 
This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* sectionColumnContentColor;

/** The width of the section column. 
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat sectionColumnWidth;

/** The background view of the fixed column used for displaying a section's custom content.
 
 When the delegate's gridView:viewForSectionColumn: is implemented, this specified view is used as a background for the column used to display the specified content. This background view is sized to the available viewport determined by the frame of the grid view and the sectionColumnWidth. This property has lower precedence than the delegate method.
 */
@property(nonatomic, readonly)UIView* sectionColumnBackgroundView; // trumps gridview prop

///---------------------------------------------------------------------------------------
/// @name Shortcut Bar
///---------------------------------------------------------------------------------------

/** The UIColor of the shortcut bar itself and not the color of the background of the column the shortcut bar is in. 
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* shortcutBarColor;

/** The UIColor of the shortcut bar when its pressed.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* shortcutBarPressedColor;

/** The width of the shortcut bar's column.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat shortcutBarColumnWidth;

/** The UIColor of the shortcut bar's background.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* shortcutBarColumnBackgroundColor;

/** The UIFont of the shortcut bar.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIFont* shortcutBarFont;

/** The UIColor of the shortcut bar's item text.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* shortcutBarTextColor;

/** The UIColor of the shortcut bar's item text when its pressed.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* shortcutBarTextPressedColor;

/** The UIColor of the shortcut bar's border.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* shortcutBarBorderColor;

///---------------------------------------------------------------------------------------
/// @name Selection
///---------------------------------------------------------------------------------------

/** The UIColor that will be used as the background of a cell when its selected.
 
 This property will override the cell level version of this property.
 */
@property(nonatomic, readonly)UIColor* selectedCellColor;

/** The UIColor that will be used for the text of a cell when its selected.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* selectedCellTextColor; 

/** The UIView that will be displayed when a cell is selected.
 
 This method will override the cell level version of this property.
 */
-(UIView*)viewForSelectedCell; // trumps cell level prop

///---------------------------------------------------------------------------------------
/// @name Column Resizing Adorner
///---------------------------------------------------------------------------------------

/** The UIColor of the adorner used for resizing a column when the columnResizing property is set to IGGridViewColumnResizeActionAdorner.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* columnResizingAdornerColor;

/** The UIColor of the thumb on the adorner used for resizing a column when the columnResizing property is set to IGGridViewColumnResizeActionAdorner.
 
  This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* columnResizingAdornerThumbColor;

/** The height of the header of the adorner used for resizing a column when the columnResizing property is set to IGGridViewColumnResizeActionAdorner.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)CGFloat columnResizingAdornerHeaderHeight;

///---------------------------------------------------------------------------------------
/// @name Row Reordering Column
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of all row reordering cells in the grid view.
 
 This property will not be used if you provide a custom reorder cell via the IGGridViewDataSource.
 */
@property(nonatomic, readonly)UIColor* rowReorderingCellBackgroundColor; 

/** The width of the row reordering column.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat rowReorderingColumnWidth;

///---------------------------------------------------------------------------------------
/// @name Filter Row
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of the filter cell.
 
   This property only exists on the theme. If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* filterCellBackgroundColor;

/** The UIColor used for the text field of the filter cell.
 
 This property only exists on the theme. If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* filterCellTextFieldColor;

/** The UIFont used for the filter cell.
 
 This property only exists on the theme. If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIFont* filterCellTextFieldFont;

/** The UIColor used for the text of the filter cell.
 
 This property only exists on the theme. If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* filterCellTextFieldTextColor;

/** The corner radius of the text field in the filter cell.
 
 This property only exists on the theme. If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)CGFloat filterCellTextFieldCornerRadius;

/** The height of the filter row.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat filterRowHeight;

///---------------------------------------------------------------------------------------
/// @name Pull Down Row
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of the pull down row.
 
 This property only exists on the theme. If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* pullDownRowBackgroundColor;

/** The UIColor used for the text of the pull down row.
 
 This property only exists on the theme. If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* pullDownRowTextColor;

/** The UIFont of the pull down row.
 
 This property only exists on the theme. If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIFont*  pullDownRowFont;

/** The height of the pull down row.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat pullDownRowHeight;

///---------------------------------------------------------------------------------------
/// @name Load More Row
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of the load more row
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* loadMoreRowBackgroundColor;

/** The UIColor used for the text of the load more row
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* loadMoreRowTextColor;

/** The UIFont used for the load more row
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIFont*  loadMoreRowFont;

///---------------------------------------------------------------------------------------
/// @name Fixed Left Column
///---------------------------------------------------------------------------------------

/** The background color of an IGGridViewCell that is fixed to the left of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIColor* fixedLeftCellBackgroundColor;

/** The text color of an IGGridViewCell that is fixed to the left of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIColor* fixedLeftCellTextColor;

/** The UIFont of an IGGridViewCell that is fixed to the left of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIFont*  fixedLeftCellFont;

/** The UIColor of every fixed left column separator in the grid view.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* fixedLeftColumnSeparatorColor;

/** The width of the fixed left column separator
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat fixedLeftColumnSeparatorWidth; 

///---------------------------------------------------------------------------------------
/// @name Fixed Right Column
///---------------------------------------------------------------------------------------

/** The background color of an IGGridViewCell that is fixed to the right of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIColor* fixedRightCellBackgroundColor;

/** The text color of an IGGridViewCell that is fixed to the right of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIColor* fixedRightCellTextColor;

/** The UIFont of an IGGridViewCell that is fixed to the right of the IGGridView.
 
 This property will only take effect if you're uing one of the IGGridViewDataSourceHelper classes along with one of the built in IGGridViewColumnDefinition objects.
 */
@property(nonatomic, readonly)UIFont*  fixedRightCellFont;

/** The UIColor of every fixed right column separator in the grid view.
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)UIColor* fixedRightColumnSeparatorColor;

/** The width of the fixed right column separator
 
 This property will override the grid level version of this property.
 */
@property(nonatomic, readonly)CGFloat fixedRightColumnSeparatorWidth; 

///---------------------------------------------------------------------------------------
/// @name Delete Button
///---------------------------------------------------------------------------------------

/** An array of CGColors used to create a gradient background for the delete row button that is displayed when swipeRowAction property of the grid view is set to: IGGridViewSwipeRowActionDeleteButton.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)NSArray* deleteButtonBackgroundColors;

/** The UIColor used for the text of the delete row button that is displayed when swipeRowAction property of the grid view is set to: IGGridViewSwipeRowActionDeleteButton.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIColor* deleteButtonTextColor;

/** The UIFont used for the delete row button that is displayed when swipeRowAction property of the grid view is set to: IGGridViewSwipeRowActionDeleteButton.
 
 This property only exists on the theme.
 */
@property(nonatomic, readonly)UIFont* deleteButtonFont;

///---------------------------------------------------------------------------------------
/// @name Editing
///---------------------------------------------------------------------------------------

/** The UIColor used for the background of a text field of a cell in edit mode.
 
 This property only exists on the theme. If you provide a custom editor, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* editCellTextFieldBackgroundColor;

/** The UIFont used for the text field of a cell in edit mode.
 
 This property only exists on the theme. If you provide a custom editor, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIFont* editCellTextFieldFont;

/** The UIColor used for the text of a text field of a cell in edit mode.
 
 This property only exists on the theme. If you provide a custom editor, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)UIColor* editCellTextFieldTextColor;


@end

/*! A predefined Theme using with white colored cells
 */
@interface IGGridViewLightTheme : NSObject<IGGridViewThemeDefinition>
@end

/*! A predefined Theme using with dark colored cells
 */
@interface IGGridViewDarkTheme : NSObject<IGGridViewThemeDefinition>
@end



