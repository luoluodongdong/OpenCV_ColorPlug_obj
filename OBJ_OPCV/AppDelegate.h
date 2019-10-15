//
//  AppDelegate.h
//  OBJ_OPCV
//
//  Created by 曹伟东 on 2019/2/17.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ScanWindowsTitle.h"
#import "colorPlug.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    IBOutlet NSViewController *_mainVC;
    IBOutlet NSButton *_callColorBtn;
    
    //Get Color Value
    IBOutlet NSButton *_getValueBtn;
    IBOutlet NSTextField *_pointX;
    IBOutlet NSTextField *_pointY;
    IBOutlet NSTextField *_printValueTF;
}
-(IBAction)callColorPlugAction:(id)sender;
-(IBAction)getValueBtn:(id)sender;

@end

