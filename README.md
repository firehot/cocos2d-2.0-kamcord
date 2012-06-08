# cocos2d-kamcord 0.9.1


## Introduction

Kamcord is a built-in gameplay recording technology for iOS. This repository contains a Kamcord SDK that works with cocos2d-2.0-rc2 and allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then replay and share these gameplay videos via YouTube, Facebook, Twitter, and email.

In order to use Kamcord, you need a developer key and developer secret. To get these, please email Matt at <a mailto="matt@kamcord.com">matt@kamcord.com</a>.

**Kamcord works on iOS 5 and above**. You can still will run without problems on older versions of iOS, though you will not be able to to record video. Kamcord works on the iPhone 3GS, iPhone 4, iPhone 4S, iPod Touch 3G and 4G, and all iPads.

We will be making lots of improvements and adding many features over the next few months. We'd love to hear your feedback and thoughts. If you have any questions or comments, please don't hesitate to <a href="mailto:matt@kamcord.com"/>contact us</a>.

## A Sample Application

Before we explain how to use Kamcord in your own applications, let's go through a quick example that runs right out the box. Clone this repository to your local machine and open the project located at `Examples/cocos2d-iphone-2.0-rc2/cocos2d-ios.xcodeproj`.  Select `RotateWorldTest` from the dropdown and build and run that application. You should see the familiar `RotateWorldTest` from the Cocos2D suite of tests. **Make sure to run the application on a physical device with iOS 5+, not the simulator. Video replay is NOT supported by the simulator!**

After 10 seconds, the Kamcord view should appear allowing you to replay a video recording of those first 10 seconds and share that video via Facebook, Twitter, YouTube, and/or email. `ParticleTest`, `SceneTest`, and `SpriteTest` all work the same way.

`RenderTextureTest` is different in that it allows you to start and stop recording by pressing the two corresponding buttons at the top right of the screen. When you press `Stop Recording`, you will again see the Kamcord view with options to replay and share. Later on in this documentation, we'll walk through all the code needed to add recording and replay functionalities to `RenderTextureTest`.

There is no practical limit on how long you can record for. Everything gets written immediately to disk and old videos are always being erased, so the only real limitation is the device's hard drive size. Since modern iOS devices have 16+ GB of hard disk space, you can safely record one continuous gameplay video for over 24 hours straight, an upper limit your gamers will probably never run into.

## A Live Game Sample

The team at <a target="_blank" href="http://www.sewerwars.com">Sewer Wars</a> has successfully integrated Kamcord into their game. Check out a <a target="_blank" href="http://kamcord.com/v/8Pm4x61dTEQ/">sample recording</a>!

## Installation

Let's walk through how to get Kamcord into your games.

### Framework

<ol>
<li style="margin: 0";>From <code>Frameworks</code>, drag and drop <code>Kamcord.framework</code> and <code>AWSiOSSDK.framework</code> into your project.</li>
<li style="margin: 0";>Drag and drop the files under <code>Frameworks/Resources</code> to your project. For both this and the previous step, make sure to check the box next to the target application you want to link these frameworks and resources to (your game, presumably).</li>
<li style="margin: 0";>Ensure you have the following frameworks under <code>Build Phases</code> ==> <code>Link Binary With Libraries</code>:
	<p>
	<ul style="margin-top: 15px; margin-bottom: 15px;">
		<li style="margin: 0;">Accounts</li>
        <li style="margin: 0;">AVFoundation</li>
        <li style="margin: 0;"><b>AWSiOSSDK</b></li>
        <li style="margin: 0;">CoreGraphics</li>
        <li style="margin: 0;">CoreMedia</li>
        <li style="margin: 0;">CoreVideo</li>
        <li style="margin: 0;">Foundation</li>
        <li style="margin: 0;"><b>Kamcord</b></li>
        <li style="margin: 0;">MediaPlayer</li>
        <li style="margin: 0;">MessageUI</li>
        <li style="margin: 0;">OpenGLES</li>
        <li style="margin: 0;">QuartzCore</li>
        <li style="margin: 0;">Security</li>
        <li style="margin: 0;">SystemConfiguration</li>
        <li style="margin: 0;">Twitter</li>
        <li style="margin: 0;">UIKit</li>
    </ul>
    </p>
    <p>
    <img src="http://dl.dropbox.com/u/6122/Kamcord/Frameworks.png" />
    </p>
