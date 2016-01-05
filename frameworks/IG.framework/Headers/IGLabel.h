//
//  IGLabel.h
//
//  Copyright (c) 2012 Infragistics. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

NS_ASSUME_NONNULL_BEGIN

@class IGLabel;

/*!
 These specify where to split text when the bounds are encountered.
*/
typedef NS_ENUM(NSInteger, IGLineBreakMode)
{
    /** Wrapping occurs at word boundaries unless the word itself doesn't fit on a single line. */
    IGBreakByWordWrapping = 0,
    /** Wrapping occurs before the first character that does not fit. */
    IGBreakByCharWrapping,
    /** Lines are simply not drawn past the edge of the frame. */
    IGBreakByClipping,
    /** Each line is displayed so that the end fits in the frame and the missing text is indicated by an ellipsis glyph. */
    IGBreakByTruncatingHead,
    /** Each line is displayed so that the beginning fits in the container and the missing text is indicated by an ellipsis glyph. */
    IGBreakByTruncatingTail,
    /** Each line is displayed so that the beginning and end fit in the container and the missing text is indicated by an ellipsis glyph in the middle. */
    IGBreakByTruncatingMiddle
} ;

/*!
 These specify how to align the displayed text.
*/
typedef NS_ENUM(NSInteger, IGTextAlignment)
{
    /** Text is visually left aligned. */
    IGTextAlignmentLeft = 0,
    /** Text is visually right aligned. */
    IGTextAlignmentRight,
    /** Text is visually center aligned. */
    IGTextAlignmentCenter,
    /** Text is justified. */
    IGTextAlignmentJustified
} ;

/*!
 These specify where the overflow view will be positioned.
*/
typedef NS_ENUM(NSInteger, IGTextOverflowAlignment)
{
    /** The set overflow view will be visible at the bottom center of the view. */
    IGTextOverflowAlignmentBottomCenter = 0,
    /** The set overflow view will be visible at the bottom left of the view. */
    IGTextOverflowAlignmentBottomLeft,
    /** The set overflow view will be visible at the bottom right of the view. */
    IGTextOverflowAlignmentBottomRight,
    /** The set overflow view will be visible at the left center of the view. */
    IGTextOverflowAlignmentLeftCenter,
    /** The set overflow view will be visible at the right center of the view. */
    IGTextOverflowAlignmentRightCenter,
    /** The set overflow view will be visible at the top center of the view. */
    IGTextOverflowAlignmentTopCenter,
    /** The set overflow view will be visible at the top left of the view. */
    IGTextOverflowAlignmentTopLeft,
    /** The set overflow view will be visible at the top right of the view. */
    IGTextOverflowAlignmentTopRight
} ;

extern const NSString *IGTextStyleBackgroundColorAttributeName;
extern const NSString *IGTextStyleBoldAttributeName;
extern const NSString *IGTextStyleFontAttributeName;
extern const NSString *IGTextStyleForegroundColorAttributeName;
extern const NSString *IGTextStyleItalicAttributeName;
extern const NSString *IGTextStyleKernAttributeName;
extern const NSString *IGTextStyleStrokeColorAttributeName;
extern const NSString *IGTextStyleStrokeWidthAttributeName;
extern const NSString *IGTextStyleTapAttributeName;
extern const NSString *IGTextStyleUnderlineAttributeName;
extern const NSString *IGTextStyleUnderlineColorAttributeName;

/*! The delegate of a IGLabel object must adopt the _IGLabelDelegate_ protocol. The optional method of the protocol allows the delegate to manage the tap gesture that occurs when the _IGTextStyleTapAttributeName_ style and value have been applied to a portion of the label text.
 */
@protocol IGLabelDelegate <NSObject>

@optional
/** Tells the delegate the label tapped and provides the object value that was set with the style attribute.

@param label The label that received the tap.
@param text The text that received the tap.
@param value The object value that was set with the style attribute applied to the text.

*/
-(void)labelTap:(IGLabel *)label tapText:(NSString *)text tapValue:(id)value;

@end

/*!
The IGLabel is a rich text label that works similarly to the generic _UILabel_ and applies styles to text in a similar fashion that is done when using attributed strings. It is based on Core Text to boost performance and functionality over the generic _UILabel_.

Attributes are used to decorate the displayed text using an _NSRange_ or a regular expression search string through these two methods; addAttributes:range:, and addAttributes:forRegEx:error:. Attributes allow you to adjust these text characteristics; bold appearance, font used, text foreground color, italic appearance, kern spacing, text stroke color and width, interaction of text through tap, and underline appearance and color.

Text variables are added by using the addTextVariable:value: method and are used to allow for the usage of dynamic text values. When the text property changes and text variables were defined, they are automatically updated with the configured value.

 */
