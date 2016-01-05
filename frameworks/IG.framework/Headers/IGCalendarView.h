//
//  IGCalendarView.h
//
//  Copyright (c) 2013 Infragistcs. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "IGCalendarThemeDefinition.h"

NS_ASSUME_NONNULL_BEGIN

@class IGCalendarView;
@class IGCalendarAppointment;

typedef NS_ENUM(NSInteger, IGCalendarViewDisplayType)
{
    IGCalendarViewDisplayTypeYear,
    IGCalendarViewDisplayTypeMonth,
    IGCalendarViewDisplayTypeDay,
    IGCalendarViewDisplayTypeWeek
    
};

typedef NS_ENUM(NSInteger, IGCalendarDayViewTimeFormat)
{
    IGCalendarDayViewTimeFormatAuto,
    IGCalendarDayViewTimeFormat12,
    IGCalendarDayViewTimeFormat24
    
};

typedef NS_ENUM(NSInteger, IGCalendarMonthViewDayClickAction)
{
    IGCalendarMonthViewDayClickActionNavigateToDay,
    IGCalendarMonthViewDayClickActionNavigateToWeek
    
};

typedef NS_ENUM(NSInteger, IGCalendarDayViewInitialScrollLocation)
{
    IGCalendarDayViewInitialScrollLocationSpecificHour,
    IGCalendarDayViewInitialScrollLocationFirstAppointment
    
};


typedef NS_ENUM(NSInteger, IGCalendarMonthViewEmptyDays)
{
    IGCalendarMonthViewEmptyDaysAll,
    IGCalendarMonthViewEmptyDaysDisableFullEmptyWeek
};

/** IGCalendarAppointmentRequest is an object that acts like an envelope to present and request information for async appointment requests.
 
This object is provided by the IGCalendarAppointmentDataSource protocol's calendarView:asyncAppointmentRequest:ofType.  From this object you get the range of appointments the calendar is looking for. Once you retreive those appointments, you can then give them back to the calling object by simpling invoking the provideAppointments: method on this object.
 */
@interface IGCalendarAppointmentRequest : NSObject

/** The beginning of the appointment range being requested by the IGCalendarView*/
@property(nonatomic, readonly)NSDate* start;

/** The end of the appointment range being requested by the IGCalendarView*/
@property(nonatomic, readonly)NSDate* end;


/** Call this when you retrieve your appointments, to notify the IGCalendarView that it should display them.
 
 @param appts An array of IGCalendar appointment objects.
 */
-(void)provideAppointments:(NSArray<__kindof IGCalendarAppointment *>*)appts;

@end

/*!
 The IGCalendarAppointmentDataSource protocol is adopted by an object that mediates the application's appointment data model for a IGCalendarView object. The data source provides the calendar view object with the IGCalendarAppointment objects that get displayed in it's various views.
 
 The only required method of this protocol is the color that the appointments provided by this datasource should use.
 
 */
@protocol IGCalendarAppointmentDataSource <NSObject>

/** Asks the datasource for the color that appointments should appear as for this calendar.
 
 This is not optional
 
 @param calView The IGCalendarView making the request.
 @return The UIColor to use.
 */
-(UIColor*)colorForAppointmentsInIGCalendarView:(IGCalendarView*)calView;

@optional


/** Asks the datasource for the color that should be used for the text of selected appointments.
 
 If not specified, white will be used.
 
 @param calView The IGCalendarView making the request.
 @return The UIColor to use.
 */
-(UIColor*)colorForSelectedAppointmentTextInIGCalendarView:(IGCalendarView*)calView;

/** Asks the datasource for an Array of IGCalendarView appointments.
 
 Although this method is synchrounous, it is actually called on a background thread to keep the calendar scrolling performance smooth.
 
 @param calView The IGCalendarView making the request.
 @param start The beginning of the appointment range being requested by the IGCalendarView.
 @param end The end of the appointment range being requested by the IGCalendarView
 @param requestType The view making the request: Day or Month
 @return An array of IGCalendar appointment objects or nil if there are no appointments to return.
 */
-(NSArray*)calendarView:(IGCalendarView *)calView appointmentsForStart:(NSDate*)start end:(NSDate*)end ofType:(IGCalendarAppointmentRequestType)requestType;


