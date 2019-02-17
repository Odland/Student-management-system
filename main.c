#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXID 20//学生的账号密码个数

//关于学生信息的结构
typedef struct {
    char name[MAXID]; //姓名
	char student_id[MAXID];//账号
    float gpt;//绩点
    int math_sc;//数学成绩
}student;

//学生账号结构信息
typedef struct {
	char id[MAXID];
    char pass[MAXID];
}stud;

student *arrin;//学生结构数组
stud *arrpid;//密码账号

char getch (void);//返回登陆所需字符
void gid (void);//验证学生登陆函数
void tea_id (void);//验证老师登陆函数
void dis_teach (void);//老师所需操作的函数
char get_tea (void);//老师所需的菜单函数
char sea_stu (void);//查询
void dis_stu (void);//显示查询
void sea_all (void);//查询全部
void sea_one (void);//查询单个
void add (void);//增加
void mod (void);//修改
int delet (void);//删除


int main(void)
{
    char ch;

    while ((ch = getch()) != 'C')//主界面
    {
        switch (ch)
        {
            case 'A':
				gid();//学生登陆查询
//				while(getchar() != '\n')
//                    continue;
                break;
            case 'B':
				tea_id();//老师登陆
                break;
        }
    }
    return 0;
}

char getch (void)//返回登陆所需字符
{
    char ch;
    puts("这是一个学生管理系统");
    puts("A 学生登陆\tB 教师登陆\nC 退出");

    ch = getchar();
    while (getchar() != '\n')//去除输入流里的'\n'
        continue;
    while (ch != 'A' && ch != 'B' && ch != 'C')
    {
        puts("你的输入有误，请重新输入:");
        ch = getchar();
        while (getchar() != '\n')
            continue;
    }
    return ch;
}

void gid()//学生的登陆查询自己的信息
{
	char id[MAXID];//学生账号
	char pass[MAXID];//学生密码
	FILE *fp;//
	int i,j;
	FILE *seach;//查询学生信息

	if ((fp = fopen("stuid.dat","rb")) == NULL)
	{
		fprintf (stderr,"打不开stuid.dat文件!");
		exit (1);
	}
	if ((seach = fopen("student.dat","rb")) == NULL)
	{
		fprintf(stderr,"找不到student.dat文件！");
		exit (1);
	}
    //定位文件结尾，计算结构个数
	fseek(fp,0L,SEEK_END);
	long x = ftell(fp)/sizeof(stud);
	//动态分配内存
	arrpid = (stud*) malloc (x * sizeof(stud));
	//将指针挪到文件开始处，从文件读入到数组
	rewind(fp);
	fread(arrpid,sizeof(stud),x,fp);

	puts("请输入你的学号:");
	fgets (id,MAXID,stdin);
	//去除数组里的'\n'
    if(strchr(id,'\n'))
    {
        *(strchr(id,'\n')) = '\0';
    }
    for (i = 0; i <= x; i++)
    {
        if (i == x)//输入的账号不正确时执行
        {
            puts("请你重新输入学号:");
            fgets(id,MAXID,stdin);
            if(strchr(id,'\n'))
            {
                *(strchr(id,'\n')) = '\0';
            }
            i = 0;
        }
        if (strcmp(arrpid[i].id,id) == 0)//账号输入正确时
        {
			puts("请输入你的密码:");
            fgets(pass,MAXID,stdin);
            if(strchr(pass,'\n'))
            {
                *(strchr(pass,'\n')) = '\0';
            }
            while (strcmp(arrpid[i].pass,pass) != 0)//密码输入不正确重新输入
            {
                puts("请重新输入你的密码:");
                fgets(pass,MAXID,stdin);
                if(strchr(pass,'\n'))
                {
                    *(strchr(pass,'\n')) = '\0';
                }
            }
            break;//退出for循环防止不必要的循环
        }
    }
    fseek(seach,0L,SEEK_END);//定位到文件结尾
    long y = ftell(seach)/sizeof(stud);//计算文件中结构的个数
    //printf("\n\n%ld\n\n",y);
    arrin = (student*) malloc (y * sizeof(student));
    //printf("\n\n%d\n\n",y);
    rewind(seach);
    if (fread (arrin,sizeof(student),y,seach) != y)
    {
        fprintf(stderr,"读入错误");
        exit(3);
    }

    for (j = 0; j < y; j++)
    {
        if (strcmp(arrpid[i].id,arrin[j].student_id) == 0)
        {
            //*(strchr(arrin[j].name,'\n')) = '\0';
            //*(strchr(arrin[j].student_id,'\n')) = '\0';
            fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
            fprintf(stdout,"%-15s%-15s\t%f\t%d\n",arrin[j].name,arrin[j].student_id,
            arrin[j].gpt,arrin[j].math_sc);
            putchar('\n');
            break;
        }
    }

	free(arrin);
	free(arrpid);

	if (fclose(fp) != 0 || fclose(seach) != 0)
	{
		fprintf (stderr,"关闭不了studid.dat或student.dat文件！");
		exit (2);
	}
}

