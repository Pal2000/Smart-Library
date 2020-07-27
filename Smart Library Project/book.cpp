#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<ctype.h>

#define AdminUser "admin"
#define Adminpass "1234"
#define User "user"
#define Userpass "1234"


using namespace std;

//#####################################  CLASS - BOOK #################################################################################
class Book
{
	char aname[10];
	char bname[10];
	int id;
		public:
		void enterBook()
		{
			cout<<"\n Enter Book name:";
			cin>>bname;
			cout<<"\n Enter author name:";
			cin>>aname;
		    cout<<"\n Enter Book Id ";
			cin>>id;
		}
		void showBook()
		{
			cout<<"\n Name of Book:"<<bname;
			cout<<"\t Author name:"<<aname;
			cout<<"\t Id:"<<id;
		}
		int returnId()
		{
			return id;
		}

};

//##################################################### CLASS - DETAILS #########################################################

class Details
{
	char name[10];
	int regno,isId;
	char issue[10];
	public:
		void getinfo()
		{
			cout<<"\n Enter your name ";
			cin>>name;
			cout<<"\n Enter your Registration number ";
			cin>>regno;
			cout<<"\n Enter name of Book want to issue ";
			cin>>issue;
			cout<<"\n Enter Book Id ";
			cin>>isId;
		}
		void showinfo()
		{
			cout<<"\n Name of Student :"<<name;
			cout<<"\t Registration no. is :"<<regno;
			cout<<"\t Book Name :"<<issue;
			cout<<"\t Book Id :"<<isId;
		}
		int getregno()
		{
			return regno;
		}
	
};
//##################################################### CLASS - ADMIN ######################################################################
class ADMIN
{
	
	public:
		void addBook();
		void deleteBook();
		void searchBook();
		void updateBook();
		void viewBooks();
		void userRecord();
	
};
//*******************************************************  ADDING BOOKS********************************************  
void ADMIN::addBook()
{
	Book b[10];
	fstream ob1;
	int n;
	cout<<"\n How many books you want to add ?";
	cin>>n;
	ob1.open("LOB.dat",ios::app |ios::binary);
	for(int i=0;i<n;i++)
	{
	    b[i].enterBook();
		ob1.write((char *)&b[i],sizeof(b[i]));
	}
	cout<<"\n \t\t BOOK IS ADDED IN THE LIST !!!!";
	ob1.close();
}

//*******************************************************  DISPLAYING BOOKS ********************************************  
void ADMIN::viewBooks()
{
	fstream ob1;
	Book b1;
	int objects;
	int size=0;
	ob1.open("LOB.dat",ios::in |ios::binary);
	ob1.seekg(0,ios::end);
	size=ob1.tellp();
//	cout<<"\n file size = "<<size;
//	cout<<"\n  objects size= "<<sizeof(b1);
	objects=size/sizeof(b1);
	cout<<"\n Total books= "<<objects<<endl;
	if(objects==0)
	{
		cout<<"\n No Book Is Available\n";
	}
	ob1.seekg(0);
	for(int i=0;i<objects;i++)
	{
		ob1.read((char *)&b1,sizeof(b1));
	    b1.showBook();
	}
	ob1.close();
}

//*******************************************************  SEARCHING BOOKS********************************************
void ADMIN::searchBook()
{
	int BId,pos,found=0,size;
	cout<<"\n Enter Id of the Book you want to Search:";
	cin>>BId;
	
	Book b1,b2[10];
	fstream obj;
	obj.open("LOB.dat",ios::in | ios::binary);
	
	int o;
	obj.seekg(0,ios::end);
	size=obj.tellg();
//	cout<<"\n file size = "<<size;
//	cout<<"\n  objects size= "<<sizeof(b1);
    o=size/sizeof(b1);
//	cout<<"\n total books= "<<o;
	obj.seekg(0);
//	cout<<"\n pos in temp is "<<obj.tellg();
		
	
	for(int i=0;i<o;i++)
	{
		while(obj.read((char *)&b2[i],sizeof(b2[i])))
	    {
	        if(b2[i].returnId()==BId)
		    {
		    	pos=(i-1)-sizeof(b2[i]);
		    	obj.seekp(pos,ios::beg);
	            obj.read((char*)&b2[i],sizeof(b2[i]));
	            b2[i].showBook();
	            found=1;
 	        }
 	    }
 	}
 
	obj.close();
	
	if(found==0)
	{
		cout<<"\n Book Is Not Found !!";
	}	
}

//*******************************************************  UPDATING BOOKS********************************************

