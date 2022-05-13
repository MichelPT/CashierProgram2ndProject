#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct customer_info
{
    string name;
    string menu_name[15];
    int price[15] = { 0 };
    int total_price = 0;
};

customer_info customer[30];


string menu[2][4][2] = {
{   {"Karaage", "20000"},
    {"Takoyaki", "17000"},
    {"Tonkatsu", "12000"},
    {"Meatball", "15000"}
} ,
{
    {"Cappuchino", "15000",},
    {"Mocachino", "15000",},
    {"Coffee  ", "16000"},
    {"Lemon Tea", "13000"}
}
};

int CountingTotalPrice(int*, int);

void menus() {
    

    cout << "Menu" << endl << "---------" << endl;
    int l = 1;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++) {
            cout << l << ". ";
            for (int k = 0; k < 2; k++)
            {
                cout << menu[i][j][k] << "\t\t";
                
            }
            l++;
            cout << endl;
        }
        cout << endl;
    }
}


int main() {
    int index=0, buffer = 0;
    int answer, quantity, chooseMenu;
    char orderMore;
    bool isEnough=true;

    do {
        system("cls");

        cout << "    MENU    \n";
        cout << "1. Order\n2. Order History\n3. Exit\n";
        cout << "Choose option : ";
        cin >> answer;

        switch (answer)
        {
        case 1:
        {
            ofstream myMenu;
            system("cls");
            int menu_index = 0;
            cout << "\n== ORDER ==\n" << "---------" << endl;
            menus();
            cout << "Customer Name: ";
            cin.ignore();
            getline(cin, customer[index].name);

            myMenu.open("Customer/" + customer[index].name + ".txt", ios::app);
            do
            {
                cout << "Choose menu: ";
                cin >> chooseMenu;
                if (0 < chooseMenu < 5)
                {
                    customer[index].menu_name[menu_index] = menu[0][chooseMenu - 1][0];
                    int temp = stoi(menu[0][chooseMenu - 1][1]);
                    customer[index].price[menu_index] = temp;
                }
                else if (4<chooseMenu<9)
                {
                    customer[index].menu_name[menu_index] = menu[1][chooseMenu - 1][0];
                    int temp = stoi(menu[0][chooseMenu - 1][1]);
                    customer[index].price[menu_index] = temp;
                } 
                else
                {
                    cout << "Please choose proper answer." << endl << endl;
                    system("pause");
                    system("cls");
                    break;
                }
                myMenu << customer[index].menu_name[menu_index] << "\tx";
                cout << "Menu Quantity: ";
                cin >> quantity;
                customer[index].price[menu_index] = customer[index].price[menu_index] * quantity;
                myMenu << " " << quantity << " = Rp "  << customer[index].price[menu_index] << endl;

                cout << "Do you want to order more menu?(y/n)";
                cin >> orderMore;
                if (orderMore == 'n')
                {
                    int totalPriceTemp = CountingTotalPrice(&index, 0);
                    customer[index].total_price = totalPriceTemp;
                    myMenu << "-----------------------------\nTotal Price \t= Rp " << totalPriceTemp << endl;
                    isEnough = false;
                }
                menu_index++;
            } while (isEnough);
            myMenu.close();
            cout << "The orer has been saved and ready to be processed." << endl;
            system("pause");
            system("cls");
            index++;
            break;
        }

        default:
            break;
        }

    } while (answer < 1 || answer > 3);

    return 0;
}


int CountingTotalPrice(int* x, int y) {
    if (customer[*x].price[y]==NULL)
    {
        return customer[*x].price[y];
    }
    else return customer[*x].price[y] + customer[*x].price[y + 1];
}