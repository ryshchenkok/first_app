//
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

CGSize CGSizeFromDictionary(NSDictionary *dictionary);
NSDictionary *NSDictionaryFromCGSize(CGSize size);
CGSize CGSizeFromCGPoint(CGPoint point);

CGSize CGSizeScaleAspectFit(CGSize size, CGSize boundingSize);
CGFloat CGSizeGetAspectFitScale(CGSize size, CGSize boundingSize);
