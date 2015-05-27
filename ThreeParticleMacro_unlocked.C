#include "ThreeParticleAnalyzer_unlocked.C"

void ThreeParticleMacro_unlocked()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    TCanvas *c1 = cf->Canvas();
    TFile *fRead = new TFile("TriHadronCorr_BkgTerm.root");
    TH2D *hSig_sameEtaRegion = SameEtaRegion(fRead, 1);
    hSig_sameEtaRegion->SetTitle("");
    hSig_sameEtaRegion->GetYaxis()->SetTitle("#Delta#phi");
    hSig_sameEtaRegion->GetXaxis()->SetTitle("#Delta#phi");
    hSig_sameEtaRegion->GetXaxis()->SetLabelFont(42);
    hSig_sameEtaRegion->GetXaxis()->SetTitleSize(0.06);
    hSig_sameEtaRegion->GetXaxis()->SetTitleOffset(0.67);
    hSig_sameEtaRegion->GetYaxis()->SetLabelFont(42);
    hSig_sameEtaRegion->GetYaxis()->SetTitleSize(0.06);
    hSig_sameEtaRegion->GetYaxis()->SetTitleOffset(0.67);
    hSig_sameEtaRegion->Draw("zcol");
    c1->SaveAs("HistSameEtaRegion.pdf");
    
    TCanvas *c2 = cf->Canvas1();
    TH2D *hSig_crossEtaRegion = CrossEtaRegion(fRead, 1);
    hSig_crossEtaRegion->GetYaxis()->SetTitle("#Delta#phi");
    hSig_crossEtaRegion->GetXaxis()->SetTitle("#Delta#phi");
    hSig_crossEtaRegion->GetXaxis()->SetLabelFont(42);
    hSig_crossEtaRegion->GetXaxis()->SetTitleSize(0.06);
    hSig_crossEtaRegion->GetXaxis()->SetTitleOffset(0.67);
    hSig_crossEtaRegion->GetYaxis()->SetLabelFont(42);
    hSig_crossEtaRegion->GetYaxis()->SetTitleSize(0.06);
    hSig_crossEtaRegion->GetYaxis()->SetTitleOffset(0.67);
    hSig_crossEtaRegion->SetTitle("");
    hSig_crossEtaRegion->Draw("zcol");
    c2->SaveAs("HistCrossEtaRegion.pdf");
    
    TCanvas *c3 = cf->Canvas2();
    const double pi_ = 3.1415927;
    TH2D *hDifference = new TH2D("hDifference", "#Delta#phi;#Delta#phi", 96,-pi_/2+pi_/32,3*pi_/2-pi_/32,96,-pi_/2+pi_/32,3*pi_/2-pi_/32);
    
    for(int iBin = 1; iBin <=hSig_sameEtaRegion->GetNbinsX(); iBin++)
    {
        for(int jBin = 1; jBin <=hSig_crossEtaRegion->GetNbinsY(); jBin++)
        {
            int bin = hDifference->GetBin(iBin, jBin);
            double sameEta = hSig_sameEtaRegion->GetBinContent(iBin, jBin);
            double crossEta = hSig_crossEtaRegion->GetBinContent(iBin, jBin);
            double _difference = sameEta - crossEta;
            cout<<sameEta<<'\t'<<crossEta<<'\t'<<_difference<<endl;
            hDifference->SetBinContent(iBin, jBin, _difference);
        }
    }
    hDifference->GetYaxis()->SetTitle("#Delta#phi");
    hDifference->GetXaxis()->SetTitle("#Delta#phi");
    hDifference->GetXaxis()->SetLabelFont(42);
    hDifference->GetXaxis()->SetTitleSize(0.06);
    hDifference->GetXaxis()->SetTitleOffset(0.67);
    hDifference->GetYaxis()->SetLabelFont(42);
    hDifference->GetYaxis()->SetTitleSize(0.06);
    hDifference->GetYaxis()->SetTitleOffset(0.67);
    hDifference->SetTitle("");
    hDifference->Draw("zcol");
    c3->SaveAs("SameMinusCrossEtaRegion.pdf");
    
    TCanvas *c4 = cf->Canvas3();
    TH2D *hSig_combBkgTerm = CombinatorialBkgTerm(fRead, 1);
    hSig_combBkgTerm->GetYaxis()->SetTitle("#Delta#phi");
    hSig_combBkgTerm->GetXaxis()->SetTitle("#Delta#phi");
    hSig_combBkgTerm->GetXaxis()->SetLabelFont(42);
    hSig_combBkgTerm->GetXaxis()->SetTitleSize(0.06);
    hSig_combBkgTerm->GetXaxis()->SetTitleOffset(0.67);
    hSig_combBkgTerm->GetYaxis()->SetLabelFont(42);
    hSig_combBkgTerm->GetYaxis()->SetTitleSize(0.06);
    hSig_combBkgTerm->GetYaxis()->SetTitleOffset(0.67);
    hSig_combBkgTerm->Draw("zcol");
    hSig_combBkgTerm->SetTitle("");
    c4->SaveAs("SameEtaRegion_combBkgTerm.pdf");
    
    
    TCanvas *c5 = cf->Canvas4();
    TH2D *hSig_combBkgTerm_cEtaRegion = CombBkgTerm_crossEtaRegion(fRead, 1);
    hSig_combBkgTerm_cEtaRegion->GetYaxis()->SetTitle("#Delta#phi");
    hSig_combBkgTerm_cEtaRegion->GetXaxis()->SetTitle("#Delta#phi");
    hSig_combBkgTerm_cEtaRegion->GetXaxis()->SetLabelFont(42);
    hSig_combBkgTerm_cEtaRegion->GetXaxis()->SetTitleSize(0.06);
    hSig_combBkgTerm_cEtaRegion->GetXaxis()->SetTitleOffset(0.67);
    hSig_combBkgTerm_cEtaRegion->GetYaxis()->SetLabelFont(42);
    hSig_combBkgTerm_cEtaRegion->GetYaxis()->SetTitleSize(0.06);
    hSig_combBkgTerm_cEtaRegion->GetYaxis()->SetTitleOffset(0.67);
    hSig_combBkgTerm_cEtaRegion->Draw("zcol");
    hSig_combBkgTerm_cEtaRegion->SetTitle("");
    c5->SaveAs("CrossEtaRegion_combBkgTerm.pdf");
    
    TCanvas *c6 = cf->Canvas5();
    TH2D *hDiffBkgTerm = new TH2D("hDiffBkgTerm", "#Delta#phi;#Delta#phi", 96,-pi_/2+pi_/32,3*pi_/2-pi_/32,96,-pi_/2+pi_/32,3*pi_/2-pi_/32);
     
    for(int iBin = 1; iBin <=hSig_combBkgTerm->GetNbinsX(); iBin++)
    {
        for(int jBin = 1; jBin <=hSig_combBkgTerm_cEtaRegion->GetNbinsY(); jBin++)
            {
                int bin = hDiffBkgTerm->GetBin(iBin, jBin);
                double sameEtaBkgTerm = hSig_combBkgTerm->GetBinContent(iBin, jBin);
                double crossEtaBkgTerm = hSig_combBkgTerm_cEtaRegion->GetBinContent(iBin, jBin);
                double _difference = sameEtaBkgTerm - crossEtaBkgTerm;
                hDiffBkgTerm->SetBinContent(iBin, jBin, _difference);
            }
    }
     
    hDiffBkgTerm->GetYaxis()->SetTitle("#Delta#phi");
    hDiffBkgTerm->GetXaxis()->SetTitle("#Delta#phi");
    hDiffBkgTerm->GetXaxis()->SetLabelFont(42);
    hDiffBkgTerm->GetXaxis()->SetTitleSize(0.06);
    hDiffBkgTerm->GetXaxis()->SetTitleOffset(0.67);
    hDiffBkgTerm->GetYaxis()->SetLabelFont(42);
    hDiffBkgTerm->GetYaxis()->SetTitleSize(0.06);
    hDiffBkgTerm->GetYaxis()->SetTitleOffset(0.67);
    hDiffBkgTerm->Draw("zcol");
    hDiffBkgTerm->SetTitle("");
    c6->SaveAs("SameMinusCrossEtaRegion_combBkgTerm.pdf");


    ////////////////////////////////////////////////////////////////////////
    TCanvas *c7 = cf->Canvas6();
    TH2D *hFinalSignal = new TH2D("hFinalSignal", "#Delta#phi;#Delta#phi", 96,-pi_/2+pi_/32,3*pi_/2-pi_/32,96,-pi_/2+pi_/32,3*pi_/2-pi_/32);
    
    for(int iBin = 1; iBin <=hDifference->GetNbinsX(); iBin++)
    {
        for(int jBin = 1; jBin <=hDiffBkgTerm->GetNbinsY(); jBin++)
        {
            int bin = hFinalSignal->GetBin(iBin, jBin);
            double RealCorrEtaDiff = hDifference->GetBinContent(iBin, jBin);
            double combBkgTermDiff = hDiffBkgTerm->GetBinContent(iBin, jBin);
            double _difference = RealCorrEtaDiff - combBkgTermDiff;
            hFinalSignal->SetBinContent(iBin, jBin, _difference);
        }
    }
    
    hFinalSignal->GetYaxis()->SetTitle("#Delta#phi");
    hFinalSignal->GetXaxis()->SetTitle("#Delta#phi");
    hFinalSignal->GetXaxis()->SetLabelFont(42);
    hFinalSignal->GetXaxis()->SetTitleSize(0.06);
    hFinalSignal->GetXaxis()->SetTitleOffset(0.67);
    hFinalSignal->GetYaxis()->SetLabelFont(42);
    hFinalSignal->GetYaxis()->SetTitleSize(0.06);
    hFinalSignal->GetYaxis()->SetTitleOffset(0.67);
    hFinalSignal->Draw("zcol");
    hFinalSignal->SetTitle("");
    c7->SaveAs("SignalMinusCombBkgTerm.pdf");
    
   /* TFile *fNew = new TFile("TriHadronAnalyzerOutput_PbPb.root", "RECREATE");
    hFactors->Write();
    fNew->Close();*/
    
}






