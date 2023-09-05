void ShowTDiff(){
  TFile *fin = new TFile("rootfile/h_s2vftx_test16ch_4group.root");
  fin->cd("Histograms/Unpack/VFTX_0/TimeDiff/");
  TH1F* h[16];
  TCanvas* c = new TCanvas();
  c->Divide(4,4);
  for(int i=0;i<16;i++){
    c->cd(1+i);
    h[i] = (TH1F*)gDirectory->Get(Form("VFTX0_TimeDiff2Ch0_leading_ch%02d",i));
    h[i]->Draw();
    int binmax = h[i]->GetMaximumBin();
    double xmax = h[i]->GetXaxis()->GetBinCenter(binmax);
    h[i]->GetXaxis()->SetRangeUser(xmax-100,xmax+100);
    cout << "channel " << i << ", sigma = " << h[i]->GetRMS() << endl;
  }
}
void ShowTDiff_Event(int ref=0){
  if(!(ref==0) && !(ref==8)){
    cout << "reference channel not available" << endl;
  }
  TFile *fin = new TFile("rootfile/h_s2vftx_test16ch_4group.root");
  fin->cd("Histograms/Unpack/VFTX_0/TimeDiff_Event/");
  TH1F* h[16];
  TH2F* h2[16];
  TCanvas* c = new TCanvas();
  c->Divide(4,4);
  for(int i=0;i<16;i++){
    c->cd(1+i);
    h2[i] = (TH2F*)gDirectory->Get(Form("VFTX0_TimeDiff2Ch%d_event_ch%02d",ref,i));
    h2[i]->Draw("colz");
    h[i] = (TH1F*)h2[i]->ProjectionY(Form("hp_%02d",i));
    int binmax = h[i]->GetMaximumBin();
    double xmax = h[i]->GetXaxis()->GetBinCenter(binmax);
    h2[i]->GetYaxis()->SetRangeUser(xmax-200,xmax+200);
    //cout << "channel " << i << ", sigma = " << h[i]->GetRMS() << endl;
  }
}
