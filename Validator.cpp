#include <iostream>
#include <chrono>
#include "Validator.h"

using namespace std;

// vector< vector<double> > instances;

double Validator::LeaveOneOutValidation(int numFeatures, vector<int> &featureSubset, vector< vector<double> > &instances) {
    // Timer Reference: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    Classifier c;
    double correctLabels = 0, testInstanceIndex;
    double accuracy;
    // Default Rate
    if (featureSubset.size() == 0) {
        double one = 0.0, two = 0.0;
        for (int i = 0; i < instances.size(); ++i) {
            if (instances.at(i).at(0) == 1) {
                ++one;
            }
            else {
                ++two;
            }
        }
        if (one > two) {
            return one/instances.size() * 100;
        }
        else {
            return two/instances.size() * 100;
        }
    }

    for (int i = 0; i < instances.size(); ++i) {
        testInstanceIndex = i;
        string testLabel = c.Test(testInstanceIndex, featureSubset, instances);
        if (testLabel == to_string(instances.at(i).at(0))) {
            correctLabels++;
        }
    }

    accuracy = correctLabels/instances.size();
    cout << "Using feature(s) "; PrintFeatureSet(featureSubset); cout<< ", the accuracy is " << accuracy* 100 << "%\n";
    return accuracy*100;
}

void Validator::PrintFeatureSet(vector<int> &featureSet) {
    sort(featureSet.begin(), featureSet.end());
    cout << '{' << featureSet.at(0);
    for (int i = 1; i < featureSet.size(); ++i) {
        cout << ',' << featureSet.at(i);
    }
    cout << '}';
}