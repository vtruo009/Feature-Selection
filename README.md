# Feature-Selection

## Introduction
The purpose of this project is to explore the two search algorithms of machine learning: Forward Selection and Backward Elimination by implementing a Nearest-Neighbor classifier and utilizing the Leave-One-Out validation technique. Given a dataset with a certain amount of features, the program first determines the subset of features using one of the two search algorithms, then validates that subset of features using Leave-One-Out validation to best classify an unseen instance.

## To run & execute the program:
```g++ -std=c++11 main.cpp Classifier.cpp Validator.cpp```<br>
```./a.out```<br>
The program will prompt for the file name that contains the dataset. For example: ```cs_170_small104.txt```. Then choose an search algorithm to perform feature search.<br>
* 1 - Forward Selection<br>
* 2 - Backward Elimination<br>

## Files
```Validator.h``` and ```Validator.cpp```<br>
These two files contain the function ```LeaveOneOutValidation()```, which tests the instances by picking out one instance for test instance and the rest is the training instances.<br>

```Classifier.h``` and ```Classifier.cpp```<br>
These two files contain the functions ```Train()```, ```Test()```, and ```Normalize()```.<br>
* ```Train()``` - Load the data from the dataset<br>
* ```Test()``` - This function computes the Euclidean distance between the test instance and all the training instances.<br>
* ```Normalize()``` - This function normalizes the data after it has been loaded to bring the data down to scale.<br>

```main.cpp```<br>
The main file contains the user interface and the search algorithms: Forward Selection and Backward Elimination.