# Phenolphathalein

The goal of this experiment is to find the order of the reaction of degration of phenolphthalein in basic media.

For this reaction you will need:

- NaOH 0.3M in water
- NaCl 0.3M in water
- Phenolphthalein 3g/L in ethanol

Theory

Sources:

- [Degradation of phenolphthalein](http://www.ccri.edu/chemistry/courses/chem_1100/wirkkala/labs/Phenolphthalein_NaOH_Kinetics.pdf)
- [Order of reaction](<https://chem.libretexts.org/Bookshelves/Physical_and_Theoretical_Chemistry_Textbook_Maps/Supplemental_Modules_(Physical_and_Theoretical_Chemistry)/Kinetics/Experimental_Methods/Methods_of_Determining_Reaction_Order>).

## Experiment

Solution were prepared using standard procedure. Phenolphthalein is really not well soluble in water. Even a saturated solution and 1 mL of this water solution would not allow to conduct the experiments. We therefore decided to dissolve phenolphthalein in alcohol fuel (mixture of ethanol and methanol).

- solution A: NaOH 0.3M in water
- solution B: NaCl 0.3M in water
- solution C: phenolphthalein 3.02 g/L in MeOH / EtOH

Four experiments were conducted in test tubes. We use a solution of NaCl instead of water in order to keep similar ionic strength in all the experiments.

In each test tube we first add the corresponding amount of solution A and B using air displacement micropipettes (we are doing this in a biological lab 😉). Just before starting the experiment we add C, mix well with a plastic transfer pipettes of 3mL (that also allows to clean the wall of the test tube) and transfer the solution in a cuvette.

| Experiment | A    | B    | C     |
| ---------- | ---- | ---- | ----- |
| 1          | 4 mL | 0 mL | 20 µL |
| 2          | 3 mL | 1 mL | 20 µL |
| 3          | 2 mL | 2 mL | 20 µL |
| 4          | 1 mL | 3 mL | 20 µL |

We then immediately start a kinetic experiments with the following parameters:

- time before blank: 2s
- time before first experiment: 10s
- time between experiments: 20s
- observed channels: R G B UV (15)
- number of experiments: 48 (the maximum)

We used as blank water.

## Results

The spectrometer was connected to a computer and the data transfered using the Arduino program. The data were then processed online on the [following page](https://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log).

In this page the more intense channel is considered and only the values having an absorbance over `0.1`.

Raw data for the 4 kinetics are in the attached corresponding documents:

- [Experiment 1](exp1.txt)
- [Experiment 2](exp2.txt)
- [Experiment 3](exp3.txt)
- [Experiment 4](exp4.txt)

For first order reaction we are expected to observe an equation like:

[A]<sub>t</sub> = [A]<sub>0</sub>e<sup>-kt</sup>

A exponential regression has been applied for the 4 experiments and the following results are observed:

| Experiment | [NaOH]  | [A]<sub>0</sub> | k      | r<sup>2</sup> |
| ---------- | ------- | --------------- | ------ | ------------- |
| 1          | 0.300 M | 0.3482          | 0.2587 | 0.99977       |
| 2          | 0.225 M | 0.4614          | 0.1812 | 0.99959       |
| 3          | 0.150 M | 0.5934          | 0.1134 | 0.99837       |
| 4          | 0.075 M | 0.6932          | 0.0497 | 0.99938       |

The corresponding regressions look like follow:

| Experiment | [NaOH]                 | [A]<sub>0</sub> | k      |
| ---------- | ---------------------- | --------------- | ------ |
| 1          | <img src="chart1.svg"> | 0.3482          | 0.2587 |
| 2          | <img src="chart2.svg"> | 0.4614          | 0.1812 |
| 3          | <img src="chart3.svg"> | 0.5934          | 0.1134 |
| 4          | <img src="chart4.svg"> | 0.6932          | 0.0497 |

Other regressions and be probed and you can see the results for `experiment 2` in the followin [pdf](regressions.pdf). The best regression is the exponential one.

## Intermediate conclusion

Because of the large excess of NaOH in this experiment we observe a pseudo-order 1 reaction. Based on the 4 experiments that were done with 4 different concentration of NaOH we can check if it is also dependent on the concentration of NaOH.

## k versus [NaOH]

| [NaOH]  | k      |
| ------- | ------ |
| 0.300 M | 0.2587 |
| 0.225 M | 0.1812 |
| 0.150 M | 0.1134 |
| 0.075 M | 0.0497 |

[NaOH] k  
0.300 0.2587
0.225 0.1812
0.150 0.1134
0.075 0.0497

A plot of the concentration of NaOH versus k show a good linear correlation.

y = −0.02295 + 0.9264 x

r<sup>2</sup> = 0.9980

<img src="NaOHregression.svg">

## Conclusions

The order of this reaction is 2.

## Possible improvements

We could acquire more points if we decide to only take the green channel especially at high concentration of NaOH in which the kinetic is fast.
