//#pragma once  由编译器进行保证，防止宏名字冲突    
//#ifndef   保证不会被多次包含      依靠于语言的可移植性

#ifndef SUBFUNCTION_H_INCLUDED
#define SUBFUNCTION_H_INCLUDED
#include"datainfo.h"
void mmbook(void);
void listmember(void);
int inputbook(void);  //录入图书
int deletebook(void);
int searchbook(void);
int modifybook(void);
int lendbook(void);
int returnbook(void);
int inputmember(void);
int deletemember(void);
int searchmember(void);
int modifymember(void);
BOOK findbook(char* ISBN);         //使用自定义的数据结构
int removebook(char* ISBN);
MEMBER findmember(char* name);
int removemember(char* name);
int memberborrow(MEMBER member);
int lendbook(BOOK book);
#endif             //SUBFUNCTION_H_INCLUDED


