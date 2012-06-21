# Kamcord 0.9.2

## Code

The code is available at the following git repository: <a href="https://github.com/kamcord/cocos2d-2.0-kamcord">https://github.com/kamcord/cocos2d-2.0-kamcord</a>.

Please add yourself as a watcher since we frequently release new features and patches.

## Introduction

Kamcord is a built-in gameplay recording technology for iOS. This repository contains a Kamcord SDK that works with cocos2d-2.0-rc2 and allows you, the game developer, to capture gameplay videos with a very simple API.
Your users can then replay and share these gameplay videos via YouTube, Facebook, Twitter, and email.

In order to use Kamcord, you need a developer key and developer secret. To get these, please email Matt at <a mailto="matt@kamcord.com">matt@kamcord.com</a>.

**Kamcord works on iOS 5+ and gracefully turns itself off on iOS 4**. You can still run without problems on versions of iOS before iOS 5, though you will not be able to to record video. Kamcord works on the iPhone 3GS, iPhone 4, iPhone 4S, iPod Touch 3G and 4G, and all iPads.

We will be making lots of improvements and adding many features over the next few months. We'd love to hear your feedback and thoughts. If you have any questions or comments, please don't hesitate to email or call Matt at <a href="mailto:matt@kamcord.com">matt@kamcord.com</a> (650.267.1051).

## Gameplay Recordings

Check out some gameplays recorded with Kamcord:

<p>
	<ul>
	<li>
		<a target="_blank" href="http://www.youtube.com/watch?v=C4yM_iZSKxk">Mr. Ball</a> (<a target="_blank" href="http://itunes.apple.com/us/app/mr.-ball/id521546799">Apple App Store</a>)
	</li>
	<li>
		<a target="_blank" href="http://www.youtube.com/watch?v=rpPb2NhlD0Q">Platform Hell</a> (<a target="_blank" href="http://itunes.apple.com/us/app/platform-hell-pro/id428765417">Apple App Store</a>)
	</li>
	<li>
		<a target="_blank" href="http://www.youtube.com/watch?v=R2zqZ0FJ6yI">Adhesion</a> (<a target="_blank" href="http://itunes.apple.com/us/app/adhesion/id501869784">Apple App Store</a>)
	</li>
	<li>
		<a target="_blank" href="http://kamcord.com/v/8Pm4x61dTEQ/">Sewar Wars</a> (<a target="_blank" href="http://www.sewerwars.com">Website</a>)
	</li>
	<li>
		<a target="_blank" href="http://kamcord.com/v/D2I3G5o8dO/">Carl The Spider</a> (<a target="_blank" href="http://itunes.apple.com/us/app/carl-the-spider/id504163507">Apple App Store</a>)
	</li>
	<li>
		<a target="_blank" href="http://kamcord.com/v/So5sOMb8pn/">Atlantis Oceans</a> (<a target="_blank" href="http://itunes.apple.com/us/app/atlantis-oceans/id384836591">Apple App Store</a>)
	</li>
	</ul>
</p>
	

## A Sample Application

Before we explain how to use Kamcord in your own applications, let's go through a quick example that runs right out the box. Clone this repository to your local machine and open the project located at `Examples/cocos2d-iphone-2.0-rc2/cocos2d-ios.xcodeproj`.  Select `RotateWorldTest` from the dropdown and build and run that application. You should see the familiar `RotateWorldTest` from the Cocos2D suite of tests. **Make sure to run the application on a physical device with iOS 5+, not the simulator. Video replay is NOT supported by the simulator!**

After 10 seconds, the Kamcord view should appear allowing you to replay a video recording of those first 10 seconds and share that video via Facebook, Twitter, YouTube, and/or email. `ParticleTest`, `SceneTest`, and `SpriteTest` all work the same way.

`RenderTextureTest` is different in that it allows you to start and stop recording by pressing the two corresponding buttons at the top right of the screen. When you press `Stop Recording`, you will again see the Kamcord view with options to replay and share. Later on in this documentation, we'll walk through all the code needed to add recording and replay functionalities to `RenderTextureTest`.

