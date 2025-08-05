
#include <iostream>     // For input/output operations
#include <string>       // To handle strings
#include <vector>       // To use the vector container
#include <cmath>        // For math functions like fabs()
#include <chrono>       // To measure execution time in milliseconds
//#include <ctime>        // To measure execution time in milliseconds

using namespace std;
using namespace std::chrono;

// ------------ Sorting Function ------------
// Bubble sort: used to sort the array for binary search
void bubbleSort(vector<string>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ------------ Helper Function ------------
// Converts a string to lowercase manually (no <algorithm>)
string toLowerCase(const string& str) {
    string result = str;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + ('a' - 'A');
        }
    }
    return result;
}

// ------------ Validation Function ------------
// Checks if the input string contains only letters
bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return true;
}

// ------------ Linear Search ------------
// Loops through each element to find a match
bool linearSearch(const vector<string>& data, const string& target) {
    string lowerTarget = toLowerCase(target);
    for (const string& name : data) {
        if (toLowerCase(name) == lowerTarget)
            return true;
    }
    return false;
}

// ------------ Binary Search ------------
// Uses divide-and-conquer to search a sorted array
bool binarySearch(const vector<string>& data, const string& target) {
    int left = 0;
    int right = data.size() - 1;
    string lowerTarget = toLowerCase(target);

    while (left <= right) {
        int mid = (left + right) / 2;
        string midValue = toLowerCase(data[mid]);

        if (midValue == lowerTarget) return true;
        else if (midValue < lowerTarget) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

// ------------ Main Program Logic ------------
int main() {
    // Step 1: Array of 50 famous tech first names
    vector<string> names = {
        "Elon", "Bill", "Steve", "Mark", "Larry", "Sergey", "Jeff", "Satya", "Tim", "Sundar",
        "Marissa", "Linus", "Dennis", "Ken", "Guido", "Brendan", "Grace", "Ada", "James", "Brian",
        "Kevin", "Evan", "Travis", "Susan", "Sheryl", "Meg", "Reed", "Drew", "Marc", "Jack",
        "Vinod", "Padmasree", "Palmer", "Gabe", "Tony", "Daniel", "Jan", "Max", "Dara", "David",
        "Whitney", "Alexis", "Stewart", "Diane", "Eric", "Peter", "Nathan", "Scott", "Lisa", "Richard"
    };

    string userName;
    char algoChoice;
    bool validAlgo = false;

    // Step 2: Ask the user for their name and validate it
    while (true) {
        cout << "Enter your first name: ";
        cin >> userName;
        if (isValidName(userName)) break;
        cout << "Invalid name! Please enter letters only.\n";
    }

    // Step 3: Ask the user to choose a search algorithm
    while (!validAlgo) {
        cout << "\nChoose a search algorithm:\n";
        cout << "  A - Binary Search\n";
        cout << "  B - Linear Search\n";
        cout << "Enter your choice (A/B): ";
        cin >> algoChoice;
        if (algoChoice == 'A' || algoChoice == 'a' || algoChoice == 'B' || algoChoice == 'b') {
            validAlgo = true;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    bool found = false;
    int algoScore = 0;
    long long execTime = 0;  // in milliseconds

    // Step 4: Perform the selected search and measure execution time
    if (algoChoice == 'A' || algoChoice == 'a') {
        bubbleSort(names);  // Sort first for binary search
        algoScore = 12;

        // Measure time
        auto start = high_resolution_clock::now();
        found = binarySearch(names, userName);
        auto end = high_resolution_clock::now();

        execTime = duration_cast<milliseconds>(end - start).count();

    }
    else {
        algoScore = 8;

        auto start = high_resolution_clock::now();
        found = linearSearch(names, userName);
        auto end = high_resolution_clock::now();

        execTime = duration_cast<milliseconds>(end - start).count();
    }

    // Step 5: Show results
    cout << "\n-----------------------------------------\n";

    if (found) {
        int nameLength = userName.length();
        double average = (nameLength + algoScore) / 2.0;

        if (fabs(average - 10.0) <= 2.0) {
            cout << "Your name is " << userName << ", you are on the right way! 🤓\n";
        }
        else {
            cout << "Your name is " << userName << ", you need to work harder. 💪\n";
        }
    }
    else {
        cout << "Your name is " << userName << ", sorry you're not on the tech legends list 😅\n";
    }

    // Step 6: Show measured execution time
    cout << "Execution time: " << execTime << " ms\n";
    cout << "-----------------------------------------\n";

    return 0;
}
