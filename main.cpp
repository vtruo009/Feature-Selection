#include <iostream>
#include <vector>
#include <queue>
#include "math.h"
#include "Validator.h"

using namespace std;

// void PrintFeatureSet(vector<int> featureSet) {
//     cout << '{' << featureSet.at(0);
//     for (int i = 1; i < featureSet.size(); ++i) {
//         cout << ',' << featureSet.at(i);
//     }
//     cout << '}';
// }
vector< vector<double> > instances;

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

void GetNextFeatureSet(int algoChoice, queue< vector<int> > &newFeatureSet, vector<int> &currSet, int numFeatures) {
    switch (algoChoice)
    {
    case 1:
        for (int i = 1; i <= numFeatures; ++i) {
            if (find(currSet.begin(), currSet.end(), i) == currSet.end()) {
                vector<int> newSet = currSet;
                newSet.push_back(i);
                newFeatureSet.push(newSet);
            }
        }
        break;
    
    case 2:
        for (int i = 0; i < currSet.size(); ++i) {
            vector<int> newSet = currSet;
            newSet.erase(newSet.begin() + i);
            newFeatureSet.push(newSet);
        }
        break;

    default:
        break;
    }

}

void ClearQueue(queue< vector<int> > &newFeatureSets) {
    queue< vector<int> > empty;
    swap(newFeatureSets, empty);
}

void ForwardSelection(int algoChoice, int numFeatures) {
    Validator v;
    queue< vector<int> > newFeatureSets;
    bool higherFound = true;

    vector<int> initFeatureSet = GetInitFeatureSet(algoChoice, numFeatures);
    double initScore = v.LeaveOneOutValidation(numFeatures, initFeatureSet, instances); // max
    cout << "\nRunning nearest neighbor with no features (default rate), using \"leave-one-out\" evaluation, I get an accuracy of " << initScore << "%\n\nBeginning search.\n\n";

    vector<int> bestFeatureSet = initFeatureSet;
    double bestScore = 0.0;

    GetNextFeatureSet(algoChoice, newFeatureSets, initFeatureSet, numFeatures);
    for (int i = 1; i <= numFeatures; ++i) {
        higherFound = false;
        while (!newFeatureSets.empty()) {
            vector<int> currFeatureSet = newFeatureSets.front();
            newFeatureSets.pop();
            double currScore = v.LeaveOneOutValidation(numFeatures, currFeatureSet, instances);
            // double currScore = CalcAccuracy();
            // cout << "Using feature(s) "; v.PrintFeatureSet(currFeatureSet); cout << " accuracy is " << currScore << "%\n\n";
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
        cout << "\nFeature set "; v.PrintFeatureSet(bestFeatureSet); cout << " was best, accuracy is " << bestScore << "%\n\n";
        ClearQueue(newFeatureSets);
        GetNextFeatureSet(algoChoice, newFeatureSets, bestFeatureSet, numFeatures);
    }
    cout << "Finished search! The best feature subset is "; v.PrintFeatureSet(bestFeatureSet); cout << ", which has an accuracy of " << bestScore << "%\n";
}

void BackwardElimination(int algoChoice, int numFeatures) {
    Validator v;
    queue< vector<int> > newFeatureSets;
    bool higherFound = true;

    vector<int> initFeatureSet = GetInitFeatureSet(algoChoice, numFeatures);
    double initScore = v.LeaveOneOutValidation(numFeatures, initFeatureSet, instances); // max
    cout << "\nRunning nearest neighbor with no features (default rate), using \"leave-one-out\" evaluation, I get an accuracy of " << initScore << "%\n\nBeginning search.\n\n";

    vector<int> bestFeatureSet = initFeatureSet;
    double bestScore = 0.0;

    GetNextFeatureSet(algoChoice, newFeatureSets, initFeatureSet, numFeatures);
    for (int i = 1; i <= numFeatures; ++i) {
        higherFound = false;
        while (!newFeatureSets.empty()) {
            vector<int> currFeatureSet = newFeatureSets.front();
            newFeatureSets.pop();
            double currScore = v.LeaveOneOutValidation(numFeatures, currFeatureSet, instances);
            // double currScore = CalcAccuracy();
            // cout << "Using feature(s) "; v.PrintFeatureSet(currFeatureSet); cout << " accuracy is " << currScore << "%\n";
            if (bestScore < currScore) {
                bestFeatureSet = currFeatureSet;
                bestScore = currScore;
                higherFound = true;
            }
        }
        if (!higherFound) {
            cout << "\n(Warning, Accuracy has decreased!)\n";
            if (i == 1) {
                cout << "Finished search! The best feature subset is the initial empty feature set, which has an accuracy of " << bestScore << "%\n";
            }
            break;
        }
        cout << "\nFeature set "; v.PrintFeatureSet(bestFeatureSet); cout << " was best, accuracy is " << bestScore << "%\n\n";
        ClearQueue(newFeatureSets);
        GetNextFeatureSet(algoChoice, newFeatureSets, bestFeatureSet, numFeatures);
    }
    cout << "Finished search! The best feature subset is "; v.PrintFeatureSet(bestFeatureSet); cout << ", which has an accuracy of " << bestScore << "%\n";
}

int main() {
    // srand(time(NULL));
    int numFeatures = 0;
    Classifier c;
    int algoChoice = 0;
    string filename = "";
    cout << "Welcome to Van's Feature Selection Algorithms." << endl;
    cout << "Type in the name of the file to test: ";
    cin >> filename;
    cout << "\n\n";

    // cout << "Please enter the total number of features: ";
    // cin >> numFeatures;

    cout << "Type in the number of the algorithm you want to run.\n" <<
        "1. Forward Selection\n" <<
        "2. Backward Elimination\n" <<
        "3. Van's Special Algorithm\n";
    cin >> algoChoice;

    c.Train(instances, filename);
    numFeatures = instances.at(0).size() - 1;
    cout << "\nThis dataset has " << numFeatures << " features (not including the class attribute), with " << instances.size() << " instances.\n\n";
    
    cout << "Please wait while I normalize the data... ";
    c.Normalize(numFeatures, instances);
    cout << "Done!\n";

    // switch (algoChoice) {
    //     case 1:
    //         ForwardSelection(algoChoice, numFeatures);
    //         break;
        
    //     case 2:
    //         BackwardElimination(algoChoice, numFeatures);
    //         break;
        
    //     case 3:
    //         //special algo
    //         break;
            
    //     default:
    //         break;
    // }
    Validator v;
    vector<int> test = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
    double ac = v.LeaveOneOutValidation(numFeatures, test, instances);
    return 0;
}