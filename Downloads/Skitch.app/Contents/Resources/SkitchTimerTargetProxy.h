//
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This class may be used to prevent retain cycles when the owner of an NSTimer
 * is also its target.
 */
@interface SkitchTimerTargetProxy : NSObject

@property (nonatomic, weak) id timerTarget;
- (id)initWithTarget:(id)targetValue;

@end
