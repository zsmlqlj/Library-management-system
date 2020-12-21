#define _CRT_SECURE_NO_WARNINGS
#include"subfunction.h"
#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<iomanip>

const char* _DATA_FILE_ = "book.dat";
const char* _TEMP_FILE_ = "book.tmp";
const char* _MEMBER_FILE_ = "member.dat";
using namespace std;
int inputbook(void)
{
	int rtn = 1;
	BOOK book;
	char check = 'n';
	FILE* fp;
	fp = fopen(_DATA_FILE_, "ab");  //追加方式打开文件
	if (fp == NULL)
	fp = fopen(_DATA_FILE_, "wb");//写方式打开文件
	if (fp == NULL)
		rtn = 0;
	else
	{
		do 
		{
			cout << "录入图书" << endl;
			cout << "ISBN--" << endl;
			cin >> book.isbn;
			cout << "书名" << endl;
			cin >> book.name;
			cout << "出版社" << endl;
			cin >> book.publisher;
			cout << "作者" << endl;
			cin >> book.author;
			cout << "版次" << endl;
			cin >> book.ver;
			cout << "价格" << endl;
			cin >> book.price;
			cout << "库存" << endl;
			cin >> book.count;
			cout << "确认保存（y/n）" << endl; \
				cin >> check;
			if (check == 'y' || check == 'Y')
				fwrite(&book, sizeof(book), 1, fp);
			cout << "继续录入嘛？" << endl;
			cin >> check;
		} while (check == 'y' || check == 'Y');
	}
	//v0.3添加了关闭文件流
	fclose(fp);
	return rtn;
}
int deletebook(void)
{
	char check = 'n';
	int rtn = 1;
	BOOK book;
	char ISBN[12];
	do {
		cout << "请输入ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			rtn = 0;
			cout << "没有找到" << endl;
		}
		else
		{
			rtn = removebook(ISBN);
			if (rtn == 0)
				cout << "删除失败" << endl;
		}
		cout << "继续吗（n/y）？" << endl;
		cin >> check;
	} while (check == 'Y' || check == 'y');
	return rtn;
}
BOOK findbook(char* ISBN)
{
	BOOK book;
	bool found = false;
	FILE* fp;
	fp = fopen(_DATA_FILE_, "rb");                                //读方式打开文件
	book.count = -1;
	if (fp != NULL)
	{
		do {
			fread(&book, sizeof(book), 1, fp);
			if (strcmp(book.isbn, ISBN))   //比较函数，相同返回零，str1>str2，返回正数，str1<str2，返回负数
			{
				found = true;
				break;
			}
			//以一个book长度为单位进行遍历寻找,fread读取一次过后，指针位置自动偏移一个sizeof(book)
		} while (!feof(fp));      //feof查找文件结尾，结尾返回非零值，未结尾，返回零
		if (!found)
			book.count = -1;
		fclose(fp);			//进行文件关闭释放
	}
	return book;
}
int removebook(char* ISBN)        //不同ISBN的不拷贝，其他都重写拷贝
{
	BOOK book;
	FILE* fp;
	FILE* temp;
	temp = fopen(_TEMP_FILE_, "w");
	fp = fopen(_DATA_FILE_, "rb");
	if (fp != NULL)
	{
		fread(&book, sizeof(book), 1, fp);
		do
		{
			if (strcmp(book.isbn, ISBN))
			{
				fwrite(&book, sizeof(book), 1, temp); //块写
			}
			fread(&book, sizeof(book), 1, fp);
		} while (!feof(fp));
		fclose(fp);
		fclose(temp);
		remove(_DATA_FILE_);
		rename(_TEMP_FILE_, _DATA_FILE_);
	}
	return 1;
}
int searchbook(void)
{
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'n';
	do {
		cout << "请输入ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			cout << "没找到" << endl;
		}
		else
		{
			cout << "ISBN=" << book.isbn << endl;
			cout << "name=" << book.name << endl;
			cout << "publisher=" << book.publisher << endl;
			cout << "author=" << book.author << endl;
			cout << "ver=" << book.ver << endl;
			cout << "price=" << book.price << endl;
			cout << "count" << book.count << endl;
		}
		cout << "继续查询嘛？(Y/N)" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
	return rtn;
}
int modifybook(void)               //修改自定义数据类型book
{
	cout << "修改图书" << endl;        //此函数负责完全删除重新录入图书，也可改动为改动所需，例如ver
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'n';
	do
	{
		cout << "请输入ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "没找到" << endl;
		else
		{
			cout << "ISBN=" << book.isbn << endl;
			cout << "name=" << book.name << endl;
			cout << "publisher=" << book.publisher << endl;
			cout << "author=" << book.author << endl;
			cout << "ver=" << book.ver << endl;
			cout << "price=" << book.price << endl;
			cout << "count" << book.count << endl;
			cout << "修改吗(Y/N)" << endl;
			cin >> check;
			if (check == 'y' || check == 'Y')
			{
				removebook(ISBN);
				inputbook();
			}
		}	
		cout << "继续嘛？（Y/N）" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
		return rtn;
}
void mmbook(void)
//v0.3 修复了图书只有一本时，列出图书显示异常的bug
//v0.2 更改了输出格式，使显示更加美观
{
	FILE* fp;
	BOOK bk;
	fp = fopen(_DATA_FILE_, "rb");
	cout <<left<<setw(16)<< "ISBN"<< left << setw(16) << "NAME"<< left << setw(16) << "PUBLISHER"
		<< left << setw(16) << "AUTHOR"<< left << setw(16) << "VER"<<
		left << setw(16) << "PRICE"<< left << setw(16) << "VER"<< left << setw(16) << "PRICE"
		<< left << setw(16) <<
		"COUNT" << endl;
	fread(&bk, sizeof(bk), 1, fp);
	do
	{
		cout << left << setw(16) << bk.isbn  << left << setw(16) << bk.name 
			<< left << setw(16) << bk.publisher << left << setw(16) << bk.author <<
			left << setw(16)<< bk.ver<< left << setw(16) << bk.price
			<< left << setw(16) << bk.ver << left << setw(16) << bk.price 
			<< left << setw(16) << bk.count<< left << setw(16) << bk.count << endl;
		fread(&bk, sizeof(bk), 1, fp);
	} while (!feof(fp));
	fclose(fp);
}
int lendbook()
{
	cout << "借阅图书" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	cout << "输入图书ISBN" << endl;
	cin >> ISBN;
	cout << "输入姓名" << endl;
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "图书不存在" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "图书不存在" << endl;
		else
		{
			if (member.borrow > 3)
				cout << "借阅超限，不得借阅" << endl;
			else 
			{
				if (book.count == 0)
					cout << "书已借完" << endl;
				else
				{
					member.borrow++;
					book.count--;
					if (member.isbn1[0] == '\0')
						strcpy(member.isbn1, book.isbn);
					else if (member.isbn2[0] == '\0')
						strcpy(member.isbn2, book.isbn);
					else
						strcpy(member.isbn3, book.isbn);
					removemember(member.name);
					memberborrow(member);
					removebook(book.isbn);
					lendbook(book);
				}
			}
		}
	}
	return 0;
}
int returnbook(void)
{
	cout << "归还图书" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	bool ok = false;
	cout << "请输入图书ISBN" << endl;
	cin >> ISBN;
	cout << "请输入借阅者姓名" << endl;
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "图书不存在" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "会员不存在" << endl;
		else
		{
			if (!strcmp(member.isbn1, book.isbn))
			{
				member.isbn1[0] = '\0';   //   赋值为空
				ok = true;
			}
			else if (!strcmp(member.isbn2, book.isbn))      //strcmp中   str1=str2，返回零
			{
				member.isbn2[0] = '\0';
				ok = true;
			}
			else if (!strcmp(member.isbn3, book.isbn))
			{
				member.isbn3[0] = '\0';
				ok = true;
			}
			else cout << "该会员没有借该书" << endl;
			if (ok)
			{
				member.borrow--;
				book.count++;
				removemember(member.name);
				removebook(book.isbn);
				lendbook(book);
			}
		}
	}
	return 0;
}
void listmember(void)
//v0.3 添加了EOF判断，修复了重复输出member的bug
{
	FILE* fp;
	MEMBER member;
	fp = fopen(_MEMBER_FILE_, "rb");
	cout<<left<<setw(10) << "姓名" << left << setw(10) <<"地址"<< left << setw(10) << "借阅数"<< left << setw(10) << " isbn1"<< left << setw(10) << "isbn2"<< left << setw(10) << "isbn3" << endl;
	fread(&member, sizeof(member), 1, fp);
	while (!feof(fp))
	{
		cout << left << setw(10) << member.name << left << setw(10) << member.address << left << setw(10) << member.borrow << left << setw(10) << member.isbn1 << left << setw(10) << member.isbn2 << left << setw(10) << member.isbn3 << left << setw(10) << endl;
		if (fgetc(fp) == EOF)
			break;
	}
	fclose(fp);   //*为取值，&为取地址，互为逆运算
}
int inputmember(void)
{
	cout << "注册会员" << endl;
	int rtn = 1;
	int renamertn = 1;
	MEMBER member;
	char check = 'n';
	//char* rename;
	char rename[20];
	//rename = (char*)malloc(10 * sizeof(char*));
	FILE* fp;
	fp = fopen(_MEMBER_FILE_, "ab");   //追加方式打开文件
	if (fp == NULL)
	{
		fp = fopen(_MEMBER_FILE_, "wb");
	cout << "写方式打开文件";
	}
	if (fp == NULL)
		rtn = 0;
	else
	{
		do
		{
			cout << "录入会员" << endl;
			cout << "姓名" << endl;
			cin >> rename;          
											   //v0.2加入了判断重复姓名注册失败的判断
			                                   //v0.3修复了feof()无限循环的bug,修复重复录入循环bug
			do
			{
				if (fgetc(fp) !=EOF)
				{
					if (!strcmp(rename, member.name))
					{
						cout << "姓名重复，不允许重复注册，注册失败，请重新注册" << endl;
						renamertn = 0;
						break;
					}
					fread(&member, sizeof(member), 1, fp);
					cout << "判断读取中，请等待" << endl;
				}
				else
					break;
			} while (!feof(fp));
			if (renamertn != 0)
			{
				cout << "地址" << endl;
				cin >> member.address;
				member.borrow = 0;
				member.isbn1[0] = '\0';
				member.isbn2[0] = '\0';
				member.isbn3[0] = '\0';
				cout << "是否保存（y/n）" << endl;
				cin >> check;
				if (check == 'Y' || check == 'y')
				{
					fwrite(&member, sizeof(member), 1, fp);  //块写
				}
				cout << "继续录入信息吗？" << endl;
				cin >> check;
			}
			else
			{
				cout << "注册失败，重新录入信息吗？" << endl;
				cin >> check;
			}
		} while (check == 'Y'||check=='y');
	}
	fclose(fp);
	return rtn;
	return 0;
}
int deletemember(void)
{
	cout << "注销会员" << endl;
	char check = 'n';
	int rtn = 1;
	char name[20];
	MEMBER member;
	do
	{
		cout << "请输入姓名" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
		{
			rtn = 0;
			cout << "没有找到" << endl;
		}
		else
		{
			rtn = removemember(name);
			if (rtn == 0)
				cout << "删除失败" << endl;
		}
		cout << "继续吗(Y/N)" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
	return rtn;
}
int searchmember(void)
{
	cout << "查询会员" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'n';
	do
	{
		cout << "请输入姓名:" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "没找到" << endl;
		else
		{
			cout << left << setw(10) << "姓名" << left << setw(10) << "地址" << left << setw(10) << "借阅数" << left << setw(10) <<
				"isbn1" << left << setw(10) << "isbn2" << left << setw(10) << "isbn3" << endl;
			cout<< left << setw(10) << member.name << left << setw(10) << member.address << left << setw(10) << member.borrow<< left << setw(10) <<
				member.isbn1<< left << setw(10) << member.isbn2 << left << setw(10) << member.isbn3 << endl;
			cout << "继续查询嘛（Y/N）？" << endl;
			cin >> check;
		}
	} while (check=='y'||check=='Y');
	return rtn;
}
MEMBER findmember(char* name)
{
	MEMBER member;
	bool found = false;
	FILE* fp;
	fp = fopen(_MEMBER_FILE_, "rb");
	member.borrow = -1;
	if (fp != NULL)
	{
		fread(&member, sizeof(member), 1, fp);
		/*
		fread:从给定输入流stream读取最多count个对象到数组buffer中
		(相当于以对每个对象调用count次fgetc），
		把buffer当作unsigned char数组并顺序保存结果。流的文件位置指示器前进读取的字节数。
		fread( void *restrict buffer, size_t size, size_t count, FILE *restrict stream )
		*/
		do 
		{
			if (!strcmp(member.name, name))
			{
				found = true;
				break;
			}
			fread(&member, sizeof(member), 1, fp);
		} while (!feof(fp));
		if (!found)
			member.borrow = -1;
		fclose(fp);
	}
	return member;           //直接返回member
}
int removemember(char* name)
{
	MEMBER member;
	FILE* fp;
	FILE* temp;
	temp = fopen(_TEMP_FILE_, "w");           //写方式打开文件
	fp = fopen(_MEMBER_FILE_, "rb");
	if (fp != NULL)
	{
		fread(&member, sizeof(member), 1, fp);
		do
		{
			if (strcmp(member.name, name))
			{
				fwrite(&member, sizeof(member), 1, temp);
			}
		} while (!feof(fp));
		fclose(fp);
		fclose(temp);
		remove(_MEMBER_FILE_);
		rename(_TEMP_FILE_, _MEMBER_FILE_);
	}
	return 1;
}
int memberborrow(MEMBER member)
{
	int rtn = 1;
	FILE* fp;
	fp = fopen(_MEMBER_FILE_, "ab");  //追加方式打开
	if (fp == NULL)
		fp = fopen(_MEMBER_FILE_, "wb");
	if(fp==NULL)
		rtn = 0;
	else
	{
		fwrite(&member, sizeof(member), 1, fp);
	}
	fclose(fp);
	return rtn;
	return 0;
}
int lendbook(BOOK book)
{
	int rtn = 1;
	FILE* fp;
	fp = fopen(_DATA_FILE_, "ab");
	if (fp == NULL)
	fp = fopen(_DATA_FILE_, "wb");
	if (fp == NULL)
	rtn = 0;
	else 
	{
		fwrite(&book, sizeof(book), 1, fp);
	}
	return rtn;
	fclose(fp);
}
int modifymember(void)
{
	cout << "修改会员" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'n';
	do 
	{
		cout << "请输入姓名" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "没有找到" << endl;
		else
		{
			cout << "姓名=" << member.name << endl;
			cout << "地址=" << member.address << endl;
			cout << "借阅数=" << member.borrow << endl;
			cout << "isbn1=" << member.isbn1 << endl;
			cout << "isbn2=" << member.isbn2 << endl;
			cout << "isbn3=" << member.isbn3 << endl;
			cout << "修改嘛？" << endl;
			cin >> check;
			if (check == 'y' || check == 'Y')
			{
				removemember(name);
				inputmember();
			}
		}
		cout << "继续嘛（Y/N）？" << endl;
		cin >> check;
	}
	while (check=='y'||check=='Y');
	return rtn;
}