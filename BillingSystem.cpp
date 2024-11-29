#include<iostream>
#include<fstream>
#include<sstream>
#include<windows.h>
using namespace std;

class Bill{
    private:
        string Item;
        int Quantity,Rate;
    public:
        Bill():Item(""),Quantity(0),Rate(0){}

        void setItem(string item)
        {
            Item=item;
        }
        void setQuantity(int quantity)
        {
            Quantity=quantity;
        }
        void setRate(int rate)
        {
            Rate=rate;
        }
        string getItem()
        {
            return Item;
        }
        int getQuantity()
        {
            return Quantity;
        }
        int getRate()
        {
            return Rate;
        }
};

void addItem(Bill b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "1)Add Item" << endl;
        cout << "2)close" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate, quant;

            cout << "Enter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "Enter Quantity Of Item: ";
            cin >> quant;
            b.setQuantity(quant);

            cout << "Enter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            ofstream out("Bill.txt", ios::app);
            if (!out)
            {
                cout << "Error: File Can't Open!" << endl;
            }
            else
            {
                out << b.getItem() << " : " <<  b.getQuantity()  << " : " << b.getRate() << endl<< endl;
            }
            out.close();
            cout << "Item Added Successfuly" << endl;
            Sleep(3000);
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "Back To Main Menu!" << endl;
            Sleep(3000);
        }
    }
}
void PrintBill()
{
    system("cls");
    int count=0;    // used to keep track of the total bill amount for all purchased items
    bool close=false;
    while(!close)
    {
        system("cls");
        int choice;
        cout<<"1)Add Bill"<<"\n";
        cout<<"2)Close Session"<<"\n";
        cout<<"Enter the Choice:";
        cin>>choice;

        if(choice==1)
        {
            string item;
            int quant;
            cout<<"Enter the item name:";
            cin>>item;
            cout<<"Enter the Quantity of that item:";
            cin>>quant;

            ifstream in("Bill.txt");
            ofstream out("Bill_Temp.txt");

            string storeItemData;
            bool found=false;
            while(getline(in,storeItemData))
            {
                stringstream ss;
                ss<<storeItemData;
                string itemname;
                int itemrate,itemquantity;
                char delimiter;
                ss>>itemname>>delimiter>>itemquantity>>delimiter>>itemrate;

                if(item==itemname)
                {
                    found=true;
                    if(quant <= itemquantity)
                    {
                        int amount = itemrate * quant;
                        cout<<"Item | Rate | Quantity | Amount"<<endl;
                        cout<<itemname<<"\t "<<itemrate<<"\t "<<quant<<"\t "<<amount<<endl;
                        int newQuant = itemquantity - quant;
                        itemquantity = newQuant;
                        count +=amount;

                        out<<itemname<<" : "<<itemrate<<" : "<<itemquantity<<endl;
                    }
                    else{
                        cout<<"Sorry, "<<item<<" Ended!"<<endl;
                    }
                } 
                else{
                    //item not found 
                    out<<storeItemData<<"\n";   
                } 
            }
            if(!found)
            {
                cout<<"Item Not Available!"<<endl;
            }
            out.close();
            in.close();
            remove("Bill.txt");
            rename("Bill_Temp.txt", "Bill.txt");
        }
        else if(choice==2)
        {
            close=true;
            cout<<"Counting Total Bill.."<<"\n";
        }
        Sleep(2000);
    }
    system("cls");
    cout<<"\n";
    cout<<"Total Bill is -------:"<<count<<"\n";
    cout<<"Thanks For Shopping!"<<endl;
    Sleep(5000);

}
int main()
{
    Bill b;
    bool exit=false;
    while(!exit)
    {
        system("cls");
        int choice;

        cout<<"Welcome To Super Market Billing System."<<"\n";
        cout<<"*******************************"<<"\n";
        cout<<"1)Add Item"<<"\n";
        cout<<"2)print Bill"<<"\n";
        cout<<"3)Exit"<<"\n";
        cout<<"Enter the Choice:";
        cin>>choice;

        if(choice==1)
        {
            system("cls");
            addItem(b);
            Sleep(3000);
        }
        else if(choice==2)
        {
            PrintBill();
        }
        else if(choice==3)
        {
            system("cls");
            exit = true;
            cout<<"Good Luck!"<<endl;
            Sleep(3000);
        }
    }
}