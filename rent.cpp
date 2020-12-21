#include"stdafx.h"
#include<iostream>
#include"mainfunction.h"
//fwrite()与fread()因字符编码问题容易出现乱码，可以考虑使用fprintf()和fscanf()
int main(void)
{
	short selected = 0;
	short selectedsub = 0;
	showwelcome();
	do 
	{
		selected = showmenu();
		do 
		{
			selectedsub = showsubmenu(selected);
			callsubtask(selectedsub);
		} while (selectedsub!=0);
	} while (selected!=0);
	return 0;
}