#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <conio.h>

#define USER_MAX 50
#define BUS_MAX 30

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

//Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

//Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

//Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

#define SLOW_BLINKING_RED  "\e[1;5;31m"
#define SLOW_BLINKING_CYAN  "\e[1;5;36m"

//Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

#define hideCursor "\e[?25l"
#define defaultCursor "\e[?25h"

//Spacing 
#define busSpacing "                       " // for animated bus only

typedef struct user user;
typedef struct bus bus;

struct user {
    char fullName[30];
    char userName[20];
    char userPass[20];
    bool userGender; // 0 for men, 1 fo female
    int userAge;
    int userRole; // 1 for customer, 2 for executive, 3 for admin
    int userId;
    bool userStatus; //0 for restricted, 1 for active
};

//User Management
user id[USER_MAX] = { 
    {"Admin", "admin", "pass", false, 22, 3, 1, 1},
    {"Hasib Hasnain", "hasib", "hasib", false, 22, 2, 2, 1},
    {"Atikur Rahman", "rajib", "rajib", false, 22, 1, 3, 1},
    {"Sarowar Mahfuz", "suman", "suman", false, 22, 1, 4, 1}
};
int countUser = 4;
int $myUserId = 0;


//Bus Section
struct bus {
    char busName[20];
    char boardingPoint[20];
    char droppingPoint[20];
    char boardingTime[10];
    int seatNumber;
    bool coachType; // 0 non ac, 1 ac
    int ticketPrice;
    int coachId;
    bool coachStatus;
    int seatList[99];
    int seatHG[99];
};

//Bus Management
bus coach[BUS_MAX] = {
    {"Safar", "Dhaka", "Rajshahi", "8:00am", 57, 0, 700, 1, 1, {0}, {0}}, 
    {"Jatra", "Dhaka", "Khulna", "9:00am", 41, 1, 1600, 2, 1, {0}, {0}},
    {"Zatri", "Dhaka", "Chattagram", "9:00am", 41, 1, 1800, 3, 1, {0}, {0}},
    {"Pother Sur","Dhaka", "Shylet", "10:00am", 41, 0, 1300, 4, 1, {0}, {0}},
    {"Meghdut","Dhaka", "Chapai", "10:00am", 41, 0, 1000, 5, 1, {0},{0}},
    {"Pother Sathi","Dhaka", "Srimangal", "10:330am", 41, 1, 1150, 6, 1, {0}, {0}},
    {"POtho Bondhhu","Dhaka", "Dinajpur", "11:00am", 41, 1, 900, 7, 1, {0}, {0}},
    {"Mridu Goti","Dhaka", "Rajshahi", "10:30am", 41, 0, 400, 8, 1, {0}, {0}},
    {"Shongi","Chapai", "Dhaka", "7:00pm", 41, 1, 900, 9, 1, {0}, {0}},
    {"Akashpoth","Feni", "Bogura", "12:00pm", 41, 1, 700, 10, 1, {0}, {0}},
    {"Shopnopothe","Rajshahi", "Rangpur", "11:30am", 41, 1, 1250, 11, 1, {0}, {0}},
    {"Meghmala","Magura", "Naogoan", "8:00pm", 41, 0, 700, 12, 1, {0}, {0}},
    {"Oronnopoth","Dhaka", "Pabna", "08:30pm", 41, 0, 400, 13, 1, {0}, {0}},
    {"Gotidhara","Rajshahi", "Barishal", "09:00pm", 41, 1, 1400, 14, 1, {0}, {0}},
    {"Songjogpoth","Dhaka", "Cumilla", "09:30pm", 41, 0, 900, 15, 1, {0}, {0}},
    {"Choltipoth","Rajshahi", "Cox's Bazar", "10:00pm", 41, 1, 1600, 16, 1, {0}, {0}},
    {"Chokro","Dhaka", "Jashore", "10:00am", 41, 0, 1000, 17, 1, {0}, {0}},
    {"Prantore","Dhaka", "Narail", "10:20am", 41, 0, 550, 18, 1, {0}, {0}},
    {"Panthopothe","Dhaka", "Magura", "11:45am", 41, 0, 1100, 19, 1, {0}, {0}},
    {"Vromon","Bogura", "Feni", "10:00am", 41, 0, 1400, 20, 1, {0}, {0}},
};
 
int countCoach = 20;
char getBusDepartFrom[20];
char getBusDestiTo[20];
int status; //payment clear or not
int totalMoney = 0;
int genderMatch;

//Default Home variables
bool lang = 0; // 0 for non english. 1 for bangla.


//Functions
void welcomeMsg();
void nonLogged_Menu();
void searchBus();
void ourBranches();
void AboutUs();
void userManual();
void login();
void createAccount();
void customerMenu();
void executiveMenu();
void adminMenu();
void allUserList();
void allBusList();
void setBusSchedule();
void updateBusScedule();
void updateBusTicket();
void showBusSummary(); 
void cancelSeat();
void createNewProfiles(); 
void updateOtherProfiles(); 
void restrictOrActivateUser(); 
void restrictOrActivateCoach(); 
void updateOwnProfile();
void logout();
void myBookedSeat();
void busDepartFrom();
void busDestiTo();
void busSchedule();
void buyTicket(int n);
void invoice(int exactBusId, int exactSeatNum);
void paymentGateway(int BusId, int exactSeatNum);
void paymentMethod(int BusId, int exactSeatNum, int via);
int availableSeat(int s);
void seatPlan(int n);
void ifExit();
void forgetPassword();
void busAnimation();
void busLogo();
void returnToMenu();
void storeDefaultUserData();
void scanUserData();
void appendUserData();
void UpdateStoredUserData();
void UpdateStoredBusData();
void storeDefaultBusData();
void scanBusData();
void appendBusData();
void storeDefaultBusSeatData();
void scanBusSeatData();
void appendBusSeatData();
void UpdateStoredBusSeatData(int exactBusId, int exactSeatNum);
void storeDefaultBusSeatHGData();
void scanBusSeatHGData();
void appendBusSeatHGData();
void UpdateStoredBusSeatHGData(int exactBusId, int exactSeatNum);
void allBusSum();
void allTicketHolder();
const char* showGender(bool gender);
const char* showRole(int role);
const char* showUserStatus(bool status);
const char* showCoachStatus(bool status);
const char* showCoachType(bool icoachType);
const char* showSeatStatus(int iseatStatus);
void sendMsg();
void getMsg();
void maintenanceMode();
void UpdateMaintenanceData();
void ScanMaintenanceData();
void storeDefaultMaintenanceData();
void paymentDetail();
void tempuserlist();

int maintenance = 0;

FILE* allUserData;
FILE* allBusData;
FILE* msg;
FILE* maintenanceData;
FILE* paymentData;
FILE* extra;

int main() {
    storeDefaultMaintenanceData();
    ScanMaintenanceData();
    if(maintenance == 1) {
        maintenanceMode();
    } else {
        storeDefaultUserData();
        scanUserData();
        storeDefaultBusData();
        scanBusData();

        if($myUserId == 0) {
            nonLogged_Menu();
        } else {
            printf("Something went wrong!\n");
            exit(0);
        }
    }
}

void busAnimation() {
    int i, j;
    int width = 5; // Width
    int steps = 10; // Number of steps
    printf(hideCursor);

    for (i = steps; i >= 0; i--) {
        // Clear the screen
        printf("\033[H\033[J");
        printf("\n\n\n");
        
        // Print the ASCII art with appropriate spacing for movement
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "         _________________\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing "       /" BHBLK "|[][][][][][][][]" YEL " | " BHBLK "- -\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "      (    " BHYEL "DURNIBAR BUS" YEL "   | " BHBLK "- -\n");
        for (j = 0; j < i % width; j++) {
            printf(" ");
        }
        printf(busSpacing YEL "      =---" BHBLK "OO" YEL "---------" BHBLK "OO" YEL "---=" BHBLK "@@@\n\n" COLOR_RESET);
        
        // Sleep for a short duration to control the speed of movement
        usleep(200000); // 200 milliseconds
    }
    printf(defaultCursor);

}

void busLogo() {
    //10,8,7,7 spaces
    printf("\n\n\n\n");
    printf(YEL "         _________________\n");
    printf("       /" BHBLK "|[][][][][][][][]" YEL " | " BHBLK "- -\n");
    printf(YEL "      (    " BHYEL "DURNIBAR BUS" YEL "   | " BHBLK "- -\n");
    printf(YEL "      =---" BHBLK "OO" YEL "---------" BHBLK "OO" YEL "---=" BHBLK "@@@\n\n" COLOR_RESET);
}

void busLogo2() {
    //10,8,7,7 spaces
    printf("\n\n\n\n");
    printf(YEL "                                    _________________\n");
    printf("                            /" BHBLK "|[][][][][][][][]" YEL " | " BHBLK "- -\n");
    printf(YEL "                        (    " BHYEL "DURNIBAR BUS" YEL "   | " BHBLK "- -\n");
    printf(YEL "                        =---" BHBLK "OO" YEL "---------" BHBLK "OO" YEL "---=" BHBLK "@@@\n\n" COLOR_RESET);
}

void welcomeMsg() {
    busLogo();
    if($myUserId == 0) {
        printf(BHWHT "            Hello User!\n");
        printf("        Welcome to our system!\n" COLOR_RESET);
    } else {
        printf(BHYEL "     Hello " BHGRN "%s, " BHYEL "an %s!\n", id[$myUserId-1].userName, showRole(id[$myUserId-1].userRole));
        printf(BHYEL "           Welcome Dear!\n" COLOR_RESET);
    }
}

void nonLogged_Menu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    int n;
    printf("\n");
    printf(WHTHB BHBLK "            Main Menu             "reset);
    printf("\n");
    printf(HBLK "        [Choose an option]\n\n");
    printf(BHCYN "  1. Search Bus " SLOW_BLINKING_RED "FAST!\n" COLOR_RESET);
    printf(BHCYN "  2. Bus Schedule\n\n");
    printf("  3. Our Branches\n");
    printf("  4. About Us\n");
    printf("  5. User Manual\n\n");
    printf("  6. Login\n");
    printf("  7. Forget Password\n");
    printf("  8. Create an account " SLOW_BLINKING_RED "JOIN!\n\n" reset);
    printf(BHCYN "  [0] Exit\n" reset);
    printf("\n");
    printf(BHYEL "Choose a option: " COLOR_RESET);
    scanf("%d", &n);

    switch(n) {
        case 0: 
            ifExit();
        case 1: 
            searchBus();
            break;
        case 2: 
            busSchedule();
            break;
        case 3: 
            ourBranches();
            break;
        case 4: 
            AboutUs();
            break;
        case 5: 
            userManual();
            break;
        case 6: 
            login();
            break;
        case 7: 
            forgetPassword();
            break;
        case 8:
            createAccount();
            break;
        default: 
            printf(BHRED "\n\nPlease try again\n\n" COLOR_RESET);
            system("pause");
            nonLogged_Menu();
            break;
    }
}

