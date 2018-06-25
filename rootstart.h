#ifndef ROOTSTART_H
#define ROOTSTART_H

// C++ core headers
#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
//#include <numeric>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// ROOT headers
#include "TSystem.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TText.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TTree.h"
#include "TTreePlayer.h"
#include "TFile.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TLegend.h"
#include "TCutG.h"
#include "TLatex.h"
#include "TMath.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TList.h"
#include "TVirtualFitter.h"
#include "TMatrixD.h"
#include "TRandom3.h"
#include "TArrow.h"

// Style
#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"

using namespace std;

void SetMyStyle(){

    // Set a list of colors
    vector<int> dscolors;
    dscolors.push_back(kBlack);                      // 0: Black
    dscolors.push_back(TColor::GetColor("#0088EE")); // 1: Blue
    dscolors.push_back(TColor::GetColor("#66CC00")); // 2: Green
    dscolors.push_back(TColor::GetColor("#6600CC")); // 3: Purple
    dscolors.push_back(TColor::GetColor("#CC6600")); // 4: Orange
    dscolors.push_back(TColor::GetColor("#00CCCC")); // 5: Cyan
    dscolors.push_back(TColor::GetColor("#CC0000")); // 6: Red
    dscolors.push_back(TColor::GetColor("#CC00CC")); // 7: Violet
    dscolors.push_back(TColor::GetColor("#FFEE00")); // 8: Yellow
    dscolors.push_back(TColor::GetColor("#00CC00")); // 9: Darker green
    dscolors.push_back(TColor::GetColor("#0000CC")); //10: Darker blue
    dscolors.push_back(TColor::GetColor("#00CC66")); //11: Blueish green
    dscolors.push_back(TColor::GetColor("#CC0066")); //13: Violet
    dscolors.push_back(TColor::GetColor("#A3FF47")); //14: Yellowish green
    dscolors.push_back(TColor::GetColor("#850AFF")); //15: Deep purple
    dscolors.push_back(TColor::GetColor("#85FF0A")); //16: Bright green
    dscolors.push_back(TColor::GetColor("#A347FF")); //17: Light purple
    
    const int dsBlack = dscolors[0];
    const int dsBlue  = dscolors[1];
    const int dsGreen = dscolors[2];
    const int dsPurple= dscolors[3];
    const int dsRed   = dscolors[6];
    
    // Courier font
    int font = 102;
    
    TStyle *MyStyle=new TStyle("MyStyle","MyStyle");
    *MyStyle = *(gROOT->GetStyle("Plain"));

    MyStyle->SetCanvasColor(kWhite);
    MyStyle->SetTitleFillColor(kWhite);
    
    MyStyle->SetName("MyStyle");
    MyStyle->SetCanvasDefH(1105);
    MyStyle->SetCanvasDefW(1920);
    MyStyle->SetLabelFont(font,"xyz");
    MyStyle->SetStatFont(font);
    MyStyle->SetTitleFont(font,"xyz");
    MyStyle->SetTitleFont(font,"pad");
    MyStyle->SetLegendFont(font);
    //MyStyle->SetLegendTextSize();
    MyStyle->SetLabelSize(.045,"xyz");
    MyStyle->SetTitleSize(.045,"xyz");
    MyStyle->SetFuncWidth(2);
    MyStyle->SetHistLineWidth(2);
    MyStyle->SetLegendBorderSize(0);
    MyStyle->SetOptFit(1);
    MyStyle->SetOptStat(0);
    MyStyle->SetStatBorderSize(0);
    MyStyle->SetTitleBorderSize(0);
    MyStyle->SetDrawBorder(0);
    MyStyle->SetStatStyle(0);
    MyStyle->SetStatX(0.85);            //Stat box x position (top right hand corner)
    MyStyle->SetStatY(0.85);            //Stat box y position
    MyStyle->SetStatW(.12);             //Stat box width as fraction of pad size
    MyStyle->SetStatH(.12);             //Size of each line in stat box
	MyStyle->SetStatColor(0);           //Stat box fill color
	MyStyle->SetStatTextColor(1);		//Stat box text color
	MyStyle->SetStatStyle(1001);		//Stat box fill style!
	MyStyle->SetStatFont(102);  		//Stat box fond
	MyStyle->SetStatBorderSize(2);		//Stat box border thickness
    MyStyle->SetTitleStyle(0);
    MyStyle->SetTitleX(.2);
    MyStyle->SetTitleXOffset(1.2);
    MyStyle->SetTitleYOffset(1.2);
    MyStyle->SetTitleW(.65);
    MyStyle->SetTitleY(.98);
    MyStyle->SetTitleH(.07);
    MyStyle->SetStatColor(0);
    MyStyle->SetStatBorderSize(0);
    MyStyle->SetFillColor(10);
    MyStyle->SetFillStyle(0);
    MyStyle->SetTextFont(102);
    MyStyle->SetCanvasBorderMode(0);
    MyStyle->SetPadBorderMode(0);
    MyStyle->SetPadLeftMargin(0.13);
    MyStyle->SetPadRightMargin(0.13);
    MyStyle->SetFrameBorderMode(0);
    MyStyle->SetDrawBorder(0);
    MyStyle->SetPalette(1,0);

    const int NRGBs = 5;
    const int NCont = 255;
    double stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    double red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    double blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    MyStyle->SetNumberContours(NCont);
    
    gROOT->SetStyle("MyStyle");
    gROOT->ForceStyle(true);
    
}

#endif
