//By Sarthak Mishra

//------------HEADER FILES--------------------

#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
#include<string>


using namespace std;

//------------exising files to store the data---------------------------- 
//buses.txt
//users.txt
//bus_num.txt //these files keep record of its passengers stored in passengers folder


//-------------CREATING THE USER OBJECT----------------------------------
class user {
    public:
    string name;
    string pass;

};

//-------------CREATING THE BUS OBJECT---------------------------------------
class bus {
    public:
    string num;
    string dest;
    int cap;
    int avail;

    //functions-------
    static void main_menu(user you);
    static void see_details(user you );
    static void check_avail(user you);
    static void book_ticket(user you);

};

//-------------bus :: Main_menu func--------------------------------------------

void bus :: main_menu(user you){

    int t;
    system("cls");
    
    cout<<"\n\n";
    cout<<"\t\tChoose from the following actions: \n";
    cout<<"\t\t1. See the details of a bus \n";
    cout<<"\t\t2. Check the availability of seats in a bus \n";
    cout<<"\t\t3. Book a ticket \n";
    cout<<"\t\t4. Exit\n";

    cout<<"\n\n\t\tEnter your choice: ";
    cin>>t;
    
    switch(t){
        case 1:
            bus :: see_details(you);
            break;
        case 2:
            bus :: check_avail(you);
            break;
        case 3:
            bus :: book_ticket(you);
            break;
        case 4:
            system("cls");                          
            cout<<"\n\n\n\t----------THANK YOU FOR USING OUR SERVICE----------\n";
            Sleep(1500);
            exit(0);
            break;
        default:
            system("cls");
            cout<<"\n\n\t\t------Invalid choice.-----------\n";
            Sleep(1500);
            bus::main_menu(you);
    }

}

//------------------------bus details func----------------------------------------------------

void bus:: see_details(user you){
    system("cls");
    string ip_bus_num;
    cout<<"\n\n\n\t\tEnter the bus number: ";
    cin>>ip_bus_num;
    ifstream bus_file;
    bus_file.open("buses.txt");
    string temp_bus_num, temp_bus_dest, temp_bus_cap, temp_bus_avail;
    bool found=false;
    while(!bus_file.eof()){
        bus_file>>temp_bus_num>>temp_bus_dest>>temp_bus_cap>>temp_bus_avail;
        if(temp_bus_num==ip_bus_num){
            system("cls");
            cout<<"\n\n\n\t\t----------BUS DETAILS----------\n";
            cout<<"\n\n\t\tBus number: "<<temp_bus_num;
            cout<<"\n\t\tDestination: "<<temp_bus_dest;
            cout<<"\n\t\tCapacity: "<<temp_bus_cap;
            Sleep(3000);
            found=true;
            break;
        }
    }

    if(!found){
        cout<<"\n\n\t\tBus with the given bus number not found.....\n";
    }
    bus_file.close();
    cout<<"\n\n\t\treturning to main menu....\n";
    Sleep(1500);
    bus::main_menu(you);

}

//------------------CHECK AVAIL FUNC------------------------------------------------------------

void bus:: check_avail(user you){
    system("cls");
    string ip_bus_num;

    cout<<"\n\n\n\t\tEnter the bus number: ";
    cin>>ip_bus_num;
    ifstream bus_file;
    bus_file.open("buses.txt");
    string temp_bus_num, temp_bus_dest, temp_bus_cap, temp_bus_avail;
    bool found=false;
    while(!bus_file.eof()){
        bus_file>>temp_bus_num>>temp_bus_dest>>temp_bus_cap>>temp_bus_avail;
        if(temp_bus_num==ip_bus_num){
            cout<<"\n\t\tAvailability: "<<temp_bus_avail<<" seats";
            Sleep(2000);
            found=true;
            break;
        }
    }
    
    if(!found){
        cout<<"\n\n\t\tBus with the given bus number not found.....\n";
    }

    bus_file.close();
    cout<<"\n\n\t\treturning to main menu....\n";
    Sleep(1500);
    bus::main_menu(you);

}

