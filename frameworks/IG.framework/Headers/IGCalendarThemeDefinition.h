//
// IGCalendarThemeDefinition.h
//
//  Copyright (c) 2013 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, IGCalendarWeekDayDisplayType)
{
    IGCalendarWeekDayDisplayTypeShort,
    IGCalendarWeekDayDisplayTypeVeryShort
    
};

typedef NS_ENUM(NSInteger, IGCalendarAppointmentRequestType)
{
    IGCalendarAppointmentRequestTypeMonth,
    IGCalendarAppointmentRequestTypeDay
    
};



/*!
 The IGCalendarThemeDefinition protocol is adopted by an object that mediates key styling points of a IGCalendarView object. The theme provides the calendar view object with the information it needs to style specific areas of the calendar view.
 
 All methods and properties in this protocol are optional.
 
 The protocol is designed to simplify whats neccessary. For example, you don't need to provide all the font sizes used by calendar. Instead you provide a range, which is used to calculate the font size that should be used in various areas of the calendar. The same goes with colors and fonts.
 
 If an option is not provided the default theme will be used.
 */
@protocol IGCalendarThemeDefinition <NSObject>

@optional

/** The name of a font that represents objects such as title bar text.
 */
@property(nonatomic, readonly)NSString* fontNameNormal;

/** The name of a font that represents objects such as appointment text.
 */

@property(nonatomic, readonly)NSString* fontNameHeavy;

/** The name of a font that represents objects such as day numbers.
 */
@property(nonatomic, readonly)NSString* fontNameLight;

/** The FontSize of the year displayed in the IGCalendarViewDisplayTypeYear
 */
@property(nonatomic, readonly)CGFloat fontSizeYearLabel;


/** The high end of the range of font sizes that should be used.
 */
@property(nonatomic, readonly)CGFloat fontSizeMax;

/** The low end of the range of font sizes that should be used.
 */
@property(nonatomic, readonly)CGFloat fontSizeMin;

/** The horizontal and vertical spacing that should be between months in the IGCalendarViewDisplayTypeYear
 */
@property(nonatomic, readonly)CGSize yearViewMonthSpacing;


/** The tint color that should be used to highlight things such as Today, and month names.
 */
@property(nonatomic, readonly)UIColor* highlightColor;

/** The color primarily used for text color
 */
@property(nonatomic, readonly)UIColor* majorColor;

/** The color used for areas such as the Title bar.
 */
@property(nonatomic, readonly)UIColor* minorColor;

/** The main background color of the calendar
 */
@property(nonatomic, readonly)UIColor* backingColor;

/** The color used for borders such as the IGCalendarViewDisplayTypeMonth separators
 */
@property(nonatomic, readonly)UIColor* outLineColor;

/** The color used for standard appointments in IGCalendarViewDisplayTypeMonth
 */
@property(nonatomic, readonly)UIColor* lightTextColor;

/** The format that the week day names should be displayed in.
 */
@property(nonatomic, readonly)IGCalendarWeekDayDisplayType weekDayDisplayType;

@end

/*! The default theme. This theme is used automatically when a theme isn't specified or certain options of a theme aren't specified. 
 
 This theme takes into account if you're on an iPhone or an iPad and makes adjustments based on that. Such as min/max font sizes, weekDisplayType and yearViewMonthSpacing.
 */
@interface IGCalendarDefaultTheme : NSObject<IGCalendarThemeDefinition>
@end


/*! Predefined theme.
 
 This theme takes into account if you're on an iPhone or an iPad and makes adjustments based on that. Such as min/max font sizes, weekDisplayType and yearViewMonthSpacing.
 */
@interface IGCalendarTheme1 : IGCalendarDefaultTheme
@end

/*! Predefined theme.
 
 This theme takes into account if you're on an iPhone or an iPad and makes adjustments based on that. Such as min/max font sizes, weekDisplayType and yearViewMonthSpacing.
 */
@interface IGCalendarTheme2 : IGCalendarDefaultTheme
@end

/*! Predefined theme.
 
 This theme takes into account if you're on an iPhone or an iPad and makes adjustments based on that. Such as min/max font sizes, weekDisplayType and yearViewMonthSpacing.
 */
@interface IGCalendarTheme3 : IGCalendarDefaultTheme
@end


/*!
 The IGCalendarViewStringsDefinition protocol is adopted by an object that replaces default strings off various objects in the IGCalendarView object.
 
 All methods and properties in this protocol are optional.
 
 */
@protocol IGCalendarViewStringsDefinition <NSObject>

@optional

/** The string used for the DayView's back button in the Title bar.
 
 The default value is "Back"
 */
@property(nonatomic, readonly)NSString* backButtonText;

@end

/*!
 A Japanese Translation of all strings in the IGCalendarView.
 */
@interface IGCalendarViewJapaneseStrings : NSObject<IGCalendarViewStringsDefinition>
@end

/*!
 An English Translation of all strings in the IGCalendarView.
 */
@interface IGCalendarViewEnglishStrings : NSObject<IGCalendarViewStringsDefinition>
@end