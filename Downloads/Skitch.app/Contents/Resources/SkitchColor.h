//
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#ifndef SkitchKit_SkitchColor_h
#define SkitchKit_SkitchColor_h

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    @import UIKit;
    #define SkitchColor UIColor
    #define CGColorFromSkitchColor(c) ((c).CGColor)
    #define SkitchColorWithRGBA(r, g, b, a) ([UIColor colorWithRed:(r) green:(g) blue:(b) alpha:(a)])
#else
    #import <Cocoa/Cocoa.h>
    #define SkitchColor NSColor
    #define CGColorFromSkitchColor(c) ((c).CGColor)
    #define SkitchColorWithRGBA(r, g, b, a) ([NSColor colorWithCalibratedRed:(r) green:(g) blue:(b) alpha:(a)])
#endif

#import "SkitchColor+Skitch.h"

#endif