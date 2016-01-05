//
//  IGGridViewDataSourceHelper.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGGridView.h"

typedef NS_ENUM(NSInteger, IGGridViewFilterConditionType)
{
    IGGridViewFilterConditionTypeStringContains,
    IGGridViewFilterConditionTypeStringBeginsWith,
    IGGridViewFilterConditionTypeStringEndsWith,
    IGGridViewFilterConditionTypeStringLike,
    IGGridViewFilterConditionTypeStringMatches,
    IGGridViewFilterConditionTypeNumberEquals, 
    IGGridViewFilterConditionTypeNumberNotEquals, 
    IGGridViewFilterConditionTypeNumberGreaterThan,
    IGGridViewFilterConditionTypeNumberGreaterThanEquals,
    IGGridViewFilterConditionTypeNumberLessThan,
    IGGridViewFilterConditionTypeNumberLessThanEquals
    
};

typedef NS_ENUM(NSInteger, IGGridViewSortedColumnDirection)
{
    IGGridViewSortedColumnDirectionNone,
    IGGridViewSortedColumnDirectionAscending,
    IGGridViewSortedColumnDirectionDescending
    
};


@class IGGridViewDataSourceHelper;

/*! The IGGridViewDataSourceHelperLoadMoreDelegate protocol provides information to a IGGridViewDataSourceHelper regarding information about loading more rows. 
 
 If you've ever used an ios app where you've scrolled down to the bottom, and the last rows says "Load More Rows" or "Loading More Rows", this is feature. 
 
 When a IGGridViewLoadMoreCell comes into view, the loadMoreRows: selector is raised, which tells the application that more rows need to be requested. They can the update their data source
 and let the the datasource helper know that more rows have been retrieved. At that point the needMoreRows: method is raised, which asks if the load more cell should be displayed anymore. 
 
 An example implementation would look something like this:
 
        -(IGGridViewLoadMoreCell *)cellForLoadingMore:(IGGridView *)gridView 
        {
            NSString* lookup = @"LOAD_MORE";
            IGGridViewLoadMoreCell *cell = [gridView dequeueReusableCellWithIdentifier:lookup];
            if (cell == nil) 
                cell = [[IGGridViewLoadMoreCell alloc] initWithReuseIdentifier:lookup];

            cell.textLabel.textAlignment = UITextAlignmentCenter;
            cell.textLabel.text = @"Loading More Movies...";
 
            return cell;
        }
 
        -(BOOL)needMoreRows:(IGGridViewDataSourceHelper *)dataSource
        {
            return (dataSource.data.count < 200);
        }
 
        -(void)loadMoreRows:(IGGridViewDataSourceHelper *)dataSource
        {
            [self makeRequestToGetMoreRows:@selector(gotMoreRows:)];
        }
 
        -(void)gotMoreRows:(NSArray*)newData
        {
            IGGridViewDataSourceHelper* dataSource = _gridView.dataSource;
            [dataSource appendData:newData];
            [_gridView updateData];
        }
 
 */
@protocol IGGridViewDataSourceHelperLoadMoreDelegate <NSObject>

/** Tells the delegate that a request has been made and it needs to load more rows.
 
 @param dataSource The IGGridViewDataSourceHelper that made this call.
 */
-(void)loadMoreRows:(IGGridViewDataSourceHelper*)dataSource;

/** Provides the IGGridViewDataSourceHelper with a cell to be display to load more rows. 
 
 @param gridView The IGGridView that the cell will be displayed in.
 @return A IGGridViewLoadMoreCell that will be displayed to indicate that more rows are being loaded. 
 */
- (IGGridViewLoadMoreCell *) cellForLoadingMore:(IGGridView *)gridView;

/** Tells the delegate whether more rows are needed
 
 @param dataSource The IGGridViewDataSourceHelper that made this call.
 @return Yes if more rows are needed, or NO if all the data is on the client.
 */
-(BOOL)needMoreRows:(IGGridViewDataSourceHelper*)dataSource;

