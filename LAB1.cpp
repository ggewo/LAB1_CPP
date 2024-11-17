#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
using namespace std;

double ValidatePositiveNumber(const string& prompt) {
    string input;
    double number = -1.0;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input.empty()) {
            cout << "Error: Input cannot be empty. Try again.\n";
            continue;
        }

        if (input.size() > 1 && input[0] == '0' && input[1] != '.') {
            cout << "Error: Leading zeros are not allowed. Try again.\n";
            continue;
        }

        try {
            size_t idx;
            number = stod(input, &idx);

            if (idx != input.length() || number <= 0) {
                throw invalid_argument("Invalid input");
            }
            break;
        } catch (...) {
            cout << "Error: Please enter a valid positive number. Try again.\n";
        }
    }
    return number;
}

bool VAlidateBooleanInput(const string& prompt) {
    string input;

    while (true) {
        cout << prompt;
        getline(cin, input);

        if (input == "1") {
            return true;
        } else if (input == "0") {
            return false;
        } else {
            cout << "Error: Please enter 1 for 'Yes' or 0 for 'No'. Try again.\n";
        }
    }
}

struct Pipe {
    string name;
    double length;
    double diameter;
    bool inRepair;
};

struct KS {
    string name;
    int quantity;
    int quantityActive;
    double efficiency;
};

void ShowMenu() {
    cout << "1. Add pipe\n";
    cout << "2. Add KS\n";
    cout << "3. View all the objects\n";
    cout << "4. Edit pipe\n";
    cout << "5. Edit KS\n";
    cout << "6. Save\n";
    cout << "7. Download\n";
    cout << "0. Exit\n";
    cout << "Enter action number: \n";
}

Pipe AddPipe() {
    Pipe pipe;
    cout << "Enter the name of the pipe: ";
    cin.ignore();
    getline(cin, pipe.name);

    pipe.length = ValidatePositiveNumber("Enter the length of the pipe in km: ");
    pipe.diameter = ValidatePositiveNumber("Enter the diameter of the pipe in m: ");
    pipe.inRepair = VAlidateBooleanInput("Is the pipe in repair? (1 - 'Yes', 0 - 'No'): ");

    return pipe;
}

KS AddKS() {
    KS ks;
    cout << "Enter the name of KS: ";
    cin.ignore();
    getline(cin, ks.name);

    ks.quantity = static_cast<int>(ValidatePositiveNumber("Enter the total number of workshops: "));
    ks.quantityActive = static_cast<int>(ValidatePositiveNumber("Enter the number of active workshops: "));
    while (ks.quantityActive > ks.quantity) {
        cout << "Error: Active workshops cannot exceed total workshops. Try again.\n";
        ks.quantityActive = static_cast<int>(ValidatePositiveNumber("Enter the number of active workshops: "));
    }
    ks.efficiency = ValidatePositiveNumber("Enter the efficiency: ");

    return ks;
}

void EditPipe(Pipe& pipe) {
    if (!pipe.name.empty()) {
        string input;

        do {
            cout << "\nEditing Pipe:\n";
            cout << "1. Edit name (current: " << pipe.name << ")\n";
            cout << "2. Edit length (current: " << pipe.length << ")\n";
            cout << "3. Edit diameter (current: " << pipe.diameter << ")\n";
            cout << "4. Edit repair status (current: " << (pipe.inRepair ? "Yes" : "No") << ")\n";
            cout << "0. Finish Editing\n";
            cout << "Choose a parameter to edit: ";
            getline(cin, input);

            
            if (input.length() == 1 && input[0] >= '0' && input[0] <= '4') {
                int choice = input[0] - '0'; 

                switch (choice) {
                    case 1:
                        cout << "Enter new name: ";
                        getline(cin, pipe.name);
                        break;
                    case 2:
                        pipe.length = ValidatePositiveNumber("Enter new length: ");
                        break;
                    case 3:
                        pipe.diameter = ValidatePositiveNumber("Enter new diameter: ");
                        break;
                    case 4:
                        pipe.inRepair = VAlidateBooleanInput("Enter new repair status (1 - if 'Yes', 0 - if 'No'): ");
                        break;
                    case 0:
                        cout << "Finished editing pipe.\n";
                        break;
                    default:
                        
                        break;
                }
            } else {
                cout << "Error: Please enter a valid choice (0-4).\n";
            }
        } while (input != "0"); 
    } else {
        cout << "No pipe to edit.\n";
    }
}

