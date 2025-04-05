#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>
#include <execution>

using namespace std;

struct KnapsackItem {
    long long int ID;
    long long int Profit;
    long long int Weight;
};

vector<KnapsackItem> readInput(const string& inputFile, int& itemCount, long long int& maxCapacity) {
    ifstream file(inputFile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        exit(EXIT_FAILURE);
    }

    file >> itemCount;
    cout << "Number of items: " << itemCount << endl;

    vector<KnapsackItem> knapsackItems(itemCount);
    for (int i = 0; i < itemCount; ++i)
        file >> knapsackItems[i].ID >> knapsackItems[i].Profit >> knapsackItems[i].Weight;

    file >> maxCapacity;
    cout << "Maximum capacity: " << maxCapacity << endl;

    file.close();

    return knapsackItems;
}


void randomizedGreedyKnapsack(const vector<KnapsackItem>& knapsackItems, long long int maxCapacity, int numRuns, long long int& bestTotalProfit, vector<long long int>& bestSelectedItems) {
    auto start = chrono::system_clock::now();
    bestTotalProfit = 0;

    for (int run = 1; run <= numRuns; ++run) {
        random_device rd;
        mt19937 g(rd());
        vector<KnapsackItem> shuffledItems = knapsackItems;
        shuffle(shuffledItems.begin(), shuffledItems.end(), g);

        long long int currentCapacity = 0;
        long long int totalProfit = 0;
        vector<long long int> selectedItems;

        for (const KnapsackItem& item : shuffledItems) {
            if (currentCapacity + item.Weight <= maxCapacity) {
                currentCapacity += item.Weight;
                totalProfit += item.Profit;
                selectedItems.push_back(item.ID);
            }
        }

        if (totalProfit > bestTotalProfit) {
            bestTotalProfit = totalProfit;
            bestSelectedItems = selectedItems;
        }

        cout << "Run " << run << ": Maximum Profit (Randomized Greedy): " << totalProfit << endl;
    }

    sort(execution::par, bestSelectedItems.begin(), bestSelectedItems.end());
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "Total time: " << elapsed_seconds.count() << "s"
         << endl;
}


void writeOutput(const string& inputFile, const long long int bestTotalProfit, const vector<long long int>& bestSelectedItems) {
    string outputFile = "output_random";
    ofstream resultFile(outputFile);

    if (resultFile.is_open()) {
        resultFile << "Best Maximum Profit (Randomized Greedy): " << bestTotalProfit << endl;
        resultFile << "Selected Item IDs: ";
        for (size_t i = 0; i < bestSelectedItems.size(); ++i) {
            resultFile << bestSelectedItems[i];
            if (i < bestSelectedItems.size() - 1) {
                resultFile << " - ";
            }
        }
        resultFile << endl;

        cout << "Results written to: " << outputFile << endl;
        resultFile.close();
    } else {
        cerr << "Error creating result file." << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    string inputFile = "test1.in";
    int numRuns = 5;
    int itemCount;
    long long int maxCapacity;
    vector<KnapsackItem> knapsackItems = readInput(inputFile, itemCount, maxCapacity);

    long long int bestTotalProfit;
    vector<long long int> bestSelectedItems;
    randomizedGreedyKnapsack(knapsackItems, maxCapacity, numRuns, bestTotalProfit, bestSelectedItems);

    writeOutput(inputFile, bestTotalProfit, bestSelectedItems);

    return 0;
}
