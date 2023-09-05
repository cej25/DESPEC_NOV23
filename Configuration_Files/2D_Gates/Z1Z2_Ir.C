void Z1Z2_Ir()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Thu May 12 06:17:20 2022) by ROOT version 6.22/08
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,958,538,315);
   Canvas_1->Range(76.91585,77.17011,78.38296,78.50704);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_Z2_Gate0",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,77.46132,78.19509);
   cutg->SetPoint(1,77.16037,77.86086);
   cutg->SetPoint(2,77.41116,77.41522);
   cutg->SetPoint(3,77.8375,77.39294);
   cutg->SetPoint(4,78.08829,77.83858);
   cutg->SetPoint(5,78.13845,78.0614);
   cutg->SetPoint(6,77.8375,78.28422);
   cutg->SetPoint(7,77.46132,78.19509);
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
