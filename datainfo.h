//typedef ����c��˵����ʡ�ԣ�typedef struct T{} A,���Խ���A��������c++�п���ʡ��
/*
   ���ȶ�������Ҫ�����ݽṹ������ϵͳ��Ҫ���ݽṹ������ͼ�����ݽṹ��ϵͳ��Ա�û����ݽṹ
*/
typedef struct bookdata
{
    char isbn[12];  //isbn 12b
    char name[20];  
    char publisher[20]; 
    char author[20];
    short ver;          //���
    float price;
    short count;      //���
 }BOOK;
typedef struct memberdata
{
    char name[20];
    char address[20];
    short borrow; //������
    char isbn1[12];
    char isbn2[12];
    char isbn3[12];   //�����Խ�������
}MEMBER;
