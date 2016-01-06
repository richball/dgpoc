#import "IGGridViewSymbolColumnDefinition.h"
#import "QuoteItem.h"
#import "SymbolCell.h"

@implementation IGGridViewSymbolColumnDefinition

- (IGGridViewCell *)gridView:(IGGridView *)gridView createCell:(IGCellPath *)path usingDataSource:(IGGridViewDataSourceHelper *)dataSource {
    QuoteItem* data = [dataSource resolveDataObjectForRow:path];
    
    if (!data) return nil;
    
    SymbolCell* cell =  [gridView dequeueReusableCellWithIdentifier:@"Symbol"];
    
    if (!cell) {
        cell = [[SymbolCell alloc]initWithReuseIdentifier:@"Symbol"];
    }

    cell.labelSymbol.text = data.symbol;
    cell.labelSymbolDescription.text = data.symbolName;
    
    return cell;
}

@end
