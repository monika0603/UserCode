#include "ThreeParticleAnalyzer_New.C"

void ThreeParticleMacro_unlocked()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    int Centrality = 2;
    
    TCanvas *c1 = cf->CanvasDressing(1);
    TFile *fRead = new TFile("TriHadronCorr_NormFactorIssueResol.root");
    TH2D *hSig_sameEtaRegion = SameEtaRegion(fRead, Centrality);
    cout<<"What is the problem... (I)"<<endl;
    TH2D *hDSig_sameEtaRegion = histoDressing(hSig_sameEtaRegion);
    cout<<"What is the problem... (II)"<<endl;
    hDSig_sameEtaRegion->Draw("zcol");
    c1->SaveAs("HistSameEtaRegion.pdf");
    
    TCanvas *c2 = cf->CanvasDressing(2);
    TH2D *hSig_crossEtaRegion = CrossEtaRegion(fRead, Centrality);
    TH2D *hDSig_crossEtaRegion = histoDressing(hSig_crossEtaRegion);
    hDSig_crossEtaRegion->Draw("zcol");
    c2->SaveAs("HistCrossEtaRegion.pdf");
    
    TCanvas *c3 = cf->CanvasDressing(3);
    TH2D *hDiffRealCorr = CalculateDifference(hSig_sameEtaRegion, hSig_crossEtaRegion);
    hDiffRealCorr->Draw("zcol");
    c3->SaveAs("SameMinusCrossEtaRegion.pdf");
    
    TCanvas *c4 = cf->CanvasDressing(4);
    TH2D *hSig_combBkgTerm = CombinatorialBkgTerm(fRead, Centrality);
    TH2D *hDSig_combBkgTerm = histoDressing(hSig_combBkgTerm);
    hDSig_combBkgTerm->Draw("zcol");
    c4->SaveAs("SameEtaRegion_combBkgTerm.pdf");
    
    TCanvas *c5 = cf->CanvasDressing(5);
    TH2D *hSig_combBkgTerm_cEtaRegion = CombBkgTerm_crossEtaRegion(fRead, Centrality);
    TH2D *hDSig_combBkgTerm_cEtaRegion = histoDressing(hSig_combBkgTerm_cEtaRegion);
    hDSig_combBkgTerm_cEtaRegion->Draw("zcol");
    c5->SaveAs("CrossEtaRegion_combBkgTerm.pdf");

    TCanvas *c6 = cf->CanvasDressing(6);
    TH2D *hDiffBkgTerm = CalculateDifference(hSig_combBkgTerm, hSig_combBkgTerm_cEtaRegion);
    hDiffBkgTerm->Draw("zcol");
    c6->SaveAs("SameMinusCrossEtaRegion_combBkgTerm.pdf");

    TCanvas *c7 = cf->CanvasDressing(7);
    TH2D *hFinalSignal = CalculateDifference(hDiffRealCorr, hDiffBkgTerm);
    hFinalSignal->Draw("zcol");
    c7->SaveAs("SignalMinusCombBkgTerm.pdf");
    
    //////////////////////////////////////////////////////////
    TCanvas *c8 = cf->CanvasDressing(8);
    TH2D *hSig_SD_sEtaRegion = SD_sameEtaRegion(fRead, Centrality);
    TH2D *hDSig_SD_sEtaRegion = histoDressing(hSig_SD_sEtaRegion);
    hDSig_SD_sEtaRegion->Draw("zcol");
    c8->SaveAs("SDSameEtaRegion.pdf");
    
    TCanvas *c9 = cf->CanvasDressing(9);
    TH2D *hSig_SD_cEtaRegion = SD_crossEtaRegion(fRead, Centrality);
    TH2D *hDSig_SD_cEtaRegion = histoDressing(hSig_SD_cEtaRegion);
    hDSig_SD_cEtaRegion->Draw("zcol");
    c9->SaveAs("SDCrossEtaRegion.pdf");
    
    TCanvas *c10 = cf->CanvasDressing(10);
    TH2D *hDiffSigmaDelta = CalculateDifference(hSig_SD_sEtaRegion, hSig_SD_cEtaRegion);
    hDiffSigmaDelta->Draw("zcol");
    
    TCanvas *c11 = cf->CanvasDressing(11);
    TH2D *hSigCombBkg_SD_sEtaRegion = SD_combBkg_sameEtaRegion(fRead, Centrality);
    TH2D *hDSigCombBkg_SD_sEtaRegion = histoDressing(hSigCombBkg_SD_sEtaRegion);
    hDSigCombBkg_SD_sEtaRegion->Draw("zcol");
    c8->SaveAs("SDcombBkgSameEtaRegion.pdf");
    
    TCanvas *c12 = cf->CanvasDressing(12);
    TH2D *hSigCombBkg_SD_cEtaRegion = SD_combBkg_crossEtaRegion(fRead, Centrality);
    TH2D *hDSigCombBkg_SD_cEtaRegion = histoDressing(hSigCombBkg_SD_cEtaRegion);
    hDSigCombBkg_SD_cEtaRegion->Draw("zcol");
    c8->SaveAs("SDcombBkgCrossEtaRegion.pdf");
    
    TCanvas *c13 = cf->CanvasDressing(13);
    TH2D *hDiffSigmaDeltaBkg = CalculateDifference(hDSigCombBkg_SD_sEtaRegion, hDSigCombBkg_SD_cEtaRegion);
    hDiffSigmaDeltaBkg->Draw("zcol");
    
    TCanvas *c14 = cf->CanvasDressing(14);
    TH2D *hSignal = CalculateDifference(hDiffSigmaDelta, hDiffSigmaDeltaBkg);
    hSignal->Draw("zcol");
}






