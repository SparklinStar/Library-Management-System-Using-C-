//Library Management System applying OOP concepts
//OOP Concepts applied: Classes and Objects,Access Specifiers,Encapsulation

//Libraries
#include<iostream> 
#include<string>
#include<iomanip>	
#include <fstream> // Include for file operations

using namespace std;

class Book {
	private:
		string isbn,title,author,edition,publication;
		bool available;
    	time_t issueDate;
    	string studentName; //private variables
	public:
		//setters - assigning user value to private variables
		void setIsbn(string a){isbn = a;}
		void setTitle(string b){title = b;}
		void setAuthor(string c){author = c;}
		void setEdition(string d){edition = d;}
		void setPublication(string e){publication = e;}
		void setAvailability(bool avail) { available = avail; }
    	void setIssueDate(time_t date) { issueDate = date; }
    	void setStudentName(string name) { studentName = name; }
		

		//getters - getting the values from private variables
		string getIsbn(){return isbn;}
		string getTitle(){return title;}
		string getAuthor(){return author;}
		string getEdition(){return edition;}
		string getPublication(){return publication;}
		bool getAvailability() { return available; }
    	time_t getIssueDate() { return issueDate; }
    	string getStudentName() { return studentName; }
	
};
class Student {
private:
    string ID;
    string name;
    string department;

public:
    // Setters
    void setID(string id) { ID = id; }
    void setName(string n) { name = n; }
    void setDepartment(string dep) { department = dep; }

    // Getters
    string getID() { return ID; }
    string getName() { return name; }
    string getDepartment() { return department; }
};

// Function to read student details from a text file
void readStudentDetailsFromFile(Student& student) {
    ifstream studentFile("studentdetails.txt");
    if (studentFile.is_open()) {
        string id, name, department;

        // Read the first line from the file
        while (studentFile >> id >> name >> department) {
            student.setID(id);
            student.setName(name);
            student.setDepartment(department);
        }
        studentFile.close();
    } else {
        cout << "Unable to open student details file." << endl;
    }
}
//initializing functions with counter as parameter
void addBook(int counter);
void deleteBook(int counter);
void editBook(int counter);
void searchBook(int counter);
void viewAllBooks(int counter);
void issueBook(int counter);
void depositBook(int counter);
void quit();
void readBooksFromFile();
//counter for Book array
int counter=0;

//function for incrementing counter
void increment(int a){
	a++;
	counter=a;
}

//function for decrementing counter
void decrement(int a){
	a--;
	counter=a;
}

//Book class array initialization
Book books[5000];

Student students[1000];
int studentCount = 0;

void readStudentDetailsFromFile(); 

void displayStudentDetails(int counter); 


//main function
int main(){
string choice;
//Main Menu
system("clear");
cout<<"LIBRARY MANAGEMENT SYSTEM\n\n";
cout<<"[1]ADD BOOK\n";	
cout<<"[2]DELETE BOOK\n";	
cout<<"[3]EDIT BOOK\n";	
cout<<"[4]SEARCH BOOK\n";	
cout<<"[5]VIEW ALL BOOKS\n";	
cout<<"[6]ISSUE BOOK\n";
cout<<"[7]DEPOSIT BOOK\n";
cout <<"[8]STUDENT DETAILS\n";
cout<<"[9]QUIT\n";
cout<<"ENTER CHOICE: ";
getline(cin,choice);
system("clear");
readBooksFromFile();
readStudentDetailsFromFile();
if(choice=="1"){
	addBook(counter); //function call
}		
else if(choice=="2"){	
	deleteBook(counter); //function call
}
else if(choice=="3"){
	editBook(counter); //function call	
}
else if(choice=="4"){
	searchBook(counter); //function call	
}
else if(choice=="5"){
	viewAllBooks(counter); //function call	
}

else if (choice == "6") {
        issueBook(counter);
    }
    else if (choice == "7") {
        depositBook(counter);
    }
	else if(choice=="9"){
	quit();	 //function call
}
else if (choice == "8") {
        displayStudentDetails(studentCount);
    }
else{
	main();  //function call to self(main)
}
	
cin.get();
return 0;
}

