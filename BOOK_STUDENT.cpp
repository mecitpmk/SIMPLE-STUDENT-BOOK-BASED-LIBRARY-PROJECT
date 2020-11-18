#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Student;
class Book
{
    private:
        string writer;
        int page_number;
        int n_copy;
        vector<Student*> taken_from;

    public:
        Book(string,int,int);
        void changePage(int new_Number) {this->page_number = new_Number;};
        void changeCopy(int newNumber) {this->n_copy = newNumber;};
        int getPageNum() {return this->page_number;};
        int getCopyNum() {return this->n_copy;};
        void printBookInfo() { cout << "Book Author : " << this->writer << " Book Page Number: " << this->page_number << " N.Copies : " << this->n_copy << endl;}
        string getWriter() {return this->writer;};
        void testSomething(Student *student_object);
        void checkWhoTake();
        bool available();
};


vector<Book*> Created_Books;
Book::Book(string writer, int page_number , int n_copy)
{
    this->writer = writer;
    this->page_number = page_number;
    this->n_copy = n_copy;
    Created_Books.push_back(this);
}

bool Book::available()
{
    if (this->n_copy > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

class Student
{
    private:
        string name;
        vector <Book*> taken_books;
    public:
        Student(string);
        void printTakenBooks();
        string getName() {return this->name;};
        //void getName() {cout << this->name << endl;};
        void AddNewBook(Book *BookObject);
};

void Book::testSomething(Student *student_object)
{
    cout << "Test Something function is running now..." << endl;
    this->taken_from.push_back(student_object);
    cout << "Addded Check Now!." << endl;
}
void Book::checkWhoTake()
{
    for(auto st : this->taken_from)
    {
        cout << st->getName() << endl;
    }
}


map<Book*,Student*> BookAndTaker;
Student::Student(string student_Name)
{
    this->name = student_Name;
}


void Student::printTakenBooks()
{
    cout << "Taken books will be listing Now.... \n" << endl;
    for (auto book : this->taken_books)
    {
        book->printBookInfo();
    }
}
void Student::AddNewBook(Book *BookObject)
{
    if (BookObject->available())
    {
        cout << "A book who writer is  : " << BookObject->getWriter() << " Has been taked.."  << endl;
        cout << "Before its Number Copy: " << BookObject->getCopyNum() << endl;
        BookObject->changeCopy(BookObject->getCopyNum()-1);
        BookObject->testSomething(this);
        cout << "After its Number Copy: " << BookObject->getCopyNum() << endl;
        this->taken_books.push_back(BookObject);
        BookAndTaker[BookObject] = this;
    }
    else
    {
        cout << "BOOK IS NOT AVAILABLE " << endl;
    }
    
}

int main()
{
    
    Book *myBook = new Book("Mecit",44,2);
    myBook->printBookInfo();
    Student *MyStudent = new Student("Muhammet");
    MyStudent->AddNewBook(myBook);
    MyStudent->printTakenBooks();
    
    cout << "--\nNOW ACCESSING INSIDE BOOK AND TAKER MAP \n" <<endl;
    BookAndTaker[myBook]->printTakenBooks();
    cout << "CHECKING BOOKINSIDE VECTOR" << endl;
    myBook->checkWhoTake();
    Student *OtherStudent = new Student("Huseyin");
    OtherStudent->AddNewBook(myBook);
    return 0;
}