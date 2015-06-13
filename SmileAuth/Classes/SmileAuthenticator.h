//
//  SmileAuthenticator.h
//  TouchID
//
//  Created by ryu-ushin on 5/25/15.
//  Copyright (c) 2015 rain. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocalAuthentication/LocalAuthentication.h>
#import "SmileKeychainWrapper.h"
#import "SmileSettingVC.h"


#define DispatchMainThread(block, ...) if(block) dispatch_async(dispatch_get_main_queue(), ^{ block(__VA_ARGS__); })
typedef void(^AuthCompletionBlock)();
typedef void(^AuthErrorBlock)(LAError);

/*!
 @typedef SecurityType
 
 @brief  A struct about the SecurityType.
 
 @discussion
 There are four types, pass the SecurtiyType to destination View Controller for appropriate security interface.
 */
typedef NS_ENUM(int, SecurityType) {
    /*! For the user turn off the password switch, user need input their password once for turn the password off. */
    INPUT_ONCE,
    /*! For the user turn on the password switch, user need input their password twice to confirm their password match each other. */
    INPUT_TWICE,
    /*! For the user change the password, user need input their password three times for change to new password. */
    INPUT_THREE,
    /*! For the user open app, user can use touch ID or input password. */
    INPUT_TOUCHID,
};

@protocol AuthenticatorDelegate;

@interface SmileAuthenticator : NSObject

@property (nonatomic, copy) NSString * localizedReason;
@property (nonatomic, strong) SmileKeychainWrapper *keychainWrapper;
@property (nonatomic, assign) SecurityType securityType;
@property (nonatomic, strong) UIViewController *rootVC;
@property (nonatomic, weak) id <AuthenticatorDelegate> delegate;
/*!@brief <b>For customization</b>, use this property to customize tint color. The default color is pink.*/
@property (nonatomic, strong) UIColor *tintColor;
/*!@brief <b>For customization</b>, use this property to customize Touch ID icon. The default icon is the Apple official pink Touch ID icon.*/
@property (nonatomic, strong) NSString *touchIDIconName;
/*!@brief <b>For customization</b>, use this property to set the app logo to UI.*/
@property (nonatomic, strong) NSString *appLogoName;
/*!@brief <b>For customization</b>, use this property to set the backgroundImage.*/
@property (nonatomic, strong) UIImage *backgroundImage;
/*!@brief <b>For customization</b>, use this property to change passcode digit. The default digit is 4.*/
@property (nonatomic) NSInteger passcodeDigit;
/*!@brief <b>For customization</b>, change UINavigationBar to transparent, if set it to Yes.*/
@property (nonatomic) BOOL navibarTranslucent;
/*!@brief <b>For customization</b>, change to a black style UI, if set it to Yes.*/
@property (nonatomic) BOOL nightMode;

+(SmileAuthenticator*)sharedInstance;
+ (BOOL)canAuthenticateWithError:(NSError **) error;
+(BOOL)hasPassword;
+(BOOL)isSamePassword:(NSString *)userInput;
+(void)clearPassword;

-(void)userSetPassword:(NSString*)newPassword;
-(void)authenticateWithSuccess:(AuthCompletionBlock) authSuccessBlock andFailure:(AuthErrorBlock) failureBlock;
-(void)presentAuthViewController;
-(void)authViewControllerDismissed;
-(void)touchID_OR_PasswordAuthSuccess;
-(void)touchID_OR_PasswordAuthFail:(NSInteger)failCount;

@end

@protocol AuthenticatorDelegate <NSObject>
@optional
/*!The method is called when AuthViewController be presented*/
-(void)AuthViewControllerPresented;
@optional
/*!The method is called when AuthViewController be dismissed*/
-(void)AuthViewControllerDismssed;
@optional
/*!The method is called when user success authentication by using Touch ID & Passcode*/
-(void)userSuccessAuthentication;
@optional
/*!The method is called when authentication failed*/
-(void)userFailAuthenticationWithCount:(NSInteger)failCount;
@end
