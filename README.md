# Template fits

This repository includes an example of performing a template fir to data.  Expected distributions of multiple backgrounds and a signal source are modeled by Monte Carlo (simulated) histograms.

These shapes are adjusted to find the best agreement with the observed data and a nice plot is generated.  The fitting code is based on https://root.cern.ch/doc/master/classTFractionFitter.html


- shapefits.C: C++ example, usage: root shapefits.C
- shapefits2.C: C++ example, usage: root shapefits2.C  (this produces a slighly better looking plot)
- shapefits.ipynb: Jupyter Notebook illustrating the same fit in python code






