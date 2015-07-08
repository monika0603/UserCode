#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TStyle.h>
#include <TF1.h>
#include <TMathBase.h>
using namespace std;

class ThreeParticleAnalyzer
{
  public:
    ThreeParticleAnalyzer();
    ThreeParticleAnalyzer(std::string fileName);
    TH2D *DivideAndScale(TH2D *hSignal, TH2D *hBackground, TH1F *hEvents);
    TH2D *SameEtaRegion(TFile *fRead, const int cent);
    TH2D *histoDressing(TH2D *histo);
    TH2D *CrossEtaRegion(TFile *fRead, const int cent);
    TH2D *CalculateDifference(TH2D *histo1, TH2D *histo2, int num);
    TH2D *CombinatorialBkgTerm(TFile *fRead, const int cent);
    TH2D *CombBkgTerm_crossEtaRegion(TFile *fRead, const int cent);
    TH2D *SD_sameEtaRegion(TFile *fRead, const int cent);
    TH2D *SD_crossEtaRegion(TFile *fRead, const int cent);
    TH2D *SD_combBkg_sameEtaRegion(TFile *fRead, const int cent);
    void WindowDressing();
    TCanvas *CanvasDressing(int i);
   double GausFunct(double *x, double *par);
    virtual ~ThreeParticleAnalyzer();
    
  private:
    TFile *fRead;
    
};

ThreeParticleAnalyzer::ThreeParticleAnalyzer()
{
 cout<<"Successfully opened the root file..."<<endl;
}

ThreeParticleAnalyzer::ThreeParticleAnalyzer( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
}


ThreeParticleAnalyzer::~ThreeParticleAnalyzer()
{
    delete fRead;
}

