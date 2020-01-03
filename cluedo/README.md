# Cluedo - An introductory rush to logic programming

Subject: [cluedo.en.pdf](cluedo.en.pdf)

This rush was an introductory rush to logic programming with
[Prolog](https://en.wikipedia.org/wiki/Prolog).

## Setup

Install [SWI-Prolog](https://www.swi-prolog.org/).

## Problem 1: Create a Family Tree ([step1.pl](step1.pl))

Interactively query the "database":

```
$ swipl -q step1.pl
?- conjoint(marc, X).
X = anne.
[...]
```

## Problem 2: Einstein’s Enigma ([step2.pl](step2.pl))

```
$ swipl -q -t find step2.pl
[verte,allemand,cafe,prince,poissons]
```

## Problem 3: The goat, the wolf and the cabbage ([step3.pl](step3.pl))

```
$ swipl -q -t cross step3.pl
[🐐,¯\_(ツ)_/¯,🌿,🐐,🐺,¯\_(ツ)_/¯,🐐]
```

## Bonus: Fibonnaci Number Calculator ([fibonnaci.pl](fibonnaci.pl))

```
$ swipl -q fibonacci.pl
?- fib(7, X).
X = 13 .
```

## Bonus: Power Calculator ([pow.pl](pow.pl))

```
swipl -q pow.pl
?- power(5,3,X).
X = 125 .
```
