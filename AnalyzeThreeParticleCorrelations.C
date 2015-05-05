#include "TriHadronLocalAnalyzer.C"

void AnalyzeThreeParticleCorrelations()
{
    
    TriHadronLocalAnalyzer tt;
    tt.Canvas();
    
    TFile *fRead;
    
    TString _Signal_sEtaRegion, _Signal_fEtaRegion;
    TString _Background_sEtaRegion, _Background_fEtaRegion;
    TString _Events;
    
    double pi_ = 3.1415927;
    
    TH2D *hSignal_sEtaRegion;
    TH2D *hBackground_sEtaRegion;
    TH2D *hSignal_fEtaRegion;
    TH2D *hBackground_fEtaRegion;
  //  TH2D *hDifference = new TH2D("hDifference", "#Delta#phi;#Delta#phi", 96,-pi_/2+pi_/32,3*pi_/2-pi_/32,96,-pi_/2+pi_/32,3*pi_/2-pi_/32);
    
    TH1F *hEvents;
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
    TH1::SetDefaultSumw2();
    
    fRead = new TFile("TriHadronFirstAttempt_FullStat.root");
    
    _Signal_sEtaRegion = "TriHadronAnalysisMult190/hSignal1";
    _Background_sEtaRegion = "TriHadronAnalysisMult190/hBackground1";
    _Events = "TriHadronAnalysisMult190/evtHPNtrk";
    
    hSignal_sEtaRegion = (TH2D*)fRead->Get(_Signal_sEtaRegion);
    hBackground_sEtaRegion = (TH2D*)fRead->Get(_Background_sEtaRegion);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_sEtaRegion->GetXaxis()->GetBinWidth(1);
    
    hSignal_sEtaRegion->Divide(hBackground_sEtaRegion);
    _x0 = hBackground_sEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_sEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_sEtaRegion->GetBinContent(_x0,_y0);
    hSignal_sEtaRegion->Scale(_B0/(_nEvents));
    hSignal_sEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    hSignal_sEtaRegion->Draw("zcol");
    
    tt.Canvas1();
    
    _Signal_fEtaRegion = "TriHadronAnalysisMult190/hSignal_af0_as1";
    _Background_fEtaRegion = "TriHadronAnalysisMult190/hBackground_af0_as1";
    
    hSignal_fEtaRegion = (TH2D*)fRead->Get(_Signal_fEtaRegion);
    hBackground_fEtaRegion = (TH2D*)fRead->Get(_Background_fEtaRegion);
    
    hSignal_fEtaRegion->Divide(hBackground_fEtaRegion);
    _x0 = hBackground_fEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_fEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_fEtaRegion->GetBinContent(_x0,_y0);
    hSignal_fEtaRegion->Scale(_B0/(_nEvents));
    hSignal_fEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    hSignal_fEtaRegion->Draw("zcol");
    
    tt.Canvas2();
    
    TH2D *hDifference = (TH2D*)hSignal_fEtaRegion->Clone("hist1 - hist2");
    
    for(int iBin = 1; iBin <=hSignal_sEtaRegion->GetNbinsX(); iBin++)
    {
       for(int jBin = 1; jBin <=hSignal_sEtaRegion->GetNbinsY(); jBin++)
        {
            int bin = hDifference->GetBin(iBin, jBin);
            double sameEta = hSignal_sEtaRegion->GetBinContent(iBin, jBin);
            double diffEta = hSignal_fEtaRegion->GetBinContent(iBin, jBin);
            double _difference = sameEta - diffEta;
            
            hDifference->SetBinContent(iBin, jBin, _difference);
        }
    }
    
    hDifference->Draw("zcol");
    
    tt.Canvas3();
    
    TH1D *hDeltaPhiProj = (TH1D*) hDifference->ProjectionY("hDeltaPhiProj",0,96,"e");
    hDeltaPhiProj->Draw();
    
    
}
