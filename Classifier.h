#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Classifier {
    public:
        void Train(vector< vector<double> > &);
        string Test(int, vector<int> &, vector< vector<double> > &);
        void Normalize(int, vector< vector<double> > &);
        void PrepareData();
};