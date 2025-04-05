#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

struct Item {
    long long int id;
    long long int profit;
    long long int weight;
};

typedef long long int lli;

void output(string& inputFilePath, vector<long long int>& selectedItems){

    string outputFilePath = inputFilePath.substr(0, inputFilePath.find_last_of('.')) + "_temp.txt";
    ofstream resultFile(outputFilePath);

    if (resultFile.is_open()) {
        for (size_t i = 0; i < selectedItems.size(); ++i) {
            resultFile << selectedItems[i];
            if (i < selectedItems.size() - 1) {
                resultFile << " - ";
            }
        }
        resultFile << endl;

        resultFile.close();
    } else {
        cerr << "Error creating result file." << endl;
    }

}

int main() {

    string inputFileName = "test1.in";

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << inputFileName << endl;
    }

    int itemCount;
    inputFile >> itemCount;

    vector<Item> Itetms(itemCount);
    for (int i = 0; i < itemCount; ++i) {
        inputFile >> Itetms[i].id >> Itetms[i].profit >> Itetms[i].weight;
    }

    long long int capacity;
    inputFile >> capacity;


    inputFile.close();

    auto start = chrono::system_clock::now();

    lli best_ans = 0;

    vector<long long int> best_selected_items;

    for (int x = 0; x < 20; ++x) {
        random_device rd;
        mt19937 g(rd());
        shuffle(Itetms.begin(), Itetms.end(), g);

        long long int current_cap = 0;
        long long int current_prof = 0;
        vector<long long int> selected_items;

        int i = 0;

        while (current_cap + Itetms[i].weight < capacity){
            current_prof += Itetms[i].profit;
            current_cap += Itetms[i].weight;
            selected_items.push_back(Itetms[i].id);
            i++;
        }

        if (current_prof > best_ans){
            best_ans = current_prof;
            best_selected_items = selected_items;
        }
    }

    cout << best_ans << endl;

    auto end = chrono::system_clock::now();

    chrono::duration<long double> elapsed_seconds = end-start;

    cout << "Total time: " << elapsed_seconds.count() << "s"
              << endl;

    output(inputFileName, best_selected_items);

    return 0;
}
