
#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TStyle.h>
using namespace std;

class ThreeParticleAnalyzer
{
  public:
    ThreeParticleAnalyzer();
    ThreeParticleAnalyzer(std::string fileName);
    TH2D *SameEtaRegion(TFile *fRead, const int cent);
    TH2D *CrossEtaRegion(TFile *fRead, const int cent);
    TH2D *CombinatorialBkgTerm(TFile *fRead, const int cent);
    TH2D *CombBkgTerm_crossEtaRegion(TFile *fRead, const int cent);
    TH2D *DivideAndScale(TH2D *hSignal, TH2D *hBackground, TH1F *hEvents);
    void WindowDressing();
    TCanvas *Canvas();
    TCanvas *Canvas1();
    TCanvas *Canvas2();
    TCanvas *Canvas3();
    TCanvas *Canvas4();
    TCanvas *Canvas5();
    TCanvas *Canvas6();
    virtual ~ThreeParticleAnalyzer();
    
  private:
    TFile *fRead;
};

ThreeParticleAnalyzer::ThreeParticleAnalyzer( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
}

ThreeParticleAnalyzer::ThreeParticleAnalyzer()
{
    fRead = new TFile("TriHadronCorr_NoEffCorr_FullStat.root");
    fRead->ls();
    
    if(fRead) cout<<"Successfully opned the input file."<<endl;
}

ThreeParticleAnalyzer::~ThreeParticleAnalyzer()
{
    delete fRead;
}

TH2D *DivideAndScale(TH2D *hSignal, TH2D *hBackground, TH1F *hEvents)
{
    TH1::SetDefaultSumw2();
    double _nEvents;
    double  _phibinwidth;
    int _x0, _y0, _B0;
    
    _nEvents = hEvents->Integral();
    _phibinwidth = hSignal->GetXaxis()->GetBinWidth(1);
    
    hSignal->Divide(hBackground);
    _x0 = hBackground->GetXaxis()->FindBin(0.0);
    _y0 = hBackground->GetYaxis()->FindBin(0.0);
    _B0 = hBackground->GetBinContent(_x0,_y0);
    hSignal->Scale(_B0/(_nEvents));
    hSignal->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal;
}

TH2D *SameEtaRegion(TFile *fRead, const int cent)
{
    TString _Signal_sEtaRegion;
    TString _Background_sEtaRegion;
    TString _Events;
    
    double pi_ = 3.1415927;
    
    TH2D *hSignal_sEtaRegion;
    TH2D *hBackground_sEtaRegion;
    TH1F *hEvents;
    
    
    
    TString _centrality[9] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "MinBias"};
    TString _signal = "/hSignal0";
    TString _background = "/hBackground0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_sEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_sEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    cout<<"[Same eta region] = "<<_Signal_sEtaRegion<<'\t'<<_Background_sEtaRegion<<'\t'<<_Events<<endl;

    TH1::SetDefaultSumw2();
    
    hSignal_sEtaRegion = (TH2D*)fRead->Get(_Signal_sEtaRegion);
    hBackground_sEtaRegion = (TH2D*)fRead->Get(_Background_sEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    
    TH2D *hSig_sameEtaRegion = DivideAndScale(hSignal_sEtaRegion, hBackground_sEtaRegion, hEvents);
    
    return hSig_sameEtaRegion;
    
}

TH2D *CrossEtaRegion(TFile *fRead, const int cent)
{
    TString _Signal_cEtaRegion;
    TString _Background_cEtaRegion;
    TString _Events;
    
    double pi_ = 3.1415927;
    
    TH2D *hSignal_cEtaRegion;
    TH2D *hBackground_cEtaRegion;
    TH1F *hEvents;
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
    TH1::SetDefaultSumw2();
    
    TString _centrality[9] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "MinBias"};
    TString _signal = "/hSignal_af0_as1";
    TString _background = "/hBackground_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_cEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_cEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    cout<<"[Cross eta region] = "<<_Signal_cEtaRegion<<'\t'<<_Background_cEtaRegion<<'\t'<<_Events<<endl;

    hSignal_cEtaRegion = (TH2D*)fRead->Get(_Signal_cEtaRegion);
    hBackground_cEtaRegion = (TH2D*)fRead->Get(_Background_cEtaRegion);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_cEtaRegion->GetXaxis()->GetBinWidth(1);
    
    hSignal_cEtaRegion->Divide(hBackground_cEtaRegion);
    _x0 = hBackground_cEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_cEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_cEtaRegion->GetBinContent(_x0,_y0);
    hSignal_cEtaRegion->Scale(_B0/(_nEvents));
    hSignal_cEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal_cEtaRegion;
    
}