@end

@class IGGridViewColumnDefinition;

/*! The IGGridViewDataSourceHelperEditingDelegate protocol provides a hook into editing.
 
 You can use these hooks to modify the editor thats used, or even update the value in the underlying data object.

 */
@protocol IGGridViewDataSourceHelperEditingDelegate <NSObject>

@optional

/** Invoked when a cell is about to enter edit mode. 
 
 You can use this method to update the display data, or make changes to the editor. 
 
 @param dsh The IGGridViewDataSourceHelper entering edit mode.
 @param cell The IGGridViewCell entering edit mode. 
 @param value The value that will be put in the editor. (In the case of an IGGridViewColumn, the value will be a string)
 @param editor The editor that will be displayed. 
 @param col The column entering edit mode. 
 */

-(void)dataSourceHelper:(IGGridViewDataSourceHelper*)dsh cellEnteringEditMode:(IGGridViewCell*)cell usingValue:(id)value withEditor:(UIView*)editor forColumn:(IGGridViewColumnDefinition*)col;

/** Invoked when a cell is about to exit edit mode.
 
 You can use this method to do validation, or update the value that will be set on the cell.
 
 @param dsh The IGGridViewDataSourceHelper exiting edit mode.
 @param cell The IGGridViewCell exiting edit mode.
 @param value The value from the editor.
 @param editor The editor that was used for editing.
 @param col The column exiting edit mode.
 @return The value that will be set on the underlying data object. If you want to use the editor's value, just return value.
 */
-(id)dataSourceHelper:(IGGridViewDataSourceHelper*)dsh cellExitingEditMode:(IGGridViewCell*)cell usingValue:(id)value withEditor:(UIView*)editor forColumn:(IGGridViewColumnDefinition*)col;

@end


/*! The IGGridViewDataSourceHelper is basically just what it sounds like. If you're just trying to display an array of your custom objects, then it can be quite
 tedious to re-implement the IGGridViewDataSource protocol for every IGGridView you've implemented. The purpose of this class is to save you from writing a bunch of extra code. 
 
 You simply set the data property and you're done. The data source will automatically walk your objects and create a column for every public property. If you don't want it to do that, you can set the autoGenerateColumns property to NO, and specify the columns in your own order using the columnDefinitions property and adding your IGGridViewColumnDefinition objects to the array.
 
 The datasource helper class will even group your data for sections. All you need to do is set the groupingKey property to the name of a property on your custom object. For example, say I have an object call MyData. On MyData I have three properties: firstName, lastName and age. If I wanted to organize my data into sections based on the lastName, I would simply do the following:
        dataSource.groupingKey = @"lastName";
 
 Likewise, if i'd like to enable filtering on my IGGridView, I can set the filteringKey property. So, to filter the data by firstName, I would do the following.
        datasource.filteringKey= @"firstName";
 
 The dataSource helper, even makes it easy to enable features such as displaying section header and footers, row reordering, or even the shortcut bar, simply by setting YES or NO on a few properties. 
 
 If you want to find the direct mapping of a IGCellPath or IGRowPath to your actual objects, you can use the resolve methods exposed on this class.
 
 However, the real power is the ability to reorganzie your data into different ways. For example: the IGGridViewSingleRowSingleFieldDataSourceHelper class will actually flip your rows into columns. To create your own DataSourceHelper class is actually rather simple. You can override any of the IGGridViewDataSource protocol methods, and if you change how the data maps to the IGCellPath objects, you can simply override the normalizePath method to map a cell path back to your data.
 */
@interface IGGridViewDataSourceHelper : NSObject<IGGridViewDataSource>
{
    NSArray* _data;
    NSMutableArray* _columns; 
    NSMutableArray* _columnTypes;
    NSMutableArray* _sections;
    NSDictionary* _sectionData;
    NSArray* _displayData;
    NSString* _filterText;
    NSMutableArray* _fieldsToIgnore;
    NSMutableArray* _columnDefinitions;
}