void login() {
    busAnimation();
    system("cls");
    char currName[20];
    char currPass[20];
    printf(WHTHB BHBLK "\n             Login Page             \n" COLOR_RESET);
    printf(HBLK"   [Write Username and Password]\n\n");
    printf(BHCYN "  Username: " COLOR_RESET);
    scanf("%s", currName);
    printf(BHCYN "  Password: " COLOR_RESET);

    int i;
    char ch;
    while ((ch = getch()) != 13 && i < sizeof(currPass) - 1) { // Ensuring the password doesn't overflow
        if (ch == 8) { 
            if (i > 0) {
                i--; 
                printf("\b \b"); 
            }
        } else if (ch != 13) {
            putch('*');
            currPass[i] = ch;
            i++;
        }
    }
    currPass[i] = '\0';


    //scanf("%s", currPass);
    
    for(int i = 0; i < countUser; i++) {
        bool nameMatching = strcmp(currName, id[i].userName);

        if(nameMatching == 0){
            bool passMatching = strcmp(currPass, id[i].userPass);
            if(passMatching == 0) {

                if(id[i].userStatus == 0) {
                    printf(BHRED"\n\n  Sorry!\n");
                    printf(BHYEL"  Your profile has been restricted by Admin.\n\n"COLOR_RESET);
                    system("pause");
                    returnToMenu();
                    return;
                }

                printf(BHGRN "\n\n     Login Successfull!\n\n" COLOR_RESET);
                system("pause");
                $myUserId = i+1;
                if(id[i].userRole == 1) {
                    customerMenu();
                    break;
                } else if(id[i].userRole == 2) {
                    executiveMenu();
                    break;
                } else if(id[i].userRole == 3) {
                    adminMenu();
                    break;
                } else {
                    printf("\nThere is a problem with role\n\n");
                    break;
                }
            } 
            else {
                printf(BHRED "\nIncorrect Username or Password.\n\n" COLOR_RESET);
                int p;
                
                printf(BHWHT "Now what?\n");
                printf(BHCYN "1. Forget Password\n");
                printf("2. Create Account\n");
                printf("3. Return to Main Menu\n");
                printf("4. Try to login again\n\n" COLOR_RESET);
                printf(BHYEL "Choose an option: " COLOR_RESET);
                scanf("%d", &p);
                switch(p) {
                    case 1:
                        forgetPassword();
                        break;
                    case 2:
                        createAccount();
                        break;
                    case 3:
                        nonLogged_Menu();
                        break;
                    case 4: 
                        login();
                        break;
                    default:
                        printf(BHRED "\n\nWrong Keyword. Try again\n\n" COLOR_RESET);
                        system("pause");
                        login();
                        break;
                }
            }
        } 
        if (i == countUser-1) {
            printf(BHRED "\nIncorrect Username or Password. Try again\n\n" COLOR_RESET); 
            int q;
            printf(BHWHT "Now What? \n");
            printf(BHCYN "1. Forget Password\n");
            printf("2. Create Account\n");
            printf("3. Return to Main Menu\n");
            printf("4. Try again\n\n");
            printf(BHYEL "Choose an option: " COLOR_RESET);
            scanf("%d", &q);
            switch(q) {
                case 1:
                    forgetPassword();
                    break;
                case 2:
                    createAccount();
                    break;
                case 3:
                    nonLogged_Menu();
                    break;
                case 4: 
                    login();
                    break;
                default:
                    printf(BHRED "\n\nWrong Keyword. Try again\n\n" COLOR_RESET);
                    system("pause");
                    login();
                    break;
            }
        }
    }
}

void forgetPassword() {
    busAnimation();
    system("cls");
    busLogo();
    printf(WHTHB "\n            Forget Password             "reset);
    printf("\n\n");
    char stemp;
    int itemp;
    int store;
    int verify = 0;
    char currName[20];
    printf(BHCYN "  Username: " COLOR_RESET);
    scanf("%c", &stemp);
    scanf("%[^\n]", currName);
    for(int i = 0; i < countUser; i++) {
        bool nameMatching = strcmp(currName, id[i].userName);
        if(nameMatching == 0) {
            store = i + 1;
            verify++;
        }  
    }

    printf(BHCYN "  Fullname: " COLOR_RESET);
    scanf("%c", &stemp);
    scanf("%[^\n]", currName);
    bool nameMatching = strcmp(currName, id[store-1].fullName);
    if(nameMatching == 0) {
        verify++;
    }  

    printf(BHCYN "  Age: " COLOR_RESET);
    scanf("%d", &itemp);
    if(itemp == id[store-1].userAge) {
        verify++;
    }  

    if(verify == 3 && id[store-1].userRole == 1) {
        $myUserId = store;
        printf(BHGRN "\n  Your provided informations are correct. " COLOR_RESET);
        printf(BHYEL "\n  You are eligible for changing password." COLOR_RESET);
        printf(BHCYN "\n\n  Write new password: " COLOR_RESET);

        int j = 0;
        char ch;
        char currPass[20];
        while ((ch = getch()) != 13 && j < sizeof(currPass) - 1) { 
        if (ch == 8) { 
            if (j > 0) {
                j--; 
                printf("\b \b"); 
            }
        } else if (ch != 13) { 
            putch('*'); 
            currPass[j] = ch; 
            j++; 
        }
    }
        currPass[j] = '\0'; 
        strcpy(id[$myUserId-1].userPass, currPass);
        UpdateStoredUserData();

        //scanf("%c", &stemp);
        //scanf("%[^\n]", id[$myUserId-1].userPass);
        
        printf(BHGRN "\n  Password has been changed." COLOR_RESET);
        printf(BHYEL "\n  Please login now!\n\n" COLOR_RESET);
        system("pause");
        login();
    } else {
        printf(BHRED "\n  Sorry. Password can not be changed." COLOR_RESET);
        printf(BHYEL "\n  Maybe your informations are wrong or you are trying to access admin panel in a wrong way...\n\n" COLOR_RESET);
        system("pause");
        returnToMenu();
    }
}

void createAccount() {
    busAnimation();
    system("cls");
    char currName[20];
    char ctemp;
    bool nameMatching;
    printf(WHTHB BHBLK "             Create an account            \n" COLOR_RESET);
    printf(HBLK"     [Submit Correct Informantions]\n\n");
    countUser++;
    printf(BHCYN "Fullname: " COLOR_RESET);
    //scanf("%s", id[countUser-1].fullName);
    scanf("%c", &ctemp);
    scanf("%[^\n]", id[countUser-1].fullName);
    //fgets(id[countUser-1].fullName, 30, stdin);

    do{
        printf(BHCYN "Username (no space allowed): " COLOR_RESET);
        scanf("%s", currName);
        for(int i = 0; i < countUser; i++) {
            nameMatching = strcmp(currName, id[i].userName);

            if(nameMatching == 0){
                printf(BHRED "\n\n  Username isn't available!\n       Try Another one.\n\n" COLOR_RESET); 
                system("pause"); 
                break;          
            }
        }
    } while(nameMatching == 0);

    strcpy(id[countUser-1].userName, currName);
    printf(BHGRN "Username is available.\n" COLOR_RESET);
    printf(BHCYN "Password: " COLOR_RESET);
    scanf("%s", id[countUser-1].userPass);
    printf(BHCYN "Gender (0 for men, 1 for women): " COLOR_RESET);
    scanf("%d", &id[countUser-1].userGender);
    printf(BHCYN "Age: " COLOR_RESET);
    scanf("%d", &id[countUser-1].userAge);

    id[countUser-1].userRole = 1;
    id[countUser-1].userStatus = 1;
    id[countUser-1].userId = countUser;
    appendUserData();

    printf("\n\n");
    system("pause");
    system("cls");
    printf(BHGRN "\nAccount has been created!\n\n" COLOR_RESET);
    printf(BHYEL "Your Informations: \n");
    printf(BHCYN "Full name: %s \n", id[countUser-1].fullName);
    printf("Username: %s \n", id[countUser-1].userName);
    printf("Password: %s \n", id[countUser-1].userPass);
    printf("Gender: %s \n", showGender(id[countUser-1].userGender));
    printf("Age: %d \n", id[countUser-1].userAge);
    printf("Role: %s \n", showRole(id[countUser-1].userRole));
    printf("User ID: %d \n" COLOR_RESET, id[countUser-1].userId);

    printf(BHYEL "\nPlease login now.\n" COLOR_RESET);
    system("pause");
    login();
}

void updateOwnProfile() {
    system("cls");
    printf("\n== My Profile ==\n");
    printf("1. Full Name: %s\n", id[$myUserId-1].fullName);
    printf("2. Username: %s\n", id[$myUserId-1].userName);
    printf("3. Password: %s\n", id[$myUserId-1].userPass);
    printf("4. Gender: %s\n", showGender(id[$myUserId-1].userGender));
    printf("5. Age: %d\n", id[$myUserId-1].userAge);
    printf("Role: %s\n", showRole(id[$myUserId-1].userRole));
    printf("User ID: %d\n\n", id[$myUserId-1].userId);

    int n;
    int m;
    char temp;
    char currName[30];
    bool p;
    int q;

    printf("Want to change profile? (yes = 1, no = 0): ");
    scanf("%d", &n);
    if(n==1) {
        do {
            printf("Choose what you want to change (Enter 0 for exit): ");
            scanf("%d", &m);
            switch(m) {
                case 1:
                    printf("Enter new fullname: ");
                    scanf("%c", &temp);
                    scanf("%[^\n]", currName);
                    strcpy(id[$myUserId-1].fullName, currName);
                    break;
                case 2:
                    printf("Enter new username: ");
                    scanf("%c", &temp);
                    scanf("%[^\n]", currName);
                    strcpy(id[$myUserId-1].userName, currName);
                    break;
                case 3:
                    printf("Enter new password: ");
                    scanf("%c", &temp);
                    scanf("%[^\n]", currName);
                    strcpy(id[$myUserId-1].userPass, currName);
                    break;
                case 4:
                    printf("Enter your correct gender: ");
                    scanf("%d", &p);
                    id[$myUserId-1].userGender = p;
                    break;
                case 5:
                    printf("Enter your new age: ");
                    scanf("%d", &q);
                    id[$myUserId-1].userAge = q;
                    break;
                case 0:
                    printf("Your profile has been updated.\n");
                    break;
                default:
                    printf("Wrong number!");
                    break;
            }
        } while(m != 0);
        UpdateStoredUserData();
        updateOwnProfile();
    } else if(n == 0) {
        returnToMenu();
    } else {
        updateOwnProfile();
    }
}

void logout() {
    $myUserId = 0;
    printf( BHGRN "\nYou have logged out successfully...\n\n" COLOR_RESET);
    system("pause");
    system("cls");
    nonLogged_Menu();
}

void searchBus() {
    busAnimation();
    system("cls");
    busLogo();
    printf(WHTHB BHBLK "           Bus Schedule           \n" COLOR_RESET);
    busDepartFrom();
    busDestiTo();
    printf(WHTHB BHBLK "           Bus Schedule           \n" COLOR_RESET);
    int temp = 0;
    //Focus here
    int storetemp[20];
    for(int i=0; i<20; i++) {
        storetemp[i] = 0;
    }

    printf(BHCYN "\n From: " YEL " %s " BHCYN " \tTo: " YEL " %s\n\n", getBusDepartFrom, getBusDestiTo);
    for(int i = 0; i < BUS_MAX; i++) {
        if(strcmp(coach[i].boardingPoint, getBusDepartFrom) == 0) {
            if(strcmp(coach[i].droppingPoint, getBusDestiTo) == 0) {
                printf(BHCYN "  Bus Name         :    " WHT "%-15s\n" COLOR_RESET, coach[i].busName);
                printf(BHCYN "  Boarding Point   :    " WHT "%-15s\n" COLOR_RESET, coach[i].boardingPoint);
                printf(BHCYN "  Dropping Point   :    " WHT "%-15s\n" COLOR_RESET, coach[i].droppingPoint);
                printf(BHCYN "  Boarding Time    :    " WHT "%-15s\n" COLOR_RESET, coach[i].boardingTime);
                printf(BHCYN "  Total Seat Num   :    " WHT "%-15d\n" COLOR_RESET, coach[i].seatNumber);
                printf(BHGRN "  Available Seat   :    %-15d\n" COLOR_RESET, availableSeat(coach[i].coachId));
                printf(BHCYN "  Coach Type       :    " WHT "%-15s\n" COLOR_RESET, showCoachType(coach[i].coachType));
                printf(BHRED "  Coach ID         :    %-15d\n" COLOR_RESET, coach[i].coachId);
                printf(BHCYN "  Coach Status     :    %-15s\n" COLOR_RESET, showCoachStatus(coach[i].coachStatus));
                printf(CYN   "  Ticket Price     :    " WHT "%-15d\n\n" COLOR_RESET, coach[i].ticketPrice);
                storetemp[temp] = i+1;
                temp++;
            }
        }
    }
    if(temp==0) {
        printf( BHRED "\nSorry, we have no bus in this route :(\n\n" COLOR_RESET );
        system("pause");
        searchBus();
        return;
    }

    int n;
    do {
        printf( BHWHT "Enter Coach ID to buy a ticket.\n" BHRED "* Place '0' to go back.\n\n" COLOR_RESET);
        printf(BHYEL "Enter your choice: " COLOR_RESET);
        scanf("%d", &n);

        if(n == 0) {
            searchBus();
            return;
        } 

        for(int i=0; i<20; i++) {
            if(storetemp[i] == n) {
                if(coach[n-1].coachStatus == 0) {
                    printf(BHWHT "\n\nThis Bus is Currently Unavailable!\n");
                    printf(BHYEL "Contact with Admin for More Information\n\n" COLOR_RESET);
                    system("pause");
                    if(temp == 1) {
                        searchBus();
                        return;
                    }
                } else {
                    buyTicket(n);
                    return;
                }
            }
        }

        printf("You have inserted wrong BusID!\n");
        printf("Try Again!\n\n");
        system("pause");

        // if(n>0 && n<countCoach) {
        //     if(coach[n-1].coachStatus == 0) {
        //         printf(BHWHT "\n\nThis Bus is Currently Unavailable!\n");
        //         printf(BHYEL "Contact with Admin for More Information\n\n" COLOR_RESET);
        //         system("pause");
        //         if(temp == 1) {
        //             searchBus();
        //         }
        //     } else {
        //         buyTicket(n);
        //         return;
        //     }
        // } else {
        //     printf("You have inserted wrong BusID!\n");
        //     printf("Try Again!\n\n");
        //     system("pause");
        // }
    } while(true);
    

}

