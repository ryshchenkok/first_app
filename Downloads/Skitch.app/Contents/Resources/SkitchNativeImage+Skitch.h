//
//  Copyright 2014 Evernote Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SkitchNativeImage.h"
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
@import ImageIO;
#endif

#define SKITCH_LOSSY_COMPRESSION_QUALITY (0.8f)

extern NSString * const SkitchNativeImageErrorDomain;

typedef enum SkitchNativeImageErrorCode : NSUInteger
{
	SkitchNativeImageErrorCodeUnknown,
	SkitchNativeImageErrorCodeFileNotFound,
	SkitchNativeImageErrorCodeUnsupportedSize
} SkitchNativeImageErrorCode;

typedef enum : NSUInteger
{ 
    SkitchImageProfileLossless, 
    SkitchImageProfileCompressed 
} SkitchImageProfile;

BOOL SkitchNativeImageDimensionsAreValid (CGSize dimensions, NSError * __autoreleasing *error);
CGImageSourceRef SkitchNativeImageSourceRefCreateWithURL (NSURL *url, NSNumber * __autoreleasing *scale, NSValue * __autoreleasing *dimensions, NSNumber * __autoreleasing *orientation, NSError * __autoreleasing *error);

NSData *SkitchImagePNGRepresentation(SkitchNativeImage *image);
NSData *SkitchImageJPEGRepresentation(SkitchNativeImage *image, CGFloat compressionQuality);

CGImageRef SkitchImageCreateWithURL(NSURL *url);
NSDictionary *SkitchSanatizeImagePropertiesForWriting(NSDictionary *imageProperties, CGFloat dpi);
BOOL SkitchImageWriteToDisk(CGImageRef image, NSURL *url, SkitchImageProfile profile, CGFloat dpi, NSDictionary *imageProperties);
NSData *SkitchImageDataFromCGImage(CGImageRef image, SkitchImageProfile profile);

CGImageRef SkitchImageCreateScaledImage(CGImageRef image, float scale);

// Degrees must be either 0, 90, 180, or 270
CGImageRef SkitchImageCreateRotatedImage(CGImageRef image, uint16_t degrees, BOOL clockwise);

CGImageRef SkitchImageCreateMirroredImage(CGImageRef image);

BOOL SkitchImageFileURLIsCompressed(NSURL* url);

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#else

NSData *SkitchImageTIFFRepresentation(SkitchNativeImage *image);
NSData *SkitchImageBMPRepresentation(SkitchNativeImage *image);
NSData *SkitchImageGIFRepresentation(SkitchNativeImage *image);
NSData *SkitchImageJPEG2000Representation(SkitchNativeImage *image, CGFloat compressionQuality);
NSData *SkitchImagePDFRepresentation(SkitchNativeImage *image);

#endif


// Returns a copy of this image that is cropped to the given bounds.
// The bounds will be adjusted using CGRectIntegral.
// This method ignores the image's imageOrientation setting.
@interface SkitchNativeImage (Skitch)

+ (SkitchNativeImage *) skitchImageNamed:(NSString *)name;

+ (SkitchNativeImage *) skitchImageWithContentsOfFile:(NSString *)path ofType:(NSString *)extension;

- (SkitchNativeImage *) croppedImage:(CGRect)bounds;

/**
 \returns the maximum image resolution in pixels for this device
 */
+(CGFloat)maximumImageResolutionForThisDevice;

// TODO: Replace bridgeport_* with skitch_* methods
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

+ (SkitchNativeImage *)bridgeport_localizedImageNamed:(NSString *)name withExtension:(NSString *)extension;
- (NSData *)bridgeport_smallestData;
- (SkitchNativeImage *)bridgeport_applyCameraOrientation:(NSString *)tempFilePath;
- (SkitchNativeImage *)bridgeport_subimageWithRect:(CGRect)rect;
- (SkitchNativeImage *)bridgeport_pixelatedImageWithRect:(CGRect)region pixelBlockSize:(CGSize)pixelSize;
- (SkitchNativeImage *)bridgeport_pixelatedImage:(CGFloat)toolSize;

// This method uses the Accelerate framework to scale down an image and then back to original size using Lanczos resampling
- (SkitchNativeImage *)bridgeport_pixelatedImageByScaling:(CGFloat)scaleFactor;

#else

/**
 \brief Pixelates an image by first scaling it down, then scaling it back up to its original size.
 \details The scaling algorithm used is the Core Image CILanczosScaleTransform filter.
 \param scaleFactor a value between 0.0 and 1.0 that affects the size of the scaled down image
 (and thus the resulting chunkiness of the pixelated image).  The result of this is
 \return a NSImage containing the pixelated version of the original image.
 */
- (SkitchNativeImage *)skitch_pixelatedImageByScaling:(CGFloat)scaleFactor;

/**
 \brief Pixelates an image by uses the Core Image CIPixellate filter.
 \details The scaling algorithm used is the Core Image CIPixellate filter.
 \param blockSizeInPoints the size of the pixelation blocks (in points).
 \return a NSImage containing the pixelated version of the original image.
 */
- (SkitchNativeImage *)skitch_pixelatedImageWithBlockSize:(CGFloat)blockSizeInPoints;

/**
 \brief Pixelates an image by first scaling it down, then scaling it back up to its original size.  (Deprecated.)
 \details The scaling algorithm used is to create a bitmap context for the small size,
 draw the original image into the smaller bitmap, then draw the smaller bitmap back into a
 final bitmap context of the original size.  The system scaling algorithm is applied.
 \note This method is not currently being used by Skitch.
 \param toolSize a value between 0.0 and 1.0 that affects the size of the scaled down image
 (and thus the resulting chunkiness of the pixelated image).
 \return a NSImage containing the pixelated version of the original image.
 */
- (SkitchNativeImage *)skitch_pixelatedImage:(CGFloat)toolSize;

/**
 \brief Performs a flip along the vertical axis resulting in an image that mimics what would be seen
 if the image were viewed in a mirror.
 \return a NSImage containing the mirror image of the original image.
 */
- (SkitchNativeImage *)skitch_mirroredImage;

/**
 \brief Rotates an image by the given number of radians.
 \param angleRadians the number of radians to rotate the image.
 \return a NSImage containing the original image rotated by the given number of radians.
 */
- (SkitchNativeImage *)skitch_rotatedImage:(CGFloat)angleRadians;

/**
 \brief Renders the given CIImage into an NSImage.
 \param image instance.
 \return an NSImage containing rendered CIImage.
 */
+ (SkitchNativeImage *)skitch_imageWithCIImage:(CIImage *)image;

#endif

@end
