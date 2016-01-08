#import "IGGridViewCurrencyColumnDefinition.h"
#import "QuoteItem.h"
#import "GridHelper.h"
#import "UIColor+TDA.h"

@implementation IGGridViewCurrencyColumnDefinition

- (instancetype)init {
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor lightGrayColor];
    }
    return self;
}

- (IGGridViewCell *)gridView:(IGGridView *)gridView createCell:(IGCellPath *)path usingDataSource:(IGGridViewDataSourceHelper *)dataSource {
    id data = [dataSource resolveDataObjectForRow:path];
    
    IGGridViewCell * cell =  [gridView dequeueReusableCellWithIdentifier:@"DollorValueCell"];
    
    if (!cell) {
        cell = [[IGGridViewCell alloc] initWithReuseIdentifier:@"DollorValueCell"];
    }
    
    NSNumber *numberValue = [data valueForKey:self.fieldKey];
    cell.textLabel.text = [[GridHelper currencyFormatter] stringFromNumber:numberValue];
    
    if (numberValue.doubleValue < 0.f) {
        cell.textLabel.textColor = [UIColor tdaRedDownTickColor];
    } else if (numberValue.doubleValue > 0.f) {
        cell.textLabel.textColor = [UIColor tdaGreenUpTickColor];
    } else {
        cell.textLabel.textColor = [UIColor lightGrayColor];
    }
    
    return cell;
}

@end
