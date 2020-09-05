//This program is written to access histograms from root files and plot them within same canvas
//Chandan Ghosh July 3 2020
//
//
TCanvas *c1 =  new TCanvas("C1","c1",800,600);
string outfile = "outfile.pdf";
const int nEnergy = 4;
const int nMaterial = 1;
const int nParticle = 2;
//void analyOneMaterial(string material, double energy, string particle);
TH1D* extractOneFile(double energy, string particle, string materials, string histo);

void analyze()
{
//	gStyle->SetOptStat(0);
	string materials[nMaterial]={"Cu_Water"};
	int colorMat[nEnergy] = {1,2,4,6};//1-black, 2-red,4-blue,6 -magnta
	int Marker[nParticle] = {24,20};
	double energy[nEnergy] = {100,10,5,1};
	//string particle[nParticle]={"ele","posi"};
	string particle[nParticle]={"posi","ele"};
	//c1->Print(Form("%s[",outfile.c_str()),"pdf");
	c1->Divide(1,2);
	for(int ij=0;ij<nMaterial;ij++)
	{
		for(int ip=0;ip<2;ip++)
		{
			for(int ik=0;ik<nEnergy;ik++)
			{
				TH1D* testhis = extractOneFile(energy[ik], particle[ip], materials[ij], "h8");
//				testhis->SetTitle(Form("Long. Energy profile"));
//		         	testhis->SetTitle(Form("Radial Energy profile"));
				testhis->SetMarkerStyle(Marker[ip]);
				testhis->SetMarkerStyle(Marker[ip]);
				testhis->SetMarkerColor(colorMat[ik]);
				//c1->SetLogy();
//				testhis->GetXaxis()->SetRangeUser(0,1.5);
//				testhis->GetXaxis()->SetRangeUser(0,15);
				if(ik==0 || ik==1)
				{
					c1->cd(1);
				        gPad->SetLogy(1);
					if(ij==0 && ip==0 && ik==0)
						testhis->Draw("hist p");
					else
						testhis->Draw("hist p same");
				}
				else
				{
					c1->cd(2);
					gPad->SetLogy(1);
					if(ij==0 && ip==0 && ik==2)
						testhis->Draw("hist p");
					else
						testhis->Draw("hist p same");
				}
			}
		}
	}
//	c1->SaveAs(Form("Cu_Water_Radial.png"));
//	c1->SaveAs(Form("Cu_Water_Long.png"));
//	c1->SaveAs(Form("Cu_Water_EnergyDepositionSlanting.png"));
}


TH1D* extractOneFile(double energy, string particle, string materials, string histo)
{
	string infile = Form("./%s_%0.0fMeV_%s_slanting.root",materials.c_str(),energy,particle.c_str());
	TFile *fin = TFile::Open(infile.c_str(),"READ");
        TH1D* hist = (TH1D*)fin->Get(Form("%s",histo.c_str()));
	std::cout<<"Reading file :: "<<infile.c_str()<<" and histogram "<<histo.c_str()<<std::endl; 
	return hist;
}

