#include <ostream>
#include <vector>
#include <algorithm>
#include "Classifier.h"

using namespace std;

class Validator {
    public:
        double LeaveOneOutValidation(int, vector<int> &, vector< vector<double> > &);
        void PrintFeatureSet(vector<int> &);
};
