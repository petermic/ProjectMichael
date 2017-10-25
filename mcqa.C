#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "d_jet.C"
#include <vector>
#include "TString.h"

void mcqa(){
	TFile *data = new TFile("DjetFiles_20170506_pp_5TeV_TuneCUETP8M1_Dfinder_MC_20170404_pthatweight.root");
	djet* tMC = new djet(data->GetName());
	tMC->loop(0);
	tMC->d_jet("output.root");
	TFile *f = new TFile("output.root");

	TTree *t = (TTree*)data->Get("djt");

	std::vector<TString> dataplots;
	dataplots.insert(dataplots.end(),
		{"PVx",
		"PVy",
		"PVz",
		"BSx",
		"BSy",
		"BSz"});

	std::vector<TString> fplots;
	fplots.insert(fplots.end(),
		{"D_Pt_sig",
		"D_Pt_bkg",
		"D_Eta_sig",
		"D_Eta_bkg",
		"D_Phi_sig",
		"D_Phi_bkg",
		"DsvpvDist_sig",
		"DsvpvDist_bkg",
		"Dchi2cl_sig",
		"Dchi2cl_bkg",
		"Dalpha_sig",
		"Dalpha_bkg",
		"Dtrk1Pt_sig",
		"Dtrk1Pt_bkg",
		"Dtrk2Pt_sig",
		"Dtrk2Pt_bkg",
		"Dtrk1Eta_sig",
		"Dtrk1Eta_bkg",
		"Dtrk2Eta_sig",
		"Dtrk2Eta_bkg",
		"fhRecoJetPt",
		"fhRecoJetEta",
		"fhRecoJetPhi"});
	std::vector<TH1F*> fhist;
	for(int i=0;i<fplots.size();i++) fhist.push_back((TH1F*)f->Get(fplots[i]));

	for(int i=0;i<fhist.size();i++){		
		TH1F *h = fhist[i];
		Double_t size = h->GetEntries();
		h->Scale(1./size);}
	std::vector<TString> fnames;
	fnames.insert(fnames.end(),
		{"D p_t",
		"D #eta",
		"D #phi",
		"Dsvpvdist",
		"#chi^{2}_{cl}",
		"#alpha",
		"Track 1 Pt",
		"Track 2 Pt",
		"Track 1 Eta",
		"Track 2 Eta",
		"Jet p_t",
		"Jet #eta",
		"Jet #phi"});
	std::vector<TString> datanames;
	datanames.insert(datanames.end(),
		{"PVx",
		"PVy",
		"PVz",
		"BSx",
		"BSy",
		"BSz"});
	
	gStyle->SetOptStat(0);	

	TCanvas *fulld = new TCanvas("Reconstructed D","Reconstructed D",900,600);
	fulld->Divide(3,2,0.01,0.01);

	TCanvas *dtrk = new TCanvas("D Tracks","D Tracks",600,600);
	dtrk->Divide(2,2,.01,.01);

	TCanvas *jets = new TCanvas("Jets","Jets",900,300);
	jets->Divide(3,1,.01,.01);

	for(int i=0;i<fnames.size();i++)
	{
		if(i<6) fulld->cd(i+1);
		else if(i<10) dtrk->cd(i-5);
		else jets->cd(i-9);
		if(i<10)
		{
			fhist[2*i]->SetTitle(fnames[i]);
			fhist[2*i]->SetFillColorAlpha(kBlue,0.6);
			fhist[2*i]->Draw("E3");
			fhist[2*i+1]->SetFillColorAlpha(kRed,0.6);
			fhist[2*i+1]->Draw("E3 same");
		}
		else
		{
			fhist[i+10]->SetTitle(fnames[i]);
			fhist[i+10]->SetFillColor(kBlue);
			fhist[i+10]->Draw("E3");
		}
		if(i+1==3 || i+1==8)
		{
			TLegend *legd = new TLegend(0.75,0.75,0.95,0.95);
			legd->AddEntry(fhist[2*i],"Signal","f");
			legd->AddEntry(fhist[2*i+1],"Background","f");
			legd->Draw();	
		}
	}

	TCanvas *pv = new TCanvas("Vertex & Beamspot","Vertex & Beamspot",900,600);
	pv->Divide(3,2,.01,.01);

	gStyle->SetOptFit(0111);

	for(int i=0;i<dataplots.size();i++)
	{
		pv->cd(i+1);
		t->Draw(dataplots[i]);
		if(i<3) t->Fit("gaus",dataplots[i]);
	}
	fulld->SaveAs("d_reco.gif");
	dtrk->SaveAs("d_trk.gif");
	pv->SaveAs("PVdist.gif");
	jets->SaveAs("jets.gif");
}
