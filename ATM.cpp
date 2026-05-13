#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include<limits>

using namespace std;

const string ClientsFileName = "Clients.txt";

enum enATMMainMenuOption{
    eQuickWithdraw=1,
    eNormalWithDraw=2,
    eDeposit=3,
    eCheckBalance=4,
    eLogOut=5,
    eExit=6
};

struct stClient{

    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;

};

stClient GlobalClient;

void ShowATMMainMenu();
void ShowNormalWithDraw();
void GoBackToQuickWithdraw();

vector<string> SplitString(string S1, string Delim){

    vector<string> vString;
    short pos = 0;
    string sWord;   
    while ((pos = S1.find(Delim)) != std::string::npos){

        sWord = S1.substr(0, pos);   
        
        if (sWord != ""){

            vString.push_back(sWord);
        
        }
        S1.erase(0, pos + Delim.length());  

    }
        
    if (S1 != ""){

        vString.push_back(S1); 
        
    }

    return vString;

}

stClient ConvertLineToReacord(string Line,string Separetor="#//#"){
    
    vector <string>vClients=SplitString(Line,Separetor);
    stClient Client;
    Client.AccountNumber=vClients[0];
    Client.PinCode=vClients[1];
    Client.Name=vClients[2];
    Client.Phone=vClients[3];
    Client.AccountBalance=stoi(vClients[4]);

    return Client;

}

string ConvertRecordToLine(stClient Client,string Separator="#//#"){

    string RecordLine="";
    RecordLine+=Client.AccountNumber+Separator;
    RecordLine+=Client.PinCode+Separator;
    RecordLine+=Client.Name+Separator;
    RecordLine+=Client.Phone+Separator;
    RecordLine+=to_string(Client.AccountBalance);

    return RecordLine;

}

vector<stClient>LoadClientDataFromFile(string FileName){

    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open(FileName,ios::in);

    if(MyFile.is_open()){

        string line;
        stClient Client;

        while(getline(MyFile,line)){
            
            Client=ConvertLineToReacord(line);
            vClient.push_back(Client);

        }

        MyFile.close();

    }
    return vClient;
}

bool FindClientByAccountNumberAndPassword(string AccountNumber,string PinCode,stClient &Client){

    vector<stClient>vClient=LoadClientDataFromFile(ClientsFileName);

    for(const stClient& C : vClient){

        if(C.AccountNumber==AccountNumber&&C.PinCode==PinCode){
            Client=C;
            return true;
        }

    }

    return false;

}

vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient> vClients){

    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open()){

        for (stClient& C : vClients){

            if (C.MarkForDelete == false){

                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }
    
        }
    
        MyFile.close();
    
    }
    
    return vClients;

}

bool DepositBalanceByAccountNumber(string AccountNumber,vector<stClient>& vClient,double Amount){
    
    char Answer='n';
    cout<<"Are you sure you want perfrom this transaction ? y/n ? ";
    cin>>Answer;

    if(toupper(Answer)=='Y'){

        for(stClient &C : vClient){

            if(C.AccountNumber==AccountNumber){

                C.AccountBalance+=Amount;
                SaveClientsDataToFile(ClientsFileName,vClient);
                cout<<"\n\nDone Successfully .New Balance is "<<C.AccountBalance;
                return true;

            }

        }
        return false;

    }
    
}

short ReadQuickWithDrawoption(){

    short Choise=0;

    while(Choise<1 || Choise >9){

        cout<<"\nChoise what to do from [1] to [8] ? ";
        cin>>Choise;

    }
    return Choise;

}

short GetQuickWithDrawOption(short QuickWithdrawOption){

    int arr[]={20,50,100,200,400,600,800,1000};
    return arr[QuickWithdrawOption-1];

}

void PerfromQuickWithDrawOption(short QuickWithdrawOption){

    short Amount=GetQuickWithDrawOption(QuickWithdrawOption);
    if(QuickWithdrawOption==9){
        system("cls");
        ShowATMMainMenu();

    }
    else{

        vector<stClient>vClient=LoadClientDataFromFile(ClientsFileName);
        DepositBalanceByAccountNumber(GlobalClient.AccountNumber,vClient,Amount*-1);
        GlobalClient.AccountBalance-=Amount;
        GoBackToQuickWithdraw();

    }
}

double ReadDopsitAmount(){

    double Balance=0;
    cout<<"\nEnter a positive Deposit Amount ? ";
    cin>>Balance;

    while(cin.fail()||Balance<=0){
        
        cin.clear();
        cin.ignore(std::numeric_limits <std::streamsize> ::max(),'\n'); 
        cout << "Invalid Number , Enter a valid one : " << endl;
        cin>>Balance;

    }

    return Balance;

}