There is no practical limit on how long you can record for. Everything gets written immediately to disk and old videos are always being erased, so the only real limitation is the device's hard drive size. Since modern iOS devices have 16+ GB of hard disk space, you can safely record one continuous gameplay video for over 24 hours straight, an upper limit your gamers will probably never run into.

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
    <p>
    <b>To support iOS 4 deployment, set the frameworks inside the orange box to <code>Optional</code>. This will allow your app to run on devices with iOS 4 and ensures Kamcord functionality will gracefully silence itself on iOS 4 as if you had never installed Kamcord.</b>
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
<li>We will provide you with a per-game Kamcord developer key and developer secret. Please set them along with your app name when your app initializes or recording won't work.
<p>
<pre><code>[Kamcord setDeveloperKey:@"My_Developer_Key"
         developerSecret:@"My_Developer_Secret"
                 appName:@"My_Game_Name"];</code></pre>
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

### Developer Key, Secret, and Application Name

You must set your Kamcord developer key, secret, and app name using this function:

	+ (void) setDeveloperKey:(NSString *)key
	         developerSecret:(NSString *)secret
	                 appName:(NSString *)name;

We will give you a key and secret per game you build. We'll give you as many key/secret pairs you need, just don't tell them to anyone else.

**This function actually gets the **`KCGLView`** from the **`CCDirector`**, so (1) it should be the <i>first</i> Kamcord function called and (2) should only be called after **`CCDirector`** is fully prepared and initialized with the **`KCGLView`.

### Video Quality

You can set the resolution of the recorded video:

	+ (void) setVideoResolution:(KC_VIDEO_RESOLUTION)resolution;

There are two video resolution settings:

- `SMART_VIDEO_RESOLUTION`: 512x384 on iPad 1 and 2, 1024x768 on iPad , and 480x320 on all iPhone/iPods.
- `TRAILER_VIDEO_RESOLUTION`: 1024x768 on all iPads, 480x320 on non-retina iPhone/iPods, and 960x480 on retina iPhone/iPods.

`SMART_VIDEO_RESOLUTION` is the default setting and should be used when you deploy your game. As the name suggests, `TRAILER_VIDEO_RESOLUTION` is only intended for you to make trailers with. Releasing your game with `TRAILER_VIDEO_RESOLUTION` is **strongly** discouraged. It will eat up your user's data plan, CPU, game resources (FPS), battery and result in video uploads that are more than five times longer (and thus potentially more network failures).

We currently don't support recording at iPad retina resolutions (2048x1536) because it seems that Apple doesn't support writing videos of those resolutions, but we plan to come back to this issue in the future.

### Audio Recording

As of version 0.9.2, you can overlay your game's audio to the recorded video with the following API calls:

	+ (KCAudio *) playSound:(NSString *)filename
    	               loop:(BOOL)loop;
	+ (KCAudio *) playSound:(NSString *)filename;

The second function call simply calls the first with `loop` set to `NO`. These sounds *are not sent to the speakers*, but will be added to the recorded video at the exact time you call `playSound`. The intended use of these methods is to pair calls to `CocosDenshion` (or whichever sound engine you use) with calls to `Kamcord` like so:

	// One time sounds
	[[SimpleAudioEngine sharedEngine] playEffect:@"sound.wav"];
	[Kamcord playSound:@"sound.wav"];
	
	// Background sounds
	[[SimpleAudioEngine sharedEngine] playBackgroundMusic:@"background.mp3"];
	[Kamcord playSound:@"background.mp3" loop:YES];

If you'd ever like to stop a sound from playing in the recording, you can save the `KCAudio *` object that is returned by `playSound` and call `stop` on that object. You don't need to call `start` on the returned `KCAudio` object, `[Kamcord playSound:]` will take care of that for you.

For convenience, we've added a method to stop all sounds:

	+ (void) stopAllSounds:(BOOL)loop;
	
If `loop` is `NO`, this will only stop non-looping sounds. If `loop` is `YES`, this will stop ALL sounds.

The `RenderTextureTest` example below shows how to record sound.

**Note that this audio track is only overlayed on the video once the video processing is finished.** We begin video processing in the background as soon as you call stopRecording, but the video you watch via the Replay Video button on the Kamcord UI may show the preprocessed video (without the audio overlay). Don't worry, the final video that is shared on Facebook/Twitter and uploaded to YouTube *will* have the sounds overlayed.

We are currently working on adding the played sounds to the replayed video. In the future, we intend to wrap calls to `CocosDenshion` so that you don't have to worry about pairing sounds calls together.

### Presenting User Options

Now that the user has finished his gameplay and you have successfully recorded a video of it, you can present several options to the user with the following API call:

	+ (void) showView;

This presents a modal view with the following options:

