void shapefits2() {
  gStyle->SetOptStat(kFALSE); 

  TFile *tf=new TFile("mydata.root");

  TH1F *data=(TH1F*)tf->Get("data");   // data histogram
  TH1F *mc0=(TH1F*)tf->Get("back1");   // first MC histogram
  TH1F *mc1=(TH1F*)tf->Get("back2");   // second MC histogram
  TH1F *msig=(TH1F*)tf->Get("signal"); // signal model

  TObjArray *mc = new TObjArray(3);        // MC histograms are put in this array
  mc->Add(mc0);
  mc->Add(mc1);
  mc->Add(msig);
  TFractionFitter* fit = new TFractionFitter(data, mc); // initialize
  fit->Constrain(1,0.0,0.9);              // example to constrain fraction of mc1 to be between 0 and 0.9
  //fit->SetRangeX(1,15);                // example to use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  cout << "fit status: " << status << endl;
  TH1F *result;
  if (status == 0) {                       // check on fit status
    result = (TH1F*) fit->GetPlot();
    result->SetLineWidth(3);
    data->Draw("Ep");
    result->Draw("same");
  }

  Double_t params[3], errors[3];
  Double_t ndata=data->Integral();
  fit->GetResult(0,params[0],errors[0]);
  fit->GetResult(1,params[1],errors[1]);
  fit->GetResult(2,params[2],errors[2]);

  TH1F* h0=(TH1F*)fit->GetMCPrediction(0);
  TH1F* h1=(TH1F*)fit->GetMCPrediction(1);
  TH1F* h2=(TH1F*)fit->GetMCPrediction(2);

   
  h0->Scale( 1./h0->Integral() * params[0]*ndata );
  h0->SetLineColor(kGreen-2);
  h0->SetLineWidth(4);
  TH1F *h00=(TH1F*)h0->Clone();
  h0->SetFillColor(kGreen);
  h0->SetFillStyle(3003);
  

  h1->Scale( 1./h1->Integral() * params[1]*ndata );
  h1->SetLineColor(kBlue-2);
  h1->SetLineWidth(4);
  TH1F *h11=(TH1F*)h1->Clone();
  h1->SetFillColor(kBlue);
  h1->SetFillStyle(3003);

  h2->Scale( 1./h2->Integral() * params[2]*ndata );
  h2->SetLineColor(kRed-2);
  h2->SetLineWidth(4);
  TH1F *h22=(TH1F*)h2->Clone();
  h2->SetFillColor(kRed);
  h2->SetFillStyle(3003);
 
  THStack *hs=new THStack("hs","stacked MC histograms");
  hs->Add(h0);
  hs->Add(h1);
  hs->Add(h2);

  hs->Draw("nostack,same,hist");
  h00->Draw("same");
  h11->Draw("same");
  data->Draw("Ep,same");
  result->Draw("same");

  TLegend *leg = new TLegend(0.1,0.7,0.45,0.9);
  leg->AddEntry(data,"Data","EL");
  leg->AddEntry(result,"Fit","L");
  leg->AddEntry(h2,"Signal");
  leg->AddEntry(h0,"Background 1");
  leg->AddEntry(h1,"Background 2");

  leg->Draw();

  
  cout << endl;
  cout << "***** Signal summary *****" << endl;
  cout << "Number of signal events = " << h2->Integral() 
       << " +- " << errors[2]* h2->Integral() << endl;

}