TH2D *DivideAndScale(TH2D *hSignal, TH2D *hBackground, TH1F *hEvents, TH1F *nMultTrig)
{
    TH1::SetDefaultSumw2();
    
    double _nEvents;
    double  _phibinwidth;
    double _nMultTrigger;
    int _x0, _y0, _B0;
    
    _nEvents = hEvents->Integral();
    _nMultTrigger = nMultTrig->GetSum();
    _phibinwidth = hSignal->GetXaxis()->GetBinWidth(1);
    
    hSignal->Divide(hBackground);
    _x0 = hBackground->GetXaxis()->FindBin(0.0);
    _y0 = hBackground->GetYaxis()->FindBin(0.0);
    _B0 = hBackground->GetBinContent(_x0,_y0);
    hSignal->Scale(_B0/_nMultTrigger);
    hSignal->Scale(1.0/_phibinwidth/_phibinwidth);
    
    return hSignal;
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
    TH1::SetDefaultSumw2();
    
    TString _Signal_sEtaRegion;
    TString _Background_sEtaRegion;
    TString _Events;
    TString _multTrig;
    
    TH2D *hSignal_sEtaRegion;
    TH2D *hBackground_sEtaRegion;
    TH1F *hEvents;
    TH1F *hMultTrig;
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal0";
    TString _background = "/hBackground0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    TString _ntrig = "/nMultTrig";
    
    _Signal_sEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_sEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    _multTrig = _dirName + _centrality[cent] + _ntrig;
    
    hSignal_sEtaRegion = (TH2D*)fRead->Get(_Signal_sEtaRegion);
    hBackground_sEtaRegion = (TH2D*)fRead->Get(_Background_sEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    hMultTrig = (TH1F*)fRead->Get(_multTrig);
    
    TH2D *hSig_sameEtaRegion = DivideAndScale(hSignal_sEtaRegion, hBackground_sEtaRegion, hEvents,hMultTrig);
    return hSig_sameEtaRegion;
}

TH2D *histoDressing(TH2D *histo)
{
    histo->SetTitle("");
    histo->GetYaxis()->SetTitle("#Delta#phi_{1}");
    histo->GetXaxis()->SetTitle("#Delta#phi_{2}");
    histo->GetXaxis()->SetLabelFont(42);
    histo->GetXaxis()->SetTitleSize(0.06);
    histo->GetXaxis()->SetTitleOffset(0.67);
    histo->GetYaxis()->SetLabelFont(42);
    histo->GetYaxis()->SetTitleSize(0.06);
    histo->GetYaxis()->SetTitleOffset(0.67);
    
    return histo;
}

TH2D *CrossEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_cEtaRegion;
    TString _Background_cEtaRegion;
    TString _Events;
    TString _multTrig;

    TH2D *hSignal_cEtaRegion;
    TH2D *hBackground_cEtaRegion;
    TH1F *hEvents;
    TH1F *hMultTrig;
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_af0_as1";
    TString _background = "/hBackground_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    TString _ntrig = "/nMultTrig";
    
    _Signal_cEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_cEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    _multTrig = _dirName + _centrality[cent] + _ntrig;
    
    hSignal_cEtaRegion = (TH2D*)fRead->Get(_Signal_cEtaRegion);
    hBackground_cEtaRegion = (TH2D*)fRead->Get(_Background_cEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    hMultTrig = (TH1F*)fRead->Get(_multTrig);
    
    TH2D *hSig_crossEtaRegion = DivideAndScale(hSignal_cEtaRegion, hBackground_cEtaRegion, hEvents, hMultTrig);
    return hSig_crossEtaRegion;
}

TH2D *CalculateDifference(TH2D *histo1, TH2D *histo2, int num)
{
    const double pi_ = 3.1415927;
    TH2D *hDifference = new TH2D(Form("hDiff%d",num), "#Delta#phi;#Delta#phi", 96,-pi_,pi_,96,-pi_,pi_);
    TH1::SetDefaultSumw2();
    
    for(int iBin = 1; iBin <=histo1->GetNbinsX(); iBin++)
    {
        for(int jBin = 1; jBin <=histo1->GetNbinsY(); jBin++)
        {
            int bin = hDifference->GetBin(iBin, jBin);
            double sameEta = histo1->GetBinContent(iBin, jBin);
            double sameEtaError = histo1->GetBinError(iBin, jBin);
            
            double crossEta = histo2->GetBinContent(iBin, jBin);
            double crossEtaError = histo2->GetBinError(iBin, jBin);
            
            double _difference = sameEta - crossEta;
            double _diffError = sqrt((sameEtaError*sameEtaError) + (crossEtaError*crossEtaError));
         //   cout<<sameEtaError<<'\t'<<crossEtaError<<'\t'<<_diffError<<endl;
            hDifference->SetBinContent(iBin, jBin, _difference);
            hDifference->SetBinError(iBin, jBin, _diffError);
        }
    }
    TH2D *hDifference_D = histoDressing(hDifference);
    return hDifference_D;
}

TH2D *CombinatorialBkgTerm(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_combBkg0;
    TString _Background_combBkg0;
    TString _Events;
    
    TH2D *hSignal_combBkg0;
    TH2D *hBackground_combBkg0;
    TH1F *hEvents;
    
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_combBkg0";
    TString _background = "/hBkg_combBkg0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_combBkg0 = _dirName + _centrality[cent] + _signal;
    _Background_combBkg0 = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;

    hSignal_combBkg0 = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0 = (TH2D*)fRead->Get(_Background_combBkg0);
    hEvents = (TH1F*)fRead->Get(_Events);
    
    TH2D *hSig_comBkg0 = DivideAndScale(hSignal_combBkg0, hBackground_combBkg0, hEvents);
    return hSig_comBkg0;
}

TH2D *CombBkgTerm_crossEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_combBkg0;
    TString _Background_combBkg0;
    TString _Events;
    
    TH2D *hSignal_combBkg0_cEtaRegion;
    TH2D *hBackground_combBkg0_cEtaRegion;
    TH1F *hEvents;
    TH1::SetDefaultSumw2();
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_combBkg_af0_as1";
    TString _background = "/hBkg_combBkg_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_combBkg0 = _dirName + _centrality[cent] + _signal;
    _Background_combBkg0 = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    hSignal_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Signal_combBkg0);
    hBackground_combBkg0_cEtaRegion = (TH2D*)fRead->Get(_Background_combBkg0);
    hEvents = (TH1F*)fRead->Get(_Events);
    
    TH2D *hSig_comBkg0_cEtaRegion = DivideAndScale(hSignal_combBkg0_cEtaRegion, hBackground_combBkg0_cEtaRegion, hEvents);
    return hSig_comBkg0_cEtaRegion;
}

TH2D *SD_sameEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_SD_sEtaRegion;
    TString _Background_SD_sEtaRegion;
    TString _Events;
    TString _multTrig;
    
    TH2D *hSignal_SD_sEtaRegion;
    TH2D *hBackground_SD_sEtaRegion;
    TH1F *hEvents;
    TH1F *hMultTrig;
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_SD0";
    TString _background = "/hBackground_SD0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    TString _ntrig = "/nMultTrig";
    
    _Signal_SD_sEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_SD_sEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    _multTrig = _dirName + _centrality[cent] + _ntrig;
    
    hSignal_SD_sEtaRegion = (TH2D*)fRead->Get(_Signal_SD_sEtaRegion);
    hBackground_SD_sEtaRegion = (TH2D*)fRead->Get(_Background_SD_sEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    hMultTrig = (TH1F*)fRead->Get(_multTrig);
    
    TH2D *hSig_SD_sEtaRegion = DivideAndScale(hSignal_SD_sEtaRegion, hBackground_SD_sEtaRegion, hEvents, hMultTrig);
    return hSig_SD_sEtaRegion;
}