@interface IGLabel : UIView

///---------------------------------------------------------------------------------------
/// @name Initialization and Configuration
///---------------------------------------------------------------------------------------

/** The object that acts as the delegate of the label.

The class must adopt the IGLabelDelegate protocol.

*/
@property (nonatomic, assign, nullable) id<IGLabelDelegate> delegate;

/** The font of the text.

The default value for this property is the _Helvetica_ font at a size of 12 points. The value for the property can only be set to a non-nil value; setting this property to nil raises an exception.

*/
@property (nonatomic, retain) UIFont *font;

/** Sets the text displayed in the label.

**Important:** Setting this property will reset any previously applied attributes.

 */
@property (nonatomic, retain, nullable) NSString *text;

///---------------------------------------------------------------------------------------
/// @name Overflow Indicator
///---------------------------------------------------------------------------------------

/** The edge alignment at which to display the overflow indicator. Type: _IGTextOverflowAlignment_. Default: _IGTextOverflowAlignmentRightCenter_.

Supported enumeration values:

- **IGTextOverflowAlignmentBottomCenter** - Aligns the overflow indicator to the bottom center of the label.
- **IGTextOverflowAlignmentBottomLeft** - Aligns the overflow indicator to the bottom left of the label.
- **IGTextOverflowAlignmentBottomRight** - Aligns the overflow indicator to the bottom right of the label.
- **IGTextOverflowAlignmentLeftCenter** - Aligns the overflow indicator to the left center of the label.
- **IGTextOverflowAlignmentRightCenter** - Aligns the overflow indicator to the right center of the label.
- **IGTextOverflowAlignmentTopCenter** - Aligns the overflow indicator to the top center of the label.
- **IGTextOverflowAlignmentTopLeft** - Aligns the overflow indicator to the top left of the label.
- **IGTextOverflowAlignmentTopRight** - Aligns the overflow indicator to the top right of the label.

*/
@property (nonatomic, assign) IGTextOverflowAlignment overflowIndicatorAlignment;

/** A view to display as the overflow indicator. Type: _UIView_. Default: _nil_.
*/
@property (nonatomic, retain, nullable) UIView *overflowIndicatorView;

/** Sets whether or not to display an indicator when the text has exceeded the available space. Type: _BOOL_. Default: _NO_.
*/
@property (nonatomic, assign) BOOL overflowIndicatorVisible;

///---------------------------------------------------------------------------------------
/// @name Paragraph and Text Styling
///---------------------------------------------------------------------------------------

/** Styled text that will be displayed. Type: _NSAttributedString_. Default: _nil_.
* This property is _nil_ by default. Setting this property will clear all previously set attributes and use the attributedText as the text to display instead of the text property.
* Replacing text variables is not supported when using this property to displayed styled text.
*/
@property (nonatomic, retain, nullable) NSAttributedString *attributedText;

/** The distance, in points, from the leading marginAll of a label to the beginning of the paragraph's first line. This value is always non-negative. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat firstLineHeadIndent;

/** The distance, in points, from the leading marginAll of the label to the beginning of lines other than the first. This value is always non-negative. Type: _CGFloat_ Default: 0.0.
*/
@property (nonatomic, assign) CGFloat headIndent;

/** The text alignment. Type: _IGTextAlignment_. Default: _IGTextAlignmentLeft_.

Supported enumerated values:

- **IGTextAlignmentLeft** - Text is visually left aligned.
- **IGTextAlignmentRight** - Text is visually right aligned.
- **IGTextAlignmentCenter** - Text is visually center aligned.
- **IGTextAlignmentJustified** - Text is fully justified. The last line in a paragraph is naturally aligned.

*/
@property (nonatomic, assign) IGTextAlignment horizontalTextAlignment;

/** Specifies what happens when a line of text is too long for the width of the label. Type: _IGLineBreakMode_. Default: _IGBreakByWordWrapping_.

Supported enumerated values:

- **IGBreakByWordWrapping** - Wrapping occurs at word boundaries unless the word itself doesn't fit on a single line.
- **IGBreakByCharWrapping** - Wrapping occurs before the first character that doesn't fit.
- **IGBreakByClipping** - Lines are simply not drawn past the edge of the label.
- **IGBreakByTruncatingHead** - Each line is displayed so that the end fits in the label and the missing text is indicated by an ellipsis glyph.
- **IGBreakByTruncatingTail** - Each line is displayed so that the beginning fits in the label and the missing text is indicated by an ellipsis glyph.
- **IGBreakByTruncatingMiddle** - Each line is displayed so that the beginning and end fit in the label and the missing text is indicated by an ellipsis glyph in the middle.

*/
@property (nonatomic, assign) IGLineBreakMode lineBreakMode;

