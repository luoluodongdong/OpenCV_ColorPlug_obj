//
//  AppDelegate.m
//  OBJ_OPCV
//
//  Created by 曹伟东 on 2019/2/17.
//  Copyright © 2019年 曹伟东. All rights reserved.
//

#import "AppDelegate.h"
//#import "myOpenCVUtils.h"
//#import "ScanWindowsTitle.h"

@interface AppDelegate ()
{
    
    colorPlugView *_colorView;
}
@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    
    //*******color view********//
    _colorView=[[colorPlugView alloc]initWithNibName:@"colorPlugView" bundle:nil];
    
    _colorView.displayH = getDisplayHeight();
    _colorView.displayW = getDisplayWidth();
    NSLog(@"H:%d W:%d",_colorView.displayH,_colorView.displayW);
    _colorView._plistFile=@"color_config.plist";
    //*******end*color view*end********//
}
-(IBAction)callColorPlugAction:(id)sender{
    
    //_ttLogView._isShowView=YES;
    NSLog(@"Open Color View...");
    //[_ttLogView.view setFrameSize:NSMakeSize(640, 450)];
    [_mainVC presentViewControllerAsModalWindow:_colorView];
}
-(IBAction)getValueBtn:(id)sender{
    int x=[_pointX intValue];
    int y=[_pointY intValue];
    NSPoint point=NSMakePoint(x, y);
    int colorValue=[_colorView getColorValue:point pTimes:2];
    [_printValueTF setStringValue:[NSString stringWithFormat:@"Value:%d",colorValue]];
}
- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

-(void)windowShouldClose:(id)sender{
    NSLog(@"window close...");
    [NSApp terminate:NSApp];
}
@end
