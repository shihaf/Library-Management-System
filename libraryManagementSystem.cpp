#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <iostream>

class Book;
class Student;

class Book
{
    char bno[6];
    char bname[50];
    char aname[20];
    
public:
    void create_book();
    void show_book() const;
    void modify_book();
    char* retbno();
    void report();
};

void Book::create_book()
{
    std::cout << "\nNEW BOOK ENTRY...\n";
    std::cout << "\nEnter The Book No.";
    std::cin >> bno;
    std::cout << "\n\nEnter The Name of Book ";
    std::cin.ignore();
    std::cin.getline(bname, 50);
    std::cout << "\n\nEnter The Author ";
    std::cin.getline(aname, 20);
    std::cout << "\n\n\nBook Created..";
}

void Book::show_book() const
{
    std::cout << "\nBook No. : " << bno;
    std::cout << "\nBook Name : " << bname;
    std::cout << "\nAuthor Name : " << aname;
    std::cin.get();
}

void Book::modify_book()
{
    std::cout << "\nBook No. : " << bno;
    std::cout << "\nModify Book Name : ";
    //??ignore???????cin input?????
    //????skip first letter
    //std::cin.ignore();
    std::cin.getline(bname, 50);
    std::cout << "\nModify Author's Name : ";
    std::cin.getline(aname, 20);
}

char* Book::retbno()
{
    return bno;
}

void Book::report()
{
    std::cout << bno << std::setw(35) << bname << std::setw(30) << aname << std::endl;
}

class Student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
    
public:
    void create_student();
    void show_student() const;
    void modify_student();
    char* retadmno();
    char* retstbno();
    int rettoken();
    void addtoken();
    void resettoken();
    void getstbno(char t[]);
    void report();
};

void Student::create_student()
{
    system("cls");
    std::cout << "\nNEW STUDENT ENTRY...\n";
    std::cout << "\nEnter The Admission No. ";
    std::cin >> admno;
    std::cout << "\n\nEnter The Name of The Student ";
    std::cin.ignore();
    std::cin.getline(name, 20);
    token = 0;
    stbno[0] = (char)0; // casting an int (integer) (0) to a character (char).
    std::cout << "\n\nStudent Record Created..";
}

void Student::show_student() const
{
    std::cout << "\nAdmission No. : " << admno;
    std::cout << "\nStudent Name : " << name;
    std::cout << "\nNo of Book issued : " << token;
    if (token == 1) {
        std::cout << "\nBook No " << stbno;
    }
}

void Student::modify_student()
{
    std::cout << "\nAdmission No. : " << admno;
    std::cout << "\nModify Student Name : ";
    std::cin.ignore();
    std::cin.getline(name, 20);
}

char* Student::retadmno()
{
    return admno;
}

char* Student::retstbno()
{
    return stbno;
}

int Student::rettoken()
{
    return token;
}

void Student::addtoken()
{
    token = 1;
}

void Student::resettoken()
{
    token = 0;
}

void Student::getstbno(char t[])
{
    strcpy(stbno, t);
}

void Student::report()
{
    std::cout << admno << std::setw(30) << name << std::setw(35) << token << std::endl;
}

void write_book();
void display_spb(char n[]);
void modify_book();
void delete_book();
void display_allb();
void book_issue();
void book_deposit();

void write_student();
void display_sps(char n[]);
void modify_student();
void delete_student();
void display_alls();

void intro();
void admin_menu();


int main(int argc, const char * argv[]) {
    char ch;
    intro();
    do
    {
        system("cls");
        std::cout<<"\n\n\n\tMAIN MENU";
        std::cout<<"\n\n\t01. BOOK ISSUE";
        std::cout<<"\n\n\t02. BOOK DEPOSIT";
        std::cout<<"\n\n\t03. ADMINISTRATOR MENU";
        std::cout<<"\n\n\t04. EXIT";
        std::cout<<"\n\n\tPlease Select Your Option (1-4) ";
        ch=std::cin.get();
        switch(ch)
        {
            case '1':system("cls");
                book_issue();
                break;
            case '2':book_deposit();
                break;
            case '3':admin_menu();
                break;
            case '4':exit(0);
            default :std::cout<<"\a";
        }
    }while(ch!='4');
    return 0;
}

