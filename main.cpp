#include <iostream>
#include <iostream>
#include <fstream>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<stdio.h>

using namespace std;
struct Book
{
    char ISBN[7];
    char Title[20];
    char Author[20];
    char Price[6];
    char Year[6];
    char Numofbages [6];
};
ostream& operator<<(ostream & os, Book &b)
{
    os << "ISBN: " << b.ISBN<<" Book Title: "<<b.Title <<" Author Name: "<<b.Author<<" Year: "<<b.Year;
    os << " Number of pages: " << b.Numofbages << " Price: " <<b.Price<< endl;
    return os;
}
void addbook(fstream &f,short &RNN);
bool Searchtitle(fstream &f , string title,short& index);
bool Search(fstream &f , string isbn,short& index);
bool Delete(fstream &f,short &RNN);
bool Ubdate(fstream &f,short &RNN);
void print (fstream &f);
void printALL (fstream &f);
void Compact (fstream &f);

int main()
{
    fstream f("Task.txt",ios::out|ios::in);
    short RNN;
    f.seekp(0,ios::end);
    int END= f.tellp();
    if (END==0)
    {
        RNN=-1;
        f.write((char*)&RNN,sizeof(RNN));
    }
    else
    {
        f.seekg(0,ios::beg);
        f.read((char*)&RNN,sizeof(RNN));
    }
    while (true)
    {
        cout << "1) Add Book\n2) Delete Book\n3) Update Book\n4) Print Book\n5) Print all Books\n6) Compact the file\n0) Exit\n";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice==1)
        {
            addbook(f,RNN);
        }
        else if (choice==2)
        {
            Delete(f,RNN);
        }
        else if (choice==3)
        {
            Ubdate(f,RNN);
        }
        else if (choice==4)
        {
            print(f);
        }
        else if (choice==5)
        {
            printALL(f);
        }
        else if (choice==6)
        {
            Compact(f);
        }
        else
            break;
    }
    return 0;
}
void Compact (fstream &f)
{
    fstream f2("Task2.txt",ios::out);
    f.seekp(0,ios::end);
    int endofloop=f.tellp();
    for (int i=2; i<endofloop; i=i+65)
    {
        f.seekg(i,ios::beg);
            Book b;
            f.read(b.ISBN,7);
            b.ISBN[strlen(b.ISBN)-1]='\0';
            if (b.ISBN[0]=='*')
                continue;
            f.read(b.Title,20);
            b.Title[strlen(b.Title)-1]='\0';
            f.read(b.Author,20);
            b.Author[strlen(b.Author)-1]='\0';
            f.read(b.Price,6);
            b.Price[strlen(b.Price)-1]='\0';
            f.read(b.Year,6);
            b.Year[strlen(b.Year)-1]='\0';
            f.read(b.Numofbages,6);
            b.Numofbages[strlen(b.Numofbages)-1]='\0';
            f2.write((char*)&b,sizeof(b));
        }}
