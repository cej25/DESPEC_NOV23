void Z1Z2_Pt()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Thu May 12 06:17:50 2022) by ROOT version 6.22/08
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,958,538,315);
   Canvas_1->Range(77.94579,77.89585,79.26334,79.42589);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_Z2_Gate1",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,78.40833,79.17088);
   cutg->SetPoint(1,78.16538,78.83088);
   cutg->SetPoint(2,78.20276,78.32086);
   cutg->SetPoint(3,78.6326,78.15086);
   cutg->SetPoint(4,78.89424,78.29253);
   cutg->SetPoint(5,79.04375,78.91588);
   cutg->SetPoint(6,78.78211,79.17088);
   cutg->SetPoint(7,78.40833,79.17088);
   cutg->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.4461567,0.9336582,0.5538433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Graph");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
