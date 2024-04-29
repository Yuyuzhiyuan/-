#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <io.h>



//定义 员工 链表
struct Employee {
	char name[15];        // 姓名
	char gender[8];        // 性别
	char birth[20];         // 出生日期 
	char num[20];         // 职工号 
	char xueli[15];         // 学历
	char posit[15];        // 职务
	char tele[16];          // 电话
	char location[25];      // 住址
	struct Employee* next;//链式存储
};
Employee* employeeList;//定义全局 员工 指针  即常用的L
int employeeCount = 0;//员工 个数记录

int compare(int a, int b);
int compare(const char* a, const char* b);//

//员工 读入文件
void readEmployee();
//员工 写入文件
void writeEmployee();
//员工 添加记录
void addEmployee();
void addOneEmployee(Employee* employee);
//员工 删除记录
void delEmployee();
//员工 根据下标删除
int delEmployeeByIndex(int index);
//员工 修改记录
void modEmployee();
//员工 查找记录
void findEmployee(int all);
//员工 排序
void sortEmployee();
//交换
void exchangeEmployee(int i, int j);
//存在判断函数

//菜单
void menu();

// 主函数
int main() {
	//读取数据
	readEmployee();//读取员工
	while (1) {
		int choice;
		menu();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addEmployee();//添加员工
			break;
		case 2:
			findEmployee(1);//查找员工
			delEmployee();//删除员工
			break;
		case 3:
			findEmployee(1);//查找员工
			modEmployee();//修改员工
			break;
		case 4:
			findEmployee(0);//查找员工
			break;
		case 5:
			sortEmployee();//排序员工
			break;
		case 0:
			printf("\n\n\n\t\t\t感谢使用\n\n\n");
			exit(0);//C ++exit函数终止进程，退出程序
		default:
			getchar();
			printf("\n\n\n\t提示：没有这个选项！请重新输入!\n\n\n\n");
			system("pause");
			break;
		}
	}
	return 0;
}