void tea_id()//验证老师登陆
{
	char id[MAXID];//用于键盘输入老师账号
	char pass[MAXID];//用于键盘输入老师密码
	FILE *fp;

	int i ;

	if ((fp = fopen("teach.dat","rb")) == NULL)
	{
		fprintf (stderr,"找不到该文件!");
		exit (1);
	}
	fseek(fp,0L,SEEK_END);
	long x = ftell(fp);//文件字节数
	rewind (fp);
	arrpid = (stud*) malloc (x * sizeof(stud));
	fread(arrpid,sizeof(stud),x,fp);//把密码账号写入数组中
	puts("请输入你的账号:");
	fgets (id,MAXID,stdin);
    if(strchr(id,'\n'))
    {
        *(strchr(id,'\n')) = '\0';
    }
    for (i = 0; i <= x; i++)
    {
        if (i == x)//输入的账号错误
        {
            puts("请你重新输入账号:");
            fgets (id,MAXID,stdin);
            if(strchr(id,'\n'))
            {
                *(strchr(id,'\n')) = '\0';
            }
            i = 0;
        }
        if (strcmp(arrpid[i].id,id) == 0)//输入的账号正确时
        {
			puts("请输入你的密码:");
            fgets (pass,MAXID,stdin);
            if(strchr(pass,'\n'))
            {
                *(strchr(pass,'\n')) = '\0';
            }
            while (strcmp(arrpid[i].pass,pass) != 0)//密码验证不正确时
            {
                puts("请重新输入你的密码:");
                fgets (pass,MAXID,stdin);
                if(strchr(pass,'\n'))
                {
                    *(strchr(pass,'\n')) = '\0';
                }
            }
            break;
        }
    }
	free(arrpid);
	if (fclose(fp) != 0)
	{
		fprintf (stderr,"关闭不了teach.dat文件!");
		exit (2);
	}
//    while(getchar() != '\n')
//        continue;
	dis_teach ();
}

void dis_teach (void)//老师操作主界面
{
    char ch;

    while ((ch = get_tea()) != 'E')
    {
        switch (ch)
        {
            case 'A':

				dis_stu ();//查询
                break;
            case 'B':
                add ();//增加
                break;
			case 'C' :
			    mod ();//修改
				break;
			case 'D' :
			    delet ();//删除
				break;
        }
    }
}

char get_tea (void)//返回一个字符选择何种操作
{
    char ch;
    puts("A 查询\tB 添加\n\nC 修改\tD 删除\n\nE 退出");
    ch = getchar();
    while (getchar() != '\n')
        continue;

    while (ch != 'A' && ch != 'B' && ch != 'C' && ch != 'D' && ch != 'E')
    {
        puts("你的输入有误，请重新输入:");
        ch = getchar();
        while (getchar() != '\n')
            continue;
    }
    return ch;
}

