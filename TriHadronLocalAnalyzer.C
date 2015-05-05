
#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>
using namespace std;

class TriHadronLocalAnalyzer
{
  public:
    TriHadronLocalAnalyzer();
    //TriHadronLocalAnalyzer(std::string fileName);
    void Analyze();
    void Canvas();
    void Canvas1();
    void Canvas2();
    void Canvas3();
    virtual ~TriHadronLocalAnalyzer();

  private:
    TFile *fRead;

    TString _Signal_sEtaRegion;
    TString _Background_sEtaRegion;
    TString _Events;
    
    TH2D *hSignal_sEtaRegion;
    TH2D *hBackground_sEtaRegion;
    TH1F *hEvents;
    
    double  _phibinwidth;
    int _x0, _y0, _B0;
    double _nEvents;
    
};

TriHadronLocalAnalyzer::TriHadronLocalAnalyzer( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
}

TriHadronLocalAnalyzer::TriHadronLocalAnalyzer()
{
    fRead = new TFile("TriHadronFirstAttempt.root");
    fRead.ls();
    
    if(fRead) cout<<"Successfully opned the input file."<<endl;
}

TriHadronLocalAnalyzer::~TriHadronLocalAnalyzer()
{
    delete fRead;
}

/*void
TriHadronLocalAnalyzer::Analyze()
{
    TH1::SetDefaultSumw2();
    
    _Signal_sEtaRegion = "TriHadronAnalysisMult100/hSignal0";
    _Background_sEtaRegion = "TriHadronAnalysisMult100/hBackground0";
    _Events = "TriHadronAnalysisMult100/evtHPNtrk";
    
    hEvents = (TH1F*)fRead->Get(_Events);
    _nEvents = hEvents->Integral();
    
    hSignal_sEtaRegion = (TH2D*)fRead->Get(_Signal_sEtaRegion);
    hBackground_sEtaRegion = (TH2D*)fRead->Get(_Background_sEtaRegion);
    
    _phibinwidth = hSignal_sEtaRegion->GetXaxis()->GetBinWidth(1);
    
    hSignal_sEtaRegion->Divide(hBackground_sEtaRegion);
    _x0 = hBackground_sEtaRegion->GetXaxis()->FindBin(0.0);
    _y0 = hBackground_sEtaRegion->GetYaxis()->FindBin(0.0);
    _B0 = hBackground_sEtaRegion->GetBinContent(_x0,_y0);
    hSignal_sEtaRegion->Scale(_B0/(_nEvents));
    hSignal_sEtaRegion->Scale(1.0/_phibinwidth/_phibinwidth);
    Canvas();
    hSignal_sEtaRegion->Draw("zcol");
    
}*/

void
TriHadronLocalAnalyzer::Canvas()
{
    TCanvas *c1 = new TCanvas("c1","",500,500);
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
TriHadronLocalAnalyzer::Canvas1()
{
  //  TCanvas *clone1 = (TCanvas*)c1->Clone("clone1");
  //  clone1->cd();
    
    TCanvas *c2 = new TCanvas("c2","",500,500);
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

void
TriHadronLocalAnalyzer::Canvas2()
{
    
    TCanvas *c3 = new TCanvas("c3","",500,500);
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
    
}

void
TriHadronLocalAnalyzer::Canvas3()
{
    
    TCanvas *c4 = new TCanvas("c4","",500,500);
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
    
}



