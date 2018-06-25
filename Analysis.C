/*
 
  Usage:
  $ root -b -q data_validation.C(+)

  To run in compiled mode, use the "+".
 
 */

#include "Analysis.h"
#include "Cuts.h"

// bool load_veto = false;
// TString outfile_name = "UAr_result.root";
// TFile* outfile = new TFile(outfile_name, "RECREATE");

Bool_t load_allpulses = true;
Bool_t load_masas_xy = true;
Bool_t load_xylocator_xy = true;
Bool_t load_aww_xy = true;
Bool_t load_veto = true;

void load_tpctree(TChain* tpc_events, TPCEvent& e, bool load_veto) {
  tpc_events->SetBranchStatus("*",0); //disable all
  
  // SLAD RunXXXXXX.root
  // events
  tpc_events->SetBranchStatus("events.run_id", 1);
  tpc_events->SetBranchAddress("run_id", &e.tpc_run_id);

  tpc_events->SetBranchStatus("events.subrun_id", 1);
  tpc_events->SetBranchAddress("subrun_id", &e.tpc_subrun_id);

  tpc_events->SetBranchStatus("events.event_id", 1);
  tpc_events->SetBranchAddress("event_id", &e.tpc_event_id);

  tpc_events->SetBranchStatus("events.tpc_digital_sum", 1);
  tpc_events->SetBranchAddress("tpc_digital_sum", &e.tpc_dig_sum);
  
  // gps
  tpc_events->SetBranchStatus("gps.gps_coarse", 1);
  tpc_events->SetBranchAddress("gps.gps_coarse", &e.tpc_gps_coarse);
  
  tpc_events->SetBranchStatus("gps.gps_fine", 1);
  tpc_events->SetBranchAddress("gps.gps_fine", &e.tpc_gps_fine);
  
  // long_lifetime
  tpc_events->SetBranchStatus("long_lifetime.lifetime",1);
  tpc_events->SetBranchAddress("long_lifetime.lifetime", &e.live_time);

  tpc_events->SetBranchStatus("long_lifetime.inhibittime",1);
  tpc_events->SetBranchAddress("long_lifetime.inhibittime", &e.inhibit_time);
  
  //logbook
  //trigger_type
  tpc_events->SetBranchStatus("trigger_type", 1);
  tpc_events->SetBranchAddress("trigger_type", &e.trigger_type);
  
  //nchannels
  tpc_events->SetBranchStatus("nchannel.nchannel", 1);
  tpc_events->SetBranchAddress("nchannel.nchannel", &e.nchannels);

  // baseline
  tpc_events->SetBranchStatus("baseline.SumChannelHasNoBaseline",1);
  tpc_events->SetBranchAddress("baseline.SumChannelHasNoBaseline", &e.baseline_not_found);

  // npulses
  tpc_events->SetBranchStatus("npulses.n_phys_pulses",1);
  tpc_events->SetBranchAddress("npulses.n_phys_pulses", &e.npulses);

  tpc_events->SetBranchStatus("npulses.has_s3",1);
  tpc_events->SetBranchAddress("npulses.has_s3", &e.has_s3);

  tpc_events->SetBranchStatus("npulses.has_s1echo",1);
  tpc_events->SetBranchAddress("npulses.has_s1echo", &e.has_s1echo);
  
  // tdrift
  tpc_events->SetBranchStatus("tdrift.tdrift", 1);
  tpc_events->SetBranchAddress("tdrift.tdrift", &e.tdrift);

  // s1
  tpc_events->SetBranchStatus("s1.total_s1", 1);
  tpc_events->SetBranchAddress("s1.total_s1", &e.total_s1);
  
  tpc_events->SetBranchStatus("s1.total_s1_corr", 1);
  tpc_events->SetBranchAddress("s1.total_s1_corr", &e.total_s1_corr);
  
  tpc_events->SetBranchStatus("s1.total_s1_top", 1);
  tpc_events->SetBranchAddress("s1.total_s1_top", &e.total_s1_top);
  
  tpc_events->SetBranchStatus("s1.total_s1_bottom", 1);
  tpc_events->SetBranchAddress("s1.total_s1_bottom", &e.total_s1_bottom);

  tpc_events->SetBranchStatus("s1.total_s1_long_us_integrals", 1);
  tpc_events->SetBranchAddress("s1.total_s1_long_us_integrals", &e.total_s1_long_us_integrals);
  
  // s1_saturation
  tpc_events->SetBranchStatus("s1_saturation.is_saturated_pulse0", 1);
  tpc_events->SetBranchAddress("s1_saturation.is_saturated_pulse0", &e.s1_saturated);

  // s1_time
  tpc_events->SetBranchStatus("s1_time.s1_start_time", 1);
  tpc_events->SetBranchAddress("s1_time.s1_start_time", &e.s1_start_time);

  // s1_f90
  tpc_events->SetBranchStatus("s1_f90.total_f90", 1);
  tpc_events->SetBranchAddress("s1_f90.total_f90", &e.total_f90);
  
  // s1_fraction
  tpc_events->SetBranchStatus("s1_fraction.s1_max_chan", 1);
  tpc_events->SetBranchAddress("s1_fraction.s1_max_chan", &e.s1_max_chan);
  
//  tpc_events->SetBranchStatus("s1_fraction.s1_max_frac", 1);
//  tpc_events->SetBranchAddress("s1_fraction.s1_max_frac", &e.s1_max_frac);

  tpc_events->SetBranchStatus("s1_fraction.s1_prompt_max_frac", 1);
  tpc_events->SetBranchAddress("s1_fraction.s1_prompt_max_frac", &e.s1_max_frac);
  
  // max_s1_frac_cut
  tpc_events->SetBranchStatus("max_s1_frac_cut.max_s1_frac_cut_threshold99", 1);
  tpc_events->SetBranchAddress("max_s1_frac_cut.max_s1_frac_cut_threshold99", &e.max_s1_frac_cut_threshold99);
  
  tpc_events->SetBranchStatus("max_s1_frac_cut.max_s1_frac_cut_exceeds99", 1);
  tpc_events->SetBranchAddress("max_s1_frac_cut.max_s1_frac_cut_exceeds99", &e.max_s1_frac_cut_exceeds99);
  
  // s2
  tpc_events->SetBranchStatus("s2.total_s2", 1);
  tpc_events->SetBranchAddress("s2.total_s2", &e.total_s2);
  
  // s2_saturation
  tpc_events->SetBranchStatus("s2_saturation.is_saturated_pulse1", 1);
  tpc_events->SetBranchAddress("s2_saturation.is_saturated_pulse1", &e.s2_saturated);


  // s2_f90
  tpc_events->SetBranchStatus("s2_f90.total_s2_f90", 1);
  tpc_events->SetBranchAddress("s2_f90.total_s2_f90", &e.total_s2_f90_fixed);

   if (load_masas_xy) {
    // SLAD RunXXXXXX_masas_xy.root
    // masa_x
    tpc_events->SetBranchStatus("masas_x", 1);
    tpc_events->SetBranchAddress("masas_x", &e.x_masas);
    
    // masa_y
    tpc_events->SetBranchStatus("masas_y", 1);
    tpc_events->SetBranchAddress("masas_y", &e.y_masas);
    
    // masas_chi2
    
    // masas_xycorr_factor
    tpc_events->SetBranchStatus("masas_xycorr_factor", 1);
    tpc_events->SetBranchAddress("masas_xycorr_factor", &e.xycorr_factor_masas);
    
    // masa_r
    tpc_events->SetBranchStatus("masas_r", 1);
    tpc_events->SetBranchAddress("masas_r", &e.r_masas);
    
    // masa_theta
    tpc_events->SetBranchStatus("masas_theta", 1);
    tpc_events->SetBranchAddress("masas_theta", &e.theta_masas);
    
    // masa_x
    tpc_events->SetBranchStatus("allpulses_x", 1);
    tpc_events->SetBranchAddress("allpulses_x", &e.pulse_x_masas);
    
    // masa_y
    tpc_events->SetBranchStatus("allpulses_y", 1);
    tpc_events->SetBranchAddress("allpulses_y", &e.pulse_y_masas);
    
    // masas_chi2
    
    // masas_xycorr_factor
    tpc_events->SetBranchStatus("allpulses_xycorr_factor", 1);
    tpc_events->SetBranchAddress("allpulses_xycorr_factor", &e.pulse_xycorr_factor_masas);
    
    // masa_r
    tpc_events->SetBranchStatus("allpulses_r", 1);
    tpc_events->SetBranchAddress("allpulses_r", &e.pulse_r_masas);
    
    // masa_theta
    tpc_events->SetBranchStatus("allpulses_theta", 1);
    tpc_events->SetBranchAddress("allpulses_theta", &e.pulse_theta_masas);
  }

  if (load_xylocator_xy) {
    // SLAD RunXXXXXX_xylocator_xy.root
    // xyl_SCM
    
    // xyl_best_x
    tpc_events->SetBranchStatus("xyl_best_x", 1);
    tpc_events->SetBranchAddress("xyl_best_x", &e.x_jasons);
    
    // xyl_best_y
    tpc_events->SetBranchStatus("xyl_best_y", 1);
    tpc_events->SetBranchAddress("xyl_best_y", &e.y_jasons);
    
    // xyl_best_chi2
    
    // xylocator xy correction factor
    tpc_events->SetBranchStatus("xyl_best_xycorr_factor", 1);
    tpc_events->SetBranchAddress("xyl_best_xycorr_factor", &e.xycorr_factor_jasons);
    
    // xyl_best_r
    tpc_events->SetBranchStatus("xyl_best_r", 1);
    tpc_events->SetBranchAddress("xyl_best_r", &e.r_jasons);
    
    // xyl_best_theta
    tpc_events->SetBranchStatus("xyl_best_theta", 1);
    tpc_events->SetBranchAddress("xyl_best_theta", &e.theta_jasons);
    
    
    // xyl_best_x
    tpc_events->SetBranchStatus("allpulses_xyl_x", 1);
    tpc_events->SetBranchAddress("allpulses_xyl_x", &e.pulse_x_jasons);
    
    // xyl_best_y
    tpc_events->SetBranchStatus("allpulses_xyl_y", 1);
    tpc_events->SetBranchAddress("allpulses_xyl_y", &e.pulse_y_jasons);
    
    // xyl_best_chi2
    
    // xylocator xy correction factor
    tpc_events->SetBranchStatus("allpulses_xyl_xycorr_factor", 1);
    tpc_events->SetBranchAddress("allpulses_xyl_xycorr_factor", &e.pulse_xycorr_factor_jasons);
    
    // xyl_best_r
    tpc_events->SetBranchStatus("allpulses_xyl_r", 1);
    tpc_events->SetBranchAddress("allpulses_xyl_r", &e.pulse_r_jasons);
    
    // xyl_best_theta
    tpc_events->SetBranchStatus("allpulses_xyl_theta", 1);
    tpc_events->SetBranchAddress("allpulses_xyl_theta", &e.pulse_theta_jasons);
  }

  if (load_aww_xy) {
    // SLAD RunXXXXXX_aww_xy.root
    // aww_x
    tpc_events->SetBranchStatus("aww_x", 1);
    tpc_events->SetBranchAddress("aww_x", &e.x_aww);
    
    // aww_y
    tpc_events->SetBranchStatus("aww_y", 1);
    tpc_events->SetBranchAddress("aww_y", &e.y_aww);
    
    // aww_chi2
    
    // aww_xycorr_factor
    tpc_events->SetBranchStatus("aww_xycorr_factor", 1);
    tpc_events->SetBranchAddress("aww_xycorr_factor", &e.xycorr_factor_aww);
    
    // aww_r
    tpc_events->SetBranchStatus("aww_r", 1);
    tpc_events->SetBranchAddress("aww_r", &e.r_aww);
    
    // aww_theta
    tpc_events->SetBranchStatus("aww_theta", 1);
    tpc_events->SetBranchAddress("aww_theta", &e.theta_aww);
    
    // aww_x
    tpc_events->SetBranchStatus("allpulses_x", 1);
    tpc_events->SetBranchAddress("allpulses_x", &e.pulse_x_aww);
    
    // aww_y
    tpc_events->SetBranchStatus("allpulses_y", 1);
    tpc_events->SetBranchAddress("allpulses_y", &e.pulse_y_aww);
    
    // aww_chi2
    
    // aww_xycorr_factor
    tpc_events->SetBranchStatus("allpulses_xycorr_factor", 1);
    tpc_events->SetBranchAddress("allpulses_xycorr_factor", &e.pulse_xycorr_factor_aww);
    
    // aww_r
    tpc_events->SetBranchStatus("allpulses_r", 1);
    tpc_events->SetBranchAddress("allpulses_r", &e.pulse_r_aww);
    
    // aww_theta
    tpc_events->SetBranchStatus("allpulses_theta", 1);
    tpc_events->SetBranchAddress("allpulses_theta", &e.pulse_theta_aww);
  }

  if (load_allpulses) {
    // SLAD RunXXXXXX_allpulses.root
    // pulse_info
    tpc_events->SetBranchStatus("pulse_info.pulse_info_start_time", 1);
    tpc_events->SetBranchAddress("pulse_info.pulse_info_start_time", e.pulse_start_time);
    
    tpc_events->SetBranchStatus("pulse_info.pulse_info_max_chan", 1);
    tpc_events->SetBranchAddress("pulse_info.pulse_info_max_chan", e.pulse_max_ch);

    tpc_events->SetBranchStatus("pulse_info.pulse_info_us_integrals", 1);
    tpc_events->SetBranchAddress("pulse_info.pulse_info_us_integrals", e.pulse_us_integrals);

    tpc_events->SetBranchStatus("pulse_info.pulse_info_peak_time", 1);
    tpc_events->SetBranchAddress("pulse_info.pulse_info_peak_time", e.pulse_peak_time);
    
    tpc_events->SetBranchStatus("pulse_info.pulse_info_peak_amp", 1);
    tpc_events->SetBranchAddress("pulse_info.pulse_info_peak_amp", e.pulse_peak_amp);
  }
  if (load_veto) {
    // SLAD RunXXXXXX_veto.root
    tpc_events->SetBranchStatus("veto_run_id", 1);
    tpc_events->SetBranchAddress("veto_run_id", &e.veto_run_id);

    tpc_events->SetBranchStatus("veto_nclusters", 1);
    tpc_events->SetBranchAddress("veto_nclusters", &e.veto_nclusters);    

    tpc_events->SetBranchStatus("veto_event_id", 1);
    tpc_events->SetBranchAddress("veto_event_id", &e.veto_event_id);
    
    tpc_events->SetBranchStatus("veto_present", 1);
    tpc_events->SetBranchAddress("veto_present", &e.veto_present);
    
    tpc_events->SetBranchStatus("veto_lsv_total_charge", 1);
    tpc_events->SetBranchAddress("veto_lsv_total_charge", &e.veto_lsv_total_charge);
    
    tpc_events->SetBranchStatus("veto_wt_total_charge", 1);
    tpc_events->SetBranchAddress("veto_wt_total_charge", &e.veto_wt_total_charge);
  
    e.veto_roi_lsv_charge_vec = 0;
   e.veto_slider_lsv_charge_vec = 0;
    e.veto_cluster_dtprompt_vec = 0;
    e.veto_cluster_charge_vec = 0;
  
    tpc_events->SetBranchStatus("veto_roi_lsv_charge_vec", 1);
    tpc_events->SetBranchAddress("veto_roi_lsv_charge_vec", &e.veto_roi_lsv_charge_vec);
  
    tpc_events->SetBranchStatus("veto_slider_lsv_charge_vec", 1);
    tpc_events->SetBranchAddress("veto_slider_lsv_charge_vec", &e.veto_slider_lsv_charge_vec);

	
    tpc_events->SetBranchStatus("veto_cluster_dtprompt_vec", 1);
    tpc_events->SetBranchAddress("veto_cluster_dtprompt_vec", &e.veto_cluster_dtprompt_vec);
  
    tpc_events->SetBranchStatus("veto_cluster_charge_vec", 1);
    tpc_events->SetBranchAddress("veto_cluster_charge_vec", &e.veto_cluster_charge_vec);
  }
} 


