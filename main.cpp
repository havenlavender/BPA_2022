#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// prints out all menu items and their price
void displayMenu(vector<pair<string, float>>& menu);

// seperates a string by spaces returning a vector of strings
vector<string> splitString(string s);

int main()
{
    // initalize some variables
    vector<pair<string, float>> menu{};
    string input{};

    // open up the menu
    ifstream in;
    in.open("menu.txt");

    // load in all the menu items from the text file
    if (in.fail()) cerr << "failed to open menu";
    while (!in.fail())
    {
        string item;
        float price;

        in >> item;
        in >> price;

        if (item != "") menu.push_back(pair<string, float>(item, price));
    }

    in.close();
    
    displayMenu(menu);

    while (true)
    {
        float price = 0;
        int items = 0;

        cout << "Enter order in format of num1 item1 num2 item2 ..." << endl;
        getline(cin, input);
        vector<string> order = splitString(input);

        // make sure there is a correct amount of tokens in the string
        while (order.size() % 2 == 1 || order.size() == 0)
        {
            cout << "improper # of tokens - ensure input is in format num1 item1 num2 item2 ..." << endl;
            getline(cin, input);
            order = splitString(input);
        }

        // loop through the order
        for (int i = 0; i < order.size(); i += 2)
        {
            bool valid = false;
            int quantity = 0;
            string name = order[i + 1];

            // turn the quantity into a int
            try { quantity = stoi(order[i]); }
            catch (exception e) { cout << '"' << order[i] << "\" is not a number, please verify format" << endl; }

            // check if the requested item is in the menu
            for (int j = 0; j < menu.size(); j++)
            {
                if (menu[j].first == name)
                {
                    price += menu[j].second * quantity;
                    items += quantity;
                    
                    valid = true;
                    break;
                }
            }
          
            // if the item isn't present, let the user know
            if (!valid) cout << '"' << name << "\" was not found!" << endl;
        }

        // verify their purchase or let the user know there was an error
        if (items > 0) cout << "purchasing " << items << " items for $" << price << endl;
        else cout << "no items were found in menu, please enter again" << endl;
        cout << endl;
    }
}

void displayMenu(vector<pair<string, float>>& menu)
{
    cout << "Store Menu:" << endl;
    for (int i = 0; i < menu.size(); i++)
    {
        cout << "  " << menu[i].first << " for " << menu[i].second << endl;
    }
    cout << endl;
}

vector<string> splitString(string s)
{
    vector<string> output{};
    string subs = "";
    while (s.size() > 0)
    {
        char token = s[0];
        s.erase(s.begin());
        if (token != ' ') subs.push_back(token);
        else {
            output.push_back(subs);
            subs = "";
        }
    }

    if (subs != "") output.push_back(subs);
    return output;
}