/** Asks the datasource for an Array of IGCalendarView appointments. 
 
 Since this method is async, to return appointments called provideAppointments: from the IGCalendarAppointmentRequest object that was provided.
 
 @param calView The IGCalendarView making the request.
 @param request The IGCalendarAppointmentRequest object that contains the date range being requested. 
 @param requestType The view making the request: Day or Month
 */
-(void)calendarView:(IGCalendarView *)calView asyncAppointmentRequest:(IGCalendarAppointmentRequest*)request ofType:(IGCalendarAppointmentRequestType)requestType;

@end

/*!
 The delegate of a IGCalendarView object must adopt the IGCalendarViewDelegate protocol. Optional methods of the protocol allow the delegate to manage navigation and interactions within the IGCalendarView.
 */
@protocol IGCalendarViewDelegate <NSObject>

@optional

/** Tells the delegate that an IGCalendarAppointment was tapped in the IGCalendarViewDisplayTypeDay view.
 
 @param calView The IGCalendarView providing the information.
 @param appt The appointment that was tapped.
 @param dataSource The dataSource that provided the appointment.
 @param rect The actual bounds of the appointment that was tapped. 
 @param date The date in which the appointment was tapped on.
 */
-(void)calendarView:(IGCalendarView *)calView appointmentTapped:(IGCalendarAppointment*)appt fromDataSource:(id<IGCalendarAppointmentDataSource>)dataSource withBounds:(CGRect)rect forDay:(NSDate*)date;

/** Tells the delegate that IGCalendarView has navigated to a different year.
 
 @param calView The IGCalendarView providing the information.
 @param date The current date of the IGCalendarView
 */
-(void)calendarView:(IGCalendarView *)calView yearChanged:(NSDate*)date;

/** Tells the delegate that IGCalendarView has navigated to a different month.
 
 @param calView The IGCalendarView providing the information.
 @param date The current date of the IGCalendarView
 */
-(void)calendarView:(IGCalendarView *)calView monthChanged:(NSDate*)date;

/** Tells the delegate that IGCalendarView has navigated to a different day.
 
 @param calView The IGCalendarView providing the information.
 @param date The current date of the IGCalendarView
 */
-(void)calendarView:(IGCalendarView *)calView dayChanged:(NSDate*)date;

/** Tells the delegate that IGCalendarView has navigated to a different week.
 
 @param calView The IGCalendarView providing the information.
 @param date The current date of the IGCalendarView
 */
-(void)calendarView:(IGCalendarView *)calView weekChanged:(NSDate*)date;


/** Asks the delegate for the title of a the rightTitleBarButton.
 
 Return nill if there shouldn't be a button displayed. This method is invoked each type the currentDisplay of the IGCalendarView changes.
 
 @param calView The IGCalendarView making the request.
 @param displayType The IGCalendarViewDisplayType currently being displayed.
 @return The title of the button to be displayed or nil.
 */
-(NSString*)calendarView:(IGCalendarView*)calView titleForRightTitleBarButtonFor:(IGCalendarViewDisplayType)displayType;

/** Tells the delegate that the rightTitleBarButton has been clicked.
 
 @param calView The IGCalendarView providing the information.
 @param displayType The IGCalendarViewDisplayType currently being displayed.
 */
-(void)calendarView:(IGCalendarView *)calView rightTitleBarButtonTappedFor:(IGCalendarViewDisplayType)displayType;

/** Tells the delegate that a yearView's month was tapped.
 
 Return YES if you want the calendarView to navigate to that month.
 
 @param calView The IGCalendarView providing the information.
 @param date The actual date being tapped.
 @return YES if you want to allow normal navigation, NO if you want to cancel navigation and perform your own task.
 */
-(BOOL)calendarView:(IGCalendarView*)calView yearViewMonthTapped:(NSDate*)date;

/** Tells the delegate that a monthView's day was tapped.
 
 Return YES if you want the calendarView to navigate to that day.
 
 @param calView The IGCalendarView providing the information.
 @param date The actual date being tapped.
 @return YES if you want to allow normal navigation, NO if you want to cancel navigation and perform your own task.
 */
-(BOOL)calendarView:(IGCalendarView*)calView monthViewDayTapped:(NSDate*)date;


