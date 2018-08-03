//
//  SkitchColor+Skitch.h
//  SkitchKit
//
//  Created by Stewart Gillen on 4/16/13.
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

/**
 @category SkitchColor (Skitch)
 @discussion This is a category based on UIColor or NSColor. We are using a category here as a subclass is not necessary.
 Per the documentation on UIColor:
 Most developers should have no need to subclass UIColor. The only time doing so might be necessary is if you require support for additional colorspaces or color models.
 */

#import "SkitchColor.h"

@interface SkitchColor (SkitchColorConvenienceMethods)

/**
 @method skitchColorFromRGB:
 Creates a new SkitchColor object from a hex based RGB value.
 @param rgbValue
 Hex based value representing the RGB values.
 For example: 0xFFFFFF
 @result
 Returns new SkitchColor object from provided RGB values and an alpha of 100%
 */
+ (instancetype) skitchColorFromRGB:(NSUInteger)rgbValue;

/**
 @method skitchColorFromRGB:alphaPercentage:
 Creates a new SkitchColor object from a hex based RGB value.
 @param rgbValue
 Hex based integer value representing the RGB values.
 For example: 0xFFFFFF
 @param percentage
 Integer value representing the alpha percentage from 0% to 100%. Any value above 100 will result as 100.
 @result
 Returns new SkitchColor object from provided RGB values.
 */
+ (instancetype) skitchColorFromRGB:(NSUInteger)rgbValue alphaPercentage:(NSUInteger)percentage;

//Palette colors

/**
 @method Returns default Skitch yellow color
 */
+ (instancetype) skitchYellow;

/**
 @method Returns default Skitch orange color
 */
+ (instancetype) skitchOrange;

/**
 @method Returns default Skitch green color
 */
+ (instancetype) skitchGreen;

/**
 @method Returns default Skitch black color
 */
+ (instancetype) skitchBlack;

/**
 @method Returns default Skitch blue color
 */
+ (instancetype) skitchBlue;

/**
 @method Returns default Skitch pink color
 */
+ (instancetype) skitchPink;

/**
 @method Returns default Skitch red color
 */
+ (instancetype) skitchRed;

/**
 @method Returns default Skitch white color
 */
+ (instancetype) skitchWhite;

/**
 @method isDarkColor:
 Creates a new SkitchColor object from a hex based RGB value.
 @param color
 SkitchColor to be evaluated for darkness.
 @result
 Returns YES if color is dark, NO if the color is not dark.
 */
+ (BOOL)isDarkColor:(SkitchColor *)color;

/**
 @method Returns YES if target is equal to the given color
 */
- (BOOL)isSkitchColorEqual:(SkitchColor *)color;

#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

/**
 \brief Returns a CGColorRef that corresponds to a tiled image.
 \param patternImage The image used for tiling on the color.
 \return a CGColorRef.
 */
+ (CGColorRef)skitch_CGColorCreateFromImage:(NSImage *)patternImage CF_RETURNS_RETAINED;

#endif

@end