void busDepartFrom() {

    struct busDepart {
        char busDepart[20];
    } busDepartFromTemp[BUS_MAX];

    printf(BHYEL "\n\nDeparture From: \n");
    int countUnique = 0;
    for(int i=0; i<countCoach; i++) {
        bool isUnique = 1;
        for(int j=0; j<i; j++) {
            if(strcmp(coach[i].boardingPoint, coach[j].boardingPoint) == 0) {
                isUnique = 0;
                break;
            }
        }
        if(isUnique) {
            countUnique++;
            printf(BHCYN "%d. %s\n" COLOR_RESET, countUnique, coach[i].boardingPoint);
            strcpy(busDepartFromTemp[countUnique-1].busDepart, coach[i].boardingPoint);
        }
    }   
    printf(BHRED "\n\n0. Back to Main Menu\n");
    printf(YEL "\nEnter your choice: " COLOR_RESET);
    int n;
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
        return;
    }
    strcpy(getBusDepartFrom, busDepartFromTemp[n-1].busDepart);
    printf(BHGRN "\nYou are going from %s\n\n" COLOR_RESET, getBusDepartFrom);
    system("pause");
}

void busDestiTo() {
    struct busDesti {
    char busDesti[20];
    } busDestiToTemp[BUS_MAX];

    printf(BHYEL "\n\nDestination To:\n");
    int countUnique = 0;
    for(int i=0; i<countCoach; i++) {
        bool isUnique = 1;
        for(int j=0; j<i; j++) {
            if(strcmp(coach[i].droppingPoint, coach[j].droppingPoint) == 0) {
                isUnique = 0;
                break;
            }
        }
        if(isUnique) {
            countUnique++;
            printf(BHCYN "%d. %s\n" COLOR_RESET, countUnique, coach[i].droppingPoint);
            strcpy(busDestiToTemp[countUnique-1].busDesti, coach[i].droppingPoint);
        }
    }
    printf(BHRED "\n\n0. Main Menu\n");

    printf(YEL "\nEnter your choice: " COLOR_RESET);
    int n;
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
        return;
    }
    strcpy(getBusDestiTo, busDestiToTemp[n-1].busDesti);
    printf(BHGRN "\nYou have choosen to go %s\n\n" COLOR_RESET, getBusDestiTo);
    system("pause");
    system("cls");
}

int availableSeat(int s) {
    int emptySeat = 0;
    for(int i=0; i<coach[s-1].seatNumber; i++) {
        if(coach[s-1].seatList[i] == 0) {
            emptySeat++;
        }
    }
    return emptySeat;
}

void busSchedule() {
    busAnimation();
    system("cls");
    busLogo();
    printf("                                     ");
    printf(WHTHB BHBLK"                 Bus Schedule                 \n" COLOR_RESET);
    printf("\n                                  ");
    printf(HBLK "[Currently this routes and buses are available only.]\n\n");
    printf(BLUHB BLKHB "\nBus Name        From            Destination      Time          Seat           Coach Type        Price        Coach ID   " COLOR_RESET);
    printf("\n");
    for(int i=0; i<countCoach; i++) {
        if(i%2 == 0) {
            printf(MAGB);
        } else {
            printf(BLUB);
        }
        printf("%-15s %-15s %-15s %-15s %-15d %-15s %-15d %-8d" reset, coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, coach[i].seatNumber, showCoachType(coach[i].coachType), coach[i].ticketPrice, coach[i].coachId);
        printf("\n");
    }
    printf(BHYEL "\n\n\n                               Now What?\n");
    printf(BHCYN "                                 1. Search Bus\n");
    printf( "                                 2. Go back\n");
    int n;
    printf(BHYEL "                               Enter your choice: " COLOR_RESET);
    scanf("%d", &n);
    switch(n){
        case 1:
            searchBus();
            break;
        case 2:
            returnToMenu();
        default:
            printf(BHRED "\n\n                                  Wrong input!\n\n" COLOR_RESET);
            system("pause");
            busSchedule();
    }
}