//员工 读入文件
void readEmployee() {
	FILE* fp;
	fp = fopen("EmployeeData.data", "r");    //	FILE* =fopen("EmployeeData.data", "r");将文件读入fp这个文件结构体，
	//读取文件为空                                               以文本格式读取EmployeeData.data文件
	if (fp == NULL)return;
	//读取个数
	fread(&employeeCount, sizeof(int), 1, fp);//将文件数据个数放进employeeCount  ，1指元素个数
	employeeList = NULL;
	Employee* tail = employeeList;   //这个tail没用
	//写入到链表
	for (int i = 0; i < employeeCount; i++) {
		Employee* p = (Employee*)malloc(sizeof(Employee));//分配一段Employee结构体大小的地址空间
		fread(p, sizeof(Employee), 1, fp);   //以Employee对象返回给p这个指针    这种动态内存分配空间节约内存，而且外部需要调用函数内部指针对应空间
		p->next = NULL;
		//指针为空则赋值。
		if (employeeList == NULL) {
			employeeList = p;
			tail = p;
		}
		else {     //这个tail指针并没有用到
			tail->next = p;
			tail = p;
		}
	}
	fclose(fp);//关闭文件函数
}
//员工 写入文件
void writeEmployee() {
	//保存到本地信息库
	FILE* fp;
	fp = fopen("EmployeeData.data", "wb");   //写入二进制内容
	Employee* p = employeeList;
	//先保存个数
	fwrite(&employeeCount, sizeof(employeeCount), 1, fp);
	//挨个保存
	while (p) {     //将p写入，将整个链表写入本地文件
		Employee* temp = (Employee*)malloc(sizeof(Employee));
		temp->next = NULL;
		strcpy(temp->name, p->name);
		strcpy(temp->gender, p->gender);
		strcpy(temp->birth, p->birth);
		strcpy(temp->num, p->num);
		strcpy(temp->xueli, p->xueli);
		strcpy(temp->posit, p->posit);
		strcpy(temp->tele, p->tele);
		strcpy(temp->location, p->location);
		fwrite(temp, sizeof(Employee), 1, fp);
		p = p->next;
	}
	fclose(fp);
}
//员工 添加记录
void addEmployee() {
	char selectYNFlag = 'y';
	while (selectYNFlag == 'y' || selectYNFlag == 'Y') {
		printf("\n");
		Employee* tempValue = (Employee*)malloc(sizeof(Employee)); //必须重新分配地址空间。
		printf("请输入姓名 ：");
		char name[15];
		scanf("%s", name);
		strcpy(tempValue->name, name); 
		printf("请输入性别 ：");
		char gender[8];
		scanf("%s", gender);
		strcpy(tempValue->gender, gender);
		printf("请输入出生日期 ：");
		char birth[20];
		scanf("%s", birth);
		strcpy(tempValue->birth, birth);
		printf("请输入职工号 ：");
		char num[20];
		scanf("%s", num);
		strcpy(tempValue->num, num);
		printf("请输入学历 ：");
		char xueli[15];
		scanf("%s", xueli);
		strcpy(tempValue->xueli, xueli);
		printf("请输入职务 ：");
		char posit[15];
		scanf("%s", posit);
		strcpy(tempValue->posit, posit);
		printf("请输入电话 ：");
		char tele[16];
		scanf("%s", tele);
		strcpy(tempValue->tele, tele);
		printf("请输入住址 ：");
		char location[25];
		scanf("%s", location);
		strcpy(tempValue->location, location);
		tempValue->next = NULL;
		addOneEmployee(tempValue);     //将新形成的链表结点加入链表   形成新的employeeList（头结点），即下方头插法函数
		printf("\n是否继续录入？(y/n)");
		getchar();//I/O流输入字符，直到回车
		scanf("%c", &selectYNFlag);
	}
	writeEmployee();
	printf("\n*****************************\n");
	printf("录入完成\n");
	printf("*****************************\n");
}
void addOneEmployee(Employee* temp) {
	//采用头插法
	if (employeeList == NULL) {
		employeeList = temp;
	}
	else {
		temp->next = employeeList;
		employeeList = temp;
	}
	employeeCount++;
}
//员工 删除
void delEmployee() {
	printf("请输入您要删除的 员工 序号(输入-1退出)：");
	int index;
	scanf("%d", &index);

	if (index >= 0) {
		int res = delEmployeeByIndex(index);
		if (res) {
			printf("删除成功！\n\n");
			writeEmployee();
		}
		else {
			printf("删除失败！请正确输入现有员工序号！！\n\n");
		}
	}
}
//员工 根据下标删除
int delEmployeeByIndex(int index) {
	if (index > employeeCount || index < 1) {
		return 0;//删除失败 ，数量没那么多
	}
	//开始删除！
	Employee* p = (Employee*)malloc(sizeof(Employee));
	Employee* q = employeeList;
	p->next = employeeList;
	if (index == 1) {
		employeeList = employeeList->next;  //通过将当前链表结点next指针指向下一个结点
	}
	else {
		for (int i = 0; i < index - 1; i++) {  ///初始时q指向employeeList即链表第一个结点，删除第几个需要移动index-1次
			p = p->next;                                 //循环后p为所要删除结点的前驱
			q = q->next;                                     //将前驱结点的后继指针指向应删除结点的下一个结点就实现了删除
		}
		p->next = q->next;
	}
	employeeCount = employeeCount - 1;    //员工信息计数减一
	return 1;              //删除成功后返回布尔值为1
}
//员工 修改
void modEmployee() {
	printf("请输入您要修改的员工 序号(输入-1退出)：");
	int indexOfMod = -1;
	scanf("%d", &indexOfMod);
	if (indexOfMod > 0 && indexOfMod <= employeeCount) {
		//开始修改
		Employee* temp = employeeList;
		for (int i = 0; i < indexOfMod - 1; i++) {   //将temp指向需要修改的链表结点，即修改该结点所在员工信息
			temp = temp->next;
		}
		printf("请输入姓名 ：");
		char name[15];
		scanf("%s", name);

		printf("请输入性别 ：");
		char gender[8];
		scanf("%s", gender);

		printf("请输入出生日期 ：");
		char birth[20];
		scanf("%s", birth);

		printf("请输入职工号 ：");
		char num[20];
		scanf("%s", num);

		printf("请输入学历 ：");
		char xueli[15];
		scanf("%s", xueli);

		printf("请输入职务 ：");
		char posit[15];
		scanf("%s", posit);

		printf("请输入电话 ：");
		char tele[16];
		scanf("%s", tele);

		printf("请输入住址 ：");
		char location[25];
		scanf("%s", location);

		//输入完毕，赋值
		strcpy(temp->name, name);
		strcpy(temp->gender, gender);
		strcpy(temp->birth, birth);
		strcpy(temp->num, num);
		strcpy(temp->xueli, xueli);
		strcpy(temp->posit, posit);
		strcpy(temp->tele, tele);
		strcpy(temp->location, location);
		printf("修改成功！\n");
		writeEmployee();    //为什么没有将temp赋值给p
	}
	else {
		printf("输入错误！\n");
	}
}
//员工 查找 如果all=1:查询全部 否则按条件查询
void findEmployee(int all) {
	int select = 0;
	char conCharArr[40];
	double conNum1, conNum2;
	while (1) {//重复循环，主要是为了选择姓名等筛选条件后继续进行重新筛选后的信息输出
		printf("\n%-5s%-8s%-8s%-12s%-12s%-10s%-20s%-12s%-20s \n\n", "序号", "姓名", "性别", "出生日期", "职工号", "学历", "职务", "电话", "住址");
		int i = 1, count = 0;     //%-5s%-15s%-8s%-20s%-20s%-15s%-15s%-16s%-25s
		if (employeeList) {
			//用于统计信息所用
			Employee* t = employeeList;
			while (t) {    //对于筛选后的链表结点进行遍历输出，不符合筛选条件进行过滤不再输出
				int delFlag = 0;
				if (select == 0
					|| select == 1 && strcmp(conCharArr, t->name) == 0   //该函数值等于0则表示字符串相等，即此处出入文字进行选择也行
					|| select == 2 && strcmp(conCharArr, t->gender) == 0
					) {
					printf("%-5d%-8s%-8s%-12s%-12s%-10s%-20s%-12s%-20s \n\n", i
						, t->name
						, t->gender
						, t->birth
						, t->num
						, t->xueli
						, t->posit
						, t->tele
						, t->location
					);
					//用于统计信息所用
					count++;
				}
				else {
					delFlag = 1;//删掉
				}
				t = t->next;   //再输出下一个员工信息（下一个链表结点）
				if (delFlag) {
					delEmployeeByIndex(i--);
				}
				i++;
			}
			printf("共%d条结果\n", count);
			printf("-----------------------------------------------------------------------------------------------------\n");
			printf("\n");
		}
		//如果参数all为1，则表示列出所有就退出
		if (all == 1)break;
		//进入过滤。
		printf("【筛选器：你可以在以上结果的基础上，进行以下条件筛选：】\n");
		printf("0：退出\n");
		printf("1：按 姓名 筛选\n");
		printf("2：按 性别 筛选\n");
		printf("请输入选择：");
		scanf("%d", &select);
		if (select > 0) {
			if (0 || select == 1 || select == 2) {
				printf("请输入筛选条件：");
				scanf("%s", conCharArr);//装姓名或性别
			}
			else if (0) {
				printf("请输入筛选范围m,n，用空格隔开(m ≤X ≤n)：");
				scanf("%lf", &conNum1);
				scanf("%lf", &conNum2);
			}
		}
		else {
			break;
		}
	}
	readEmployee();//从新读取数据。
}
//员工 排序
void sortEmployee() {
	int select, i, j;
	printf("1：按 姓名     排序\n");
	printf("2：按 性别     排序\n");
	printf("3：按 出生日期 排序\n");
	printf("4：按 职工号   排序\n");
	printf("5：按 学历     排序\n");
	printf("6：按 职务     排序\n");
	printf("7：按 电话     排序\n");
	printf("8：按 住址     排序\n");
	printf("请输入选择：");
	scanf("%d", &select);
	Employee* list[100];      //将现有读取的链表数据写进用于排序的临时链表当中
	for (i = 0; i < employeeCount; i++) {
		list[i] = employeeList;
		employeeList = employeeList->next;
	}
	for (i = employeeCount - 1; i > 0; i--) {//通过嵌套两次for循环进行比较，比较字符串使用strcmp函数，比较数字直接相减     冒泡排序
		for (j = 0; j < i; j++) {
			if (0        //0||的表达式，表示逻辑真值不为0则为1
				|| select == 1 && compare(list[j]->name, list[j + 1]->name) > 0   //前后两个节点数据进行顺序比较
				|| select == 2 && compare(list[j]->gender, list[j + 1]->gender) > 0
				|| select == 3 && compare(list[j]->birth, list[j + 1]->birth) > 0
				|| select == 4 && compare(list[j]->num, list[j + 1]->num) > 0
				|| select == 5 && compare(list[j]->xueli, list[j + 1]->xueli) > 0
				|| select == 6 && compare(list[j]->posit, list[j + 1]->posit) > 0
				|| select == 7 && compare(list[j]->tele, list[j + 1]->tele) > 0
				|| select == 8 && compare(list[j]->location, list[j + 1]->location) > 0
				) {
				Employee* temp = (Employee*)malloc(sizeof(Employee));
				temp = list[j]; //交换位置   前者字母排序大于后者则进行位置调换，即按照字母从前往后排序
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}

		}
	}
	for (i = 0; i < employeeCount - 1; i++) {      //将链表指针进行绑定，将链表结点连接
		list[i]->next = list[i + 1];
	}
	list[employeeCount - 1]->next = NULL;//释放临时链表，减少内存占用
	employeeList = list[0];
	findEmployee(1);
	writeEmployee();
}

void menu() {
	//菜单
	printf("*-------------职工管理系统--------------*\n");
	printf("*-------------1 :添加员工：-------------*\n");
	printf("*-------------2 :删除员工：-------------*\n");
	printf("*-------------3 :修改员工：-------------*\n");
	printf("*-------------4 :查找员工：-------------*\n");
	printf("*-------------5 :排序员工：-------------*\n");
	printf("*-------------0 :退出    ：-------------*\n");
	printf("*---------------------------------------*\n");
	printf("请输入选择：");
}

//对比函数
int compare(int a, int b) {
	return a - b;
}
int compare(const char* a, const char* b) {
	return strcmp(a, b);
}
