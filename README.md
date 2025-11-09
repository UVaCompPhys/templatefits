# Template fits

This repository includes an example of performing a template fit to data.  Expected distributions of multiple backgrounds and a signal source are modeled by Monte Carlo (simulated) histograms.

These normalizations of the different shapes are adjusted to find the best agreement with the observed data and a nice plot is generated.  The fitting code is based on https://root.cern.ch/doc/master/classTFractionFitter.html

Begin by generating a data set using
```root -q make_hists.C```

- shapefits.ipynb: Jupyter Notebook illustrating the the use of the template fitter
- shapefits.C: C++ example, usage: root shapefits.C
- shapefits2.C: C++ example, usage: root shapefits2.C  (this produces a slighly better looking plot)
- plot_inputs.C: C++ example to plot the histograms in the datafile

## A few additional comments

The basic example given here assume that the uncertainties on the bin contents of the model histograms are negligible (at least compared to the incertaintied on the data).  This can be a good assumption if models are derived from a high statistics simulation or control sample in the data.  If this assumpion is not valid, then the method risks being biased by statistical fluctuations in the models.  For example, stat fluftuations can be interpred as significant contributions to the shape of the model.

A way to protect against biases one can apply the [Barlow-Beeston](https://www.sciencedirect.com/science/article/abs/pii/001046559390005W?via%3Dihub) (or related methods) which, roughly speaking, simultaneously maximizes the likelihood of the data given the model, where the model is allowed to vary within statistical uncertainties.  





