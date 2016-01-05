//
//  IGCalendarEKDataSourceHelper.h
//
//  Copyright (c) 2013 Infragistcs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IGCalendarView.h"
#import <EventKit/EventKit.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/*! The IGCalendarEKDataSourceHelper is basically just what it sounds like. If you'd like to display your iOS devices calendars, this class can handle that for you.
 
 You simply provide an reference to the EKEventStore the calendar came from and EKCalendar that you want to display.
 
 You can even change the color of the calendar if you don't want to use the color from the EKCalendar. 
 
 If you don't want to display the calendar tempoaritly, just set the hide property to YES and call invalidate on the IGCalendarView. 
 
 You can even look up the EKEvent that a particular IGCalendarAppointment represents. 
 
 */
@interface IGCalendarEKDataSourceHelper : NSObject<IGCalendarAppointmentDataSource>

/** Creates an IGCalendarEKDataSourceHelper with the given calendar.
 
 @param calendar An EKCalendar object.
 @param store An EKEventStore object. The object is stored weakly, so it's up to you to keep a reference to it.
 @return Returns an initialized IGCalendarEKDataSourceHelper object or nil if the object could not be successfully initialized.
 */
-(instancetype)initWithCalendar:(EKCalendar*)calendar forStore:(EKEventStore*)store NS_DESIGNATED_INITIALIZER;

/** The UIColor that should be used to represent appointments from this calendar. If not specified, it simply uses the color from the EKCalendar*/
@property(nonatomic, retain, nullable)UIColor* color;

/** Whehter or not to hide this calendar from the IGCalendarView. If set to hide, no appointments will appear for this dataSource */
@property(nonatomic, assign)BOOL hide;


/** The title of the Calendar. If not specified, it simply uses the color from the EKCalendar*/
@property(nonatomic, retain, nullable)NSString* title;

/** Resolves the EKEvent that an IGCalendarAppointment represents.
 
 @param appt An IGCalendarAppointment that came from this IGCalendarEKDataSourceHelper
 @return Returns the backing EKEvent that this appointment represents. 
 */
-(EKEvent*)resolveEventFromAppointment:(IGCalendarAppointment*)appt;


/** Helper method: Asks for permission to access the device's calendar, and creates a IGCalendarEKDataSourceHelper for each one it finds.
 
 @return An array of IGCalendarEKDataSourceHelper objects for each EKCalendar it finds.
 */
+(NSArray<__kindof IGCalendarEKDataSourceHelper*>*)createDatasourcesForAllDeviceCalendars;


@end

NS_ASSUME_NONNULL_END