void printALL(fstream &f)
{
    f.seekp(0,ios::end);
    int endofloop=f.tellp();
    for (int i=2; i<endofloop; i=i+65)
    {
        f.seekg(i,ios::beg);
            Book b;
            f.read(b.ISBN,7);
            b.ISBN[strlen(b.ISBN)-1]='\0';
            if (b.ISBN[0]=='*')
                continue;
            f.read(b.Title,20);
            b.Title[strlen(b.Title)-1]='\0';
            f.read(b.Author,20);
            b.Author[strlen(b.Author)-1]='\0';
            f.read(b.Price,6);
            b.Price[strlen(b.Price)-1]='\0';
            f.read(b.Year,6);
            b.Year[strlen(b.Year)-1]='\0';
            f.read(b.Numofbages,6);
            b.Numofbages[strlen(b.Numofbages)-1]='\0';
            cout << b;
        }
}
void print (fstream &f)
{
    cout << "1) Search By ISBN         2) Search By Title";
    int choice;
    cin >> choice;
    bool check;
    short index;
    if (choice==1)
    {
    string isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;
    check=Search(f,isbn,index);
    }
    else if (choice==2)
    {
    string title;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin,title);
    check=Searchtitle(f,title,index);
    }
    if (check)
    {
        Book b;
        f.seekg(2+(65*index),ios::beg);
        f.read(b.ISBN,7);
        b.ISBN[strlen(b.ISBN)-1]=' ';
        if (b.ISBN[0]=='*')
            cout << "Was Deleted"<< endl;
        else
        {
        f.read(b.Title,20);
        b.Title[strlen(b.Title)-1]=' ';
        f.read(b.Author,20);
        b.Author[strlen(b.Author)-1]=' ';
        f.read(b.Price,6);
        b.Price[strlen(b.Price)-1]=' ';
        f.read(b.Year,6);
        b.Year[strlen(b.Year)-1]=' ';
        f.read(b.Numofbages,6);
        b.Numofbages[strlen(b.Numofbages)-1]=' ';
        cout << b;
    }
    }
}
bool Ubdate(fstream &f,short &RNN)
{
    if (Delete(f,RNN))
    {
        addbook(f,RNN);
        return true;
    }
    else
        return false;
}
bool Delete(fstream &f,short &RNN)
{
    string isbn;
    short index;
    char* del="*";
    short NEW;
    cout << "Enter ISBN: ";
    cin >> isbn ;
    if (Search(f,isbn,index))
    {
        f.seekg(0,ios::beg);
        f.read((char*)&NEW,sizeof(NEW));
        f.seekp(0,ios::beg);
        f.write((char*)&index,sizeof(index));
        f.seekp(2+(index*65),ios::beg);
        f.write(del,1);
        RNN= NEW;
        f.write((char*)&RNN,sizeof(RNN));
        return true;
    }
    else
    {
        cout << "Not found";
        return false;
    }
}

bool Searchtitle(fstream &f , string title,short& index)
{
    char* s=new char[20];
    f.seekp(0,ios::end);
    int counter=0,endofloop=f.tellp();
    for (int i=9; i<endofloop; i=i+65)
    {
        f.seekg(i,ios::beg);
        f.read(s,20);
        s[strlen(s)-1]='\0';
        if (s==title)
        {
            index=counter;
            return true;
        }
        counter++;
    }
    return false;
}
bool Search(fstream &f , string isbn,short &index)
{
    char* s=new char[7];
    f.seekp(0,ios::end);
    int counter=0,endofloop=f.tellp();
    for (int i=2; i<endofloop; i=i+65)
    {
        f.seekg(i,ios::beg);
        f.read(s,7);
        s[strlen(s)-1]='\0';
        if (s==isbn)
        {
            index=counter;
            return true;
        }
        counter++;
    }
    return false;
}
void addbook(fstream &f,short &RNN)
{
    Book b;
    short check,NEW;
    cin.ignore();
    cout << "Enter Book ISBN: ";
    cin.getline(b.ISBN,7);
    strcat(b.ISBN,"|");
    cout << "Enter Book title: ";
    cin.getline(b.Title,20);
    strcat(b.Title,"|");
    cout << "Enter Author Name: ";
    cin.getline(b.Author,20);
    strcat(b.Author,"|");
    cout << "Enter Book Price: ";
    cin.getline(b.Price,6);
    strcat(b.Price,"|");
    cout << "Enter Book Year: ";
    cin.getline(b.Year,6);
    strcat(b.Year,"|");
    cout << "Enter Number of pages: ";
    cin.getline(b.Numofbages,6);
    strcat(b.Numofbages,"|");
    check=RNN;
    if (check!=-1)
    {
        f.seekp(2+65*(check),ios::beg);
        f.seekg(3+65*(check),ios::beg);
        f.read((char*)&NEW,sizeof(NEW));
        RNN=NEW;
        f.seekp(0,ios::beg);
        f.write((char*)&RNN,sizeof(RNN));
        f.seekp(2+65*(check),ios::beg);
        cout << check;
        f.write((char*)&b,sizeof (b));
    }
    else
    {
        f.seekp(0,ios::end);
        f.write((char*)&b,sizeof (b));
    }
}
