#include "ThreeParticleAnalyzer_New.C"

void ThreeParticleMacro_unlocked()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    int Centrality = 6;
    const double pi_ = 3.1415927;
    
    TCanvas *c1 = cf->CanvasDressing(1);
    TFile *fRead = new TFile("TriHadronCorr_NormFactorIssueResol.root");
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
    CalculateDifference(hDSig_sameEtaRegion, hDSig_crossEtaRegion, 1);
    TH2D *hDiffRealCorr = new TH2D("hDiffRealCorr", "#Delta#phi;#Delta#phi", 96,-pi_,pi_,96,-pi_,pi_);
    hDiffRealCorr = CalculateDifference(hSig_sameEtaRegion, hSig_crossEtaRegion, 1);
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
    TH2D *hDiffBkgTerm = CalculateDifference(hSig_combBkgTerm, hSig_combBkgTerm_cEtaRegion, 2);
    hDiffBkgTerm->Draw("zcol");
    c6->SaveAs("SameMinusCrossEtaRegion_combBkgTerm.pdf");
    
    TCanvas *c7 = cf->CanvasDressing(7);
    TH2D *hFinalSignal = CalculateDifference(hDiffRealCorr, hDiffBkgTerm, 3);
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
    TH2D *hDiffSigmaDelta = CalculateDifference(hSig_SD_sEtaRegion, hSig_SD_cEtaRegion, 4);
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
    TH2D *hDiffSigmaDeltaBkg = CalculateDifference(hDSigCombBkg_SD_sEtaRegion, hDSigCombBkg_SD_cEtaRegion, 5);
    hDiffSigmaDeltaBkg->Draw("zcol");
    
    TCanvas *c14 = cf->CanvasDressing(14);
    TH2D *hSignal = CalculateDifference(hDiffSigmaDelta, hDiffSigmaDeltaBkg, 6);
    hSignal->Draw("zcol");
    
    TCanvas *c15 = cf->CanvasDressing(15);
    float phimin = -0.30;
    float phimax = 0.30;
    
    TH1::SetDefaultSumw2();
    
    int phiBinMin = hSignal->GetYaxis()->FindBin(phimin+0.01);
    int phiBinMax = hSignal->GetYaxis()->FindBin(phimax+0.01);
    
    TString nameHisto = "_px";
    TH1D *px = (TH1D *)hSignal->ProjectionX(nameHisto, phiBinMin, phiBinMax, "e");
    px->Draw("E1");
   
    TFile *_file = new TFile("Signal.root","RECREATE");
    hSignal->Write();
    
    TF1 *gauss = new TF1("GausFunct", GausFunct, -2.0, 2.0, 3);
   // gauss->SetParameters( 0.06, 0, 1);
    gauss->SetParNames("constant", "mean", "sigma");
    px->Fit("GausFunct", "", "", -1.0, 1.0);
    cout<<px->GetBinContent(44)<<'\t'<<px->GetBinError(44)<<endl;
}