void readStudentDetailsFromFile() {
    ifstream studentFile("studentdata.txt");
    if (studentFile.is_open()) {
        string id, name, department;

        // Read the first line from the file
        while (studentFile >> id >> name >> department) {
            students[studentCount].setID(id);
            students[studentCount].setName(name);
            students[studentCount].setDepartment(department);
            studentCount++;

            // Check if counter reaches maximum limit
            if (studentCount >= 300) {
                break;
            }
        }
        studentFile.close();
		
    } else {
        cout << "Unable to open student details file." << endl;
    }
}

void displayStudentDetails(int counter) {
    string studentID;
    cout << "STUDENT DETAILS\n\n";
    cout << "Enter Student ID: ";
    getline(cin, studentID);

    bool found = false;
    int issuedBooks = 0;
    int depositedBooks = 0;
    double totalFine = 0.0;
    string studentName, studentDept;

    // Find the student
    for (int i = 0; i < counter; ++i) {
        if (students[i].getID() == studentID) {
            found = true;
            studentName = students[i].getName();
            studentDept = students[i].getDepartment();

            // Count the books for the student
            for (int j = 0; j < counter; j++) {
                if (books[j].getStudentName() == studentID) {
                    if (!books[j].getAvailability()) {
                        issuedBooks++;
                    } else {
                        depositedBooks++;

                        // Calculate fine for deposited books
                        time_t currentTime;
                        time(&currentTime);
                        time_t issueTime = books[j].getIssueDate();
                        double timeDifference = difftime(currentTime, issueTime);
                        int daysLate = static_cast<int>(timeDifference / (60 * 60 * 24));
                        
                        // Calculate the fine for each deposited book
                        if (daysLate > 0) {
                            totalFine += daysLate; // Assuming 1 rupee per day late
                        }
                    }
                }
            }

            // Display student details and book counts
            cout << "Student ID: " << studentID << endl;
            cout << "Student Name: " << studentName << endl;
            cout << "Department: " << studentDept << endl;
            cout << "Books Issued: " << issuedBooks << endl;
            // cout << "Books Deposited: " << depositedBooks << endl;
            // cout << "Total Fine Paid: $" << totalFine << endl;

            break;
        }
    }

    if (!found) {
        cout << "Student ID not found!\n";
    }

    cout << "\n\nPress any key to continue . . .";
    cin.get();
    main(); // Consider removing this recursive call if possible
}


// Function to read book details from a text file and populate the library
void readBooksFromFile() {
    ifstream inputFile("books.txt"); // Open the file
    if (inputFile.is_open()) {
        string isbn, title, author, edition, publication;

        // Loop through lines in the file to read book details
        while (inputFile >> isbn >> title >> author >> edition >> publication) {
            books[counter].setIsbn(isbn);
            books[counter].setTitle(title);
            books[counter].setAuthor(author);
            books[counter].setEdition(edition);
            books[counter].setPublication(publication);
            books[counter].setAvailability(true);
            counter++;

            // Check if counter reaches maximum limit
            if (counter >= 50) {
                break;
            }
        }
        inputFile.close(); // Close the file
    } else {
        cout << "Unable to open file." << endl;
    }
}

