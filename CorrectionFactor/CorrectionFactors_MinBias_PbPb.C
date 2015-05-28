
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
    
    double nEvents_[8]={-99,-99,-99,-99,-99,-99,-99,-99};
    const int centBin = 8;
    const float binWidth = 0.06;
    
    char *_baseHistoName[8];
    strcpy(_baseHistoName[0], "TriHadronAnalysisMult0_10/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[1], "TriHadronAnalysisMult10_20/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[2], "TriHadronAnalysisMult20_30/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[3], "TriHadronAnalysisMult30_40/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[4], "TriHadronAnalysisMult40_50/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[5], "TriHadronAnalysisMult50_60/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[6], "TriHadronAnalysisMult60_70/hdNdEta_VzBin_7");
    strcpy(_baseHistoName[7], "TriHadronAnalysisMult70_80/hdNdEta_VzBin_7");
    
    char *_baseEventHisto[8];
    strcpy(_baseEventHisto[0], "TriHadronAnalysisMult0_10/nEventsVzBin_7");
    strcpy(_baseEventHisto[1], "TriHadronAnalysisMult10_20/nEventsVzBin_7");
    strcpy(_baseEventHisto[2], "TriHadronAnalysisMult20_30/nEventsVzBin_7");
    strcpy(_baseEventHisto[3], "TriHadronAnalysisMult30_40/nEventsVzBin_7");
    strcpy(_baseEventHisto[4], "TriHadronAnalysisMult40_50/nEventsVzBin_7");
    strcpy(_baseEventHisto[5], "TriHadronAnalysisMult50_60/nEventsVzBin_7");
    strcpy(_baseEventHisto[6], "TriHadronAnalysisMult60_70/nEventsVzBin_7");
    strcpy(_baseEventHisto[7], "TriHadronAnalysisMult70_80/nEventsVzBin_7");
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        cout<<_baseHistoName[iCent_]<<endl;
        hdNdEta_default[iCent_]  = (TH1F*)fRead->Get(_baseHistoName[iCent_]);

        cout<<_baseEventHisto[iCent_]<<endl;
        hEvents[iCent_] = (TH1F *)fRead->Get(_baseEventHisto[iCent_]);
        nEvents_[iCent_] = hEvents[iCent_]->GetEntries();
        cout<<nEvents_[iCent_]<<endl;
    
        hdNdEta_default[iCent_]->Scale(1.0/nEvents_[iCent_]/binWidth);
    }
    
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
    
    TH2F *hVzEtaEff[8];
    TH1F *hdNdEtaVzBin[8][15];
    TH1F * hEventsVzBin[8];
    double nEvents[8];
    double numerator[8];
    double denominator[8];
    
    char *nEventsVzBin[8];
    strcpy(nEventsVzBin[0], "TriHadronAnalysisMult0_10/nEventsVzBin_");
    strcpy(nEventsVzBin[1], "TriHadronAnalysisMult10_20/nEventsVzBin_");
    strcpy(nEventsVzBin[2], "TriHadronAnalysisMult20_30/nEventsVzBin_");
    strcpy(nEventsVzBin[3], "TriHadronAnalysisMult30_40/nEventsVzBin_");
    strcpy(nEventsVzBin[4], "TriHadronAnalysisMult40_50/nEventsVzBin_");
    strcpy(nEventsVzBin[5], "TriHadronAnalysisMult50_60/nEventsVzBin_");
    strcpy(nEventsVzBin[6], "TriHadronAnalysisMult60_70/nEventsVzBin_");
    strcpy(nEventsVzBin[7], "TriHadronAnalysisMult70_80/nEventsVzBin_");
    
    char *ndNdEtaVzBin[8];
    strcpy(ndNdEtaVzBin[0], "TriHadronAnalysisMult0_10/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[1], "TriHadronAnalysisMult10_20/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[2], "TriHadronAnalysisMult20_30/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[3], "TriHadronAnalysisMult30_40/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[4], "TriHadronAnalysisMult40_50/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[5], "TriHadronAnalysisMult50_60/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[6], "TriHadronAnalysisMult60_70/hdNdEta_VzBin_");
    strcpy(ndNdEtaVzBin[7], "TriHadronAnalysisMult70_80/hdNdEta_VzBin_");
    
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
            stringstream ss;
            ss<<nEventsVzBin[iCent_]<<iBin_;
            cout<<"*********"<<ss.str()<<endl;
            hEventsVzBin[iCent_] = (TH1F *)fRead->Get(nEventsVzBin[iCent_]);
            nEvents[iCent_] = hEventsVzBin[iCent_]->GetEntries();
        
            stringstream dd;
            dd<<ndNdEtaVzBin[iCent_]<<iBin_;
            cout<<"*********"<<dd.str()<<endl;
            hdNdEtaVzBin[iCent_][iBin_] = (TH1F*)fRead->Get(ndNdEtaVzBin[iCent_]);
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