void write_book()
{
    Book bk;
    std::fstream outFile;
    char ch;
    outFile.open("book.bin", std::ios::out | std::ios::app);
    do
    {
        system("cls");
        bk.create_book();
        outFile.write((char *)&bk, sizeof(Book));
        std::cout << "\n\nDo you want to add more record? (y/n)";
        std::cin >> ch;
    }
    while (ch == 'y' || ch == 'Y');
    outFile.close();
}

void write_student()
{
    Student st;
    std::fstream outFile;
    char ch;
    outFile.open("student.bin", std::ios::out | std::ios::app);
    do
    {
        st.create_student();
        outFile.write((char *)&st, sizeof(Student));
        std::cout << "\n\nDo you want to add more record? (y/n)";
        std::cin >> ch;
    }
    while (ch == 'y' || ch == 'Y');
    outFile.close();
}

void display_spb(char n[])
{
    std::cout << "\nBOOK DETAILS\n";
    Book bk;
    std::fstream outFile;
    int flag = 0;
    outFile.open("book.bin", std::ios::in);
    while (outFile.read((char *)&bk, sizeof(Book))) {
        if (strcmp(bk.retbno(), n) == 0) {
            bk.show_book();
            flag = 1;
        }
    }
    outFile.close();
    if (flag == 0) {
        std::cout << "\n\nBook does not exist";
    }
    std::cin.get();
}

void display_sps(char n[])
{
    std::cout << "\nStudent DETAILS\n";
    Student st;
    std::fstream outFile;
    int flag = 0;
    outFile.open("student.bin", std::ios::in);
    while (outFile.read((char *)&st, sizeof(Student))) {
        if (strcmp(st.retadmno(), n) == 0) {
            st.show_student();
            flag = 1;
        }
    }
    outFile.close();
    if (flag == 0) {
        std::cout << "\n\nStudent does not exist";
    }
    std::cin.ignore();
    std::cin.get();
}