void EditKS(KS& ks) {
    if (!ks.name.empty()) {
        string input;

        do {
            cout << "\nEditing KS:\n";
            cout << "1. Edit name (current: " << ks.name << ")\n";
            cout << "2. Edit total workshops (current: " << ks.quantity << ")\n";
            cout << "3. Edit active workshops (current: " << ks.quantityActive << ")\n";
            cout << "4. Edit efficiency (current: " << ks.efficiency << ")\n";
            cout << "0. Finish Editing\n";
            cout << "Choose a parameter to edit: ";
            getline(cin, input);

            
            if (input.length() == 1 && input[0] >= '0' && input[0] <= '4') {
                int choice = input[0] - '0'; 

                switch (choice) {
                    case 1:
                        cout << "Enter new name: ";
                        getline(cin, ks.name);
                        break;

                    case 2:
                        ks.quantity = static_cast<int>(ValidatePositiveNumber("Enter new total workshops: "));
                        break;

                    case 3:
                        ks.quantityActive = static_cast<int>(ValidatePositiveNumber("Enter new active workshops: "));
                        while (ks.quantityActive > ks.quantity) {
                            cout << "Error: Active workshops cannot exceed total workshops. Try again.\n";
                            ks.quantityActive = static_cast<int>(ValidatePositiveNumber("Enter new active workshops: "));
                        }
                        break;

                    case 4:
                        ks.efficiency = ValidatePositiveNumber("Enter new efficiency: ");
                        break;

                    case 0:
                        cout << "Finished editing KS.\n";
                        break;

                    default:
                        break;
                }
            } else {
                cout << "Error: Please enter a valid choice (0-4).\n";
            }
        } while (input != "0"); 
    } else {
        cout << "No KS to edit.\n";
    }
}

void SaveDataToFile(const Pipe& pipe, const KS& ks, bool pipeAdded, bool ksAdded) {
    ofstream file("data.txt");
    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    if (pipeAdded || ksAdded) {
        if (pipeAdded) {
            file << "Pipe Information:\n";
            file << "Name of the pipe: " << pipe.name << "\n";
            file << "Length of the pipe: " << pipe.length << "\n";
            file << "Diameter of the pipe: " << pipe.diameter << "\n";
            file << "In repair: " << (pipe.inRepair ? "Yes" : "No") << "\n\n";
        } else {
            file << "No pipe information available.\n\n";
        }

        if (ksAdded) {
            file << "KS Information:\n";
            file << "Name of the KS: " << ks.name << "\n";
            file << "Number of workshops: " << ks.quantity << "\n";
            file << "Number of active workshops: " << ks.quantityActive << "\n";
            file << "Efficiency: " << ks.efficiency << "\n";
        } else {
            file << "No KS information available.\n";
        }
    } else {
        file << "No information about pipes and KS.\n";
    }
    file.close();
    cout << "Data saved successfully to 'data.txt'.\n";
}

