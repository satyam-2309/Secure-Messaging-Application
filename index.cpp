#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Simple XOR encryption
string encryptDecrypt(string data) {
    char key = 'K'; // secret key
    string output = data;
    for (int i = 0; i < data.size(); i++) {
        output[i] = data[i] ^ key;
    }
    return output;
}

// Function to login user
bool login(string name, string pass) {
    if ((name == "Kamlesh" && pass == "kam123") ||
        (name == "Satyam" && pass == "sat123") ||
        (name == "Aryan" && pass == "ary123")) {
        return true;
    }
    return false;
}

// Function to send message
void sendMessage(string sender) {
    string receiver, msg;
    cout << "Enter receiver name (Kamlesh/Satyam/Aryan): ";
    cin >> receiver;
    cin.ignore();
    cout << "Enter message: ";
    getline(cin, msg);

    string encryptedMsg = encryptDecrypt(msg);
    
    ofstream out("messages.txt", ios::app);
    out << "From: " << sender << " To: " << receiver << " => " << encryptedMsg << endl;
    out.close();

    cout << "Message sent (Encrypted)!\n";
}

// Function to view received messages
void viewMessages(string user) {
    ifstream in("messages.txt");
    string line;
    cout << "\n--- Messages for " << user << " ---\n";
    while (getline(in, line)) {
        if (line.find("To: " + user) != string::npos) {
            size_t pos = line.find("=>");
            if (pos != string::npos) {
                string enc = line.substr(pos + 3);
                cout << line.substr(0, pos) << "=> " << encryptDecrypt(enc) << endl;
            }
        }
    }
    in.close();
}

int main() {
    string name, pass;
    cout << "Enter your name (Kamlesh/Satyam/Aryan): ";
    cin >> name;
    cout << "Enter password: ";
    cin >> pass;

    if (login(name, pass)) {
        cout << "Login successful!\n";
        int choice;
        do {
            cout << "\n1. Send Message\n2. View Messages\n3. Exit\nEnter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: sendMessage(name); break;
                case 2: viewMessages(name); break;
                case 3: cout << "Bye!\n"; break;
                default: cout << "Invalid option!\n";
            }
        } while (choice != 3);
    } else {
        cout << "Login failed. Try again.\n";
    }

    return 0;
}
