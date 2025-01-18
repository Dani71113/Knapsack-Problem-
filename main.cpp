#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name;
    int weight;
    int value;
};

// Function to get user input for number of items
int getNumItems() {
    int numItems;
    cout << "Welcome to the Knapsack Optimization Program!" << endl;
    cout << "This program helps you maximize the total value of items you can carry in a knapsack with limited capacity." << endl;
    cout << "Enter the number of items you want to evaluate: ";
    cin >> numItems;
    return numItems;
}

// Function to get user input for an item
Item getItem(int itemNumber) {
    Item item;
    cout << "Enter details for item " << itemNumber << ":" << endl;
    cout << "  Name: ";
    cin >> item.name;
    cout << "  Weight: ";
    cin >> item.weight;
    cout << "  Value: ";
    cin >> item.value;
    return item;
}

// Function to get user input for items
vector<Item> getItems(int numItems) {
    vector<Item> items;
    for (int i = 0; i < numItems; ++i) {
        items.push_back(getItem(i + 1));
    }
    cout << "\nYou have entered the following items:" << endl;
    for (int i = 0; i < numItems; ++i) {
        cout << "  Item " << i + 1 << ": " 
             << items[i].name << " (Weight: " 
             << items[i].weight << ", Value: " 
             << items[i].value << ")" << endl;
    }
    return items;
}

// Function to get knapsack capacity
int getCapacity() {
    int capacity;
    cout << "\nEnter the total capacity of the knapsack: ";
    cin >> capacity;
    return capacity;
}

// Knapsack algorithm (0/1 Knapsack)
pair<int, vector<int>> knapsack(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    vector<vector<bool>> keep(n + 1, vector<bool>(capacity + 1, false));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                if (items[i - 1].value + dp[i - 1][w - items[i - 1].weight] > dp[i - 1][w]) {
                    dp[i][w] = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
                    keep[i][w] = true;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    vector<int> selectedItems;
    int w = capacity;
    for (int i = n; i > 0; --i) {
        if (keep[i][w]) {
            selectedItems.push_back(i - 1); // Store index of the item
            w -= items[i - 1].weight;
        }
    }

    return {dp[n][capacity], selectedItems};
}

// Function to display the result
void displayResult(int maxValue, const vector<Item>& items, const vector<int>& selectedItems) {
    cout << "\n=== Knapsack Optimization Result ===" << endl;
    cout << "Maximum value that can be obtained: " << maxValue << endl;
    if (selectedItems.empty()) {
        cout << "No items could be selected within the given capacity." << endl;
    } else {
        cout << "Selected items are:" << endl;
        for (int idx : selectedItems) {
            cout << " - " << items[idx].name 
                 << " (Weight: " << items[idx].weight 
                 << ", Value: " << items[idx].value << ")" << endl;
        }
    }
    cout << "\nThank you for using the Knapsack Optimization Program!" << endl;
}

int main() {
    int numItems = getNumItems();
    vector<Item> items = getItems(numItems);
    int capacity = getCapacity();

    auto [maxValue, selectedItems] = knapsack(items, capacity);

    displayResult(maxValue, items, selectedItems);

    return 0;
}
