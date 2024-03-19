#include <iostream>
#include <fstream>
#include <string>

			/*SUPERMARKET BILLING  SYSTEM */

using namespace std;

class Shopping {
private:
    int pcode;
    string pname;
    float price;
    float discount;
    string username="nagesh";
    string pass="nagesh";

public:  //function prototypes 
    void menu(); 
    bool Authentication();
    void administrator();
    void buyer();
    void add();
    void rem();
    void list();
    void receipt();
    void edit();
};

bool Shopping::Authentication(){

            string user,pas;
            cout << "\t\t\t\t--------Authentication--------" << endl;
            cout << "\t\t\t\t Enter your Username: " ;
            cin>>user;
            cout << "\t\t\t\t Enter your Password: " ;
            cin>>pas;
            if(username==user && pass==pas){
                return true;
            }
            else{
                return false;
            }
}

void Shopping::menu() {
    int choice;

    while (true) {
        cout << "\t\t\t\t ________________________" << endl;
        cout << "\t\t\t\t|                        |" << endl;
        cout << "\t\t\t\t| Supermarket Main Menu  |" << endl;
        cout << "\t\t\t\t|                        |" << endl;
        cout << "\t\t\t\t| 1) Administrator       |" << endl;
        cout << "\t\t\t\t| 2) Buyer               |" << endl;
        cout << "\t\t\t\t| 3) Exit                |" << endl;
        cout << "\t\t\t\t|________________________|" << endl;

        cout << "\t\t\t\tPlease Select one Option: ";
        cin >> choice;

        switch (choice) {

            case 1:
            
            if(Authentication()==true){
                cout << "\t\t\t\t------------------------------------"<<endl;
                cout << "\t\t\t\tAdministrator Logged In Successfully!!";

                administrator();

            }
            else{
                cout<<"Invalid username OR password"<<endl;
            }                
                break;
            case 2:
                buyer();
                break;
            case 3:
                exit(0);
            default:
                cout << "Please Select from the given options." << endl;
        }
    }
}

void Shopping::administrator() {
    int choice;

    while (true) {
        cout << "\t\t\t\t _______________________________" << endl;
        cout << "\t\t\t\t|-------------------------------|" << endl;
        cout << "\t\t\t\t|  1) Add the Product           |" << endl;
        cout << "\t\t\t\t|  2) Modify the Product        |" << endl;
        cout << "\t\t\t\t|  3) Delete the Product        |" << endl;
        cout << "\t\t\t\t|  4) List all Products         |" << endl;
        cout << "\t\t\t\t|  5) Generate Receipt          |" << endl;
        cout << "\t\t\t\t|  6) Back to main menu         |" << endl;
        cout << "\t\t\t\t|_______________________________|" << endl;
        cout << "\t\t\t\t Please Enter the Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                rem();
                break;
            case 4:
                list();
                break;
            case 5:
                receipt();
                break;
            case 6:
                return;
            default:
                cout << "Invalid Choice!" << endl;
        }
    }
}

void Shopping::buyer() {
    int choice;

    while (true) {
        cout << "\t\t\t ------ Buyer------" << endl;
        cout << "\t\t\t __________________" << endl;
        cout << "\t\t\t  1) Buy Product	  " << endl;
        cout << "\t\t\t  2) Go Back		  " << endl;
        cout << "\t\t\t  Enter your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                receipt();
                break;
            case 2:
                return;
            default:
                cout << "Invalid Choice!" << endl;
        }
    }
}

void Shopping::add() {
    ofstream data("database.txt", ios::app);
    if (!data) {
        cout << "Error: Cannot open file." << endl;
        return;
    }

    cout<<endl;
    cout << "\n\n\t\t-----------Add New Product------------";
    cout << "\n\n\t Product code of Product: ";
    cin >> pcode;
    cout << "\n\n\t Name of the Product: ";
    cin >> pname;
    cout << "\n\n\t Price of the Product: ";
    cin >> price;
    cout << "\n\n\t Discount on Product: ";
    cin >> discount;
    cout<<endl;

    data << pcode << " " << pname << " " << price << " " << discount << endl;
    data.close();

    cout << "\n\n\t\t Record Inserted!" << endl;
}