/** The space in points added between lines within the paragraph (commonly known as leading). This value is always non-negative. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat lineSpacing;

/** The space separating the edge of the label from the text. This value is always non-negative. When this property is set, the marginBottom, marginLeft, marginRight, and marginTop properties are invalidated and set to 0.0. Type: _CGFloat_. Default: 8.0.
*/
@property (nonatomic, assign) CGFloat marginAll;

/** The space separating the bottom edge of the label from the text. This value is always non-negative. When this property is set, the marginAll property is invalidated and set to -1.0. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat marginBottom;

/** The space separating the left edge of the label from the text. This value is always non-negative. When this property is set, the marginAll property is invalidated and set to -1.0. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat marginLeft;

/** The space separating the right edge of the label from the text. This value is always non-negative. When this property is set, the marginAll property is invalidated and set to -1.0. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat marginRight;

/** The space separating the top edge of the label from the text. This value is always non-negative. When this property is set, the marginAll property is invalidated and set to -1.0. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat marginTop;

/** The distance between the paragraph's top and the beginning of its text content. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat paragraphSpacingBefore;

/** The space added at the end of the paragraph to separate it from the following paragraph. This value is always non-negative. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat paragraphSpacingAfter;

/** The distance, in points, from the marginAll of a label to the end of lines. If positive, this value is the distance from the leading marginAll. If 0 or negative, it's the distance from the trailing marginAll. Type: _CGFloat_. Default: 0.0.
*/
@property (nonatomic, assign) CGFloat tailIndent;

/** The color of the text.

The default value for this property is a black color (set through the _blackColor_ class method of _UIColor_). The value for the property can only be set to a non-nil value; setting this property to nil raises an exception.

*/
@property (nonatomic, retain) UIColor *textColor;

///---------------------------------------------------------------------------------------
/// @name Text Styling Attributes
///---------------------------------------------------------------------------------------

/** Adds styling attributes to a specific range of text.

Supported key enumeration values:

- **IGTextStyleBackgroundColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleBoldAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleFontAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleForegroundColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleItalicAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleKernAttributeName** - the value used with this key is a _NSNumber_ with float.
- **IGTextStyleStrokeColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleStrokeWidthAttributeName** - the value used with this key is a _NSNumber_ with float.
- **IGTextStyleTapAttributeName** - the value used with this key is a _NSObject_.
- **IGTextStyleUnderlineAttributeName** - the value used with this key is a _NSNumber_ with int. An int value of 1 means on, 0 means off.
- **IGTextStyleUnderlineColorAttributeName** - the value used with this key is a _UIColor_.

The following code is an example of adding attributes to an instanced label.

    label.text = @"The quick brown fox jumped over the lazy dogs.";
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
            [NSNumber numberWithInt:1], IGTextStyleUnderlineAttributeName,
            [UIColor greenColor], IGTextStyleUnderlineColorAttributeName, nil];
    [label addAttributes:attributes range:NSMakeRange(16, 3)];

@param attributes The dictionary of styling key/value attributes.
@param styleRange The range of text where the styling attributes are to be applied.
*/
-(void)addAttributes:(NSDictionary *)attributes range:(NSRange)styleRange;

/** Adds styling attributes to the matched results of the supplied regular expression.

Supported key enumeration values:

- **IGTextStyleBackgroundColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleBoldAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleFontAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleForegroundColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleItalicAttributeName** - the value used with this key is a _UIFont_.
- **IGTextStyleKernAttributeName** - the value used with this key is a _NSNumber_ with float.
- **IGTextStyleStrokeColorAttributeName** - the value used with this key is a _UIColor_.
- **IGTextStyleStrokeWidthAttributeName** - the value used with this key is a _NSNumber_ with float.
- **IGTextStyleTapAttributeName** - the value used with this key is a _NSObject_.
- **IGTextStyleUnderlineAttributeName** - the value used with this key is a _NSNumber_ with int. An int value of 1 means on, 0 means off.
- **IGTextStyleUnderlineColorAttributeName** - the value used with this key is a _UIColor_.

The following code is an example of adding attributes to an instanced label.

    label.text = @"The quick brown fox jumped over the lazy dogs.";
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
                    [UIFont systemFontOfSize:24], IGTextStyleBoldAttributeName,
                    [UIColor darkTextColor], IGTextStyleForegroundColorAttributeName,
                    @"The word 'fox' was tapped.", IGTextStyleTapAttributeName, nil];
    NSError *error;
    [label addAttributes:attributes forRegEx:@"fox" error:&error];

@param attributes The dictionary of styling key/value attributes.
@param expression The regular expression that will apply the styling attributes to expression matches.
@param error The error output reference, should the regular expression contain any errors.
*/
-(void)addAttributes:(NSDictionary *)attributes forRegEx:(NSString *)expression error:(NSError **)error;