void s1_to_txt(std::ofstream& s1pulse, TPCEvent& e){
        if (s1pulse.is_open()){ //Write s1 signal up to 7 usec into text file 
            s1pulse << e.tpc_run_id<< " ";
            s1pulse << e.tpc_event_id << " ";
        for(int i = 0; i<58; i++){
            s1pulse << e.total_s1_long_us_integrals[i] << " ";
        }
        s1pulse << " " << endl;
    }
    else{
        cout << "Can't open the txt file" << endl;
    }    
    }

void event_loop(TFile* outfile, TChain* tpc_events, bool load_veto, TString type = "uar", Int_t nevents=-1, TString txt_output="") {
  TH1::SetDefaultSumw2(kTRUE);
  
  TPCEvent e;
  load_tpctree(tpc_events, e, load_veto);

  Bool_t aar  = (type == "aar");
  Bool_t uar  = (type == "uar");
  Bool_t ambe = (type == "ambe" || type == "ambebg");


  //Load max_s1_frac threshold file so can apply other versions of S1 max frac cut on the fly.
  TFile* s1mf_file = new TFile("max_frac_cut_fixed_acceptance_full_stats.root");
  if(s1mf_file->IsZombie() || !s1mf_file) std::cout << "Bad S1mf_file" << std::endl;
  TH2F* h_s1mf_thresholds = (TH2F*) s1mf_file->Get("s1pmf_c95"); // Load 95%ile cut.
  
  // Load 1-sigma contours for getting NR from AmBe data
  TFile* dmbox_file = new TFile("dmbox.root");
  if(dmbox_file->IsZombie() || !dmbox_file) std::cout << "Bad dmbox_file (getting NR 99% acc from here)" << std::endl;
  TGraph* ambe_acc99 = (TGraph*) dmbox_file->Get("NRacceptances/g_acceptance_99");

  outfile->cd();
  outfile->mkdir(type);
  outfile->cd(type);

  TH2F* h_S1_f90 = new TH2F("h_S1_f90","UAr data", 200, 0., 1000., 100., 0., 1.);
  h_S1_f90 -> GetXaxis() -> SetTitle("S1 [PE]");
  h_S1_f90 -> GetYaxis() -> SetTitle("f90");
 
  TH2F*  h_s1_s2s1 = new TH2F("h_s1_s2s1", "No veto cuts, deep R", 200, 0, 1000, 250, 0, 2.5);
  h_s1_s2s1->GetXaxis()->SetTitle("S1 [PE]");
  h_s1_s2s1->GetYaxis()->SetTitle("Log_{10}(S2/S1)");
  
  //TH2F* h_f90_s2s1 = new TH2F("h_f90_s2s1", "No veto cuts, deep R", 500, 0, 1, 250, 0, 2.5);
  //h_f90_s2s1->GetXaxis()->SetTitle("f_{90}");
  //h_f90_s2s1->GetYaxis()->SetTitle("Log_{10}(S2/S1)");
    
  TH1F* h_tdrift       = new TH1F("h_tdrift",       "; t_{drift} [#mus]", 200, 0., 400.);
  TH1F* h_tdrift_lowS1 = new TH1F("h_tdrift_lowS1", "; t_{drift} [#mus]", 200, 0., 400.);
  TH1F* h_S2f90        = new TH1F("h_S2f90",        "; S2_f90", 1000, 0., 1.);

  TString s1_filename = txt_output;
  if(type == "aar"){   s1_filename += "s1_signal_ER.txt";}
  if(type == "kr"){    s1_filename += "s1_signal_Kr.txt";}
  if(type == "ambe"){  s1_filename += "s1_signal_NR.txt";}
  if(type == "uar"){   s1_filename += "s1_signal_UAR.txt";}
  
  ofstream s1pulse(s1_filename);
  
  TDirectory* MLP_output = gDirectory->mkdir("MLP");
  MLP_output->cd();
  const Int_t nmlp = 2;
  TH2F** h_MLP = new TH2F*[nmlp];
  const Int_t nbins_s1_mlp = 200, nbins_f90_mlp = 100;
  const Float_t s1_min_mlp = 0., s1_max_mlp = 1000., f90_min_mlp = 0., f90_max_mlp = 1.;
  const TString h_MLPLabels[nmlp] = {
    "MLP result, label 1","MLP result, label 0",
  };
  for (Int_t ihmlp=0; ihmlp<nmlp; ++ihmlp) {
    h_MLP[ihmlp] = new TH2F(Form("h_mlp_%d",ihmlp),h_MLPLabels[ihmlp].Data(),nbins_s1_mlp,s1_min_mlp,s1_max_mlp,nbins_f90_mlp,f90_min_mlp,f90_max_mlp);
    h_MLP[ihmlp]->GetXaxis()->SetTitle("S1 [PE]");
    h_MLP[ihmlp]->GetYaxis()->SetTitle("f_{90}");
  }

  TH2F** h_f90_s2s1 = new TH2F*[nmlp];
 
  for (Int_t ihmlp=0; ihmlp<nmlp; ++ihmlp) {
    h_f90_s2s1[ihmlp] = new TH2F(Form("h_f90_s2s1_%d",ihmlp),h_MLPLabels[ihmlp].Data(), 500, 0, 1, 250, 0, 2.5);
    h_f90_s2s1[ihmlp]->GetXaxis()->SetTitle("f_{90}");
    h_f90_s2s1[ihmlp]->GetYaxis()->SetTitle("Log_{10}(S2/S1)");
  }
  
  outfile->cd(type);
  TDirectory* Slice = gDirectory->mkdir("Slices");
  Slice->cd();
  const Int_t nhslice = 12;
  TH1F* h_Slice[nhslice];
  const Int_t nbins_f90_slice = 200;
  const Float_t f90_min_bin_slice = 0., f90_max_bin_slice = 1;
  const TString h_SliceLabel[nhslice] = {
    "MLP, label 1, 0<s1[PE]<50", "MLP, label 0, 0<s1[PE]<50, AmC data",
    "MLP, label 1, 50<s1[PE]<100", "MLP, label 0, 50<s1[PE]<100, AmC data",
    "MLP, label 1, 100<s1[PE]<200", "MLP, label 0, 100<s1[PE]<200, AmC data",
    "MLP, label 1, 200<s1[PE]<300", "MLP, label 0, 200<s1[PE]<300, AmC data",
    "MLP, label 1, 300<s1[PE]<500", "MLP, label 0, 300<s1[PE]<500, AmC data",
    "MLP, label 1, 500<s1[PE]<1000", "MLP, label 0, 500<s1[PE]<1000, AmC data"
  };
  for (Int_t ihslice=0; ihslice<nhslice; ++ihslice){
   h_Slice[ihslice] = new TH1F(Form("h_slice_%d",ihslice),h_SliceLabel[ihslice].Data(), nbins_f90_slice, f90_min_bin_slice, f90_max_bin_slice);
    h_Slice[ihslice]->GetXaxis()->SetTitle("f90");	
  }
  
  outfile->cd(type);
  
  ifstream fin(txt_output+"UAr_MLP_output.txt");

  Int_t number=0;
  Int_t target=0;
  Int_t run_number=0;
  Int_t event_number=0;

  
  //-------------------------//
  //     MAIN EVENT LOOP     //
  //-------------------------//
     
  Int_t tpc_nevents = 0;
  
     if(nevents < 0){
        tpc_nevents = tpc_events->GetEntries();
    }
     else{
        tpc_nevents = nevents;
    }
  cout << "Total events: " << tpc_nevents << '\n';
  e.muon_dt = 999;
  int event_counter = 0;
  for (Int_t n = 0; n<tpc_nevents; n++) {
    if (!(n%1000000)) cout << "Processing event " << n << ", " << Int_t(100.*n/tpc_nevents) << "% completed" << endl;
    tpc_events->GetEntry(n);    

       // Calculate some variables on the fly
    e.s1_prompt       = e.total_f90 * e.total_s1;
    e.s1_late         = e.total_s1 - e.s1_prompt;
    e.x               = (e.x_masas > -99. ? e.x_masas : (e.x_jasons > -99. ? e.x_jasons : -998.)); //Use Masa's xy by default. If not good, try Jason's. If still not good, junk.
    e.y               = (e.y_masas > -99. ? e.y_masas : (e.y_jasons > -99. ? e.y_jasons : -998.));
    e.r               = (e.r_masas > -99. ? e.r_masas : (e.r_jasons > -99. ? e.r_jasons : -998.));
    e.xycorr_factor   = (e.xycorr_factor_masas > -99. ? e.xycorr_factor_masas : (e.xycorr_factor_jasons > -99. ? e.xycorr_factor_jasons : -998.));
    e.total_s2_xycorr = e.total_s2 * e.xycorr_factor;
//    Int_t s1mf_xbin   = h_s1mf_thresholds->GetXaxis()->FindBin(e.total_s1_corr);
    Int_t s1mf_xbin   = h_s1mf_thresholds->GetXaxis()->FindBin(e.s1_prompt); // S1pmf cut uses s1_prompt binning
    Int_t s1mf_ybin   = h_s1mf_thresholds->GetYaxis()->FindBin(e.tdrift);
    e.s1mf_threshold  = h_s1mf_thresholds->GetBinContent(s1mf_xbin, s1mf_ybin);	
    
    // Generate cuts.
    Bool_t CX_nchan           = cx_nchan(e); // CX#1
    Bool_t CX_baseline        = cx_baseline(e); // CX#2
    Bool_t CX_event_dt        = cx_event_dt(e); // CX#3
    Bool_t CX_file_io         = (aar ? cx_file_io(e) : true); // CX#4 //apply if type is aar. otherwise, don't apply
    Bool_t CX_veto_present    = ((aar || uar) && cx_veto_present(e)) || (ambe);
    Bool_t CX_veto_prompt     = (aar && cx_old_veto_prompt(e))  || (uar && cx_veto_prompt(e))    || (ambe);
    Bool_t CX_veto_delayed    = (aar && cx_old_veto_delayed(e)) || (uar && cx_veto_delayed(e))   || (ambe);
    Bool_t CX_veto_preprompt  = (aar)                           || (uar && cx_veto_preprompt(e)) || (ambe);
    Bool_t CX_veto_muon       = (aar)                           || (uar && cx_veto_muon(e))      || (ambe);
    Bool_t CX_veto_cosmogenic = (aar)                           || (uar && cx_veto_cosmogenic(e))|| (ambe);
    Bool_t CX_single_scatter  = cx_single_scatter(e); // CX#8
    Bool_t CX_fiducial        = cx_fiducial(e); // CX#15
    Bool_t CX_quality        = (CX_nchan && CX_baseline && CX_event_dt && CX_file_io && CX_veto_present); // CX#QUALITY
    Bool_t CX_veto           = (CX_veto_present && CX_veto_prompt && CX_veto_delayed && CX_veto_preprompt && CX_veto_muon && CX_veto_cosmogenic);
    Bool_t CX_trg_time        = cx_trg_time(e); // CX#9
    Bool_t CX_s1_sat          = cx_s1_sat(e); // CX#10
    Bool_t CX_s1_mf           = cx_s1_mf(e); // CX#11
    Bool_t CX_s2_f90          = cx_s2_f90(e); // CX#12
    Bool_t CX_s2_size         = cx_s2_size(e); // CX#13
    Bool_t CX_s1_range        = cx_s1_range(e); // CX#14
    Bool_t CX_r10             = cx_r(e, 10.); // CX#18
    Bool_t CX_f90_s2s1_s1range = cx_f90_s2s1_s1range(e);
    Bool_t isNR              = (e.total_f90 > ambe_acc99->Eval(e.total_s1_corr));

    // Quantities
    Float_t s1               = e.total_s1_corr;
    Float_t f90              = e.total_f90;
    Float_t s2               = e.total_s2 * e.xycorr_factor;
    Float_t log10s2overs1    = (s2>0 ? TMath::Log10(s2/s1) : -999);
    

    if (e.tdrift > 40. && e.tdrift < 336.){
        
    if (CX_quality && CX_veto && CX_single_scatter && CX_trg_time
        && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size /*&& CX_fiducial*/
        && CX_s1_range)                                                       h_tdrift       -> Fill(e.tdrift);
    if (CX_quality && CX_veto && CX_single_scatter && CX_trg_time                               
        && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size /*&& CX_fiducial*/                  
        && CX_s1_range && s1<200.)                                            h_tdrift_lowS1 -> Fill(e.tdrift);
    if (CX_quality && CX_veto && CX_single_scatter && CX_trg_time                               
        && CX_s1_sat && CX_s1_mf/*&& CX_s2_f90*/&& CX_s2_size && CX_fiducial                    
        && CX_s1_range)                                                       h_S2f90        -> Fill(e.total_s2_f90_fixed);
    if (CX_quality /*&& CX_veto*/ && CX_single_scatter                                          
        && CX_trg_time && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size                      
        /*&& CX_s1_range*/ && CX_fiducial && CX_r10)                          h_s1_s2s1      -> Fill(s1,log10s2overs1);	
    if (CX_quality /*&& CX_veto*/ && CX_single_scatter
        && CX_trg_time && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size
        /*&& CX_s1_range*/ && CX_fiducial && CX_r10 && CX_f90_s2s1_s1range)  // h_f90_s2s1  -> Fill(f90,log10s2overs1);
        
    if(type == "ambe"){    
	for (unsigned i=0; i<e.veto_cluster_dtprompt_vec->size(); i++){
     if (e.veto_cluster_dtprompt_vec->at(i)>-0.05 && e.veto_cluster_dtprompt_vec->at(i)<-0.04){
	 for (unsigned j=0; j<e.veto_cluster_charge_vec->size(); j++){
     if (e.veto_cluster_charge_vec->at(j)>2400 && e.veto_cluster_charge_vec->at(j)<3600){
    
    if(isNR && f90<0.85 && f90>0.5){
        s1_to_txt(s1pulse, e);
        h_S1_f90 -> Fill(s1, f90);
        event_counter++;
            }
    }}}}
    }
    
    
    if(type == "aar"){
    if(f90<0.8 && f90>0.15){ 
        s1_to_txt(s1pulse, e);
        h_S1_f90 -> Fill(s1, f90);
        event_counter++;
    }
    }
    
    if(type == "kr"){
    if(s1>220 && f90<0.45 && f90>0.14){ 
        s1_to_txt(s1pulse, e);
        h_S1_f90 -> Fill(s1, f90);
        event_counter++;
    }
    }
    
    if(type == "uar"){
        s1_to_txt(s1pulse, e);
        h_S1_f90 -> Fill(s1, f90);
        event_counter++;
    }
    
    if(type == "mlp"){
        fin >> number;                                                       //just a number from python, don't use it.
    	fin >> target ;
        fin >> run_number;
	fin >> event_number;
	if (run_number == e.tpc_run_id && event_number == e.tpc_event_id){
	if (target == 0){
            h_MLP[1]->SetMarkerColor(7);
            h_MLP[1]->SetMarkerStyle(7);
	    h_MLP[1]->Fill(s1,f90);
            if (s1>=0. && s1<50.){     h_Slice[1]->Fill(f90);}
	    if (s1>=50. && s1<100.){   h_Slice[3]->Fill(f90);}
 	    if (s1>=100. && s1<200.){  h_Slice[5]->Fill(f90);}
	    if (s1>=200. && s1<300.){  h_Slice[7]->Fill(f90);}
	    if (s1>=300. && s1<500.){  h_Slice[9]->Fill(f90);}
	    if (s1>=500. && s1<1000.){ h_Slice[11]->Fill(f90);}
	if (/*CX_single_scatter
        && CX_trg_time && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size
         &&*/ CX_fiducial /*&& CX_r10*/ && CX_f90_s2s1_s1range){
	 h_f90_s2s1[1]->SetMarkerColor(7);
	 h_f90_s2s1[1]->SetMarkerStyle(26);
	 h_f90_s2s1[1]->SetMarkerSize(1.1);
	//cout << log10s2overs1 << endl;
	 h_f90_s2s1[1]->Fill(f90,log10s2overs1);}
        }
	
	if (target == 1){
	    h_MLP[0]->SetMarkerColor(2);
	    h_MLP[0]->SetMarkerStyle(7);
            h_MLP[0]->Fill(s1,f90);
            if (s1>=0. && s1<50.){     h_Slice[0]->Fill(f90);}
            if (s1>=50. && s1<100.){   h_Slice[2]->Fill(f90);}
            if (s1>=100. && s1<200.){  h_Slice[4]->Fill(f90);}
            if (s1>=200. && s1<300.){  h_Slice[6]->Fill(f90);}
            if (s1>=300. && s1<500.){  h_Slice[8]->Fill(f90);}
            if (s1>=500. && s1<1000.){ h_Slice[10]->Fill(f90);}
	if ( /*CX_single_scatter
        && CX_trg_time && CX_s1_sat && CX_s1_mf && CX_s2_f90 && CX_s2_size
         &&*/ CX_fiducial /*&& CX_r10*/ && CX_f90_s2s1_s1range){
	h_f90_s2s1[0]->SetMarkerColor(2);
	h_f90_s2s1[0]->SetMarkerStyle(24);
	h_f90_s2s1[0]->SetMarkerSize(1.1);
	h_f90_s2s1[0]->Fill(f90,log10s2overs1);}
			
        }
	event_counter++;
	}
	h_S1_f90 -> Fill(s1, f90);
        
    }
    
  }

  }//loop over events
// }}}}
  s1pulse.close();
  cout << "Number of events: " << event_counter << endl;  
}


