//
//  RMDocument.m
//  RaiseMan
//
//  Created by Sang Chul Choi on 3/23/13.
//  Copyright (c) 2013 Sang Chul Choi. All rights reserved.
//

#import "RMDocument.h"
#import "Person.h"

@implementation RMDocument

// RMDocumentKVOContext enables this class to differentiate
// between its KVO messages and those intended for a superclass.
static void *RMDocumentKVOContext;

- (void)startObservingPerson:(Person *)person
{
    [person addObserver:self
             forKeyPath:@"personName"
                options:NSKeyValueObservingOptionOld
                context:&RMDocumentKVOContext];
    [person addObserver:self
             forKeyPath:@"expectedRaise"
                options:NSKeyValueObservingOptionOld
                context:&RMDocumentKVOContext];
}
- (void)stopObservingPerson:(Person *)person
{
    [person removeObserver:self
                forKeyPath:@"personName"
                   context:&RMDocumentKVOContext];
    [person removeObserver:self
                forKeyPath:@"expectedRaise"
                   context:&RMDocumentKVOContext];
}

- (id)init
{
    self = [super init];
    if (self) {
        // Add your subclass-specific initialization here.
        employees = [[NSMutableArray alloc] init];
    }
    return self;
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"RMDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *)aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
}

+ (BOOL)autosavesInPlace
{
    return YES;
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to write your document to data of the specified type. If outError != NULL, ensure that you create and set an appropriate error when returning nil.
    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.
    NSException *exception = [NSException exceptionWithName:@"UnimplementedMethod" reason:[NSString stringWithFormat:@"%@ is unimplemented", NSStringFromSelector(_cmd)] userInfo:nil];
    @throw exception;
    return nil;
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to read your document from the given data of the specified type. If outError != NULL, ensure that you create and set an appropriate error when returning NO.
    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead.
    // If you override either of these, you should also override -isEntireFileLoaded to return NO if the contents are lazily loaded.
    NSException *exception = [NSException exceptionWithName:@"UnimplementedMethod" reason:[NSString stringWithFormat:@"%@ is unimplemented", NSStringFromSelector(_cmd)] userInfo:nil];
    @throw exception;
    return YES;
}

- (void)setEmployees:(NSMutableArray *)a
{
    for (Person *person in employees) {
        [self stopObservingPerson:person];
    }
    employees = a;
    for (Person *person in employees) {
        [self stopObservingPerson:person];
    }
}

- (void)insertObject:(Person *)p inEmployeesAtIndex:(NSUInteger)index {
    NSLog(@"adding %@ to %@", p, employees);
    // Add the inverse of this operation to the undo stack
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self]
     removeObjectFromEmployeesAtIndex:index];
    if (![undo isUndoing]) {
        [undo setActionName:@"Add Person"];
    }
    // Add the Person to the array
    [self startObservingPerson:p];
    [employees insertObject:p atIndex:index];
}

- (void)removeObjectFromEmployeesAtIndex:(NSUInteger)index {
    Person *p = [employees objectAtIndex:index];
    NSLog(@"removing %@ from %@", p, employees);
    // Add the inverse of this operation to the undo stack
    NSUndoManager *undo = [self undoManager];
    [[undo prepareWithInvocationTarget:self] insertObject:p
                                       inEmployeesAtIndex:index];
    if (![undo isUndoing]) {
        [undo setActionName:@"Remove Person"];
    }
    [self stopObservingPerson:p];
    [employees removeObjectAtIndex:index];
}

- (void)changeKeyPath:(NSString *)keyPath
             ofObject:(id)obj
              toValue:(id)newValue
{
    // setValue:forKeyPath: will cause the key-value observing method
    // to be called, which takes care of the undo stuff
    [obj setValue:newValue forKeyPath:keyPath];
}

- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    if (context != &RMDocumentKVOContext)
    {
        // If the context does not match, this message
        // must be intended for our superclass.
        [super observeValueForKeyPath:keyPath
                             ofObject:object
                               change:change
                              context:context];
        return;
    }
    NSUndoManager *undo = [self undoManager];
    id oldValue = [change objectForKey:NSKeyValueChangeOldKey];
    // NSNull objects are used to represent nil in a dictionary
    if (oldValue == [NSNull null]) {
        oldValue = nil;
    }
    NSLog(@"oldValue = %@", oldValue);
    [[undo prepareWithInvocationTarget:self] changeKeyPath:keyPath
                                                  ofObject:object
                                                   toValue:oldValue];
    [undo setActionName:@"Edit"];
}

- (IBAction)createEmployee:(id)sender
{
    NSWindow *w = [tableView window];
    // Try to end any editing that is taking place
    BOOL editingEnded = [w makeFirstResponder:w];
    if (!editingEnded) {
        NSLog(@"Unable to end editing");
        return;
    }
    NSUndoManager *undo = [self undoManager];
    // Has an edit occurred already in this event?
    if ([undo groupingLevel] > 0) {
        // Close the last group
        [undo endUndoGrouping];
        // Open a new group
        [undo beginUndoGrouping];
    }

    // Create the object
    Person *p = [employeeController newObject];
    // Add it to the content array of ’employeeController’
    [employeeController addObject:p];
    // Re-sort (in case the user has sorted a column)
    [employeeController rearrangeObjects];
    // Get the sorted array
    NSArray *a = [employeeController arrangedObjects];
    // Find the object just added
    NSUInteger row = [a indexOfObjectIdenticalTo:p];
    NSLog(@"starting edit of %@ in row %lu", p, row);
    // Begin the edit in the first column
    [tableView editColumn:0
                      row:row
                withEvent:nil
                   select:YES];   
}
@end
