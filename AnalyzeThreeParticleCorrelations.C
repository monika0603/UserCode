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
    
    
    tt.Canvas4();
    TH1F *hdNdEta = Default(fRead);
    hdNdEta->Draw();
    
    TH1F *hUnSymmetrized = (TH1F *)hdNdEta->Clone();
    TH1F *hSymmetrized = Symmetrize(hUnSymmetrized);
    hSymmetrized->SetLineColor(kRed);
    hSymmetrized->Draw("same");
    
    tt.Canvas5();
    TH2F *hFactors = AlldNdEta(fRead, hSymmetrized);
    hFactors->Draw("zcol");
    
}

TH1F *Default(TFile *fRead)
{
    TH1::SetDefaultSumw2();
    
    const float binWidth = 0.06;
    
    TString _baseHistoName = "TriHadronAnalysisMult190/hdNdEta_VzBin_7";
    TH1F *hdNdEta_default  = (TH1F*)fRead->Get(_baseHistoName);
    
    TString _baseEventHisto = "TriHadronAnalysisMult190/nEventsVzBin_7";
    TH1F *hEvents = (TH1F *)fRead->Get(_baseEventHisto);
    double nEvents_ = hEvents->GetEntries();
    
    hdNdEta_default->Scale(1.0/nEvents_/binWidth);
    
    return hdNdEta_default;
    
}

TH1F *Symmetrize(TH1F *h)
{
    int nBins_ = h->GetNbinsX();
    TH1F * htemp = (TH1F *)h->Clone();
    for(int iBin_=1; iBin_<=nBins_/2; iBin_++)
    {
        double symmetric = (h->GetBinContent(iBin_)+h->GetBinContent(nBins_- iBin_+1))/2.0;
        htemp->SetBinContent(iBin_,symmetric);
        htemp->SetBinContent(nBins_ - iBin_ + 1,symmetric);
    }
    
    return htemp;
}

TH2F *AlldNdEta(TFile *fRead, TH1F *hSymmetrized)
{
    const float binWidth = 0.06;
    const int nBins = 1;
    const int nEtaBins = 51;
    const double vZMin = -15.0;
    const double vZMax = 15.0;
    const int nVz = 15;
    
    TH2F *hVzEtaEff = new TH2F("hVzEtaEff_cent","hVzEtaEff;eta;vz", nEtaBins, -3.0, 3.0, nVz, vZMin, vZMax);
    TH1F *hdNdEtaVzBin[15];
    
    for(int iBin_=0; iBin_<=nBins; iBin_++)
    {
        char nEventsVzBin[400];
        sprintf(nEventsVzBin,"TriHadronAnalysisMult190/nEventsVzBin_%d",iBin_);
        TH1F * hEventsVzBin = (TH1F *)fRead->Get(nEventsVzBin);
        double nEvents = hEventsVzBin->GetEntries();
        
        char ndNdEtaVzBin[400];
        sprintf(ndNdEtaVzBin,"TriHadronAnalysisMult190/hdNdEta_VzBin_%d",iBin_);
        hdNdEtaVzBin[iBin_] = (TH1F*)fRead->Get(ndNdEtaVzBin);
        if(iBin_!=7)		hdNdEtaVzBin[iBin_]->Scale(1.0/nEvents/binWidth);
        
        for(int iEta_=0; iEta_<=nEtaBins; iEta_++)
        {
         
            double numerator = hdNdEtaVzBin[iBin_]->GetBinContent(iEta_+1);
            double denominator = hSymmetrized->GetBinContent(iEta_+1);
            if(denominator > 0) double ratio = numerator/denominator;
            
            cout<<iEta_<<'\t'<<hSymmetrized->GetBinContent(iEta_+1)<<'\t'<<hdNdEtaVzBin[iBin_]->GetBinContent(iEta_+1)<<'\t'<<ratio<<endl;
            if(hSymmetrized->GetBinContent(iEta_+1) > 0.0) hVzEtaEff->SetBinContent(iEta_+1,iBin_+1,ratio);
        }

        
    }
    
    return hVzEtaEff;
}



