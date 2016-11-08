//
//  AppDelegate.h
//  CoreData_Study
//
//  Created by juju on 2016/11/8.
//  Copyright © 2016年 juju. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (readonly, strong) NSPersistentContainer *persistentContainer;

- (void)saveContext;


@end

