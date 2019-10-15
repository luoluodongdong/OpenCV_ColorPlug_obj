//
//
//  AutoClickTest
//
//  Created by Weidong2 on 2018/6/13.
//  Copyright © 2018年 LUXShare-ICT. All rights reserved.
//
#include <stdio.h>

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import "ApplicationServices/ApplicationServices.h"
#import <CoreGraphics/CoreGraphics.h>

#define DEBUG_F 0

extern AXError _AXUIElementGetWindow(AXUIElementRef, CGWindowID* out);
//terminate app with kCGWindowOwnerName
bool terminateApp(NSString *OwnerName);
//title-->kCGWindowOwnerName point-->(x,y)
//bool moveWin2Position(NSString *title,CGPoint *point);
//scan opened windows return array of kCGWindowOwnerName
NSArray* scanOpenWin(void);
int getDisplayHeight(void);
int getDisplayWidth(void);

//return WindowOwnerName array of running apps
NSArray* scanOpenWin(void){
    NSMutableArray *winsList;
    // Get all the windows
    CFArrayRef windowListAll = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    NSArray* arr = CFBridgingRelease(windowListAll);
    winsList = [[NSMutableArray alloc] initWithCapacity:arr.count];
    for (NSMutableDictionary* entry in arr){
        if (entry == nil){
            break;
        }
        //id wndName=[entry objectForKey:(id)kCGWindowName];
        id wndName=[entry objectForKey:(id)kCGWindowOwnerName];
        //NSLog(@"wndName: %@",wndName);
        [winsList addObject:wndName];
        
    }
    //if(DEBUG_FLAG) NSLog(@"winsList: %@",winsList);
    return winsList;
}
int getDisplayHeight(void){
    int displayHeight = 0;
    CFArrayRef windowListAll = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    NSArray* arr = CFBridgingRelease(windowListAll);
    // NSUInteger count = [arr count]; //CFArrayGetCount(arr);
    // Loop through the windows
    for (NSMutableDictionary* entry in arr){
        if (entry == nil){
            break;
        }
        //if(DEBUG_FLAG) NSLog(@"enter:%@",entry);
        NSString *wndName=[entry objectForKey:(id)kCGWindowName];
        // NSInteger wndNumber=[[entry objectForKey:(id)kCGWindowNumber] intValue];
        // if(DEBUG_FLAG) NSLog(@"wndName:%@ number:%ld",wndName,wndNumber);
        if (![wndName isEqualToString: @"Dock"]){
            //不是自己想要的窗口继续下一个循环
            continue;
        }
        //找到属于自己app的窗口
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)[entry objectForKey:@"kCGWindowBounds"], &bounds);
        if(DEBUG_F) NSLog(@"bounds: %@",NSStringFromRect(bounds));
        displayHeight = bounds.size.height;
        return displayHeight;
    }
    return displayHeight;
}
int getDisplayWidth(void){
    int displayWidth = 0;
    CFArrayRef windowListAll = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    NSArray* arr = CFBridgingRelease(windowListAll);
    // NSUInteger count = [arr count]; //CFArrayGetCount(arr);
    // Loop through the windows
    for (NSMutableDictionary* entry in arr){
        if (entry == nil){
            break;
        }
        //if(DEBUG_FLAG) NSLog(@"enter:%@",entry);
        NSString *wndName=[entry objectForKey:(id)kCGWindowName];
        // NSInteger wndNumber=[[entry objectForKey:(id)kCGWindowNumber] intValue];
        // if(DEBUG_FLAG) NSLog(@"wndName:%@ number:%ld",wndName,wndNumber);
        if (![wndName isEqualToString: @"Dock"]){
            //不是自己想要的窗口继续下一个循环
            continue;
        }
        //找到属于自己app的窗口
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)[entry objectForKey:@"kCGWindowBounds"], &bounds);
        if(DEBUG_F) NSLog(@"bounds: %@",NSStringFromRect(bounds));
        displayWidth = bounds.size.width;
        return displayWidth;
    }
    return displayWidth;
}
/*
bool moveWin2Position(NSString *title,CGPoint *point){
    bool flag = 0;
    // Get all the windows
    CFArrayRef windowListAll = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    NSArray* arr = CFBridgingRelease(windowListAll);
    // NSUInteger count = [arr count]; //CFArrayGetCount(arr);
    // Loop through the windows
    for (NSMutableDictionary* entry in arr){
        if (entry == nil){
            break;
        }
        if(DEBUG_F) NSLog(@"enter:%@",entry);
        //NSString *wndName=[entry objectForKey:(id)kCGWindowName];
        NSString *wndName=[entry objectForKey:(id)kCGWindowOwnerName];
        NSInteger wndNumber=[[entry objectForKey:(id)kCGWindowNumber] intValue];
        if(DEBUG_F) NSLog(@"wndName:%@ number:%ld",wndName,wndNumber);
        if (![wndName isEqualToString: title]){
            //不是自己想要的窗口继续下一个循环
            continue;
        }
        //属于自己app的窗口
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)[entry objectForKey:@"kCGWindowBounds"], &bounds);
        if(DEBUG_F) NSLog(@"bounds: %@",NSStringFromRect(bounds));
        //根据pid获取窗口所属的app
        pid_t pid = [[entry objectForKey:(id)kCGWindowOwnerPID] intValue];
        AXUIElementRef appRef = AXUIElementCreateApplication(pid);
        if(DEBUG_F) NSLog(@"Ref = %@",appRef);
        //获取app所有的窗口
        CFArrayRef windowList;
        AXError error = AXUIElementCopyAttributeValue(appRef, kAXWindowsAttribute, (CFTypeRef *)&windowList);
        if(DEBUG_F) NSLog(@"WindowList = %@", windowList);
        if(DEBUG_F) NSLog(@"windowlist error = %d",(int)error);
        CFRelease(appRef);
        if (!windowList){
            if(DEBUG_F) NSLog(@"windowList is nil");
            continue;
        }
        for (int i=0;i<CFArrayGetCount(windowList);i++){
            //遍历app所有窗口，查找跟全局遍历所获得窗口的实体
            AXUIElementRef windowRef = (AXUIElementRef) CFArrayGetValueAtIndex( windowList, i);
            if(DEBUG_F) NSLog(@"windowRef:%@",windowRef);
            CGWindowID application_window_id = 0;
            _AXUIElementGetWindow(windowRef, &application_window_id);
            if (application_window_id == wndNumber){
                //找到
                if(DEBUG_F) NSLog(@"Found a wnd that number is:%u",application_window_id);
                //根据需要来操作窗口的位置，移动至桌面左上角
                CFTypeRef position;
                //CGPoint newPoint;
                //newPoint.x = 0;
                //newPoint.y = 0;
                if(DEBUG_F) NSLog(@"Create new position");
                position = (CFTypeRef)(AXValueCreate(kAXValueCGPointType, (const void *)&point));
                //setting new position
                AXUIElementSetAttributeValue(windowRef, kAXPositionAttribute, position);
                
                //得到运行的程序窗口，并置于最前面
                //ProcessSerialNumber myPSN = {kNoProcess,kNoProcess};
                //GetProcessForPID(pid, &myPSN);
                //SetFrontProcessWithOptions(&myPSN,kSetFrontProcessFrontWindowOnly);
                NSRunningApplication *runningApp= [NSRunningApplication runningApplicationWithProcessIdentifier:pid];
                [runningApp activateWithOptions:NSApplicationActivateIgnoringOtherApps];
                
                CFRelease(windowRef);
                flag = 1;
                [NSThread sleepForTimeInterval:0.1];
                
                break;
            }
            CFRelease(windowRef);
        }
        if(DEBUG_F) NSLog(@"end a loop ----------------------------");
        if(flag) break;
    } //for windowListAll
    return flag;
}
 */