///---------------------------------------------------------------------------------------
/// @name Configuring Data
///---------------------------------------------------------------------------------------

/** Gets or sets the array of data that will be consumed by the IGGridViewDataSourceHelper

 As of right now, the data must be of a derivation of NSObject and have at least one property.
 */
@property(nonatomic, retain) NSArray* data;

/** Gets or sets a string that represents a property on the underlying data objects. 
 
 The data is in the grouped by unique values of this property in the array of data that was assigned to the datasource
 Note if you want the data to be grouped by the entire object, i.e. your data is an array of strings, you should set the value of the property to "self"
 */
@property(nonatomic, retain) NSString* groupingKey;

/** The direction in which data should be sorted for the grouping of data specified by the groupingKey
 
 The default is IGGridViewSortedColumnDirectionAscending.
 */
@property(nonatomic, assign)IGGridViewSortedColumnDirection groupingSortDirection;

/** Whether the sorting of sections should use a case insensitive sort
 */
@property(nonatomic, assign)BOOL groupingSortCaseInsensitive;
    
/** A boolean value that determines whether section headers will respond to taps so that the user can expand/collapse a section
 
 The default is NO.
 */
@property(nonatomic, assign)BOOL allowSectionExpansion;

/** A boolean value that controls whether columns will automatically be created by looking at the properties of the underlying data objects.
 
 */
@property(nonatomic, assign) BOOL autoGenerateColumns;

/** A collection of developer specified IGColumnDefinition objects that should be displayed in the IGGridView
 
 */
@property(nonatomic, readonly) NSMutableArray* columnDefinitions;

/** A collection of strings that map to properties in the underlying data object that should not be autogenerated
 
 */
@property(nonatomic, readonly) NSMutableArray* fieldsToIgnore;

/** A collection of developer specified IGGridViewSortedColumn objects in the order in which the data should be sorted by.
 
 The first IGGridViewSortedColumn in the collection will have the highest priority. If the data is grouped using the groupingKey property, then the field being grouped will 
 have the highest priority. To control the direction of the grouped field, use the groupingSortDirection property.
 */
@property(nonatomic, readonly) NSMutableArray* sortedColumns;


/** Inserts the specified IGGridViewColumnDefinition objects at the specified index.
 
 @param columns An array of IGGridViewColumnDefinition objects to insert into the grid view.
 @param index The index in which to insert the columns.
 */
-(void)insertColumns:(NSArray*)columns atIndex:(NSInteger)index;

/** Deletes the specified IGGridViewColumnDefinition objects.
 
 @param columns An array of IGGridViewColumnDefinition objects to remove from the grid view.
 */
-(void)deleteColumns:(NSArray*)columns;

/** A boolean value that controls whether the dataSource helper will determine the height of each row so that each column's content is completely visible
*/
@property(nonatomic, assign)BOOL dynamicRowHeight;

///---------------------------------------------------------------------------------------
/// @name Setup whats displayed
///---------------------------------------------------------------------------------------

/** Gets or sets whether the shortcut bar should be displayed. 
 
 If set to YES the groupingKey must also be set, in order for the shortcutbar to be displayed.
 */
@property(nonatomic, assign) BOOL displayShortcutbar;

/** Gets or sets whether the headers for sections should be displayed
 
 The groupingKey must also be set.
 */
@property(nonatomic, assign) BOOL sectionFooterEnabled;

/** Gets or sets whether the footers for sections should be displayed
 
 The groupingKey must also be set.
 */
@property(nonatomic, assign) BOOL sectionHeaderEnabled;

/** Gets or sets whether row reordering is allowed for this data
 
 You would still have to turn on row reordering on the IGGridView to turn on ths feature, this just gives you the option to override it on the datasource level, and say that its not supported. 
 */
@property(nonatomic, assign) BOOL allowRowReordering;

/** YES if column reordering is allowed, or NO if it is not.
 
 */
@property(nonatomic, assign) BOOL allowColumnReordering;

