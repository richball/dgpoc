#import <UIKit/UIKit.h>
#import <IG/IG.h>

@class IGGridViewSortingDataSourceHelper;
@interface GridViewController : UIViewController <IGGridViewDelegate>

@property (nonatomic, weak) IBOutlet IGGridView* gridView;
@property (nonatomic, strong) IGGridViewSortingDataSourceHelper *ds;

@end