/** Asks the delegate for the title of a the title bar.
 
 Return nil if the calendarView should use the default. This method is invoked each type the currentDisplay of the IGCalendarView changes.
 
 @param calView The IGCalendarView making the request.
 @param date The date that needs to be represented.
 @param displayType The IGCalendarViewDisplayType currently being displayed.
 @return The value of the title bar to be displayed or nil.
 */
-(NSString*)calendarView:(IGCalendarView *)calView titleLabelForDate:(NSDate*)date forDisplayType:(IGCalendarViewDisplayType)displayType;


/** Asks the delegate for the title of a the back title bar button.
 
 Return nil if the calendarView should use the default. This method is invoked each type the currentDisplay of the IGCalendarView changes.
 
 @param calView The IGCalendarView making the request.
 @param date The date that needs to be represented.
 @param displayType The IGCalendarViewDisplayType currently being displayed.
 @return The value of the title bar's back button to be displayed or nil.
 */
-(NSString*)calendarView:(IGCalendarView *)calView titleForBackButtonForDate:(NSDate*)date forDisplayType:(IGCalendarViewDisplayType)displayType;


/** Asks the delegate for the title of the month view's # more... label, that is displayed when there isn't enough space to display all of the appointments in a month view day.
 
 Return nil if the calendarView should use the default.
 
 @param calView The IGCalendarView making the request.
 @param appts An array of IGCalendarAppointment objects that belong to the day of the month thats requesting the string.
 @param notShownCount The number of appoitnments that can't fit into the day's cell.
 @return The text that will be displayed in the extra appointments' label. 
 */
-(NSString*)calendarView:(IGCalendarView *)calView titleForMonthViewMoreAppointmentsLabel:(NSArray*)appts notShownCount:(NSInteger)notShownCount;


/** Asks the delegate for the background color of a month view's particular day.
 
 @param calView The IGCalendarView making the request.
 @param month The month.
 @param day The day of the current month.
 @param year The year of the month.
 @return The color that will be used as the background color of the particular day.
 */
-(UIColor*)calView:(IGCalendarView*)calView monthViewDayBackgroundColorFor:(NSInteger)month day:(NSInteger)day year:(NSInteger)year;

/** Asks the delegate for the background color of a month's empty day.
 
 This will be called for each empty day within the month.
 
 @param calView The IGCalendarView making the request.
 @param month The month.
 @param year The year of the month.
 @return The color that will be used as the background color of the particular day.
 */
-(UIColor*)calView:(IGCalendarView*)calView monthViewDayBackgroundColorForEmptyDay:(NSInteger)month year:(NSInteger)year;

/** Asks the delegate for a view that will be displayed for a particular day in the month view display.
 
 If you use this delegate, appointments will no longer be displayed automatically. You'll take on the responsibility to display them.
 If you return nil, then we will display the day like normal.
 
 @param calView The IGCalendarView making the request.
 @param month The month.
 @param day The day of the current month.
 @param year The year of the month.
 @return The view that will be dispalyed in the day area.
 */
-(UIView*)calView:(IGCalendarView*)calView monthViewDayCustomViewFor:(NSInteger)month day:(NSInteger)day year:(NSInteger)year;


/** Tells the delegate that appointments are avaialble for a partiular day in the month view display. Use this method to display appointments in your custom view.
 
If you implemented the calView:monthViewDayCustomViewFor:day:year: this method will notify you of the appointments for that day.
 
 @param calView The IGCalendarView making the request.
 @param appts The appointments for a specific day.
 @param customView The custom view provided in calView:monthViewDayCustomViewFor:day:year:
 */
-(void)calView:(IGCalendarView*)calView appointments:(NSArray*)appts loadedForMonthViewDayCustomView:(UIView*)customView;

/** Tells the delegate that the day view was tapped at a specific hour.

 @param calView The IGCalendarView making providing the information.
 @param hour A float from 0 - 23. This number does include decimals, so you can provide more accurate time slots.
 @param date The date of the day tapped. Note this does NOT include the hour.
 */
-(void)calView:(IGCalendarView*)calView hourTapped:(CGFloat)hour forDate:(NSDate*)date;

/** Tells the delegate that the day view was long pressed at a specific hour.
 
 @param calView The IGCalendarView making providing the information.
 @param hour A float from 0 - 23. This number does include decimals, so you can provide more accurate time slots.
 @param date The date of the day tapped. Note this does NOT include the hour.
 */
