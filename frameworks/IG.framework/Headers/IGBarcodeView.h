#import <UIKit/UIKit.h>

/*! 
 These specify the return result when setting a barcode value.
*/
typedef NS_ENUM(NSInteger, IGBarcodeError)
{
    /** No error was encountered when setting the barcode value. */
    IGBarcodeErrorNone = 0,
    /** The barcode value was not valid for the barcode type. */
    IGBarcodeErrorInvalidValue,
    /** The value length does not match what is expected for the barcode type. */
    IGBarcodeErrorLength
} ;

/*!
 These specify the barcode type.
 */
typedef NS_ENUM(NSInteger, IGBarcodeType)
{
    /** Codabar barcode encoding. */
    IGBarcodeTypeCodabar = 0,
    /** Code-39 barcode encoding. */
    IGBarcodeTypeCode39,
    /** Code-39 extended barcode encoding. */
    IGBarcodeTypeCode39Ext,
    /** Code-128 barcode encoding. */
    IGBarcodeTypeCode128,
    /** EAN-8 barcode encoding. */
    IGBarcodeTypeEAN8,
    /** EAN-13 barcode encoding. */
    IGBarcodeTypeEAN13,
    /** Interleaved 2 of 5 barcode encoding. */
    IGBarcodeTypeInterleaved2Of5,
    /** Planet barcode encoding. */
    IGBarcodeTypePlanet,
    /** PostNet barcode encoding. */
    IGBarcodeTypePostNet,
    /** Standard 2 of 5 barcode encoding. */
    IGBarcodeTypeStandard2Of5,
    /** UPC-A barcode encoding. */
    IGBarcodeTypeUPCA,
    /** UPC-E barcode encoding. */
    IGBarcodeTypeUPCE
} ;

/*!
 
 The IGBarcodeView is a flexible control capable of displaying one of the 12 supported barcode types.
 
 - Codabar
 - Code 39
 - Code 39 Extended
 - Code 128
 - EAN-8
 - EAN-13
 - Interleaved 2 Of 5
 - Planet
 - PostNet
 - Standard 2 Of 5
 - UPC-A
 - UPC-E
 
 Barcodes with the exception of Planet and PostNet can display their set value under the barcode using any font set through the fontName property. The barcode bar color and text color are controllable through the barcodeColor and textColor properties.
 
 */
@interface IGBarcodeView : UIView

/** The bar color of the barcode.

The default color is black.

*/
@property (nonatomic, retain) UIColor *barcodeColor;

/** Returns the type of barcode the _IGBarcodeView_ has been initialized with. (Read-Only)

Support barcode enumerations:

- IGBarcodeTypeCodabar
- IGBarcodeTypeCode39
- IGBarcodeTypeCode39Ext
- IGBarcodeTypeCode128
- IGBarcodeTypeEAN8
- IGBarcodeTypeEAN13
- IGBarcodeTypeInterleaved2Of5
- IGBarcodeTypePlanet
- IGBarcodeTypePostNet
- IGBarcodeTypeStandard2Of5
- IGBarcodeTypeUPCA
- IGBarcodeTypeUPCE

*/
@property (nonatomic, readonly) IGBarcodeType barcodeType;

/** The font name that will be used when the _IGBarcodeView_ is showing text.

The default font used is, __HelveticaNeue-Bold__.

*/
@property (nonatomic, retain) NSString *fontName;

/** Displays the _IGBarcodeView_ value under the barcode.

The showText property is set to YES by default. No text value is displayed for __IGBarcodeTypePlanet__ and __IGBarcodeTypePostNet__ barcode types.

*/
@property (nonatomic, assign) BOOL showText;

/** The text color of the _IGBarcodeView_ when __showText__ has been set to __YES__.

The default color is black.

*/
@property (nonatomic, retain) UIColor *textColor;

/** The value displayed on the _IGBarcodeView_.
*/
@property (nonatomic, readonly) NSString *value;