void modify_book()
{
    Book bk;
    std::fstream outFile;
    char n[6];
    int found = 0;
    system("cls");
    std::cout << "\n\n\tMODIFY BOOK REOCORD.... ";
    std::cout << "\n\n\tEnter The book no. of The book: ";
    std::cin >> n;
    outFile.open("book.bin",  std::ios::in | std::ios::out);
    while (!outFile.eof() && found == 0){
        outFile.read((char *)&bk, sizeof(Book));
        if (strcmp(bk.retbno(), n) == 0) {
            bk.show_book();
            std::cout<<"\nEnter The New Details of book"<<std::endl;
            bk.modify_book();
            int pos =(-1)*static_cast<int>(sizeof(bk));
            outFile.seekp(pos, std::ios::cur);
            outFile.write((char *)&bk, sizeof(Book));
            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    outFile.close();
    if (found == 0) {
        std::cout<<"\n\n Record Not Found ";
    }
    
    std::cin.get();
}

void modify_student()
{
    Student st;
    std::fstream outFile;
    char n[6];
    int found = 0;
    system("cls");
    std::cout << "\n\n\tMODIFY STUDENT REOCORD.... ";
    std::cout << "\n\n\tEnter The admission no. of The student";
    std::cin >> n;
    outFile.open("student.bin", std::ios::in | std::ios::out);
    while (!outFile.eof() && found == 0) {
        outFile.read((char *)&st, sizeof(Student));
        if (strcmp(st.retadmno(), n) == 0) {
            st.show_student();
            std::cout<<"\nEnter The New Details of student"<<std::endl;
            st.modify_student();
            int pos = (int)(-1 * sizeof(st));
            outFile.seekp(pos, std::ios::cur);
            outFile.write((char *)&st, sizeof(Student));
            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    outFile.close();
    if (found == 0) {
        std::cout<<"\n\n Record Not Found ";
    }
    std::cin.get();
}

void delete_student()
{
    Student st;
    std::fstream inFile;
    std::fstream outFile;
    char n[6];
    int flag = 0;
    system("cls");
    std::cout << "\n\n\n\tDELETE STUDENT...";
    std::cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
    std::cin >> n;
    inFile.open("student.bin", std::ios::in | std::ios::out);
    outFile.open("temp.bin", std::ios::out);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read((char *)&st, sizeof(Student))) {
        if (strcmp(st.retadmno(), n) != 0) {
            outFile.write((char *)&st, sizeof(Student));
        }
        else {
            flag = 1;
        }
    }
    
    outFile.close();
    inFile.close();
    remove("student.bin");
    rename("temp.bin", "student.bin");
    if(flag == 1)
        std::cout << "\n\n\tRecord Deleted...";
    else
        std::cout << "\n\nRecord not found";
    std::cin.get();
}

void delete_book()
{
    Book bk;
    std::fstream inFile;
    std::fstream outFile;
    char n[6];
    int flag = 0;
    system("cls");
    std::cout << "\n\n\n\tDELETE BOOK...";
    std::cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
    std::cin >> n;
    inFile.open("book.bin", std::ios::in | std::ios::out);
    outFile.open("temp.bin", std::ios::out);
    inFile.seekg(0, std::ios::beg);
    while (inFile.read((char *)&bk, sizeof(Book))) {
        if (strcmp(bk.retbno(), n) != 0) {
            outFile.write((char *)&bk, sizeof(Book));
        }
        else {
            flag = 1;
        }
    }
    
    outFile.close();
    inFile.close();
    remove("book.bin");
    rename("temp.bin", "book.bin");
    if(flag == 1)
        std::cout << "\n\n\tRecord Deleted...";
    else
        std::cout << "\n\nRecord not found";
    std::cin.get();
}

void display_alls()
{
    Student st;
    std::fstream outFile;
    system("cls");
    outFile.open("student.bin", std::ios::in);
    if (!outFile) {
        std::cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        std::cin.get();
        return;
    }
    
    std::cout << "\n\n\t\tSTUDENT LIST\n\n";
    std::cout<<"==================================================================\n";
    std::cout<<"Admission No.               Name                       Book Issued\n";
    std::cout<<"==================================================================\n";
    
    while (outFile.read((char *)&st, sizeof(Student))) {
        st.report();
    }
    outFile.close();
    std::cin.ignore();
    std::cin.get();
}

void display_allb()
{
    Book bk;
    std::fstream outFile;
    system("cls");
    outFile.open("book.bin", std::ios::in);
    if (!outFile) {
        std::cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        std::cin.get();
        return;
    }
    
    std::cout << "\n\n\t\t\t\t\tBOOK LIST\n\n";
    std::cout<<"==================================================================\n";
    std::cout<<"Book No.                Book Name                      Book Author\n";
    std::cout<<"==================================================================\n";
    
    while (outFile.read((char *)&bk, sizeof(Book))) {
        bk.report();
    }
    outFile.close();
    
    std::cin.ignore();
    std::cin.get();
}

void book_issue()
{
    Student st;
    Book bk;
    std::fstream stFile;
    std::fstream bkFile;
    char sn[6], bn[6];
    int found = 0, flag = 0;
    system("cls");
    std::cout<<"\n\nBOOK ISSUE ...";
    std::cout<<"\n\n\tEnter The student's admission no.";
    std::cin>>sn;
    stFile.open("student.bin", std::ios::in | std::ios::out);
    bkFile.open("book.bin", std::ios::in | std::ios::out);
    while (!stFile.eof() && found == 0) {
        stFile.read((char *)&st, sizeof(Student));
        if(strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if(st.rettoken() == 0)
            {
                std::cout<<"\n\n\tEnter the book no. ";
                std::cin>>bn;
                while (!bkFile.eof() && flag == 0) {
                    bkFile.read((char *)&bk, sizeof(Book));
                    if(strcmp(bk.retbno(), bn) == 0) {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = (int)(-1 * sizeof(st));
                        stFile.seekp(pos, std::ios::cur);
                        stFile.write((char *)&st, sizeof(Student));
                        std::cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
                    }
                }
                
                if(flag == 0)
                    std::cout<<"Book no does not exist";
            }
            else
                std::cout<<"You have not returned the last book ";
        }
    }
    
    if (found == 0)
        std::cout << "Student record not exist...";
    stFile.close();
    bkFile.close();
    std::cin.ignore();
    std::cin.get();
}

void book_deposit()
{
    Student st;
    Book bk;
    std::fstream stFile;
    std::fstream bkFile;
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    system("cls");
    std::cout<<"\n\nBOOK DEPOSIT ...";
    std::cout<<"\n\n\tEnter The student admission no. ";
    std::cin >> sn;
    stFile.open("student.bin", std::ios::in | std::ios::out);
    bkFile.open("book.bin", std::ios::in | std::ios::out);
    while (!stFile.eof() && found == 0) {
        stFile.read((char *)&st, sizeof(Student));
        if(strcmp(st.retadmno(), sn) == 0)
        {
            found = 1;
            if (st.rettoken() == 1) {
                while (!bkFile.eof() && flag == 0) {
                    bkFile.read((char *)&bk, sizeof(Book));
                    if(strcmp(bk.retbno(), st.retstbno()) == 0)
                    {
                        bk.show_book();
                        flag = 1;
                        std::cout<<"\n\nBook deposited in no. of days";
                        std::cin>>day;
                        if(day > 15)
                        {
                            fine = (day-15)*1;
                            std::cout<<"\n\nFine has to deposited Rs. "<<fine;
                        }
                        st.resettoken();
                        int pos=(int)(-1*sizeof(st));
                        stFile.seekp(pos, std::ios::cur);
                        stFile.write((char *)&st, sizeof(Student));
                        std::cout<<"\n\n\t Book deposited successfully";
                    }
                }
                if (flag == 0) {
                    std::cout<<"Book no does not exist";
                }
            }
            else
                std::cout<<"No book is issued..please check!!";
        }
    }
    
    if(found==0)
        std::cout<<"Student record not exist...";
    stFile.close();
    bkFile.close();
    std::cin.ignore();
    std::cin.get();
}

void intro()
{
    system("cls");
    std::cout << "\n\n\n\t  LIBRARY";
    std::cout << "\n\n\tMANAGEMENT";
    std::cout << "\n\n\t  SYSTEM";
    std::cin.get();
}

void admin_menu()
{
    system("cls");
    int ch2;
    std::cout<<"\n\n\n\tADMINISTRATOR MENU";
    std::cout<<"\n\n\t1.CREATE STUDENT RECORD";
    std::cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    std::cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    std::cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    std::cout<<"\n\n\t5.DELETE STUDENT RECORD";
    std::cout<<"\n\n\t6.CREATE BOOK ";
    std::cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    std::cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    std::cout<<"\n\n\t9.MODIFY BOOK ";
    std::cout<<"\n\n\t10.DELETE BOOK ";
    std::cout<<"\n\n\t11.BACK TO MAIN MENU";
    std::cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    std::cin>>ch2;
    switch(ch2)
    {
            case 1: system("cls");
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
            system("cls");
                   std::cout<<"\n\n\tPlease Enter The Admission No. ";
                   std::cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: system("cls");
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   system("cls");
                   std::cout<<"\n\n\tPlease Enter The book No. ";
                   std::cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
        default:std::cout<<"\a";
       }
    
    admin_menu();
}
