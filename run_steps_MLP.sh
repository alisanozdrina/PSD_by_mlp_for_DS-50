#!/bin/bash

set -e

# HOW TO RUN RANDOM FOREST CLASSIFIER
# 1) Make sure you have following python packages installed: numpy, scikit-learn, pandas
# 2) Run the script in the terminal: bash run_steps_MLP.sh 1 1 1 1  
# first argument - NR_Flag, second - ER Flag, third - UAr Flag, forth - python script flag 
# NR_Flag = 1 if you want to create a txt file with NR data to train classifier
# ER_Flag = 1 if you want to create a txt file with ER data to train classifier
# UAr_Flag = 1 if you want to create a txt file with UAr data ready for classification
# Python_flag = 1 if you want to start the classification
# 
# For the first time you should run it as - "bash run_steps_MLP.sh 1 1 1 1", 
# but after NR and ER files are ready, you don't need to create them everytime, 
# so you can run as "bash run_steps_MLP.sh 0 0 1 1" if you change cuts for UAr, or number of events or veto or something else, and therefore need a new UAr (or any other) txt file 
# or "bash run_steps_MLP.sh 0 0 0 1" if you have NR, ER, UAr files ready and you want to change python script or whatever
# MAKE SURE you create appropriate txt file after you did some changes in the code!
#
# NOTICE make sure that you have rootstart.h, dmbox.root and max_frac_cut_fixed_acceptance_full_stats.root files in the same folder as Analysis.C file.
# 
# NOTICE when you used Python_flag = 1 for the first time it will create random_forest_DS50.pkl file in your folder.
# This is your trained classifier ready for deployment, so you don't need to train it everytime you analize data
# But if you want to retrain your classifier on new dataset you should delete this file beforehand.

# Specify the path to the files below


NR_Flag=$1 
ER_Flag=$2
UAr_Flag=$3
Python_flag=$4
ROOTsource="/opt/root_v5.34.25/bin/thisroot.sh" #path to your ROOT source

AnalysisScript="/home/nozdrina/DS50_analisys/machine_learning_lib/mlp_ds50_files/Analysis.C+"
NR_input_file="/home/nozdrina/DS50_analisys/amb_160/AmBe_160nps_SLAD_v3_3_0_merged.root"
ER_input_file="/home/nozdrina/DS50_analisys/AAr_50d/AAr_50d_SLAD_v3_1_1_merged_p0.root"
UAr_input_file="/home/nozdrina/DS50_analisys/UAr_70d_SLAD_v3_3_0_no12922.root"
Kr_input_file="/home/nozdrina/DS50_analisys/validation_code/data_validation/Run020704/Run020704.root"
#UAr_input_file="/home/nozdrina/DS50_analisys/validation_code/data_validation/AmC/AmC_SLAD_v3_0_0_merged.root"
output_dir="/home/nozdrina/DS50_analisys/machine_learning_lib/mlp_ds50_files/data_for_mlp/"
Python_script_MLP="/home/nozdrina/DS50_analisys/machine_learning_lib/mlp_ds50_files/MLP_Darkside50.py"

vetoMLP=false #if you don't want to use veto for UAr in the classification leave it "false"
nEventsMLP=800000 #number of events in the UAr file you want to analyze. NOTICE more events means heavier txt file

bash run.sh "$NR_Flag" "$ER_Flag" "$UAr_Flag" "$Python_flag" "$AnalysisScript" "$NR_input_file" "$ER_input_file" "$Kr_input_file" "$UAr_input_file" "$output_dir" "$Python_script_MLP" "$ROOTsource" "$vetoMLP" "$nEventsMLP" 
