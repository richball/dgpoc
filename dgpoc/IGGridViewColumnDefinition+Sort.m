#import "IGGridViewColumnDefinition+Sort.h"
#import <objc/runtime.h>


NSString const *key = @"my.very.unique.key";
NSString const *keyAscending = @"my.very.unique.key.asc";
NSString const *keyDescending = @"my.very.unique.key.des";


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

- (NSString *)sortFieldKeyAscending {
    
    NSString *sortFieldKeyAscending = objc_getAssociatedObject(self, &keyAscending);
    
    if (sortFieldKeyAscending)
        return sortFieldKeyAscending;
    
    return nil;
}

- (void)setSortFieldKeyAscending:(NSString *)sortFieldKeyAscending
{
    objc_setAssociatedObject(self, &keyAscending, sortFieldKeyAscending, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (NSString *)sortFieldKeyDescending {
    
    NSString *sortFieldKeyDescending = objc_getAssociatedObject(self, &keyDescending);
    
    if (sortFieldKeyDescending)
        return sortFieldKeyDescending;
    
    return nil;
}

- (void)setSortFieldKeyDescending:(NSString *)sortFieldKeyDescending
{
    objc_setAssociatedObject(self, &keyDescending, sortFieldKeyDescending, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

@end
