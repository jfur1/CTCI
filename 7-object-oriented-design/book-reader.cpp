/*
Author: John Furlong
Date: June 12, 2020
Description: Online Book Reader
    Design the data structures for an online book reader system.
*/
#include <iostream>
using namepsace std;

struct Page{
    int page_num;
    string contents;
    int chapter;
};

class Book{
    private:
        int year;
        int bookID;
        int chapter;
        string author;
        vector<Page> story;

    public:
        // To construct a new book, fill its pages vector with the given pages
        Book(vector<Page> pages){
            for(int i = 0; i < pages.size(); i++){
                story.push_back(pages[i])
            }
        }
};

class BookReader(){
    private:
        int nBooks;
        int userID;
        string userName;
        string userEmail;
        vector<Book> library;

    public:
        BookReader(userName){
            userName = userName;
        }

        void printMenu(){
            // Print the menu for the book reader
        }
        
        Book* find_book(int bookID){
            for(int i = 0; i < library.size(); i++){
                if(library[i].bookID == bookID)
                    return library[i]
            }
            print("Book not found.\n")
            return None
        }

};