TChain* load_files(TString mainfile, bool veto)
{

  // Load and friend the TTrees
  TChain* tpc_events = new TChain("events");
  tpc_events->Add(mainfile);

  if (load_masas_xy) {
    TString xyfile_masas = mainfile;
    xyfile_masas.Remove(xyfile_masas.Length()-5);
    xyfile_masas += "_masas_xy.root";
    
    TChain* xy_masas = new TChain("masas_xy");
    xy_masas->Add(xyfile_masas);
    tpc_events->AddFriend(xy_masas);
    
    TChain* pulse_xy_masas = new TChain("allpulses_xy");
    pulse_xy_masas->Add(xyfile_masas);
    tpc_events->AddFriend(pulse_xy_masas);
  }

  if (load_xylocator_xy) {
    TString xyfile_jasons = mainfile;
    xyfile_jasons.Remove(xyfile_jasons.Length()-5);
    xyfile_jasons += "_xylocator_xy.root";

    TChain* xy_jasons = new TChain("xylocator_xy");
    xy_jasons->Add(xyfile_jasons);
    tpc_events->AddFriend(xy_jasons);
    
    TChain* pulse_xy_jasons = new TChain("allpulses_xyl_xy");
    pulse_xy_jasons->Add(xyfile_jasons);
    tpc_events->AddFriend(pulse_xy_jasons);
  }

  if (load_aww_xy) {
    TString xyfile_aww = mainfile;
    xyfile_aww.Remove(xyfile_aww.Length()-5);
    xyfile_aww += "_aww_xy.root";
    
    TChain* xy_aww = new TChain("aww_xy");
    xy_aww->Add(xyfile_aww);
    tpc_events->AddFriend(xy_aww);
    
    TChain* pulse_xy_aww = new TChain("allpulses_aww_xy");
    pulse_xy_aww->Add(xyfile_aww);
    tpc_events->AddFriend(pulse_xy_aww);
  }

  if (load_allpulses) {
    TString pulsefile = mainfile;
    pulsefile.Remove(pulsefile.Length()-5);
    pulsefile += "_allpulses.root";
    
    TChain* pulse_info = new TChain("pulse_info");
    pulse_info->Add(pulsefile);
    tpc_events->AddFriend(pulse_info);
  }

  if (load_veto) {
    TString vetofile = mainfile;
    vetofile.Remove(vetofile.Length()-5);
    vetofile += "_veto_cluster.root";
  
    TChain* veto_events = new TChain("veto");
    veto_events->Add(vetofile);
    tpc_events->AddFriend(veto_events);
  }

  return tpc_events;
}

void Analysis(TString mainfile = "/home/agr/AGR/DarkSide/UAr_70d_SLAD_v3_3_0_no12922.root", TString type = "uar", bool veto = false, Int_t nEvents = 1000000, TString txt_output_dir = "./") {
  
  gROOT->SetBatch(kTRUE);
  gROOT->Reset();
  //SetMyStyle();

  TStopwatch* clock = new TStopwatch();
  clock->Start();
  bool load_veto = veto;  
  
  TString outfile_name = txt_output_dir + type;
  if(veto) outfile_name += "_veto_ON_";
  if(!veto) outfile_name += "_veto_OFF_";
//   if(nEvents>0) outfile_name += std::to_string(nEvents)+"_events_";
//   std::time_t t = std::time(0);
  outfile_name += "output.root";
  TFile* outfile = new TFile(outfile_name, "RECREATE");
  cout << "Saving output to " << outfile->GetName() << '\n';

  TChain* tpc_events = load_files(mainfile, load_veto);
  event_loop(outfile, tpc_events, load_veto, type, nEvents, txt_output_dir); //types are "ambe", "uar", "aar", "kr", "mlp"

  outfile->Write();
  
  outfile->Close();
  
  cout << "Done! " << clock->RealTime() << " s." << endl;
}