///---------------------------------------------------------------------------------------
/// @name Data Updates
///---------------------------------------------------------------------------------------

/** Takes the newly specified data, and appends it to the original data provided to the datasource helper.
 
 @param newData An array of data that should be appended to the end of the data already assigned to the datasource helper.
 */
-(void)appendData:(NSArray*)newData;

/** Tells the datasource helper to revaulate its data. 
 
 Such as calcuating the secions, applying a filter or sort, calculating how many rows are in the datasource and even regenerating columns.
 
 */
-(void)invalidateData;

/** Tells the datasource helper to revaulate its data.
 
 Such as calcuating the secions, applying a filter or sort, calculating how many rows are in the datasource and even regenerating columns.
 
 @param invalidateColumns YES if columns should be reset and regenerated.
 
 */
-(void)invalidateData:(BOOL)invalidateColumns;

///---------------------------------------------------------------------------------------
/// @name Data Manipulation
///---------------------------------------------------------------------------------------

/** Gets or sets the type of animation that will occur when you delete a row.

 */
@property(nonatomic, assign) IGGridViewAnimation deleteRowAnimation;


/** Deletes the specified rows, and animates them based on the specified deleteRowAnimation.
 
 @param gridView The gridView to update.
 @param paths A list of row paths to delete.
 
 */
-(void)gridView:(IGGridView *)gridView deleteRowsAtPaths:(NSArray*)paths;

///---------------------------------------------------------------------------------------
/// @name Data Access
///---------------------------------------------------------------------------------------

/** Given an IGCellPath, it identifies the data object and specific property value.
 
 @param path An IGCellPath that maps to a cell in the IGGridView.
 @return The property value for the given path. 
 */
-(id)resolveDataValueForCell:(IGCellPath*)path;


/** Given an IGRowPath, it identifies the data object at that position in the array.
 
 @param path An IGRowPath that maps to a row in the IGGridView.
 @return The an item from the array assigned to the datasource.
 */
-(id)resolveDataObjectForRow:(IGRowPath*)path;

/** Does a reverse lookup to find the cell for the specified value
 
 @param data The data object to look up in the array of data assigned to datasource
 @return A path to the cell location of the specified data object, or nil if it isn't found.
 
 */
-(IGCellPath*)resolveCellPathForData:(NSObject*)data;

/** A readonly list that provides the data currently being dislayed. 
 
 This is useful for example if you've filtered your data, displayData would contain just the items that match the filter. 
 Note: it only contains data when there are no sections, i.e. the goupingKey property is not set. 
 */
@property(nonatomic, readonly) NSArray* displayData;

/** A readonly list that contains all of the unique keys used for the sections. 
 
 These are the values that will be used in the shortcutbar. Note this property only is set when there is a groupingKey provided.
 
 */
@property(nonatomic, readonly) NSArray* sections;

/** A readonly list of IGGridViewColumnDefinition objects that represent all the columns that will be displayed by the datasource. 
 
 This list contains both the columns specified in the columnDefinitions property and any autoGeneratedColumns.
 */
@property(nonatomic, readonly) NSArray* columns;

/** A readonly dictionary, where the key is each value in the sections property, that contains a list of data for that section 
 
 */
@property(nonatomic, readonly) NSDictionary* sectionData;


///---------------------------------------------------------------------------------------
/// @name Load More
///---------------------------------------------------------------------------------------

/** A delegate for loading more rows. 
 
 Check out the IGGridViewDataSourceHelperLoadMoreDelegate documentation for more details.
 */ 
@property(nonatomic, assign) id<IGGridViewDataSourceHelperLoadMoreDelegate> loadMoreDelegate;


///---------------------------------------------------------------------------------------
/// @name Filtering
///---------------------------------------------------------------------------------------

/** Gets or sets a string that represents a property on the underlying data objects.
 
 The data can then be filterd by the specified property. 
 Note if you want the data to be filterd by the entire object, i.e. your data is an array of strings, you should set the value of the property to "self"*/