void ADMIN::updateBook()
{
	int BId,found=0,size;
	cout<<"\n Enter Id of the Book you want to Search:";
	cin>>BId;
	
	Book b1,b2[10];
	fstream obj;
	obj.open("LOB.dat",ios::out|ios::ate |ios::in| ios::binary);
	
	int o,loc;
	obj.seekg(0,ios::end);
	size=obj.tellg();
//	cout<<"\n file size = "<<size;
//	cout<<"\n  objects size= "<<sizeof(b1);
    o=size/sizeof(b1);
//	cout<<"\n total books= "<<o;
	obj.seekg(0);
	//cout<<"\n pos in temp is "<<obj.tellg();
		
	for(int i=0;i<o;i++)
	{
	
	while(obj.read((char *)&b2[i],sizeof(b2[i])))
	{
		for(int i=0;i<o;i++)
		{
		if(b2[i].returnId()==BId)
		{
			loc=obj.tellg()-sizeof(b2[i]);
			obj.seekp(loc,ios::beg);
			b2[i].enterBook();
			obj.write((char*)&b2[i],sizeof(b2[i]));
	        cout<<"\n Book Is Successfully Updated!!!!";
	        found=1;
	        break;
		}
	    }
	}
    }
  if(found==0)
  cout<<"\n Book Is Not Found";
	obj.close();	
}

//*******************************************************  DELETING BOOKS********************************************

void ADMIN::deleteBook()
{
	fstream ob1;
	ofstream ob2;
	Book b1,b2[10];
	int idBook,size;
	ob1.open("LOB.dat",ios::in |ios::binary);
	ob2.open("fak.dat",ios::out |ios::binary);
	cout<<"\n Enter Id of the Book ";
	cin>>idBook;
	int objects;
	ob1.seekg(0,ios::end);
	size=ob1.tellp();
	//cout<<"\n file size = "<<size;
	//cout<<"\n  objects size= "<<sizeof(b1);
    objects=size/sizeof(b1);
	//cout<<"\n total books= "<<objects;
	ob1.seekg(0);

	//cout<<"\n pos is "<<ob1.tellp();

	for(int i=0;i<objects;i++)
	{
		while(ob1.read((char *)&b2[i],sizeof(b2[i])))
		{
			if(b2[i].returnId()!=idBook)
			{
				ob2.write((char *)&b2[i],sizeof(b2[i]));
			}
		}
	}
	
	ob1.close();
	ob2.close();
	
/*	obj2.open("fak.dat",ios::in |ios::binary);
	int ooo;
	obj2.seekg(0,ios::end);
	size=obj2.tellg();
	cout<<"\n file size = "<<size;
	cout<<"\n  objects size= "<<sizeof(b1);
    ooo=size/sizeof(b1);
	cout<<"\n total books= "<<ooo;
	obj2.seekg(0);
	cout<<"\n pos in temp is "<<obj2.tellg();
		
	for(int i=0;i<ooo;i++)
	{
		obj2.read((char *)&b2[i],sizeof(b2[i]));
	    b2[i].showBook();
	}
	obj2.close();  */
	remove("LOB.dat");
	rename("fak.dat","LOB.dat");
    
}

//*********************************************************  USER RECORDS ***************************************************
void ADMIN::userRecord()
{
	Details dd;
	ifstream obj1;
	obj1.open("Records.dat",ios::binary);
	int objects,size;
	obj1.seekg(0,ios::end);
	size=obj1.tellg();
	//cout<<"\n file size = "<<size;
//	cout<<"\n  objects size= "<<sizeof(dd);
    objects=size/sizeof(dd);
	
	obj1.seekg(0);
//	cout<<"\n pos in temp is "<<obj1.tellg();
    if(objects==0)
    {
    	cout<<"\n 0 Book is Issued ";
	}
	else
	{
	cout<<"\n Total books issued = "<<objects<<endl;
    cout<<"\n Information about the users who issued the books :-";
	for(int i=0;i<objects;i++)
	{
		obj1.read((char *)&dd,sizeof(dd));
	    dd.showinfo();
	}
	obj1.close();  
    }
}


//############################################################# CLASS - USER ###########################################################
class USER:public ADMIN
{
	public:
		void issueBook();
		void returnBook();
		void findBook();
};

//********************************** issuing  Books******************************
void USER::issueBook()
{
	deleteBook();
	fstream ob1;
	Details dl;
	ob1.open("Records.dat",ios::out | ios::app |ios::binary);
	dl.getinfo();
	ob1.write((char *)&dl,sizeof(dl));
	ob1.close();
	cout<<"\n Book Is Issued To You!!";
	cout<<"\n\n Return It Within 7 days \n";
}

