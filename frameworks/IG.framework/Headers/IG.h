#ifndef NS_DESIGNATED_INITIALIZER
#if __has_attribute(objc_designated_initializer)
#define NS_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
#else
#define NS_DESIGNATED_INITIALIZER
#endif
#endif

#import "IGBuildVersion.h"
#import "IGGridView.h"
#import "IGGridViewSingleFieldMultiColumnDataSourceHelper.h"
#import "IGGridViewSingleFieldDynamicColumnDataSourceHelper.h"
#import "IGGridViewColumnDefinition.h"
#import "IGLabel.h"
#import "IGOverlayView.h"
#import "IGProgressView.h"
#import "IGCalendarView.h"
#import "IGCalendarEKDataSourceHelper.h"
#import "IGBarcodeView.h"
#import "IGSlideTabView.h"
#import "IGSlideTabItem.h"
#import "IGFlowLayoutView.h"
#import "IGSideMenuView.h"
#import "IGSlideTabViewController.h"