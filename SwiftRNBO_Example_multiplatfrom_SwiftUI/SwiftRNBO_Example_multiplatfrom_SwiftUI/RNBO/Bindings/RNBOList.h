//
//  RNBOList.h
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 22.02.2023.
//

#import <Foundation/Foundation.h>



NS_ASSUME_NONNULL_BEGIN

@interface RNBOList : NSObject

- (void)fromArrayOfNumbers:(NSArray<NSNumber *> *)array;
- (NSArray<NSNumber *> *)toArrayOfNumbers;

@end

NS_ASSUME_NONNULL_END
