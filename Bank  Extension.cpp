// ===================================================================
// Same Previous Project with Extension Added
// Comments have been added to functions that were without comments
// Program: Simple Banking System for Managing Client Records
// ===================================================================

// Bank 1 Project Extension.cpp 
// A simple console-based banking system to manage client records (Add, Delete, Update, Find, and Display clients)

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;


const string FileName = "ClientsRecords.txt";

// Structure to store client data - contains all client information
struct stClientData
{
    string PinCode;
    string AccountNumber;
    string Name;
    string Phone;
    float AccountBalance;
};

// Main menu options enumeration
enum enMenuOptions { eShowList = 1, eAddNew, eDelete, eUpdateInfo, eFind, eTransaction ,eExit };

enum enTransactionsMenu { eDeposit = 1, eWithdraw , eTotalBalances , eMainMenu };

// Function to ask user to enter account number
string Ask4AccountNumber()
{
    string AccountNumber;


    cout << "Please Enter Account Number " << endl;
    getline(cin, AccountNumber);


    return AccountNumber;
}


// Function to split a string into parts based on a delimiter
// Example: "User#//#123" becomes ["User", "123"]
vector <string> SplitString(string S1, string Delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;


    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); //Store the Word
        if (sWord != Delim)
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());//Erasing until position and move to the next word

    }

    if (S1 != Delim)
    {
        vString.push_back(S1);
    }



    return  vString;
}

// Function to convert a text line from file into organized client data
stClientData ConvertLineToRecord(string Line, string Delim = "#//#")
{
    stClientData ClientData;
    vector <string> vClientData;

    vClientData = SplitString(Line, Delim);


    if (vClientData.size() >= 5)
    {
        ClientData.AccountNumber = vClientData[0];
        ClientData.PinCode = vClientData[1];
        ClientData.Name = vClientData[2];
        ClientData.Phone = vClientData[3];
        ClientData.AccountBalance = stof(vClientData[4]);
    }

    return ClientData;

}

// Function to read all clients data from file and store them in a list
vector<stClientData> LoadClientDataFromFile(string FileName)
{
    vector <stClientData> vClients;

    fstream ClientsRecords;

    ClientsRecords.open(FileName, ios::in);

    if (ClientsRecords.is_open())
    {
        string Line;
        stClientData Client;

        while (getline(ClientsRecords, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }
        ClientsRecords.close();
    }

    return vClients;


}


// Function to print one client record in a formatted line
void PrintClientRecord(stClientData ClientData)
{
    cout << "| " << setw(15) << left << ClientData.AccountNumber;
    cout << "| " << setw(10) << left << ClientData.PinCode;
    cout << "| " << setw(40) << left << ClientData.Name;
    cout << "| " << setw(12) << left << ClientData.Phone;
    cout << "| " << setw(12) << left << ClientData.AccountBalance;
}

// Function to check if an account number exists in the clients list
void CheckClient(string AccountNumber, vector<stClientData> vClientData)
{
    stClientData ClientData;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            cout << "Client With Account Number (" << AccountNumber << ") is Already exists , Please Enter Another Account Number ? ";
            return;
        }
    }


}

// Function to print a table containing all clients data
void PrintAllClientsData(vector <stClientData> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData ClientData : vClients)
    {
        PrintClientRecord(ClientData);
        cout << endl;
    }

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

// Function to print one client data in detail (each field in a separate line)
void PrintClientData(stClientData ClientData)
{
    cout << "Account Number : " << ClientData.AccountNumber << endl;
    cout << "Pin Code       : " << ClientData.PinCode << endl;
    cout << "Name           : " << ClientData.Name << endl;
    cout << "Phone          : " << ClientData.Phone << endl;
    cout << "Account Balance : " << ClientData.AccountBalance << endl;
}

// Function to delete a client record from file
void DeleteRecordFromFile()
{

    vector <stClientData> vClient = LoadClientDataFromFile(FileName);

    string AccountNumber;
    AccountNumber = Ask4AccountNumber();



    bool Found = false;
    stClientData Client;

    // Search for the client
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            Found = true;
            break;
        }
    }
    if (!Found)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return;

    }

    PrintClientData(Client);

    char Answer;

    cout << "\nAre you sure you want to delete this client? (y/n): ";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (Answer == 'Y' || Answer == 'y')
    {


        fstream ClientsRecords;

        ClientsRecords.open(FileName, ios::out);

        if (ClientsRecords.is_open())
        {
            // Rewrite all clients except the one to be deleted
            for (stClientData& Client : vClient)
            {
                //U can not Delete a line directly
                if (Client.AccountNumber != AccountNumber)
                {
                    ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;

                }
            }
            ClientsRecords.close();


        }

        cout << "\n\nClient Deleted Successfully !\n";
    }
    else
    {
        cout << "\nDeletion Cancelled\n";
    }
}

