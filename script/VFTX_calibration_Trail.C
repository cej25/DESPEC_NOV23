#define VFTX_SN 11000
TFile *fin = new TFile("rootfile/hist_sofiavftx_calib.root");
void VFTXCalibration(int module, int channel,bool plot =false);
		     
void run(){
  fin->cd("Histograms/Unpack/VFTX_0/FineTime/Trailing/");
  for(int ch=0;ch<16;ch++)
    VFTXCalibration(0,ch);
}
void VFTXCalibration(int module, int channel,bool plot =false) {
  fin->cd("Histograms/Unpack/VFTX_0/FineTime/Trailing/");
  printf("Calibration, channel %02d\n", channel);
  TH1F* h = (TH1F*)gDirectory->Get(Form("VFTX0_FineTime_trailing_ch%02d",channel));
  TCanvas *c;
  if(plot){
    c= new TCanvas();
    c->Divide(2,1);
    c->cd(1);
    h->Draw();
  }
  
  double integral_ft;
  int    FirstBin_ft;
  double integral [1000];
  double calib[1000];
  double bins[1000];
  for (int bin=0; bin<=1000; bin++) {
    calib[bin-1] = 0. ;
    integral [bin-1] = 0. ;
    bins [bin-1] = bin ;
  }
  std::ofstream f_int;
  std::ofstream f_cal;
  f_cal.open(Form("TrailBin2Ps/VFTX_%05d_Bin2Ps_ch%02d.dat",VFTX_SN,channel),std::ios::out);
  f_int.open(Form("TrailBin2Ps/INT/VFTX_%05d_INT_ch%02d.txt",VFTX_SN,channel),std::ios::out);
  // calculation of the integral
  integral_ft     = (double)h->Integral(5,1000);
  // calculation of the first bin
  FirstBin_ft = 1 ;
  for (int bin=2; bin<=1000; bin++)     {
    if (h->GetBinContent(bin)>0) {
      FirstBin_ft = bin;
      break;
    }
  }//end of for(bin)
  
  // calculation of the calibration parameters
  if(integral_ft>0){
    for (int bin=FirstBin_ft; bin<=1000; bin++) {
      integral[bin-1]  = integral[bin-2]+h->GetBinContent(bin);
      calib[bin-1]     = (integral[bin-1]*5000.)/integral_ft ;
    }
  }//end of if spectrum not empty
  //SAVE
  TGraph* g;
  if(plot){
    g = new TGraph(1000,bins,calib);
    c->cd(2);
    g->Draw("AP");
  }
  for(int bin=1; bin<=1000;bin++)       {
    f_cal <<std::setw(4) <<bin-1 <<" " <<std::setw(15) <<std::fixed <<std::setprecision(9) <<calib[bin-1]    <<std::endl;
    f_int <<std::setw(4) <<bin-1 <<" " <<std::setw(15) <<std::fixed <<std::setprecision(9) <<integral[bin-1] <<std::endl;
  }
  f_cal.close();
  f_int.close();
  return;
}
