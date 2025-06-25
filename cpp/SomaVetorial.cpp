#include <iostream>
#include <iomanip>
#include <vector>

//uses next n doubles to fill the vector inplace
void fillVector(std::vector<double> *vector, int n) {
    double input;
    int i;
    for (i = 0; i< n; i++) {
        std::cin >> input;
        (*vector).push_back(input);
    }
}

std::vector<double> sumVector(std::vector<double> *v1, std::vector<double> *v2) {
    std::vector<double> sumVector = {};
    int i;
    if (v1->size() != v2->size()) {
        return (std::vector<double>) {};
    }

    for(i = 0; i < v1->size(); i++) {
        sumVector.push_back((double)(v1->at(i) + v2->at(i)));
    }
    return sumVector;
}

int main() {
    int n, i;
    std::vector<double> vector1, vector2, sum;
    std::cout << std::fixed << std::setprecision(2);
    
    while (std::cin >> n && n != 0) { 
        vector1 = {}, vector2 = {};
        fillVector(&vector1, n);
        fillVector(&vector2, n);
        sum = sumVector(&vector1, &vector2);
        for (i = 0; i<sum.size(); i++) 
        {
            std::cout << sum.at(i);
            if (i < sum.size()-1) 
            {
                std::cout << ' ';
            }
            else 
            {
                std::cout << std::endl;
            }
        }
    }
    return 0;
}