</li>
<li style="margin: 0;">Add the following to <code>Build Settings</code> ==> <code>Other Linker Flags</code>:
	<p>
    <ul style="margin-bottom: 15px;">
        <li style="margin: 0;">-ObjC</li>
        <li style="margin: 0;">-all_load</li>
        <li style="margin: 0;">-lxml2</li>
    </ul>
    </p>
    <p>
    <img src="http://dl.dropbox.com/u/6122/Kamcord/other_linker_flags2.png"/>
    </p>
</li>
</ol>

### Code

<ol>
<li>
<p>
Import Kamcord into your application delegate:

<pre><code>#import &lt;Kamcord/Kamcord.h&gt;
</code></pre>
</p>
</li>
<li style="margin: 0;">
<p>
In your application delegate (or wherever you create the <code>UIWindow</code> and initialize <code>CCDirector</code>), instantiate a <code>KCGLView</code>. This is our special sublcass of <code>CCGLView</code> that aids in video recording. You literally just need to replace <code>CCGLView</code> with <code>KCGLView</code>:
<pre><code>// Instantiate a KCGLView, which is a subclass with CCGLView with
// special recording functionality.
<b>KCGLView</b> * glView = [<b>KCGLView</b> viewWithFrame:[window_ bounds]
							      pixelFormat:kEAGLColorFormatRGB565
								  depthFormat:0 /* GL_DEPTH_COMPONENT24_OES */
						   preserveBackbuffer:NO
								   sharegroup:nil
							    multiSampling:NO
							  numberOfSamples:0];

</code></pre>
</p>
<li>We will provide you with a per-game Kamcord developer key and developer secret. Please set them when your app initializes or recording won't work.
<p>
<pre><code>[Kamcord setDeveloperKey:@"My_Developer_Key"
         developerSecret:@"My_Developer_Secret"];</code></pre>
</p>
</li>

<p>
<b>This must be done after </b><code>CCDirector</code><b> initialization is finished and before</b>:

<pre><code>[window addSubview:glView];
[window makeKeyAndVisible];
</code></pre>
</p>
<p>
The full examples further below lay this out very clearly.
</p>
</li>
</ol>

Your project should build successfully at this point.

## How to use Kamcord

We've tried to keep the Kamcord API as simple as possible. The only class you will need to interface with is `Kamcord`, which you can get by including `<Kamcord/Kamcord.h>`.

Kamcord's public API is broken down by different functionalities.

### Developer Key and Secret

You must set your Kamcord developer key and secret using this function:

	+(void) setDeveloperKey:(NSString *)key
	        developerSecret:(NSString *)secret;

We will give you a key and secret per game you build. We'll give you as many key/secret pairs you need, just don't tell them to anyone else.

**This function actually gets the **`KCGLView`** from the **`CCDirector`**, so (1) it should be the <i>first</i> Kamcord function called and (2) should only be called after **`CCDirector`** is fully prepared and initialized with the **`KCGLView`.

### Video Recording

The recording interface is built around the concept of one video, which has one or more clips. Most videos will just have one clip, but if your game is interrupted (for example, if the user gets a phone call), you'll have several clips that need to be stitched together into one seamless video. Kamcord handles all of that behind the scenes as long as you pause and resume your recording at the appropriate places in the app lifecycle.

The API is:

    +(void) startRecording;
    +(void) stopRecording;
    +(void) pause;
    +(void) resume;

