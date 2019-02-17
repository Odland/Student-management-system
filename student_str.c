//添加学生结构信息
#include <stdio.h>
#include <stdlib.h>
#define MAXID 20
#define MAXSTR 20
typedef struct {
    char name[MAXID];
	char  student_id[MAXID];
    float gpt;
    int math_sc;
}student;

student *stu;

int main (void)
{
	FILE *fp;
	int i;
	int j;

	if ((fp = fopen("student.dat","ab+")) == NULL)
	{
		fprintf (stderr,"打不开student.dat这个文件");
		exit (1);
	}
    stu = (student*) malloc (MAXSTR * sizeof(student));
    printf ("请输入学生信息,终止输入请在输入姓名时按'Enter'键(注意：一次最多只能添加%d个).\n",MAXSTR);
    for (i = 0; i < MAXSTR; i++)
    {

        puts ("请输入姓名:");
        fgets (stu[i].name,MAXID,stdin);
        if (stu[i].name[0] == '\n')
            break;
        else if (strchr(stu[i].name,'\n'))
        {
            *(strchr(stu[i].name,'\n')) = '\0';
        }
        puts ("请输入学号:");
        fgets (stu[i].student_id,MAXID,stdin);
        if(strchr(stu[i].student_id,'\n'))
        {
            *(strchr(stu[i].student_id,'\n')) = '\0';
        }
        puts ("请输入绩点:");
        scanf ("%f",&stu[i].gpt);
        while (getchar () != '\n')
            continue;
        puts ("请输入数学成绩:");
        scanf ("%d",&stu[i].math_sc);
        while (getchar () != '\n')
            continue;
    }
    if (i == MAXSTR)
        puts ("\n已存满\n");
    rewind(fp);//确保在文件起始位置
	fwrite (stu,sizeof(student),i,fp);
    fseek(fp,0L,SEEK_END);//定位到文件末尾
	long x = ftell(fp)/sizeof(student);//结构的个数
	//printf("\n\n%ld\n\n",x);
	rewind(fp);
	student s1[x];//回显存入文件的结构信息
	if (fread(s1,sizeof(student),x,fp) != x)
    {
        fprintf (stderr,"读入错误");
        exit(3);
    }
    fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
	for (j = 0; j < x; j++)
	{
	    //*(strchr(s1[j].name,'\n')) = '\0';
	    //*(strchr(s1[j].student_id,'\n')) = '\0';

        fprintf(stdout,"%-15s%-15s\t%f\t%d\n",s1[j].name,s1[j].student_id,s1[j].gpt,s1[j].math_sc);
	}
	free(stu);
	if (fclose(fp) != 0)
    {
        puts("关闭不了student.dat这个文件");
        exit(2);
    }
	return 0;
}
