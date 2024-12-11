#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"

using namespace std;

//a global function, which takes the file name and the BST and reads the books in the file into the BST.
void readBooks (const string& filename,BST& tree)
{
    // Create an object of ifstream class
    ifstream file;
    // Open method and pass the file name we want to read
    file.open(filename);
    // Check whether the file has opened successfully or not
    if(!file.is_open())
    {
        cout<<"Error while opening the file."<<endl;
        return;
    }

    cout<<"Reading from the file "<<filename<<" ..."<<endl;

    string title, author , category;
    int numOfPages;

    while(std::getline(file,title) &&
          std::getline(file,author) &&
          std::getline(file,category) &&
          (file >> numOfPages))
        {
            file.ignore();

            // Create a Book object and insert it into the BST
            Book book(title,author,category,numOfPages);
            tree.BSTInsert(book);
        }

    if (file.eof())
       cout << "Finished reading books." <<endl;
    else
       cout << "Error: File format is invalid." <<endl;

    file.close();
}

int main()
{
    // Create an object of BST
    BST tree;

    string filename ="Book.txt";

    readBooks (filename,tree);

    string title,author,category;
    int numOfpages;
    int option;

    while(1)
    {
        // Display the menu to the user
        cout<<"Which operation would you like to do on your BST : "<<endl;
        cout<<"1-Display all books sorted by title ascendingly."<<endl;
        cout<<"2-Display all books sorted by title descendingly."<<endl;
        cout<<"3-Remove a book by title."<<endl;
        cout<<"4-Add a new book(to be added to the already existing books)."<<endl;
        cout<<"5-Search for a book by title."<<endl;
        cout<<"6-Display certain author books."<<endl;
        cout<<"7-Display certain category books."<<endl;
        cout<<"8-Exit."<<endl;
        cin>>option;
        switch(option)
        {
            case 1:
                {
                    tree.DisplayAscending();
                    break;
                }
            case 2:
                {
                    tree.DisplayDescending();
                    break;
                }
            case 3:
                {
                    cout<<"Please enter the title of the book you want to remove : "<<endl;
                    cin.ignore();
                    std::getline(cin,title);
                    tree.Remove(title);
                    break;
                }
            case 4:
                {
                    cout<<"Please enter the data of the book you want to add (title,author,category,no. of pages): "<<endl;
                    cin.ignore();
                    std::getline(cin,title);
                    std::getline(cin,author);
                    std::getline(cin,category);
                    cin>>numOfpages;
                    Book newBook(title,author,category,numOfpages);
                    tree.BSTInsert(newBook);
                    std::cout<<"Book added successfully."<<std::endl;
                    break;
                }
            case 5:
                {
                    cout<<"Please enter the title of the book you want to search for: "<<endl;
                    cin.ignore();
                    std::getline(cin,title);
                    tree.SearchTitle(title);
                    break;
                }
            case 6:
                {
                    cout<<"Please enter the name of the author you want to display its books : "<<endl;
                    cin.ignore();
                    std::getline(cin,author);
                    tree.SearchAuthor(author);
                    break;
                }
            case 7:
                {
                    cout<<"Please enter the category you want to display related books : "<<endl;
                    cin.ignore();
                    std::getline(cin,category);
                    tree.SearchCategory(category);
                    break;
                }
            case 8:
                return 0;
        }
    }
    return 0;
}