bool terminateApp(NSString *OwnerName){
    bool bResult = 0;
    
    bool flag = 0;
    // Get all the windows
    CFArrayRef windowListAll = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly, kCGNullWindowID);
    NSArray* arr = CFBridgingRelease(windowListAll);
    // NSUInteger count = [arr count]; //CFArrayGetCount(arr);
    
    // Loop through the windowsListAll
    for (NSMutableDictionary* entry in arr){
        if (entry == nil){
            break;
        }
        if(DEBUG_F) NSLog(@"enter:%@",entry);
        //NSString *wndName=[entry objectForKey:(id)kCGWindowName];
        NSString *wndName=[entry objectForKey:(id)kCGWindowOwnerName];
        NSInteger wndNumber=[[entry objectForKey:(id)kCGWindowNumber] intValue];
        if(DEBUG_F) NSLog(@"wndName:%@ number:%ld",wndName,wndNumber);
        if (![wndName isEqualToString:OwnerName]){
            //不是自己想要的窗口继续下一个循环
            continue;
        }
        //appeared what we want
        flag=1;
        //属于自己app的窗口
        CGRect bounds;
        CGRectMakeWithDictionaryRepresentation((CFDictionaryRef)[entry objectForKey:@"kCGWindowBounds"], &bounds);
        if(DEBUG_F) NSLog(@"bounds: %@",NSStringFromRect(bounds));
        //根据pid获取窗口所属的app
        pid_t pid = [[entry objectForKey:(id)kCGWindowOwnerPID] intValue];
        //get application,terminate it
        NSRunningApplication *runningApp= [NSRunningApplication runningApplicationWithProcessIdentifier:pid];
        [runningApp terminate];
        [NSThread sleepForTimeInterval:1.0f];
        bResult=[runningApp isTerminated];
        
        
        
           // CFRelease(windowRef);
        //}
        if(DEBUG_F) NSLog(@"end a loop ----------------------------");
        if(flag) break;
    } //for windowListAll
    
    if(!flag) bResult=1;
    
    return bResult;
    
}


