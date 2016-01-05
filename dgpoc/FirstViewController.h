#import <UIKit/UIKit.h>
#import <IG/IG.h>


@interface FirstViewController : UIViewController<IGGridViewDelegate>

@property (nonatomic, weak) IBOutlet IGGridView* gridView;
@property (nonatomic, strong) IGGridViewDataSourceHelper* ds;

@end