TH2D *CombinatorialBkgTerm(TFile *fRead, const int cent)
{
    TString _Signal_combBkg0;
    TString _Background_combBkg0;
    TString _Events;
    
    double pi_ = 3.1415927;
    
    TH2D *hSignal_combBkg0;
    TH2D *hBackground_combBkg0;
    TH1F *hEvents;
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
    TH1::SetDefaultSumw2();
    
    TString _centrality[9] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "MinBias"};
    TString _signal = "/hSignal_combBkg0";
    TString _background = "/hBackground0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_combBkg0 = _dirName + _centrality[cent] + _signal;
    _Background_combBkg0 = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    cout<<"[Combinatorial same eta region] = "<<_Signal_combBkg0<<'\t'<<_Background_combBkg0<<'\t'<<_Events<<endl;

    hSignal_combBkg0 = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0 = (TH2D*)fRead->Get(_Background_combBkg0);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_combBkg0->GetXaxis()->GetBinWidth(1);
    
    hSignal_combBkg0->Divide(hBackground_combBkg0);
    _x0 = hBackground_combBkg0->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_combBkg0->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_combBkg0->GetBinContent(_x0,_y0);
   // hSignal_combBkg0->Scale(_B0/(_nEvents*_nEvents));
    hSignal_combBkg0->Scale(_B0/(_nEvents*_nEvents/2.));
    hSignal_combBkg0->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal_combBkg0;
    
}

TH2D *CombBkgTerm_crossEtaRegion(TFile *fRead, const int cent)
{
    TString _Signal_combBkg0;
    TString _Background_combBkg0;
    TString _Events;
    
    double pi_ = 3.1415927;
    
    TH2D *hSignal_combBkg0_cEtaRegion;
    TH2D *hBackground_combBkg0_cEtaRegion;
    TH1F *hEvents;
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
    TH1::SetDefaultSumw2();
    
    TString _centrality[9] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "MinBias"};
    TString _signal = "/hSignal_combBkg_af0_as1";
    TString _background = "/hBackground_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_combBkg0 = _dirName + _centrality[cent] + _signal;
    _Background_combBkg0 = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    cout<<"[Combinatorial cross eta region] = "<<_Signal_combBkg0<<'\t'<<_Background_combBkg0<<'\t'<<_Events<<endl;
    
    hSignal_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Background_combBkg0);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_combBkg0_cEtaRegion->GetXaxis()->GetBinWidth(1);
    
    hSignal_combBkg0_cEtaRegion->Divide(hBackground_combBkg0_cEtaRegion);
    _x0 = hBackground_combBkg0_cEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_combBkg0_cEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_combBkg0_cEtaRegion->GetBinContent(_x0,_y0);
  //  hSignal_combBkg0_cEtaRegion->Scale(_B0/(_nEvents*_nEvents));
    hSignal_combBkg0_cEtaRegion->Scale(_B0/(_nEvents*_nEvents/2.));
    cout<<"Number of events = "<<_nEvents<<endl;
    hSignal_combBkg0_cEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal_combBkg0_cEtaRegion;
    
}

