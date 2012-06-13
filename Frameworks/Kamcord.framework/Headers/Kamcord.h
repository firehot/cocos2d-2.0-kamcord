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
#import "Common/Core/Audio/KCAudio.h"

@interface Kamcord : NSObject

////////////////////////////////////////////////
// Public methods

// Setup
+ (void) setDeveloperKey:(NSString *)key
         developerSecret:(NSString *)secret;
+ (NSString *) developerKey;
+ (NSString *) developerSecret;

// View and OpenGL
+ (void) setParentViewController:(UIViewController *)viewController;
+ (UIViewController *) parentViewController;

+ (void) setView:(KCGLView *)glView;

// Convenience wrapper around [[UIApplication sharedApplication] statusBarOrientation]
+ (KCDeviceOrientation) deviceOrientation;

// Social media
+ (void) setYouTubeTitle:(NSString *)title
             description:(NSString *)description 
                keywords:(NSString *)keywords;
+ (NSString *) youtubeTitle;
+ (NSString *) youtubeDescription;
+ (NSString *) youtubeKeywords;

+ (void) setFacebookTitle:(NSString *)title
                  caption:(NSString *)caption
              description:(NSString *)description;
+ (NSString *) facebookTitle;
+ (NSString *) facebookCaption;
+ (NSString *) facebookDescription;

+ (void) setLevel:(NSString *)level
            score:(NSNumber *)score;
+ (NSString *) level;
+ (NSNumber *) score;

// Video recording
+ (BOOL) startRecording;
+ (BOOL) stopRecording;
+ (BOOL) resume;
+ (BOOL) pause;

// Video recording settings
// For release, use SMART_VIDEO_DIMENSIONS:
//   iPad 1 and 2: 512x384
//   iPad 3: 1024x768
//   All iPhone and iPods: 480x320
//
// For trailers, use TRAILER_VIDEO_RESOLUTION
//   All iPads: 1024x768
//   iPhone/iPod non-retina: 480x320
//   iPhone/iPad retina: 960x640
typedef enum {
    SMART_VIDEO_RESOLUTION,
    TRAILER_VIDEO_RESOLUTION,
} KC_VIDEO_RESOLUTION;

// Size refers to the pixel dimensions. 
+ (void) setVideoResolution:(KC_VIDEO_RESOLUTION)resolution;
+ (KC_VIDEO_RESOLUTION) videoResolution;


// Audio recording
+ (KCAudio *) playSound:(NSString *)filename
                   loop:(BOOL)loop;
+ (KCAudio *) playSound:(NSString *)filename;

// Will stop all non-looping sounds. If loop is YES, will also stop
// all looping sounds.
+ (void) stopAllSounds:(BOOL)loop;

// Displays the Kamcord view inside the previously set parentViewController;
+ (void) showView;


// --------------------------------------------------------
// For Kamcord internal use, don't worry about these.

// Returns the singleton Kamcord object. You don't ever really need this, just
// use the static API calls.
+ (Kamcord *) sharedManager;

// Helper to figure calculate the internal scale factor
+ (unsigned int) resolutionScaleFactor;

+ (KCAudio *) audioBackground;

@end
