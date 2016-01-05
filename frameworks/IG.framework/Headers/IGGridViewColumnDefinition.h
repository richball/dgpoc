//
//  IGGridViewColumnDefinition.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGGridViewCell.h"
#import "IGGridViewDataSourceHelper.h"

@class IGGridViewDataSourceHelper;

/*! IGGridViewColumnDefinition is an object that is used by the IGGridViewDataSourceHelper classes to identify properties on the underlying data objects.
 
 For example, if I had an array of objects of type MyClass. And MyClass had three properties: firstName, lastName and age. I could create a column definition for my firstName property:

 `colDef = [[IGGridViewColumnDefinition alloc] initWithKey:@"firstName"];`
 
 `colDef.headerText = "@First Name";`
 
 The real benefits of using column definitions comes with the ability to create your own derived versions that override the gridView:createCell:usingDataSource: method. By doing so, you can specify any custom cell that you want to display in the column. For example: the IGGridViewImageColumnDefinition creates a column that uses the IGGridViewImageCell.
 
 Note: when deriving your own column defition, you should follow the same practice of using the grid view's dequeueReusableCellWithIdentifier: method.
 
 */
@interface IGGridViewColumnDefinition : NSObject<NSCoding>
{
    NSString* _fieldKey;
}

///---------------------------------------------------------------------------------------
/// @name Configuring the Column Definition
///---------------------------------------------------------------------------------------

/** Creates an IGGridViewColumnDefinition for the specified property name.
 
 @param key A string that maps to an actual property on your underlying data object.
 @return Returns an initialized IGGridViewColumnDefinition object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithKey:(NSString*)key NS_DESIGNATED_INITIALIZER;

/** The name of the property that this column definition represents (readonly)
 
 */
@property(nonatomic, retain, readonly) NSString* fieldKey;

/** The value that should be display in the header of the IGGridView for this column.
 
 */
@property(nonatomic, retain) NSString* headerText;

/** The font color of the text field.
 
 */
@property(nonatomic, retain)UIColor* textColor;

/** The font of the text field.
 
 */
@property(nonatomic, retain)UIFont* textFont;

/** The alignment of the text field.
 
 */
@property(nonatomic, assign)NSTextAlignment textAlignment;


/** The alignment of the header text field.
 
 */
@property(nonatomic, assign)NSTextAlignment headerTextAlignment;


/** The background color for every cell in the column.
 
 */
@property(nonatomic, retain )UIColor* backgroundColor;

/** The width of the column. The default is nil.
 
 Note: This has lower priority than if the delegate specifies the width for the column.
 
 */
@property(nonatomic, retain)IGColumnWidth* width;

///---------------------------------------------------------------------------------------
/// @name Editing
///---------------------------------------------------------------------------------------

/** Determines whether this particular column can be put into edit mode. 
 */
@property(nonatomic, assign)BOOL editable;

/** Asks the column definition to display an editor for a cell.
 
 @param gridView The grid view requesting the cell to be placed in edit mode.
 @param path The path of the cell that should be placed in edit mode. 
 @param dataSource The IGGridViewDataSourceHelper that has invoked this method.
 */
-(void)gridView:(IGGridView*)gridView displayEditorForCell:(IGCellPath*)path usingDataSource:(IGGridViewDataSourceHelper*)dataSource;

/** Asks the column definition to remove its editor.
 
 @param gridView The grid view requesting the editor to be removed.
 @param path The path of the cell that is currently in edit mode.
 @param dataSource The IGGridViewDataSourceHelper that has invoked this method.
 @param cellVisible Tells the method whether the cell that was in edit mode is still in the grid's viewport.
 @param anotherCellEnteringEditMode Tells the method whether this cell is exiting edit mode b/c another cell is currently in edit mode. 
 */
-(void)gridView:(IGGridView *)gridView removeEditorForCell:(IGCellPath *)path usingDataSource:(IGGridViewDataSourceHelper *)dataSource isCellStillVisible:(BOOL)cellVisible isAnotherCellEnteringEditMode:(BOOL)anotherCellEnteringEditMode;


///---------------------------------------------------------------------------------------
/// @name Protected Members
///---------------------------------------------------------------------------------------


/** Asks the column definition for a cell to place at a particular location in the grid view.
 
 The returned IGGridViewCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCell. 
 
 @param gridView The grid view requesting the cell.
 @param path The path of the cell that is needed
 @param dataSource The IGGridViewDataSourceHelper that has invoked this method.
 @return An object inheriting IGGridViewCell that the grid view can use for the specified location. 
 */
-(IGGridViewCell*)gridView:(IGGridView*)gridView createCell:(IGCellPath*)path usingDataSource:(IGGridViewDataSourceHelper*)dataSource;

/** Asks the column definition for a header cell to place at a particular location in the grid view.
 
 The returned IGGridViewHeaderCell object is frequently one that the application reuses for performance reasons. You should fetch a previously created cell object that is marked for reuse by sending a dequeueResuableCellWithIdentifier: message to the grid view. The identifier for a reusable cell object is assigned when the the initWithStyle:reuseIdentifier: method of the IGGridViewCell.
 
 @param gridView The grid view requesting the cell.
 @param dataSource The IGGridViewDataSourceHelper that has invoked this method.
 @return An object inheriting IGGridViewHeaderCell that the grid view can use for the specified location.
 */
-(IGGridViewHeaderCell*)gridView:(IGGridView*)gridView createHeaderCellUsingDataSource:(IGGridViewDataSourceHelper*)dataSource;

/** Sets the text provided to the cell's text label.
 
 This method allows a cell to be updated properly. Especially if there is a filter applied and a special string attributes such as font color should be applied to the cell's text.
 
 @param text The text to be set on the cell.
 @param cell The cell that should be updated.
 @param dataSource The datasource being used.
 */
