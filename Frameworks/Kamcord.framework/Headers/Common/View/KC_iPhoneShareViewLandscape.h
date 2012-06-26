//
//  KC_iPhoneShareView.h
//  cocos2d-ios
//
//  Created by Chris Grimm on 6/22/12.
//  Copyright (c) 2012 Kamcord. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KC_iPhoneViewLandscape.h"
#import "HintTextView.h"
#import "KCViewController.h"

#import "KC_ShareMessageDelegate.h"

@interface KC_iPhoneShareViewLandscape : KCViewController <UITextViewDelegate, KCShareDelegate>
@property (retain, nonatomic) KC_BaseView *parent;
@property (retain, nonatomic) HintTextView *textView;

-(id)initWithTitle:(NSString *)title parent:(KC_BaseView *)parent text:(NSString *)text delegate:(id)delegate;

@end