<img src="https://dl.dropbox.com/u/6122/Kamcord/MainMenu.png" style="display: block; margin-left: auto; margin-right: auto;" />

`Replay video` will show the video of the gameplay that just happened (the result of the last `stopRecording` call).

`Share` will bring the user to a new view that lets them enter a message and select Facebook, Twitter, YouTube, and/or email. When the user taps the `Share` button on this second view, we upload the video to our servers and share their message to their selected social networks. The first time the user selects Facebook, Twitter, or YouTube, he will be prompted for the relevant credentials and permissions.

<img src="https://dl.dropbox.com/u/6122/Kamcord/ShareView.png" style="display: block; margin-left: auto; margin-right: auto;" />

All uploading to YouTube and sharing on Facebook/Twitter happens in a background thread. Based on testing, this has negligible impact on performance and provides for a great user experience, because your user can hit `Share` and get back to playing your game  as soon as possible.

On Facebook, we will share the URL of the video with their typed message. A thumbnail from the video will be automatically generated and shown. On Twitter, if the user types the following message:

`Check out my gameplay!`

the actual tweeted message will be

`Check out my gameplay! | kamcord.com/v/abcfoo123`

### Downloading Video Trailers

To get to the recorded videos from your device, click on `Window` ==> `Organizer`, select your device on the left hand side, and select your app from the apps list:

<img src="https://dl.dropbox.com/u/6122/Kamcord/Organizer.png" />

Click the `Download` button at the bottom of the window and you should get a folder on your computer that is a full copy of your device's filesystem. You can then browse to `Documents/Kamcord` and find the `GUID__coverted.mov` for your trailer.

### Developer Settings

A YouTube video looks like this:

<img src="http://dl.dropbox.com/u/6122/Kamcord/youtube_video2.png"/>

You can set the title, description, and keywords (highlighted in the orange boxes) with the following function:

	+ (void) setYouTubeTitle:(NSString *)title
     	         description:(NSString *)description 
                    keywords:(NSString *)keywords;

`youtubeKeywords` is one string of word tokens delimited by commas (e.g. `"multi-word keyword, another multiword keyword, keyword3, keyword4"`).

A Facebook wall post looks like the following:

<img src="http://dl.dropbox.com/u/6122/Kamcord/facebook_share.png"/>

The `Message` is the text the user will enter. You can set the title, caption, and description with the following function:

	+ (void) setFacebookTitle:(NSString *)title
   	                  caption:(NSString *)caption
                  description:(NSString *)description;

When the user shares to Facebook, their video is first uploaded to Kamcord. We will then use your settings to populate the corresponding fields on Facebook. Needless to say, this is a great way to advertise your game by putting links to your website or your game's page on the Apple App Store.

It's worth noting that every time we post to Facebook, we use the currently set values of these fields. Therefore, you may want to change the title, caption, and or description to match the results of the most recent gameplay. We recommend you do this so that the message looks more customized which should result in more clicks on the video.

Another function you need to set after you call `stopRecording` is:

	+ (void) setLevel:(NSString *)level
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
    [Kamcord setDeveloperKey:@"kamcord-test"
    		 developerSecret:@"kamcord-test"
    		         appName:@"A Test App"];
    </b>
	[window_ addSubview:navController_.view];
	[window_ makeKeyAndVisible];

	return YES;
}
</code></pre>

Inside `Examples/cocos2d-iphone-2.0-rc2/tests/RenderTextureTest.m`, add the "Start Recording" and "Stop Recording" buttons and insert the corresponding Kamcord hooks.

<pre><code>@interface KamcordRecording ()

@property (nonatomic, retain) KCAudio * sound1;
@property (nonatomic, retain) KCAudio * sound2;

@property (nonatomic, retain) AVAudioPlayer * audioPlayer1;
@property (nonatomic, retain) AVAudioPlayer * audioPlayer2;

@end

@implementation KamcordRecording
{
    KCAudio * sound1_;
    KCAudio * sound2_;
    
    AVAudioPlayer * audioPlayer1_;
    AVAudioPlayer * audioPlayer2_;
}

@synthesize sound1 = sound1_;
@synthesize sound2 = sound2_;

