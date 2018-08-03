//
//  SkitchNativeImage.h
//  SkitchKit
//
//  Created by Stewart Gillen on 6/28/13.
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef SkitchKit_SkitchNativeImage_h
#define SkitchKit_SkitchNativeImage_h

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define SkitchNativeImage UIImage
#else
#define SkitchNativeImage NSImage
#endif

#endif

#import "SkitchNativeImage+Skitch.h"
