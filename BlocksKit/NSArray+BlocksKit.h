//
//  NSArray+BlocksKit.h
//  BlocksKit
//

#import "BlocksKit_Globals.h"

/** Block extensions for NSArray.

 Both inspired by and resembling Smalltalk syntax, these utilities
 allows for iteration of an array in a concise way that
 saves quite a bit of boilerplate code for filtering or finding
 objects or an object.

 Includes code by the following:

- Robin Lu.       <https://github.com/robin>.      2009. MIT.
- Michael Ash.    <https://github.com/mikeash>.    2010. BSD.
- Aleks Nesterow. <https://github.com/nesterow>.   2010. BSD.
- Zach Waldowski. <https://github.com/zwaldowski>. 2011. MIT.

 @see NSDictionary(BlocksKit)
 @see NSSet(BlocksKit)
 */
@interface NSArray (BlocksKit)

/** Loops through an array and executes the given block with each object.
 
 @param block A single-argument, void-returning code block.
 */
- (void)each:(BKSenderBlock)block;

/** Loops through an array and returns the object matching the block.
 
 @param block A single-argument, `BOOL`-returning code block.
 @return Returns the object if found, `nil` otherwise.
 @see select:
 */
- (id)match:(BKValidationBlock)block;

/** Loops through an array and returns an array of the objects matching the block.
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns an array of the objects found, `nil` otherwise.
 @see match:
 */
- (NSArray *)select:(BKValidationBlock)block;

/** Loops through an array and returns an array of all objects but the ones matching the block.
 
 This selector performs *literally* the exact same function as select: but in reverse.
 
 This is useful, as one may expect, for removing objects from an array.
     NSArray *new = [computers reject:^BOOL(id obj) {
       return ([obj isUgly]);
     }];
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns an array of all objects not found, `nil` if all are excluded.
 */
- (NSArray *)reject:(BKValidationBlock)block;

/** Call the block once for each object and create an array of the return values.
 
 This is sometimes referred to as a transform, mutating one of each object:
     NSArray *new = [stringArray map:^id(id obj) {
       return [obj stringByAppendingString:@".png"]);
     }];
 
 @warning *Important:* the block can NOT return nil for a given object.  If you
 really have nothing to insert, pass `[NSNull null]` as the return value.
 
 @param block A single-argument, object-returning code block.
 @return Returns an array of the objects returned by the block.
 */
- (NSArray *)map:(BKTransformBlock)block;

/** Arbitrarily accumulate objects using a block.
 
 The concept of this selector is difficult to illustrate in words. The sum can
 be any NSObject, including (but not limited to) an NSString, NSNumber, or NSValue.
 
 For example, you can concentate the strings in an array:
     NSString *concentrated = [stringArray reduce:@"" withBlock:^id(id sum, id obj) {
       return [sum stringByAppendingString:obj];
     }];
 
 You can also do something like summing the lengths of strings in an array:
     NSNumber *sum = [stringArray reduce:nil withBlock:^id(id sum, id obj) {
       return [NSNumber numberWithInteger: [sum integerValue] + obj.length];
     }];
     NSUInteger value = [sum integerValue];

 @param initial The value of the reduction at its start.
 @param block A block that takes the current sum and the next object to return the new sum.
 @return An accumulated value.
 */
- (id)reduce:(id)initial withBlock:(BKAccumulationBlock)block;

@end