//----------------------BOOK TICKET FUNC-----------------------------------------------------------

void bus:: book_ticket(user you){
    system("cls");
    string ip_bus_num;

    cout<<"\n\n\n\t\tEnter the bus number: ";
    cin>>ip_bus_num;
    ifstream bus_file;
    bus_file.open("buses.txt");

    ofstream temp_bus_file;                                                          //this file is used to update the existing buses file.......we copy the new data into this file and delete the old file, then rename this file.
    temp_bus_file.open("temp_buses.txt", ios::out | ios:: app);
    
    string temp_bus_num, temp_bus_dest, temp_bus_cap, temp_bus_avail;
    bool found=false;
    int flag=-1;
    while(!bus_file.eof()){
        flag++;

        if(flag>0){
            temp_bus_file<<"\n";                                                    //this is used to add a new line in the temp file, but we donot add a new line if it is going to the first line
        }
        bus_file>>temp_bus_num>>temp_bus_dest>>temp_bus_cap>>temp_bus_avail;

        if(temp_bus_num==ip_bus_num){
            
            found=true;
            
            int available= stoi(temp_bus_avail);
            
            if(available==0){

                temp_bus_file<<temp_bus_num<<" "<<temp_bus_dest<<" "<<temp_bus_cap<<" "<<available;
                cout<<"\n\n\t\tSorry, there are no available seats in this bus.\n";
                Sleep(3000);

            }else{

                cout<<"\n\n\t\tEnter your phone number: ";
                string phone;
                cin>>phone;

                ofstream this_bus;                                                      //adds the user to the passenger list of that bus............. 
                this_bus.open("passengers/"+ip_bus_num+".txt", ios::out | ios::app);
                this_bus<<you.name<<" "<<phone<<endl;
                this_bus.close();

                cout<<"\n\n\t\tYour ticket has been booked successfully.\n";
                cout<<"\n\t\t----------BUS DETAILS----------\n";
                cout<<"\n\n\t\tBus number: "<<temp_bus_num;
                cout<<"\n\t\tDestination: "<<temp_bus_dest;
                cout<<"\n\t\tPassenger: "<<you.name;
                cout<<"\n\t\tPhone number: "<<phone;
                available--;
                temp_bus_file<<temp_bus_num<<" "<<temp_bus_dest<<" "<<temp_bus_cap<<" "<<available;
                cout<<"\n\t\tSeats available: "<<available;
                cout<<"\n\n\n\t\t----------THANK YOU FOR USING OUR SERVICE----------\n";
                Sleep(5000);

            }

        }else{
            temp_bus_file<<temp_bus_num<<" "<<temp_bus_dest<<" "<<temp_bus_cap<<" "<<temp_bus_avail;
        }
    }

    bus_file.close();
    temp_bus_file.close();
    remove("buses.txt");
    rename("temp_buses.txt", "buses.txt");
    
    if(!found){
        cout<<"\n\n\t\tBus with the given bus number not found.....\n";
    }

    cout<<"\n\n\t\treturning to main menu....\n";
    Sleep(1500);
    bus::main_menu(you);

}

int main();


//----------------LOG-IN FUNCTION-----------------------------------------------------------------------

