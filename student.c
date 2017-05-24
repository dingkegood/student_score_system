#include <stdio.h>
#include <string.h>
#include "student.h"


void student_menu()
{
	printf("\tWelcome to use Student Achievement Management System\n");
	printf("*******************************************************************\n");
	printf("\t\t1 Add Score\t\t 2 Delete Score\n");
	printf("\t\t3 Search Dcore\t\t 4 Statistic Score\n");
	printf("\t\t5 Modify INFO\t\t 6 Print Score\n");
	printf("\t\t0 Display Menu\t\t 9 Exit\n");
	printf("*******************************************************************\n");
}

void student_array_printf(int len, struct student stu[])
{
	int i = 0;

	printf("----------------------------------------------------------------------------\n");
	printf("学号\t 姓名\t 性别\t 年龄\t 英语\t\t 语文\t\t 数学\t \n");
	for (i; i < len; i++)
	{	
		printf("%d\t %s\t %c\t %d\t %f\t %f\t %f\t \n",
			stu[i].no, stu[i].name, stu[i].sex, stu[i].age,
			stu[i].english, stu[i].chinese, stu[i].math);
	}

	printf("----------------------------------------------------------------------------\n");
}

void student_printf(struct student std)
{
	printf("----------------------------------------------------------------------------\n");
	printf("学号\t 姓名\t 性别\t 年龄\t 英语\t\t 语文\t\t 数学\t \n");
	printf("%d\t %s\t %c\t %d\t %f\t %f\t %f\t \n", 
		std.no, std.name, std.sex, std.age, std.english, std.chinese, std.math);
	printf("----------------------------------------------------------------------------\n");
}

int student_save(int len, struct student stu[])
{
	FILE *fp;
	int i = 0;

	if ((fp = fopen("student.dat", "wb")) == NULL)
	{
		printf("open file failed!\n");
		return -1;
	}
	else
	{
		for (i; i < len; i++)
		{
			fwrite(&stu[i], sizeof(struct student), 1, fp);
			if (ferror(fp))
			{
				printf("write file failed！\n");
				return -1;
			}	
		}
		printf("save file success！\n");
	}

	fclose(fp);
	return 0;
}

int student_array_init(int *len, struct student stu[])
{
	FILE *fp;
	int i = 0;
	if ((fp=fopen("student.dat", "ab+")) == NULL)
	{
		printf("open file failed！\n");
		return -1;
	}
	fread(&stu[0], sizeof(struct student), 1, fp);	//init file point
	while (!feof(fp))	//feof:0 file not end，1 file end
	{
		i++;
		fread(&stu[i], sizeof(struct student), 1, fp);
		if (ferror(fp))
		{
			printf("read file failed！\n");
			return -2;
		}
	}
	fclose(fp);
	*len = i;

	return 0;	//array length
}

int student_add(int *len, struct student *stu)
{
	int number = 0;
	int i = 0;
	struct student std;

	printf("How much students would you want to add,please input:");
	scanf("%d", &number);
	for (i; i < number; i++)
	{
		printf("please input student no:");
		scanf("%d", &std.no);
		printf("please input student name:");
		scanf("%s", &std.name);
		printf("please input student sex:");
		fflush(stdin);	//flush the stdin for clean "enter"
		scanf("%c", &std.sex);
		printf("please input student age:");
		scanf("%d", &std.age);
		printf("please input english score:");
		scanf("%f", &std.english);
		printf("please input chinese score:");
		scanf("%f", &std.chinese);
		printf("please input math score:");
		scanf("%f", &std.math);
		stu[*len] = std;
		(*len)++;
	}
	student_save(*len, stu);
	printf("length:%d \n", *len);
	student_array_printf(*len, stu);

	return 0;
}

static int student_del_by_number(unsigned int num, int *len, struct student stu[])
{
	int i = 0;
	printf("len %d,\n", *len);
	for (i; i < *len; i++)	//compare
	{
		if (stu[i].no == num)
			break;

	}
	
	if (i == *len) {
		printf("Can't find student %d.\n", num);
		return -1;
	}
	printf("test1 len = %d \n", len);
	for (i; i < (*len - 1); i++)
		stu[i] = stu[i+1];
	printf("test2 \n");
	(*len)--;

	return 0;
}

