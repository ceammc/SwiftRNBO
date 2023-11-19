//
//  RNBOList.m
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 22.02.2023.
//

#include "RNBO.h"
#import "RNBOList.h"

@implementation RNBOList{
    std::shared_ptr<RNBO::list> _obj;
}

- (void)fromArrayOfNumbers:(NSArray<NSNumber *> *)array {
}

- (NSArray<NSNumber *> *)toArrayOfNumbers {
    return @[];
}

@end

#pragma mark -

@interface RNBOList (CxxCounterpart)
- (void)setCxxList:(std::shared_ptr<RNBO::list>)list;
@end

@implementation RNBOList (CxxCounterpart)
- (void)setCxxList:(std::shared_ptr<RNBO::list>)list {
    self->_obj = list;
}

@end
