#ifndef MAINFUNCTION_H_INCLUDED   //如果没有定义，则的定义宏
#define MAINFUNCTION_H_INCLUDED
#define _QUIT_0
//显示欢迎信息
void showwelcome(void);
//显示菜单项，返回选择的菜单
short showmenu(void);
short showsubmenu(short menu);  //显示子菜单
void callsubtask(short selected);  //功能调用函数，依据菜单选择调用函数
#endif 
