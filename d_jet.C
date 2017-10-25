#include "d_jet.h"

#include "TFile.h"
#include "TH1.h"

int djet::d_jet(std::string output) {
    if (fChain == 0)
        return 1;

    TFile* foutput=new TFile(output.c_str(),"recreate");
    fhRecoJetPt->Write();
    fhRecoJetEta->Write();
    fhRecoJetPhi->Write();
    D_Pt_sig->Write();
    D_Pt_bkg->Write();
    D_Eta_sig->Write();
    D_Eta_bkg->Write();
    D_Phi_sig->Write();
    D_Phi_bkg->Write();
    DsvpvDist_sig->Write();
    DsvpvDist_bkg->Write();
    Dalpha_sig->Write();
    Dalpha_bkg->Write();
    Dchi2cl_sig->Write();
    Dchi2cl_bkg->Write();
    Dtrk1_Pt_sig->Write();
    Dtrk1_Pt_bkg->Write();
    Dtrk2_Pt_sig->Write();
    Dtrk2_Pt_bkg->Write();
    Dtrk1_Eta_sig->Write();
    Dtrk1_Eta_bkg->Write();
    Dtrk2_Eta_sig->Write();
    Dtrk2_Eta_bkg->Write();
    Delta_Phi->Write();

    foutput->Close();
    delete foutput;
   return 0;
}

int djet::loop(int isData) {
  int nentries = fChain->GetEntriesFast();
  for (int jentry = 0; jentry < nentries; jentry++) {
    if (LoadTree(jentry) < 0) break;
    fChain->GetEntry(jentry);
    cout<<"analyzing event="<<jentry<<endl;
    if(isData==0){
    cout<<"good"<<endl;
      for(int indexjets=0;indexjets<njet_akpu3pf;indexjets++){
        if(fabs((*jeteta_akpu3pf)[indexjets]) < 2){
            fhRecoJetPt->Fill((*jetptCorr_akpu3pf)[indexjets]);
	    fhRecoJetEta->Fill((*jeteta_akpu3pf)[indexjets]);
	    fhRecoJetPhi->Fill((*jetphi_akpu3pf)[indexjets]);
             
            for (int indexDm = 0; indexDm < Dsize; indexDm++) {
		if((*Dgen)[indexDm] == 23333) {            
            	    Delta_Phi->Fill((*jetphi_akpu3pf)[indexjets]-(*Dpt)[indexDm]);
		}//loop over D meson
            }
        }//end of selection over jets
      }
      for(int indexd=0;indexd<Dsize;indexd++) {
        if((*Dgen)[indexd]==23333) {
	  D_Pt_sig->Fill((*Dpt)[indexd]);
	  D_Eta_sig->Fill((*Deta)[indexd]);
	  D_Phi_sig->Fill((*Dphi)[indexd]);
	  DsvpvDist_sig->Fill((*DsvpvDistance)[indexd]);
	  Dalpha_sig->Fill((*Dalpha)[indexd]);
	  Dchi2cl_sig->Fill((*Dchi2cl)[indexd]);
	  Dtrk1_Pt_sig->Fill((*Dtrk1Pt)[indexd]);
	  Dtrk2_Pt_sig->Fill((*Dtrk2Pt)[indexd]);
	  Dtrk1_Eta_sig->Fill((*Dtrk1Eta)[indexd]);
	  Dtrk2_Eta_sig->Fill((*Dtrk2Eta)[indexd]);
	}
	else {
	  D_Pt_bkg->Fill((*Dpt)[indexd]);
	  D_Eta_bkg->Fill((*Deta)[indexd]);
	  D_Phi_bkg->Fill((*Dphi)[indexd]);
	  DsvpvDist_bkg->Fill((*DsvpvDistance)[indexd]);
	  Dalpha_bkg->Fill((*Dalpha)[indexd]);
	  Dchi2cl_bkg->Fill((*Dchi2cl)[indexd]);
	  Dtrk1_Pt_bkg->Fill((*Dtrk1Pt)[indexd]);
	  Dtrk2_Pt_bkg->Fill((*Dtrk2Pt)[indexd]);
	  Dtrk1_Eta_bkg->Fill((*Dtrk1Eta)[indexd]);
	  Dtrk2_Eta_bkg->Fill((*Dtrk2Eta)[indexd]);
	}
      }
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
