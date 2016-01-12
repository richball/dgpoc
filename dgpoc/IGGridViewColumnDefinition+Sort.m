#import "IGGridViewColumnDefinition+Sort.h"
#import <objc/runtime.h>


NSString const *key = @"my.very.unique.key";


@implementation IGGridViewColumnDefinition (Sort)

- (NSString *)sortFieldKey {
    
    NSString *sortFieldKey = objc_getAssociatedObject(self, &key);

    if (sortFieldKey)
        return sortFieldKey;
    
    return self.fieldKey;
}

- (void)setSortFieldKey:(NSString *)sortFieldKey
{
    objc_setAssociatedObject(self, &key, sortFieldKey, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
