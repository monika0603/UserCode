
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
    fRead = new TFile("TriHadronCorr_BkgTerm.root");
    fRead->ls();
    
    if(fRead) cout<<"Successfully opned the input file."<<endl;
}

ThreeParticleAnalyzer::~ThreeParticleAnalyzer()
{
    delete fRead;
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
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
    TString _centrality[9] = {"0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80"};

    TH1::SetDefaultSumw2();
   // cout<<"cent = "<<cent<<'\t'<<_centrality[cent]<<endl;
    
    switch(cent)
    {
        case 0:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult0_10/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult0_10/hBackground0";
            _Events = "TriHadronAnalysisMult0_10/evtHPNtrk";
            break;
        }
        case 1:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult10_20/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult10_20/hBackground0";
            _Events = "TriHadronAnalysisMult10_20/evtHPNtrk";
            break;
        }
        case 2:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult20_30/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult20_30/hBackground0";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 3:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult20_30/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult20_30/hBackground0";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 4:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult30_40/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult30_40/hBackground0";
            _Events = "TriHadronAnalysisMult30_40/evtHPNtrk";
            break;
        }
        case 5:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult40_50/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult40_50/hBackground0";
            _Events = "TriHadronAnalysisMult40_50/evtHPNtrk";
            break;
        }
        case 6:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult50_60/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult50_60/hBackground0";
            _Events = "TriHadronAnalysisMult50_60/evtHPNtrk";
            break;
        }
        case 7:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult60_70/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult60_70/hBackground0";
            _Events = "TriHadronAnalysisMult60_70/evtHPNtrk";
            break;
        }
        case 8:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult70_80/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMult70_80/hBackground0";
            _Events = "TriHadronAnalysisMult70_80/evtHPNtrk";
            break;
        }
        default:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMultMinBias/hSignal0";
            _Background_sEtaRegion = "TriHadronAnalysisMultMinBias/hBackground0";
            _Events = "TriHadronAnalysisMultMinBias/evtHPNtrk";
            break;
        }
    }
    
    cout<<_Signal_sEtaRegion<<endl;
    
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
    
    return hSignal_sEtaRegion;
    
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
    cout<<"cent = "<<cent<<endl;
    
    switch(cent)
    {
        case 0:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult0_10/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult0_10/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult0_10/evtHPNtrk";
            break;
        }
        case 1:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult10_20/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult10_20/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult10_20/evtHPNtrk";
            break;
        }
        case 2:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult20_30/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult20_30/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 3:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult20_30/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult20_30/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 4:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult30_40/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult30_40/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult30_40/evtHPNtrk";
            break;
        }
        case 5:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult40_50/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult40_50/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult40_50/evtHPNtrk";
            break;
        }
        case 6:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult50_60/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult50_60/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult50_60/evtHPNtrk";
            break;
        }
        case 7:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult60_70/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult60_70/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult60_70/evtHPNtrk";
            break;
        }
        case 8:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMult70_80/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMult70_80/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult70_80/evtHPNtrk";
            break;
        }
        default:
        {
            _Signal_cEtaRegion = "TriHadronAnalysisMultMinBias/hSignal_af0_as1";
            _Background_cEtaRegion = "TriHadronAnalysisMultMinBias/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMultMinBias/evtHPNtrk";
            break;
        }
    }
    
    cout<<_Signal_cEtaRegion<<endl;
    
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
    cout<<"cent = "<<cent<<endl;
    
    switch(cent)
    {
        case 0:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult0_10/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult0_10/hBackground0";
            _Events = "TriHadronAnalysisMult0_10/evtHPNtrk";
            break;
        }
        case 1:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult10_20/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult10_20/hBackground0";
            _Events = "TriHadronAnalysisMult10_20/evtHPNtrk";
            break;
        }
        case 2:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult20_30/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult20_30/hBackground0";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 3:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult20_30/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult20_30/hBackground0";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 4:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult30_40/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult30_40/hBackground0";
            _Events = "TriHadronAnalysisMult30_40/evtHPNtrk";
            break;
        }
        case 5:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult40_50/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult40_50/hBackground0";
            _Events = "TriHadronAnalysisMult40_50/evtHPNtrk";
            break;
        }
        case 6:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult50_60/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult50_60/hBackground0";
            _Events = "TriHadronAnalysisMult50_60/evtHPNtrk";
            break;
        }
        case 7:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult60_70/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult60_70/hBackground0";
            _Events = "TriHadronAnalysisMult60_70/evtHPNtrk";
            break;
        }
        case 8:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult70_80/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMult70_80/hBackground0";
            _Events = "TriHadronAnalysisMult70_80/evtHPNtrk";
            break;
        }
        default:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMultMinBias/hSignal_combBkg0";
            _Background_combBkg0 = "TriHadronAnalysisMultMinBias/hBackground0";
            _Events = "TriHadronAnalysisMultMinBias/evtHPNtrk";
            break;
        }
    }
    
    cout<<_Signal_combBkg0<<endl;
    
    hSignal_combBkg0 = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0 = (TH2D*)fRead->Get(_Background_combBkg0);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_combBkg0->GetXaxis()->GetBinWidth(1);
    
    hSignal_combBkg0->Divide(hBackground_combBkg0);
    _x0 = hBackground_combBkg0->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_combBkg0->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_combBkg0->GetBinContent(_x0,_y0);
    hSignal_combBkg0->Scale(_B0/(_nEvents));
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
    cout<<"cent = "<<cent<<endl;
    
    switch(cent)
    {
        case 0:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult0_10/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult0_10/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult0_10/evtHPNtrk";
            break;
        }
        case 1:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult10_20/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult10_20/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult10_20/evtHPNtrk";
            break;
        }
        case 2:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult20_30/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult20_30/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 3:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult20_30/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult20_30/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case 4:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult30_40/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult30_40/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult30_40/evtHPNtrk";
            break;
        }
        case 5:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult40_50/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult40_50/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult40_50/evtHPNtrk";
            break;
        }
        case 6:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult50_60/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult50_60/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult50_60/evtHPNtrk";
            break;
        }
        case 7:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult60_70/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult60_70/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult60_70/evtHPNtrk";
            break;
        }
        case 8:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMult70_80/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMult70_80/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMult70_80/evtHPNtrk";
            break;
        }
        default:
        {
            _Signal_combBkg0 = "TriHadronAnalysisMultMinBias/hSignal_combBkg_af0_as1";
            _Background_combBkg0 = "TriHadronAnalysisMultMinBias/hBackground_af0_as1";
            _Events = "TriHadronAnalysisMultMinBias/evtHPNtrk";
            break;
        }
    }
    
    cout<<_Signal_combBkg0<<endl;
    
    hSignal_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Background_combBkg0);
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    _phibinwidth = hSignal_combBkg0_cEtaRegion->GetXaxis()->GetBinWidth(1);
    
    hSignal_combBkg0_cEtaRegion->Divide(hBackground_combBkg0_cEtaRegion);
    _x0 = hBackground_combBkg0_cEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_combBkg0_cEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_combBkg0_cEtaRegion->GetBinContent(_x0,_y0);
    hSignal_combBkg0_cEtaRegion->Scale(_B0/(_nEvents));
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


