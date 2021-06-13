#include <iostream>
#include <typeinfo>
#include <sstream>
#include <limits>

#include "Classifier.h"

using namespace std;

void Classifier::Train(vector< vector<double> > &instances, string filename) {
    // Lod Data References: https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus
    fstream newfile(filename);
    string tp;
    while (getline(newfile >> ws, tp)) {
        string feature = "";
        vector<double> features;
        double temp;
        for (int i = 0; i < tp.size(); ++i) {
            if (tp.at(i) == ' ') {
                istringstream os(feature);
                os >> temp;
                features.push_back(temp);
                feature = "";
                ++i;
            }
            else {
                feature += tp.at(i);
            }
        }
        istringstream os(feature);
        os >> temp;
        features.push_back(temp);
        instances.push_back(features);
    }
}

string Classifier::Test(int testInstanceIndex, vector<int> &featureSubset, vector< vector<double> > &instances) {
    // Compute distance matrix
    double shortestDist = numeric_limits<double>::max();
    string label = "";
    for (int i = 0; i < instances.size(); ++i) {
        double sum = 0.0;
        if (i != testInstanceIndex) {
            for (int k = 0; k < featureSubset.size(); ++k) {
                int feature = featureSubset.at(k);
                double testFeature = instances.at(testInstanceIndex).at(feature);
                double trainFeature = instances.at(i).at(feature);
                sum += pow(testFeature - trainFeature, 2);
            }
            double dist = sqrt(sum);
            if (dist < shortestDist) {
                shortestDist = dist;
                label = to_string(instances.at(i).at(0));
            }
        }
    }
    return label;
}

void Classifier::Normalize(int numFeatures, vector< vector<double> > &instances) {
    // Calculating the mean of each column/feature
    vector<double> means(1, 0);
    for (int i = 1; i <= numFeatures; ++i) { // added <=
        double sum = 0;
        for (int j = 0; j < instances.size(); ++j) {
            sum += instances.at(j).at(i);
        }
        means.push_back(sum/instances.size());
    }
    
    // Calculating the standard deviation of each column
    for (int i = 1; i <= numFeatures; ++i) {
        double sum = 0;
        for (int j = 0; j < instances.size(); ++j) {
            sum += pow(instances.at(j).at(i) - means.at(i), 2);
        }
        double sd = sqrt(sum/instances.size());
        for (int k = 0; k < instances.size(); ++k) {
            instances.at(k).at(i) = (instances.at(k).at(i) - means.at(i)) / sd;
        }
    }
}