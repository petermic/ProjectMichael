#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput = new TFile(output.c_str(), "recreate");
    fhRecoJetPt->Write();
    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  int nentries = fChain->GetEntriesFast();
  for (int jentry = 0; jentry < 100000; jentry++) {
    if (LoadTree(jentry) < 0) break;
    fChain->GetEntry(jentry);
    cout<<"analyzing event="<<jentry<<endl;
    if(isData==0){
    cout<<"good"<<endl;
      for(int indexjets=0;indexjets<njet_akpu3pf;indexjets++){
        if(fabs((*jeteta_akpu3pf)[indexjets]) < 1.5){
            fhRecoJetPt->Fill((*jetptCorr_akpu3pf)[indexjets]);
            /* 
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {            
            //(*Dpt)[indexDm]
            //(*DsvpvDistance)[indexDm]
            //(*Dalpha)[indexDm]
            //(*Dchi2cl)[indexDm]
            }//loop over D meson
             */
        }//end of selection over jets
      }//end of loop over jets
    }//end of is data
  }//end of loop over events

  cout<<"calling fit"<<endl;
  return 1;
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: ./d_jet [input] [output]\n");
        return 1;
    }

    djet* t = new djet(argv[1]);

    if (argc == 3)
        return t->d_jet(argv[2]);
    else
        return 1;
}
