#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<graphics.h>

class data
{
public:
char name[30];
int roomno;
char PHONENO[11];
int NO_OF_DAYS;
int total_no_rooms;
int price,no;
char AC;
data()
{
roomno=0;
strcpy(name,"");
PHONENO;
NO_OF_DAYS =0;
price=0;
}

void enter_name()
{
cout<<"\n Enter room no.                   : ";
cin>>roomno;
cout<<"\n Enter customer name              : ";
gets(name);
cout<<"\n Enter PHONENO                    : ";
gets(PHONENO);
cout<<"\n Enter the no. of days you\n    want to accomodate the room   : ";
cin>>NO_OF_DAYS;
prices();
}
void show_record()
{
cout<<"\n room No.           : "<<roomno;
cout<<"\n customer name      : "<<name;
cout<<"\n Phone no.          : "<<PHONENO;
cout<<"\n No. of days        : "<<NO_OF_DAYS;
cout<<"\n";
}
void show_bill()
{
cout<<"\n Room no.           :"<<roomno;
cout<<"\nCustomer name       :"<<name;
cout<<"\nPhone no.           :"<<PHONENO;
cout<<"\nNo. of days         :"<<NO_OF_DAYS;
cout<<"\nPrice               : Rs."<<price;
cout<<"\n";
}
void prices()
{
char AC;
cout<<"\nDo you want your room to \n          be air contioned?(y/n)  :  ";
cin>>AC;
if(AC=='y'||AC=='Y')
{
price=NO_OF_DAYS*1500;
}
else
{
price=NO_OF_DAYS*1000;
}
}
int getroomno()
{
return roomno;
}
int totalprice()
{
return price;
}
char* get_name()
{
return name;
}

void modify_data()
{
clrscr();
cout<<"\n Enter new data for modification   \n";
cout<<"\n Enter your name     : ";
gets(name);
cout<<"\n Enter Phone no.     : ";
cin>>PHONENO;
cout<<"\n Enter no. of days   : ";
cin>>NO_OF_DAYS;
prices();
}
};
data d;
fstream file;
fstream file1;

int getno()
{
file.read((char *)&d,sizeof(d));
return d.no;
}

void insert()
{
clrscr();
textbackground(WHITE);
textcolor(BLUE);
int i,p;
file.open("record.dat",ios::in|ios::app|ios::binary);
cout<<"\n:::::::::::::::::: INSERT NEW RECORD ::::::::::::::::::\n ";
cout<<"\n How many record you want to enter     : ";
cin>>d.no;
file.write((char *)&d,sizeof(d));
p=getno();
if(p<=d.total_no_rooms)
{
for(i=1;i<=p;i++)
{
d.enter_name();
file.write((char*)&d,sizeof(d));
}
file.close();
}
else
{
cout<<"\n Sorry...All rooms are occupied... ";
}
}
void check_available_rooms()
{
cout<<"\n::::::::::::::::: TOTAL NO. OF AVALABLE ROOMS :::::::: \n";
int temp=d.total_no_rooms;
int p=getno();
temp=temp-p;
cout<<"Total no. of rooms available : "<<temp;
}
void display()
{
clrscr();
file.open("record.dat",ios::in|ios::binary);
cout<<"\n:::::::::::::::::: DISPLAY RECORDS ::::::::::::::::::";
file.read((char*)&d,sizeof(d));
while(file)
{
d.show_record();
file.read((char*)&d,sizeof(d));
}
file.close();
}

