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
	fp = fopen(_DATA_FILE_, "ab");  //׷�ӷ�ʽ���ļ�
	if (fp == NULL)
	fp = fopen(_DATA_FILE_, "wb");//д��ʽ���ļ�
	if (fp == NULL)
		rtn = 0;
	else
	{
		do 
		{
			cout << "¼��ͼ��" << endl;
			cout << "ISBN--" << endl;
			cin >> book.isbn;
			cout << "����" << endl;
			cin >> book.name;
			cout << "������" << endl;
			cin >> book.publisher;
			cout << "����" << endl;
			cin >> book.author;
			cout << "���" << endl;
			cin >> book.ver;
			cout << "�۸�" << endl;
			cin >> book.price;
			cout << "���" << endl;
			cin >> book.count;
			cout << "ȷ�ϱ��棨y/n��" << endl; \
				cin >> check;
			if (check == 'y' || check == 'Y')
				fwrite(&book, sizeof(book), 1, fp);
			cout << "����¼���" << endl;
			cin >> check;
		} while (check == 'y' || check == 'Y');
	}
	//v0.3����˹ر��ļ���
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
		cout << "������ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			rtn = 0;
			cout << "û���ҵ�" << endl;
		}
		else
		{
			rtn = removebook(ISBN);
			if (rtn == 0)
				cout << "ɾ��ʧ��" << endl;
		}
		cout << "������n/y����" << endl;
		cin >> check;
	} while (check == 'Y' || check == 'y');
	return rtn;
}
BOOK findbook(char* ISBN)
{
	BOOK book;
	bool found = false;
	FILE* fp;
	fp = fopen(_DATA_FILE_, "rb");                                //����ʽ���ļ�
	book.count = -1;
	if (fp != NULL)
	{
		do {
			fread(&book, sizeof(book), 1, fp);
			if (strcmp(book.isbn, ISBN))   //�ȽϺ�������ͬ�����㣬str1>str2������������str1<str2�����ظ���
			{
				found = true;
				break;
			}
			//��һ��book����Ϊ��λ���б���Ѱ��,fread��ȡһ�ι���ָ��λ���Զ�ƫ��һ��sizeof(book)
		} while (!feof(fp));      //feof�����ļ���β����β���ط���ֵ��δ��β��������
		if (!found)
			book.count = -1;
		fclose(fp);			//�����ļ��ر��ͷ�
	}
	return book;
}
int removebook(char* ISBN)        //��ͬISBN�Ĳ���������������д����
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
				fwrite(&book, sizeof(book), 1, temp); //��д
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
		cout << "������ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			cout << "û�ҵ�" << endl;
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
		cout << "������ѯ�(Y/N)" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
	return rtn;
}
int modifybook(void)               //�޸��Զ�����������book
{
	cout << "�޸�ͼ��" << endl;        //�˺���������ȫɾ������¼��ͼ�飬Ҳ�ɸĶ�Ϊ�Ķ����裬����ver
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'n';
	do
	{
		cout << "������ISBN" << endl;
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "û�ҵ�" << endl;
		else
		{
			cout << "ISBN=" << book.isbn << endl;
			cout << "name=" << book.name << endl;
			cout << "publisher=" << book.publisher << endl;
			cout << "author=" << book.author << endl;
			cout << "ver=" << book.ver << endl;
			cout << "price=" << book.price << endl;
			cout << "count" << book.count << endl;
			cout << "�޸���(Y/N)" << endl;
			cin >> check;
			if (check == 'y' || check == 'Y')
			{
				removebook(ISBN);
				inputbook();
			}
		}	
		cout << "�������Y/N��" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
		return rtn;
}
void mmbook(void)
//v0.3 �޸���ͼ��ֻ��һ��ʱ���г�ͼ����ʾ�쳣��bug
//v0.2 �����������ʽ��ʹ��ʾ��������
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
	cout << "����ͼ��" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	cout << "����ͼ��ISBN" << endl;
	cin >> ISBN;
	cout << "��������" << endl;
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "ͼ�鲻����" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "ͼ�鲻����" << endl;
		else
		{
			if (member.borrow > 3)
				cout << "���ĳ��ޣ����ý���" << endl;
			else 
			{
				if (book.count == 0)
					cout << "���ѽ���" << endl;
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
	cout << "�黹ͼ��" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	bool ok = false;
	cout << "������ͼ��ISBN" << endl;
	cin >> ISBN;
	cout << "���������������" << endl;
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "ͼ�鲻����" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "��Ա������" << endl;
		else
		{
			if (!strcmp(member.isbn1, book.isbn))
			{
				member.isbn1[0] = '\0';   //   ��ֵΪ��
				ok = true;
			}
			else if (!strcmp(member.isbn2, book.isbn))      //strcmp��   str1=str2��������
			{
				member.isbn2[0] = '\0';
				ok = true;
			}
			else if (!strcmp(member.isbn3, book.isbn))
			{
				member.isbn3[0] = '\0';
				ok = true;
			}
			else cout << "�û�Աû�н����" << endl;
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
//v0.3 �����EOF�жϣ��޸����ظ����member��bug
{
	FILE* fp;
	MEMBER member;
	fp = fopen(_MEMBER_FILE_, "rb");
	cout<<left<<setw(10) << "����" << left << setw(10) <<"��ַ"<< left << setw(10) << "������"<< left << setw(10) << " isbn1"<< left << setw(10) << "isbn2"<< left << setw(10) << "isbn3" << endl;
	fread(&member, sizeof(member), 1, fp);
	while (!feof(fp))
	{
		cout << left << setw(10) << member.name << left << setw(10) << member.address << left << setw(10) << member.borrow << left << setw(10) << member.isbn1 << left << setw(10) << member.isbn2 << left << setw(10) << member.isbn3 << left << setw(10) << endl;
		if (fgetc(fp) == EOF)
			break;
	}
	fclose(fp);   //*Ϊȡֵ��&Ϊȡ��ַ����Ϊ������
}
int inputmember(void)
{
	cout << "ע���Ա" << endl;
	int rtn = 1;
	int renamertn = 1;
	MEMBER member;
	char check = 'n';
	//char* rename;
	char rename[20];
	//rename = (char*)malloc(10 * sizeof(char*));
	FILE* fp;
	fp = fopen(_MEMBER_FILE_, "ab");   //׷�ӷ�ʽ���ļ�
	if (fp == NULL)
	{
		fp = fopen(_MEMBER_FILE_, "wb");
	cout << "д��ʽ���ļ�";
	}
	if (fp == NULL)
		rtn = 0;
	else
	{
		do
		{
			cout << "¼���Ա" << endl;
			cout << "����" << endl;
			cin >> rename;          
											   //v0.2�������ж��ظ�����ע��ʧ�ܵ��ж�
			                                   //v0.3�޸���feof()����ѭ����bug,�޸��ظ�¼��ѭ��bug
			do
			{
				if (fgetc(fp) !=EOF)
				{
					if (!strcmp(rename, member.name))
					{
						cout << "�����ظ����������ظ�ע�ᣬע��ʧ�ܣ�������ע��" << endl;
						renamertn = 0;
						break;
					}
					fread(&member, sizeof(member), 1, fp);
					cout << "�ж϶�ȡ�У���ȴ�" << endl;
				}
				else
					break;
			} while (!feof(fp));
			if (renamertn != 0)
			{
				cout << "��ַ" << endl;
				cin >> member.address;
				member.borrow = 0;
				member.isbn1[0] = '\0';
				member.isbn2[0] = '\0';
				member.isbn3[0] = '\0';
				cout << "�Ƿ񱣴棨y/n��" << endl;
				cin >> check;
				if (check == 'Y' || check == 'y')
				{
					fwrite(&member, sizeof(member), 1, fp);  //��д
				}
				cout << "����¼����Ϣ��" << endl;
				cin >> check;
			}
			else
			{
				cout << "ע��ʧ�ܣ�����¼����Ϣ��" << endl;
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
	cout << "ע����Ա" << endl;
	char check = 'n';
	int rtn = 1;
	char name[20];
	MEMBER member;
	do
	{
		cout << "����������" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
		{
			rtn = 0;
			cout << "û���ҵ�" << endl;
		}
		else
		{
			rtn = removemember(name);
			if (rtn == 0)
				cout << "ɾ��ʧ��" << endl;
		}
		cout << "������(Y/N)" << endl;
		cin >> check;
	} while (check == 'y' || check == 'Y');
	return rtn;
}
int searchmember(void)
{
	cout << "��ѯ��Ա" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'n';
	do
	{
		cout << "����������:" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "û�ҵ�" << endl;
		else
		{
			cout << left << setw(10) << "����" << left << setw(10) << "��ַ" << left << setw(10) << "������" << left << setw(10) <<
				"isbn1" << left << setw(10) << "isbn2" << left << setw(10) << "isbn3" << endl;
			cout<< left << setw(10) << member.name << left << setw(10) << member.address << left << setw(10) << member.borrow<< left << setw(10) <<
				member.isbn1<< left << setw(10) << member.isbn2 << left << setw(10) << member.isbn3 << endl;
			cout << "������ѯ�Y/N����" << endl;
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
		fread:�Ӹ���������stream��ȡ���count����������buffer��
		(�൱���Զ�ÿ���������count��fgetc����
		��buffer����unsigned char���鲢˳�򱣴����������ļ�λ��ָʾ��ǰ����ȡ���ֽ�����
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
	return member;           //ֱ�ӷ���member
}
int removemember(char* name)
{
	MEMBER member;
	FILE* fp;
	FILE* temp;
	temp = fopen(_TEMP_FILE_, "w");           //д��ʽ���ļ�
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
	fp = fopen(_MEMBER_FILE_, "ab");  //׷�ӷ�ʽ��
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
	cout << "�޸Ļ�Ա" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'n';
	do 
	{
		cout << "����������" << endl;
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "û���ҵ�" << endl;
		else
		{
			cout << "����=" << member.name << endl;
			cout << "��ַ=" << member.address << endl;
			cout << "������=" << member.borrow << endl;
			cout << "isbn1=" << member.isbn1 << endl;
			cout << "isbn2=" << member.isbn2 << endl;
			cout << "isbn3=" << member.isbn3 << endl;
			cout << "�޸��" << endl;
			cin >> check;
			if (check == 'y' || check == 'Y')
			{
				removemember(name);
				inputmember();
			}
		}
		cout << "�����Y/N����" << endl;
		cin >> check;
	}
	while (check=='y'||check=='Y');
	return rtn;
}