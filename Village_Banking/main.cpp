#include<iostream>
#include<string>
#include<vector>
using namespace std;


//Create a profile class
class Banker
{
private:
    string name, password;
    int age;
    float balance = 0;
    float coffer;
    float loan = 0;
public:
    //constructor
    Banker(string n, string p, int a)
    {
        name = n;
        password = p;
        age = a;
    }
    //Setters
    void setName(string name1) {name = name1;}
    void setPassword(string password1) {password = password1;}
    void setAge(int age1) {age = age1;}
    void setBalance(float balance1) {balance += balance1;}
    void setLoan(float loan1) {loan += loan1;}
    void setCoffer(float coffer1) {coffer = coffer1;}
    //Getters
    string getName() {return name;}
    string getPassword() {return password;}
    int getAge() {return age;}
    float getBalance() {return balance;}
    float getLoan() {return loan;}
    float getCoffer() {return coffer;}
};
class BankManager
{
private:
    //Total number of bankers
    int TOTAL_BANKERS = 10;
    //Create a vector with the properties of the banker class
    vector<Banker> bankStorage;
    //count members registered
    int countBankers = 0;
public:

    //Create a function to add members to the system
    void addBankers(string &name, string &password, int &age)
    {
        //check if the total banker has reached or not
        if(countBankers<TOTAL_BANKERS)
        {
            bankStorage.push_back(Banker(name, password, age));
            countBankers++;
        }
        else
        {
                cout<<"The bank is full"<<endl;
        }
    }
    //For debugging purposes display the names
    void display()
    {
        const int totalNum = bankStorage.size();
        for(int i=0; i<totalNum; i++)
        {
            cout<<bankStorage.at(i).getName();
            cout<<endl;
        }
    }
    //Check if user is in the system
    const bool checkUser(const string &name1, const string &password1)
    {
        bool found = false;
        //Iterate through the namestorage to check if the name is in the system
        const int totalNum = bankStorage.size();
        for(int i=0; i<totalNum; i++)
        {
            if(bankStorage.at(i).getName() == name1 && bankStorage.at(i).getPassword() == password1)
            {
                found = true;
            }
        }
        return found;
    }
    //all functionality that inherites from this class
    void changePassword();
    void deposit(string &password1);
    void checkBalance(string &password1);
    void grantLoan(string &password1);
    void repayLoan(string &password1);
    void userMenu(string &name1);
    //Calculate all the money deposited
    float coffer(float aDefult);
    //hold the total money
    float totalCoffer;
    //hold all the credits
    float totalPay = 0;

};
//Adding all the money in the coffer
float BankManager::coffer(float loanPayBack)
{
    //add the update the loan
    totalPay -= loanPayBack;
    const int totalNum = bankStorage.size();
    for(int i=0; i<totalNum; i++)
    {
        totalCoffer += bankStorage.at(i).getCoffer();
    }
    //deduct any loan given
    totalCoffer -= totalPay;
    return totalCoffer;
}
//Modifying the forgot password function
void BankManager::changePassword()
{
    string name, newPassword;
    int age;
    cout<<"Enter username :";
    cin>>name;
    cout<<"To change password enter you age :";
    cin>>age;
    cout<<"Enter your new password :";
    cin>>newPassword;
    const int totalNum = bankStorage.size();
    for(int i=0; i<totalNum; i++)
    {
        if((bankStorage.at(i).getName()) == name && (bankStorage.at(i).getAge() == age))
        {
            bankStorage.at(i).setPassword(newPassword);
            cout<<"Password changed successfully"<<endl;
            break;
        }
        else
        {
            cout<<"Sorry there is no such a name registered"<<endl;
            cout<<"Please double check your name or age"<<endl;
        }
    }
}
//Depositing in an account
void BankManager::deposit(string &password1)
{
    cout<<"Amount :";
    int amount;
    cin>>amount;
    cout<<"Enter your password to confirm :";
    string password2;
    cin>>password2;
    //for assurance purposes check if password is correct
    if(password2 == password1)
    {
        const int totalNum = bankStorage.size();
        for(int i=0; i<totalNum; i++)
        {
            //check where this password belongs to
            if(bankStorage.at(i).getPassword() == password1)
            {
                //when someone deposit we want to deduct loan if the have one
                if(bankStorage.at(i).getLoan() > 0)
                {
                    //then you have a loan and resettle the paid loan;
                    bankStorage.at(i).setLoan(+amount);
                    cout<<"Loan deducted"<<endl;
                    cout<<"k"<<bankStorage.at(i).getLoan();
                    cout<<" loan debt remaining"<<endl;
                }
                cout<<"Where do you want to deposit"<<endl;
                cout<<"1. Main account"<<endl;
                cout<<"2. Group account(coffer)"<<endl;
                int choice;
                cin>>choice;
                if(choice == 1)
                {
                    //you don't have any loan debt
                    bankStorage.at(i).setBalance(amount);
                }
                else if(choice == 2)
                {
                    //add to the coffer
                    bankStorage.at(i).setCoffer(amount);
                }
                else
                {
                    //invalid choice
                    cout<<"Invalid input"<<endl;
                }

            }

        }
    }
    else
    cout<<"Password incorrect!"<<endl;
}
//check for balance function
void BankManager::checkBalance(string &password1)
{
    //Do you want to check for loan debt or account
    cout<<"1.Check account balance"<<endl;
    cout<<"2.Check group balance(coffer)"<<endl;
    cout<<"3.Check for loan debt"<<endl;
    int check;
    cin>>check;

    string password2;
    //store balance and loan debt here to be displayed
    float balance;
    float loanBalance;
    cout<<"Enter password :";
    cin>>password2;
    if(password2 == password1)
    {
        const int totalNum = bankStorage.size();
        for(int i=0; i<totalNum; i++)
        {
            //check where this password belongs to
            if(bankStorage.at(i).getPassword() == password1)
            {
                balance = bankStorage.at(i).getBalance();
                loanBalance = bankStorage.at(i).getLoan();
            }
            //loan debt or account balance
            if(check == 1)
                cout<<"Balance :K"<<balance<<endl;
            else if(check == 2)
                cout<<"Total balance in the coffer :K"<<coffer(0)<<endl;
            else if(check == 3)
                cout<<"Loan debt :k"<<loanBalance<<endl;
            else
                cout<<"Invalid input"<<endl;

        }
    }
    else
    cout<<"Password incorrect!"<<endl;
}
//Give a loan function
void BankManager::grantLoan(string &password1)
{
/*We want to check if this person already as a loan or debt
so that we don't end up giving him another loan*/
    bool hasLoan = true;
    const int totalNum = bankStorage.size();
    for(int i=0; i<totalNum; i++)
    {
        //locate the user
        if(bankStorage.at(i).getPassword() == password1)
        {
            //check if they don't have a loan
            if(bankStorage.at(i).getLoan() <= 0)
            {
                hasLoan = false;
            }
        }
    }
    //if doesn't have a loan then grant a loan
    if(!hasLoan)
    {
        int accountPos;
        float balance;
        string password2;
        cout<<"Enter password :";
        cin>>password2;
        if(password2 == password1)
        {
            const int totalNum = bankStorage.size();
            for(int i=0; i<totalNum; i++)
            {
                //check where this password belongs to
                if(bankStorage.at(i).getPassword() == password1)
                {
                    //If someone hasn't deposited in the coffer yet they can't get a loan
                    balance = bankStorage.at(i).getCoffer();
                    //keep the index of account
                    accountPos = i;
                }

            }
                //double the money he/she has deposited in the coffer;
                float eligibleLoan = (balance * 2);
                cout<<"You are eligible to get a loan of K"<<eligibleLoan;
                cout<<" or below"<<endl;
                cout<<"Enter amount :";
                int amountRequest;
                cin>>amountRequest;
                if(amountRequest <= eligibleLoan)
                {
                    cout<<"Enter number of days to repay :";
                    //this number should be made global to keep track of days
                    int numberOfDays;
                    cin>>numberOfDays;
                    float interest = 0.5;
                    //Simple interest fomular plus amount request
                    float loanPayBack = ((amountRequest) + ((amountRequest * interest * numberOfDays)/100));
                    cout<<"If you get K"<<amountRequest;
                    cout<<" You will need to repay K"<<loanPayBack<<endl;
                    cout<<"Enter password to confirm :";
                    cin>>password2;
                    if(password2 == password1)
                    {
                        //store the loan
                        bankStorage.at(accountPos).setLoan(-loanPayBack);
                        //add the requested money in the main account
                        bankStorage.at(accountPos).setBalance(amountRequest);
                        //deduct from the coffer
                        coffer(-loanPayBack);
                        cout<<"Your new balance is "<<bankStorage.at(accountPos).getBalance()<<endl;
                    }
                    else
                        cout<<"Incorrect password!"<<endl;
                }
                else
                    cout<<"You are not yet eligible get K"<<amountRequest<<" loan"<<endl;
        }
        else
            cout<<"Password incorrect!"<<endl;
    }
    //user has a pending loan debt
    else
        cout<<"Sorry you need to repay your loan debt first"<<endl;
}
//repaying the loan debt
void BankManager::repayLoan(string &password1)
{
    cout<<"Enter password to deduct from account";
    string password2;
    cin>>password2;
    if(password2 == password1)
    {
        const int totalNum = bankStorage.size();
        for(int i=0; i<totalNum; i++)
        {
            if(bankStorage.at(i).getPassword() == password1)
            {

            }
        }
    }
}
/*Display and handle all the function calls */
void BankManager::userMenu(string &password1)
{
    //We are taking the same password(password1) entered to reach this stage
    //And using it for confirmation
    int choice;
    do
    {
    cout<<"\n1. Deposit"<<endl;
    cout<<"2. Check Balance, Group balance(coffer) Or loan debt"<<endl;
    cout<<"3. Change Password"<<endl;
    cout<<"4. Request for a loan"<<endl;
    cout<<"5. Repay loan"<<endl;
    cout<<"6. Quit the village banking(conditions apply)"<<endl;
    cout<<"7. Main menu"<<endl;
    //Add functionality
    cout<<"Choice :";
    cin>>choice;

    if(choice == 1)
    {
        //call the deposit function
        deposit(password1);
    }
    else if(choice == 2)
    {
       //call upon the check balance fuction
       checkBalance(password1);
    }
    //change password
    else if(choice == 3)
    {
        //call function to change password
        changePassword();
    }
    //request for a loan
    else if(choice == 4)
    {
        //call function to grant loan
        grantLoan(password1);
    }
}while(choice != 7);

}
//create a welcome page or UI
void menu()
{
    cout<<"\tWELCOME TO OUR VILLAGE BAKING\n"<<endl;
    cout<<"1.Register (first time) "<<endl;
    cout<<"2.To see our 'terms and conditions' "<<endl;
    cout<<"3.Login (Already have any account) "<<endl;
    cout<<"4.To quit program"<<endl;
}