char sea_stu (void)//返回一个字符
{
    char ch;
    puts("A 查询全部\tB 单个查询\nC 退出");
    ch = getchar();
    while (getchar() != '\n')
        continue;

    while (ch != 'A' && ch != 'B' && ch != 'C')
    {
        puts("你的输入有误，请重新输入:");
        ch = getchar();
        while (getchar() != '\n')
            continue;
    }
    return ch;
}

void dis_stu (void)//查询操作界面
{
    char ch;

    while ((ch = sea_stu()) != 'C')
    {
        switch (ch)
        {
            case 'A':
                sea_all ();
                break;
            case 'B':
                sea_one ();
                break;
        }
    }
}

void sea_all (void)//查询全部
{
	FILE *fp;//账号密码校验
	int j;


	if ((fp = fopen("student.dat","rb")) == NULL)
	{
		fprintf (stderr,"找不到student.dat文件!");
		exit (1);
	}
	fseek(fp,0L,SEEK_END);
	long x = ftell(fp)/sizeof(student);
	arrin = (student*) malloc(x * sizeof(student));
	rewind(fp);
	if (fread (arrin,sizeof(student),x,fp) != x)
	{
        fprintf(stderr,"读入错误");
		exit(3);
	}
	fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
	for (j = 0; j < x; j++)//显示x个结构
    {
        //*(strchr(arrin[j].name,'\n')) = '\0';
        //*(strchr(arrin[j].student_id,'\n')) = '\0';
        fprintf(stdout,"%-15s%-15s\t%f\t%d\n",arrin[j].name,arrin[j].student_id,
        arrin[j].gpt,arrin[j].math_sc);
       // putchar('\n');
    }
    free(arrin);
    if (fclose(fp) != 0)
    {
        fprintf(stderr,"关闭不了student.dat这个文件\n");
        exit(2);
    }
}

void sea_one (void)//单个查询
{
    FILE *fp;//账号密码校验
	int j;
	char id[MAXID];

	if ((fp = fopen("student.dat","rb")) == NULL)
	{
		fprintf (stderr,"找不到student.dat文件!");
		exit (1);
	}
	fseek(fp,0L,SEEK_END);
	long x = ftell(fp)/sizeof(student);
	arrin = (student*) malloc(x * sizeof(student));
	rewind(fp);
	if (fread (arrin,sizeof(student),x,fp) != x)
	{
		fprintf(stderr,"读入错误");
		exit (3);
	}
    puts("请输入学生的学号");
    fgets(id,MAXID,stdin);
    if (strchr(id,'\n'))
    {
        *(strchr(id,'\n')) = '\0';
    }
    for (j = 0; j <= x; j++)
    {
        if (j == x)
        {
            puts("请你重新输入学号:");
            fgets(id,MAXID,stdin);
            if (strchr(id,'\n'))
            {
                *(strchr(id,'\n')) = '\0';
            }
            j = 0;
        }
        else if (strcmp(arrin[j].student_id,id) == 0)
        {
           //*(strchr(arrin[j].name,'\n')) = '\0';
            //*(strchr(arrin[j].student_id,'\n')) = '\0';
            fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
            fprintf(stdout,"%-15s%-15s\t%f\t%d\n",arrin[j].name,arrin[j].student_id,
            arrin[j].gpt,arrin[j].math_sc);
            //putchar('\n');
            break;
        }
    }
    if (fclose(fp) != 0)
    {
        puts("关闭不了student.dat这个文件");
        exit(2);
    }
    free(arrin);
}

