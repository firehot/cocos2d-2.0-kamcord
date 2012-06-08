//
//  Kamcord.h
//  cocos2d-ios
//
//  Created by Kevin Wang on 5/5/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "KCGLView.h"
#import "CCDirectorIOS.h"

// Convenient for game developers
#import "KamcordMacros.h"
#import "Common/View/KCViewController.h"

@interface Kamcord : NSObject

////////////////////////////////////////////////
// Public methods

// Setup
+ (void) setDeveloperKey:(NSString *)key
         developerSecret:(NSString *)secret;
+ (NSString *)developerKey;
+ (NSString *)developerSecret;

// View and OpenGL
+ (void) setParentViewController:(UIViewController *)viewController;
+ (UIViewController *)parentViewController;

+ (void) setView:(KCGLView *)glView;

// Convenience wrapper around [[UIApplication sharedApplication] statusBarOrientation]
+ (KCDeviceOrientation) deviceOrientation;

// Social media
+ (void) setYouTubeTitle:(NSString *)title
             description:(NSString *)description 
                keywords:(NSString *)keywords;
+ (NSString *)youtubeTitle;
+ (NSString *)youtubeDescription;
+ (NSString *)youtubeKeywords;

+ (void) setFacebookTitle:(NSString *)title
                  caption:(NSString *)caption
              description:(NSString *)description;
+ (NSString *)facebookTitle;
+ (NSString *)facebookCaption;
+ (NSString *)facebookDescription;

+ (void) setLevel:(NSString *)level
            score:(NSNumber *)score;
+ (NSString *) level;
+ (NSNumber *) score;

// Audio
+ (BOOL) setAudioResourceName:(NSString *)name
                    extension:(NSString *)extension;
+ (NSString *)audioResourceName;
+ (NSString *)audioResourceExtension;

// Video recording
+ (BOOL) startRecording;
+ (BOOL) stopRecording;
+ (BOOL) resume;
+ (BOOL) pause;

// Video recording settings
enum KC_VIDEO_DIMENSIONS {
    VIDEO_DIMENSIONS_FULL,
    VIDEO_DIMENSIONS_HALF
};

enum KC_VIDEO_QUALITY {
    VIDEO_QUALITY_MEDIUM,
    VIDEO_QUALITY_HIGH
};

// Video recording settings
// Recommend setting is SMART_VIDEO_DIMENSIONS:
//   All iPads: 512x384
//   All iPhone and iPods: 480x320
//
// Other option is FULL_VIDEO_DIMENSIONS:
//   All iPads: 1024x768
//   iPhone/iPod non-retina: 480x320
//   iPhone/iPad retina: 960x640
typedef enum {
    SMART_VIDEO_RESOLUTION,
    FULL_VIDEO_RESOLUTION,
} KC_VIDEO_RESOLUTION;

typedef enum {
    MEDIUM_VIDEO_QUALITY,
    HIGH_VIDEO_QUALITY
} KC_VIDEO_QUALITY;

// Size refers to the pixel dimensions. 
+ (void) setVideoResolution:(KC_VIDEO_RESOLUTION)resolution
                    quality:(KC_VIDEO_QUALITY)quality;
+ (KC_VIDEO_RESOLUTION) videoResolution;
+ (KC_VIDEO_QUALITY) videoQuality;


// Displays the Kamcord view inside the previously set parentViewController;
+ (void) showView;

// Returns the singleton Kamcord object. You don't ever really need this, just
// use the static API calls.
+ (Kamcord *) sharedManager;


@end