//Terms and conditions
void termsAndConditions()
{
    cout<<"There is a non-refundable payment of k10 to start"<<endl;
    cout<<"your village bank and please state your source of income,"<<endl;
    cout<<"or how you intend to repay after taking your share"<<endl;
    cout<<"You have to agree to deposit K5 everyday and"<<endl;
    cout<<"every week one among you is paid so the more"<<endl;
    cout<<"people you are, more money in the pocket"<<endl;
}

int main()
{
    BankManager manager;

    int choice;
    const int quit = 4;
    do
    {
        menu();
        cin>>choice;
        if(choice == 1)
        {
            //If you agree with the terms then you will register
            string agreeOrDeny;
            termsAndConditions();
            cout<<"Enter 'agree' to Accept our terms or 'any' key to Deny"<<endl;
            cin>>agreeOrDeny;
            if((agreeOrDeny == "agree" || agreeOrDeny == "AGREE") || (agreeOrDeny == "Agree"))
            {
                //Declaration of person
                string name, password;
                int age;
                cout<<"User name :";
                cin>>name;
                cout<<"Age :";
                cin>>age;
                cout<<"Password :";
                cin>>password;
                //initializing the names
                manager.addBankers(name, password, age);
                manager.userMenu(password);

            }
        }
        else if(choice == 2)
        {
            termsAndConditions();
        }
        else if(choice == 3)
        {
            string name, password;
            cout<<"Username :";
            cin>>name;
            cout<<"Password :";
            cin>>password;
            const bool isRegistered = manager.checkUser(name, password);
            if (isRegistered)
            {
                manager.userMenu(password);
            }
            else
            {
                cout<<"Sorry you are not registered in the system"<<endl;
                cout<<"Please double check your name or age"<<endl;
                cout<<"1. Main menu"<<endl;
                cout<<"2. Forgot password"<<endl;
                cout<<"Choice :";
                int choose;
                cin>>choose;
                if(choose == 2)
                {
                    manager.changePassword();

                }
            }
        }
    }while(choice != quit);

    return 0;
}