// Function to display the delete client screen
void DeleteClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tDelete Clients Screen";
    cout << "\n------------------------------------\n";

    DeleteRecordFromFile();
}

// Function to check if an account number exists in clients list (returns true if exists)
bool IsAccountNumberExist(string AccountNumber, vector<stClientData>& vClientData)
{
    for (const stClientData& Client : vClientData)
    {
        if (AccountNumber == Client.AccountNumber)
        {
            cout << "Client With Account Number (" << AccountNumber << ") already exists. Please enter another number.\n";
            return true;
        }
    }
    return false;
}


// Function to read new client data from user
stClientData ReadClientData()
{
    stClientData ClientData;
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);


    do
    {

        cout << "Enter Account Number ?";
        //ws Will Extract All The Whitespaces Character
        getline(cin >> ws, ClientData.AccountNumber);


    } while (IsAccountNumberExist(ClientData.AccountNumber, vClientData));


    cout << "Enter PIN Code ?";
    getline(cin, ClientData.PinCode);


    cout << "Enter Name ?";
    getline(cin, ClientData.Name);


    cout << "Enter Phone ?";
    getline(cin, ClientData.Phone);


    cout << "Enter Account Balance ?";
    cin >> ClientData.AccountBalance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    return ClientData;



}

// Function to convert client data into a text line ready to save in file
string Convert2Line(stClientData ClientData, string Delim = "#//#")
{
    string ClientRecord = "";

    ClientRecord += ClientData.AccountNumber + Delim;
    ClientRecord += ClientData.PinCode + Delim;
    ClientRecord += ClientData.Name + Delim;
    ClientRecord += ClientData.Phone + Delim;
    ClientRecord += to_string(ClientData.AccountBalance);

    return ClientRecord;
}

// Function to save a new client record in file
void SavingClientReccord(string ClientRecord)
{
    fstream ClientsRecordsFile;

    ClientsRecordsFile.open("ClientsRecords.txt", ios::out | ios::app);

    if (ClientsRecordsFile.is_open())
    {
        ClientsRecordsFile << ClientRecord << endl;

        ClientsRecordsFile.close();
    }

}

// Function to add a new client (reads data then saves it)
void AddNewClient()
{
    stClientData ClientData;

    ClientData = ReadClientData();

    SavingClientReccord(Convert2Line(ClientData, "#//#"));

}

// Function to ask user if they want to add more clients
void Asking2AddClients()
{
    char Answer;

    do
    {

        cout << "\nAdding New Client : \n" << endl;
        AddNewClient();

        cout << "\n\nClient Add Successfully , do You Want to Add More ? [Y/N]\n";
        cin >> Answer;

    } while (Answer == 'Y' || Answer == 'y');
}

// Function to display add new client screen
void AddNewClientScreen()
{
    cout << "------------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n------------------------------------\n";



    Asking2AddClients();
}

// Function to update existing client data
void UpdateClientRecord(string AccountNumber)
{

    vector <stClientData> vClient = LoadClientDataFromFile(FileName);

    bool Found = false;
    stClientData Client;

    // Search for the client
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            Found = true;
            break;
        }
    }
    if (!Found)
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
        return;

    }

    cout << "Current Client Data :\n";
    PrintClientData(Client);

    char Answer;

    cout << "\nAre you sure you want to Update this client? (y/n): ";
    cin >> Answer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    if (Answer != 'Y' && Answer != 'y')
    {
        cout << "\nUpdate Cancelled.\n";
        return;
    }


    // Read new data
    cout << "Enter Pin Code :";
    getline(cin, Client.PinCode);

    cout << "Enter Name :";
    getline(cin, Client.Name);

    cout << "Enter Phone :";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance :";
    cin >> Client.AccountBalance;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Update data in the list
    for (stClientData& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C = Client;
            break;
        }
    }

    // Save all data to file
    fstream ClientsRecords;

    ClientsRecords.open(FileName, ios::out);

    if (ClientsRecords.is_open())
    {

        for (stClientData& Client : vClient)
        {
            ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
        }
        ClientsRecords.close();


    }

    cout << "\nClient Updated Successfully !\n";
}