void search()
{
clrscr();
int p,r,srch=0;
file.open("record.dat",ios::in|ios::binary);
cout<<"\n:::::::::::::::::: SEARCH RECORD ::::::::::::::::::\n";
cout<<"\n Enter the room no. you are searching for   : ";
cin>>r;
file.seekg(0);
file.read((char*)&d,sizeof(d));
while(file)
{
p=d.getroomno();
if(r==p)
{
d.show_record();
srch=1;
break;
}
else
{
file.read((char*)&d,sizeof(d));
}
}
file.close();
if(srch==0)
{
cout<<"\n There is no such record  ";
}
}
void bill()
{
clrscr();
int k,l,m=0;
file.open("record.dat",ios::in|ios::binary);
cout<<"\n:::::::::::::::::::BILL::::::::::::::::::::\n";
cout<<"Enter room no. to show the bill    :";
cin>>l;
file.seekg(0);
file.read((char*)&d,sizeof(d));
while(file)
{
k=d.getroomno();
if(l==k)
{
d.show_bill();
m=1;
break;
}
else
{
file.read((char*)&d,sizeof(d));
}
}
file.close();
if(m==0)
{
cout<<"\nNo such record";
}
}
void modify()
{
clrscr();
int posi=0,got=0,dmd=0;
cout<<"\n:::::::::::::::::: MODIFY RECORD ::::::::::::::::::\n";
cout<<"\n Enter the room no. whose record to be modified    : ";
cin>>dmd;
int ifdata=1;
file.open("record.dat",ios::in|ios::out|ios::binary);
posi=file.tellg();
while(file)
{
file.read((char*)&d,sizeof(d));
got=d.getroomno();
if(dmd==got)
{
file.seekg(posi);
d.modify_data();
ifdata=2;
file.write((char*)&d,sizeof(d));
break;
}
posi=file.tellg();
}
file.close();
if(ifdata==1)
{
cout<<"\n           Data not available for modification         ";
}
}

void delete_record()
{
clrscr();
int o,p;
int remove_record=0,code_get=0;
cout<<"\n:::::::::::::::::: DELETE RECORD ::::::::::::::::::\n";
cout<<"\n Enter the room no. whose record to be deleted   : ";
cin>>remove_record;
file.open("record.dat",ios::in|ios::out|ios::binary);
file1.open("tempo.dat",ios::in|ios::out|ios::binary);
file.seekg(0);
while(file)
{
file.read((char*)&d,sizeof(d));
code_get=d.getroomno();
if(remove_record==code_get)
{
cout<<" ";
}
else
{
file1.write((char*)&d,sizeof(d));
}
}
file.close();
file1.close();
remove("record.dat");
rename("tempo.dat","record.dat");
cout<<"\n\n Record deleted...";
getno();
}
void main()
{
clrscr();
textbackground(YELLOW);
textcolor(BLACK);
cout<<"\n\n\t\t R.M.K COLLEGE OF ENGINEERING AND TECHNOLOGY";
cout<<"\n\t   =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*";
cout<<"\n\n\t\t\t  WELCOME TO OUR C++ PROJECT ";
cout<<"\n\t\t     =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*";
cout<<"\n\n\n\t TOPIC :- HOTEL MANAGEMENT";
cout<<"\n\n\n\t By    :- \n\t\t SOWMYA.V \n\t\t SHAKTHI.A.S \n\t\t V.SARASWATHY \n\t\t D.VIDHYAVARSHINI";
getch();
clrscr();
int choice;
char pw[8];
cout<<"\nEnter password : ";
gets(pw);
if(strcmp(pw,"abc")==0)
{
char ans='n';
cout<<"Enter total no. of rooms available in your hotel : ";
cin>>d.total_no_rooms;
file.write((char *)&d,sizeof(d));
do
{
clrscr();
cout<<"\n=*=*=*=*=*=*=*=*=* HOTEL MANAGEMENT*=*=*=*=*=*=*=*=*=*";
cout<<"\n 1.CHECK AVAILABLE ROOMS \n 2.INSERT RECORD \n 3.DISPLAY RECORD \n 4.SEARCH RECORD \n 5.MODIFY RECORD  \n 6.SHOW BILL\n 7.DELETE RECORD \n 8.EXIT  ";
cout<<"\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*";
cout<<"\n Enter any one of the options (1-8) : ";
cin>>choice;
cout<<"\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*";
switch(choice)
{
case 1: check_available_rooms();
break;
case 2: insert();
break;
case 3: display();
break;
case 4: search();
break;
case 5: modify();
break;
case 6: bill();
break;
case 7: delete_record();
break;
case 8: exit(0);
break;
}
cout<<"\n=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*";
cout<<"\n\n Do you want to choose any other option ? (y/n): ";
cin>>ans;
clrscr();
}
while(ans=='y'||ans=='Y');
}
else
{
cout<<"\nInvalid password...  ";
}
getch();
}