///*************************************** returning Books*******************************
void USER::returnBook()
{
	int Reg,size;
	cout<<"\n Enter Your Registration Number";
	cin>>Reg;
	Details d,d2[10];
	fstream obj,obj2;
	obj.open("Records.dat",ios::in |ios::binary);
	obj2.open("temp.dat",ios::out |ios::binary);
	int objects;
	obj.seekg(0,ios::end);
	size=obj.tellp();
//	cout<<"\n file size = "<<size;
//	cout<<"\n  objects size= "<<sizeof(d);
    objects=size/sizeof(d);
//	cout<<"\n total books= "<<objects;
	obj.seekg(0);

//	cout<<"\n pos is "<<obj.tellp();

	for(int i=0;i<objects;i++)
	{
		while(obj.read((char *)&d2[i],sizeof(d2[i])))
		{
			if(d2[i].getregno()!=Reg)
			{
				obj2.write((char *)&d2[i],sizeof(d2[i]));
			}
		}
	}
	
	obj.close();
	obj2.close();
	
	remove("Records.dat");
	rename("temp.dat","Records.dat");
/// Adding The Book Again After Returning 
	Book b;
	fstream ob1;
	ob1.open("LOB.dat",ios::app |ios::binary);
	b.enterBook();
	ob1.write((char *)&b,sizeof(b));
	
	ob1.close();
	cout<<"\n Book Is Returned By You \n";
}

//************************************* find Book*************************************************
void USER::findBook()
{
	viewBooks();
	cout<<"\n\n";
	searchBook();
}


//###############################################    MAIN()    ##############################################################################

int main()
{
	system( "color B5");
	cout<<"\n\n******************************************************************************* SMART  LIBRARY  *******************************************************************************************************************";
	int status;
	char adname[10],uname[10];
	char adpass[10],upass[10];
	cout<<"\n\n\t Login As A  :";
	cout<<"\n\n\t1. admin   or   2.user\n";
	cin>>status;


switch(status)
{
	A:case 1:///************************case 1****************
	{
		
	cout<<"\n\t\t Enter your Id ";
    cin>>adname;
	cout<<"\n\t\t Enter your Password ";
	cin>>adpass;
		
	if(strcmp(adname,AdminUser)==0  && strcmp(adpass,Adminpass)==0)
	{
	
	ADMIN objAD;
	int adminch;
	cout<<"\n\t\t\t WELCOME ADMIN !!!"<<endl;
	cout<<"\n\n";
	cout<<"1. ADD a book";
	cout<<"\n2. SEARCH a book";
	cout<<"\n3. DELETE a book";
	cout<<"\n4. UPDATE a book";
	cout<<"\n5. VIEW a books";
	cout<<"\n6. userRecord";
	cout<<"\n7. Exit";
	
	
	while(1)
	{
		
		cout<<"\n\n\n What do you want to do ?"<<endl;
		cin>>adminch;
		switch(adminch)
		{
			case 1:
				objAD.addBook();
				break;
			case 2:
				objAD.searchBook();
				break;
			case 3:
				objAD.deleteBook();
				cout<<"\n\t\t  BOOK IS DELETED !!!!";
				break;
			case 4:
				objAD.updateBook();
				break;
			case 5:
				objAD.viewBooks();
				break;
			case 6:
				objAD.userRecord();
				break;
			case 7:
				exit(0);
				break;
			default:
				cout<<"\n Please enter valid choice";
				break;
		}
		
    }
    }// IF ENDS
    else
    {
    	cout<<"\n\n Wrong Id and Password"<<endl;
    	goto A;
	}
    break;
    } // *************case1 ends*****************************

//----------------------------------------------------------	
	B:case 2:
	{
	cout<<"\n\t\t Enter your Id ";
	cin>>uname;
	cout<<"\n\t\t Enter your Password ";
	cin>>upass;
	if(strcmp(uname,User)==0  && strcmp(upass,Userpass)==0)
	{
	USER objUS;
	int userch;
	cout<<"\n\t\t\t WELCOME USER !!!"<<endl;
	cout<<"\n\n";
	cout<<"1. ISSUE a book";
	cout<<"\n2. RETURN a book";
	cout<<"\n3. SEARCH a books";
	cout<<"\n4. Exit";
	
	
	while(1)
	{
		
		cout<<"\n\n\n What do you want to do ?"<<endl;
		cin>>userch;
		switch(userch)
		{
			case 1:
				objUS.issueBook();
				break;
			case 2:
	    	objUS.returnBook();
				break;
			case 3:
				objUS.findBook();
				break; 
			case 4:
				exit(0);
				break;
			default:
				cout<<"\n Please enter valid choice";
				break;
		}
		
    }
    } //If Closes
    else
    {
    	cout<<"\n\n Wrong Id and Password"<<endl;
    	goto B;
	}
    break;
    }//***********************case 2 ends******************

    default:
    {
	cout<<"\n\n Please write valid choice"<<endl;
	break;
    }
}  //***********Switch ends********************
return 0;
}