void
ThreeParticleAnalyzer::WindowDressing()
{
    
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(0);
    gStyle->SetPalette(1);
    gStyle->SetFrameFillColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetPadBorderSize(0);
    gStyle->SetCanvasBorderSize(0);
    gStyle->SetFrameLineColor(1);
    gStyle->SetFrameLineWidth(2.0);
    gStyle->SetCanvasColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadColor(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetLegendBorderSize(0);
    gStyle->SetErrorX(0.5);
    gStyle->SetTextFont(42);
    gStyle->SetLabelFont(42,"x");
    gStyle->SetLabelFont(42,"y");
    gStyle->SetLabelFont(42,"z");
    gStyle->SetTitleFont(42,"x");
    gStyle->SetTitleFont(42,"y");
    gStyle->SetTitleFont(42,"z");
    gStyle->SetEndErrorSize(1);
}

TCanvas
*ThreeParticleAnalyzer::Canvas()
{
    TCanvas *c1 = new TCanvas("c1","C1",700,500);
    WindowDressing();
    c1->SetFillColor(0);
    c1->SetBorderMode(0);
    c1->SetBorderSize(2);
    c1->SetTickx(1);
    c1->SetTicky(1);
    c1->SetFrameFillStyle(0);
    c1->SetFrameBorderMode(0);
    c1->SetTopMargin(0.05);
    c1->SetBottomMargin(0.1);
    c1->SetLeftMargin(0.1);
    c1->SetRightMargin(0.15);
    c1->SetTheta(50.61189);
    c1->SetPhi(40.90062);
    c1->cd();
    return c1;
    
}

TCanvas
*ThreeParticleAnalyzer::Canvas1()
{
    TCanvas *c2 = new TCanvas("c2","C2",700,500);
    WindowDressing();
    c2->SetFillColor(0);
    c2->SetBorderMode(0);
    c2->SetBorderSize(2);
    c2->SetTickx(1);
    c2->SetTicky(1);
    c2->SetFrameFillStyle(0);
    c2->SetFrameBorderMode(0);
    c2->SetTopMargin(0.05);
    c2->SetBottomMargin(0.1);
    c2->SetLeftMargin(0.1);
    c2->SetRightMargin(0.15);
    c2->SetTheta(50.61189);
    c2->SetPhi(40.90062);
    c2->cd();
    return c2;

}

TCanvas
*ThreeParticleAnalyzer::Canvas2()
{
    TCanvas *c3 = new TCanvas("c3","C3",700,500);
    WindowDressing();
    c3->SetFillColor(0);
    c3->SetBorderMode(0);
    c3->SetBorderSize(2);
    c3->SetTickx(1);
    c3->SetTicky(1);
    c3->SetFrameFillStyle(0);
    c3->SetFrameBorderMode(0);
    c3->SetTopMargin(0.05);
    c3->SetBottomMargin(0.1);
    c3->SetLeftMargin(0.1);
    c3->SetRightMargin(0.15);
    c3->SetTheta(50.61189);
    c3->SetPhi(40.90062);
    c3->cd();
    return c3;
    
}

TCanvas
*ThreeParticleAnalyzer::Canvas3()
{
    TCanvas *c4 = new TCanvas("c4","C4",700,500);
    WindowDressing();
    c4->SetFillColor(0);
    c4->SetBorderMode(0);
    c4->SetBorderSize(2);
    c4->SetTickx(1);
    c4->SetTicky(1);
    c4->SetFrameFillStyle(0);
    c4->SetFrameBorderMode(0);
    c4->SetTopMargin(0.05);
    c4->SetBottomMargin(0.1);
    c4->SetLeftMargin(0.1);
    c4->SetRightMargin(0.15);
    c4->SetTheta(50.61189);
    c4->SetPhi(40.90062);
    c4->cd();
    return c4;
    
}

TCanvas
*ThreeParticleAnalyzer::Canvas4()
{
    TCanvas *c5 = new TCanvas("c5","C5",700,500);
    WindowDressing();
    c5->SetFillColor(0);
    c5->SetBorderMode(0);
    c5->SetBorderSize(2);
    c5->SetTickx(1);
    c5->SetTicky(1);
    c5->SetFrameFillStyle(0);
    c5->SetFrameBorderMode(0);
    c5->SetTopMargin(0.05);
    c5->SetBottomMargin(0.1);
    c5->SetLeftMargin(0.1);
    c5->SetRightMargin(0.15);
    c5->SetTheta(50.61189);
    c5->SetPhi(40.90062);
    c5->cd();
    return c5;
    
}

TCanvas
*ThreeParticleAnalyzer::Canvas5()
{
    TCanvas *c6 = new TCanvas("c6","C6",700,500);
    WindowDressing();
    c6->SetFillColor(0);
    c6->SetBorderMode(0);
    c6->SetBorderSize(2);
    c6->SetTickx(1);
    c6->SetTicky(1);
    c6->SetFrameFillStyle(0);
    c6->SetFrameBorderMode(0);
    c6->SetTopMargin(0.05);
    c6->SetBottomMargin(0.1);
    c6->SetLeftMargin(0.1);
    c6->SetRightMargin(0.15);
    c6->SetTheta(50.61189);
    c6->SetPhi(40.90062);
    c6->cd();
    return c6;
    
}

TCanvas
*ThreeParticleAnalyzer::Canvas6()
{
    TCanvas *c7 = new TCanvas("c7","C7",700,500);
    WindowDressing();
    c7->SetFillColor(0);
    c7->SetBorderMode(0);
    c7->SetBorderSize(2);
    c7->SetTickx(1);
    c7->SetTicky(1);
    c7->SetFrameFillStyle(0);
    c7->SetFrameBorderMode(0);
    c7->SetTopMargin(0.05);
    c7->SetBottomMargin(0.1);
    c7->SetLeftMargin(0.1);
    c7->SetRightMargin(0.15);
    c7->SetTheta(50.61189);
    c7->SetPhi(40.90062);
    c7->cd();
    return c7;
   
    
}