/** Removes a styling attribute from the matched results of the supplied regular expression.

Supported key enumeration values:

- **IGTextStyleBackgroundColorAttributeName**
- **IGTextStyleBoldAttributeName**
- **IGTextStyleFontAttributeName**
- **IGTextStyleForegroundColorAttributeName**
- **IGTextStyleItalicAttributeName**
- **IGTextStyleKernAttributeName**
- **IGTextStyleStrokeColorAttributeName**
- **IGTextStyleStrokeWidthAttributeName**
- **IGTextStyleTapAttributeName**
- **IGTextStyleUnderlineAttributeName**
- **IGTextStyleUnderlineColorAttributeName**

The following code is an example of removing an attribute from an instanced label.

    label.text = @"The quick brown fox jumped over the lazy dogs.";
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
                    [UIFont systemFontOfSize:24], IGTextStyleBoldAttributeName,
                    [UIColor darkTextColor], IGTextStyleForegroundColorAttributeName,
                    @"The word 'fox' was tapped.", IGTextStyleTapAttributeName, nil];
    [label addAttributes:attributes range:NSMakeRange(16, 3)];

    //Removing an applied style attribute
    [label removeAttribute:IGTextBoldAttributeName forRegEx:@"fox" error:nil];

@param name A supported styling key enumeration value.
@param expression The regular expression that will apply the styling attributes to expression matches.
@param error The error output reference, should the regular expression contain any errors.
*/
-(void)removeAttribute:(NSString *)name forRegEx:(NSString *)expression error:(NSError **)error;

/** Removes a styling attribute from a specific range of text.

Supported key enumeration values:

- **IGTextStyleBackgroundColorAttributeName**
- **IGTextStyleBoldAttributeName**
- **IGTextStyleFontAttributeName**
- **IGTextStyleForegroundColorAttributeName**
- **IGTextStyleItalicAttributeName**
- **IGTextStyleKernAttributeName**
- **IGTextStyleStrokeColorAttributeName**
- **IGTextStyleStrokeWidthAttributeName**
- **IGTextStyleTapAttributeName**
- **IGTextStyleUnderlineAttributeName**
- **IGTextStyleUnderlineColorAttributeName**

The following code is an example of removing style attributes from an instanced label.
    label.text = @"The quick brown fox jumped over the lazy dogs.";
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
                    [UIFont systemFontOfSize:12], IGTextStyleFontAttributeName,
                    [UIFont systemFontOfSize:28], IGTextStyleBoldAttributeName,
                    [UIColor redColor], IGTextStyleForegroundColorAttributeName, nil];
    [label addAttributes:attributes range:NSMakeRange(0, 3)];

    //Removing an applied style attribute
    [label removeAttribute:IGTextStyleForegroundColorAttributeName range:NSMakeRange(0, 3)];

@param name A supported styling key enumeration value.
@param styleRange The range of text where the styling attributes are to be removed.
*/
-(void)removeAttribute:(NSString *)name range:(NSRange)styleRange;

/** Removes all attributes that have been added to the label.
*/
-(void)resetAttributes;

///---------------------------------------------------------------------------------------
/// @name Text Variables
///---------------------------------------------------------------------------------------

/** Adds a text variable to the label that replaces occurrences of the variable with a string value.

Changing the text property will automatically reapply the variables.

The following code is an example of adding text variables to an instanced label.
    label.text = @"Hello Mr. {LastName}, welcome back to the application.";
    [label addTextVariable:@"{LastName}" value:@"Betts"];

@param variable The text variable to search and replace.
@param value The string value to replace occurrences of the variable with.
*/
-(void)addTextVariable:(NSString *)variable value:(NSString *)value;

/** Removes a text variable entry

This removes a text variable entry from the label, so that is no longer auto replaced should the text property be set again.

@param variable The text variable to remove from auto replacement.
*/
-(void)removeTextVariable:(NSString *)variable;

/** Removes all text variables that have been added to the label.
*/
-(void)resetTextVariables;

/** Resizes the IGLabel height to fit the text.

Use this method when you need to resize the IGLabel to fit its text and respect the width bounds. This method requires the IGLabel to have drawn to the screen beforehand.

*/
-(void)sizeToFitWidth;

/** Updates a text variable value

@param variable The text variable to update its value.
@param value The updated string value to replace occurrences of the variable with.
*/
-(void)updateTextVariableValue:(NSString *)variable value:(NSString *)value;

@end

NS_ASSUME_NONNULL_END
