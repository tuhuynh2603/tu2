///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 13.0.2.2
///////////////////////////////////////////////////////////////////////////////




#ifndef __APPLE__
#  include "HalconCpp.h"
#  include "HDevThread.h"
#else
#  ifndef HC_LARGE_IMAGES
#    include <HALCONCpp/HalconCpp.h>
#    include <HALCONCpp/HDevThread.h>
#  else
#    include <HALCONCppxl/HalconCpp.h>
#    include <HALCONCppxl/HDevThread.h>
#  endif
#endif



using namespace HalconCpp;


// Chapter: Identification / Bar Code
// Short Description: Convert a decoded string of a bar code of type 'Code 39' to the type 'Code 32'. 
void convert_decoded_string_code39_to_code32 (HTuple hv_DecodedDataStringCode39, 
    HTuple *hv_ConvertedDataStringCode32)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_Symbols, hv_Digit, hv_CheckDigit, hv_CheckSum;
  HTuple  hv_Value;

  //This procedure converts a decoded string of a 'Code 32'
  //barcode that was read with the bar code reader for 'Code 39'
  //to the 'Code 32' decoding.
  //
  //Basically a 'Code 32' bar code corresponds to a 'Code 39' with
  //8 digits and a checksum digit % 10 whereas even positions are
  //weighted twice.
  //The 9-digit number is represented to the base 32 and written
  //with chars (via the symbol table) analogous to a hexadecimal number.
  //
  //Initialize symbol table
  hv_Symbols.Clear();
  hv_Symbols[0] = "0";
  hv_Symbols[1] = "1";
  hv_Symbols[2] = "2";
  hv_Symbols[3] = "3";
  hv_Symbols[4] = "4";
  hv_Symbols[5] = "5";
  hv_Symbols[6] = "6";
  hv_Symbols[7] = "7";
  hv_Symbols[8] = "8";
  hv_Symbols[9] = "9";
  hv_Symbols[10] = "B";
  hv_Symbols[11] = "C";
  hv_Symbols[12] = "D";
  hv_Symbols[13] = "F";
  hv_Symbols[14] = "G";
  hv_Symbols[15] = "H";
  hv_Symbols[16] = "J";
  hv_Symbols[17] = "K";
  hv_Symbols[18] = "L";
  hv_Symbols[19] = "M";
  hv_Symbols[20] = "N";
  hv_Symbols[21] = "P";
  hv_Symbols[22] = "Q";
  hv_Symbols[23] = "R";
  hv_Symbols[24] = "S";
  hv_Symbols[25] = "T";
  hv_Symbols[26] = "U";
  hv_Symbols[27] = "V";
  hv_Symbols[28] = "W";
  hv_Symbols[29] = "X";
  hv_Symbols[30] = "Y";
  hv_Symbols[31] = "Z";
  //Check the chars in the decoded 'Code 39' string.
  //It must consist of exactly 6 chars and must not
  //contain any invalid chars. If these conditions are
  //fulfilled, convert the string to 'Code 32', else
  //return an empty string.
  if (0 != (hv_DecodedDataStringCode39.TupleRegexpTest(("^["+(hv_Symbols.TupleSum()))+"]{6}$")))
  {
    //
    //Convert the value of each digit in the decoded 'Code 39' string
    (*hv_ConvertedDataStringCode32) = 0;
    for (hv_Digit=0; hv_Digit<=5; hv_Digit+=1)
    {
      (*hv_ConvertedDataStringCode32) += hv_Symbols.TupleFind(hv_DecodedDataStringCode39.TupleStrBitSelect(hv_Digit));
      if (0 != (hv_Digit<5))
      {
        (*hv_ConvertedDataStringCode32) = (*hv_ConvertedDataStringCode32)*32;
      }
    }
    //Write the converted string as 9 digit string with leading zeros
    (*hv_ConvertedDataStringCode32) = (*hv_ConvertedDataStringCode32).TupleString("9.9d");
    //
    //Verify the checksum (last digit)
    hv_CheckDigit = ((*hv_ConvertedDataStringCode32).TupleStrBitSelect(8)).TupleNumber();
    hv_CheckSum = 0;
    for (hv_Digit=0; hv_Digit<=7; hv_Digit+=1)
    {
      //Sum first 8 digits, but even digits have weight 2
      hv_Value = (1+(hv_Digit%2))*(((*hv_ConvertedDataStringCode32).TupleStrBitSelect(hv_Digit)).TupleNumber());
      //But actually we only want the cross digit sum,
      //This 'formula' works for 0-19
      if (0 != (hv_Value>=10))
      {
        hv_Value = hv_Value-9;
      }
      hv_CheckSum += hv_Value;
    }
    hv_CheckSum = hv_CheckSum%10;
    //
    //If the checksum fits, return the converted 'Code 32' string,
    //else return an empty string
    if (0 != (hv_CheckDigit!=hv_CheckSum))
    {
      //Bad checksum
      (*hv_ConvertedDataStringCode32) = "";
    }
    else
    {
      //Always printed with leading A
      (*hv_ConvertedDataStringCode32) = "A"+(*hv_ConvertedDataStringCode32);
    }
  }
  else
  {
    //Wrong number of chars or invalid chars
    (*hv_ConvertedDataStringCode32) = "";
  }
  return;
  //
}