void PerformDepositOption(){
    
    double Balance=ReadDopsitAmount();
    vector<stClient> vClient=LoadClientDataFromFile(ClientsFileName);
    DepositBalanceByAccountNumber(GlobalClient.AccountNumber,vClient,Balance);
    GlobalClient.AccountBalance+=Balance;

}

void ShowDepositScreen(){

    cout << "===========================================\n";
    cout << "\t\tDeposit Screen\n";
    cout << "===========================================\n";

    PerformDepositOption();

}

int ReadWithDrawAmount(){

    int Amount;
    cout<<"\nEnter an amount multiple of 5's ? ";
    cin>>Amount;

        while(cin.fail()||Amount%5!=0){
        
        cin.clear();
        cin.ignore(std::numeric_limits <std::streamsize> ::max(),'\n'); 
        cout<<"\nEnter an amount multiple of 5's ? ";
        cin>>Amount;

    }

    return Amount;

}

void PerfromWithdrawoption(){
    
    int Amount=ReadWithDrawAmount();

    if(Amount>GlobalClient.AccountBalance){

        cout <<"\nThe amount exceeds your balacne , make another choise .\n";
        system("pause>0");
        ShowNormalWithDraw();
        return ;

    }

    vector<stClient> vClient=LoadClientDataFromFile(ClientsFileName);
    DepositBalanceByAccountNumber(GlobalClient.AccountNumber,vClient,Amount *-1);
    GlobalClient.AccountBalance-=Amount;

}

void ShowNormalWithDraw(){
    
    cout << "===========================================\n";
    cout << "\t\tWithDraw Screen\n";
    cout << "===========================================\n";

    PerfromWithdrawoption();

}

bool loadClientInfo(string AccountNumber,string PinCode){

    if(FindClientByAccountNumberAndPassword(AccountNumber,PinCode,GlobalClient)){

        return true;

    }
    else{

        return false;

    }

}

void LogInScreen(){

    string AccountNumber,PinCode;
    bool FieldLogin=false;

    do{

        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\t\tLogIn ";
        cout << "\n-----------------------------------\n";

        if(FieldLogin){

            cout<<"Invalid AccountNumber/PinCode !\n";

        }

        cout<<"PLease Enter a Account Numebr :  ";
        cin>>AccountNumber;
        cout<<"Please Enter a PinCode :  ";
        cin>>PinCode;
        FieldLogin=!loadClientInfo(AccountNumber,PinCode);

    }while(FieldLogin);

    ShowATMMainMenu();

}

void ShowQuickWithdrawScreen(){
    
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\t\t\n";
    cout << "===========================================\n";

    PerfromQuickWithDrawOption(ReadQuickWithDrawoption());

}

void GoBackToQuickWithdraw(){

    cout << "\n\nPress any key to Continue...\n";
    system("pause>0");

    ShowQuickWithdrawScreen();

}

void GoBackToATMMainMenu(){

    cout << "\n\nPress any key to go back to ATM Main Menue...";
    system("pause>0");

    ShowATMMainMenu();

}

short ReadATMMainMenuOption(){

    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    while(cin.fail()){

        cin.clear();
        cin.ignore(std::numeric_limits <std::streamsize> ::max(),'\n'); 
        cout << "Invalid Number , Enter a valid one : " << endl;
        cin>>Choice;

    }

    return Choice;

}

void ShowExitScreen(){

    cout << "===========================================\n";
    cout << "\t\tExit Screen\n";
    cout << "===========================================\n";

}

void CheckBalanceScreen(){

    cout << "===========================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "===========================================\n";
    cout<<"Yoiur Balance is  "<<GlobalClient.AccountBalance<<endl;

}

void PerfromMainMenuOption(enATMMainMenuOption ATMMainMenueOption){

    switch (ATMMainMenueOption){

        case enATMMainMenuOption::eQuickWithdraw:{
    
            system("cls");
            ShowQuickWithdrawScreen();
            break;
        
        }

        case enATMMainMenuOption::eNormalWithDraw:{
        
            system("cls");
            ShowNormalWithDraw();
            GoBackToATMMainMenu();
            break;

        }

        case enATMMainMenuOption::eDeposit:{

            system("cls");
            ShowDepositScreen();
            GoBackToATMMainMenu();
            break;

        }

        case enATMMainMenuOption::eCheckBalance:{

            system("cls");
            CheckBalanceScreen();
            GoBackToATMMainMenu();
            break;

        }

        case enATMMainMenuOption::eLogOut:{

            system("cls");
            LogInScreen();
            break;

        }

        case enATMMainMenuOption::eExit:{

            system("cls");
            ShowExitScreen();
            break;

        }

    }

}

void ShowATMMainMenu(){

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Log Out.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";

    PerfromMainMenuOption((enATMMainMenuOption)ReadATMMainMenuOption());

}

int main(){
    
    LogInScreen();
    
    return 0;
}