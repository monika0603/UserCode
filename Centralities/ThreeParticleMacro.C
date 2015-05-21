#include "ThreeParticleAnalyzer.C"

void ThreeParticleMacro()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    cf->Canvas();
    TFile *fRead = new TFile("TriHadronCorr_BkgTerm.root");
    TH2D *hSig_sameEtaRegion = SameEtaRegion(fRead, 2);
    hSig_sameEtaRegion->Draw("zcol");
    
    cf->Canvas1();
    TH2D *hSig_crossEtaRegion = CrossEtaRegion(fRead, 2);
    hSig_crossEtaRegion->Draw("zcol");
    
    cf->Canvas2();
    TH2D *hDifference = (TH2D*)hSig_crossEtaRegion->Clone("hist1 - hist2");
    
    for(int iBin = 1; iBin <=hSig_sameEtaRegion->GetNbinsX(); iBin++)
    {
        for(int jBin = 1; jBin <=hSig_crossEtaRegion->GetNbinsY(); jBin++)
        {
            int bin = hDifference->GetBin(iBin, jBin);
            double sameEta = hSig_sameEtaRegion->GetBinContent(iBin, jBin);
            double crossEta = hSig_crossEtaRegion->GetBinContent(iBin, jBin);
            double _difference = sameEta - crossEta;
            hDifference->SetBinContent(iBin, jBin, _difference);
        }
    }
    
    hDifference->Draw("zcol");
    
    cf->Canvas3();
    TH2D *hSig_combBkgTerm = CombinatorialBkgTerm(fRead, 2);
    hSig_combBkgTerm->Draw("zcol");
    
    
    cf->Canvas4();
    TH2D *hSig_combBkgTerm_cEtaRegion = CombBkgTerm_crossEtaRegion(fRead, 2);
    hSig_combBkgTerm_cEtaRegion->Draw("zcol");
    
     cf->Canvas5();
     TH2D *hDiffBkgTerm = (TH2D*)hSig_combBkgTerm_cEtaRegion->Clone("bkg1 - bkg2");
     
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
     
     hDiffBkgTerm->Draw("zcol");
    
    ////////////////////////////////////////////////////////////////////////
    cf->Canvas6();
    TH2D *hFinalSignal = (TH2D*)hDifference->Clone("hist - bkg");
    
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
    
    hFinalSignal->Draw("zcol");
    
   /* TFile *fNew = new TFile("TriHadronAnalyzerOutput_PbPb.root", "RECREATE");
    hFactors->Write();
    fNew->Close();*/
    
}






