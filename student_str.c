//���ѧ���ṹ��Ϣ
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
		fprintf (stderr,"�򲻿�student.dat����ļ�");
		exit (1);
	}
    stu = (student*) malloc (MAXSTR * sizeof(student));
    printf ("������ѧ����Ϣ,��ֹ����������������ʱ��'Enter'��(ע�⣺һ�����ֻ�����%d��).\n",MAXSTR);
    for (i = 0; i < MAXSTR; i++)
    {

        puts ("����������:");
        fgets (stu[i].name,MAXID,stdin);
        if (stu[i].name[0] == '\n')
            break;
        else if (strchr(stu[i].name,'\n'))
        {
            *(strchr(stu[i].name,'\n')) = '\0';
        }
        puts ("������ѧ��:");
        fgets (stu[i].student_id,MAXID,stdin);
        if(strchr(stu[i].student_id,'\n'))
        {
            *(strchr(stu[i].student_id,'\n')) = '\0';
        }
        puts ("�����뼨��:");
        scanf ("%f",&stu[i].gpt);
        while (getchar () != '\n')
            continue;
        puts ("��������ѧ�ɼ�:");
        scanf ("%d",&stu[i].math_sc);
        while (getchar () != '\n')
            continue;
    }
    if (i == MAXSTR)
        puts ("\n�Ѵ���\n");
    rewind(fp);//ȷ�����ļ���ʼλ��
	fwrite (stu,sizeof(student),i,fp);
    fseek(fp,0L,SEEK_END);//��λ���ļ�ĩβ
	long x = ftell(fp)/sizeof(student);//�ṹ�ĸ���
	//printf("\n\n%ld\n\n",x);
	rewind(fp);
	student s1[x];//���Դ����ļ��Ľṹ��Ϣ
	if (fread(s1,sizeof(student),x,fp) != x)
    {
        fprintf (stderr,"�������");
        exit(3);
    }
    fprintf(stdout,"����\t\tѧ��\t\t����\t\t��ѧ�ɼ�\n");
	for (j = 0; j < x; j++)
	{
	    //*(strchr(s1[j].name,'\n')) = '\0';
	    //*(strchr(s1[j].student_id,'\n')) = '\0';

        fprintf(stdout,"%-15s%-15s\t%f\t%d\n",s1[j].name,s1[j].student_id,s1[j].gpt,s1[j].math_sc);
	}
	free(stu);
	if (fclose(fp) != 0)
    {
        puts("�رղ���student.dat����ļ�");
        exit(2);
    }
	return 0;
}