`startRecording` starts the video recording, which you can pause and resume with `pause` and `resume`. Once you're done with the entire video, call `stopRecording`.

**Please be aware that video replay will NOT work in the simulator! The video will be recorded and it will be the right length, but it will be all black. You must test on a device to see the video replay actually work.**

### Video Quality

You can set the dimensions and quality of the recorded video:

	+(void) setVideoResolution:(KC_VIDEO_RESOLUTION)resolution
	    	           quality:(KC_VIDEO_QUALITY)quality;

There are two video dimension settings:

- `SMART_VIDEO_RESOLUTION`: 512x384 on all iPads, 480x320 on all iPhone/iPods.
- `FULL_VIDEO_RESOLUTION`: 1024x768 on all iPads, 480x320 on non-retina iPhone/iPods, and 960x480 on retina iPhone/iPods.

The two video quality settings are `HIGH_VIDEO_QUALITY` and `MEDIUM_VIDEO_QUALITY`.

Keep in mind that videos that are larger and have higher quality will take much longer to process and upload. We recommend running with  `SMART_VIDEO_RESOLUTION` and `MEDIUM_VIDEO_QUALITY` (the default). You should experiment with different combinations to see what works best for your games.

We currently don't support recording at iPad retina resolutions (2048x1536) because it seems that Apple doesn't support writing videos of those resolutions, but we plan to come back to this issue in the future.

### Background Audio

You can add a repeating background audio track to your videos by giving a filename and extension using the following API call:

	+(BOOL) setAudioResourceName:(NSString *)name
	    	           extension:(NSString *)extension;

For example, if you have a resource named `game_background.wav`, call this method with `"game_background"` and `"wav"`. This method returns `YES` if the specified audio file was found. Otherwise, it returns `NO`. We suport all the common file formats (`aac`, `aif`, `caf`, `m4a`, `mp3`, and `wav`).

If the audio file is too long for the video, then we truncate the end to match the video length. If the audio file is too short for the video, we repeat it endlessly so that it plays throughout the entire video.

<b>Note that this audio track is only overlayed on the video once the video processing is finished.</b> We begin video processing in the background as soon as you call `stopRecording`, but the video you watch via the `Replay Video` button on the Kamcord UI may show the preprocessed video (without the audio overlay).

If you have any existing game background music, we recommend you use this API call. It makes for a much better viewer experience. The `RenderTextureTest` example below shows this in action.

### Presenting User Options

Now that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	+(void) showView;

This presents a modal view with the following options:

<p>
<ul>
    <li style="margin: 0;">Replay video</li>
    <li style="margin: 0;">Share</li>
</ul>
</p>

`Replay video` will show the video of the gameplay that just happened (the result of the last `stopRecording` call). 

`Share` will bring the user to a new view that lets them enter a message and select Facebook, Twitter, YouTube, and/or email. When the user taps the `Share` button on this second view, we upload the video to our servers and share their message to their selected social networks. The first time the user selects Facebook, Twitter, or YouTube, he will be prompted for the relevant credentials and permissions.

All uploading to YouTube and sharing on Facebook/Twitter happens in a background thread. Based on testing, this has negligible impact on performance and provides for a great user experience, because your user can hit `Share` and get back to playing your game  as soon as possible.

On Facebook, we will share the URL of the video with their typed message. A thumbnail from the video will be automatically generated and shown. On Twitter, if the user types the following message:

`Check out my gameplay!`

the actual tweeted message will be

`Check out my gameplay! | kamcord.com/v/abcfoobar123`

where the kamcord.com URL will instantly <a href="http://en.wikipedia.org/wiki/HTTP_302">HTTP 302</a> redirect to the corresponding YouTube video.

### Developer Settings

A YouTube video looks like this:

<img src="http://dl.dropbox.com/u/6122/Kamcord/youtube_video2.png"/>

You can set the title, description, and keywords (highlighted in the orange boxes) with the following function:

	+(void) setYouTubeTitle:(NSString *)title
     	        description:(NSString *)description 
                   keywords:(NSString *)keywords;

