#ifndef Analysis_H
#define Analysis_H

#include "rootstart.h"

#include "TROOT.h"
#include "TStopwatch.h"
#include "TString.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TMath.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TList.h"

#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>

#define N_CHANNELS 38
#define PRESCALE 33
#define TPC_RMAX 17.44 // TPC radius (cold)
//#define TPC_FULL_MASS 43.9 //kg; used in depletion factor plots
//#define TPC_CORE_MASS 4.1  //kg; used in depletion factor plots
#define FULL_VOL_TDRIFT_MIN 40    //[us]
#define FULL_VOL_TDRIFT_MAX 310   //[us]
#define CORE_TDRIFT_MIN 135       //[us]
#define CORE_TDRIFT_MAX 235       //[us]
#define CORE_R_MAX 10             //[cm]
#define CORE2_TDRIFT_MIN 40
#define CORE2_TDRIFT_MAX 334.6
#define CORE2_R_MAX 14.14         // = sqrt(200)
#define VDRIFT 0.93               //[mm/us]
#define LAR_DENSITY 1.4           //[g/cm^3]

#define FV_TDRIFT_MIN 40
#define FV_TDRIFT_MAX 334.6
#define S1_MIN 60.
#define S1_MAX 460.

const Int_t nCuts = 24;
enum EventCut_t {
  NOCUTS,        NCHANNEL,     BASELINE,      LIVEINHIBIT,    LONGWAIT,                      //BASIC
  VETO_PRESENT,  VETO_PROMPT,  VETO_DELAYED,  VETO_PREPROMPT, VETO_MUON,  VETO_COSMOGENIC,   //VETO PHYSICS
  NPULSES,       TRIGGERTIME,  S1SATURATION,  S1MAXFRAC,      S2VALID,    S2MINIMUM,         //TPC PHYSICS
  S2MAXIMUM,     Z_FIDUCIAL,   S1RANGE,                                                      //TPC PHYSICS
  RADIUS16,      S2OVERS1,     RADIUS10,      FASTf90                                        //TEST CUTS
}; // enum starts from 0. ie, NOCUTS=0, NCHANNEL=1, ...

const EColor colors[26] = {kBlack, kGray, kYellow, kRed, kMagenta, kBlue, kCyan, kGreen,
                           EColor(kOrange-5), EColor(kPink-5), EColor(kViolet-5), EColor(kAzure-5), EColor(kTeal-5), EColor(kSpring-5), 
                           EColor(kYellow+2), EColor(kRed+2), EColor(kMagenta+2), EColor(kBlue+2), EColor(kCyan+2), EColor(kGreen+2),
                           EColor(kYellow-9), EColor(kRed-9), EColor(kMagenta-9), EColor(kBlue-9), EColor(kCyan-9), EColor(kGreen-9)};

struct TPCEvent {
  // variables from main file
  // SLAD RunXXXXXX.root
  //events
  Int_t tpc_run_id;
  Int_t tpc_subrun_id;
  Int_t tpc_event_id;
  UInt_t tpc_dig_sum;
  //gps
  Int_t tpc_gps_coarse;
  Int_t tpc_gps_fine;
  //long_lifetime
  Double_t live_time;
  Double_t inhibit_time;
  //logbook
  //trigger
  UInt_t trigger_type;
  
  //nchannels
  Int_t nchannels;
  //baseline
  Short_t baseline_not_found;
  //npulses
  Int_t npulses;
  Int_t has_s3;
  Int_t has_s1echo;
  //tdrift
  Double_t tdrift;
  //s1
  Float_t total_s1;
  Float_t total_s1_corr;
  Float_t total_s1_top;
  Float_t total_s1_bottom;
  Float_t total_s1_long_us_integrals[170];
  Float_t total_s2_long_us_integrals[170]; 
  //s1_saturation
  Int_t s1_saturated;
  //s1_time
  Float_t s1_start_time;
  //s1_f90
  Float_t total_f90;
  //s1_fraction
  Int_t s1_max_chan;
  Float_t s1_max_frac;
  //max_s1_frac_cut
  Float_t max_s1_frac_cut_threshold99;
  Int_t max_s1_frac_cut_exceeds99;
  //s2
  Float_t total_s2;
  //s2_saturation
  Int_t s2_saturated;
  //s2_f90
  Float_t total_s2_f90_fixed;
  //bary_s2
  
  // SLAD RunXXXXXX_s2.root
  //s2_fraction
  //Int_t s2_max_chan;
  //Float_t s2_max_frac;
  //Float_t s2_ch_frac[N_CHANNELS];
  
  // SLAD RunXXXXXX_masas_xy.root
  // variables from xy file
  Float_t x_masas;
  Float_t y_masas;
  Float_t xycorr_factor_masas;
  Float_t r_masas;
  Float_t theta_masas;

  Float_t pulse_x_masas[100];
  Float_t pulse_y_masas[100];
  Float_t pulse_xycorr_factor_masas[100];
  Float_t pulse_r_masas[100];
  Float_t pulse_theta_masas[100];
  
