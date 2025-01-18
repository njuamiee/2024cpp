#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class System {
public:
    // 增加库存
    void addStock(const string& food, const int quantity) {
        stock[food] += quantity;
        cout << "Stocked " << food << " with " << quantity << " units" << endl;
    }

    // 处理订单
    void handleOrder(const string& customer, const vector<pair<string, int>>& order) {
        vector<string> missingItems;
        vector<int> missingQuantities;
        bool allItemsAvailable = true;
        
        // 检查订单中的配料是否足够
        for (const auto& item : order) {
            const string& ingredient = item.first;
            int requiredQuantity = item.second;
            if (stock[ingredient] < requiredQuantity) {
                missingItems.push_back(ingredient);
                missingQuantities.push_back(requiredQuantity - stock[ingredient]);
                allItemsAvailable = false;
            } else {
                stock[ingredient] -= requiredQuantity;
            }
        }

        // 输出订单结果
        if (allItemsAvailable) {
            cout << "Order " << customer << " completed" << endl;
        } else {
            cout << "Order " << customer << " failed: missing ";
            for (size_t i = 0; i < missingItems.size(); ++i) {
                cout << missingItems[i] << " " << missingQuantities[i];
                if (i < missingItems.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    // 打印库存
    void printInventory() {
        cout << "=== Inventory ===" << endl;
        for (const auto& ingredient : ingredients) {
            cout << ingredient << ": " << stock[ingredient] << endl;
        }
        cout << "=================" << endl;
    }

private:
    // 配料名称顺序
    vector<string> ingredients = {"Chicken", "Lettuce", "Tomato", "Cheese", "Onion", "Sauce"};
    
    // 配料的库存
    map<string, int> stock;
};

void handle(System& system) {
    int n;
    cin >> n;
    cin.get();  // consume the newline after the integer input
    string command;
    for (int i = 0; i < n; ++i) {
        getline(cin, command);
        stringstream ss(command);
        string action;
        ss >> action;
        if (action == "Stock") {
            string ingredient;
            int quantity;
            ss >> ingredient >> quantity;
            system.addStock(ingredient, quantity);
        } else if (action == "Order") {
            string customer;
            ss >> customer;
            vector<pair<string, int>> order;
            string ingredient;
            int quantity;
            while (ss >> ingredient >> quantity) {
                order.push_back({ingredient, quantity});
            }
            system.handleOrder(customer, order);
        } else if (action == "Inventory") {
            system.printInventory();
        }
    }
}

int main() {
    System system;
    handle(system);
    return 0;
}
