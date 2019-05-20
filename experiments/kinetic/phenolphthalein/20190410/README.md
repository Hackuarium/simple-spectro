# Phenolphathalein

Kinetic of degradation of phenolphthalein in basic media works well as shown in the [previous experiment](../20190406/README.md).

## Goal

We want to measure the order of the reaction. In the literature, it is told that you are expected to use constant ionic force. But is this necessary ?

Let's check if we replace NaCl 0.3M by water to see if it yields to the same result.

## Solutions

- solution A: NaOH 0.3M in water
- solution B: water
- solution C: phenolphthalein 3.02 g/L in MeOH / EtOH

| Experiment | A    | B    | C     |
| ---------- | ---- | ---- | ----- |
| 1          | 4 mL | 0 mL | 40 µL |
| 2          | 3 mL | 1 mL | 20 µL |
| 3          | 2 mL | 2 mL | 20 µL |
| 4          | 1 mL | 3 mL | 20 µL |

## Results

Raw data for the 4 kinetics are attached in the corresponding documents:

- [Experiment 1](exp1.txt)
- [Experiment 2](exp2.txt)
- [Experiment 3](exp3.txt)
- [Experiment 4](exp4.txt)

The data were processed online on the [following page](https://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log).

An exponential regression has been applied for the 4 experiments for all the points having an absorbance over 0.3 and the following results are observed:

| Experiment | [NaOH]  | k      | r<sup>2</sup> |
| ---------- | ------- | ------ | ------------- |
| 1          | 0.300 M | 0.2878 | 0.99997       |
| 2          | 0.225 M | 0.1984 | 0.99998       |
| 3          | 0.150 M | 0.1217 | 0.99997       |
| 4          | 0.075 M | 0.0460 | 0.99959       |

## What is r<sup>2</sup> ???

## NaOH regression

<img src="NaOHregression.svg">

- y = −0.03705 + 1.069 x
- r<sup>2</sup> = 0.9983

Even without constant ionic strength the results are still quite good. The slope is close to 1 despite the fact that it is far from passing through 0,0.
