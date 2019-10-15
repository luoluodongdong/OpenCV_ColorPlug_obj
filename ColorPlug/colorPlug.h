//
//  colorPlug.h
//  OBJ_OPCV
//
//  Created by 曹伟东 on 2019/2/18.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface colorPlugView : NSViewController
{
    IBOutlet NSButton *_testBtn;
    IBOutlet NSPopUpButton *_pointTimesBtn;
    IBOutlet NSPopUpButton *_modeBtn;
    IBOutlet NSImageView *_screenView;
    IBOutlet NSImageView *_outputView;
    IBOutlet NSButton *_startBtn;
    IBOutlet NSButton *_saveBtn;
    IBOutlet NSTextField *_printLabel;
    
}

//@property (nonatomic) IBOutlet NSTextView *_logView;
//@property (nonatomic) NSString *_logString;
//@property (nonatomic) BOOL _isShowView;

-(IBAction)testBtnAction:(id)sender;
-(IBAction)pointTimesBtnAction:(id)sender;
-(IBAction)saveBtnAction:(id)sender;
-(IBAction)modeBtnAction:(id)sender;
-(IBAction)startBtnAction:(id)sender;

@property (nonatomic) int displayW;
@property (nonatomic) int displayH;
@property (nonatomic) NSString *_plistFile;
-(int)getColorValue:(NSPoint )point pTimes:(int )times;
//-(void)printTTLogString:(NSString *)log;
@end
