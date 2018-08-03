//
//  NSString+Drawing.h
//  SkitchKit
//
//  Created by Ken Ryall on 2/20/13.
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Skitch)

// Drawing

- (CGSize)sizeWithFont:(NSString*)fontName andSize:(CGFloat)fontSize;

- (void)drawAtCGPoint:(CGContextRef)context atPoint:(CGPoint)textOrigin fontName:(NSString*)fontName fontSize:(CGFloat)fontSize textColor:(CGColorRef)textColor;
- (void)drawAtCGPoint:(CGContextRef)context atPoint:(CGPoint)textOrigin fontName:(NSString*)fontName fontSize:(CGFloat)fontSize textColor:(CGColorRef)textColor rightJustify:(BOOL)rightJustify extras:(NSDictionary *)extras;

+ (NSString *)skitch_stringWithNewUUID;
- (NSString *)skitch_sanitizedFilename;
- (NSString *)skitch_stringByAddingPercentEscapesUsingEncoding:(NSStringEncoding)encoding;
- (NSString *)skitch_sanitizedTitleForURL;

@end
