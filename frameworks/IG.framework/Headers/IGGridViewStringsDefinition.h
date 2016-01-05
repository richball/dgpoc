//
//  IGGridViewStringsDefinition.h
//
//  Copyright (c) 2012 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 The IGGridViewStringsDefinition protocol is adopted by an object that replaces default strings off various objects in the IGGridView object.
 
 All methods and properties in this protocol are optional.
  
 */
@protocol IGGridViewStringsDefinition <NSObject>

@optional

/** The string used for the placeholder text of the filter cell. 
 
 The default value is "Search"
 
 If you provide a custom filter cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)NSString* filterPlaceholderText;

/** The text used for the delete row button that is displayed when swipeRowAction property of the grid view is set to: IGGridViewSwipeRowActionDeleteButton.
 
 The IGGridViewDelegate method gridView:titleForDeleteConfirmationButtonForRowAtPath: has higher precedence.
 */
@property(nonatomic, readonly)NSString* deleteButtonText;

/** The text that is used in the displayLabel of the PullDownRow when the cell is in it's PullDown state.
 
 If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)NSString* pullDownText;

/** The text that is used in the displayLabel of the PullDownRow when the cell is in it's Release state
 
 If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)NSString* pullDownReleaseText;

/** The text that is used in the displayLabel of the PullDownRow when the cell is in it's Updating state
 
 If you provide a custom pull down cell, this property will take no effect, unless implemented manually.
 */
@property(nonatomic, readonly)NSString* pullDownUpdatingText;

@end

/*!
 A Japanese Translation of all strings in the IGGridView.
 */
@interface IGGridViewJapaneseStrings : NSObject<IGGridViewStringsDefinition>
@end

/*!
 An English Translation of all strings in the IGGridView.
 */
@interface IGGridViewEnglishStrings : NSObject<IGGridViewStringsDefinition>
@end

