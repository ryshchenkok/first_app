//
//  SkitchNativeView.h
//  SkitchKit
//
//  Created by Stewart Gillen on 7/2/13.
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#ifndef SkitchKit_SkitchNativeView_h
#define SkitchKit_SkitchNativeView_h

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
@import UIKit;
#define SkitchNativeView UIView
#else
#import <Cocoa/Cocoa.h>
#define SkitchNativeView NSView
#endif

#endif