void LoadFromFile(Pipe& pipe, KS& ks, bool& pipeAdded, bool& ksAdded) {
    ifstream inFile("data.txt");
    if (!inFile.is_open()) {
        cout << "Error: Unable to open the file.\n";
        return;
    }

    string line;
    bool pipeLoaded = false, ksLoaded = false;

    while (getline(inFile, line)) {
        try {
            if (line == "Pipe Information:") {
                
                getline(inFile, line);
                pipe.name = line.substr(line.find(":") + 2);

                getline(inFile, line);
                pipe.length = stod(line.substr(line.find(":") + 2));
                if (pipe.length <= 0) throw invalid_argument("Invalid pipe length");

                getline(inFile, line);
                pipe.diameter = stod(line.substr(line.find(":") + 2));
                if (pipe.diameter <= 0) throw invalid_argument("Invalid pipe diameter");

                getline(inFile, line);
                string repairStatus = line.substr(line.find(":") + 2);
                pipe.inRepair = (repairStatus == "Yes");

                pipeLoaded = true;
            } else if (line == "KS Information:") {
                
                getline(inFile, line);
                ks.name = line.substr(line.find(":") + 2);

                getline(inFile, line);
                ks.quantity = stoi(line.substr(line.find(":") + 2));
                if (ks.quantity <= 0) throw invalid_argument("Invalid workshop count");

                getline(inFile, line);
                ks.quantityActive = stoi(line.substr(line.find(":") + 2));
                if (ks.quantityActive < 0 || ks.quantityActive > ks.quantity) {
                    throw invalid_argument("Invalid active workshop count");
                }

                getline(inFile, line);
                ks.efficiency = stod(line.substr(line.find(":") + 2));
                if (ks.efficiency <= 0) throw invalid_argument("Invalid efficiency");

                ksLoaded = true;
            }
        } catch (...) {
            cout << "Error: Data in the file is incorrect.\n";
            pipeLoaded = false;
            ksLoaded = false;
            break;
        }
    }

    inFile.close();

    if (pipeLoaded) {
        pipeAdded = true;
        cout << "Pipe data loaded successfully.\n";
    } else {
        cout << "No valid pipe data found.\n";
        pipeAdded = false;
    }

    if (ksLoaded) {
        ksAdded = true;
        cout << "KS data loaded successfully.\n";
    } else {
        cout << "No valid KS data found.\n";
        ksAdded = false;
    }
}

int main() {
    Pipe pipe;
    KS ks;
    bool pipeAdded = false;
    bool ksAdded = false;

    string input;

    while (true) {
        ShowMenu();
        cout << "Enter your choice: ";
        getline(cin, input); 

        if (input.length() == 1 && input[0] >= '0' && input[0] <= '7') {
            int choice = input[0] - '0'; 

            switch (choice) {
                case 1:
                    cout << "Adding a pipe:\n";
                    pipe = AddPipe();
                    pipeAdded = true;
                    break;

                case 2:
                    cout << "Adding a KS:\n";
                    ks = AddKS();
                    ksAdded = true;
                    break;

                case 3:
                    cout << "Viewing all objects...\n";

                    if (pipeAdded) {
                        cout << "Info about the pipe:\n";
                        cout << "Name of the pipe: " << pipe.name << endl;
                        cout << "Length of the pipe: " << pipe.length << "km\n";
                        cout << "Diameter of the pipe: " << pipe.diameter << "m\n";
                        cout << "In repair: " << (pipe.inRepair ? "Yes" : "No") << endl;
                    } else {
                        cout << "Pipe not added or loaded.\n";
                    }

                    if (ksAdded) {
                        cout << "Info about the KS:\n";
                        cout << "Name of the KS: " << ks.name << endl;
                        cout << "Number of workshops: " << ks.quantity << endl;
                        cout << "Number of active workshops: " << ks.quantityActive << endl;
                        cout << "Efficiency: " << ks.efficiency << endl;
                    } else {
                        cout << "KS not added or loaded.\n";
                    }
                    break;

                case 4:
                    cout << "Editing pipe:\n";
                    EditPipe(pipe);
                    break;

                case 5:
                    cout << "Editing KS:\n";
                    EditKS(ks);
                    break;

                case 6:
                    cout << "Saving information...\n";
                    SaveDataToFile(pipe, ks, pipeAdded, ksAdded);
                    break;

                case 7:
                    cout << "Loading data from file...\n";
                    LoadFromFile(pipe, ks, pipeAdded, ksAdded);
                    break;

                case 0:
                    cout << "Exit the program.\n";
                    return 0;

                default:
                    break;
            }
        } else {
            cout << "Error: Please enter a valid choice (0-7).\n";
        }

        cout << endl;
    }
}