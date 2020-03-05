# Phenolphathalein

[Phenolphthalein](https://en.wikipedia.org/wiki/Phenolphthalein) is a common acid-base indicator used for titration. It is colorless in acidic (pH < 8.2) and fuchsia at a pH overs 8.2. In strongly basic media (pH over 10) it will slowly become colorless.

<img src="reaction.png">

While the reaction from the neutral form to the doubly negatively charged is fast, going from [ɸɸ]<sup>-2</sup> to [ɸɸOH]<sup>-3</sup> is relatively slow.

The goal of this experiment is determine the kinetic parameters of this second reaction, the conversion of the fuchsia to colorless form obtained that can be observed in strongly basic media.

## Theory

The rate of this reaction has the general form:

rate = k [ɸɸ]<sup>x</sup> [OH<sup>-</sup>]<sup>y</sup>

The goal of this experiment is to determine x and y. Because of the difficulty to find these 2 coefficients at once it is usual to put one the 2 reagents in large excess so that during the experiment the concentration does not virtually change.

In this experiment we will put [OH]<sup>-1</sup> in large excess and it may be considered as constant.

rate = k' [ɸɸ]<sup>x</sup>

where

k' = k [OH<sup>-</sup>]<sup>y</sup> = apparent constant

### Zeroth-order reaction

rate = − Δ[A] / Δt = k [A]<sup>0</sup> = k

### First-order reaction

rate = − Δ[A] / Δt = k [A]<sup>1</sup>

[A] = [A]<sub>0<sub> e<sup>−kt</sup>

### Second-order reaction

2 A → Products

rate = − Δ[A] / 2 Δt = k [A]<sup>2</sup>

1 / [A] = 1 / [A]<sub>0</sub> + kt

## Material

For this reaction you will need:

- NaOH 0.3M in water
- NaCl 0.3M in water
- Phenolphthalein 3g/L in ethanol

## Experiment

Solutions were prepared using standard procedure. Phenolphthalein is really not well soluble in water. Even a saturated solution and 1 mL of this water solution would not allow to conduct the experiments. We therefore decided to dissolve phenolphthalein in alcohol fuel (mixture of ethanol and methanol).

- solution A: NaOH 0.3M in water
- solution B: NaCl 0.3M in water
- solution C: phenolphthalein 3.02 g/L in MeOH / EtOH

Four experiments were conducted in test tubes. We use a solution of NaCl instead of water in order to keep similar ionic strength in all the experiments.

In each test tube we first add the corresponding amount of solution A and B using air displacement micropipettes (we are doing this in a biology lab 😉). Just before starting the experiment we add C, mix well with a plastic transfer pipette of 3mL (that also allows to clean the wall of the test tube) and transfer the solution in a cell.

| Experiment | A    | B    | C     |
| ---------- | ---- | ---- | ----- |
| 1          | 4 mL | 0 mL | 20 µL |
| 2          | 3 mL | 1 mL | 20 µL |
| 3          | 2 mL | 2 mL | 20 µL |
| 4          | 1 mL | 3 mL | 20 µL |

We then immediately start a kinetic experiment with the following parameters:

- time before blank: 2s
- time before first experiment: 10s
- time between experiments: 20s
- observed channels: R G B UV (15)
- number of experiments: 48 (the maximum)

We used water as blank and did the 4 experiments in parallel using 4 different spectrophotometers. All the data was acquired in less than 20 minutes.

## Results

The spectrophotometer was connected to a computer and the data transferred using the Arduino program. The data was then processed online on the [following page](https://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log).

On this page the most intense channel is considered and only the values having an absorbance over `0.1`.

Raw data for the 4 kinetics is attached in the corresponding documents:

- [Experiment 1](exp1.txt)
- [Experiment 2](exp2.txt)
- [Experiment 3](exp3.txt)
- [Experiment 4](exp4.txt)

For first order reaction we expect to observe an equation like:

[A]<sub>t</sub> = [A]<sub>0</sub>e<sup>-kt</sup>

An exponential regression has been applied for the 4 experiments and the following results are observed:

| Experiment | [NaOH]  | [NaOH]<sub>0</sub> | k      | r<sup>2</sup> |
| ---------- | ------- | ------------------ | ------ | ------------- |
| 1          | 0.300 M | 0.3482             | 0.2587 | 0.99977       |
| 2          | 0.225 M | 0.4614             | 0.1812 | 0.99959       |
| 3          | 0.150 M | 0.5934             | 0.1134 | 0.99837       |
| 4          | 0.075 M | 0.6932             | 0.0497 | 0.99938       |

The corresponding regressions look like follow:

| Experiment | [NaOH]                 | [NaOH]<sub>0</sub> | k      |
| ---------- | ---------------------- | ------------------ | ------ |
| 1          | <img src="chart1.svg"> | 0.3482             | 0.2587 |
| 2          | <img src="chart2.svg"> | 0.4614             | 0.1812 |
| 3          | <img src="chart3.svg"> | 0.5934             | 0.1134 |
| 4          | <img src="chart4.svg"> | 0.6932             | 0.0497 |

Other regressions have been probed, you can see the results for `experiment 2` in the following [pdf](regressions.pdf). The best regression is the exponential one.

## Intermediate conclusion

Because of the large excess of NaOH in this experiment we observe a pseudo-order 1 reaction. Based on the 4 experiments that were done with 4 different concentrations of NaOH, we can check if it is also dependent on the concentration of NaOH.

## k versus [NaOH]

| [NaOH]  | k      |
| ------- | ------ |
| 0.300 M | 0.2587 |
| 0.225 M | 0.1812 |
| 0.150 M | 0.1134 |
| 0.075 M | 0.0497 |

A plot of the concentration of NaOH versus k shows a linear correlation:

- y = −0.02295 + 0.9264 x
- r<sup>2</sup> = 0.9980

<img src="NaOHregression.svg">

## Conclusions

The order of this reaction is 2.

## Possible improvements

We could acquire more points if we decided to only take the green channel especially at high concentrations of NaOH in which the kinetic is fast.

## References

- [Degradation of phenolphthalein](http://www.ccri.edu/chemistry/courses/chem_1100/wirkkala/labs/Phenolphthalein_NaOH_Kinetics.pdf)
- [Order of reaction](<https://chem.libretexts.org/Bookshelves/Physical_and_Theoretical_Chemistry_Textbook_Maps/Supplemental_Modules_(Physical_and_Theoretical_Chemistry)/Kinetics/Experimental_Methods/Methods_of_Determining_Reaction_Order>).
