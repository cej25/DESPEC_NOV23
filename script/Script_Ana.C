#include "TFRSAnlEvent.h"

#include "TFile.h"
#include "TTree.h"

#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TTreeReaderValue.h"

#include "TString.h"
#include "Riostream.h"

#include "TEventList.h"

#include <vector>

#include "TH1F.h"
#include "TH2F.h"
#include "TCutG.h"

int Script_Ana(const TString& name_In, const TString& name_Out)
{
  TFile* file_In = TFile::Open(name_In);
  if(file_In == nullptr)
    {
      std::cout<<"E> no file found ! "<<name_In<<"\n";
      return -1;
    }
  
  TTree* InTree = dynamic_cast<TTree*>(file_In->Get("AnalysisxTree"));
  assert(InTree != nullptr);
  //InTree->Print();
  
  TTreeReader AnaReader(InTree);

  TTreeReaderValue<TFRSAnlEvent> ReaderEvent(AnaReader,"FRSAnlEvent.");

  //hdEdegoQ_Z = MakeH2I("ID/ID_S4","ID_dEdegoQ_Z", 450,50,95, 400, 0.1,0.8, "Z from MUSIC41", "dE(S2deg)/Q [a.u.]", 2);
  //hID_Z1_Z2 = MakeH2I("ID/ID_S4","ID_Z_Z2", 350,1,30, 350,1,30,"Z", "Z2", 2);
  // std::unordered_map<std::string,std::unordered_map<std::string, std::tuple<std::string, int, double, double> > > Hindexes =
  //    {
  //      {"ID_dEdegoQ_Z", { {"id_Z",{"Z from MUSIC41",450,50.95.}},{"dEdegoQ".{"dE(S2deg)/Q [a.u.]",400,0.1,0.8}} }},
  //      {"ID_Z_Z2", { {"Z",{"id_Z",350,1.,30.}}, {"Z2",{"id_Z2",350,1.,30.}} }},
  //    };
  // std::vector<std::string> Ncuts = {"_all","_accepted","_rejected"};
  std::vector<TH1*> allHists;
     
  TH2F* h_Z_Z2_all = new TH2F("ID_Z_Z2_all","ID_Z_Z2_all;id_Z2;id_Z",900,1.,90.,900,1.,90.);
  allHists.emplace_back(h_Z_Z2_all);
  TH2F* h_Z_Z2_acc = new TH2F("ID_Z_Z2_accepted","ID_Z_Z2_accepted;id_Z2;id_Z",900,1.,90.,900,1.,90.);
  allHists.emplace_back(h_Z_Z2_acc);
  TH2F* h_Z_Z2_rej = new TH2F("ID_Z_Z2_rejected","ID_Z_Z2_rejected;id_Z2;id_Z",900,1.,90.,900,1.,90.); 
  allHists.emplace_back(h_Z_Z2_rej);
  
  TH1F* h_Z_all = new TH1F("ID_Z_all","ID_Z_all;id_Z",900,1.,90.);
  allHists.emplace_back(h_Z_all);
  TH1F* h_Z_acc = new TH1F("ID_Z_accepted","ID_Z_accepted;id_Z",900,1.,90.);
  allHists.emplace_back(h_Z_acc);
  TH1F* h_Z_rej = new TH1F("ID_Z_rejected","ID_Z_rejected;id_Z",900,1.,90.);
  allHists.emplace_back(h_Z_rej);
  
  TH1F* h_Z2_all = new TH1F("ID_Z2_all","ID_Z2_all;id_Z2",900,1.,90.);
  allHists.emplace_back(h_Z2_all);
  TH1F* h_Z2_acc = new TH1F("ID_Z2_accepted","ID_Z2_accepted;id_Z2",900,1.,90.);
  allHists.emplace_back(h_Z2_acc);
  TH1F* h_Z2_rej = new TH1F("ID_Z2_rejected","ID_Z2_rejected;id_Z2",900,1.,90.);
  allHists.emplace_back(h_Z2_rej);
  
  TH2F* h_dEdegoQ_Z_all = new TH2F("ID_dEdegoQ_Z_all","ID_dEdegoQ_Z_all;dE(S2deg)/Q [a.u.];Z from MUSIC41;",400,0.1,0.8,450,50.,95.);
  allHists.emplace_back(h_dEdegoQ_Z_all);
  TH2F* h_dEdegoQ_Z_acc = new TH2F("ID_dEdegoQ_Z_acc","ID_dEdegoQ_Z_accepted;dE(S2deg)/Q [a.u.];Z from MUSIC41;",400,0.1,0.8,450,50.,95.);
  allHists.emplace_back(h_dEdegoQ_Z_acc);
  TH2F* h_dEdegoQ_Z_rej = new TH2F("ID_dEdegoQ_Z_rej","ID_dEdegoQ_Z_rejected;dE(S2deg)/Q [a.u.];Z from MUSIC41;",400,0.1,0.8,450,50.,95.);
  allHists.emplace_back(h_dEdegoQ_Z_rej);
  
  TH1F* h_id_ZQ_all = new TH1F("ID_ZQ_all","ID_ZQ_all;Z from MUSIC41;",450,50.,95.);
  allHists.emplace_back(h_id_ZQ_all);
  TH1F* h_id_ZQ_acc = new TH1F("ID_ZQ_acc","ID_ZQ_accepted;Z from MUSIC41;",450,50.,95.);
  allHists.emplace_back(h_id_ZQ_acc);
  TH1F* h_id_ZQ_rej = new TH1F("ID_ZQ_rej","ID_ZQ_rejected;Z from MUSIC41;",450,50.,95.);
  allHists.emplace_back(h_id_ZQ_rej);
    
  TH1F* h_dEdegoQ_all = new TH1F("ID_dEdegoQ_all","ID_dEdegoQ_all;dE(S2deg)/Q [a.u.];",400,0.1,0.8);
  allHists.emplace_back(h_dEdegoQ_all);
  TH1F* h_dEdegoQ_acc = new TH1F("ID_dEdegoQ_accepted","ID_dEdegoQ_accepted;dE(S2deg)/Q [a.u.];",400,0.1,0.8);
  allHists.emplace_back(h_dEdegoQ_acc);
  TH1F* h_dEdegoQ_rej = new TH1F("ID_dEdegoQ_rejected","ID_dEdegoQ_rejected;dE(S2deg)/Q [a.u.];",400,0.1,0.8);
  allHists.emplace_back(h_dEdegoQ_rej);

  
  //TH2F* h_cutIsotope = new TH2F("h_cutIsotope","h_cutIsotope",20,0,20,
  
  for(auto hist : allHists)
    hist->SetDirectory(0);
  
  std::vector<double> x1(5), y1(5);
  x1[0]=0.507863; y1[0]=81.3092;
  x1[1]=0.439493; y1[1]=69.0018;
  x1[2]=0.473826; y1[2]=68.0687;
  x1[3]=0.542196; y1[3]=79.5764;
  x1[4]=0.507863; y1[4]=81.3092;

  std::vector<double> x2(5), y2(5);
  x2[0]=79.4248; y2[0]=79.9763;
  x2[1]=60.7192; y2[1]=61.2263;
  x2[2]=61.2224; y2[2]=60.3821;
  x2[3]=80.2831; y2[3]=79.4876;
  x2[4]=79.4248; y2[4]=79.9763;

  std::vector<TCutG*> all_cuts;
  
  TCutG* cutZ_dE = new TCutG("Z_dE");
  cutZ_dE->SetVarX("id_dEdegoQ");
  cutZ_dE->SetVarY("id_z");
  cutZ_dE->SetFillStyle(1000);
  for(size_t i=0;i<x1.size();++i)
    cutZ_dE->SetPoint(i,x1[i],y1[i]);
  all_cuts.emplace_back(cutZ_dE);
  
  TCutG* cutZ2_Z = new TCutG("Z2_Z");
  cutZ2_Z->SetVarX("id_z2");
  cutZ2_Z->SetVarY("id_z");
  cutZ2_Z->SetFillStyle(1000);
  for(size_t i=0;i<x2.size();++i)
    cutZ2_Z->SetPoint(i,x2[i],y2[i]);
  all_cuts.emplace_back(cutZ2_Z);
  
   TCutG *cut_e0e0 = new TCutG("e0e0",7);
   cut_e0e0->SetVarX("id_z");
   cut_e0e0->SetVarY("id_dEdegoQ");
   cut_e0e0->SetFillStyle(1000);
   cut_e0e0->SetPoint(0,76.3782,0.496424);
   cut_e0e0->SetPoint(1,68.1297,0.418101);
   cut_e0e0->SetPoint(2,65.3216,0.385348);
   cut_e0e0->SetPoint(3,70.4112,0.398165);
   cut_e0e0->SetPoint(4,76.7292,0.443734);
   cut_e0e0->SetPoint(5,80.5903,0.477911);
   cut_e0e0->SetPoint(6,76.3782,0.496424);
   all_cuts.emplace_back(cut_e0e0);

   TCutG* cut_Ir = new TCutG("Ir",5);
   cut_Ir->SetVarX("id_AoQ");
   cut_Ir->SetVarY("id_z");
   cut_Ir->SetFillStyle(1000);
   cut_Ir->SetPoint(0,2.57136,77.2987);
   cut_Ir->SetPoint(1,2.57195,76.5505);
   cut_Ir->SetPoint(2,2.63164,76.1764);
   cut_Ir->SetPoint(3,2.62888,77.3255);
   cut_Ir->SetPoint(4,2.57136,77.2987);
   all_cuts.emplace_back(cut_Ir);

   TCutG* cut_W = new TCutG("W",7);
   cut_W->SetVarX("id_AoQ");
   cut_W->SetVarY("id_z");
   cut_W->SetFillStyle(1000);
   cut_W->SetPoint(0,2.62356,74.5463);
   cut_W->SetPoint(1,2.62317,73.6377);
   cut_W->SetPoint(2,2.56801,73.7713);
   cut_W->SetPoint(3,2.55875,74.0118);
   cut_W->SetPoint(4,2.56309,74.8402);
   cut_W->SetPoint(5,2.58948,74.6532);
   cut_W->SetPoint(6,2.62356,74.5463);
   all_cuts.emplace_back(cut_W);

   TCutG* cut_Re = new TCutG("Re",6);
   cut_Re->SetVarX("id_AoQ");
   cut_Re->SetVarY("id_z");
   cut_Re->SetFillStyle(1000);
   cut_Re->SetPoint(0,2.56959,75.6686);
   cut_Re->SetPoint(1,2.56998,74.9738);
   cut_Re->SetPoint(2,2.60564,74.5463);
   cut_Re->SetPoint(3,2.62534,74.5463);
   cut_Re->SetPoint(4,2.62573,75.3747);
   cut_Re->SetPoint(5,2.56959,75.6686);
   all_cuts.emplace_back(cut_Re);

   TCutG* cut_Pt = new TCutG("Pt",6);
   cut_Pt->SetVarX("id_AoQ");
   cut_Pt->SetVarY("id_z");
   cut_Pt->SetFillStyle(1000);
   cut_Pt->SetPoint(0,2.5755,78.0203);
   cut_Pt->SetPoint(1,2.61529,78.1271);
   cut_Pt->SetPoint(2,2.62888,77.8599);
   cut_Pt->SetPoint(3,2.62199,77.3789);
   cut_Pt->SetPoint(4,2.56801,77.2987);
   cut_Pt->SetPoint(5,2.5755,78.0203);
   all_cuts.emplace_back(cut_Pt);

   TCutG* cut_Os = new TCutG("Os",6);
   cut_Os->SetVarX("id_AoQ");
   cut_Os->SetVarY("id_z");
   cut_Os->SetFillStyle(1000);
   cut_Os->SetPoint(0,2.57176,76.3634);
   cut_Os->SetPoint(1,2.57176,75.8023);
   cut_Os->SetPoint(2,2.62415,75.3747);
   cut_Os->SetPoint(3,2.62534,76.2565);
   cut_Os->SetPoint(4,2.57156,76.6039);
   cut_Os->SetPoint(5,2.57176,76.3634);
   all_cuts.emplace_back(cut_Os);

   std::vector<TEventList*> lists_SelectedEvents; 
   for(auto* cut : all_cuts)
     {
       TString name_sel_temp("Selected_from_");
       name_sel_temp+= cut->GetName();
       lists_SelectedEvents.emplace_back(new TEventList(name_sel_temp,name_sel_temp));
       lists_SelectedEvents.back()->SetDirectory(0);
     }
  // TTreeReaderArray<UInt_t> Reader_scaler_frs(AnaReader, "FRSUnpackEvent.scaler_frs");
  // if(!CheckValue(Reader_scaler_frs))
  //   std::cout<<"E> Reader_scaler_frs not found and loaded in TreeReader !\n";

  // TTreeReaderValue<Int_t> Reader_qlength(AnaReader, "FRSUnpackEvent.qlength");
  // if(!CheckValue(Reader_qlength))
  //   std::cout<<"E> Reader_qlength not found and loaded in TreeReader !\n";


  //AnaReader.SetEntriesRange(0,10);
  const auto Entries = InTree->GetEntries();
  std::cout << " Entries :" << Entries << std::endl;
  int timing = 0;
  
  while(AnaReader.Next())
    {
      Long64_t iEntry = AnaReader.GetCurrentEntry();
      if(static_cast<int>(static_cast<double>(iEntry) / static_cast<double>(Entries) * 10) == timing)
	{
	  std::cout << "Processing :" << timing * 10 << "% \n";
	  ++timing;
	}
      

      //std::cout<<"event #"<<id_event<<" scaler : ";
      // for(UInt_t frs_scaler : Reader_scaler_frs)
      // 	std::cout<<frs_scaler<<" ";

      // std::cout<<" | qlength = "<<*Reader_qlength<<" \n";
      //for(UInt_t frs_scaler : ReaderEvent->scaler_frs)
      //std::cout<<frs_scaler<<" ";

      //std::cout<<" | qlength = "<<ReaderEvent->qlength<<" \n";

      double dEdegoQ = ReaderEvent->id_dEdegoQ;
      double Z1 = ReaderEvent->id_z;
      double Z2 = ReaderEvent->id_z2;
      double AoQ = ReaderEvent->id_AoQ;

      
	
      h_dEdegoQ_all->Fill(dEdegoQ);
      h_id_ZQ_all->Fill(Z1);
      h_Z_all->Fill(Z1);
      h_Z2_all->Fill(Z2);

      h_dEdegoQ_Z_all->Fill(dEdegoQ,Z1);
      h_Z_Z2_all->Fill(Z2,Z1);
      
      if(cutZ_dE->IsInside(dEdegoQ,Z1)==1)
	{
	  h_dEdegoQ_acc->Fill(dEdegoQ);
	  h_id_ZQ_acc->Fill(Z1);
	  h_dEdegoQ_Z_acc->Fill(dEdegoQ,Z1);
	  lists_SelectedEvents[0]->Enter(iEntry);
	}
      else
	{
	  h_dEdegoQ_rej->Fill(dEdegoQ);
	  h_id_ZQ_rej->Fill(Z1);
	  h_dEdegoQ_Z_rej->Fill(dEdegoQ,Z1);
	}

      if(cutZ2_Z->IsInside(Z2,Z1)==1)
	{
	  h_Z_acc->Fill(Z1);
	  h_Z2_acc->Fill(Z2);
	  h_Z_Z2_acc->Fill(Z2,Z1);
	  lists_SelectedEvents[1]->Enter(iEntry);
      	}
      else
	{
	  h_Z_rej->Fill(Z1);
	  h_Z2_rej->Fill(Z2);
	  h_Z_Z2_rej->Fill(Z2,Z1);
	}

      if(cut_e0e0->IsInside(Z1,dEdegoQ)==1)
	{
	  lists_SelectedEvents[2]->Enter(iEntry);
	  if(cut_Ir->IsInside(AoQ,Z1)==1)
	    lists_SelectedEvents[3]->Enter(iEntry);
	  if(cut_W->IsInside(AoQ,Z1)==1)
	    lists_SelectedEvents[4]->Enter(iEntry);
	  if(cut_Re->IsInside(AoQ,Z1)==1)
	    lists_SelectedEvents[5]->Enter(iEntry);
	  if(cut_Pt->IsInside(AoQ,Z1)==1)
	    lists_SelectedEvents[6]->Enter(iEntry);
	  if(cut_Os->IsInside(AoQ,Z1)==1)
	    lists_SelectedEvents[7]->Enter(iEntry);
	}
      
    }

  TFile* f_out = new TFile(name_Out,"RECREATE");
  f_out->cd();
  //cutZ_dE->Write();
  //cutZ2_Z->Write();
  for(auto cut : all_cuts)
    cut->Write();
  for(auto hist : allHists)
    hist->Write();
  f_out->Close();

  TString name_Out_sel("EventList_");
  name_Out_sel+=name_Out;
  TFile* f_out2= new TFile(name_Out_sel, "RECREATE");
  f_out2->cd();
  for(auto list : lists_SelectedEvents)
    list->Write();
  f_out2->Close();
  
  return 0;
}

int main(int argc, char** argv)
{
  if(argc != 3)
    {
      std::cout<<"E> Wrong number of parameters!\n";
      return -1;
    }

  TString nameIn(argv[1]);
  TString nameOut(argv[2]);

  std::cout<<" Processing "<<nameIn<<" in "<<nameOut<<"\n";

  return Script_Ana(nameIn,nameOut);
  
}