  // SLAD RunXXXXXX_xylocator_xy.root
  // variables from xy file
  Float_t x_jasons;
  Float_t y_jasons;
  Float_t xycorr_factor_jasons;
  Float_t r_jasons;
  Float_t theta_jasons;

  Float_t pulse_x_jasons[100];
  Float_t pulse_y_jasons[100];
  Float_t pulse_xycorr_factor_jasons[100];
  Float_t pulse_r_jasons[100];
  Float_t pulse_theta_jasons[100];
 
  // SLAD RunXXXXXX_xylocator_xy.root
  // variables from xy file
  Float_t x_aww;
  Float_t y_aww;
  Float_t xycorr_factor_aww;
  Float_t r_aww;
  Float_t theta_aww;
  
  Float_t pulse_x_aww[100];
  Float_t pulse_y_aww[100];
  Float_t pulse_xycorr_factor_aww[100];
  Float_t pulse_r_aww[100];
  Float_t pulse_theta_aww[100];
  
  // SLAD RunXXXXXX_allpulses.root
  //pulse_info
  Float_t pulse_start_time[100];
  Float_t pulse_max_ch[100];
  Float_t pulse_us_integrals[7*100];
  Float_t pulse_peak_time[100];
  Float_t pulse_peak_amp[100];
  
  // SLAD RunXXXXXX_veto.root
  Int_t veto_run_id;
  Int_t veto_event_id;
  Int_t veto_present;
  Float_t veto_lsv_total_charge;
  Float_t veto_wt_total_charge;
  Int_t	veto_nclusters; 
  std::vector<float>* veto_roi_lsv_charge_vec;
  std::vector<float>* veto_slider_lsv_charge_vec;
  std::vector<float>* veto_cluster_dtprompt_vec;
  std::vector<float>* veto_cluster_charge_vec;

  // Variables to be calculated on the fly
  Float_t s1_prompt;
  Float_t s1_late;
  Float_t s1_tbacorr;
  Float_t s1_prompt_tbacorr;
  Float_t s1_late_tbacorr;
  Float_t x, y, z, r, xycorr_factor;
  Float_t total_s2_xycorr;
  Float_t s1mf_threshold;

  Float_t nr_median_s2;
  Float_t nr_rms_s2;
  Float_t nr_sigma_s2;

  Float_t nr_s2overs1;
  Float_t s2overs1;

  Float_t kr85mpeaktime;
  Float_t p0f5000;

  Float_t muon_dt;   // Time since previous muon
};


Float_t s1_tbacorr(Float_t s1, Float_t tbasym){
  
  Float_t s1_par0 = 0.948485;
  Float_t s1_par1 = -0.793215;
  Float_t s1_par2 = -2.26064;
  Float_t s1_par3 = 6.84532;
  Float_t s1_par4 = 73.8491;
  Float_t s1_par5 = 127.36;
  Float_t s1_corr = 0.;

  if (tbasym <= -0.35)   s1_corr = s1/(s1_par0 + s1_par1*-0.35 + s1_par2*pow(-0.35,2) + s1_par3*pow(-0.35,3) + s1_par4*pow(-0.35,4) + s1_par5*pow(-0.35,5));
  else if(tbasym < 0.15) s1_corr = s1/(s1_par0 + s1_par1*tbasym + s1_par2*pow(tbasym,2) + s1_par3*pow(tbasym,3) + s1_par4*pow(tbasym,4) + s1_par5*pow(tbasym,5));
  else                   s1_corr = s1/(s1_par0 + s1_par1*0.15 + s1_par2*pow(0.15,2) + s1_par3*pow(0.15,3) + s1_par4*pow(0.15,4) + s1_par5*pow(0.15,5));

  return s1_corr;
}

//---------------------------------------
// AAr G2 trigger has pre-scale thresholds, and the thresholds are run dependent.
//
// The function below check to see if an events is pre-scaled
// The pre-scale factor is 33, meaning only 1/33 of AAr events is saved
// If this event is pre-scaled, you can fill the same event 33 times
//
// Note, below check is only valid for 50d AAr (calibration run are more complicated)
//----------------------------------------


Bool_t isPrescaled(TPCEvent const& e) {
  
  UInt_t thres[2] = {999999, 999999};
  if (e.tpc_run_id >= 5372 && e.tpc_run_id <= 8433) {
    if (e.tpc_run_id < 7854) {
      thres[0] = 999999;
      thres[1] = 999999;
    }
    else if (e.tpc_run_id >= 7854 && e.tpc_run_id < 8276){
      thres[0] = 360;
      thres[1] = 999999;
    }
    else{
      thres[0] = 360;
      thres[1] = 1500;
    }
  }
  else return false;
  
  if (e.tpc_dig_sum >= thres[0] && e.tpc_dig_sum < thres[1]) return true;
  else return false;
}

#endif