@synthesize audioPlayer1 = audioPlayer1_;
@synthesize audioPlayer2 = audioPlayer2_;
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
        CCMenuItem *item2 = [CCMenuItemFont itemWithString:@"Stop Recording" target:self selector:@selector(stopRecordingAndShowDialog:)];
		CCMenuItem *item3 = [CCMenuItemFont itemWithString:@"Play Sound #1" target:self selector:@selector(playSound1:)];
        CCMenuItem *item4 = [CCMenuItemFont itemWithString:@"Play Sound #2" target:self selector:@selector(playSound2:)];
        CCMenuItem *item5 = [CCMenuItemFont itemWithString:@"Stop Sound #1" target:self selector:@selector(stopSound1:)];
        CCMenuItem *item6 = [CCMenuItemFont itemWithString:@"Stop Sound #2" target:self selector:@selector(stopSound2:)];
        CCMenuItem *item7 = [CCMenuItemFont itemWithString:@"Stop All Sounds" target:self selector:@selector(stopAllSounds:)];
		CCMenu *menu = [CCMenu menuWithItems:item1, item2, item3, item4, item5, item6, item7, nil];
</b>
		
		CCMenu *menu = [CCMenu menuWithItems:item1, item2, nil];
		[self addChild:menu];
		[menu alignItemsVertically];
		[menu setPosition:ccp(s.width-80, s.height<b>-90</b>)];
		
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
}

-(void) startRecording:(id)sender
{
    [Kamcord startRecording];
}

-(void) stopRecordingAndShowDialog:(id)sender
{
    [Kamcord stopRecording];
    [Kamcord showView];
}

-(void) playSound1:(id)sender
{
    if (!self.audioPlayer1)
    {
        NSURL * url = [[NSBundle mainBundle] URLForResource:@"test8" withExtension:@"caf"];
        self.audioPlayer1 = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
    }
    
    if ([self.audioPlayer1 play]) {
        self.sound1 = [Kamcord playSound:@"test8.caf"];
    }
}

-(void) playSound2:(id)sender
{
    if (!self.audioPlayer2)
    {
        NSURL * url = [[NSBundle mainBundle] URLForResource:@"test3" withExtension:@"m4a"];
        self.audioPlayer2 = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:nil];
    }
    
    if ([self.audioPlayer2 play]) {
        self.sound2 = [Kamcord playSound:@"test3.m4a"];
    }
}

-(void) stopSound1:(id)sender
{
    [self.audioPlayer1 stop];
    [self.sound1 stop];
}

-(void) stopSound2:(id)sender
{
    [self.audioPlayer2 stop];
    [self.sound2 stop];
}

-(void) stopAllSounds:(id)sender
{
    [self.audioPlayer1 stop];
    [self.audioPlayer2 stop];
    [Kamcord stopAllSounds:NO];
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

## Other Kamcord details

### Mixpanel

We collect analytics on user behavior. Specifically, we keep track of how often users replay videos, how often they share to social networks, which social networks they share to, etc. The information we track is purely aggregate statistics and **not** personally identifiable, so you can rest assured there are no privacy concerns for your end users.

### Amazon Simple Storage Service (S3)

Kamcord stores videos on Amazon S3, hence why we need `AWSiOSSDK.framework`.

## Troubleshooting

Below are various integration issues that some game developers have run into.

### Application crashes when you press [Done] on the main Kamcord view

Make sure that there is only **one** view controller in your application delegate, and barring some strange cases, that root view controller should be an instance of `KCViewController`. We've seen cases where people have had both a `RootViewController` and a `KCViewController` instantiated inside their app delegate. Removing the `RootViewController` solved the crash problems.

### Video uploads to kamcord.com don't succeed

Kamcord uploads videos in the background. This allows your user to get back to playing your game right away. Even after your app loses foreground, we still have 10 mins of time to upload. In the case that we can't finish it in those 10 minutes, we queue the job for next time the app regains foreground, and keep doing this until the video upload succeeds.

If you are testing Kamcord with XCode and press the `Stop` button too soon after you press `Share`, the video will most likely not have finished uploading. This is especially true for videos recorded with `TRAILER_VIDEO_RESOLUTION` since they are about 5x larger than those recorded with `SMART_VIDEO_RESOLUTION`. Videos also upload much more quickly on WiFi than 3G. To ensure the video upload succeeds, just leave the app running for a sufficient time and check the video on kamcord.com. 

### armv6

Kamcord only supports i386 and armv7. If you need an armv6 build for some reason, <a href="mailto:matt@kamcord.com" />shoot us an email</a>.

## Contact Us

If you have any questions or comments, don't hesitate to email Matt at <a href="mailto:matt@kamcord.com">matt@kamcord.com</a> (650.267.1051). We reply to every email!

