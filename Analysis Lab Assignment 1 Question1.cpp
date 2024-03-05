//Ismaiel Sabet 900221277

//Analysis Lab Assignment 1.1

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <queue>
using namespace std;


class Compare {
public:
    bool operator()(const std::vector<int> a, const std::vector<int> b) const {
        return a.size() > b.size();
    }
};



int main() {
    int num_of_operations = 0;
    filesystem::path folderPath = "C:\\Users\\ismai\\OneDrive\\Documents\\Coding projects\\C++\\SortedNumbersFiles"; // Specify the folder path (change it manually when you run the code)
    int count = 0;

    for (const auto &entry: filesystem::directory_iterator(folderPath)) {
        count++;
        num_of_operations++;
    }
    std::cout << "Number of files in " << folderPath << ": " << count << '\n';
    vector<vector<int>> data;
    vector<int> sizes;
    data.resize(count);
    num_of_operations+=2;

    for (int fileIndex = 0; fileIndex < count; ++fileIndex) {
        num_of_operations++;
        ifstream inputFile("SortedNumbersFiles\\file" + std::to_string(fileIndex + 1) + ".txt"); 
        if (!inputFile) {
            cout << "Error opening file" << fileIndex << endl;
            continue;
        }
        int value;
        while (inputFile >> value) {
            data[fileIndex].push_back(value);
            num_of_operations++;
        }
        inputFile.close();
    }

    for (int i = 0; i < count; i++) {
        cout << "Content in file" << to_string(i+1) <<": ";
        for (int num: data[i]) {
            cout << num << " ";
            num_of_operations++;
        }
        cout << endl;
    }

    for (int i = 0; i < count; i++) {
        int size = data[i].size();
        sizes.push_back(size);
        num_of_operations++;
    }
    priority_queue<vector<int>, vector<vector<int>>, Compare> pq;
    num_of_operations++;

    for (const auto &vec: data) {
        pq.push(vec);
        num_of_operations++;
    }

    while (pq.size() != 1) {
        vector<int> list1, list2;
        vector <int> result;
        num_of_operations+=6;
        list1 = pq.top();
        pq.pop();
        list2 = pq.top();
        pq.pop();
        auto i1 = list1.begin();
        auto i2 = list2.begin();
        while(i1 != list1.end() && i2 != list2.end()) {
            if (*i2 < *i1) {
                result.push_back(*i2);
                i2++;
            }
            else if(*i1 < *i2){
                result.push_back(*i1);
                i1++;
            }
            num_of_operations+=3;
        }
        while(i1 != list1.end() || i2 != list2.end()) {
            if (i1 == list1.end() && i2 != list2.end()) {
                result.push_back(*i2);
                i2++;
                num_of_operations += 5;
            } else if (i2 == list2.end() && i1 != list1.end()) {
                result.push_back(*i1);
                i1++;
                num_of_operations += 5;
            }

            pq.push(result);
            num_of_operations++;
        }

    }



        ofstream o;
        o.open("outputlist.txt");
        vector<int> temp;
        num_of_operations++;
        temp = pq.top();
        cout << "The combined file: ";
        for (int i = 0; i < temp.size(); i++) {
            cout << temp[i] << " ";
            num_of_operations++;
            o << temp[i] << " ";
        }
        cout << endl;

    cout << "Total number of operations: " << num_of_operations << endl;
        return 0;
    }