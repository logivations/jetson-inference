#ifndef L_Types_H_Include
#define L_Types_H_Include

/*!Linear Decoder constants
*/
extern "C"
{
enum TYPE_CODE{
    TC_ANY               = -1,
    TC_TCODE128          = 1,
    TC_TCODE39           = 2,
    TC_TCODABAR          = 3,
    TC_TINTERLEAVED      = 4,
    TC_TEAN13            = 5,
    TC_TEAN8             = 6,
    TC_TUPCE             = 7,
    TC_TPOSTNET          = 8,
    TC_TIMB              = 9,
    TC_TPHARMACODE       = 10,

    TC_TRSS              = 11,
    TC_TRSS_L            = 12,
    TC_TRSS_E            = 13,

    TC_TEAN13EX          = 14,
    TC_TUPCEEX           = 15,

    TC_TADF              = 17,
    TC_TNZP              = 18,
    TC_TSP               = 19, // SuissPost

    TCM_TCODE128         = 0x00200,
    TCM_TCODE39          = 0x00400,
    TCM_TCODABAR         = 0x00800,
    TCM_TINTERLEAVED     = 0x01000,
    TCM_TEAN13           = 0x02000,
    TCM_TEAN8            = 0x04000,
    TCM_TUPCE            = 0x08000,
    TCM_TEAN13EX         = 0x400000, // 0x100<<14
    TCM_TUPCEEX          = 0x800000,

    TCM_TRSS             = 0x80000,
    TCM_TRSS_L           = 0x100000,
    TCM_TRSS_E           = 0x200000,

    TCM_TPOSTNET         = 0x10000,
    TCM_TIMB             = 0x20000,
    TCM_TPHARMACODE      = 0x40000,

    TCM_TRSS_ALL         = 0x380000
};

enum L_REJECTION_REASON{
    L_SUCCESSFUL         = 0,
    L_NO_LINEAR_FOUND    = 1,
    L_POOR_IMAGE_QUALITY = 2,
    L_RR_UNKNOWN         = 3,
//    L_LICENSE_EXPIRED    = 4,
//
    L_RS_ERROR           = 5,
    L_CHECKSUM_FAILED    = 6,
    L_NOT_CONFIRMED      = 7,
    L_NOT_QUIET_ZONE     = 8
//UseRSS
    ,L_2D_FAILED         = 9 //!< obligatory 2D-symbol is not found
    ,L_NOT_SUPPORTED     = 10 // not supported code type

};

enum L_BREAK_REASON{
    L_ALL_INSPECTED      = 0, //!< Normal termination (whole image was inspected)
    L_TIMEOUT            = 1, //!< Termination by time-out
    L_TERMINATED         = 2  //!< Termination by user break (not implemented)
};

enum L_SCAN_DIR{
    L_SCAN_VERTICAL      = 0,
    L_SCAN_HORIZONTAL    = 1,
    L_SCAN_ALL           = 2
};

/*! Directions of Pharmacode*/
enum L_PHARMACODEDIR{
    L_LR   = 0, //!< Barcode goes approximately from image left to image right
    L_TB   = 1, //!< From image top to bottom
    L_RL   = 2, //!< From image right to left
    L_BT   = 3, //!< From image bottom to top
    L_LRL  = 4, //!< left -> right -> left (result as "XXXX YYYY")
    L_TBT  = 5  //!< top -> bottom -> top
};

enum L_Color{
	L_BLACK = 1,
	L_WHITE   = 2, //!< Is valide for NZP
	L_DEFAULT = 3  //!< Any, if type code = -1..7, Black for all other code types
};

//--------------------------------------------------------------------------
/// The structure accumulates decoder options.
struct TL_OptMode
{                        //=== PP4 ===
  union {int maxLcount;    int maxLCount;};
  //!<\brief From 1 to 100. Equals to 1 by Default.
  //!<
  //!< Maximum number of barcodes.
  //!< Should be equal to 1 if code type is PostNet or USPS IMB
  union {int typecode;int typeCode;};
  /*!<\brief Equals to -1 by Default.
   Value TC_ANY (=-1) means search within all linear barcode types
   except of Pharma, PostNet and USPS IMB
  */
  union {int timeout;      int timeOut;};
  //!< TimeOut in mls. Timeout = 0 - the infinite timeout.
  union {int paramq;       int paramQ;};       //!< 1 - on, 0 - off
  union {int checksum_I25; int checkSum_I25;}; //!< 1 - on, 0 - off
  union {int checksum_C39; int checkSum_C39;}; //!< 1 - on, 0 - off
  union {int quietzone;    int quietZone;};    //!< 1<=quietzone<=15
  int smartmode;    //!< \brief Not assigned  (=0) by Default
/*!<
 Is equal to number of couples bar+space at both sides of a barcode
 that we can treat as noise.
 Negative value means the unlimited quantity of "excessive" bars and spaces.
 Option is valid for all code types except Pharma, PostNet and USPS IMB
*/
  int EC_Factor;
  //!< [0..4] - Maximum errors to be corrected in USPS IMB (1..2 are preferable)
  int pharmacodedir;
  int scandir; //!< Option is valid for all code types except of PostNet and USPS IMB
  int scanstep; //!< \brief By Default is equal to 8
  //!<
  //!< The value should conform to 1<= scanstep<=20.
  //!< Option is valid for all code types except of PostNet and USPS IMB

  union {int checksum_CB; int checkSum_CB;};  //!< 1 - on, 0 - off
  int FullASCII_C39;

  int colbeg;  //!<Left column of ROI. -1 for leftmost
  int colend;  //!<Right column of ROI. -1 for rightmost
  int rowbeg;  //!< Top row of  ROI. -1 for upper row
  int rowend;  //!< Bottom row of ROI. -1 for lower row

  int TADF_num;
  int color;
};

const TL_OptMode DefaultOptMode =
{
   { 1} //!< maxLcount
  ,{-1} //!< typecode
  ,{ 0} //!< timeout
  ,{ 1} //!< paramq
  ,{ 0} //!< checksum_I25
  ,{ 0} //!< checksum_C39
  ,{-1} //!< quietzone
  , 0 //!< smartmode
  , 2 //!< EC_Factor
  , 0 //!< pharmacodedir
  , 2 //!< scandir
  , 8 //!< scanstep
  , 0 //!< checksum_CB
  , 0 //!< Full ASCII code39
  ,-1 //!< colbeg
  ,-1 //!< colend
  ,-1 //!< rowbeg
  ,-1 //!< rowend
  ,65
  ,3
};

//--------------------------------------------------------------------------
/// Linear Image properties.
struct  TL_ImageInfo
{
  int LCount;          //!< Number of well decoded Linear symbols within image
  int RejectionReason;	//!< not 0 if no one symbol was well decoded
  int BreakReason;	    //!< 0 - normal termination (whole image inspected),
                       //!< 1 - termination by time-out
};

//--------------------------------------------------------------------------
/// Linear codes ISO 15416 Standard Quality Parameters.
struct LINEAR_QUALITY
{
    float decode;
    float symbol_contrast;
    float min_reflectance;
    float max_reflectance;
    float global_threshold;
    float min_edge_contrast;
    float modulation;
    float defects;
    float decodability;
    float decode_grad;
    float symbol_contrast_grad;
    float min_reflectance_grad;
    float global_threshold_grad;
    float min_edge_contrast_grad;
    float modulation_grad;
    float defects_grad;
    float decodability_grad;
    float overall_grade_grad;

    float decode_grad_av;
    float symbol_contrast_grad_av;
    float min_reflectance_grad_av;
    float global_threshold_grad_av;
    float min_edge_contrast_grad_av;
    float modulation_grad_av;
    float defects_grad_av;
    float decodability_grad_av;
    float overall_grade_grad_av;

};

//--------------------------------------------------------------------------
/// scan line descriptor.
struct  LINEAR_SCAN_LINE
{
  int  	scan_line_start_x;  //!< column of scan line begin
  int  	scan_line_start_y;  //!< row of scan line begin
  int  	scan_line_end_x;    //!< column of scan line end
  int  	scan_line_end_y;    //!< row of scan line end
  int 	first;                    //!< flag of main scan line
  int 	quietzone;                //!< QZ OK
  int 	checksum;                 //!< checksum OK
  int length;           //!< number of decoded characters
  char*	dataRes;                  //!< result of decoding the scan line
 };

#define bar_limit     100  // for TADF

/// Additional symbol Quality Parameters for IMB codes
struct TIMB_L_QUALITY   //!< Total number of bars in symbol
{
 int   Size_index_T;    //!< Length of array TrackerHeight
 int   Size_index_A;    //!< Length of array AscenderHeight
 int   Size_index_D;    //!< Length of array DescenderHeight
 int   Size_index_F;    //!< Length of array  FullHeight

 float BarWidth               [bar_limit];
 float SpaceWidth             [bar_limit];
 float BarPitch               [bar_limit];
 float BarHeight              [bar_limit];

 float TrackerHeight          [bar_limit];  //!< not 0 if BarType[i] = 'T'
 float AscenderHeight         [bar_limit];  //!< not 0 if BarType[i] = 'A'
 float DescenderHeight        [bar_limit];  //!< not 0 if BarType[i] = 'D'
 float FullHeight             [bar_limit];  //!< not 0 if BarType[i] = 'F'
 float BarRotation            [bar_limit];

 int   BarType                [bar_limit];  //!< 'T' or 'A' or 'D' or 'F'
 int   BarCol                 [bar_limit];  //!< column where base line intersects bar
 int   BarRow                 [bar_limit];  //!< row where base line intersects bar

 float BarReflectance         [bar_limit];
 float SpaceReflectance       [bar_limit];
 float BackgroundReflectance  [bar_limit];
 float PrintReflectanceDifference [bar_limit];

 float BaselineShift          [bar_limit];
      //!< the bar shift in vertical direction from estimated base (middle) line
 int   BarInk                 [bar_limit];
      //!< the average over-ink size of the bars
 int   VoidGrade              [bar_limit];
      //!< the average void spacing (area without ink) of the bars
 int   OverinkGrade           [bar_limit];

 int   minClearZoneLeft;
 int   minClearZoneRight;
 int   minClearZoneTop;
 int   minClearZoneBottom;
 int   gradeClearZoneLeft;
 int   gradeClearZoneRight;
 int   gradeClearZoneTop;
 int   gradeClearZoneBottom;

 int   actTADFnum;

};

//--------------------------------------------------------------------------
/// Linear symbol properties (per each decoded symbol)
struct  TL_Info{
  int     RejectionReason;
  //!< \brief Rejection qualifier.
  //!<
  //!< Available Rejection Reasons.
  //!< 0 - Successful.
  //!< 6 - The Checksum failed.
  //!< 7 - Code not Confirmed on several scan lines.
  //!< 8 - No Quiet Zone to the left or to the right of the barcode.


  int     rowcols[8];    //!< Coordinates of barcode rectangle
  int     type;          //!< Actual type of a barcode
  int idx_scan_line;     //!< Index of "main" scan line (0<=idx_scan_line<10)
  int pchlen;            //!< Length of decoded byte array
  char*         pch;     //!<Pointer to that array
  LINEAR_SCAN_LINE  sl[10];   //!< Descriptors of 10 scan lines
  LINEAR_QUALITY lq;   //!< ISO 15416 Quality Parameters
  TIMB_L_QUALITY* add_lq; //!< In accordance with code type: PL_IMBQuality...
};

//--------------------------------------------------------------------------
/*
  The type Definitions:
*/
typedef unsigned char*  TRow;         //!< - pointer to image rows
typedef void*           PL_Decoder;   //!< - handle of L_Decoder
typedef void*           PL_Options;   //!< - handle of L_Decoder Options
typedef TL_ImageInfo*   PL_ImageInfo; //!< - descriptor of structure ImageInfo
typedef TL_Info*        PL_Info;      //!< - descriptor of structure Linear Symbol Info
typedef LINEAR_QUALITY* PL_Quality;   //!< - descriptor of Quality Parameter.
typedef TIMB_L_QUALITY* PL_IMBQuality;//!< - pointer to IMB Quality Parameters

};