-(void)calView:(IGCalendarView*)calView hourPressed:(CGFloat)hour forDate:(NSDate*)date;

@end

/*!
 The IGCalendarView is a container that displays different views for navigating dates and display appointments. Within in this control you can view 3 different display types Year, Month, and Day. 
 
 Each display type knows how to animate smoothly between other display types to prvoide a seamless transition. 
 
 You can use this control to display your own calendars/appointments.
 
 */
@interface IGCalendarView : UIView

/** Sets the IGCalendarThemeDefinition that will control the styling of particular elements of the IGCalendarView.
 */
@property(nonatomic, weak, nullable)id<IGCalendarThemeDefinition> theme;

/** The object that acts as the delegate of the calendar view.
 
 The delegate must adopt the IGCalendarViewDelegate protocol.
 */
@property(nonatomic, weak, nullable)id<IGCalendarViewDelegate> delegate;

/** Sets the IGCalendarViewStringsDefinition that will control the default text values of particular elements of the IGCalendarView.
 
 When setting this property, you should call the calendar's invalidate method afterwards to ensure all elements are refreshed.
 */
@property(nonatomic, weak, nullable)id<IGCalendarViewStringsDefinition> strings;

/** An array of objects that each provides differen't calendar appointments to the IGCalendarView.
 
 Each dataSource in the array must implement the IGCalendarAppointmentDataSource protocol.
 */
@property(nonatomic, retain, nullable)NSArray<__kindof id<IGCalendarAppointmentDataSource>>* appointmentDataSources;


/** The maximum year the IGCalendarView should display. If the max year is hit, it will automatically loop around to the min year.
 */
@property(nonatomic, assign)NSInteger maxYear;

/** The minimum year the IGCalendarView should display. If the min year is hit, it will automatically loop around to the max year.
 */
@property(nonatomic, assign)NSInteger minYear;

/** Determines if the navigate back button on the titleBar is displayed.
 */
@property(nonatomic, assign)BOOL displayBackButton;

/** Determines if the title bar on the IGCalendarView displayed.
 */
@property(nonatomic, assign)BOOL displayTitleBar;

/** Provies the locale used for the IGCalendarView. 
 
 If not set the [NSCalendar current] is used.
 */
@property(nonatomic, retain, nullable)NSString* localeIdentifier;


/** Provides access to the UIButton used for the title bar on the right side (readOnly)
 
This is provided so that if you wanted to display a popup, you have a refrence/bounds of where to display the popup to.
 */
@property(nonatomic, readonly)UIButton* rightTitleBarButton;


/** Provides the currentDate of the IGCalendarView(readOnly)
 
 IGCalendarDisplayTypeYear = 1/1/Year
 IGCalendarDisplayTypeMonth = Month/1/Year
 IGCalendarDisplayTypeDay = Month/Day/Year
 
 To changed the date, use the navigateToDate:forType method.
 
 */
@property(nonatomic, readonly)NSDate* currentDate;

/** Provides the current IGCalendarViewDisplayType (readOnly)
 
 To changed the displayType, use the navigateToDate:forType method.
 
 */
@property(nonatomic, readonly)IGCalendarViewDisplayType calendarType;

/** Determines whether clicking a MonthView's day should navigate to a DayView or WeekView
 */
@property(nonatomic, assign)IGCalendarMonthViewDayClickAction monthViewDayClickAction;


/** Navigates to the provided date in the specified view.
 
 The navigation will animate if possible. If not, it will simply snap to that view. 
 
 For example if you go from YearView to MonthView, If the current month is in view of YearView it will animate to the month.  However, if you went from a YearView to a DayView, it will just snap.
 
 */
-(void)navigateToDate:(NSDate*)date forType:(IGCalendarViewDisplayType)calendarType;

/** Navigates back to the next logical IGCalendarDisplayType
 
 If you're on a Month it will go back to a Year
 If you're on a Day it will go back to a Month
 If you're on a Year it will do nothing.
 
 */
-(void)navigateBack;

/** Causes the IGCalendarView to completely invalidate itself and reload the theme and any appointments getting displayed.
 
 */
-(void)invalidate;


