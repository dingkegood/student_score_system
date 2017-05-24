#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
	unsigned int no;
	char name[10];
	char sex;
	unsigned char age;
	float english;
	float chinese;
	float math;
};
//extern struct student;
void student_menu();
void student_printf(struct student std);
void student_array_printf(int len, struct student stu[]);
int student_save(int len, struct student stu[]);
int student_array_init(int *len, struct student stu[]);
int student_add(int *len, struct student *stu);
int student_delete(int *len, struct student *stu);
int student_find(int len, struct student stu[]);
int student_modify(int len, struct student stu[]);
int student_statistic(int len, struct student stu[]);

#endif	