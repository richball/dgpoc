
#import <UIKit/UIKit.h>
#import "IGSlideTabView.h"

/*!
The _IGSlideTabViewController_ is a view controller that contains an added instance of the _IGSlideTabView_.
*/
@interface IGSlideTabViewController : UIViewController

/** Instance of the _IGSlideTabView_ contained in the view controller.
*/
@property (nonatomic, readonly) IGSlideTabView *slideTabView;

@end