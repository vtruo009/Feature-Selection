#include <ostream>
#include <vector>
#include "Classifier.h"

using namespace std;

class Validator {
    public:
        double LeaveOneOutValidation(int, vector<int> &);
        void PrintFeatureSet(vector<int> &);
};
