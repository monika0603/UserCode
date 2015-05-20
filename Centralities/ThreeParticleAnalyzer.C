
#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>
using namespace std;

class ThreeParticleAnalyzer
{
  public:
    ThreeParticleAnalyzer();
    ThreeParticleAnalyzer(std::string fileName);
    TH2D *SameEtaRegion(TFile *fRead, const int cent);
    void gStyle();
    void Canvas();
    void Canvas1();
    virtual ~ThreeParticleAnalyzer();
    
  private:
    TFile *fRead;
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
};

ThreeParticleAnalyzer::ThreeParticleAnalyzer( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
}

ThreeParticleAnalyzer::ThreeParticleAnalyzer()
{
    fRead = new TFile("TriHadronCorr_2pCorrFullStat.root");
    fRead.ls();
    
    if(fRead) cout<<"Successfully opned the input file."<<endl;
}

ThreeParticleAnalyzer::~ThreeParticleAnalyzer()
{
    delete fRead;
}

TH2D *SameEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    cout<<"cent = "<<cent<<endl;
    
    switch(cent)
    {
        case '0':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult0_10/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult0_10/hBackground1";
            _Events = "TriHadronAnalysisMult0_10/evtHPNtrk";
            cout<<"Why don't I get here?"<<endl;
            break;
        }
        case '1':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult10_20/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult10_20/hBackground1";
            _Events = "TriHadronAnalysisMult10_20/evtHPNtrk";
            break;
        }
        case '2':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult20_30/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult20_30/hBackground1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case '3':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult20_30/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult20_30/hBackground1";
            _Events = "TriHadronAnalysisMult20_30/evtHPNtrk";
            break;
        }
        case '4':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult30_40/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult30_40/hBackground1";
            _Events = "TriHadronAnalysisMult30_40/evtHPNtrk";
            break;
        }
        case '5':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult40_50/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult40_50/hBackground1";
            _Events = "TriHadronAnalysisMult40_50/evtHPNtrk";
            break;
        }
        case '6':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult50_60/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult50_60/hBackground1";
            _Events = "TriHadronAnalysisMult50_60/evtHPNtrk";
            break;
        }
        case '7':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult60_70/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult60_70/hBackground1";
            _Events = "TriHadronAnalysisMult60_70/evtHPNtrk";
            break;
        }
        case '8':
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMult70_80/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMult70_80/hBackground1";
            _Events = "TriHadronAnalysisMult70_80/evtHPNtrk";
            break;
        }
        default:
        {
            _Signal_sEtaRegion = "TriHadronAnalysisMultMinBias/hSignal1";
            _Background_sEtaRegion = "TriHadronAnalysisMultMinBias/hBackground1";
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
    //  hSignal_sEtaRegion->Scale(_B0/(_nEvents));
    hSignal_sEtaRegion->Scale(_B0);
    hSignal_sEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal_sEtaRegion;
    
}


void
ThreeParticleAnalyzer::gStyle()
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

void
ThreeParticleAnalyzer::Canvas()
{
    TCanvas *c1 = new TCanvas("c1","C1",700,500);
    gStyle();
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
    c1->SetLogy();
    c1->cd();
    
}

void
ThreeParticleAnalyzer::Canvas1()
{
    TCanvas *c2 = new TCanvas("c2","C2",500,500);
    gStyle();
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

}

