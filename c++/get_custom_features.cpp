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

extern void append_length_or_values (HTuple hv_Mode, HTuple hv_Feature, HTuple hv_AccumulatedResults, 
    HTuple *hv_ExtendedResults);

extern void append_names_or_groups (HTuple hv_Mode, HTuple hv_Name, HTuple hv_Groups, 
    HTuple hv_CurrentName, HTuple hv_AccumulatedResults, HTuple *hv_ExtendedResults);


// Chapter: Classification / Misc
// Short Description: Describe and calculate user-defined features to be used in conjunction with the calculate_feature_set procedure library. 
void get_custom_features (HObject ho_Region, HObject ho_Image, HTuple hv_CurrentName, 
    HTuple hv_Mode, HTuple *hv_Output)
{

  // Local iconic variables
  HObject  ho_RegionSelected, ho_Contours, ho_ContoursSelected;
  HObject  ho_ContoursSplit;

  // Local control variables
  HTuple  hv_TmpResults, hv_Name, hv_Groups, hv_Feature;
  HTuple  hv_NumRegions, hv_I, hv_NumContours, hv_NumLines;
  HTuple  hv_J, hv_NumSplit;

  //
  //This procedure can be used to extend the functionality
  //of the calculate_feature_set procedure library by
  //user-defined features.
  //
  //Instructions:
  //
  //1. Find the template block at the beginning the procedure
  //(marked by comments) and duplicate it.
  //
  //2. In the copy edit the two marked areas as follows:
  //
  //2.1. Feature name and groups:
  //Assign a unique identifier for your feature to the variable "Name".
  //Then, assign the groups that you want your feature to belong to
  //to the variable "Groups".
  //
  //2.2. Feature calculation:
  //Enter the code that calculates your feature and
  //assign the result to the variable "Feature".
  //
  //3. Test
  //Use the "test_feature" procedure to check,
  //if the feature is calculated correctly.
  //If the procedure throws an exception,
  //maybe the order of the feature vector is wrong
  //(See note below).
  //
  //4. Integration
  //- Save your modified procedure get_custom_features.hdvp
  //  to a location of your choice.
  //  (We recommend not to overwrite the template.)
  //- Make sure, that your version of get_custom_procedures
  //  is included in the procedure directories of HDevelop.
  //  (Choose Procedures -> Manage Procedures -> Directories -> Add from the HDevelop menu bar.)
  //
  //Note:
  //The current implementation supports region arrays as input.
  //In that case, multi-dimensional feature vectors are simply concatenated.
  //Example: The feature 'center' has two dimensions [Row,Column].
  //If an array of three regions is passed, the correct order of the "Feature" variable is
  //[Row1, Column1, Row2, Column2, Row3, Column3].
  //
  hv_TmpResults = HTuple();
  //************************************************
  //************************************************
  //**** Copy the following template block     *****
  //**** and edit the two marked code sections *****
  //**** to add user-defined features          *****
  //************************************************
  //************************************************
  //
  //***************************************
  //*********** TEMPLATE BLOCK ************
  //***************************************
  //
  //********************************************************************
  //** Section 1:
  //** Enter unique feature name and groups to which it belongs here ***
  hv_Name = "custom_feature_numlines";
  hv_Groups = "custom";
  //** Enter unique feature name and groups above this line ************
  //********************************************************************
  if (0 != (hv_Name==hv_CurrentName))
  {
    //******************************************************
    //** Section 2:
    //** Enter code to calculate feature here **************
    hv_Feature = HTuple();
    CountObj(ho_Region, &hv_NumRegions);
    {
    HTuple end_val69 = hv_NumRegions;
    HTuple step_val69 = 1;
    for (hv_I=1; hv_I.Continue(end_val69, step_val69); hv_I += step_val69)
    {
      SelectObj(ho_Region, &ho_RegionSelected, hv_I);
      GenContourRegionXld(ho_RegionSelected, &ho_Contours, "border");
      CountObj(ho_Contours, &hv_NumContours);
      hv_NumLines = 0;
      {
      HTuple end_val74 = hv_NumContours;
      HTuple step_val74 = 1;
      for (hv_J=1; hv_J.Continue(end_val74, step_val74); hv_J += step_val74)
      {
        SelectObj(ho_Contours, &ho_ContoursSelected, hv_J);
        SegmentContoursXld(ho_ContoursSelected, &ho_ContoursSplit, "lines", 5, 2, 
            1);
        CountObj(ho_ContoursSplit, &hv_NumSplit);
        hv_NumLines += hv_NumSplit;
      }
      }
      hv_Feature = hv_Feature.TupleConcat(hv_NumLines);
    }
    }
    //** Enter code to calculate feature above this line ***
    //******************************************************
    append_length_or_values(hv_Mode, hv_Feature, hv_TmpResults, &hv_TmpResults);
  }
  append_names_or_groups(hv_Mode, hv_Name, hv_Groups, hv_CurrentName, hv_TmpResults, 
      &hv_TmpResults);
  //
  //************************************
  //****** END OF TEMPLATE BLOCK *******
  //************************************
  //
  (*hv_Output) = hv_TmpResults;
  return;
}