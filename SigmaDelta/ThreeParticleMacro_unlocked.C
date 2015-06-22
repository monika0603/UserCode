#include "ThreeParticleAnalyzer_New.C"

void ThreeParticleMacro_unlocked()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    int Centrality = 0;
    
    TCanvas *c1 = cf->CanvasDressing(1);
    TFile *fRead = new TFile("TriHadronCorrSigmaDeltaFullStat.root");
    TH2D *hSig_sameEtaRegion = SameEtaRegion(fRead, Centrality);
    TH2D *hDSig_sameEtaRegion = histoDressing(hSig_sameEtaRegion);
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

    ////////////////////////////////////////////////////////////////////////
    TCanvas *c7 = cf->CanvasDressing(7);
    TH2D *hFinalSignal = CalculateDifference(hDiffRealCorr, hDiffBkgTerm);
    hFinalSignal->Draw("zcol");
    c7->SaveAs("SignalMinusCombBkgTerm.pdf");
    
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
}






