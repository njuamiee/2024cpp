#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <sstream>
using namespace std;

// Base class for Character
class Character {
protected:
    string character_id;
    double level = 0.0;
    double max_level = 5.0;
    double base_strength = 0.0;
    double base_mana = 0.0;
    double base_agility = 0.0;
    double weapon_strength = 0.0;
    double staff_power = 0.0;
    double stealth_bonus = 0.0;

public:
    Character(string id) : character_id(id) {}
    virtual ~Character() {}

    virtual double calculatePower() const = 0;
    virtual void upgrade() = 0;

    string getId() const { return character_id; }

    void setAttribute(const string &attribute, double value) {
        if (attribute == "base_strength") base_strength = value;
        else if (attribute == "base_mana") base_mana = value;
        else if (attribute == "base_agility") base_agility = value;
    }

    void equip(const string &equipment_type, double value) {
        if (equipment_type == "weapon") {
            if (weapon_strength != 0.0 || staff_power != 0.0 || stealth_bonus != 0.0) {
                cout << "Character " << character_id << " already has equipment" << endl;
            } else {
                weapon_strength = value;
            }
        } 
        else if (equipment_type == "staff") {
            if (staff_power != 0.0 || weapon_strength != 0.0 || stealth_bonus != 0.0) {
                cout << "Character " << character_id << " already has equipment" << endl;
            } else {
                staff_power = value;
            }
        } 
        else if (equipment_type == "cloak") {
            if (stealth_bonus != 0.0 || weapon_strength != 0.0 || staff_power != 0.0) {
                cout << "Character " << character_id << " already has equipment" << endl;
            } else {
                stealth_bonus = value;
            }
        } 
        else {
            cout << "Invalid equipment type: " << equipment_type << endl;
        }
    }

    virtual void printAttributes() const {
        cout << character_id << " strength " << base_strength + weapon_strength
             << " mana " << base_mana + 2.0 * staff_power
             << " agility " << base_agility + stealth_bonus << endl;
    }
};

class Warrior : public Character {
public:
    Warrior(string id) : Character(id) {}

    double calculatePower() const override {
        return (base_strength + weapon_strength) * 1.5 + base_mana * 0.5 + base_agility * 0.8;
    }

    void upgrade() override {
        if (level < max_level) {
            base_strength *= 1.1;
            level++;
        } else {
            cout << "Character " << character_id << " is already at max level" << endl;
        }
    }
};

class Mage : public Character {
public:
    Mage(string id) : Character(id) {}

    double calculatePower() const override {
        return (base_mana + 2.0 * staff_power) * 2.0 + base_strength * 0.6 + base_agility * 0.7;
    }

    void upgrade() override {
        if (level < max_level) {
            base_mana *= 1.2;
            level++;
        } else {
            cout << "Character " << character_id << " is already at max level" << endl;
        }
    }
};

class Rogue : public Character {
public:
    Rogue(string id) : Character(id) {}

    double calculatePower() const override {
        return (base_agility + stealth_bonus) * 1.8 + base_strength * 0.6 + base_mana * 0.4;
    }

    void upgrade() override {
        if (level < max_level) {
            base_agility *= 1.15;
            level++;
        } else {
            cout << "Character " << character_id << " is already at max level" << endl;
        }
    }
};

class System {
private:
    unordered_map<string, Character *> characters;
    unordered_map<string, vector<string>> teams;

public:
    ~System() {
        for (auto &pair : characters) delete pair.second;
    } 

    void addCharacter(const string &role, const string &id) {
        if (characters.find(id) != characters.end()) return;
        if (role == "Warrior") characters[id] = new Warrior(id);
        else if (role == "Mage") characters[id] = new Mage(id);
        else if (role == "Rogue") characters[id] = new Rogue(id);
    }

    void setAttribute(const string &id, const string &attribute, double value) {
        if (characters.find(id) != characters.end())
            characters[id]->setAttribute(attribute, value);
    }

    void equip(const string &id, const string &equipment_type, double value) {
        if (characters.find(id) != characters.end())
            characters[id]->equip(equipment_type, value);
    }

