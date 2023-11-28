#include<bits/stdc++.h>
using namespace std; 

class Book{
  private:
  int bookid;
  char title[20];
  float price;

  public:
  Book(){
    bookid = 0;
    strcpy(title, "no title");
    price=0;
  }

   void getBookData(){
    cout<<"Enter bookid, title and price ";
    cin>>bookid;
     cin.ignore();
     cin.getline(title,19);
     cin>>price;
   }

   void showBookData(){
    cout<<"Book id : "<<bookid<<endl;
    cout<<"Title : "<<title<<endl;
    cout<<"Price : "<<price<<endl;
   }

   int storeBook();
   void viewAllBooks();
   void searchBook(char *);
   void deleteBook(char *);
   void updateBook(char *);

};


void Book::viewAllBooks(){
      ifstream fin;
      fin.open("book.txt", ios::in|ios::binary);
      if(!fin){
        cout<<"\n file is not found";
      }else{
           fin.read((char*)this, sizeof(*this));
           while(!fin.eof()){
            showBookData();
            fin.read((char*)this, sizeof(*this));
           }
      }
      fin.close();
}

int Book::storeBook(){

    if(bookid==0 && price==0){
        cout<<"Book id and price cannot be 0"<<endl;
        return 0;
    }
    else{
       ofstream fout;
       fout.open("book.txt",ios::app|ios::binary);
       fout.write((char*)this, sizeof(*this));
       fout.close();
       return 1;
    }
}

void Book::searchBook(char* t){

    int counter=0;
    ifstream fin;
    fin.open("book.txt", ios::in|ios::binary);
    if(!fin){
        cout<<"\n file is not found";
    }else{
        fin.read((char*)this, sizeof(*this));
         while(!fin.eof()){
            if (!strcmp(title,t)){
                counter++;
                showBookData();
         }
                fin.read((char*)this, sizeof(*this)); 
       }
    }
        fin.close();   
        if(counter == 0){
            cout<<"Record not found";
        }
}

void Book :: deleteBook(char *t){
    ifstream fin;
    ofstream fout;

    fin.open("book.txt", ios::in|ios::binary);
    if(!fin)  cout<<"\n file not found";
    else{
        fout.open("temp.txt", ios::out|ios::binary);
        fin.read((char*)this, sizeof(*this));
         while(!fin.eof()){
            if(strcmp(title, t)) {
                fout.write((char*)this, sizeof(*this));
            }
        fin.read((char*)this, sizeof(*this));
         }
         fin.close();
         fout.close();
         remove("book.txt");
         rename("temp.txt", "book.txt");
    }

}

void Book::updateBook(char *t) {
  fstream file;
  file.open("book.txt", ios::in | ios::out | ios::ate | ios::binary);
  file.seekg(0);
  file.read((char *)this, sizeof(*this));
  while (!file.eof()) {
    if (!strcmp(title, t)) {
      getBookData();
      file.seekp(file.tellp() - sizeof(*this));
      file.write((char *)this, sizeof(*this));
    }
    file.read((char *)this, sizeof(*this));
  }
  file.close();
}


int menu2(){
    int choice;
    cout<<"\nBook Managemant";
    cout<<"\n1. Insert book record";
    cout<<"\n2. View all book record";
    cout<<"\n3. Search book record";
    cout<<"\n4. Delete book record";
    cout<<"\n5. Update book record";
    cout<<"\n6. Exit";
    cout<<"\n\nEnter your choice";
    cin>>choice;
    return choice;
}

void CRUD_Operation(){
        Book b1;
    char title[20];

     while(1){
       //  system("CLS"); 
        switch (menu2()) {
            case 1:
            b1.getBookData();
            b1.storeBook();
            cout<<"\nRecord inserted";
            break;
            case 2:
            b1.viewAllBooks();
            break;
            case 3:
            cout<<"\nEnter title of book to search";
            cin.ignore();
            cin.getline(title, 19);
            b1.searchBook(title);
            break;
            case 4:
            cout<<"\nEnter book title to delete record";
            cin.ignore();
            cin.getline(title, 19);
            b1.deleteBook(title);
            break;
            case 5:
            cout<<"\nEnter book title to update record";
            cin.ignore();
            cin.getline(title, 19);
            b1.updateBook(title);
            break;
            case 6:
            cout<<"\nThank you for using this application";
            exit(0);
            default :
            cout<<"\nInvalid choice";
        }
       system("pause");
     }
}

int Login(int choice){

    char p1[20], p2[20], pass[20], old_p[20], p[20];

      switch(choice)
		{
			case 1:
				{
                    ifstream fin;
                    fin.open("CodeSpeedy.txt",ios::in| ios::binary);
					cout<<"Enter your old password:";
                    cin.ignore();
                    cin.getline(old_p,sizeof(old_p));
					while(fin.getline(p, sizeof(p)))
					{						
						if(!strcmp(old_p, p))
						{
							fin.close();
							ofstream fout;
                            fout.open("CodeSpeedy.txt",ios::out| ios::binary);

							cout<<"Enter your new password:";
							cin.getline(p1, sizeof(p1));
							cout<<"Confirm your new password:";
							cin.getline(p2, sizeof(p2));        

							if(!strcmp(p1, p2))
							{
								fout<<p1;
								cout<<"Congrats! password change successfully"<<endl<<endl;
							}else{
                                cout<<"Passwords do not match!"<<endl<<endl;
                                fout<<p;
                            }
							fout.close();
							break;
						}
						else
						{
							cout<<"Please, enter valid password."<<endl<<endl;
						}
					}
					break;
				}
			case 2:
				{
                    ifstream fin;
                    fin.open("CodeSpeedy.txt",ios::in| ios::binary);
                    char s1[20];
                    fin.getline(s1, sizeof(s1));
                    cout<<"Plz Enter a password\n";
                    char check[20];
                    cin.ignore();
                    cin.getline(check, sizeof(check));
                    if(!strcmp(check, s1))
						{
							cout<<"Congrats! Access granted"<<endl<<endl;
                            CRUD_Operation();
							break;
						}
						else
						{
							cout<<"Sorry! Password is wrong"<<endl;
						}
                    fin.close();
					break;
				}
			default:
				cout<<"Enter a valid choice";
		}

}

void menu1(){
  
     while(1){
     system("CLS");
     int choice;
     cout<<"1.Change the password\n2.Login page to see the data\n3.Quit"<<endl;
	 cout<<"Enter your choice:";
	 cin>>choice;
     if(choice == 3) return ;
     Login(choice);  
     system("pause");
     }
     return ;

}

int main(){

        menu1();
        return 0;
}