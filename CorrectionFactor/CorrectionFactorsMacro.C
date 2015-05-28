#include "CorrectionFactors_MinBias_PbPb.C"
#include <TH1.h>

void CorrectionFactorsMacro()
{
    CorrectionFactors_MinBias_PbPb *cf = new CorrectionFactors_MinBias_PbPb();
    
    TFile *fRead = new TFile("TriHadronFirstAttempt_FullStat_Centralities.root");
    
    const int nEtaBins = 51;
    TH1F *hdNdEta[8];
    const int centBin = 8;
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hdNdEta[iCent_] = new TH1F(Form("hdNdEta_cent%d",iCent_), "hdNdEta", nEtaBins, -3.0, 3.0);
    }
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hdNdEta[iCent_] = Default(fRead);
    }
    
    TH1F *hUnSymmetrized[8];
    TH1F *hSymmetrized[8];
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hSymmetrized[iCent_] = Symmetrize(hdNdEta[iCent_]);
    }
    
    TH2F *hFactors[8];
    
    const double vZMin = -15.0;
    const double vZMax = 15.0;
    const int nVz = 15;
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        hFactors[iCent_] = new TH2F(Form("hFactors_cent%d",iCent_), "Efficiency; vZ vs eta", nEtaBins, -3.0, 3.0, nVz, vZMin, vZMax );
    }
    
    
    for(int iCent_=0; iCent_<centBin; iCent_++)
    {
        AlldNdEta(fRead, hSymmetrized[iCent_]);
    }
    
    
}






