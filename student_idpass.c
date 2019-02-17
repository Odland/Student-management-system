//添加账号密码
#include <stdio.h>
#include <stdlib.h>
#define MAXID 20
#define MAXSTR 20

typedef struct {
    char id[MAXID];
    char pass[MAXID];
}student;

student *stu;

int main (void)
{
	FILE *fp;
	int i;

	if ((fp = fopen("stuid.dat","ab+")) == NULL)
	{
		fprintf (stderr,"找不到stuid.dat这个文件");
		exit (1);
	}
	stu = (student*) malloc(MAXSTR * sizeof(student));
	printf ("请输入学生的密码 和账号,若终止输入请在输入账号时按Enter键结束输入(注意:一次最多只能输入%d个).\n",MAXSTR);
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
        puts ("\n已存满!\n");
    rewind(fp);
	fwrite (stu,sizeof(student),i,fp);
	int x = ftell(fp)/sizeof(student);//计算结构的个数
	rewind(fp);
	student *s1 = (student*) malloc(x * sizeof(student));
	if (fread(s1,sizeof(student),x,fp) != x)
    {
        fprintf (stderr,"读入错误");
        exit(3);
    }
    printf ("账号\t\t密码\n\n");
	for (i = 0; i < x; i++)
	{
	    //*(strchr(s1[i].id,'\n')) = '\0';
	    //*(strchr(s1[i].pass,'\n')) = '\0';
		printf ("%-15s%-10s\n\n",s1[i].id,s1[i].pass);
	}
	free(s1);
	free(stu);
	if (fclose(fp) != 0)
    {
        puts("关闭不了这个文件");
        exit(1);
    }
	return 0;
}