// Function to display update client screen
void UpdateClientInfoScreen()
{
    cout << "------------------------------------\n";
    cout << "\tUpdate Clients Screen";
    cout << "\n------------------------------------\n";

    UpdateClientRecord(Ask4AccountNumber());

}

// Function to search for a client and print their data
void CheckClient2Find(string AccountNumber, vector<stClientData> vClientData)
{
    stClientData ClientData;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            PrintClientData(Client);
            return;
        }
    }
    cout << "Client With Account Number (" << AccountNumber << ") Not Found ! " << endl;

}

// Function to display find client screen
void FindClientScreen()
{
    vector <stClientData> vClient = LoadClientDataFromFile(FileName);
    cout << "\n------------------------------------\n";
    cout << "\tFind Clients Screen";
    cout << "\n------------------------------------\n";

    CheckClient2Find(Ask4AccountNumber(), vClient);

}

// Function to ask user to press any key to return to main menu
void PressAnyKeyFunction()
{

    cout << "Press Any Key to go back to Main Menu...";
    system("pause>0");

}

// Function to ask user for the desired action in the transactions menu
short AskWhatToDo()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 4] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;

}

// Function to display the transaction menu screen
void TransactionMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\Transaction Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balance.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "================================================\n";


}

//Function to perform deposit operation
//Searches for client, requests amount, updates balance, and saves changes to file
void DepositOperation()
{
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);
    
    
    string AccountNumber = Ask4AccountNumber();

    CheckClient2Find(AccountNumber, vClientData);
    
    float Amount;
    float NewBalance = 0;
    char Answer;

   
        cout << "\nPlease Enter Deposit Amount? ";
        cin >> Amount;

        for (stClientData& Client : vClientData)
        {

            if (AccountNumber == Client.AccountNumber)
            {
                Client.AccountBalance += Amount;
                NewBalance = Client.AccountBalance;

                break;
            }
        }


        cout << "\n\nAre you sure you want perform this transaction [Y/N] ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            // Save all data to file
            fstream ClientsRecords;

            ClientsRecords.open(FileName, ios::out);

            if (ClientsRecords.is_open())
            {

                for (stClientData& Client : vClientData)
                {
                    ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
                }
                ClientsRecords.close();

            }
            cout << "Deposit Done Successfully , New Balance is : " << NewBalance << endl << endl;

        }
        else
        {
            cout << "Deposit Cancelled ! " << endl;
        }
        vClientData = LoadClientDataFromFile(FileName);


        

}

// Displays screen title and calls the deposit operation function
void DepositScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n------------------------------------\n";

    DepositOperation();


}

// Function to perform withdraw operation
// Searches for client, verifies sufficient balance, executes withdrawal, and saves changes
void WithdrawOperation()
{
    vector <stClientData> vClientData = LoadClientDataFromFile(FileName);

    string AccountNumber = Ask4AccountNumber();

    CheckClient2Find(AccountNumber, vClientData);

    float Amount;
    float NewBalance = 0;
    char Answer;

    cout << "\nPlease Enter Withdraw Amount? ";
    cin >> Amount;

    for (stClientData& Client : vClientData)
    {

        if (AccountNumber == Client.AccountNumber)
        {
            if (Amount > Client.AccountBalance)
            {
                cout << "Amount Exceeds the balance, You can withdraw up to : " << Client.AccountBalance << endl;
                cout << "\nPlease Enter Another Amount? ";
                cin >> Amount;
            }
            else
            {
            Client.AccountBalance -= Amount;
            NewBalance = Client.AccountBalance;
            }

            break;
        }
    }


    cout << "\n\nAre you sure you want perform this transaction [Y/N] ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        // Save all data to file
        fstream ClientsRecords;

        ClientsRecords.open(FileName, ios::out);

        if (ClientsRecords.is_open())
        {

            for (stClientData& Client : vClientData)
            {
                ClientsRecords << Client.AccountNumber << "#//#" << Client.PinCode << "#//#" << Client.Name << "#//#" << Client.Phone << "#//#" << Client.AccountBalance << endl;
            }
            ClientsRecords.close();

        }
        cout << "Withdraw Done Successfully , New Balance is : " << NewBalance << endl << endl;

    }
    else
    {
        cout << "Withdraw Cancelled ! " << endl;
    }
    vClientData = LoadClientDataFromFile(FileName);



}

// Function to display the withdraw screen
void WithdrawScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n------------------------------------\n";

    WithdrawOperation();

}