@property(nonatomic, retain) NSString* filteringKey;

/** Gets or sets a Boolean value that determines if filtering will be case insensitive.
 
 The default value is YES.
 */
@property(nonatomic, assign)BOOL filteringCaseInsensitivity;

/** Gets or sets a Boolean value that determines if filtering will be diacritic insensitive.
 
 For example: Two diacritics appear in the word “déjà vu, when YES, they would be ignored. The default value is YES.
 */
@property(nonatomic, assign)BOOL filteringDiacriticInsensitiveFiltering;

/** Gets or sets the type of filtering condition that will be applied to the property associated with the filteringKey. 
 
 The default is IGGridViewFilterConditionTypeStringContains.
 */
@property(nonatomic, assign)IGGridViewFilterConditionType filterType;

/** The value that the datasource is currently filtered by.
 
 This property is readonly. 
 */
@property(nonatomic, readonly)NSString* filterValue;

/** A readonly dictionary, that can be used in iOS 6 and greater to highlight the text that applies to the filter.
 
 */
@property(nonatomic, readonly) NSDictionary* filterAttributes NS_AVAILABLE_IOS(6_0);

/** Gets or sets the string that will be displayed in the shortcutbar.
 
 The default is a magnifying glass.
 */
@property(nonatomic, retain)NSString* filterShortcutbarValue;

/** Removes any filters applied to the DataSource and clears our the values in the FilterCell,
 
 @param gridView The IGGridView requesting the action.
 */
-(void)clearFilter:(IGGridView*)gridView;

/** Given the specified filter value, the DSH will set the value to the filter cell and apply to the grid
 
 @param gridView The IGGridView requesting the action.
 @param filterText The text that should be filtered on.
 */
-(void)gridView:(IGGridView *)gridView applyFilter:(NSString *)filterText;

///---------------------------------------------------------------------------------------
/// @name Fixed Columns
///---------------------------------------------------------------------------------------

/** A list of IGGridViewColumnDefinition objects that represent columns pinned to the left of the grid view.
 */
@property(nonatomic, readonly) NSMutableArray* fixedLeftColumns;

/** A list of IGGridViewColumnDefinition objects that represent columns pinned to the right of the grid view.
 */
@property(nonatomic, readonly) NSMutableArray* fixedRightColumns;

///---------------------------------------------------------------------------------------
/// @name Fixed Rows
///---------------------------------------------------------------------------------------

/** Gets or sets the array of data that will be used for displaying FixedRows.
 
 The objects in the array should be of the same type as data.
 */
@property(nonatomic, retain) NSArray* fixedRowData;

/** Fixes the specifeid row to the top of the Grid.
 
 @param gridView The gridView to update.
 @param path The path of a non fixed row that should be fixed.
 
 */
-(void)gridView:(IGGridView*)gridView addFixedRowAtPath:(IGRowPath *)path;

/** Removes the fixed row from the top of the grid.
 
 @param gridView The gridView to update.
 @param paths The fixed row path that should no longer be fixed.
 
 */
-(void)gridView:(IGGridView*)gridView removeFixedRowAtPath:(IGRowPath*)path;


///---------------------------------------------------------------------------------------
/// @name Editing
///---------------------------------------------------------------------------------------

/** Gets or sets whether a cell can enter edit mode via a double tap. 
 */
@property(nonatomic, assign)BOOL allowEditing;

/** Gets or sets the time in seconds it takes for a cell to animate into edit mode and exit edit mode. 
 
 Note: it is up to the IGGridViewColumnDefintion to apply this property.
 */
@property(nonatomic, assign)CGFloat editingTransitionDuration;

/** Gets or sets the transition for a cell to enter edit mode.
 
 Note: it is up to the IGGridViewColumnDefintion to apply this property.
 */
@property(nonatomic, assign)UIViewAnimationOptions editingStartTransitionOptions;

/** Gets or sets the transition for a cell to exit edit mode.
 
  Note: it is up to the IGGridViewColumnDefintion to apply this property.
 */
