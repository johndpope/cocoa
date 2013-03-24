//
//  Person.m
//  RaiseMan
//
//  Created by Sang Chul Choi on 3/23/13.
//  Copyright (c) 2013 Sang Chul Choi. All rights reserved.
//

#import "Person.h"

@implementation Person
@synthesize personName;
@synthesize expectedRaise;
- (id)init {
    self = [super init];
    if (self) {
        expectedRaise = 0.05;
        personName = @"New Person";
    }
    return self;
}
- (void)setNilValueForKey:(NSString *)key
{
    if ([key isEqual:@"expectedRaise"]) {
        [self setExpectedRaise:0.0];
    } else {
        [super setNilValueForKey:key];
    }
}
@end