void log_in(){
    system("cls");

    //------------login credentials required-------------
    user you;                                             //creating a user object to store input data
    cout<<"\n\n\t\tLogin to continue\n\n";

    cout<<"\t\tUsername: ";
    cin>>you.name;
    cout<<"\t\tPassword: ";
    cin>>you.pass;
    
    cout<<"\n\n\n";

    ifstream user_file;
    bool found=false;

    //--------checks if the login credentials are correct----------
    user_file.open("users.txt");
    string user_detail;

    while(!user_file.eof()){
        getline(user_file,user_detail);
        //user_file>>temp_user>>temp_pass;
        if(user_detail== you.name+" "+you.pass){
            found=true;
            break;
        }
    }
    user_file.close();
    if(found){
        cout<<"\t\tlogging in.........\n\n";
        Sleep(2000);                              
        bus::main_menu(you);
    }else{
        system("cls");
        cout<<"\n\n\n\t\t--------INCORRECT CREDENTIALS--------\n\n";
        cout<<"\t\tPress '1' to exit\n";
        cout<<"\t\tPress any other key to go back\n";
        cout<<"\t\tYour choice: ";

        string choice;
        cin>>choice;

        if(choice=="1"){
            system("cls");                          
            cout<<"\n\n\n\t----------THANK YOU FOR USING OUR SERVICE----------\n";
            Sleep(1000);                          
        }else{
            cout<<"\n\n\t\tredirecting to the home page.....";
            Sleep(1500);                           
            system("cls");                          
            main();
        }
    }
}


//---------------REGISTER NEW FUNCTION------------------------------------------------------------------

void register_new(){

    system("cls");
    //------------sign up credentials required-------------
    user you;                                              //creating a user object to store input data
    cout<<"\n\n\n\t\tSign up to continue.....\n\n";

    cout<<"\t\tUsername: ";
    cin>>you.name;
    cout<<"\t\tPassword: ";
    cin>>you.pass;
    
    cout<<"\n\n\n";

    ifstream user_file;

    //--------checks if a user already exists with tha same user_name-----------------

    user_file.open("users.txt");
    user check_user;                                        //creating a user object to check if input data matches with existing data
    while(!user_file.eof()){
        user_file>>check_user.name>>check_user.pass;
        //getline(user_file,user_detail);
        //user_file>>temp_user>>temp_pass;
        if(check_user.name == you.name){
            system("cls");
            cout<<"\n\n\n\t\t--------USERNAME ALREADY EXISTS--------\n\n";
            cout<<"\t\tPress '1' to exit\n";
            cout<<"\t\tPress any other key to go back\n";
            cout<<"\t\tYour choice: ";
            string choice;
            cin>>choice;
            if(choice=="1"){
                system("cls");                          
                cout<<"\n\n\n\t----------THANK YOU FOR USING OUR SERVICE----------\n";
                Sleep(1000);                            
            }else{
                cout<<"\n\n\t\tredirecting to the home page.....";
                Sleep(1500);                            
                system("cls");                          
                main();
            }
        }
    }

    user_file.close();

    //--------if the user doesn't exist, the user is added to the file----------
    //----------registers a new user----------------------
    ofstream include_user;
    include_user.open("users.txt", ios:: app);
    include_user<<you.name<<" "<<you.pass<<endl;
    include_user.close();
    
    system("cls");
    cout<<"\n\n\t\t-----------REGISTERED SUCCESSFULLY----------\n\n";
    cout<<"\n\n\t\tredirecting to the log-in page.....";            //redirecting to the log-in page after registration
    Sleep(2000);                              
    
    log_in();
}


//---------------MAIN driving FUNCTION-------------------------------------------------------------------

int main(){

    cout<<"\n\n\n\n";

    cout<<"\t\t----------WELCOME!!!----------";

    cout<<"\n\n";

    cout<<"\t\tPress 1 to log in \n\t\tPress 2 for new registration \n\t\tPress 3 to exit \n\n\t\tYour choice: ";
    
    string t;
    cin>>t;

    if(t=="1"){
        //goto log-in func-----------------------
        log_in();

    }else if(t=="2"){
        //goto register new func-----------------
        register_new();
        
    }else if(t=="3"){
        //--------------------user chose to exit----------------------
        system("cls");
        cout<<"\n\n\n\t----------THANK YOU FOR USING OUR SERVICE----------\n";
        Sleep(1000);
        exit(0);
    }else{
        system("cls");
        cout<<"\n\n\t\tInvalid choice......";
        Sleep(1500);
        main();
    }

    return 0;
}