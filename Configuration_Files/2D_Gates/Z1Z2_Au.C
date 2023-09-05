void Z1Z2_Au()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Thu May 12 06:18:27 2022) by ROOT version 6.22/08
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,958,538,315);
   Canvas_1->Range(78.67346,78.82724,80.11116,80.18068);
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
   cutg->SetPoint(0,79.21162,79.86708);
   cutg->SetPoint(1,78.91308,79.51496);
   cutg->SetPoint(2,79.14877,79.07482);
   cutg->SetPoint(3,79.58872,79.05282);
   cutg->SetPoint(4,79.8244,79.51496);
   cutg->SetPoint(5,79.87154,79.71303);
   cutg->SetPoint(6,79.573,79.95511);
   cutg->SetPoint(7,79.21162,79.86708);
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
