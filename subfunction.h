//#pragma once  �ɱ��������б�֤����ֹ�����ֳ�ͻ    
//#ifndef   ��֤���ᱻ��ΰ���      ���������ԵĿ���ֲ��

#ifndef SUBFUNCTION_H_INCLUDED
#define SUBFUNCTION_H_INCLUDED
#include"datainfo.h"
void mmbook(void);
void listmember(void);
int inputbook(void);  //¼��ͼ��
int deletebook(void);
int searchbook(void);
int modifybook(void);
int lendbook(void);
int returnbook(void);
int inputmember(void);
int deletemember(void);
int searchmember(void);
int modifymember(void);
BOOK findbook(char* ISBN);         //ʹ���Զ�������ݽṹ
int removebook(char* ISBN);
MEMBER findmember(char* name);
int removemember(char* name);
int memberborrow(MEMBER member);
int lendbook(BOOK book);
#endif             //SUBFUNCTION_H_INCLUDED