//addBook function
void addBook(int counter){
	string isbn,title,author,edition,publication;
	cout<<"ADD BOOK\n\n";
	if(counter<500){
		cout<<"Enter ISBN: ";
		getline(cin,isbn); //getline - just like cin but includes white spaces
		cout<<"Enter Title: ";
		getline(cin,title);
		cout<<"Enter Author: ";
		getline(cin,author);
		cout<<"Enter Edition: ";
		getline(cin,edition);
		cout<<"Enter Publication: ";
		getline(cin,publication);
		books[counter].setIsbn(isbn); //assigning the values entered to book object
		books[counter].setTitle(title);
		books[counter].setAuthor(author);
		books[counter].setEdition(edition);
		books[counter].setPublication(publication);	
		books[counter].setAvailability(true);
		increment(counter);	//calling function to increment counter
		cout<<"\nBOOK ADDED SUCCESSFULLY!\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
	else{
		cout<<"YOU HAVE REACHED THE MAXIMUM NUMBER OF BOOKS TOBE ADDED!\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
}
void issueBook(int counter) {
    string isbn, studentID;
    time_t currentTime;
    time(&currentTime);

    cout << "ISSUE BOOK\n\n";
    if (counter == 0) {
        cout << "THERE ARE NO BOOKS TO ISSUE!\n\n";
        cout << "\n\nPress any key to continue . . .";
                    cin.get();
        main();
    }

    cout << "Enter ISBN of the book to issue: ";
    getline(cin, isbn);

    for (int i = 0; i < counter; i++) {
        if (books[i].getIsbn() == isbn) {
            if (books[i].getAvailability()) {
                cout << "Enter student ID: ";
                getline(cin, studentID);

                // Validate the student ID
                bool validStudent = false;
                for (int j = 0; j < studentCount; j++) {
                    if (students[j].getID() == studentID) {
                        validStudent = true;
                        break;
                    }
                }

                if (validStudent) {
                    // Set book details for issuing
                    books[i].setAvailability(false);
                    books[i].setIssueDate(currentTime);
                    books[i].setStudentName(studentID); // Store student ID in the book

                    cout << "\nBOOK SUCCESSFULLY ISSUED!\n\n";
                    time_t reissueTime = currentTime + (14 * 24 * 60 * 60); // Assuming a 14-day loan period
                    tm* reissueDate = localtime(&reissueTime);
                    cout << "Return by: " << put_time(reissueDate, "%F") << "\n\n";
                    cout << "\n\nPress any key to continue . . .";
                    cin.get();
                    main();
                } else {
                    cout << "Invalid student ID. Enter a valid student ID.\n\n";
					cout << "\n\nPress any key to continue . . .";
                    cin.get();
                    main();
                }
            } else {
                cout << "Book is not available for issue.\n\n";
				cout << "\n\nPress any key to continue . . .";
                    cin.get();
                main();
            }
        }
    }
    cout << "BOOK NOT FOUND!\n\n";
}

void depositBook(int counter) {
    string isbn;
    time_t currentTime;
    time(&currentTime);

    cout << "DEPOSIT BOOK\n\n";
    if (counter == 0) {
        cout << "THERE ARE NO BOOKS TO DEPOSIT!\n\n";
		cout << "\n\nPress any key to continue . . .";
                    cin.get();
        main();
    }

    cout << "Enter ISBN of the book to deposit: ";
    getline(cin, isbn);

    for (int i = 0; i < counter; i++) {
        if (books[i].getIsbn() == isbn) {
            if (!books[i].getAvailability()) {
                double damageCharge = 0.0;
                time_t issueTime = books[i].getIssueDate();
                double timeDifference = difftime(currentTime, issueTime);
                int daysLate = static_cast<int>(timeDifference / (60 * 60 * 24)); // Calculate days late

                if (daysLate > 0) {
                    // Calculate damage charges for late deposit
                    damageCharge = daysLate; // Example: Charge 1 rupee per day late
                    cout << "Book deposited " << daysLate << " days late. Damage charge: $" << damageCharge << endl;
                }

                // Reset book details after deposit
                books[i].setAvailability(true);
                books[i].setIssueDate(0);
                books[i].setStudentName("");

                cout << "BOOK SUCCESSFULLY DEPOSITED!\n\n";
                cout<<"\n\nPress any key to continue . . .";
				cin.get();
				main();
            } else {
                cout << "Book is already deposited.\n\n";
                cout<<"\n\nPress any key to continue . . .";
				cin.get();
				main();
            }
        }
    }
    cout << "BOOK NOT FOUND!\n\n";
}

//deleteBook function
void deleteBook(int counter){
	string isbn;
	int choice;
	cout<<"DELETE BOOK\n\n";
	if(counter==0){
		cout<<"THERE IS NO BOOK TO DELETE!\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
	cout<<"Enter ISBN: ";
	getline(cin,isbn);

	for(int i=0;i<counter;i++){
		//finding a match using for loop
		if(books[i].getIsbn()==isbn){
			cout<<"\nBOOK FOUND\n\n";
			cout<<"Do you want to delete?\n[1]Yes\n[2]No\n\nEnter Choice: ";
			cin>>choice;
			if(choice==1){
				books[i].setIsbn(""); //setting the value to none
				books[i].setTitle("");
				books[i].setAuthor("");
				books[i].setEdition("");
				books[i].setPublication("");
				for(int a=i;a<counter;a++){
					//adjusting the values after deletion of data eg. data from book[4] copied to book[3]
					books[a] = books[a+1];
				}
				books[9].setIsbn(""); //adjustment if the library is full(10 books)
				books[9].setTitle("");
				books[9].setAuthor("");
				books[9].setEdition("");
				books[9].setPublication("");
				decrement(counter); //calling function to decrement counter
				cout<<"\nBOOK SUCCESSFULLY DELETED!\n\nPress any key to continue . . .";
				cin.get();
				main();
			}
			else{
				main();
			}
		}
	}
	cout<<"\nBOOK NOT FOUND!\n\nPress any key to continue . . .";
	cin.get();
	main();
	
}
void editBook(int counter){
	system("clear");
	string editIsbn,choice;
	string isbn,title,author,edition,publication;
	cout<<"\nEDIT BOOK\n\n";
	if(counter==0){
		cout<<"THERE IS NO BOOK TO EDIT!\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
	cout<<"Enter ISBN: ";
	getline(cin,editIsbn);
	for(int i=0;i<counter;i++){
		//finding a match using for loop
		if(books[i].getIsbn()==editIsbn){
			cout<<"\nBOOK FOUND!\n\n";
			cout<<"ISBN: "<<books[i].getIsbn()<<endl;
			cout<<"TITLE: "<<books[i].getTitle()<<endl;
			cout<<"AUTHOR: "<<books[i].getAuthor()<<endl;
			cout<<"EDITION: "<<books[i].getEdition()<<endl;
			cout<<"PUBLICATION: "<<books[i].getPublication()<<endl;
			cout<<"\nDo you want to edit?\n[1]Yes\n[2]No\n\nEnter choice: ";
			getline(cin,choice);
			if(choice=="1"){
				//re-entering values
				cout<<"Enter ISBN: ";
				getline(cin,isbn);
				cout<<"Enter Title: ";
				getline(cin,title);
				cout<<"Enter Author: ";
				getline(cin,author);
				cout<<"Enter Edition: ";
				getline(cin,edition);
				cout<<"Enter Publication: ";
				getline(cin,publication);
				books[i].setIsbn(isbn);
				books[i].setTitle(title);
				books[i].setAuthor(author);
				books[i].setEdition(edition);
				books[i].setPublication(publication);	
				cout<<"\nBOOK EDITED SUCCESSFULLY!\n\nPress any key to continue . . .";
				cin.get();
				editBook(counter);//function call to self
			}
			else{
				main();
			}			
		}
}
	cout<<"\nBOOK NOT FOUND!\n\nPress any key to continue . . .";
	cin.get();
	main();
}
void searchBook(int counter){
	string isbn;
	int choice;
	bool print = false; //boolean expression to decide which to print
	cout<<"SEARCH BOOK\n\n";
	if(counter==0){
		cout<<"THERE IS NO BOOK TO SEARCH!\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
	cout<<"Enter ISBN: ";
	getline(cin,isbn);
	for(int i=0;i<counter;i++){
		//finding a match using for loop
		if(books[i].getIsbn()==isbn){ 
			cout<<"\nBOOK FOUND!\n\n";
			cout<<"ISBN: "<<books[i].getIsbn()<<endl;
			cout<<"TITLE: "<<books[i].getTitle()<<endl;
			cout<<"AUTHOR: "<<books[i].getAuthor()<<endl;
			cout<<"EDITION: "<<books[i].getEdition()<<endl;
			cout<<"PUBLICATION: "<<books[i].getPublication()<<endl;
			print = true;
			
		}
	}
	if(print){
		cout<<"\n\nPress any key to continue . . .";
		cin.get();
		main();
	}
	//if there's no book found
	else{
		cout<<"\nBOOK NOT FOUND!\n\nPress any key to continue . . .";
		cin.get();
		main();		
	}
}
void viewAllBooks(int counter){
	//iterating all the values on the library using book array
	cout<<"VIEW ALL BOOKS\n\n";
	for(int i=0;i<counter;i++){
		cout<<"BOOK DETAILS\n\n";
		cout<<"ISBN: "<<books[i].getIsbn()<<endl;
		cout<<"TITLE: "<<books[i].getTitle()<<endl;
		cout<<"AUTHOR: "<<books[i].getAuthor()<<endl;
		cout<<"EDITION: "<<books[i].getEdition()<<endl;
		cout<<"PUBLICATION: "<<books[i].getPublication()<<endl<<endl;
	}
	cout<<"Press any key to continue . . .";
	cin.get();
	main();
}
void quit(){
	//quit function
	exit(1);
}