`youtubeKeywords` is one string of word tokens delimited by commas (e.g. `"multi-word keyword, another multiword keyword, keyword3, keyword4"`).

A Facebook wall post looks like the following:

<img src="http://dl.dropbox.com/u/6122/Kamcord/facebook_share.png"/>

The `Message` is the text the user will enter. You can set the title, caption, and description with the following function:

	+(void) setFacebookTitle:(NSString *)title
   	                 caption:(NSString *)caption
                 description:(NSString *)description;

When the user shares to Facebook, their video is first uploaded to Kamcord. We will then use your settings to populate the corresponding fields on Facebook. Needless to say, this is a great way to advertise your game by putting links to your website or your game's page on the Apple App Store.

It's worth noting that every time we post to Facebook, we use the currently set values of these fields. Therefore, you may want to change the title, caption, and or description to match the results of the most recent gameplay. We recommend you do this so that the message looks more customized which should result in more clicks on the video.

Another function you need to set after you call `stopRecording` is:

	+(void) setLevel:(NSString *)level
     	       score:(NSNumber *)score;
	
These values should be set per video. This metadata will be uploaded along with the video and be used to better organize videos for viewers.

## Examples

The `Examples` directory has some fully functional examples of how to use Kamcord in your application. You will recognize these as test apps that come bundled with Cocos2D. The following test apps have been ported over to `Kamcord`:

<ul>
    <li style="margin: 0;">ParticleTest</li>
    <li style="margin: 0;">RenderTextureTest</li>
    <li style="margin: 0;">RotateWorldTest</li>
    <li style="margin: 0;">SceneTest</li>
    <li style="margin: 0;">SpriteTest</li>
</ul>

### RenderTextureTest

When this app launches, there are two buttons on the top right of the screen you can press to start and stop video recording. Play around by pressing `Start Recording`, doing some drawing or flipping between different tests, and then pressing `Stop Recording`. The Kamcord dialog should pop up and you'll be able to replay a video recording of your actions as well as share that video online.

Below are all of the code integration points inside `Examples/cocos2d-iphone-2.0-rc2/tests/BaesAppController.m`. We bold the lines we added to make Kamcord work. First, include the library:

<pre><code><b>#import &lt;Kamcord/Kamcord.h&gt;</b>
</code></pre>

Then do all the Kamcord initialization:

<pre><code>- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	// Main Window
	window_ = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	
	// Director
	director_ = (CCDirectorIOS*)[CCDirector sharedDirector];
	[director_ setDisplayStats:NO];
	[director_ setAnimationInterval:1.0/60];
	<b>
	// GL View
	KCGLView * __glView = [KCGLView viewWithFrame:[window_ bounds]
									  pixelFormat:kEAGLColorFormatRGB565
									  depthFormat:0 /* GL_DEPTH_COMPONENT24_OES */
							   preserveBackbuffer:NO
									   sharegroup:nil
								    multiSampling:NO
								  numberOfSamples:0];
	</b>
	[director_ setView:__glView];
	[director_ setDelegate:self];
	director_.wantsFullScreenLayout = YES;

	// Retina Display ?
	[director_ enableRetinaDisplay:useRetinaDisplay_];
	
	// Navigation Controller
	navController_ = [[UINavigationController alloc] initWithRootViewController:director_];
	navController_.navigationBarHidden = YES;
    <b>
    // This must go after CCDirector initialization is finished and before
    // window_ addSubView and makeKeyAndVisible
    [Kamcord setDeveloperKey:@"kamcord-test" developerSecret:@"kamcord-test"];
    </b>
	[window_ addSubview:navController_.view];
	[window_ makeKeyAndVisible];

	return YES;
}
</code></pre>

Inside `Examples/cocos2d-iphone-2.0-rc2/tests/RenderTextureTest.m`, add the "Start Recording" and "Stop Recording" buttons and insert the corresponding Kamcord hooks.

