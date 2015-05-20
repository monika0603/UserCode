#include "ThreeParticleAnalyzer.C"

void ThreeParticleMacro()
{
    
    ThreeParticleAnalyzer *cf = new ThreeParticleAnalyzer();
    
    cf->Canvas();
    TFile *fRead = new TFile("TriHadronCorr_2pCorrFullStat.root");
    TH2D *hSig_sameEtaRegion = SameEtaRegion(fRead, 2);
    hSig_sameEtaRegion->Draw("zcol");
    
   /* TFile *fNew = new TFile("TriHadronAnalyzerOutput_PbPb.root", "RECREATE");
    hFactors->Write();
    fNew->Close();*/
    
}