// Function to print a single client record in the total balances list
void PrintClientRecordForTotalBalances(stClientData ClientData)
{
    cout << "| " << setw(15) << left << ClientData.AccountNumber;
    cout << "| " << setw(40) << left << ClientData.Name;
    cout << "| " << setw(12) << left << ClientData.AccountBalance;


}

// Function to print all client data and calculate total balances
void PrintAllClientsDataForTotalBalances(vector <stClientData> vClients)
{
    float TotalBalances = 0;

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData ClientData : vClients)
    {
        PrintClientRecordForTotalBalances(ClientData);
        TotalBalances += ClientData.AccountBalance;
        cout << endl;
    }

    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

   
    cout << "\t\t\t\nTotalBalances = " << TotalBalances << endl;

}

// Function to display the total balances screen
void ToalBalancesScreen()
{
    // Loads client data and displays the balances table with total
    vector <stClientData> vClients = LoadClientDataFromFile(FileName);

    PrintAllClientsDataForTotalBalances(vClients);

}

// Function to display the main menu of the program
void MainMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Exit.\n";
    cout << "================================================\n";



}



// Function to ask user to choose an option from the menu
short Ask4Option()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 7] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;
}

// Function to convert option number to enum value
enMenuOptions ChoosingOption(short Number)
{

    switch (Number)
    {
    case 1:      return eShowList;

    case 2:      return eAddNew;

    case 3:      return eDelete;

    case 4:      return eUpdateInfo;

    case 5:      return eFind;

    case 6:      return eTransaction;

    case 7:      return eExit;

    }

}


// Function to convert option number to enum value in transactions menu
enTransactionsMenu ChoosingOperation(short Number)
{
    switch (Number)
    {
    case 1:      return eDeposit;

    case 2:      return eWithdraw;

    case 3:      return eTotalBalances;

    case 4:      return eMainMenu;
    }
}



//Displays menu and performs selected option until user chooses to return to main
void PerformTransactionMenuOption()
{
    
    enTransactionsMenu Operation;
    do
    {

    TransactionMenuScreen();

    vector <stClientData> vClient;
    vClient = LoadClientDataFromFile(FileName);

    Operation = (enTransactionsMenu)AskWhatToDo();


     switch (Operation)
     {
     case eDeposit:
        system("cls");
        DepositScreen();
        PressAnyKeyFunction();
        break;

     case eWithdraw:
        system("cls");
        WithdrawScreen();
        PressAnyKeyFunction();
        break;





     case eTotalBalances:
        system("cls");
        ToalBalancesScreen();
        PressAnyKeyFunction();
        break;



     case eMainMenu:
         return;



     default:
         system("cls");
         cout << "\nError: Invalid Option! Please enter a number between 1 and 4.\n";
         PressAnyKeyFunction();
         break;
     }





    } while (Operation != eMainMenu);

}



// Function to display exit screen
void ExitScreen()
{
    cout << "\n------------------------------------\n";
    cout << "\tProgram Ends : )\n";
    cout << "\n------------------------------------\n";

    system("pause>0");

}


// Function to execute the option chosen by user from the main menu
void PerformMenuOption()
{
    enMenuOptions Option;

    MainMenuScreen();
    vector <stClientData> vClient;
    vClient = LoadClientDataFromFile(FileName);

    do
    {
        MainMenuScreen();
        Option = ChoosingOption(Ask4Option());


        switch (Option)
        {
        case eShowList:
            system("cls");
            PrintAllClientsData(LoadClientDataFromFile(FileName));
            PressAnyKeyFunction();
            break;


        case eAddNew:
            system("cls");
            AddNewClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eDelete:
            system("cls");
            DeleteClientScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;


        case eUpdateInfo:
            system("cls");
            UpdateClientInfoScreen();
            vClient = LoadClientDataFromFile(FileName);
            PressAnyKeyFunction();
            break;

        case eFind:
            system("cls");
            FindClientScreen();
            PressAnyKeyFunction();
            break;


        case eTransaction:
            system("cls");
            PerformTransactionMenuOption();
            break;


        case eExit:
            system("cls");
            ExitScreen();
            break;

        default:
            system("cls");
            cout << "\nError: Invalid Option! Please enter a number between 1 and 6.\n";
            PressAnyKeyFunction();
            break;



        }

    } while (Option != eExit);



}



// Main function - starting point of the program
int main()
{
    // Load data (file will be created after adding first client)
    vector <stClientData> vClient = LoadClientDataFromFile(FileName);


    //You should Start by "[2] Add New Client" to Create The txt File !
    PerformMenuOption();



    return 0;
}
// Duration : 2 H 







