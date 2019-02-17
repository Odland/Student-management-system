//添加老师密码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXID 20
#define MAXSTR 20
typedef struct {
	char id[MAXID];
    char pass[MAXID];
}stud;

stud *stu;

int main (void)
{
	FILE *fp;
	int i;

	if ((fp = fopen("teach.dat","ab+")) == NULL)
	{
		puts ("找不到teach.dat这个文件");
		exit (1);
	}
	stu = (stud*) malloc(MAXSTR * sizeof(stud));
	printf ("请输入你想要输入老师的账号和密码,若终止输入请在输入账号时按Enter键结束输入(注意:一次最多只能输入%d个).\n",MAXSTR);
	for (i = 0;i < MAXSTR;i++)
	{
		puts ("请输入账号:");
        fgets (stu[i].id,MAXID,stdin);
        if (stu[i].id[0] == '\n')
            break;
        else if(strchr(stu[i].id,'\n'))
        {
            *(strchr(stu[i].id,'\n')) = '\0';
        }
        puts ("请输入密码:");
        fgets (stu[i].pass,MAXID,stdin);
        if(strchr(stu[i].pass,'\n'))
        {
            *(strchr(stu[i].pass,'\n')) = '\0';
        }
	}
    if (i == MAXSTR)
        puts("\n已存满\n");
    rewind(fp);//文件开始位置
	fwrite (stu,sizeof(stud),i,fp);//写入文件
	int x = ftell(fp)/sizeof(stud);//计算结构的个数
	rewind(fp);
	stud s1[x];//用于文件内容回显
	if (fread(s1,sizeof(stud),x,fp) != x)
    {
        fprintf(stderr,"读入错误");
        exit(3);
    }
    printf ("账号\t\t密码\n\n");
	for (i = 0; i < x; i++)
	{
        //*(strchr(s1[i].id,'\n')) = '\0';
	    //*(strchr(s1[i].pass,'\n')) = '\0';
		printf ("%-15s%-15s\n\n",s1[i].id,s1[i].pass);
	}
	free(stu);
	if (fclose(fp) != 0)
	{
	    puts("关闭不了teach.dat这个文件");
	    exit(2);
	}
	return 0;
}