-(void)setText:(NSString*)text onCell:(IGGridViewCell*)cell forDataSource:(IGGridViewDataSourceHelper*)dataSource;

/** Call this from a derived class to ensure the proper styling is applied to your cell.
 
 @param cell The cell that should be updated.
 @param rowIndex The index of the row for the cell beging updated.
 @param gridView The gridView that the cell belongs to.
 */
-(void)applyStylingToCell:(IGGridViewCell*)cell AtRow:(NSInteger)rowIndex inGrid:(IGGridView*)gridView;

/** Given an object, it returns a string value of the underlying property this column represents.
 
If your derived column is not representing a property, you should override this to resolve the correct value
 
 @param obj The underlying data object mapped to the cell.
 @param dsh The IGGridViewDataSourceHelper that this column belongs to. 
 @return A string representation of the value that this column represents.
 
 */
-(NSString*)resolveValueForObject:(id)obj inDataSource:(IGGridViewDataSourceHelper*)dsh;


/** Asks the column what the height that this column needs for a given row.
 
 This method is only invoked if the IGGridViewDataSourceHelper is resolving
 
 @param path The section and row whose height is being asked for.
 @param gridView The IGGridView that this column belongs to.
 @param width The actual width value of the column.
 @param dataSource The IGGridViewDataSourceHelper that this column belongs to.
 @return The total height for the content being displayed in this column given the specific row and section.
 
 */
-(CGFloat)resolveHeightforPath:(IGRowPath*)path inGrid:(IGGridView*)gridView usingWidth:(CGFloat)width inDataSource:(IGGridViewDataSourceHelper*)dataSource;

@end


/*! IGGridViewValueColumnDefinition is an object that is used by the IGGridViewDataSourceHelper classes to identify properties on the underlying data objects.
 
This particular column definition object is used to represent the entire underlying data object, and not a specific property off of the object. This is useful if your data, is just an array of numbers or strings, and you don't need to display extra columns.
 
To filter or group by this the entire data object, the key that should be use is "self". 
 
    dataSourceHelper.filteringKey = @"self";
    dataSourceHelper.groupingKey = @"self";
 
 */
@interface IGGridViewValueColumnDefinition : IGGridViewColumnDefinition 


@end


typedef NS_ENUM(NSInteger, IGGridViewImageColumnDefinitionPropertyType)
{
    IGGridViewImageColumnDefinitionPropertyTypeStringUrl,
    IGGridViewImageColumnDefinitionPropertyTypeURL,
    IGGridViewImageColumnDefinitionPropertyTypeData,
    IGGridViewImageColumnDefinitionPropertyTypeImage
    
};

@class IGGridViewCell;

/*! IGGridViewImageColumnDefinition is an object that is used by the IGGridViewDataSourceHelper classes to identify properties that represent images.
 
 This column definition supports 4 different type of data properties:
        - String url
        - NSURL
        - NSData object
        - UIImage object
 
 The type of cell that is returned is of type IGGridViewImageCell. 
 
 You can use this class to configure how the image will load, and even whether to enable zooming.
 
 Note: not all features are available for all images types.
    - cacheImages is only supported for url type images
    - loadAsync is only supported for properties of type UIImage and NSData
    - preloadImagePath must be a property type of UIImage or NSData, and much be the same type as the property this column definitions represents.
 
 */
@interface IGGridViewImageColumnDefinition : IGGridViewColumnDefinition 
{
    NSMutableDictionary* _cachedImages;
    IGGridViewImageColumnDefinitionPropertyType _propertyType;
}

///---------------------------------------------------------------------------------------
/// @name Configuring the Column Definition
///---------------------------------------------------------------------------------------

/** Creates an IGGridViewImageColumnDefinition for the specified property name.
 
 @param key A string that maps to an actual image type property on your underlying data object.
 @param type A value that describes the type of property that this column definitions represents.
 @return Returns an initialized IGGridViewImageColumnDefinition object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithKey:(NSString*)key forPropertyType:(IGGridViewImageColumnDefinitionPropertyType)type NS_DESIGNATED_INITIALIZER;

/** A value that describes the type of property that this column definitions represents. (readonly)
 */
@property(nonatomic, assign, readonly)IGGridViewImageColumnDefinitionPropertyType propertyType;

/** A value that determines if zooming is enabled on the IGGridViewImageCell
 
 See the IGGridViewImageCell's enableZooming property for more information.
 */
@property(nonatomic, assign)BOOL enableZooming;

/** The name of the property that should be used to display text for the image provided.
 
 */
@property(nonatomic, retain)NSString* textFieldKey;

/** The amount of space between the text field and the image.
 
 */
@property(nonatomic, assign)CGFloat textPadding;

///---------------------------------------------------------------------------------------
/// @name Image Loading Options
///---------------------------------------------------------------------------------------

/** Gets or sets whether a url type image should be cached by the column definition, for faster loading times when the cell comes back into view.
 */
@property(nonatomic, assign)BOOL cacheImages;

/** Gets or sets whther a NSData or UIImage should be loaded on a background thread
 
 */
@property(nonatomic, assign)BOOL loadAsync;

/** Gets or sets an interval for how long it should take to fade an image into view, once the cell becomes visible.
 
 The default is 0, which means no animation.
 */
@property(nonatomic, assign)NSTimeInterval fadeImageInterval;

/** Gets or sets the contentMode of the imageView
 
 The default is: UIViewContentModeScaleAspectFit
 
 */
@property(nonatomic, assign)UIViewContentMode contentMode;

@end

