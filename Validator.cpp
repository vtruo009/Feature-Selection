#include <iostream>
#include <chrono>
#include "Validator.h"

using namespace std;

vector< vector<double> > instances;

double Validator::LeaveOneOutValidation(int numFeatures, vector<int> &featureSubset) {
    // Timer Reference: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    Classifier c;
    if (instances.size() == 0) {
        c.Train(instances);          // Load data
        c.Normalize(numFeatures, instances);
    }
    double correctLabels = 0, testInstanceIndex;
    double accuracy;
    cout << "Starting validation..." << endl;
    auto start = chrono::high_resolution_clock::now();
    
    // Default Rate
    if (featureSubset.size() == 0) {
        int one = 0, two = 0;
        for (int i = 0; i < instances.size(); ++i) {
            if (instances.at(i).at(0) == 1) {
                ++one;
            }
            else {
                ++two;
            }
        }
        if (one > two) {
            return one/instances.size();
        }
        else {
            return two/instances.size();
        }
    }
    else {
        for (int i = 0; i < instances.size(); ++i) {
            testInstanceIndex = i;
            Classifier c;
            string testLabel = c.Test(testInstanceIndex, featureSubset, instances);
            if (testLabel == to_string(instances.at(i).at(0))) {
                correctLabels++;
            }
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "Time taken for validation = " << duration.count() << " milliseconds" << endl;
    accuracy = correctLabels/instances.size();
    // string subset = "{" + to_string(featureSubset.at(0));
    // for (int i = 1; i < featureSubset.size(); ++i) {
    //     subset += ' ' + to_string(featureSubset.at(i));
    // }
    // subset += "}";
    // cout << "Using features " << subset << ", the accuracy is " << accuracy*100 << "%" << endl;
    cout << "Using feature(s) "; PrintFeatureSet(featureSubset); cout<< ", the accuracy is " << accuracy* 100 << "%" << endl << endl;
    return accuracy*100;
}

void Validator::PrintFeatureSet(vector<int> &featureSet) {
    cout << '{' << featureSet.at(0);
    for (int i = 1; i < featureSet.size(); ++i) {
        cout << ',' << featureSet.at(i);
    }
    cout << '}';
}