    void listCharacters(const string &mode) {
        vector<Character *> character_list;
        for (auto &pair : characters) character_list.push_back(pair.second);

        if (mode == "Normal") {
            sort(character_list.begin(), character_list.end(), [](Character *a, Character *b) {
                int num_a = stoi(a->getId().substr(1)); // 保留 character_id 提取数字部分逻辑
                int num_b = stoi(b->getId().substr(1));
                return num_a < num_b;
            });
        }else if (mode == "Power") {
            sort(character_list.begin(), character_list.end(), [](Character *a, Character *b) {
                // 首先按照战力降序排序
                double power_a = a->calculatePower();
                double power_b = b->calculatePower();
                
                if (power_a == power_b) {
                    int num_a = stoi(a->getId().substr(1)); // 保留 character_id 提取数字部分逻辑
                    int num_b = stoi(b->getId().substr(1));
                    return num_a < num_b;
                }
                
                // 按照战力降序排序
                return power_a > power_b;
            });
        }
        for (const auto &character : character_list) character->printAttributes();
    }

    void upgradeCharacter(const string &id) {
        if (characters.find(id) != characters.end()) characters[id]->upgrade();
    }

    void battle(const string &id1, const string &id2) {
        if (characters.find(id1) != characters.end() && characters.find(id2) != characters.end()) {
            double power1 = characters[id1]->calculatePower();
            double power2 = characters[id2]->calculatePower();

            if (fabs(power1 - power2) / max(power1, power2) < 0.1) {
                cout << "Draw" << endl;
            } else {
                cout << (power1 > power2 ? id1 : id2) << " wins" << endl;
            }
        }
    }

    void addTeam(const string &team_id, const vector<string> &member_ids) {
        if (teams.find(team_id) != teams.end()) {
            cout << "Team " << team_id << " already exists" << endl;
            return;
        }
        for (const auto &id : member_ids) {
            if (characters.find(id) == characters.end()) {
                cout << "Character " << id << " does not exist" << endl;
                return;
            }
        }
        teams[team_id] = member_ids;
    }

    void modifyTeam(const string &team_id, const string &attribute, double value) {
        if (teams.find(team_id) == teams.end()) {
            cout << "Team " << team_id << " does not exist" << endl;
            return;
        }
        for (const auto &id : teams[team_id]) {
            if (characters.find(id) != characters.end()) {
                characters[id]->setAttribute(attribute, value);
            }
        }
    }

    void powerList() {
        vector<pair<string, double>> power_list;
        for (const auto &pair : characters) {
            power_list.emplace_back(pair.first, pair.second->calculatePower());
        }

        sort(power_list.begin(), power_list.end(), [](const pair<string, double> &a, const pair<string, double> &b) {
            int num_a = stoi(a.first.substr(1)); // 保留 character_id 提取数字部分逻辑
            int num_b = stoi(b.first.substr(1));
            return num_a < num_b;
        });

        for (const auto &entry : power_list) {
            cout << entry.first << " power: " << entry.second << endl;
        }
    }
};

void interactiveMode(System &system) {
    int n;
    cin >> n;
    cin.get();
    string command;
    for (int i = 0; i < n; i++) {
        getline(cin, command);
        if (command.empty()) continue;

        stringstream ss(command);
        string action;
        ss >> action;

        if (action == "Add") {
            string role, id;
            ss >> role >> id;
            system.addCharacter(role, id);
        } 
        else if (action == "Set") {
            string id, attribute;
            double value;
            ss >> id >> attribute >> value;
            system.setAttribute(id, attribute, value);
        } 
        else if (action == "Equip") {
            string id, equipment_type;
            double value;
            ss >> id >> equipment_type >> value;
            system.equip(id, equipment_type, value);
        } 
        else if (action == "List") {
            string mode;
            ss >> mode;
            system.listCharacters(mode);
        } 
        else if (action == "Upgrade") {
            string id;
            ss >> id;
            system.upgradeCharacter(id);
        } 
        else if (action == "Battle") {
            string id1, id2;
            ss >> id1 >> id2;
            system.battle(id1, id2);
        } 
        else if (action == "Team") {
            string team_id, member_id;
            vector<string> members;
            ss >> team_id;
            while (ss >> member_id) {
                members.push_back(member_id);
            }
            system.addTeam(team_id, members);
        } 
        else if (action == "Modify") {
            string team_id, attribute;
            double value;
            ss >> team_id >> attribute >> value;
            system.modifyTeam(team_id, attribute, value);
        } 
        else if (action == "PowerList") {
            system.powerList();
        } 
        else {
            cout << "Invalid command" << endl;
        }
    }
}

int main() {
    System system;
    interactiveMode(system);
    return 0;
}
