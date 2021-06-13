# Feature-Selection

## Introduction
The purpose of this project is to explore the two search algorithms of machine learning: Forward Selection and Backward Elimination by implementing a Nearest-Neighbor classifier and utilizing the Leave-One-Out validation technique. Given a dataset with a certain amount of features, the program first determines the subset of features using one of the two search algorithms, then validates that subset of features using Leave-One-Out validation to best classify an unseen instance.

## To run & execute the program:
```g++ -std=c++11 main.cpp Classifier.cpp Validator.cpp```<br>
```./a.out```

## Files
```Validator.h```<br>
```Validator.cpp```<br>
```Classifier.h```<br>
```Classifier.cpp```<br>
```main.cpp```<br>