<pre><code>@implementation KamcordRecording
-(id) init
{
	if( (self = [super init]) ) {

		
		CCDirector *director = [CCDirector sharedDirector];
		
		// Testing multiple OpenGL locks
		if( [NSThread currentThread] != [director runningThread] )
			[(CCGLView*)[director view] lockOpenGLContext];
		
		CGSize s = [[CCDirector sharedDirector] winSize];

		// create a render texture, this is what we're going to draw into
		target = [[CCRenderTexture alloc] initWithWidth:s.width height:s.height pixelFormat:kCCTexture2DPixelFormat_RGBA8888];
		[target setPosition:ccp(s.width/2, s.height/2)];


		// It's possible to modify the RenderTexture blending function by
//		[[target sprite] setBlendFunc:(ccBlendFunc) {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}];

		// note that the render texture is a CCNode, and contains a sprite of its texture for convience,
		// so we can just parent it to the scene like any other CCNode
		[self addChild:target z:-1];

		// create a brush image to draw into the texture with
		brush = [[CCSprite spriteWithFile:@"fire.png"] retain];
		[brush setColor:ccRED];
		[brush setOpacity:20];
#ifdef __CC_PLATFORM_IOS
		self.isTouchEnabled = YES;
#elif defined(__CC_PLATFORM_MAC)
		self.isMouseEnabled = YES;
		lastLocation = CGPointMake( s.width/2, s.height/2);
#endif

		// Save Image menu
		[CCMenuItemFont setFontSize:16];
        <b>CCMenuItem *item1 = [CCMenuItemFont itemWithString:@"Start Recording" target:self selector:@selector(startRecording:)];
		CCMenuItem *item2 = [CCMenuItemFont itemWithString:@"Stop Recording" target:self selector:@selector(stopRecordingAndShowDialog:)];</b>
		
		CCMenu *menu = [CCMenu menuWithItems:item1, item2, nil];
		[self addChild:menu];
		[menu alignItemsVertically];
		[menu setPosition:ccp(s.width-80, s.height-30)];
		
		if( [NSThread currentThread] != [director runningThread] )
			[(CCGLView*)[director view] unlockOpenGLContext];
	}
	return self;
}
<b>
-(void) startRecording:(id)sender
{
    [Kamcord startRecording];
}

-(void) stopRecordingAndShowDialog:(id)sender
{
    [Kamcord stopRecording];
    [Kamcord showView];
}</b></code></pre>

For most games, you'll want to defer the calls to `startRecording` until appropriate (your user begins the actual level, etc.).

To highlight the handling of the application lifecycle, we've made additions to the following functions:

<pre><code>-(void) applicationWillResignActive:(UIApplication *)application
{
	[[CCDirecto shraredDirector] pause];
    <b>[Kamcord pause];</b>
}

-(void) applicationDidBecomeActive:(UIAplicpation *)applicaton
{i
    <b>[Kamcord resume];</b>
	[[CCDirector sharedDirector] resume];
}
</code></pre>

That's all you have to do to manage the applicaton lifecycle. If no video is currently being recorded (i.e. `startRecording` has not been called), the calls to `pause` and `resume` do nothing.

To test this functionality, press `Start Recording`, play with the app, then close it by pressing the home button. Re-open the app, do some more actions, then press `Stop Recording`. When the Kamcord dialog appears, select `Replay Video`. It should show one seamless video of everything that's happened.

<b>Note: in your game, you should defer calling</b> `resume` <b>until your user resumes gameplay. Calling it in</b> `applicationDidBecomeActive:` <b>like in this example will capture the pause screen of your game, which is probably not what you or your user wants.</b>

## Contact Us

If you have any questions or comments, don't hesitate to email Matt at <a href="mailto:matt@kamcord.com">matt@kamcord.com</a> (650.267.1051). We reply to every email!

