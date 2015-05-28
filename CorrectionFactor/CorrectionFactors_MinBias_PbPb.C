
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
    void AlldNdEta(TFile *fRead, TH1F *hSymmetrized);
    virtual ~CorrectionFactors_MinBias_PbPb();
    
  private:
    TFile *fRead;
};

CorrectionFactors_MinBias_PbPb::CorrectionFactors_MinBias_PbPb( std::string fileName )
{
    fRead = new TFile(fileName.c_str());
    if(fRead) cout<<"Successfully opned the input file."<<endl;
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
    
    TH1F *hdNdEta_default[8];
    TH1F *hEvents[8];
    const float binWidth = 0.06;
    char *cent0 = "0_10"; char *cent1 = "10_20"; char *cent2 = "20_30"; char *cent3 = "30_40";
    char *cent4 = "40_50"; char *cent5 = "50_60"; char *cent6 = "60_70"; char *cent7 = "70_80";
    
    char *array[8];
    
    array[0] = cent0; array[1] = cent1; array[2] = cent2; array[3] = cent3; array[4] = cent4;
    array[5] = cent5; array[6] = cent6; array[7] = cent7;
    
    double nEvents_[8]={-99,-99,-99,-99,-99,-99,-99,-99};
    const int centBin = 8;
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        char _baseHistoName[400];
        sprintf(_baseHistoName,"TriHadronAnalysisMult%d/hdNdEta_VzBin_7",array[iCent_]);
        cout<<_baseHistoName<<endl;

        hdNdEta_default[iCent_]  = (TH1F*)fRead->Get(_baseHistoName);
    
        char _baseEventHisto[400];
        sprintf(_baseEventHisto,"TriHadronAnalysisMult%d/hdNdEta_VzBin_7",array[iCent_]);
        cout<<_baseEventHisto<<endl;

        hEvents[iCent_] = (TH1F *)fRead->Get(_baseEventHisto);
        nEvents_[iCent_] = hEvents[iCent_]->GetEntries();
    
        hdNdEta_default[iCent_]->Scale(1.0/nEvents_[iCent_]/binWidth);
        return hdNdEta_default[iCent_];
    }
    
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

void AlldNdEta(TFile *fRead, TH1F *hSymmetrized)
{
    const float binWidth = 0.06;
    const int nBins = 14;
    const int nEtaBins = 51;
    const double vZMin = -15.0;
    const double vZMax = 15.0;
    const int nVz = 15;
    double ratio[8] = {99,99,99,99,99,99,99,99};
    const int centBin = 8;
    
    char *cent0 = "0_10"; char *cent1 = "10_20"; char *cent2 = "20_30"; char *cent3 = "30_40";
    char *cent4 = "40_50"; char *cent5 = "50_60"; char *cent6 = "60_70"; char *cent7 = "70_80";
    
    char *array[8];
    
    array[0] = cent0; array[1] = cent1; array[2] = cent2; array[3] = cent3; array[4] = cent4;
    array[5] = cent5; array[6] = cent6; array[7] = cent7;
    
    TH2F *hVzEtaEff[8];
    TH1F *hdNdEtaVzBin[8][15];
    TH1F * hEventsVzBin[8];
    double nEvents[8];
    double numerator[8];
    double denominator[8];
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hVzEtaEff[iCent_] = new TH2F(Form("hVzEtaEff_cent%d",iCent_), "Efficiency; vZ vs eta", nEtaBins, -3.0, 3.0, nVz, vZMin, vZMax);
        
        for(int iBin_=0; iBin_<=nBins; iBin_++)
        {
            for(int iEta_=0; iEta_<=nEtaBins; iEta_++)
            {
                hVzEtaEff[iCent_]->SetBinContent(iEta_+1,iBin_+1, 0.0);
            }
        }
    }
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        for(int iBin_=0; iBin_<=nBins; iBin_++)
        {
            char nEventsVzBin[400];
            sprintf(nEventsVzBin,"TriHadronAnalysisMult%d/nEventsVzBin_%d",array,iBin_);
            cout<<nEventsVzBin<<endl;
            hEventsVzBin[iCent_] = (TH1F *)fRead->Get(nEventsVzBin);
            nEvents[iCent_] = hEventsVzBin[iCent_]->GetEntries();
        
            char ndNdEtaVzBin[400];
            sprintf(ndNdEtaVzBin,"TriHadronAnalysisMult%d/hdNdEta_VzBin_%d",array,iBin_);
            hdNdEtaVzBin[iCent_][iBin_] = (TH1F*)fRead->Get(ndNdEtaVzBin);
            if(iBin_!=7)		hdNdEtaVzBin[iCent_][iBin_]->Scale(1.0/nEvents[iCent_]/binWidth);
        
            for(int iEta_=0; iEta_<=nEtaBins; iEta_++)
            {
            
                numerator[iCent_] = hdNdEtaVzBin[iCent_][iBin_]->GetBinContent(iEta_+1);
                denominator[iCent_] = hSymmetrized[iCent_].GetBinContent(iEta_+1);
                if(denominator[iCent_] > 0) ratio[iCent_] = numerator[iCent_]/denominator[iCent_];
            
                //   cout<<iEta_<<'\t'<<hSymmetrized->GetBinContent(iEta_+1)<<'\t'<<hdNdEtaVzBin[iBin_]->GetBinContent(iEta_+1)<<'\t'<<ratio<<endl;
                if(hSymmetrized[iCent_].GetBinContent(iEta_+1) > 0.0 && ratio[iCent_] < 2.0) hVzEtaEff[iCent_]->SetBinContent(iEta_+1,iBin_+1,ratio[iCent_]);
            }
        }
    }
    
    
    TFile *fNew = new TFile("CorrectionFactors_PbPb.root", "RECREATE");
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hVzEtaEff[iCent_]->Write();
    }
    fNew->Close();
}