static int student_del_by_name(char name[], int *len, struct student stu[])
{
	int i = 0;

	for (i; i < *len; i++)	//compare
	{
		if (strcmp(name, stu[i].name) == 0)
			break;

	}
	if (i == *len) {
		printf("Can't find student %s.\n", name);
		return -1;
	}
	for (i; i < *len - 1; i++)
		stu[i] = stu[i++];
	(*len)--;

	return 0;
}

int student_delete(int *len, struct student stu[])
{
	int number = 0;

	student_array_printf(*len, stu);

	printf("----------------------------------------------------------------------------\n");
	printf("Delete student info by number or by name? \n number: input 1 \n name: input 2 \n");
	scanf("%d", &number);

	int num = 0;
	char name[10] = {0};
	
	switch (number)
	{
		case 1:
			printf("Please input student number:\n");
			scanf("%d", &num);
			student_del_by_number(num, len, stu);
			break;
		case 2:
			
			printf("Please input student name:\n");
			scanf("%s", name);
			student_del_by_name(name, len, stu);
			break;
		default:printf("usiness input! \n"); 
			return -1; break;
	}
	student_save(*len, stu);
	return 0;
}

static struct student *student_find_by_number(const unsigned num,int len,struct student stu[])
{
	int i = 0;
	printf("len %d,\n", len);
	for (i; i < len; i++)	//compare
	{
		if (stu[i].no == num)
			break;
	}
	if (i == len) {
		printf("Can't find student %d.\n", num);
		return NULL;
	}
	student_printf(stu[i]);
	printf("test find \n");
	return &stu[i];
}

static struct student *student_find_by_name(const char name[], int len, struct student stu[])
{
	int i = 0;

	for (i; i < len; i++)	//compare
	{
		if (strcmp(name, stu[i].name) == 0)
			break;
	}
	if (i == len) {
		printf("Can't find student %s.\n", name);
		return NULL;
	}
	student_printf(stu[i]);
	printf("test find \n");
	return &stu[i];
}

int student_find(const int len, struct student stu[])
{
	int number = 0;
	printf("----------------------------------------------------------------------------\n");
	printf("Find student info by number or by name? \n number: input 1 \n name: input 2 \n");
	scanf("%d", &number);

	int num = 0;
	char name[10] = { 0 };

	switch (number)
	{
		case 1:
			printf("Please input student number:\n");
			scanf("%d", &num);
			student_find_by_number(num, len, stu);
			break;
		case 2:
			printf("Please input student name:\n");
			scanf("%s", name);
			student_find_by_name(name, len, stu);
			break;
		default:
			printf("usiness input! \n");
			return -1;
			break;
	}

	return 0;
}

static int student_modify_by_number(unsigned num, int len, struct student stu[])
{
	int number = 0;
	struct student *std = NULL;		//creat a point point on position
	std = student_find_by_number(num, len, stu);	//just need modify std 
	if (std == NULL)
	{
		return -1;
	}

	printf("----------------------------------------------------------------------------\n");
	printf("0 : modify no \n");
	printf("1 : modify name \n");
	printf("2 : modify sex \n");
	printf("3 : modify age \n");
	printf("4 : modify chinese score \n");
	printf("5 : modify english score \n");
	printf("6 : modify math    score \n");
	scanf("%d", &number);

	switch (number)
	{
		case 0:
			printf("input no:");
			scanf("%d", &std->no);
			break;
		case 1:
			printf("input name:");
			scanf("%s", &std->name);
			break;
		case 2:
			printf("input sex:");
			scanf("%c", &std->sex);
			break;
		case 3:
			printf("input age:");
			scanf("%d", &std->age);
			break;
		case 4:
			printf("input chinese:");
			scanf("%f", &std->chinese);
			break;
		case 5:
			printf("input english:");
			scanf("%f", &std->english);
			break;
		case 6:
			printf("input math:");
			scanf("%f", &std->math);
			break;
		default:
			printf("modify fail! \n");
			break;
	}
	student_save(len, stu);

	return 0;
}

