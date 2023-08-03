#include <vector>
#include <string>
#include <vector>
#include <string>
#include <iostream> // for std::cout
#include "TFile.h"
#include "TEfficiency.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TColor.h"


{
    gROOT->LoadMacro("plotHist.C+"); // Load the macro containing plotHistograms function
    
    plotHist( 
        //paths and filenames
        {//"~/alice/actsdir/test-ckf/output/n10/subruns/step1/merged_performance_ckf_DEFAULT_ckf_ONLY.root",
        //"~/alice/actsdir/test-ckf/output/n10/-44/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/n10/subruns/step,1/merged_performance_ckf_ONLY_default_n10e-44.root", 
        //"~/alice/actsdir/test-ckf/output/n10/subruns/step,1/merged_performance_ckf_ONLY_default_n10e-44.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Optuna_output_CKF/merged_performance_ckf_n10t500e-44_FR_newP8.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Optuna_output_CKF/merged_performance_ckf_n10t500e-44_AR_newP8.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Orion_output_CKF/merged_performance_ckf_n10t500e-44_FR_newP8.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Orion_output_CKF/merged_performance_ckf_FR_rerunckf_optimparams_fatras-44.root",
        //"~/alice/actsdir/test-ckf/output/e01seed_fatras/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/e01seed_e-44fatras/performance_ckf.root",
        //"/Users/achalume/alice/actsdir/test-ckf/output/test-fatras/fatras-subranges/merged_performance_ckf_default_n10e-44_fatras-subranges.root",
        //"/Users/achalume/alice/actsdir/test-ckf/output/test-fatras/fatras-44/merged_performance_ckf_default_n10e-44_fatras-44.root",
        //"~/alice/actsdir/test-ckf/output/test-fatras/fatras-44/e3_4seed_e-44fatras/performance_ckf.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Optuna_output_CKF/Optuna_output_CKF_3_4_n10t100e34_AR_fatras-44/performance_ckf.root",
        //"~/alice/actsdir/source/Examples/Scripts/Optimization/Optuna_output_CKF/Optuna_output_CKF_3_4_n10t100e34_FR_fatras-44/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/particle-gun/pMin500/z1300/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/particle-gun/pMin500/z2000/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/particle-gun/pMin100/z1300/performance_ckf.root",
        //"~/alice/actsdir/test-ckf/output/particle-gun/pMin100/z2000/performance_ckf.root",
        "/Users/achalume/alice/actsdir/acts/bin/output/python/ckf_gun_13_Bfield2_npart10_nEvents5000_noseedconf_nobin_ambi_infl100_paramsckfv13_cfg10_pTmin100_z1300/performance_ckf.root",
        //"/Users/achalume/alice/actsdir/acts/bin/output/python/ckf_gun_13_Bfield2_npart10_nEvents5000_noseedconf_nobin_ambi_infl100_paramsckfv13_cfg10_pTmin100_z2000/performance_ckf.root",
        "/Users/achalume/alice/actsdir/acts/bin/output/python/ckf_gun_13_Bfield2_npart10_nEvents5000_noseedconf_nobin_ambi_infl100_paramsckfv13_cfg10_pTmin500_z1300/performance_ckf.root",
        //"/Users/achalume/alice/actsdir/acts/bin/output/python/ckf_gun_13_Bfield2_npart10_nEvents5000_noseedconf_nobin_ambi_infl100_paramsckfv13_cfg10_pTmin500_z2000/performance_ckf.root",        
        }, 

        //treeBranches (trackeff_vs_eta ; duplicationRate_vs_eta ; trackeff_vs_pT )
        {"trackeff_vs_pT",
        "trackeff_vs_pT",
        //"trackeff_vs_eta",
        //"trackeff_vs_eta",
        //"duplicationRate_vs_eta",
        //"trackeff_vs_eta",
        //"trackeff_vs_eta",
        }, 

        //labels (corresponding to the different files)
        {//"CKF default on subranges",
        //"CKF default params",
        //Optuna AR",
        //Optuna FR",
        //"ptMin = 500MeV, |z| = 1300mm, ckf only",
        //"ptMin = 500MeV, |z| = 2000mm, ckf only",
        //"ptMin = 100MeV, |z| = 1300mm, ckf only",
        //"ptMin = 100MeV, |z| = 2000mm, ckf only",
        "ptMin = 100MeV, |z| = 1300mm, full chain",
        //"ptMin = 100MeV, |z| = 2000mm, full chain",
        "ptMin = 500MeV, |z| = 1300mm, full chain",
        //"ptMin = 500MeV, |z| = 2000mm, full chain",
        }
        //main title
        //"Efficiency vs eta"
    );


    // Add more calls to plotHistograms with different arguments as needed
}