TH2D *SD_crossEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_SD_cEtaRegion;
    TString _Background_SD_cEtaRegion;
    TString _Events;
    TString _multTrig;
    
    TH2D *hSignal_SD_cEtaRegion;
    TH2D *hBackground_SD_cEtaRegion;
    TH1F *hEvents;
    TH1F *hMultTrig;
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_SD_af0_as1";
    TString _background = "/hBackground_SD0_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    TString _ntrig = "/nMultTrig";
    
    _Signal_SD_cEtaRegion = _dirName + _centrality[cent] + _signal;
    _Background_SD_cEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    _multTrig = _dirName + _centrality[cent] + _ntrig;
    
    hSignal_SD_cEtaRegion = (TH2D*)fRead->Get(_Signal_SD_cEtaRegion);
    hBackground_SD_cEtaRegion = (TH2D*)fRead->Get(_Background_SD_cEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    hMultTrig = (TH1F*)fRead->Get(_multTrig);
    
    TH2D *hSig_SD_cEtaRegion = DivideAndScale(hSignal_SD_cEtaRegion, hBackground_SD_cEtaRegion, hEvents, hMultTrig);
    return hSig_SD_cEtaRegion;
}

TH2D *SD_combBkg_sameEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_SD_combBkg_sEtaRegion;
    TString _Bkg_SD_combBkg_sEtaRegion;
    TString _Events;
    
    TH2D *hSignal_SD_combBkg_sEtaRegion;
    TH2D *hBkg_SD_combBkg_sEtaRegion;
    TH1F *hEvents;
    TH1::SetDefaultSumw2();
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_combBkg_SD0";
    TString _background = "/hBkg_combBkgSD0";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_SD_combBkg_sEtaRegion = _dirName + _centrality[cent] + _signal;
    _Bkg_SD_combBkg_sEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    hSignal_SD_combBkg_sEtaRegion = (TH2D*)fRead->Get(_Signal_SD_combBkg_sEtaRegion);
    hBkg_SD_combBkg_sEtaRegion = (TH2D*)fRead->Get(_Bkg_SD_combBkg_sEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    
    TH2D *hSig_SD_sEtaRegion = DivideAndScale(hSignal_SD_combBkg_sEtaRegion, hBkg_SD_combBkg_sEtaRegion, hEvents);
    return hSig_SD_sEtaRegion;
}


TH2D *SD_combBkg_crossEtaRegion(TFile *fRead, const int cent)
{
    TH1::SetDefaultSumw2();
    
    TString _Signal_SD_combBkg_cEtaRegion;
    TString _Bkg_SD_combBkg_cEtaRegion;
    TString _Events;
    
    TH2D *hSignal_SD_combBkg_cEtaRegion;
    TH2D *hBkg_SD_combBkg_cEtaRegion;
    TH1F *hEvents;
    TH1::SetDefaultSumw2();
    
    TString _centrality[10] = {"0_2", "0_10", "10_20", "20_30", "30_40", "40_50", "50_60", "60_70", "70_80", "MinBias"};
    TString _signal = "/hSignal_combBkg_SD0_af0_as1";
    TString _background = "/hBkg_combBkg_SD0_af0_as1";
    TString _dirName = "TriHadronAnalysisMult";
    TString _events = "/evtHPNtrk";
    
    _Signal_SD_combBkg_cEtaRegion = _dirName + _centrality[cent] + _signal;
    _Bkg_SD_combBkg_cEtaRegion = _dirName + _centrality[cent] + _background;
    _Events = _dirName + _centrality[cent] + _events;
    
    hSignal_SD_combBkg_cEtaRegion = (TH2D*)fRead->Get(_Signal_SD_combBkg_cEtaRegion);
    hBkg_SD_combBkg_cEtaRegion = (TH2D*)fRead->Get(_Bkg_SD_combBkg_cEtaRegion);
    hEvents = (TH1F*)fRead->Get(_Events);
    
    TH2D *hSig_SD_cEtaRegion = DivideAndScale(hSignal_SD_combBkg_cEtaRegion, hBkg_SD_combBkg_cEtaRegion, hEvents);
    return hSig_SD_cEtaRegion;
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
*ThreeParticleAnalyzer::CanvasDressing(int i)
{
    TString name = "c";
    char numstr[21];
    sprintf(numstr, "%d", i);
    TString result = name + numstr;
    
    TCanvas *c = new TCanvas(result,result,700,500);
    WindowDressing();
    c->SetFillColor(0);
    c->SetBorderMode(0);
    c->SetBorderSize(2);
    c->SetTickx(1);
    c->SetTicky(1);
    c->SetFrameFillStyle(0);
    c->SetFrameBorderMode(0);
    c->SetTopMargin(0.05);
    c->SetBottomMargin(0.1);
    c->SetLeftMargin(0.1);
    c->SetRightMargin(0.15);
    c->SetTheta(50.61189);
    c->SetPhi(40.90062);
    c->cd();
    return c;
}

double GausFunct(double *x, double *par)
{
    double arg = 0;
    if(par[2] != 0) arg = (x[0] - par[1])/par[2];
    double sig = par[0]*exp(-0.5*arg*arg);
    return sig;
}

