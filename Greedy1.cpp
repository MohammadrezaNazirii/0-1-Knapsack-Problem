using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <execution>

struct KnapsackItem {
    int ID;
    long long int Value;
    long long int Weight;
    double GreedyChoice;
};

bool CompareItems(const KnapsackItem& item1, const KnapsackItem& item2) {
    return item1.GreedyChoice > item2.GreedyChoice;
}

void ReadInput(const string& inputFileName, int& itemCount, vector<KnapsackItem>& knapsackItems, long long int& knapsackCapacity) {
    ifstream inputFile(inputFileName);

    inputFile >> itemCount;
//    cout << "Number of items: " << itemCount << endl;


    knapsackItems.resize(itemCount);
    for (int i = 0; i < itemCount; ++i) {
        inputFile >> knapsackItems[i].ID >> knapsackItems[i].Value >> knapsackItems[i].Weight;
        knapsackItems[i].GreedyChoice = static_cast<double>(knapsackItems[i].Value) / knapsackItems[i].Weight;
    }


    inputFile >> knapsackCapacity;
//    cout << "Knapsack capacity: " << knapsackCapacity << endl;

    inputFile.close();
}

void KnapsackGreedy(vector<KnapsackItem>& knapsackItems, long long int knapsackCapacity, long long int& totalValue, long long int& totalWeight, vector<long long int>& selectedItems) {
    auto start = chrono::system_clock::now();
    sort(execution::par, knapsackItems.begin(), knapsackItems.end(), CompareItems);

    long long int currentCapacity = 0;

    for (const KnapsackItem& item : knapsackItems) {
        if (currentCapacity + item.Weight <= knapsackCapacity) {
            currentCapacity += item.Weight;
            totalValue += item.Value;
            totalWeight += item.Weight;
            selectedItems.push_back(item.ID);
        }
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Total time: " << elapsed_seconds.count() << "s"
         << endl;
}

void WriteOutput(const string& outputFileName, long long int totalValue, long long int totalWeight, const vector<long long int>& selectedItems) {
    ofstream resultFile(outputFileName);

    if (resultFile.is_open()) {
        resultFile << "Value: " << totalValue << endl;
        resultFile << "Weight: " << totalWeight << endl;
        resultFile << "Selected Item IDs: ";
        for (size_t i = 0; i < selectedItems.size(); ++i) {
            resultFile << selectedItems[i];
            if (i < selectedItems.size() - 1) {
                resultFile << " - ";
            }
        }
        resultFile << endl;

        cout << "Results written to file: " << outputFileName << endl;
        resultFile.close();
    } else {
        cerr << "Error creating result file." << endl;
    }
    cout << "Value: " << totalValue << endl;
    cout << "Weight: " << totalWeight << endl;
    cout << "Selected Item IDs: ";
    for (size_t i = 0; i < selectedItems.size(); ++i) {
        cout << selectedItems[i];
        if (i < selectedItems.size() - 1) {
            cout << " - ";
        }
    }
    cout << endl;
}

int main() {
    string inputFileName = "test1.in";

    int itemCount;
    vector<KnapsackItem> knapsackItems;
    long long int knapsackCapacity;

    long long int totalValue = 0;
    long long int totalWeight = 0;
    vector<long long int> selectedItems;

    ReadInput(inputFileName, itemCount, knapsackItems, knapsackCapacity);

//    auto start = chrono::system_clock::now();

    KnapsackGreedy(knapsackItems, knapsackCapacity, totalValue, totalWeight, selectedItems);

//    auto end = chrono::system_clock::now();
//    chrono::duration<double> elapsed_seconds = end-start;
//    cout << "Total time: " << elapsed_seconds.count() << "s"
//              << endl;

    string outputFileName = "output.txt";
    WriteOutput(outputFileName, totalValue, totalWeight, selectedItems);

    return 0;
}