/** When a DayView comes into view, this property determines if it should auto scroll to the first appointment in the day, or a specified start hour.
 
If there is no appointment available for a specific day and the value of this property is set to: IGCalendarDayViewInitialScrollLocationFirstAppointment it will fall back to the dayViewInitialScrollStartHour.
 
 */
@property(nonatomic, assign)IGCalendarDayViewInitialScrollLocation dayViewInitialScrollLocation;


/** Specifies the start hour that should be displayed when a DayView comes into view and the dayViewInitialScrollLocation property is set to IGCalendarDayViewInitialScrollLocationSpecificHour
 
 Values should range from 0 - 23 and the default is 0.
 
 */
@property(nonatomic, assign)CGFloat dayViewInitialScrollStartHour;

/** Specifies whether the hours displayed in the dayView are displayed in 24 hour time, 12 hour time, or automatically determined by culture.
 
 */
@property(nonatomic, assign)IGCalendarDayViewTimeFormat dayViewHourTimeFormat;


/** Specifies whether am/pm should be appended to the hours of the dayview when the dayViewHourTimeFormat is set to 12.
 */
@property(nonatomic, assign)BOOL dayViewShowAMPM;

/** Specifies whether the week area of a dayView is displayed.
 */
@property(nonatomic, assign)BOOL dayViewWeekAreaVisible;

/** Specifies the start hour for working for the dayView and weekViews views.
    A number between 0 and 23. Note, styleWorkingHours must be true for this to take affect.
 */
@property(nonatomic, assign)CGFloat startWorkingHour;

/** Specifies the end hour for working.
 A number between 0 and 23. Note, styleWorkingHours must be true for this to take affect.
 */
@property(nonatomic, assign)CGFloat endWorkingHour;

/** For the dayView and weekView views a style will be applied for the startWorkingHour and endWorkingHour properites
 */
@property(nonatomic, assign)BOOL styleWorkingHours;


/** Normally we will limit the all day area height to the size of 2.5 appts high, just like the iOS Calendar App.  However, you can set this property to NO, and we 
 will make it so that all allday appointments are visible.*/
@property(nonatomic, assign)BOOL limitAllDayAreaHeight;


/** Specifies what empty days are allowed to appear for a Month in the Month view. 
 */
@property(nonatomic, assign)IGCalendarMonthViewEmptyDays monthViewEmptyDaysRule;

/** If the IGCalendarView is displaying the monthView, it will return the date at the specified point. Or nil, if there isn't a date at that point. 
 
 If the IGCalendarView is not displaying a monthView it will always return nil;
 */
-(NSDate*)resolveDateInMonthViewForPoint:(CGPoint)point;


/** If the IGCalendarView is displaying the yearView, it will return the date at the specified point. Or nil, if there isn't a date at that point.
 
 If the IGCalendarView is not displaying a yearView it will always return nil; This method will not return the specific day, just the month and year.
 */
-(NSDate*)resolveDateInYearViewForPoint:(CGPoint)point;

@end

/*!
 The IGCalendarAppointment is essentially a packet of information that represents an appointment that should be displayed in the IGCalendarView. 
 
 This is the object you would return via the IGCalendarAppointmentDataSource
 
 */
@interface IGCalendarAppointment : NSObject

/** The title of the appointment.
*/
@property(nonatomic, retain, nullable)NSString* title;

/** The startTime of the apppointment.
 */
@property(nonatomic, retain, nullable)NSDate* startTime;

/** The endTime of the appointment.
 */
@property(nonatomic, retain, nullable)NSDate* endTime;

/** Whether the appointment is an allDay event.
 */
@property(nonatomic, assign)BOOL allDay;

/** The location of the appointment.
 */
@property(nonatomic, retain, nullable)NSString* location;

/** Whether the appointment is a recurrence.
 */
@property(nonatomic, assign)BOOL recurrence;

/** A unique identifier to later identify the appointment. This is purely optional.
 */
@property(nonatomic, retain, nullable)NSString* identifier;

/** Any other information you may want to store on the appointment object.
 */
@property(nonatomic, readonly)NSMutableDictionary* miscProperties;

@property(nonatomic, retain)UIColor* color;

@property(nonatomic, retain)UIColor* selectedTextColor;


@end

NS_ASSUME_NONNULL_END


