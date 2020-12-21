//typedef 对于c来说可以省略：typedef struct T{} A,可以叫做A，但是在c++中可以省略
/*
   首先定义所需要的数据结构，本次系统需要数据结构两个：图书数据结构，系统会员用户数据结构
*/
typedef struct bookdata
{
    char isbn[12];  //isbn 12b
    char name[20];  
    char publisher[20]; 
    char author[20];
    short ver;          //版次
    float price;
    short count;      //库存
 }BOOK;
typedef struct memberdata
{
    char name[20];
    char address[20];
    short borrow; //借阅数
    char isbn1[12];
    char isbn2[12];
    char isbn3[12];   //最多可以借三本书
}MEMBER;
