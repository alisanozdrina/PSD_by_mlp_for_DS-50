#!/bin/bash

set -e

DataValidationNR_Flag=$1
DataValidationER_Flag=$2
UAr_MLP_run_Flag=$3
Python_flag=$4
DataValidationScript=$5
NR_input_file=$6
ER_input_file=$7
Kr_input_file=$8
UAr_input_file=$9
output_dir=${10}
Python_script_MLP=${11}
loadROOTscript=${12}
vetoMLP=${13}
nEventsMLP=${14}
AnalysisFlag=${15}
veto=${16}
train_flag=${17}
nEvents=${18}
MLPFlag="mlp"

echo loading ROOT
source "$loadROOTscript"

mkdir -p "$output_dir"

if [ "$DataValidationNR_Flag" = 1 ]; then
    echo Starting data validation script for AmBe data
    AnalysisFlag="ambe"
    veto=true
    nEvents=-1
    root -l -b -q "$DataValidationScript(\"$NR_input_file\", \"$AnalysisFlag\", $veto, $nEvents, \"$output_dir\")"
fi

if [ "$DataValidationER_Flag" = 1 ]; then
    echo Starting data validation script for AAr data
    AnalysisFlag="aar"
    veto=false
    nEvents=400000
    root -l -b -q "$DataValidationScript(\"$ER_input_file\", \"$AnalysisFlag\", $veto, $nEvents, \"$output_dir\")"
fi

if [ "$DataValidationER_Flag" = 1 ]; then
    echo Starting data validation script for Kr data
    AnalysisFlag="kr"
    veto=false
    nEvents=-1
    root -l -b -q "$DataValidationScript(\"$Kr_input_file\", \"$AnalysisFlag\", $veto, $nEvents, \"$output_dir\")"
fi

if [ "$UAr_MLP_run_Flag" = 1 ]; then
    echo Starting data validation script for UAr data
    echo Creating txt file with S1 for UAr data
    AnalysisFlag="uar"
    root -l -b -q "$DataValidationScript(\"$UAr_input_file\", \"$AnalysisFlag\", $vetoMLP, $nEventsMLP, \"$output_dir\")"
fi

if [ "$Python_flag" = 1 ]; then
    echo Starting python script for MLP Classification
    if [ -e mlp_DS50.pkl ]; then
        train_flag=0
        python "$Python_script_MLP" "$output_dir"/s1_signal_NR.txt "$output_dir"/s1_signal_ER.txt "$output_dir"/s1_signal_Kr.txt "$output_dir"/s1_signal_UAR.txt "$output_dir" $train_flag
    else
        train_flag=1
        python "$Python_script_MLP" "$output_dir"/s1_signal_NR.txt "$output_dir"/s1_signal_ER.txt "$output_dir"/s1_signal_Kr.txt "$output_dir"/s1_signal_UAR.txt "$output_dir" $train_flag
    fi
fi

echo Applying mlp_DS50 results to UAr data. See MLP folder in а mlp_output.root file

root -l -b -q "$DataValidationScript(\"$UAr_input_file\", \"$MLPFlag\", $vetoMLP, $nEventsMLP, \"$output_dir\")"
