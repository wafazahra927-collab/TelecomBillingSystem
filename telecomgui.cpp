#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h> // Colors aur Sleep ke liye
#include <conio.h>   // Password hidden rakhne ke liye
using namespace std;
const int MAX = 100;
int custID[MAX];
string custName[MAX];
string custPlan[MAX];
float prepaidBal[MAX];
float postpaidBill[MAX];
int total = 0;
void drawHeader(string title) {
    system("cls");
    cout << "\t\t" << (char)201; for(int i=0; i<40; i++) cout << (char)205; cout << (char)187 << endl;
    cout << "\t\t" << (char)186 << "  " << left << setw(38) << title << (char)186 << endl;
    
    cout << "\t\t" << (char)200; for(int i=0; i<40; i++) cout << (char)205; cout << (char)188 << endl;
}
void loadingBar() {
    cout << "\n\n\n\t\tInitializing System... Please Wait\n\t\t";
    for(int i=0; i<40; i++) {
        cout << (char)219;
        Sleep(30);
    }
    system("cls");
}
void login() {
    string user = "", pass = "";
    char ch;
    cout << "\n\n\n\t\t" << (char)201 << "------- LOGIN TO SYSTEM -------" << (char)187 << endl;
    cout << "\t\t\tUsername: "; cin >> user;
    cout << "\t\t\tPassword: ";
    while((ch = _getch()) != 13) { 
        pass += ch;
        cout << '*'; 
    }
    if (user == "admin" && pass == "123") {
        cout << "\n\n\t\t[SUCCESS] Access Granted!";
        Sleep(1000);
    } else {
        cout << "\n\n\t\t[FAILED] Invalid Credentials!";
        Sleep(1000);
        system("cls");
        login();
    }
}
// --- ORIGINAL LOGIC (Unchanged) ---
int findCustomer(int id) {
    for (int i = 0; i < total; i++) {
        if (custID[i] == id) return i;
    }
    return -1;
}
void line() {
    cout << "\t\t--------------------------------------------------" << endl;
}
void customerMenu() {
    int choice;
    do {
        drawHeader("CUSTOMER MANAGEMENT");
        cout << "\t\t1. Add Customer" << endl;
        cout << "\t\t2. Update Customer" << endl;
        cout << "\t\t3. Delete Customer" << endl;
        cout << "\t\t4. View All Customers" << endl;
        cout << "\t\t5. Back to Main Menu" << endl;
        line();
        cout << "\t\tEnter choice: ";
        cin >> choice;
        if (choice == 1) {
            int id;
            cout << "\t\tEnter Customer ID: "; cin >> id;
            if (findCustomer(id) != -1) { cout << "\t\tCustomer already exists!" << endl; Sleep(1000); continue; }
            custID[total] = id;
            cout << "\t\tEnter Customer Name: "; cin >> custName[total];
            int planChoice;
            cout << "\t\tSelect Plan (1.Prepaid / 2.Postpaid): "; cin >> planChoice;
            if (planChoice == 1) {
                custPlan[total] = "Prepaid";
                cout << "\t\tEnter Initial Balance: "; cin >> prepaidBal[total];
                postpaidBill[total] = 0;
            } else {
                custPlan[total] = "Postpaid";
                prepaidBal[total] = 0;
                postpaidBill[total] = 0;
            }
            total++;
            cout << "\t\tCustomer added successfully!"; Sleep(1000);
        }
         else if (choice == 2) {
            int id;
            cout<<"Enter Customer ID to update: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                cout<<"Enter new name: ";
                cin>>custName[index];
                cout<<"Customer updated successfully!"<<endl;
            }
        }
        else if (choice == 3) {
            int id;
            cout<<"Enter Customer ID to delete: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                for (int i = index; i < total - 1; i++) {
                    custID[i] = custID[i + 1];
                    custName[i] = custName[i + 1];
                    custPlan[i] = custPlan[i + 1];
                    prepaidBal[i] = prepaidBal[i + 1];
                    postpaidBill[i] = postpaidBill[i + 1];
                }
                total--;
                cout<<"Customer deleted successfully!"<<endl;
            }
        }
        else if (choice == 4) {
            system("cls");
            drawHeader("VIEWING ALL CUSTOMERS");
            if (total == 0) cout << "\t\tNo customers available." << endl;
            else {
                cout << left << "\t\t" << setw(10) << "ID" << setw(15) << "Name" << setw(12) << "Plan" << setw(10) << "Bal/Bill" << endl;
                line();
                for (int i = 0; i < total; i++) {
                    cout << left << "\t\t" << setw(10) << custID[i] << setw(15) << custName[i] << setw(12) << custPlan[i] << setw(10) << (custPlan[i] == "Prepaid" ? prepaidBal[i] : postpaidBill[i]) << endl;
                }
            }
            cout << "\n\t\tPress any key to return..."; getch();
        }
    } while (choice != 5);
}
// Baki menus (usageMenu, billingMenu etc) mein bhi drawHeader use kiya hai
void usageMenu() {
    int choice;
    do {
        drawHeader("USAGE & SERVICES");
        cout << "\t\t1. Record Call" << endl;
        cout << "\t\t2. Recharge Prepaid" << endl;
        cout << "\t\t3. Back" << endl;
        line();
        cout << "\t\tChoice: "; cin >> choice;
        if (choice == 1) {
            int id;
            float minutes;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
                continue;
            }
            cout<<"Enter Call Duration (minutes): ";
            cin>>minutes;
            float rate = 2.0;
            if (custPlan[index] == "Prepaid") {
                float cost = minutes * rate;
                if (prepaidBal[index] >= cost) {
                    prepaidBal[index] -= cost;
                    cout<<"Call recorded. Balance updated."<<endl;
                } else {
                    cout<<"Insufficient balance!"<<endl;
                }
            } else {
                postpaidBill[index] += minutes * rate;
                cout<<"Call recorded. Bill updated."<<endl;
            }
        }
        else if (choice == 2) {
            int id;
            float amount;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);

            if (index == -1 || custPlan[index] != "Prepaid") {
                cout<<"Invalid prepaid customer!"<<endl;
                continue;
            }
            cout<<"Enter Recharge Amount: ";
            cin>>amount;
            prepaidBal[index] += amount;
            cout<<"Recharge successful!"<<endl;
        }
    } while (choice != 3);
}
void billingMenu() {
    int choice;
    do {
        line();
        cout<<"BILLING & PAYMENTS MENU"<<endl;
        cout<<"1. View Bill / Balance"<<endl;
        cout<<"2. Pay Postpaid Bill"<<endl;
        cout<<"3. Back to Main Menu"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        if (choice == 1) {
            int id;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1) {
                cout<<"Customer not found!"<<endl;
            } else {
                if (custPlan[index] == "Prepaid")
                    cout<<"Remaining Balance: "<<prepaidBal[index]<<endl;
                else
                    cout<<"Total Bill: "<<postpaidBill[index]<<endl;
            }
        }
        else if (choice == 2) {
            int id;
            float amount;
            cout<<"Enter Customer ID: ";
            cin>>id;
            int index = findCustomer(id);
            if (index == -1 || custPlan[index] != "Postpaid") {
                cout<<"Invalid postpaid customer!"<<endl;
                continue;
            }
            cout<<"Current Bill: "<<postpaidBill[index]<<endl;
            cout<<"Enter Payment Amount: ";
            cin>>amount;
            if (amount <= postpaidBill[index]) {
                postpaidBill[index] -= amount;
                cout<<"Payment successful!"<<endl;
            } else {
                cout<<"Amount exceeds bill!"<<endl;
            }
        }
    } while (choice != 3);
}
void searchMenu() {
    int id;
    cout<<"Enter Customer ID to search: ";
    cin>>id;
    int index = findCustomer(id);

    if (index == -1) {
        cout<<"Customer not found!"<<endl;
    } else {
        cout<<"Name: "<<custName[index]<<endl;
        cout<<"Plan: "<<custPlan[index]<<endl;
    }
}
int main() {
    // GUI SETUP
    system("color f0"); // Professional White Screen
    loadingBar();
    login();
    int choice;
    do {
        drawHeader("TELECOM BILLING SYSTEM");
        cout << "\t\t1. Customer Management" << endl;
        cout << "\t\t2. Usage & Services" << endl;
        cout << "\t\t3. Billing & Payments" << endl;
        cout << "\t\t4. Search & Reports" << endl;
        cout << "\t\t5. Exit" << endl;
        line();
        cout << "\t\tEnter choice: "; cin >> choice;
        if (choice == 1) customerMenu();
        else if (choice == 2) usageMenu();
        else if (choice== 3)billingMenu();
        else if(choice == 4)searchMenu();
        else if (choice == 5) {
            system("cls");
            drawHeader("EXITING SYSTEM...");
            Sleep(1000);
        }
    } while (choice != 5);
    return 0;
}