void buyTicket(int n) {
    system("cls");
    busAnimation();
    printf(WHTHB BHBLK"                                Buy Ticket                                " COLOR_RESET);
    seatPlan(n);

    //Ticketing

    if($myUserId==0){
        printf(BHRED "\n\n\n                    Please Login for buying a ticket.\n\n" COLOR_RESET);
        system("pause");
        int p;
        do {
            printf(BHYEL "\nChoose an option:\n");
            printf(BHCYN " 1. Login\n");
            printf(" 2. Forgotten Password\n");
            printf(" 3. Create an account\n");
            printf(" 4. Search Bus\n");
            printf(" 5. Main Menu\n\n");
            printf(BHYEL "Enter your choice: "COLOR_RESET);
            scanf("%d", &p);
            switch(p) {
                case 1: 
                    login();
                    return;
                case 2:
                    forgetPassword();
                    return;
                case 3:
                    createAccount();
                    return;
                case 4:
                    searchBus();
                    return;
                case 5:
                    returnToMenu();
                    return;
                default:
                    printf(BHRED "Invalid Insertion!\n" COLOR_RESET);
            } 
        } while(p>5 || p<1);
    } 

    int choice;
    genderMatch = 0;
    int x = 0;
    int ifTicketForYou;

    do {
        printf(BHWHT "                  Buying ticket for you or someone else?\n");
        printf(BHRED "                     ( Enter 1 for yours, 0 for others )\n" COLOR_RESET);
        printf(BHYEL "                  Enter your choice: " COLOR_RESET);
        scanf("%d", &ifTicketForYou);
        if(ifTicketForYou != 0 && ifTicketForYou != 1) {
            printf(BHRED "\n\n                  Something Went wrong. Try again.\n\n");
            system("pause");
            printf("\n");
            continue;
        }
        printf(BHWHT "\n\n                  Enter Seat number to buy a ticket " BHRED "\n                  (Put 0 to return)\n" COLOR_RESET );
        printf(BHYEL "                  Enter your choice: " COLOR_RESET );
        scanf("%d", &choice);
        if(choice == 0) {
            searchBus();
            return;
        }
        if(choice > coach[n-1].seatNumber || choice < 1) {
            printf(BHRED "\n                  Wrong Seat Number\n");
            continue;
        }

        if(coach[n-1].seatList[choice-1] == 0) {
            if(ifTicketForYou == 0) {
                printf(BHWHT "\n                  Ticket owner's gender (1 for men, 2 for women)\n" COLOR_RESET);
                printf(BHYEL "                  Enter your choice: " COLOR_RESET);
            scanf("%d", &genderMatch);
            } else if(ifTicketForYou == 1){
                genderMatch = (id[$myUserId-1].userGender+1);
            } else {
                printf(BHRED "\n\n                  Something Went wrong. Try again.\n\n" COLOR_RESET);
                system("                  pause");
                continue;
            }
            if(choice == 1 || (choice-1)%4 == 0) {
                if(coach[n-1].seatHG[choice] == genderMatch || coach[n-1].seatList[choice] == 0) {
                    //coach[n-1].seatList[choice-1] = -1;
                    coach[n-1].seatHG[choice-1] = -1;
                    
                    printf(BHGRN "\n                  You have to complete booking ASAP!\n\n" COLOR_RESET);
                    x = 1;
                    system("                  pause");
            } else {
                    printf(BHRED "\n                  Sorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("                  pause");
                }
            } else if(choice == 2 || (choice-2)%4 == 0) {
                if(coach[n-1].seatHG[choice-2] == genderMatch || coach[n-1].seatHG[choice-2] == 0) {
                    //coach[n-1].seatList[choice-1] = -1;
                    coach[n-1].seatHG[choice-1] = -1;
                    printf(BHGRN "\n\n                  You have to complete booking ASAP!\n\n" COLOR_RESET);
                    system("                  pause");
                    x = 1;
                } else {
                    printf(BHRED "\n\n                  Sorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("                  pause");
                }   
            } else if((choice+1)%4 == 0) {
                if(coach[n-1].seatHG[choice] == genderMatch || coach[n-1].seatHG[choice] == 0) {
                    //coach[n-1].seatList[choice-1] = -1;
                    coach[n-1].seatHG[choice-1] = -1;
                    printf(BHGRN "\n\n                  You have to complete booking ASAP!\n\n" COLOR_RESET);
                    x = 1;
                    system("                  pause");
                } else {
                    printf(BHRED "\n\n                  Sorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("                  pause");
                }
            } else if(choice%4 == 0) {
                if(coach[n-1].seatHG[choice-2] == genderMatch || coach[n-1].seatHG[choice-2] == 0) {
                    //coach[n-1].seatList[choice-1] = -1;
                    coach[n-1].seatHG[choice-1] = -1;
                    printf(BHGRN "\n\n                  You have to complete booking ASAP!\n\n" COLOR_RESET);
                    x = 1;
                    system("                  pause");
                } else {
                    printf(BHRED "\n\n                  Sorry! You cann't seat beside your unknown opposite gender.\n\n" COLOR_RESET);
                    system("                  pause");
                }
            }
        } else {
            printf(BHRED "\n                  Sorry! The seat has been already booked!\n" COLOR_RESET);
            system("                  pause");
            searchBus();
            return;
        }
    } while (x == 0);

    system("cls");
    busAnimation();
    printf(WHTHB BHBLK"                                Updated Seat Plan                                " COLOR_RESET);
    seatPlan(n);
    coach[n-1].seatHG[choice-1] = 0;
    status = 0;
    system("\n\n\n                                                pause");
    invoice(coach[n-1].coachId, choice-1);
    if(status != 1) {
        printf("                  Ticket booking unsuccessfull!\n");
        coach[n-1].seatHG[choice-1] = 0;
        coach[n-1].seatList[choice-1] = 0;
        system("                  pause");
        buyTicket(n);
        return;
    }
    UpdateStoredBusSeatData(n, choice);
    UpdateStoredBusSeatHGData(n, choice);
    system("cls");
    busAnimation();
    printf(WHTHB BHBLK"                                Updated Seat Plan                                " COLOR_RESET);
    seatPlan(n);
    printf("\n\n");

    int q;
    do {
        printf(BHYEL "\n\nChoose an option:\n");
        printf(BHWHT" 1. Search Bus\n");
        printf(" 2. Buy Ticket Again\n");
        printf(" 3. Main Menu\n\n");
        printf(BHYEL "Enter your choice:  "COLOR_RESET);
        scanf("%d", &q);
        switch(q) {
            case  1:
                searchBus();
                return; 
            case  2:
                buyTicket(n);
                return;
            case 3:
                returnToMenu();
                return;
            default:
                printf(BHRED "Invalid Insertion!\n" COLOR_RESET);
            } 
        } while(q>3 || q<1);
}

void invoice(int BusId, int exactSeatNum) {
    system("cls");
    busLogo();
    printf("                     "WHTHB BHBLK "\n              Auto Genareted Invoice             \n" COLOR_RESET);
    printf("\n\n");
    struct tm tm = *localtime(&(time_t){ time(NULL) });

    printf(BHCYN"     Bus name          : " HWHT "%-20s\n", coach[BusId-1].busName);
    printf(BHCYN"     Bus ID            : " HWHT "%-20d\n", coach[BusId-1].coachId);
    printf(BHCYN"     From              : " HWHT "%-20s\n", coach[BusId-1].boardingPoint);
    printf(BHCYN"     To                : " HWHT "%-20s\n", coach[BusId-1].droppingPoint);
    printf(BHCYN"     Selected Seat     : " HWHT "%-20d\n", exactSeatNum+1);
    printf(BHCYN"     Ticket Price      : " HWHT "%-20d\n", coach[BusId-1].ticketPrice);
    printf(BHCYN"     Your Name         : " HWHT "%-20s\n", id[$myUserId-1].fullName);
    printf(BHCYN"     Seat for          : " HWHT "%-20s\n", showGender(genderMatch-1));
    printf(BHCYN"     Invoice Issued at : " HWHT "%-20s\n\n", asctime(&tm));

    int p;
    printf(BHYEL "  You are trying to buy a ticket on this bus.\n\n");
    printf(BHWHT "  Are your sure?\n" reset);
    printf(BHCYN "      1. Sure\n");
    printf(      "      0. Not Sure\n\n" reset);
    printf(BHYEL "  Enter your choice: " COLOR_RESET);
    scanf("%d", &p);
    if(p != 1) {
        buyTicket(BusId);
        return;
    }
    printf(BHGRN "\n  You have to pay now!\n\n" COLOR_RESET);
    system("pause");
    paymentGateway(BusId, exactSeatNum);
}

void paymentGateway(int BusId, int exactSeatNum) {

    int n;
    int m;
    int p;
    int via;
    int amount;
    status = 0;

    do {
        system("cls");
        busAnimation();
        system("cls");
        busLogo();
        printf(WHTHB BHBLK "\n             Payment Gateway             \n" COLOR_RESET);
        printf(BHYEL "\nChoose a Medium for Payment: \n");
        printf(BHWHT "1. Visa\n");
        printf("2. Master Card\n");
        printf("3. BDBL\n");
        printf("4. Paypal\n");
        printf("5. Mobile Banking\n");
        printf("0. Back\n\n"COLOR_RESET);
        printf(BHCYN "Enter your choice: "COLOR_RESET);
        scanf("%d", &n);
        switch(n) {
            case 1:
                via = 1;
                paymentMethod(BusId, exactSeatNum, via);
                break;
            case 2:
                via = 2;
                paymentMethod(BusId, exactSeatNum, via);
                break;
            case 3:
                via = 3;
                paymentMethod(BusId, exactSeatNum, via);
                break;
            case 4:
                via = 4;
                paymentMethod(BusId, exactSeatNum, via);
                break;
            case 5:
                do {
                    printf(BHWHT "  6. Nagad\n");
                    printf("  7. Bkash\n");
                    printf("  8. Dutch bangla\n");
                    printf("  9. Back\n\n" COLOR_RESET);
                    printf(BHCYN "Enter your choice: " COLOR_RESET);
                    scanf("%d", &m);
                    switch(m);
                        case 6:
                            via = 6;
                            paymentMethod(BusId, exactSeatNum, via);
                            break;
                        case 7:
                            via = 7;
                            paymentMethod(BusId, exactSeatNum, via);
                            break;
                        case 8:
                            via = 8;
                            paymentMethod(BusId, exactSeatNum, via);
                            break;
                        case 9: 
                            invoice(BusId, exactSeatNum);
                            break;
                } while (status != 1);
                break;
            case 0:
                invoice(BusId, exactSeatNum);
                break;
            default:
                printf(BHRED "Wrong choice.\n" COLOR_RESET);
                printf("pause");
                break;
        }
    }while(status != 1 || n>9 || n<0);


}

void seatPlan(int n) {
    printf("\n\n");
    printf(BHCYN"                         Bus name    :   " BHWHT "%-15s\n", coach[n-1].busName);
    printf(BHCYN"                         Bus ID      :   " BHWHT "%-15d\n", coach[n-1].coachId);
    printf(BHCYN"                         From        :   " BHWHT "%-15s\n", coach[n-1].boardingPoint);
    printf(BHCYN"                         To          :   " BHWHT "%-15s\n\n", coach[n-1].droppingPoint);
    printf(BLKHB BHWHT"                                Seat Plan                                " COLOR_RESET);
    printf("\n\n");
    int tabtemp = 0;
    int lastrowtemp = 0;
    for(int i=0; i<coach[n-1].seatNumber; i++) {
        if(i+5 >= coach[n-1].seatNumber) {
            if(tabtemp==2) {
                printf("\n");
                tabtemp = 0;
            }
            printf("%d. %s \t", i+1, showSeatStatus(coach[n-1].seatHG[i]));
            continue;
        } else {
            if((i+1)%4==1 && (i+1)>=4) {
                printf("\n");
            }
            printf("%d. %s \t", i+1, showSeatStatus(coach[n-1].seatHG[i]));
            tabtemp++;
            if(tabtemp == 2 && i+6 < coach[n-1].seatNumber) {
                printf("\t\t");
                tabtemp = 0;
            }
        }
    }
    printf("\n\n\n");
}

void myBookedSeat() {
    system("cls");
    busLogo();
    printf(WHTHB BHBLK "            My Booked Seat              \n" COLOR_RESET);
    printf("\n\n");
    int tempBus[50];
    int tempSeat[50];
    int t = 0;
    int serial = 0;
    int tempSeatNum;

    for(int i=0; i<countCoach; i++) {
        for(int j=0; j<coach[i].seatNumber; j++) {
            if($myUserId == coach[i].seatList[j]) {
                serial++;
                printf(BHWHT"[Ticket Serial: %d]\n"COLOR_RESET, serial);
                printf("Bus Name: %s\n", coach[i].busName);
                printf("Bus ID: %d\n", coach[i].coachId);
                tempBus[t] = coach[i].coachId;
                printf("Boarding Point: %s\n", coach[i].boardingPoint);
                printf("Dropping Point: %s\n", coach[i].droppingPoint);
                printf("Boarding Time: %s\n", coach[i].boardingTime);
                printf("Coach Type: %s\n", showCoachType( coach[i].coachType));
                printf("Ticket Price: %d\n"BHGRN"(Paid)\n"COLOR_RESET, coach[i].ticketPrice);
                tempSeatNum = j+i;
                printf(BHYEL"Booked Seat Number: %d\n\n"COLOR_RESET, j+1);
                tempSeat[t] = j+1; 
                t++;
            }
        }
    }

    int n;
    int m;
    int x;
    int y;
    
    if(serial>0) {

        printf("Want to cancel any ticket?\n");
        printf("Enter 1 for yes, 0 for no: ");
        scanf("%d", &n);
        if(n==1) {
            printf("Enter ticket serial num: ");
            scanf("%d", &m);
            if(m<1 || m>serial) {
                printf("Invalid Serial Number!\n\n");
                system("pause");
                myBookedSeat();
                return;
            }
            x = tempBus[m-1];
            y = tempSeat[m-1];
            coach[x-1].seatList[y-1] = 0;
            coach[x-1].seatHG[y-1] = 0;
            UpdateStoredBusSeatHGData(x-1, y-1);
            UpdateStoredBusSeatData(x-1, y-1);
            printf("Your seat has been cancelled!\n");
            system("pause");
            myBookedSeat();
        } else{
            system("pause");
            returnToMenu();
        }
    } else {
        printf("You haven't booked any ticket till now!\n");
        system("pause");
        returnToMenu();
    }
}

void cancelSeat() {
    busAnimation();
    system("cls");
    printf("\n\n\n             ");
    printf(WHTHB BHBLK "              Cancel Any Seat             \n" COLOR_RESET);
    int n;
    printf(HBLK"                [You can cancel any ticket you want]\n\n" reset);
    printf(BHWHT"  Enter BusID "BHRED"(Press 0 to return): "reset);
    scanf("%d", &n);
    if(n == 0) {
        returnToMenu();
        return;
    } 
    if(n>countCoach || n<1) {
        printf("\n\nWrong BusID!\n\n");
        system("pause");
        cancelSeat();
        return;
    }
    seatPlan(n);
    int m;
    int p;

    do{
        printf(BHWHT "Enter the seat number you want to empty: "reset);
        scanf("%d", &m);
        if(m>coach[n-1].seatNumber && m<coach[n-1].seatNumber) {
            printf(BHRED"\n\nWrong Seat Number.\n\n"reset);
        }
        if(coach[n-1].seatList[m-1] == 0) {
            printf(BHRED"\n\nSeat is already Empty!\n\n"reset);
        } else{
            printf("\n                        "MAGB" TICKET HOLDER DETAIL "COLOR_RESET"\n");
            printf("\n"BHWHT"Name:"reset" %s\n", id[coach[n-1].seatList[m-1]].fullName);
            printf(BHWHT"Role:"reset" %s\n", showRole(id[coach[n-1].seatList[m-1]].userRole)); 
            printf(BHWHT"Ticket Price:"reset" %d "BHGRN"(Paid)\n\n"COLOR_RESET, coach[n-1].ticketPrice);
            printf(BHWHT"Your are trying to cancel this ticket.\n"reset);
            printf(BHRED"     Are you sure?\n"reset);
            printf(HCYN"        1. Yes\n");
            printf(HCYN"        2. No\n"reset);
            printf(BHYEL"\nEnter your choice: ");
            scanf("%d", &p);
            if(p!=1) {
                printf(BHYEL"\n\nMake a choice again!\n\n"reset);
                system("pause");
                printf("\n\n");
                continue;
            }
            coach[n-1].seatList[m-1] = 0;
            coach[n-1].seatHG[m-1] = 0;
            UpdateStoredBusSeatData(n, m);
            UpdateStoredBusSeatHGData(n, m);
            system("cls");
            printf("\n\n\n             ");
            printf(WHTHB BHBLK "                  Cancel Any Seat             \n" COLOR_RESET);
            printf(HBLK"                      [Here is the updated seat plan]\n\n"reset);
            seatPlan(n);
            printf(BHWHT"          "BHYEL"%d Number"BHGRN" Seat of "BHYEL"%s"BHGRN" Bus Has Been Cancelled!\n\n"reset, m, coach[n-1].busName);
            system("pause");
            cancelSeat();
        }
    } while(true);

}

void customerMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    int n;
    
    printf(WHTHB BHBLK "\n         Customer Menu         \n" COLOR_RESET);
    printf(HBLK "       [Choose an option] \n\n");
    printf(BHCYN"  1. Search Bus\n");
    printf("  2. Bus Schedule\n\n");
    printf("  3. Update Own Profile\n");
    printf("  4. My Booked Seat\n");
    printf("  5. Cancel Seat\n");
    printf("  6. Send a Msg to Admin\n\n");
    printf("  7. User Manual\n");        
    printf("  8. Our Branches\n");
    printf("  9. About Us\n\n");
    printf("  10. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "         [0] Exit\n\n" COLOR_RESET);
    printf(BHYEL "Choose an option: " COLOR_RESET);
    scanf("%d", &n);

    switch(n) {
        case 0:
            ifExit();
        case 1:
            searchBus();
            break;
        case 2:
            busSchedule();
            break;
        case 3:
            updateOwnProfile();
            break;
        case 4:
            myBookedSeat();
            break;    
        case 5:
            //cancelSeat();
            myBookedSeat();
            break;
        case 6:
            sendMsg();
            break;
        case 7:
            userManual();
            break;
        case 8:
            ourBranches();
            break;
        case 9:
            AboutUs();
            break;
        case 10:
            logout();
            break;
        default:
            printf(BHRED "   \n\nSomething went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            customerMenu();
            return;
    }
}

void executiveMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    printf(WHTHB BHBLK"\n             Executive Menu              \n" COLOR_RESET);
    printf(HBLK "         [Choose an option] \n\n");
    printf(BHCYN "  1. Search Bus\n");
    printf("  2. Bus Schedule\n\n");
    printf(BHYEL" Special Menu For Executive\n");
    printf(BHCYN"  3. Show System Summary\n");
    printf("  4. Active Or Inactive Bus\n");
    printf("  5. Cancel Any Seat\n");
    printf("  6. Restrict Or Activate Users\n");
    printf("  7. View Payment Details\n\n");
    printf("  8. Cancel Own Seat\n");
    printf("  9. Update Own Profile\n");
    printf("  10. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "            [0] Exit\n\n");
    printf(BHYEL "\nChoose an option: " COLOR_RESET);

    int n;
    scanf("%d", &n);

    switch(n) {
        case 1:
            searchBus();
            break;
        case 2:
            busSchedule();
            break;
        case 3:
            showBusSummary();
            break;
        case 4: 
            restrictOrActivateCoach();
            break;
        case 5:
            cancelSeat();
            break;
        case 6: 
            restrictOrActivateUser();
            break;
        case 7:
            paymentDetail();
        case 8:
            //cancelSeat();
            myBookedSeat();
            break;    
        case 9:
            updateOwnProfile();
            break;
        case 10:
            logout();
            break;
        case 0:
            ifExit();
            break;
        default:
            printf(BHRED "\n\nSomething went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            executiveMenu();
    }
}

//ADMIN MENU

void adminMenu() {
    busAnimation();
    system("cls");
    welcomeMsg();
    printf(WHTHB BHBLK "\n             Admin Menu             \n" COLOR_RESET);
    printf(HBLK "         [Choose an option] \n\n");
    printf(BHCYN "  1. Search Bus\n");
    printf("  2. View Bus Schedule\n\n");

    printf(BHYEL "  Exclusive Admin Features: \n");
    printf(BHCYN "  3. Add New Bus & Route\n");
    printf("  4. Update Bus & Route\n");
    printf("  5. Activate or Inactivate Bus\n");
    printf("  6. Show System Summary\n");
    printf("  7. Cancel any Seat\n");
    printf("  8. Create new Profiles\n");
    printf("  9. Update other Profiles\n");
    printf("  10. Restrict or Activate Users\n");
    printf("  11. Customer Massages\n");
    printf("  12. View Payment Details\n\n");
    printf(BHRED "  13. Enable Maintenance Mode\n\n");
    printf(BHCYN "  14. Update Own Profile\n");
    printf("  15. Logout " COLOR_RESET "(Logged as %s)\n\n", id[$myUserId-1].userName);
    printf(BHRED "         [0] Exit\n\n" COLOR_RESET);

    printf(BHYEL "\n  Choose an option: " COLOR_RESET);

    int n;
    scanf("%d", &n);

    switch(n) {
        case 1: 
            searchBus();
            break;
        case 2: 
            busSchedule();
            break;
        case 3:
            setBusSchedule();
            break;
        case 4:
            updateBusScedule();
            break;
        case 5:
            restrictOrActivateCoach();
            break;
        case 6:
            showBusSummary();
            break;
        case 7:
            cancelSeat();
            break;
        case 8:
            createNewProfiles();
            break;
        case 9:
            updateOtherProfiles();
            break;
        case 10:
            restrictOrActivateUser();
            break;
        case 11:
            getMsg();
            break;
        case 12:
            paymentDetail();
            break;
        case 13:
            system("cls");
            int x;
            printf("\n\n\n\t\t\tYou are trying to enter maintenace mode.\n");
            printf("\t\t\tOnly Developers can come back to regualr mode.\n\n");
            printf("Are you sure?\n");
            printf("1. No\n");
            printf("2. Yes\n\n");
            printf("Enter your choice: \n");
            scanf("%d", &x);
            if(x != 2) {
                returnToMenu();
                return;
            }
            maintenance = 1;
            UpdateMaintenanceData();
            maintenanceMode();
            return;
        case 14:
            updateOwnProfile();
            break;
        case 15:
            logout();
            break;
        case 0:
            ifExit();
            break;
        default:
            printf(BHRED "\n\n   Something went wrong, plz try again!\n\n" COLOR_RESET);
            system("pause");
            adminMenu();
    }
}

void setBusSchedule() {
    busAnimation();
    system("cls");
    busLogo();
    printf(WHTHB BHBLK "\n             Create Bus Schedule             \n" COLOR_RESET);
    char ctemp;

    allBusList();

    printf(BHWHT"\n\nADD NEW BUS \n\n" COLOR_RESET);

    countCoach++;
    printf(BHCYN "\n  Bus Name: " COLOR_RESET);
    scanf("%c", &ctemp);
    scanf("%[^\n]", coach[countCoach-1].busName);
    printf(BHCYN "  Boarding Point: " COLOR_RESET);
    scanf("%s", coach[countCoach-1].boardingPoint);
    printf(BHCYN "  Dropping Point: " COLOR_RESET);
    scanf("%s", coach[countCoach-1].droppingPoint);
    printf(BHCYN "  Boarding Time: " COLOR_RESET);
    scanf("%c", &ctemp);
    scanf("%[^\n]", coach[countCoach-1].boardingTime);

    bool p;
    do {      
        printf(BHCYN "  Seat Number (41,45,49,53,57): " COLOR_RESET);
        scanf("%d", &coach[countCoach-1].seatNumber);

        if(coach[countCoach-1].seatNumber == 41 || coach[countCoach-1].seatNumber == 45 || coach[countCoach-1].seatNumber == 49 || coach[countCoach-1].seatNumber == 53 || coach[countCoach-1].seatNumber == 57) {
            p = 1;
        } else {
            p = 0;
            printf(BHRED "\n  Seat number doesn't match with our bus requirements.\n\n" COLOR_RESET);
        }
    } while (p != 1);

    printf(BHCYN "  Coach Type (1 for ac, 0 for non ac): " COLOR_RESET);
    scanf("%d", &coach[countCoach-1].coachType);
    printf(BHCYN "  Ticket Price: " COLOR_RESET);
    scanf("%d", &coach[countCoach-1].ticketPrice);
    coach[countCoach-1].coachId = countCoach;
    coach[countCoach-1].coachStatus = 1;
    for(int i=0; i<60; i++) {
        coach[countCoach-1].seatList[i] = 0;
    }
    coach[countCoach-1].coachId = countCoach;
    for(int i=0; i<60; i++) {
        coach[countCoach-1].seatHG[i] = 0;
    }
    printf(BHYEL "\n  New bus and route has been inserted...\n\n" COLOR_RESET);
    system("pause");
    system("cls");
    appendBusData();
    returnToMenu();
}

void updateBusScedule() {
    busAnimation();
    system("cls");
    busLogo();
    printf(WHTHB BHBLK "\n             Update Bus Schedule             \n" COLOR_RESET);
    char ctemp;

    printf("\n\nWe have total %d buses available now.\n", countCoach-1);
    printf("You can update, evaluate or manupulate each bus data!\n\n");

    printf("Our  buses with CoachID:\n");

    printf("Bus name        Bus ID\t");
    printf("Bus name        Bus ID\n");
    for(int i=0; i<countCoach; i++) {
        printf("%-15s (%d)\t", coach[i].busName, i+1);
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");
    int n;
    do {
        printf("Do you want to change any bus detail?\n");
        printf("1. Yes\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        switch(n) {
            case 1:
                break;
            case 2: 
                returnToMenu();
                return;
            default: 
                printf("Wrong Input!\n");
                system("pause");
                updateBusScedule();
                return;
        }
    } while(n != 1 && n != 2);

    int m;
    do {
        printf("\nEnter the bus ID your want to update: ");
        scanf("%d", &m);
        if(m-1<0 || m-1>countCoach-1) {
            printf("There is no bus wiht this ID!\n");
            printf("Try Again.\n");
        }
    } while (m-1<0 || m-1>countCoach-1);

    printf("\n\nYour choosen bus's info:\n");
    printf("1. Bus name:           %s\n", coach[m-1].busName);
    printf("2. Boarding Point:     %s\n", coach[m-1].boardingPoint);
    printf("3. Dropping Point:     %s\n", coach[m-1].droppingPoint);
    printf("4. Boarding time:      %s\n", coach[m-1].boardingTime);
    printf("5. Seat Number:        %d\n", coach[m-1].seatNumber);
    printf("6. Coach Type:         %s\n", showCoachType(coach[m-1].coachType));
    printf("7. Ticket price:       %d tk\n\n", coach[m-1].ticketPrice);
    printf("Bus Status:       %s\n\n", showCoachStatus(coach[m-1].coachStatus));
    
    printf("[0] to go back to Main Manu\n\n");

    int x;
    do {
        printf("  What you Want to change?\n");
        printf("(Enter '8' If you have Done)\n\n");
        printf("Enter your choice: ");
        scanf("%d", &x);
        switch(x) {
            case 1:
                printf("New bus name: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", coach[m-1].busName);
                printf("Bus name has been changed!\n");
                break;
            case 2: 
                printf("New Boarding Point: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", coach[m-1].boardingPoint);
                printf("Boarding Point has been changed!\n");
                break;
            case 3:
                printf("New Dropping Point: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", coach[m-1].droppingPoint);
                printf("Dropping Point has been changed!\n\n"); 
                break;
            case 4: 
                printf("New Boarding Time: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", coach[m-1].boardingTime);
                printf("Boarding Time has been changed!\n\n"); 
                break;
            case 5:
                bool p;
                do {      
                    printf(BHCYN "Seat Number (41,45,49,53,57): " COLOR_RESET);
                    scanf("%d", &coach[m-1].seatNumber);

                    if(coach[m-1].seatNumber == 41 || coach[m-1].seatNumber == 45 || coach[m-1].seatNumber == 49 || coach[m-1].seatNumber == 53 || coach[m-1].seatNumber == 57) {
                    p = 1;
                    }  else {
                        p = 0;
                        printf(BHRED "\n  Seat number doesn't match with our bus requirements.\n\n" COLOR_RESET);
                    }
                } while (p != 1);

                printf("Seat Number has been changed!\n\n"); 
                break;
            case 6: 
                printf("New Coach Type: ");
                scanf("%d", &coach[m-1].coachType);
                printf("Coach Type has been changed!\n\n"); 
                break;
            case 7:
                printf("New Ticket Price: ");
                scanf("%d", &coach[m-1].ticketPrice);
                printf("Ticket Price has been changed!\n\n");  
                break;
            case 0:
                returnToMenu();
                return;
            case 8:
                break;
            default:
                printf("Wrong Input!\n");
                break; 
        }
    } while (x != 8 && x != 0);
    UpdateStoredBusData();
    
    printf(BHWHT "\nUpdated Bus Data:\n" COLOR_RESET);
        printf("1. Bus name:           %s\n", coach[m-1].busName);
    printf("2. Boarding Point:     %s\n", coach[m-1].boardingPoint);
    printf("3. Dropping Point:     %s\n", coach[m-1].droppingPoint);
    printf("4. Boarding time:      %s\n", coach[m-1].boardingTime);
    printf("5. Seat Number:        %d\n", coach[m-1].seatNumber);
    printf("6. Coach Type:         %s\n", showCoachType(coach[m-1].coachType));
    printf("7. Ticket price:       %d tk\n\n", coach[m-1].ticketPrice);
    printf("Bus Status:       %s\n\n", showCoachStatus(coach[m-1].coachStatus));
    system("pause");
    updateBusScedule();

}

void updateBusTicket() {

}

void showBusSummary() {
    busAnimation();
    system("cls");
    printf("\n\n\n         ");
    printf(WHTHB BHBLK"                 Bus Summary                 " COLOR_RESET);
    printf("\n\n\n");
    allBusSum();
} 

void createNewProfiles() {
    busAnimation();
    system("cls");
    char currName[20];
    char ctemp;
    bool nameMatching;
    printf(WHTHB BHBLK "             Create New Profiles            \n" COLOR_RESET);
    printf(HBLK"       [Admin can create profiles as he want]\n\n");
    countUser++;
    printf(BHCYN "Fullname: " COLOR_RESET);
    scanf("%c", &ctemp);
    scanf("%[^\n]", id[countUser-1].fullName);

    do{
        printf(BHCYN "Username (no space allowed): " COLOR_RESET);
        scanf("%s", currName);
        for(int i = 0; i < countUser; i++) {
            nameMatching = strcmp(currName, id[i].userName);

            if(nameMatching == 0){
                printf(BHRED "\n\n  Username isn't available!\n       Try Another one.\n\n" COLOR_RESET); 
                system("pause"); 
                break;          
            }
        }
    } while(nameMatching == 0);

    strcpy(id[countUser-1].userName, currName);
    printf(BHGRN "Username is available.\n" COLOR_RESET);
    printf(BHCYN "Password: " COLOR_RESET);
    scanf("%s", id[countUser-1].userPass);
    printf(BHCYN "Gender (0 for men, 1 for women): " COLOR_RESET);
    scanf("%d", &id[countUser-1].userGender);
    printf(BHCYN "Age: " COLOR_RESET);
    scanf("%d", &id[countUser-1].userAge);
    printf("\nHints:\n");
    printf("User Role 1 means Customer\n");
    printf("User Role 2 means Executive\n");
    printf("User Role 3 means Admin\n\n");
    printf(BHCYN "User Role: " COLOR_RESET);
    scanf("%d", &id[countUser-1].userRole);

    id[countUser-1].userStatus = 1;
    id[countUser-1].userId = countUser;
    appendUserData();

    printf("\n\n");
    system("pause");
    system("cls");
    printf(BHGRN "\nAccount has been created!\n\n" COLOR_RESET);
    printf(BHYEL "New User Informations: \n");
    printf(BHCYN "Full name: %s \n", id[countUser-1].fullName);
    printf("Username: %s \n", id[countUser-1].userName);
    printf("Password: %s \n", id[countUser-1].userPass);
    printf("Gender: %s \n", showGender(id[countUser-1].userGender));
    printf("Age: %d \n", id[countUser-1].userAge);
    printf("Role: %s \n", showRole(id[countUser-1].userRole));
    printf("User ID: %d \n\n" COLOR_RESET, id[countUser-1].userId);

    int p;
    do{
        printf("\nNow what?\n");
        printf("1. Create more accounts\n");
        printf("2. Main Menu\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &p);
        switch(p) {
            case 1:
                createNewProfiles();
                break;
            case 2:
                returnToMenu();
                break;
            case 3: 
                logout();
                break;
            default: 
                printf("Wrong Choice!\n");
                break;
        }
    } while(p != 1 && p != 2 && p != 3);
} 

void updateOtherProfiles() {
    busAnimation();
    system("cls");
    char ctemp;
    printf("Update Other Profiles\n");
    allUserList();

    int n;
    do {
        printf("Do you want to change any bus detail?\n");
        printf("1. Yes\n");
        printf("2. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &n);
        switch(n) {
            case 1:
                break;
            case 2: 
                returnToMenu();
                return;
            default: 
                printf("Wrong Input!\n");
                system("pause");
                updateOtherProfiles();
                return;
        }
    } while(n != 1 && n != 2);

    int m;
    do {
        printf("\nEnter the user ID your want to update: ");
        scanf("%d", &m);
        if(m-1<0 || m-1>countUser-1) {
            printf("There is no user with this ID!\n");
            printf("Try Again.\n");
        }
    } while (m-1<0 || m-1>countUser-1);

    printf("\n\nYour choosen user's info:\n");
    printf("1. Fullname\n");
    printf("2. Username\n");
    printf("3. User Password\n");
    printf("4. User Gender\n");
    printf("5. User Age\n");
    printf("6. User Role\n\n");
    printf("[0] to go back to Main Manu\n\n");

    int x;
    do {
        printf("  What you Want to change?\n");
        printf("(Enter '7' If you have Done)\n\n");
        printf("Enter your choice: ");
        scanf("%d", &x);
        switch(x) {
            case 1:
                printf("New fullname: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", id[m-1].fullName);
                printf("Fullname has been changed!\n");
                break;
            case 2: 
                printf("New username: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", id[m-1].userName);
                printf("Username has been changed!\n");
                break;
            case 3:
                printf("New userpass: ");
                scanf("%c", &ctemp); 
                scanf("%[^\n]", id[m-1].userPass);
                printf("Password has been changed!\n\n"); 
                break;
            case 4:
                printf("New user gender: ");
                scanf("%d", &id[m-1].userGender);
                printf("Gender has been changed!\n\n"); 
                break;
            case 5: 
                printf("New user Age: ");
                scanf("%d", &id[m-1].userAge);
                printf("Role has been changed!\n\n"); 
                break;
            case 6: 
                printf("New user Role: ");
                scanf("%d", &id[m-1].userRole);
                printf("Role has been changed!\n\n"); 
                break;
            case 0:
                returnToMenu();
                return;
            case 7:
                break;
            default:
                printf("Wrong Input!\n");
                break; 
        }
    } while (x != 7 && x != 0);
    UpdateStoredUserData();
    system("pause");
    updateOtherProfiles();
}

void restrictOrActivateUser() {
    busAnimation();
    system("cls");
    printf("\n\n\n");
    printf("                        ");
    printf(WHTHB BHBLK"            Restrict or Activate User Accounts         " COLOR_RESET);
    printf("\n\n");
    printf(BHYEL"\n      All users with user ID:\n\n"COLOR_RESET);
    printf("   "BLKB" UserID "COLOR_RESET"\t "BLKB" Username "reset"\t     "BLKB" Status "reset"\t");
    printf("  "BLKB" UserID "reset"\t    "BLKB" Username "reset" \t   "BLKB" Status "reset"\n" COLOR_RESET);
    for(int i=0; i<countUser; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", id[i].userId, id[i].userName, showUserStatus(id[i].userStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");

    int n;
    int m;
    int p;

    do{
        printf(BHCYN "Choose an option\n");
        printf(BHWHT "1. Restrict an active user\n");
        printf("2. Activate a restricted user \n");
        printf("3. Return to Menu \n\n");
        printf(BHYEL "Enter your choice: " COLOR_RESET);
        scanf("%d", &n);
        if(n == 1) {
            printf(BHWHT "Enter the user id to restrict: ");
            scanf("%d", &m);
            if(m<1 || m>countUser) {
                printf(BHRED "Invalid ID Number!\n\n");
                system("pause");
                restrictOrActivateUser();
                return;
            }
            if(id[m-1].userStatus == 0) {
                printf(BHRED "The user is already restricted!\n\n");
                system("pause");
                restrictOrActivateUser();
                return;
            } 
            id[m-1].userStatus = 0;
            UpdateStoredUserData();
            printf("\n\n\n");
    printf("                        ");
    printf(WHTHB BHBLK"            Restrict or Activate User Accounts         " COLOR_RESET);
    printf("\n\n");
    printf(BHYEL"\n      All users with user ID:\n\n"COLOR_RESET);
    printf("  "BLKB" UserID "COLOR_RESET"\t     "BLKB" Username "reset"\t      "BLKB" Status "reset"\t");
    printf("  "BLKB" UserID "reset"\t     "BLKB" Username "reset" \t      "BLKB" Status "reset"\n" COLOR_RESET);
    for(int i=0; i<countUser; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", id[i].userId, id[i].userName, showUserStatus(id[i].userStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");
            
            printf("\n\n" BHYEL "%s " BHWHT "has been Restricted!\n", id[m-1].fullName);
            printf(BHWHT "The user will not be able to login or buy a seat anymore!\n\n" COLOR_RESET);

        } else if(n == 2) {
            printf(BHWHT "Enter the user id to activate: " COLOR_RESET);
            scanf("%d", &p);
            if(p<1 || p>countUser) {
                printf(BHRED "Invalid ID Number!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateUser();
                return;
            }
            if(id[p-1].userStatus == 1) {
                printf(BHYEL "The user is already activated!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateUser();
                return;
            } 
            id[p-1].userStatus = 1;
            UpdateStoredUserData();
            system("cls"); 
            printf("\n\n\n");
    printf("                        ");
    printf(WHTHB BHBLK"            Restrict or Activate User Accounts         " COLOR_RESET);
    printf("\n\n");
    printf(BHYEL"\n      All users with user ID:\n\n"COLOR_RESET);
    printf(BHWHT "      UserID\t   Username\t       Status\t");
    printf("      UserID\t   Username\t       Status\n" COLOR_RESET);
    for(int i=0; i<countUser; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", id[i].userId, id[i].userName, showUserStatus(id[i].userStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");
            printf("\n\n" BHYEL "%s " BHWHT "has been Activated!\n", id[p-1].fullName);
            printf(BHWHT "The user will be able to login and buy a seat now!\n\n" COLOR_RESET);

        } else if (n == 3) {
            returnToMenu();
            return;
        } else {
            printf(BHRED "\n\nWrong Insertion.\n");
            printf(BHYEL "Try Again.\n\n");
        }
    } while (n!=1 && n!=2 && n!=3);
    system("pause");
    restrictOrActivateUser();
}

void restrictOrActivateCoach() {
    busAnimation();
    system("cls");
    printf("\n\n\n");
    printf("                             ");
    printf(WHTHB BHBLK"            Restrict or Activate a Bus            " COLOR_RESET);
    printf("\n\n");
    
    printf(BHYEL"\n      Our  buses with CoachID:\n\n"COLOR_RESET);
    printf(BHWHT "      BusID\t   Bus name\t       Status\t");
    printf("      BusID\t   Bus name\t       Status\n" COLOR_RESET);
    for(int i=0; i<countCoach; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", coach[i].coachId, coach[i].busName, showCoachStatus(coach[i].coachStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");

    int n;
    int m;
    int p;

    do{
        printf(BHCYN "Choose an option\n");
        printf(BHWHT "1. Restrict an active Bus\n");
        printf("2. Activate an Inactive Bus \n");
        printf("3. Return to Menu \n\n");
        printf(BHYEL"Enter your choice: " COLOR_RESET);
        scanf("%d", &n);
        if(n == 1) {
            printf(BHWHT "\nEnter the coach id to restrict: " COLOR_RESET);
            scanf("%d", &m);
            if(m<1 || m>countCoach) {
                printf(BHRED "Invalid Coach ID!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateCoach();
                return;
            }
            if(coach[m-1].coachStatus == 0) {
                printf(BHYEL "The Bus is already restricted!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateCoach();
                return;
            } 
            coach[m-1].coachStatus = 0;
            UpdateStoredBusData();
            system("cls"); 
            printf("\n\n\n");
            printf("                              ");
            printf(WHTHB BHBLK"            Restrict or Activate a Bus            " COLOR_RESET);
            printf("\n\n");
            printf(BHWHT "      BusID\t   Bus name\t       Status\t");
    printf("      BusID\t   Bus name\t       Status\n" COLOR_RESET);
    for(int i=0; i<countCoach; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", coach[i].coachId, coach[i].busName, showCoachStatus(coach[i].coachStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");

            printf("\n\n" BHYEL "%s " BHWHT "bus has been Restricted!\n", coach[m-1].busName);
            printf(BHWHT "User will not be able to buy any ticket from this bus!\n\n" COLOR_RESET);

        } else if(n == 2) {
            printf(BHWHT "Enter the Coach id to reactivate: " COLOR_RESET);
            scanf("%d", &p);
            if(p<1 || p>countCoach) {
                printf(BHRED "Invalid CoachId!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateCoach();
                return;
            }
            if(coach[p-1].coachStatus == 1) {
                printf(BHYEL "The bus is already activated!\n\n" COLOR_RESET);
                system("pause");
                restrictOrActivateCoach();
                return;
            } 
            coach[p-1].coachStatus = 1;
            UpdateStoredBusData();
            system("cls"); 
            printf("\n\n\n");
            printf("                              ");
    printf(WHTHB BHBLK"            Restrict or Activate a Bus            " COLOR_RESET);
    printf("\n\n");
            printf(BHWHT "      BusID\t   Bus name\t       Status\t");
    printf("      BusID\t   Bus name\t       Status\n" COLOR_RESET);
    for(int i=0; i<countCoach; i++) {
        printf(BHWHT "      %-12d" COLOR_RESET " %-18s %-18s\t", coach[i].coachId, coach[i].busName, showCoachStatus(coach[i].coachStatus));
        if((i+1)%2==0) {
            printf("\n");
        }
    }
    printf("\n\n");
            printf("\n\n" BHYEL "%s " BHWHT "bus has been Activated!\n", coach[p-1].busName);
            printf(BHWHT "Users will be able to buy any seat from this bus now!\n\n" COLOR_RESET);

        } else if (n == 3) {
            returnToMenu();
            return;
        } else {
            printf("\n\nWrong Insertion.\n");
            printf("Try Again.\n\n");
        }
    } while (n!=1 && n!=2 && n!=3);
    system("pause");
    restrictOrActivateCoach();
}


void ifExit() {
    busAnimation();
    system("cls");
    printf( BHGRN "\n\n\n       Have a good Day, TaTa!\n\n\n" COLOR_RESET);
    system("pause");
    system("cls");
    exit(0);
}

void returnToMenu() {
    if($myUserId == 0) {
        nonLogged_Menu();
        return;
    } else {
        if(id[$myUserId-1].userRole == 1) {
            customerMenu();
            return;
        } else if(id[$myUserId-1].userRole == 2) {
            executiveMenu();
            return;
        } else if(id[$myUserId-1].userRole == 3){
            adminMenu();
            return;
        }
    }
}

const char* showGender(bool gender) {
    if(gender == 1) {
        return "Female";
    } else if(gender == 0) {
        return "Male";
    } else {
        return "Undefined";
    }
}

const char* showUserStatus(bool status) {
    if(status == 1) {
        return "\e[1;92mActive\e[0m";
    } else if(status == 0) {
        return "\e[1;91mRestricted\e[0m";
    } else {
        return "Corrupted";
    }
}

const char* showCoachStatus(bool status) {
    if(status == 1) {
        return "\e[1;92mActive\e[0m";
    } else if(status == 0) {
        return "\e[1;91mInactive\e[0m";
    } else {
        return "Corrupted";
    }
}

const char* showRole(int role) {
    if(role == 3) {
        return "Admin";
    } else if(role == 2) {
        return "Executive";
    } else if(role == 1){
        return "Customer";
    }
}

const char* showCoachType(bool icoachType) {
    if(icoachType == 1) {
        return "AC";
    } else {
        return "Non AC";
    }
}

const char* showSeatStatus(int iseatStatus) {
    if(iseatStatus == 0) {
        return "\e[0;37mEmpty\033[1;0m";
    } else if(iseatStatus == -1){
        return "\e[1;92mPending\e[0m";
    } else if(iseatStatus == 1){
        return "\e[1;94mMale\e[0m";
    } else if(iseatStatus == 2){
        return "\e[1;95mFemale\033[1;0m";
    }
}

const char* showPaymentVia(int via) {
    if(via == 1) {
        return "\e[1;94mVisa\e[0m";
    } else if(via == 2) {
        return "\e[1;96mMaster Card\e[0m";
    } else if(via == 3) {
        return "\e[1;92mBDBL\e[0m";
    } else if(via == 4) {
        return "\e[1;91mPaypal\e[0m";
    } else if(via == 6) {
        return "\e[1;92mNagad\e[0m";
    } else if(via == 7) {
        return "\e[1;91mbKash\e[0m";
    } else if(via == 8) {
        return "\e[1;96mDutch Bangla\e[0m";
    } else {
        return "Undefined";
    }
}

void ourBranches() {
    system("cls");
    int n;
    do {
        printf("== Our Branches ==\n\n");
        printf("1. Dhaka\n");
        printf("2. Sylhet\n");
        printf("3. Chattogram\n");
        printf("4. Rajshahi\n");
        printf("5. Narail\n");
        printf(BHRED "[0] Exit\n" COLOR_RESET);

        printf("\nChoose an option: ");
        scanf("%d", &n);

        switch(n) {
            case 1: 
                system("cls");
                printf("== Dhaka ==\n\n");
                printf("Gabtoli\n");
                printf("Address: Inter District Bus Terminal, Gabtoli, Mirpur\n");
                printf("Call: 017**\n\n");

                printf("Abdullahpur\n");
                printf("Address: Address : 7/D,H#20, Sec# 9 ,Uttara\n");
                printf("Call: 018**\n\n");

                printf("kalyanpur\n");
                printf("Address: 3/1-KA, South Kallyanpur\n");
                printf("Call: 019**\n\n");
                break;
            case 2: 
                system("cls");
                printf("== Sylhet ==\n\n");
                printf("Rajib Chattor\n");
                printf("Address:3/4 Rio Complex, Rajib Chattor\n");
                printf("Call: 015**\n\n");

                printf("Oishi Zaman City Road\n");
                printf("Address:3/4 OR Complex, Oishi Zaman City Road\n");
                printf("Call: 015**\n\n");
                break;
            case 3: 
                system("cls");
                printf("== Chattogram ==\n\n");
                printf("Dampara CMP\n");
                printf("Address:167/1 Eden Complex, Dampara CMP\n");
                printf("Call: 014**\n\n");

                printf("Ashish Road\n");
                printf("Address:17/1 Mustari Complex, shawapara CMP\n");
                printf("Call: 014**\n");

                printf("== Rajshahi ==\n\n");
                printf("Raigate\n");
                printf("Address:191/2 C&B road\n");
                printf("Call: 019**\n\n");

                printf("Terminal Point\n");
                printf("Address:12/1 Mohila College Road Complex\n");
                printf("Call: 019**\n");
                break;
            case 4: 
                system("cls");
                printf("== Rajshahi ==\n\n");
                printf("Boalia\n");
                printf("Address: Zero Point, Shaheb Bazar\n");
                printf("Call: 017**\n\n");
                
                printf("Rajpara\n");
                printf("Address: Thanar Mor, Chandipur\n");
                printf("Call: 017**\n");
                break;
            case 5: 
                system("cls");
                printf("== Narail ==\n\n");
                printf("Jessore Road\n");
                printf("Address:9/11 C&B Road\n");
                printf("Call: 017**\n\n");

                printf("Muchir Pole\n");
                printf("Address:12/1 NGVC Road, Muchir Pole\n");
                printf("Call: 019**\n");
                break;
            case 0: 
                returnToMenu();
                break;
            default: 
                printf("Wrong choice!\n\n");
                break;
        } 
    }while (true);
}

void AboutUs() {
    system("cls");
    printf("\n\n\n          ");
    printf(WHTB BHBLK "            About Us             " reset);
    printf("\n\n\n");
    printf(BHWHT "This website is designed By\n"reset);
    printf(BHYEL "S. M. Hasib Hasnain\n" reset);
    printf(BHRED "CEO, Durnibar IT\n\n\n\n" reset);
    system("pause");
    returnToMenu();

}

void userManual() {
    system("cls");
    printf("\n\n\n");
    printf(BLKB"            User Manual             " reset);
    printf("\n\n\n");
    printf(BHWHT"Create two folders on the same place\nwhere is the"BHYEL" .exe file"BHWHT" named \n"BHGRN"Seat Data"BHWHT", "BHGRN"Seat HG Data\n\n" reset);
    printf(BHWHT"Default Admin Account\n");
    printf(BHCYN"Username: admin\n");
    printf(BHCYN"UserPass: pass\n"reset);
    printf("\n\n\n\n");
    system("pause");
    returnToMenu();
}


void storeDefaultUserData(){
    allUserData = fopen("userdata.txt", "r");
    if(allUserData == NULL) {
        allUserData = fopen("userdata.txt", "w");
        for(int i=0; i<countUser; i++) {
            fprintf(allUserData, "%s,%s,%s,%d,%d,%d,%d,%d\n", id[i].fullName, id[i].userName, id[i].userPass, id[i].userGender, id[i].userAge, id[i].userRole, id[i].userId, id[i].userStatus);
        }
    } 
    fclose(allUserData);
}

void storeDefaultBusData(){
    allBusData = fopen("busdata.txt", "r");
    if(allBusData == NULL) {
        allBusData = fopen("busdata.txt", "w");
        for(int i=0; i<countCoach; i++) {
            fprintf(allBusData, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n", coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, coach[i].seatNumber, coach[i].coachType, coach[i].ticketPrice, coach[i].coachId, coach[i].coachStatus);
        }
    } 
    fclose(allBusData);
    storeDefaultBusSeatData();
    storeDefaultBusSeatHGData();
}

void storeDefaultBusSeatData(){
    FILE* allBusSeatData[countCoach];
    char folderName[30] = "Seat Data";
    char filePath[256]; 

    for (int i = 0; i < countCoach; i++) {
        strcpy(filePath, folderName);
        strcat(filePath, "/");
        strcat(filePath, coach[i].busName);
        strcat(filePath, ".txt");
        //printf("Attempting to open file: %s\n", filePath); 
        allBusSeatData[i] = fopen(filePath, "r");
        if(allBusSeatData[i] == NULL) {
            allBusSeatData[i] = fopen(filePath, "w");
            if(allBusSeatData[i] == NULL) {
                perror("Error opening file for writing");
                continue; 
            }
            for (int j = 0; j < coach[i].seatNumber; j++) {
                fprintf(allBusSeatData[i], "%d,", coach[i].seatList[j]); 
            }
        } else {
            //printf("File already exists: %s\n", filePath);
        }
        fclose(allBusSeatData[i]);
    }
}

void storeDefaultBusSeatHGData(){
    FILE* allBusSeatHGData[countCoach];
    char folderName[30] = "Seat HG Data";
    char filePath[256]; 

    for (int i = 0; i < countCoach; i++) {
        strcpy(filePath, folderName);
        strcat(filePath, "/");
        strcat(filePath, coach[i].busName);
        strcat(filePath, ".txt");
        //printf("Attempting to open file: %s\n", filePath); 
        allBusSeatHGData[i] = fopen(filePath, "r");
        if(allBusSeatHGData[i] == NULL) {
            allBusSeatHGData[i] = fopen(filePath, "w");
            if(allBusSeatHGData[i] == NULL) {
                perror("Error opening file for writing");
                continue; 
            }
            for (int j = 0; j < coach[i].seatNumber; j++) {
                fprintf(allBusSeatHGData[i], "%d,", coach[i].seatHG[j]); 
            }
        } else {
            //printf("File already exists: %s\n", filePath);
        }
        fclose(allBusSeatHGData[i]);
    }
}

void UpdateStoredUserData(){
    allUserData = fopen("userdata.txt", "w");
    for(int i=0; i<countUser; i++) {
        fprintf(allUserData, "%s,%s,%s,%d,%d,%d,%d,%d\n", id[i].fullName, id[i].userName, id[i].userPass, id[i].userGender, id[i].userAge, id[i].userRole, id[i].userId, id[i].userStatus);
    }
    fclose(allUserData);
}

void UpdateStoredBusData() {
    allBusData = fopen("busdata.txt", "w");
    for(int i=0; i<countCoach; i++) {
        fprintf(allBusData, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n", coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, coach[i].seatNumber, coach[i].coachType, coach[i].ticketPrice, coach[i].coachId, coach[i].coachStatus);
    }
     
    fclose(allBusData);
}

void UpdateStoredBusSeatData(int exactBusId, int exactSeatNum){
    FILE* allBusSeatData[countCoach];
    char folderName[30] = "Seat Data";
    char filePath[256]; 

    strcpy(filePath, folderName);
    strcat(filePath, "/");
    strcat(filePath, coach[exactBusId-1].busName);
    strcat(filePath, ".txt");
    allBusSeatData[exactBusId-1] = fopen(filePath, "w");
    for (int j = 0; j < coach[exactBusId-1].seatNumber; j++) {
        if(exactSeatNum-1 == j) {
            fprintf(allBusSeatData[exactBusId-1], "%d,", coach[exactBusId-1].seatList[exactSeatNum-1]); 
            continue;
        }
        fprintf(allBusSeatData[exactBusId-1], "%d,", coach[exactBusId-1].seatList[j]); 
    }
    fclose(allBusSeatData[exactBusId-1]); 
}

void UpdateStoredBusSeatHGData(int exactBusId, int exactSeatNum){
    FILE* allBusSeatHGData[countCoach];
    char folderName[30] = "Seat HG Data";
    char filePath[256]; 

    strcpy(filePath, folderName);
    strcat(filePath, "/");
    strcat(filePath, coach[exactBusId-1].busName);
    strcat(filePath, ".txt");
    allBusSeatHGData[exactBusId-1] = fopen(filePath, "w");
    for (int j = 0; j < coach[exactBusId-1].seatNumber; j++) {
        if(exactSeatNum-1 == j) {
            fprintf(allBusSeatHGData[exactBusId-1], "%d,", coach[exactBusId-1].seatHG[exactSeatNum-1]); 
            continue;
        }
        fprintf(allBusSeatHGData[exactBusId-1], "%d,", coach[exactBusId-1].seatHG[j]); 
    }
    fclose(allBusSeatHGData[exactBusId-1]); 
}


void scanUserData() {
    allUserData = fopen("userdata.txt", "r");
    int i = 0;
    char line[300];

    if(allUserData != NULL) {
        while(fgets(line, sizeof(line), allUserData) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",id[i].fullName,id[i].userName,id[i].userPass,&id[i].userGender,&id[i].userAge,&id[i].userRole,&id[i].userId,&id[i].userStatus);
        i++;
    }
    countUser = i++;
    fclose(allUserData);
}
}

void scanBusData() {
    allBusData = fopen("busdata.txt", "r");
    int i = 0;
    char line[300];

    if(allBusData != NULL) {
        while(fgets(line, sizeof(line), allBusData) != NULL) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, &coach[i].seatNumber, &coach[i].coachType, &coach[i].ticketPrice, &coach[i].coachId,&coach[i].coachStatus);
            i++;
        }
        countCoach = i++;
        fclose(allBusData);
        scanBusSeatData();
        scanBusSeatHGData();
    }
}

void scanBusSeatData() {
    FILE* allBusSeatData[countCoach];
    char folderName[30] = "Seat Data";
    char filePath[256]; 

    for (int i = 0; i < countCoach; i++) {
        strcpy(filePath, folderName);
        strcat(filePath, "/");
        strcat(filePath, coach[i].busName);
        strcat(filePath, ".txt");
        allBusSeatData[i] = fopen(filePath, "r");
        if(allBusSeatData[i] != NULL) {
            for (int j = 0; j < coach[i].seatNumber; j++) {
                fscanf(allBusSeatData[i], "%d,", &coach[i].seatList[j]); 
            }
        } else {
            printf("File %s is empty!\n", filePath);
        }
        fclose(allBusSeatData[i]);
    }
}

void scanBusSeatHGData() {
    FILE* allBusSeatHGData[countCoach];
    char folderName[30] = "Seat HG Data";
    char filePath[256]; 

    for (int i = 0; i < countCoach; i++) {
        strcpy(filePath, folderName);
        strcat(filePath, "/");
        strcat(filePath, coach[i].busName);
        strcat(filePath, ".txt");
        allBusSeatHGData[i] = fopen(filePath, "r");
        if(allBusSeatHGData[i] != NULL) {
            for (int j = 0; j < coach[i].seatNumber; j++) {
                fscanf(allBusSeatHGData[i], "%d,", &coach[i].seatHG[j]); 
            }
        } else {
            printf("File %s is empty!\n", filePath);
        }
        fclose(allBusSeatHGData[i]);
    }
}


void appendUserData(){
    allUserData = fopen("userdata.txt", "a");
    fprintf(allUserData, "%s,%s,%s,%d,%d,%d,%d,%d\n", id[countUser-1].fullName, id[countUser-1].userName, id[countUser-1].userPass, id[countUser-1].userGender, id[countUser-1].userAge, id[countUser-1].userRole, id[countUser-1].userId, id[countUser-1].userStatus);
    fclose(allUserData);
}

void appendBusData(){
    allBusData = fopen("busdata.txt", "a");
    fprintf(allBusData, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n", coach[countCoach-1].busName, coach[countCoach-1].boardingPoint, coach[countCoach-1].droppingPoint, coach[countCoach-1].boardingTime, coach[countCoach-1].seatNumber, coach[countCoach-1].coachType, coach[countCoach-1].ticketPrice, coach[countCoach-1].coachId, coach[countCoach-1].coachStatus);
    fclose(allBusData);
    appendBusSeatData();
    appendBusSeatHGData();
}

void appendBusSeatData() {
    storeDefaultBusSeatData();
}

void appendBusSeatHGData() {
    storeDefaultBusSeatHGData();
}

void storeDefaultMaintenanceData(){
    maintenanceData = fopen("maintenanceData.txt", "r");
    if(maintenanceData == NULL) {
        maintenanceData = fopen("maintenanceData.txt", "w");
        fprintf(maintenanceData, "%d", maintenance);
        fclose(maintenanceData);
    } 
    
}

void UpdateMaintenanceData(){
    maintenanceData = fopen("maintenanceData.txt", "w");
    fprintf(maintenanceData, "%d", maintenance);
    fclose(maintenanceData);
}

void ScanMaintenanceData(){
    maintenanceData = fopen("maintenanceData.txt", "r");
    fscanf(maintenanceData, "%d", &maintenance);
    // Close the file
    fclose(maintenanceData);
}

void tempuserlist(){
    printf("Usercount: %d\n", countUser);
    for(int i=0; i<countUser; i++) {
        printf("%s %s %s %d %d %d %d %d\n", id[i].fullName, id[i].userName, id[i].userPass, id[i].userGender, id[i].userAge, id[i].userRole, id[i].userId, id[i].userStatus);
}
system("pause");
nonLogged_Menu();
}



void allBusSum() {
    int allBusSum[countCoach];
    int totalTicketSold = 0;
    int totalActiveBus = 0;

    // Calculate bus rankings
    for(int i = 0; i < countCoach; i++) {
        allBusSum[i] = coach[i].seatNumber - availableSeat(i + 1);
        totalTicketSold += allBusSum[i];
        totalActiveBus++;
    }
    int n = 0;
    printf( BHWHT "Total ticket Sold: " BHYEL " %d\n\n", totalTicketSold);
    printf(BHWHT "Total Buses: "BHMAG" %d\n", countCoach);
    printf(BHCYN "   Active Buses: "BHGRN" %d\n", totalActiveBus);
    printf(BHCYN "   Inactive Buses: "BHRED" %d\n\n", countCoach-totalActiveBus);
    
    printf( BHWHT "Total Users: "BHMAG" %d\n", countUser);
    
    int x = 0;
    int y = 0;
    int z = 0;
    int t = 0;

    for(int i=0; i<countUser; i++) {
        if(id[i].userRole == 3) {
            x++;
        }
        if(id[i].userRole == 2) {
            y++;
        }
        if(id[i].userRole == 1) {
            z++;
        }
        if(id[i].userStatus == 0) {
            t++;
        }
    }
    printf(BHCYN"   Total Restricted Account: "BHRED" %d\n", t);
    printf(BHCYN"   Total Customer: "BHGRN" %d\n", z);
    printf(BHCYN"   Total Executive: "BHGRN" %d\n", y);
    printf(BHCYN"   Total Admin: "BHGRN" %d\n\n", x);
    

    if(totalTicketSold>0) {
        printf(BHWHT "Most Popular Buses: \n\n");
        printf(BLKB" BusID "reset"     "BLKB" Bus Name "COLOR_RESET"       "BLKB" Ticket Sold "COLOR_RESET"        "BLKB" Profit "reset"\n");
        for(int i = 0; i < countCoach; i++) {
            if(allBusSum[i] == 0) {
              continue;
            } else {
                printf("%-12d %-20s %-15d %dtk\n", i+1, coach[i].busName, allBusSum[i], allBusSum[i]*coach[i].ticketPrice);
            }
        }

    }

    int m;
    do{
        printf(BHWHT"\n\nNow what?\n"COLOR_RESET);
        printf(BHCYN"  1. Show bus wise ticket holders\n");
        printf("  2. Go back to main menu\n");
        printf("  0. Exit\n\n"reset);
        printf(BHYEL"Enter your choice: "reset);
        scanf("%d", &m);
        switch(m) {
            case 1:
                allTicketHolder();
                return;
            case 2:
                returnToMenu();
                return;
            case 0:
                ifExit();
                break;
            default:
                printf("Wrong choice!\n");
                system("pause\n");
                break;
        }
    } while(m<0 && m>2);
}


void allTicketHolder() {
    int n;
    printf(BHWHT"\nEnter BusID From the List: "reset);
    scanf("%d", &n);
    printf("\n\n");
    
    if(n>countCoach || n<1) {
        printf("Wrong Choice\n");
        system("pause");
        showBusSummary();
        return;
    }

    printf("     "UGRN"ALL TICKET HOLDER FOR %s BUS"reset"\n\n", coach[n-1].busName);

    int serial = 0;
    for(int j=0; j<coach[n-1].seatNumber; j++) {
        if(coach[n-1].seatList[j] != 0) {
            serial++;
            printf(MAGB " Ticket Serial: %d " COLOR_RESET, serial);
            printf("\nName: %s\n", id[coach[n-1].seatList[j]-1].fullName);
            printf("Role: %s\n", showRole(id[coach[n-1].seatList[j]-1].userRole));
            printf("Bus Name: %s\n", coach[n-1].busName);
            printf("Ticket Price: %d "BHGRN"(Paid)\n"COLOR_RESET, coach[n-1].ticketPrice);
            printf(CYN"Booked Seat Number: %d\n\n"COLOR_RESET, j+1);
        }
    }

    if(serial == 0) {
        printf(BHRED "\n      No seat holder on %s bus!\n\n"reset, coach[n-1].busName);
    }

    system("pause");
    showBusSummary();

}

void paymentMethod(int BusId, int exactSeatNum, int via) {
    int p;
    do {
        printf(BHRED "\nNeeded Amount: %d\n" COLOR_RESET, coach[BusId-1].ticketPrice);
        printf(BHWHT "1. Pay\n");
        printf("0. Back\n");
        printf(BHCYN "\nPut your dicision: " COLOR_RESET);
        scanf("%d", &p);
        if(p == 0) {
            paymentGateway(BusId, exactSeatNum);
        } else if(p == 1) {
            printf(BHYEL"\n%d has been paid!\n" COLOR_RESET, coach[BusId-1].ticketPrice);
            printf(BHGRN "Horray! Ticket has been booked!\n\n"COLOR_RESET);
                                
            totalMoney = totalMoney + coach[BusId-1].ticketPrice;
            coach[BusId-1].seatList[exactSeatNum] = $myUserId;
            coach[BusId-1].seatHG[exactSeatNum] = genderMatch;

            paymentData = fopen("paymentdata.txt", "a");
            fprintf(paymentData, "%s,%d,%d\n", id[$myUserId-1].userName, coach[BusId-1].ticketPrice, via);
            fclose(paymentData);

            status = 1;
            system("pause\n");
        }
                                
    } while(status != 1);
}

void sendMsg(){
    system("cls");
    printf(BLKB "\n\n\n  ");
    printf("CUSTOMER MASSEGE BOX                                                                                           \n"reset);
    int n;
    char temp;
    char fullmsg[280];
    printf(BHBLK "Send a short msg to admin\n"reset);
    printf(BHYEL"\nWrite here: "reset);
    scanf("%c", &temp);
    scanf("%[^\n]", fullmsg);
    msg = fopen("userMsg.txt", "a");
    fprintf(msg, "%d,%s\n", $myUserId-1, fullmsg);
    fclose(msg);
    printf(BHGRN"\n\nMassage has been sent!\n"reset);
    system("pause");
    returnToMenu();
}
void getMsg() {
    system("cls");
    printf(BLKB "\n\n\n  ");
    printf("ADMIN INBOX                                                                                                               \n"reset);
    printf(BHBLK "All messages are from customers\n\n"reset);
    
    int n;
    char fullmsg[280];
    char msgtime[100];
    msg = fopen("userMsg.txt", "r");
    int i = 0;
    char line[400];    
    while(fgets(line, sizeof(line), msg) != NULL) {
        sscanf(line, "%d, %[^\n]",&n, fullmsg);
        i++;
        printf(BHBLK "   @" BHMAG "%s" BHYEL " said:" BHWHT " %s\n\n" COLOR_RESET, id[n].userName, fullmsg);
    }
    fclose(msg);
    system("pause");
    returnToMenu();
} 

void allUserList() {
    printf("\n\nOur All Users: \n\n");
    printf( BHWHT "UserID  FullName           UserName   UserPass         UserAge       Role            Status\n" COLOR_RESET);
    for(int i=0; i<countUser; i++) {
        printf("%-7d %-18s %-10s %-16s %-13d %-15s %-10s\n", id[i].userId, id[i].fullName, id[i].userName, id[i].userPass, id[i].userAge, showRole(id[i].userRole), showUserStatus(id[i].userStatus));  
    }
    printf("\n\n");
}


void allBusList() {
    printf("\n\nOur All Buses: \n\n");
    printf( BHWHT "BusID   BusName            BoardingPoint      DroppingPoint     Time         Seat             CoachType     TicketPrice       Status\n" COLOR_RESET);
    for(int i=0; i<countCoach; i++) {
        printf("%-7d %-18s %-18s %-16s %-13s %-15d %-15s %-15d %-10s\n", coach[i].coachId, coach[i].busName, coach[i].boardingPoint, coach[i].droppingPoint, coach[i].boardingTime, coach[i].seatNumber, showCoachType(coach[i].coachType), coach[i].ticketPrice, showCoachStatus(coach[i].coachStatus));  
    }
    printf("\n\n");
}

void maintenanceMode() {
    system("cls");
    printf("\n\n\n\n\t\t\t\t");

printf(BHRED" SITE IS UNDER MAINTENANCE MODE \n");     
printf(BHYEL"\t\t\t\t       CONTACT WITH ADMIN \n\n\n\n" COLOR_RESET);     

    printf("\n\n\n");
    system("pause");
    return;
}

void paymentDetail() {
    system("cls");
    printf(WHTHB BHBLK "\n             Payment Detail             \n\n" COLOR_RESET);
    paymentData = fopen("paymentdata.txt", "r");
    int i = 0;
    char line[300];
    char x[30]; 
    int y, z;
    int totalPrice = 0;

    if(paymentData != NULL) {
        printf(UCYN "Payment Log: \n\n" COLOR_RESET);
        while(fgets(line, sizeof(line), paymentData) != NULL) {
            sscanf(line, "%[^,],%d,%d", x, &y, &z);
            printf( BHBLK "-> " BHMAG "@%s" BHWHT " completed payment " BHGRN "%d Taka " BHWHT " via %s.\n", x, y, showPaymentVia(z));
            i++;
            totalPrice = totalPrice + y;
        }
        printf( BHYEL "\n\n\tTotal Money Earned: %d Taka\n" COLOR_RESET, totalPrice);
        fclose(paymentData);
    } else {
        printf(BHRED "\n\n   Payment.txt isn't available!\n\n" COLOR_RESET);
    }
    printf("\n\n");
    system("pause");
    returnToMenu();
}