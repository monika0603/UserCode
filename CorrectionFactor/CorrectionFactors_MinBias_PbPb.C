
#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TString.h>
#include <TCanvas.h>
#include <TStyle.h>

using namespace std;

class CorrectionFactors_MinBias_PbPb
{
  public:
    CorrectionFactors_MinBias_PbPb();
    CorrectionFactors_MinBias_PbPb(std::string fileName);
    TH1F *Default(TFile *fRead);
    TH1F *odNdEta(TFile *fRead);
    TH1F *Symmetrize(TH1F *h);
    TH2F *AlldNdEta(TFile *fRead, TH1F *hSymmetrized);
    void WindowDressing();
    TCanvas *Canvas();
    TCanvas *Canvas1();
    virtual ~CorrectionFactors_MinBias_PbPb();
    
  private:
    TFile *fRead;
};

CorrectionFactors_MinBias_PbPb::CorrectionFactors_MinBias_PbPb( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
}

CorrectionFactors_MinBias_PbPb::CorrectionFactors_MinBias_PbPb()
{
    fRead = new TFile("TriHadronFirstAttempt_FullStat_Centralities.root");
    fRead->ls();
    
    if(fRead) cout<<"Successfully opned the input file."<<endl;
}

CorrectionFactors_MinBias_PbPb::~CorrectionFactors_MinBias_PbPb()
{
    delete fRead;
}

TH1F *Default(TFile *fRead)
{
    TH1::SetDefaultSumw2();
    
    const float binWidth = 0.06;
    
    TString _baseHistoName = "TriHadronAnalysisMultMinBias/hdNdEta_VzBin_7";
    TH1F *hdNdEta_default  = (TH1F*)fRead->Get(_baseHistoName);
    
    TString _baseEventHisto = "TriHadronAnalysisMultMinBias/nEventsVzBin_7";
    TH1F *hEvents = (TH1F *)fRead->Get(_baseEventHisto);
    double nEvents_ = hEvents->GetEntries();
    
    hdNdEta_default->Scale(1.0/nEvents_/binWidth);
    
    return hdNdEta_default;
    
}

TH1F *odNdEta(TFile *fRead)
{
    TH1::SetDefaultSumw2();
    
    const float binWidth = 0.06;
    
    TString _baseHistoName = "TriHadronAnalysisMultMinBias/hdNdEta_VzBin_0";
    TH1F *hdNdEta_0  = (TH1F*)fRead->Get(_baseHistoName);
    
    TString _baseEventHisto = "TriHadronAnalysisMultMinBias/nEventsVzBin_0";
    TH1F *hEvents = (TH1F *)fRead->Get(_baseEventHisto);
    double nEvents_ = hEvents->GetEntries();
    
    return hdNdEta_0;
    
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
    const int nBins = 14;
    const int nEtaBins = 51;
    const double vZMin = -15.0;
    const double vZMax = 15.0;
    const int nVz = 15;
    double ratio = 999;
    
    TH2F *hVzEtaEff = new TH2F("hVzEtaEff_cent","hVzEtaEff;eta;vz", nEtaBins, -3.0, 3.0, nVz, vZMin, vZMax);
    TH1F *hdNdEtaVzBin[15];
    
    for(int iBin_=0; iBin_<=nBins; iBin_++)
    {
        for(int iEta_=0; iEta_<=nEtaBins; iEta_++)
        {
            hVzEtaEff->SetBinContent(iEta_+1,iBin_+1, 0.0);
        }
    }
    
    for(int iBin_=0; iBin_<=nBins; iBin_++)
    {
        char nEventsVzBin[400];
        sprintf(nEventsVzBin,"TriHadronAnalysisMultMinBias/nEventsVzBin_%d",iBin_);
        TH1F * hEventsVzBin = (TH1F *)fRead->Get(nEventsVzBin);
        double nEvents = hEventsVzBin->GetEntries();
        
        char ndNdEtaVzBin[400];
        sprintf(ndNdEtaVzBin,"TriHadronAnalysisMultMinBias/hdNdEta_VzBin_%d",iBin_);
        hdNdEtaVzBin[iBin_] = (TH1F*)fRead->Get(ndNdEtaVzBin);
        if(iBin_!=7)		hdNdEtaVzBin[iBin_]->Scale(1.0/nEvents/binWidth);
        
        for(int iEta_=0; iEta_<=nEtaBins; iEta_++)
        {
            
            double numerator = hdNdEtaVzBin[iBin_]->GetBinContent(iEta_+1);
            double denominator = hSymmetrized->GetBinContent(iEta_+1);
            if(denominator > 0) ratio = numerator/denominator;
            
         //   cout<<iEta_<<'\t'<<hSymmetrized->GetBinContent(iEta_+1)<<'\t'<<hdNdEtaVzBin[iBin_]->GetBinContent(iEta_+1)<<'\t'<<ratio<<endl;
            if(hSymmetrized->GetBinContent(iEta_+1) > 0.0 && ratio < 2.0) hVzEtaEff->SetBinContent(iEta_+1,iBin_+1,ratio);
        }
        
        
    }
    
    return hVzEtaEff;
}


void
CorrectionFactors_MinBias_PbPb::WindowDressing()
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
*CorrectionFactors_MinBias_PbPb::Canvas()
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
    c1->SetLogy();
    c1->cd();
    return c1;
    
}

TCanvas
*CorrectionFactors_MinBias_PbPb::Canvas1()
{
    TCanvas *c2 = new TCanvas("c2","C2",500,500);
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

