#include "CorrectionFactors_MinBias_PbPb.C"

void CorrectionFactorsMacro()
{
    
    CorrectionFactors_MinBias_PbPb *cf = new CorrectionFactors_MinBias_PbPb();
    
    cf->Canvas();
    TFile *fRead = new TFile("TriHadronFirstAttempt_FullStat_Centralities.root");
    TH1F *hdNdEta = Default(fRead);
    hdNdEta->Draw();
    
    TH1F *hUnSymmetrized = (TH1F *)hdNdEta->Clone();
    TH1F *hSymmetrized = Symmetrize(hUnSymmetrized);
    hSymmetrized->SetLineColor(kRed);
    hSymmetrized->Draw("same");
    
    TH1F *hdNdEta_0 = odNdEta(fRead);
    hdNdEta_0->SetLineColor(kGreen+4);
    hdNdEta_0->Draw("same");
    
    cf->Canvas1();
    TH2F *hFactors = AlldNdEta(fRead, hSymmetrized);
    hFactors->Draw("zcol");
    
}