@property(nonatomic, assign)UIViewAnimationOptions editingEndTransitionOptions;

/** A delegate for editing cells.
 
 Check out the IGGridViewDataSourceHelperEditingDelegate documentation for more details.
 */
@property(nonatomic, assign) id<IGGridViewDataSourceHelperEditingDelegate> editingDelegate;

/** Checks to see if a cell in the grid is currently being edited
 */
@property(nonatomic, readonly)BOOL isEditing;

/** Exits edit mode.
 
 */
-(void)endEditing;

/** Puts the specified cell into edit mode if it supports editing. 
 
 If a cell is already in edit mode, that cell will exit edit mode first. If the specified cell is not in view, it will be scrolled into view.
 
 @param cellPath The path of the cell to put into edit mode.
 @param gridView The gridView in which to resolve the cell.
 */
-(void)beginEditing:(IGCellPath*)cellPath inGrid:(IGGridView*)gridView;

///---------------------------------------------------------------------------------------
/// @name Protected Overrides
///---------------------------------------------------------------------------------------

/** Given a IGCellPath it is converted to a path that realistically maps to the underlying data. 
 
 This should be overriden if you change how your data is being displayed, for example if you swapped rows and columns 
 
 @param path An IGCellPath that maps to a cell in the IGGridView.
 @return An IGCellPath that has been converted to map to an actuall item in your data source.
 
 */
-(IGCellPath*)normalizePath:(IGCellPath*)path;

/** Given a IGCellPath that maps to the underlying data, it converts it to a path that maps to the display.
 
 This should be overriden if you change how your data is being displayed, for example if you swapped rows and columns 
 
 @param path An IGCellPath that maps to the underlying data.
 @return An IGCellPath that has maps to a cell in the grid.
 
 */
-(IGCellPath*)deNormalizePath:(IGCellPath*)path;


/** When overriden, a developer can provide their own custom filtering to the data.
 
 This should be overriden if you want to provide your own custom filtering.
 
 @param value The string that the data should be filtered by.
 @param dataToFilter An NSArray that contains the data that should be filtered.
 @return An array of filtered data. 
 
 */
-(NSArray*)applyFilterForValue:(NSString*)value toData:(NSArray*)dataToFilter;

/** When overriden, a developer can sort the data on their own.
 
 This should be overriden if you want to provide your own custom sorting.
 
 @param sortKey The field that the data should be sorted on
 @param dataToSort An NSArray that contains the data that should be sorted.
 @param ascending Whether the data should be sort ascending or descending.
 @param caseInsensitive Whether the sort operation should be case insensitive.
 @return An array of sorted data.
 
 */
-(NSArray*)applySort:(NSString*)sortKey toData:(NSArray*)dataToSort ascending:(BOOL)ascending caseInsensitive:(BOOL)caseInsensitive;


@end

/*! IGGridViewSortedColumn is an object that is used by the IGGridViewDataSourceHelper classes to identify fields that should be sorted.
 
 You can use the sortDirection property to determine the direction in which a particular field should be sorted.
 
 */
@interface IGGridViewSortedColumn : NSObject

/** Creates an IGGridViewSortedColumn for the specified property name and direction.
 
 @param field A string that maps to an actual property on your underlying data object.
 @param direction The direction in which the data should be sorted for that field.
 @return Returns an initialized IGGridViewSortedColumn object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithField:(NSString*)field forDirection:(IGGridViewSortedColumnDirection)direction NS_DESIGNATED_INITIALIZER;

/** The direction that the data for the field should be sorted in.
 
 */
@property(nonatomic, assign) IGGridViewSortedColumnDirection sortDirection;

/** Whether or not a sort operation should be case insensitive
 */
@property(nonatomic, assign)BOOL useCaseInsensitiveSort;

/** The name of the property that should be sorted (readonly)
 
 */
@property(nonatomic, readonly) NSString* fieldName;

@end