void Shopping::edit() {
    ifstream data("database.txt");
    ofstream temp("temp.txt");
    if (!data || !temp) {
        cout << "Error: Cannot open file." << endl;
        return;
    }

    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the Record ";
    cout << "\n\t\t\t Product Code: ";
    cin >> pkey;

    while (data >> pcode >> pname >> price >> discount) {
        if (pkey == pcode) {
            cout << "\n\t\t Product New Code: ";
            cin >> c;
            cout << "\n\t\t Name of the Product: ";
            cin >> n;
            cout << "\n\t\t Price: ";
            cin >> p;
            cout << "\n\t\t Discount: ";
            cin >> d;
            temp << c << " " << n << " " << p << " " << d << endl;
            cout << "\n\n\t\t Record edited." << endl;
            token++;
        } else {
            temp << pcode << " " << pname << " " << price << " " << discount << endl;
        }
    }
    data.close();
    temp.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (token == 0) {
        cout << "\n\n Record not Found, Sorry!" << endl;
    }
}

void Shopping::rem() { 
    ifstream data("database.txt");
    ofstream temp("temp.txt");
    if (!data || !temp) {
        cout << "Error: Cannot open file." << endl;
        return;
    }

    int pkey;
    int token = 0;

    cout << "\n\n\t ----Delete Product----";
    cout << "\n\n\t 	Product code:     ";
    cin >> pkey;

    while (data >> pcode >> pname >> price >> discount) {
        if (pcode == pkey) {
            cout << "\n\n\t Product deleted Successfully." << endl;
            token++;
        } else {
            temp << pcode << " " << pname << " " << price << " " << discount << endl;
        }
    }
    data.close();
    temp.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (token == 0) {
        cout << "\n\n Record not found!" << endl;
    }
}

void Shopping::list() {
    ifstream data("database.txt");
    if (!data) {
        cout << "Error: Cannot open file." << endl;
        return;
    }

    cout << "\n\n |\n";
    cout << "Product No \t Name \t\t price \n";
    cout << "\n\n |_\n";
    while (data >> pcode >> pname >> price >> discount) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
    }
    data.close();
}

void Shopping::receipt() {
    ifstream data("database.txt");
    if (!data) {
        cout << "Error: Cannot open file." << endl;
        return;
    }

    int arrc[100]; // size of array product codes
    int arrq[100]; 
    char choice = 0;
    int c = 0;
    float amount = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t----RECEIPT----";
    list();
    cout << "\------------------------------\n";
    cout << "\n						    	\n";
    cout << "\n		Please place the order	\n";
    cout << "\n							    \n";
    cout << "\n-----------------------------\n";
    do {
        cout << "\n\n Enter Product Code: ";
        cin >> arrc[c];
        cout << "\n\n Enter the product quantity: ";
        cin >> arrq[c];
        for (int i = 0; i < c; i++) {
            if (arrc[c] == arrc[i]) {
                cout << "\n\n Duplicate Product code. Please try again !" << endl;
                goto m;
            }
        }
        c++;
        cout << "\n\n Do you want to buy another Product? Press 'y' for yes, or 'n' for no: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t__RECEIPT\n";
    cout << "\n Product No \t Product Name \t Product quantity \t price \t amount with discount \n";

    for (int i = 0; i < c; i++) {
        data.clear();
        data.seekg(0, ios::beg);
        while (data >> pcode >> pname >> price >> discount) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                float discountedAmount = amount - (amount * discount / 100);
                total += discountedAmount;
                cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << discountedAmount << endl;
            }
        }
    }
    data.close();
    cout << "\n\n______";
    cout << "\n	Total Amount: " << total << endl;

m:
    return;
}

int main() {
    Shopping s;
    s.menu();
    return 0;
}
