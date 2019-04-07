# Phenolphathalein

Order to the reaction. Theory can be find [here](<https://chem.libretexts.org/Bookshelves/Physical_and_Theoretical_Chemistry_Textbook_Maps/Supplemental_Modules_(Physical_and_Theoretical_Chemistry)/Kinetics/Experimental_Methods/Methods_of_Determining_Reaction_Order>).

- solution A: NaOH 0.3M in water
- solution B: NaCl 0.3M in water
- solution C: phenolphthalein 3.02 g/L in MeOH / EtOH

| Experiment | A    | B    | C     |
| ---------- | ---- | ---- | ----- |
| 1          | 4 mL | 0 mL | 20 µL |
| 2          | 3 mL | 1 mL | 20 µL |
| 3          | 2 mL | 2 mL | 20 µL |
| 4          | 1 mL | 3 mL | 20 µL |

## Results

Results for the 4 kinetics are in the attached corresponding documents.

The data were proceed on [this page](https://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2F7b6eb01da45510275179c4b587bb63f0%2Fview.json&loadversion=true&fillsearch=Analyse+spectro+log). Only the green channel has been considered and only the points having an absorbance over `0.1`.

For first order reaction we are expected to observe an equation like:

[A]<sub>t</sub> = [A]<sub>0</sub>e<sup>-kt</sup>

A exponential regression has been applied for the 4 experiments and the following results are observed:

| Experiment | [NaOH]  | [A]<sub>0</sub> | k      | r<sup>2</sup> |
| ---------- | ------- | --------------- | ------ | ------------- |
| 1          | 0.300 M | 0.3482          | 0.2587 | 0.99977       |
| 2          | 0.225 M | 0.4614          | 0.1812 | 0.99959       |
| 3          | 0.150 M | 0.5934          | 0.1134 | 0.99837       |
| 4          | 0.075 M | 0.6932          | 0.0497 | 0.99938       |

| Experiment | [NaOH]                 | [A]<sub>0</sub> | k      |
| ---------- | ---------------------- | --------------- | ------ |
| 1          | <img src="chart1.svg"> | 0.3482          | 0.2587 |
| 2          | <img src="chart2.svg"> | 0.4614          | 0.1812 |
| 3          | <img src="chart3.svg"> | 0.5934          | 0.1134 |
| 4          | <img src="chart4.svg"> | 0.6932          | 0.0497 |

# Linear regression

y=0.4622−0.5943x

r<sup>2</sup> = 0.9970

<img src="regression.svg">