/** Initializes the _IGBarcodeView_ with the specified barcode type.

Support barcode enumerations:

- IGBarcodeTypeCodabar
- IGBarcodeTypeCode39
- IGBarcodeTypeCode39Ext
- IGBarcodeTypeCode128
- IGBarcodeTypeEAN8
- IGBarcodeTypeEAN13
- IGBarcodeTypeInterleaved2Of5
- IGBarcodeTypePlanet
- IGBarcodeTypePostNet
- IGBarcodeTypeStandard2Of5
- IGBarcodeTypeUPCA
- IGBarcodeTypeUPCE

@param barcodeType The _IGBarcodeType_ to initialize with.
@return The _IGBarcodeView_ instance.
*/
- (instancetype)initWithBarcode:(IGBarcodeType)barcodeType NS_DESIGNATED_INITIALIZER;

/** Static method that initializes the _IGBarcodeView_ with the specified barcode type.

Support barcode enumerations:

- IGBarcodeTypeCodabar
- IGBarcodeTypeCode39
- IGBarcodeTypeCode39Ext
- IGBarcodeTypeCode128
- IGBarcodeTypeEAN8
- IGBarcodeTypeEAN13
- IGBarcodeTypeInterleaved2Of5
- IGBarcodeTypePlanet
- IGBarcodeTypePostNet
- IGBarcodeTypeStandard2Of5
- IGBarcodeTypeUPCA
- IGBarcodeTypeUPCE

@param barcodeType The _IGBarcodeType_ to initialize with.
@return The _IGBarcodeView_ instance.
*/
+ (IGBarcodeView *)createBarcode:(IGBarcodeType)barcodeType;

/** Initializes the _IGBarcodeView_ with the specified barcode type and frame.

Support barcode enumerations:

- IGBarcodeTypeCodabar
- IGBarcodeTypeCode39
- IGBarcodeTypeCode39Ext
- IGBarcodeTypeCode128
- IGBarcodeTypeEAN8
- IGBarcodeTypeEAN13
- IGBarcodeTypeInterleaved2Of5
- IGBarcodeTypePlanet
- IGBarcodeTypePostNet
- IGBarcodeTypeStandard2Of5
- IGBarcodeTypeUPCA
- IGBarcodeTypeUPCE

@param frame The frame rectangle, which describes the _IGBarcodeView_ location and size in its superview’s coordinate system.
@param barcodeType The _IGBarcodeType_ to initialize with.
@return The _IGBarcodeView_ instance.
*/
- (instancetype)initWithFrame:(CGRect)frame barcodeType:(IGBarcodeType)barcodeType NS_DESIGNATED_INITIALIZER;

/** Static method that initializes the _IGBarcodeView_ with the specified barcode type and frame.

Support barcode enumerations:

- IGBarcodeTypeCodabar
- IGBarcodeTypeCode39
- IGBarcodeTypeCode39Ext
- IGBarcodeTypeCode128
- IGBarcodeTypeEAN8
- IGBarcodeTypeEAN13
- IGBarcodeTypeInterleaved2Of5
- IGBarcodeTypePlanet
- IGBarcodeTypePostNet
- IGBarcodeTypeStandard2Of5
- IGBarcodeTypeUPCA
- IGBarcodeTypeUPCE

@param frame The frame rectangle, which describes the _IGBarcodeView_ location and size in its superview’s coordinate system.
@param barcodeType The _IGBarcodeType_ to initialize with.
@return The _IGBarcodeView_ instance.
*/
+ (IGBarcodeView *)createBarcode:(IGBarcodeType)barcodeType frame:(CGRect)frame;

/** Set the value to display on the _IGBarcodeView_.

The return value enumerations:

- __IGBarcodeErrorNone__ - The set value was validated and successfully set.
- __IGBarcodeErrorInvalidValue__ - The value was invalid and not set.
- __IGBarcodeErrorLength__ - The value length was incorrect and not set.

@param value The value to display on the _IGBarcodeView_.
@return A return _IGBarcodeError_ enumeration value to indicate success or error.
*/
- (IGBarcodeError)setValue:(NSString *)value;

@end
