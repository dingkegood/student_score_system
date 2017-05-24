#include <stdio.h>
#include "student.h"

int length = 0;
struct student stu_all[50];

int main(int argc, char *argv[])
{
	student_array_init(&length, stu_all);
	student_menu();
	int choice = 0;
	while (1)
	{
		printf("Please input operation number(0~9):");
		scanf("%d", &choice);
		system("cls");
		student_menu();
		switch (choice)
		{
		case 0:
			system("cls");
			student_menu();
			break;
		case 1:
			student_add(&length, stu_all);
			break;
		case 2:
			student_delete(&length, stu_all);
			break;
		case 3:
			student_find(length, stu_all);
			break;
		case 4:
			student_statistic(length, stu_all);
			break;
		case 5:
			student_modify(length, stu_all);
			break;
		case 6:
			student_array_printf(length, stu_all);
			break;
		case 9:
			system("cls");
			return 0;
			break;
		default:
			printf("ÎŞĞ§ÊäÈë!\n");
			break;
		}
	}

	/**************** test code *******************
	struct student stu[4] = {{002, "HanMei", 'F', 21, 98.5, 90, 77 },
							 {001, "LEsdfs", 'M', 21, 98.5, 90, 77 }};
	struct student std = 
	{
		.no = 001,
		.name = "LiLei",
		.sex = 'M',
		.age = 20,
		.english = 89.5,
		.chinese = 90,
		.math = 78
	};
#if 0
	//student_printf(std);
	printf("file length = %d. \n", length);
	//student_save(2, stu);
	student_array_init(&length, stu);
	printf("read file length = %d. \n", length);
	student_array_printf(2, stu);
#endif

#if 0
	student_add(&length, stu);
#endif

#if 0
	student_array_init(&length, stu);
	printf("file length = %d. \n", length);
	student_array_printf(length, stu);
	student_delete(&length, stu);
	student_array_printf(length, stu);
#endif
#if 0
	student_add(&length, stu);
	student_find(length, stu);
#endif

#if 0
	student_add(&length, stu);
	student_modify(length, stu);
	student_array_printf(length, stu);
#endif

#if 1
	student_add(&length, stu);
	student_statistic(length, stu);
#endif
	*/
	return 0;
}