void add (void)//增加学生信息
{
    FILE *fp;
    int i,j;
    if ((fp = fopen("student.dat","ab+")) == NULL)
    {
        puts("找不到student.dat这个文件!");
        exit(1);
    }
	puts ("你想要增加几个学生的信息?");
    while(1)//剔除非整数和小于1的整数
    {
        if (scanf("%d",&i) != 1)
        {
            puts("请你输入整数:");
            while(getchar() != '\n')
                continue;
        }
        else if(i <= 0 )//限制超过数组的下标
        {
            puts("请你输入大于0的整数:");
            while(getchar() != '\n')
                continue;
            continue;
        }
        else
            while(getchar() != '\n')
                continue;
            break;
    }
    arrin = (student*) malloc(i * sizeof(student));
    for (j = 0; j < i; j++)
    {
        puts("输入姓名:");
        fgets(arrin[j].name,MAXID,stdin);
        if (strchr(arrin[j].name,'\n'))
        {
            *(strchr(arrin[j].name,'\n')) = '\0';
        }
        puts("输入学号:");
        fgets(arrin[j].student_id,MAXID,stdin);
        if (strchr(arrin[j].student_id,'\n'))
        {
            *(strchr(arrin[j].student_id,'\n')) = '\0';
        }
        puts("输入绩点:");
        scanf("%f",&arrin[j].gpt);
        while(getchar() != '\n')//清除'\n'
            continue;
        puts("输入数学成绩:");
        scanf("%d",&arrin[j].math_sc);
        while(getchar() != '\n')
            continue;
    }
    fseek(fp,0L,SEEK_END);
    fwrite(arrin,sizeof(student),i,fp);//添加i个结构写入文件
    free(arrin);
    if (fclose(fp) != 0)
    {
        puts("关闭不了student.dat这个文件");
        exit(2);
    }
}

void mod (void)//修改学生信息
{
	FILE *fp,*open;
	int j,i;
	char id[MAXID];
	char name[MAXID];
    float gpt;
    int math;
	char temp[] = "temp.dat";

	if ((fp =fopen("student.dat","ab+")) == NULL)
	{
		puts ("无法打开这个文件student.dat!");
		exit(2);
	}
	//定位到文件结尾，计算结构的个数
	fseek ( fp,0L,SEEK_END);
	long x = ftell (fp) / sizeof(student);
	//动态的分配内存
	arrin = (student*) malloc (x * sizeof(student));

	rewind (fp);
	if (fread (arrin,sizeof (student),x,fp) != x)
	{
		puts ("读入错误");
		exit (3);
	}
	if (fclose(fp) != 0)
    {
        puts("无法关闭student.dat这个文件");
        exit(2);
    }

    puts ("请输入你想要修改的学生的学号:");
	fgets (id,MAXID,stdin);
    if (strchr(id,'\n'))
    {
        *(strchr(id,'\n')) = '\0';
    }

    for (j = 0; j <= x; j++)
    {
        if (j == x)
        {
            puts("请你重新输入学号:");
            fgets(id,MAXID,stdin);
            if (strchr(id,'\n'))
            {
                *(strchr(id,'\n')) = '\0';
            }
            j = 0;
        }
        if (strcmp(arrin[j].student_id,id) == 0)
        {
            fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
            //*(strchr(arrin[j].name,'\n')) = '\0';
            //*(strchr(arrin[j].student_id,'\n')) = '\0';
            fprintf(stdout,"%-15s%-15s\t%f\t%d\n",arrin[j].name,arrin[j].student_id,
            arrin[j].gpt,arrin[j].math_sc);
            putchar('\n');
            break;
        }
    }

	puts("请输入你想要修改的学生的参数,例如1-name，2-id,3-绩点,4-成绩");
	while(1)//剔除非整数和小于1的整数
    {
        while (scanf("%d",&i) != 1)
        {
            puts("请你输入整数:");
            while(getchar() != '\n')
                continue;
        }
        if(i <= 0 || i > 4 )//限制超过数组的下标
        {
            puts("请你输入大于0小于4的整数:");
            continue;
        }
        else
            while(getchar() != '\n')
                continue;
            break;
    }
	switch (i)
	{
		case 1 :
			puts ("请输入姓名:");
			fgets (arrin[j].name,MAXID,stdin);
            if (strchr(arrin[j].name,'\n'))
            {
                *(strchr(arrin[j].name,'\n')) = '\0';
            }
			break;
		case 2 :
			puts ("请输入学号:");
			fgets (arrin[j].student_id,MAXID,stdin);
            if(strchr(arrin[j].student_id,'\n'))
            {
                *(strchr(arrin[j].student_id,'\n')) = '\0';
            }
			break;
		case 3 :
			puts ("请输入绩点:");
			scanf ("%f",&arrin[j].gpt);
			while(getchar() != '\n')
				continue;
			break;
		case 4 :
			puts ("请输入数学成绩:");
			scanf("%d",&arrin[j].math_sc);
			while(getchar() != '\n')
				continue;
			break;
	}

    if ((fp =fopen("student.dat","wb+")) == NULL)
	{
		puts ("无法打开这个文件student.dat!");
		exit(2);
	}

	rewind (fp);
	if (fwrite (arrin,sizeof(student),x,fp) != x)//修改之后写入student.dat
	{
	    puts("写入有错误!");
	    exit(4);

	}
	if (fclose(fp) != 0)
    {
        puts("无法关闭这个文件");
        exit(2);
    }
	free(arrin);
//	remove("student.dat");
//	rename(temp,"student.dat");
}


