#include <iostream>
#include <vector>
#include <queue>
#include "math.h"
// #include "Node.h"

using namespace std;

double CalcAccuracy() {
    double accuracy = (double)(rand() % 100);

    return accuracy;
}


void PrintFeatureSet(vector<int> featureSet) {
    cout << '{' << featureSet.at(0);
    for (int i = 1; i < featureSet.size(); ++i) {
        cout << ',' << featureSet.at(i);
    }
    cout << '}';
}

vector<int> GetInitFeatureSet(int algoChoice, int numFeatures) {
    vector<int> featureSet;
    switch (algoChoice)
    {
    case 1:
        break;
    case 2:
        for (int i = 1; i <= numFeatures; ++i) {
            featureSet.push_back(i);
        }
    default:
        break;
    }
    return featureSet;
}

void GetNextFeatureSet(queue< vector<int> > &newFeatureSet, vector<int> &currSet, int numFeatures) {
    for (int i = 1; i <= numFeatures; ++i) {
        if (find(currSet.begin(), currSet.end(), i) == currSet.end()) {
            vector<int> newSet = currSet;
            newSet.push_back(i);
            newFeatureSet.push(newSet);
        }
    }
}

void ClearQueue(queue< vector<int> > &newFeatureSets) {
    queue< vector<int> > empty;
    swap(newFeatureSets, empty);
}

void ForwardSelection(int algoChoice, int numFeatures) {
    queue< vector<int> > newFeatureSets;
    bool higherFound = true;

    vector<int> initFeatureSet = GetInitFeatureSet(algoChoice, numFeatures);
    double initScore = 55.4; // max
    cout << "Using no features and \"random\" evaluation, I get an accuracy of " << initScore << "%\n\nBeginning search.\n\n";

    vector<int> bestFeatureSet = initFeatureSet;
    double bestScore = initScore;

    GetNextFeatureSet(newFeatureSets, initFeatureSet, numFeatures);
    for (int i = 1; i <= numFeatures; ++i) {
        higherFound = false;
        while (!newFeatureSets.empty()) {
            vector<int> currFeatureSet = newFeatureSets.front();
            newFeatureSets.pop();
            double currScore = CalcAccuracy();
            cout << "Using feature(s) "; PrintFeatureSet(currFeatureSet); cout << " accuracy is " << currScore << "%\n";
            if (bestScore < currScore) {
                bestFeatureSet = currFeatureSet;
                bestScore = currScore;
                higherFound = true;
            }
        }
        if (!higherFound) {
            cout << "\n(Warning, Accuracy has decreased!)\n";
            if (i == 1) {
                cout << "Finished search! The best feature subset is the initial feature set, which has an accuracy of " << bestScore << "%\n";
            }
            break;
        }
        cout << "\nFeature set "; PrintFeatureSet(bestFeatureSet); cout << " was best, accuracy is " << bestScore << "%\n\n";
        ClearQueue(newFeatureSets);
        GetNextFeatureSet(newFeatureSets, bestFeatureSet, numFeatures);
    }
    cout << "Finished search! The best feature subset is "; PrintFeatureSet(bestFeatureSet); cout << ", which has an accuracy of " << bestScore << "%\n";
}

int BackwardElimination(int algoChoice, int numFeatures) {
    vector<int> initFeatureSet = GetInitFeatureSet(algoChoice, numFeatures);
    if (!initFeatureSet.empty()) {
        PrintFeatureSet(initFeatureSet);
    }
}


int main() {
    srand(time(NULL));
    int numFeatures = 0;
    int algoChoice = 0;
    cout << "Welcome to Van's Feature Search Algorithms." << endl;

    cout << "Please enter the total number of features: ";
    cin >> numFeatures;

    cout << "Type in the number of the algorithm you want to run.\n" <<
        "1. Forward Selection\n" <<
        "2. Backward Ellimination\n" <<
        "3. Van's Special Algorithm\n";
    cin >> algoChoice;

    
    switch (algoChoice) {
        case 1:
            ForwardSelection(algoChoice, numFeatures);
            break;
        
        case 2:
            BackwardElimination(algoChoice, numFeatures);
        default:
            break;
    }

    return 0;
}