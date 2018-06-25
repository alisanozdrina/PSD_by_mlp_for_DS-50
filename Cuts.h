#ifndef Cuts_H
#define Cuts_H

#include "Analysis.h"

//------------------------------------------------------------------------------
// Define cuts.

//--- Quality cuts
Bool_t cx_nchan(TPCEvent const& e)        { return e.nchannels == N_CHANNELS; }
Bool_t cx_baseline(TPCEvent const& e)     { return e.baseline_not_found == false; }
Bool_t cx_old_event_dt(TPCEvent const& e) { return (e.live_time + e.inhibit_time) > 1.35E-3; } // used in analyses up to 70d.
Bool_t cx_event_dt(TPCEvent const& e)     { return e.live_time > 400.E-6; }
Bool_t cx_file_io(TPCEvent const& e)      { return e.live_time < 1.; } // only for AAr
Bool_t cx_veto_present(TPCEvent const& e) { return e.veto_present > 0; }

//--- Old veto cuts (for AAr)
Bool_t cx_old_veto_prompt(TPCEvent const& e)  { return e.veto_present && e.veto_roi_lsv_charge_vec->at(3) < 10.; }
Bool_t cx_old_veto_delayed(TPCEvent const& e) { return
    e.veto_present && e.veto_slider_lsv_charge_vec->at(2) < 80. && e.veto_slider_lsv_charge_vec->at(3) < 110. && e.veto_wt_total_charge < 200.; }
    
//--- Veto cuts for UAr
Bool_t cx_veto_prompt(TPCEvent const& e)     { return e.veto_present && !(e.veto_roi_lsv_charge_vec->at(0) > 1.); }
Bool_t cx_veto_delayed(TPCEvent const& e)    { return e.veto_present &&
    !((e.veto_run_id < 12638 && e.veto_slider_lsv_charge_vec->at(0) > 3.) || (e.veto_run_id >= 12638 && e.veto_slider_lsv_charge_vec->at(0) > 6.)); }
Bool_t cx_veto_preprompt(TPCEvent const& e)  { return e.veto_present && !(e.veto_slider_lsv_charge_vec->at(1) > 3.); }
Bool_t cx_veto_muon(TPCEvent const& e)       { return e.veto_present && !(e.veto_lsv_total_charge > 2000. || e.veto_wt_total_charge > 400.); }
Bool_t cx_veto_cosmogenic(TPCEvent const& e) { return e.veto_present && e.muon_dt > 2.; }

//--- For estimating Veto prompt cut acceptance
Bool_t cx_veto_prompt_acc(TPCEvent const& e)     { return e.veto_present && e.veto_roi_lsv_charge_vec->at(1) > 1.; }
Bool_t cx_veto_prompt_acc_sys(TPCEvent const& e) { return e.veto_present && e.veto_roi_lsv_charge_vec->at(2) > 1.; }

//--- Physics cuts
Bool_t cx_single_scatter(TPCEvent const& e)  { return e.npulses == 2 || (e.npulses == 3 && e.has_s3); }
Bool_t cx_trg_time(TPCEvent const& e) { return
  ((e.tpc_run_id >= -999 && e.tpc_run_id < 7344 && e.s1_start_time >= -0.25 && e.s1_start_time <= -0.15) ||
   (e.tpc_run_id >= 7344 && e.tpc_run_id < 7641 && e.s1_start_time >= -4.10 && e.s1_start_time <= -4.00) ||
   (e.tpc_run_id >= 7641 && e.tpc_run_id < 999999 && e.s1_start_time >= -6.10 && e.s1_start_time <= -6.00)); }
Bool_t cx_s1_sat(TPCEvent const& e)   { return e.s1_saturated == 0; }
Bool_t cx_s1_mf(TPCEvent const& e)    { return e.s1_max_frac < e.s1mf_threshold; }
Bool_t cx_s2_f90(TPCEvent const& e)   { return e.total_s2_f90_fixed < 0.2; }
Bool_t cx_s2_size(TPCEvent const& e)  { return e.r > 0. && e.r < 20. && e.total_s2_xycorr > 100.; }
Bool_t cx_max_s2(TPCEvent const& e)   { return e.r > 0. && e.r < 20. && e.total_s2_xycorr < 8000.; } // NEW
Bool_t cx_s1_range(TPCEvent const& e) { return e.total_s1_corr > S1_MIN && e.total_s1_corr < S1_MAX; }
Bool_t cx_fiducial(TPCEvent const& e) { return e.tdrift > FV_TDRIFT_MIN && e.tdrift < FV_TDRIFT_MAX; }
Bool_t cx_r(TPCEvent const& e, Float_t r_cx) { return e.r > 0 && e.r < r_cx; }
//Bool_t cx_s2overs1(TPCEvent const& e) { return e.nr_sigma_s2 < -0.1; }
Bool_t cx_s2overs1(TPCEvent const& e) { return e.s2overs1 < e.nr_s2overs1; }
Bool_t cx_f90_fast(TPCEvent const& e) { return e.total_f90 > 0.05; }  //2015-09-05 AFan: Changed from .15 to .05 for null field runs. wasn't really being used for field on analysis anyway

// Select core of TPC
Bool_t cx_core(TPCEvent const& e)     { return e.tdrift > CORE_TDRIFT_MIN && e.tdrift < CORE_TDRIFT_MAX && e.r >= 0 && e.r < CORE_R_MAX; }
Bool_t cx_core2(TPCEvent const& e)    { return e.tdrift > CORE2_TDRIFT_MIN && e.tdrift < CORE2_TDRIFT_MAX && e.r >= 0 && e.r < CORE2_R_MAX; }

// Use maximum TPC volume for good events. Outside this, weird reconstruction effects may appear.
Bool_t cx_full_volume(TPCEvent const& e) { return e.tdrift > FULL_VOL_TDRIFT_MIN && e.tdrift < FULL_VOL_TDRIFT_MAX && e.r > 0 && e.r < TPC_RMAX; }

// Cuts for Kr85m search
Bool_t cx_kr85m_1p(TPCEvent const& e)        { return (e.npulses >= 2 && e.pulse_start_time[1] - e.pulse_start_time[0] > 5.); }
Bool_t cx_kr85m_2p(TPCEvent const& e)        { return (e.npulses >= 3 && e.pulse_start_time[1] - e.pulse_start_time[0] <= 5. &&
                                                       e.pulse_start_time[2] - e.pulse_start_time[0] > 5.); }
Bool_t cx_kr85m_peaktime(TPCEvent const& e)  { return e.kr85mpeaktime > 0.05 && e.kr85mpeaktime < 5; }
Bool_t cx_kr85m_f5000(TPCEvent const& e)     { return e.p0f5000 > 0.90; }
Bool_t cx_kr85m_box(TPCEvent const& e)       { return e.npulses >= 2 && e.total_s1 > 400. && e.total_s1 < 10.E+3 && e.total_f90 < 0.2; }

Bool_t cx_f90_s2s1_s1range(TPCEvent const& e){ return e.total_s1_corr > 200 && e.total_s1_corr < 400; }

#endif