static int student_modify_by_name(char name[], int len, struct student stu[])
{
	int number = 0;
	struct student *std = NULL;		//creat a point point on position
	std = student_find_by_name(name, len, stu);	//just need modify std 
	if (std == NULL)
	{
		return -1;
	}

	printf("----------------------------------------------------------------------------\n");
	printf("0 : modify no \n");
	printf("1 : modify name \n");
	printf("2 : modify sex \n");
	printf("3 : modify age \n");
	printf("4 : modify chinese score \n");
	printf("5 : modify english score \n");
	printf("6 : modify math    score \n");
	scanf("%d", &number);

	switch (number)
	{
		case 0:
			printf("input no:");
			scanf("%d", &std->no);
			break;
		case 1:
			printf("input name:");
			scanf("%s", &std->name);
			break;
		case 2:
			printf("input sex:");
			fflush(stdin);
			scanf("%c", &std->sex);
			break;
		case 3:
			printf("input age:");
			scanf("%d", &std->age);
			break;
		case 4:
			printf("input chinese:");
			scanf("%f", &std->chinese);
			break;
		case 5:
			printf("input english:");
			scanf("%f", &std->english);
			break;
		case 6:
			printf("input math:");
			scanf("%f", &std->math);
			break;
		default:
			printf("modify fail! \n");
			return -1;
			break;
	}
	student_save(len, stu);

	return 0;
}

int student_modify(int len, struct student stu[])
{
	int number = 0;
	printf("----------------------------------------------------------------------------\n");
	printf("Modify student info by number or by name? \n number: input 1 \n name: input 2 \n");
	scanf("%d", &number);

	int num = 0;
	unsigned char name[10];

	switch (number)
	{
	case 1:
		printf("Please input student number:\n");
		scanf("%d", &num);
		student_modify_by_number(num, len, stu);
		break;
	case 2:

		printf("Please input student name:\n");
		fflush(stdin);
		scanf("%s", name);
		printf("name = %s\n", name);
		student_modify_by_name(name, len, stu);
		break;
	default:printf("usiness input! \n"); break;
	}
	//student_save(len, stu);

	return 0;
}
#define llen  100
int student_statistic(const int len, struct student stu[])
{
	float chinese_avr = 0, english_avr = 0, math_avr = 0;
	int   chinese_num = 0, english_num = 0, math_num = 0;
	int total_num = 0;
	float score_avr[llen];
	float avr = 0;
	int i;
	for (i = 0; i<len; i++)
	{
		chinese_avr += stu[i].chinese;	//caculate every subject score
		english_avr += stu[i].english;
		math_avr += stu[i].math;
		score_avr[i] = stu[i].chinese + stu[i].english + stu[i].math;
		score_avr[i] /= 3;
		if (stu[i].chinese < 60)	//caculate every subject no passing number
			chinese_num++;
		if (stu[i].english < 60)
			english_num++;
		if (stu[i].math<60)
			math_num++;
	}

	chinese_avr /= len;
	english_avr /= len;
	math_avr /= len;
	total_num = chinese_num + english_num + math_num;
	avr = (chinese_avr + english_avr + math_avr) / 3;

	printf("\t\t\t Students' Archievement Statistics\n");
	printf("-------------------------------------------------------------\n");
	printf("No\tName\tAverage\n");
	for (i = 0; i<len; i++)
		printf("%d\t%s\t%f\n", stu[i].no, stu[i].name,
		score_avr[i]);
	printf("-------------------------------------------------------------\n");
	printf("Average score in Chinese: %f\t\tFailure number: %d\n", chinese_avr, chinese_num);
	printf("Average score in English: %f\t\tFailure number: %d\n", english_avr, english_num);
	printf("Average score in Math   : %f\t\tFailure number: %d\n", math_avr, math_num);
	printf("-------------------------------------------------------------\n");
	printf("Total average：%f\n", avr);
	printf("Total failure number:%d\n", total_num);
	printf("-------------------------------------------------------------\n");
	return 0;
}