#ifdef __cplusplus
  #define extern_c extern "C"
#else
  #define extern_c
#endif

//--------------------------------------------------------------------------
/// The procedure constructs Linear Decoder Class. Returns Decoder Handler.
extern_c PL_Decoder Connect_L_Decoder(int maxrowcount, int maxcolcount);
//--------------------------------------------------------------------------

///The procedure destructs a Linear Decoder.
extern_c void Disconnect_L_Decoder(PL_Decoder& pDecoder);
//--------------------------------------------------------------------------


///The procedure constructs pointer on Decoder Options. Returns Options Handler.
extern_c PL_Options Create_L_Options(PL_Decoder pDecoder, TL_OptMode optmode);
//--------------------------------------------------------------------------


///The procedure deletes Decoder Options.
extern_c void Delete_L_Options(PL_Options &pOptions);
//--------------------------------------------------------------------------


///The procedure decodes image with given Options.
extern_c int Decode_L_Bits(PL_Options pOptions, int rowcount, int colcount, TRow* ppbits);
//--------------------------------------------------------------------------


///The procedure returns pointer on structure ImageInfo.
extern_c PL_ImageInfo GetL_ImageInfo(PL_Options pOptions);
//--------------------------------------------------------------------------


///The procedure returns pointer on structure Linear Symbol Info.
extern_c PL_Info  GetL_Info (PL_Options pOptions, int LNum);
//--------------------------------------------------------------------------

#endif