int delet (void)//删除学生信息
{
	FILE *fp,*open;
	char id[MAXID];
	int j,i;

	char dele[] = "dele.dat";

	if ((open = fopen(dele,"ab+")) == NULL)
	{
		puts ("无法打开这个文件temp!");
		exit(1);
	}
	if ((fp = fopen("student.dat","ab+")) == NULL)
	{
		puts("找不到这个文件");
		exit (1);
	}
	fseek ( fp,0L,SEEK_END);
	long x = ftell (fp) / sizeof(student);
	arrin = (student*) malloc (x * sizeof(student));
	rewind (fp);
	if (fread (arrin,sizeof (student),x,fp) != x)
	{
		puts ("读入错误");
		exit (3);
	}

	puts ("请输入你想要删除的学生的学号:");
	fgets (id,MAXID,stdin);
	if (strchr(id,'\n'))
    {
        *(strchr(id,'\n')) ='\0';
    }
    for (j = 0; j <= x; j++)
    {
        if (j == x)
        {
            puts("请你重新输入学号:");
            fgets(id,MAXID,stdin);
            if (strchr(id,'\n'))
            {
                *(strchr(id,'\n')) ='\0';
            }
            j = 0;
        }
        if (strcmp(arrin[j].student_id,id) == 0)
        {
            fprintf(stdout,"姓名\t\t学号\t\t绩点\t\t数学成绩\n");
            //*(strchr(arrin[j].name,'\n')) = '\0';
            //*(strchr(arrin[j].student_id,'\n')) = '\0';
            fprintf(stdout,"%-15s%-15s\t%f\t%d\n",arrin[j].name,arrin[j].student_id,
            arrin[j].gpt,arrin[j].math_sc);
            putchar('\n');
            break;
        }
    }
	if(j == 0)
	{
		rewind(open);
		fwrite(&arrin[j+1],sizeof(student),x-1,open);
		if(fclose(open) != 0 || fclose(fp) != 0)
		{
			puts("无法关闭dele.dat或student.dat文件");
			exit(2);
		}
		remove("student.dat");
		rename(dele,"student.dat");
	}

	else if(j == x-1)
	{
		rewind(open);
		fwrite(arrin,sizeof(student),x-1,open);
		if(fclose(open) != 0 || fclose(fp) != 0)
		{
			puts("无法关闭dele.dat或student.dat文件");
			exit(2);
		}
		remove("student.dat");
		rename(dele,"student.dat");
	}

	else
	{
		rewind(open);
		fwrite(arrin,sizeof(student),j,open);
		fwrite(&arrin[j+1],sizeof(student),x-j-1,open);
		if(fclose(open) != 0 || fclose(fp) != 0)
		{
			puts("无法关闭dele.dat或student.dat文件");
			exit(2);
		}
		remove("student.dat");
		rename(dele,"student.dat");
	}
	free(arrin);
}
