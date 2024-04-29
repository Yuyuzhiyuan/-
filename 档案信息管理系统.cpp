#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <io.h>



//���� Ա�� ����
struct Employee {
	char name[15];        // ����
	char gender[8];        // �Ա�
	char birth[20];         // �������� 
	char num[20];         // ְ���� 
	char xueli[15];         // ѧ��
	char posit[15];        // ְ��
	char tele[16];          // �绰
	char location[25];      // סַ
	struct Employee* next;//��ʽ�洢
};
Employee* employeeList;//����ȫ�� Ա�� ָ��  �����õ�L
int employeeCount = 0;//Ա�� ������¼

int compare(int a, int b);
int compare(const char* a, const char* b);//

//Ա�� �����ļ�
void readEmployee();
//Ա�� д���ļ�
void writeEmployee();
//Ա�� ��Ӽ�¼
void addEmployee();
void addOneEmployee(Employee* employee);
//Ա�� ɾ����¼
void delEmployee();
//Ա�� �����±�ɾ��
int delEmployeeByIndex(int index);
//Ա�� �޸ļ�¼
void modEmployee();
//Ա�� ���Ҽ�¼
void findEmployee(int all);
//Ա�� ����
void sortEmployee();
//����
void exchangeEmployee(int i, int j);
//�����жϺ���

//�˵�
void menu();

// ������
int main() {
	//��ȡ����
	readEmployee();//��ȡԱ��
	while (1) {
		int choice;
		menu();
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			addEmployee();//���Ա��
			break;
		case 2:
			findEmployee(1);//����Ա��
			delEmployee();//ɾ��Ա��
			break;
		case 3:
			findEmployee(1);//����Ա��
			modEmployee();//�޸�Ա��
			break;
		case 4:
			findEmployee(0);//����Ա��
			break;
		case 5:
			sortEmployee();//����Ա��
			break;
		case 0:
			printf("\n\n\n\t\t\t��лʹ��\n\n\n");
			exit(0);//C ++exit������ֹ���̣��˳�����
		default:
			getchar();
			printf("\n\n\n\t��ʾ��û�����ѡ�����������!\n\n\n\n");
			system("pause");
			break;
		}
	}
	return 0;
}



//Ա�� �����ļ�
void readEmployee() {
	FILE* fp;
	fp = fopen("EmployeeData.data", "r");    //	FILE* =fopen("EmployeeData.data", "r");���ļ�����fp����ļ��ṹ�壬
	//��ȡ�ļ�Ϊ��                                               ���ı���ʽ��ȡEmployeeData.data�ļ�
	if (fp == NULL)return;
	//��ȡ����
	fread(&employeeCount, sizeof(int), 1, fp);//���ļ����ݸ����Ž�employeeCount  ��1ָԪ�ظ���
	employeeList = NULL;
	Employee* tail = employeeList;   //���tailû��
	//д�뵽����
	for (int i = 0; i < employeeCount; i++) {
		Employee* p = (Employee*)malloc(sizeof(Employee));//����һ��Employee�ṹ���С�ĵ�ַ�ռ�
		fread(p, sizeof(Employee), 1, fp);   //��Employee���󷵻ظ�p���ָ��    ���ֶ�̬�ڴ����ռ��Լ�ڴ棬�����ⲿ��Ҫ���ú����ڲ�ָ���Ӧ�ռ�
		p->next = NULL;
		//ָ��Ϊ����ֵ��
		if (employeeList == NULL) {
			employeeList = p;
			tail = p;
		}
		else {     //���tailָ�벢û���õ�
			tail->next = p;
			tail = p;
		}
	}
	fclose(fp);//�ر��ļ�����
}
//Ա�� д���ļ�
void writeEmployee() {
	//���浽������Ϣ��
	FILE* fp;
	fp = fopen("EmployeeData.data", "wb");   //д�����������
	Employee* p = employeeList;
	//�ȱ������
	fwrite(&employeeCount, sizeof(employeeCount), 1, fp);
	//��������
	while (p) {     //��pд�룬����������д�뱾���ļ�
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
//Ա�� ��Ӽ�¼
void addEmployee() {
	char selectYNFlag = 'y';
	while (selectYNFlag == 'y' || selectYNFlag == 'Y') {
		printf("\n");
		Employee* tempValue = (Employee*)malloc(sizeof(Employee)); //�������·����ַ�ռ䡣
		printf("���������� ��");
		char name[15];
		scanf("%s", name);
		strcpy(tempValue->name, name); 
		printf("�������Ա� ��");
		char gender[8];
		scanf("%s", gender);
		strcpy(tempValue->gender, gender);
		printf("������������� ��");
		char birth[20];
		scanf("%s", birth);
		strcpy(tempValue->birth, birth);
		printf("������ְ���� ��");
		char num[20];
		scanf("%s", num);
		strcpy(tempValue->num, num);
		printf("������ѧ�� ��");
		char xueli[15];
		scanf("%s", xueli);
		strcpy(tempValue->xueli, xueli);
		printf("������ְ�� ��");
		char posit[15];
		scanf("%s", posit);
		strcpy(tempValue->posit, posit);
		printf("������绰 ��");
		char tele[16];
		scanf("%s", tele);
		strcpy(tempValue->tele, tele);
		printf("������סַ ��");
		char location[25];
		scanf("%s", location);
		strcpy(tempValue->location, location);
		tempValue->next = NULL;
		addOneEmployee(tempValue);     //�����γɵ��������������   �γ��µ�employeeList��ͷ��㣩�����·�ͷ�巨����
		printf("\n�Ƿ����¼�룿(y/n)");
		getchar();//I/O�������ַ���ֱ���س�
		scanf("%c", &selectYNFlag);
	}
	writeEmployee();
	printf("\n*****************************\n");
	printf("¼�����\n");
	printf("*****************************\n");
}
void addOneEmployee(Employee* temp) {
	//����ͷ�巨
	if (employeeList == NULL) {
		employeeList = temp;
	}
	else {
		temp->next = employeeList;
		employeeList = temp;
	}
	employeeCount++;
}
//Ա�� ɾ��
void delEmployee() {
	printf("��������Ҫɾ���� Ա�� ���(����-1�˳�)��");
	int index;
	scanf("%d", &index);

	if (index >= 0) {
		int res = delEmployeeByIndex(index);
		if (res) {
			printf("ɾ���ɹ���\n\n");
			writeEmployee();
		}
		else {
			printf("ɾ��ʧ�ܣ�����ȷ��������Ա����ţ���\n\n");
		}
	}
}
//Ա�� �����±�ɾ��
int delEmployeeByIndex(int index) {
	if (index > employeeCount || index < 1) {
		return 0;//ɾ��ʧ�� ������û��ô��
	}
	//��ʼɾ����
	Employee* p = (Employee*)malloc(sizeof(Employee));
	Employee* q = employeeList;
	p->next = employeeList;
	if (index == 1) {
		employeeList = employeeList->next;  //ͨ������ǰ������nextָ��ָ����һ�����
	}
	else {
		for (int i = 0; i < index - 1; i++) {  ///��ʼʱqָ��employeeList�������һ����㣬ɾ���ڼ�����Ҫ�ƶ�index-1��
			p = p->next;                                 //ѭ����pΪ��Ҫɾ������ǰ��
			q = q->next;                                     //��ǰ�����ĺ��ָ��ָ��Ӧɾ��������һ������ʵ����ɾ��
		}
		p->next = q->next;
	}
	employeeCount = employeeCount - 1;    //Ա����Ϣ������һ
	return 1;              //ɾ���ɹ��󷵻ز���ֵΪ1
}
//Ա�� �޸�
void modEmployee() {
	printf("��������Ҫ�޸ĵ�Ա�� ���(����-1�˳�)��");
	int indexOfMod = -1;
	scanf("%d", &indexOfMod);
	if (indexOfMod > 0 && indexOfMod <= employeeCount) {
		//��ʼ�޸�
		Employee* temp = employeeList;
		for (int i = 0; i < indexOfMod - 1; i++) {   //��tempָ����Ҫ�޸ĵ������㣬���޸ĸý������Ա����Ϣ
			temp = temp->next;
		}
		printf("���������� ��");
		char name[15];
		scanf("%s", name);

		printf("�������Ա� ��");
		char gender[8];
		scanf("%s", gender);

		printf("������������� ��");
		char birth[20];
		scanf("%s", birth);

		printf("������ְ���� ��");
		char num[20];
		scanf("%s", num);

		printf("������ѧ�� ��");
		char xueli[15];
		scanf("%s", xueli);

		printf("������ְ�� ��");
		char posit[15];
		scanf("%s", posit);

		printf("������绰 ��");
		char tele[16];
		scanf("%s", tele);

		printf("������סַ ��");
		char location[25];
		scanf("%s", location);

		//������ϣ���ֵ
		strcpy(temp->name, name);
		strcpy(temp->gender, gender);
		strcpy(temp->birth, birth);
		strcpy(temp->num, num);
		strcpy(temp->xueli, xueli);
		strcpy(temp->posit, posit);
		strcpy(temp->tele, tele);
		strcpy(temp->location, location);
		printf("�޸ĳɹ���\n");
		writeEmployee();    //Ϊʲôû�н�temp��ֵ��p
	}
	else {
		printf("�������\n");
	}
}
//Ա�� ���� ���all=1:��ѯȫ�� ����������ѯ
void findEmployee(int all) {
	int select = 0;
	char conCharArr[40];
	double conNum1, conNum2;
	while (1) {//�ظ�ѭ������Ҫ��Ϊ��ѡ��������ɸѡ�����������������ɸѡ�����Ϣ���
		printf("\n%-5s%-8s%-8s%-12s%-12s%-10s%-20s%-12s%-20s \n\n", "���", "����", "�Ա�", "��������", "ְ����", "ѧ��", "ְ��", "�绰", "סַ");
		int i = 1, count = 0;     //%-5s%-15s%-8s%-20s%-20s%-15s%-15s%-16s%-25s
		if (employeeList) {
			//����ͳ����Ϣ����
			Employee* t = employeeList;
			while (t) {    //����ɸѡ�����������б��������������ɸѡ�������й��˲������
				int delFlag = 0;
				if (select == 0
					|| select == 1 && strcmp(conCharArr, t->name) == 0   //�ú���ֵ����0���ʾ�ַ�����ȣ����˴��������ֽ���ѡ��Ҳ��
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
					//����ͳ����Ϣ����
					count++;
				}
				else {
					delFlag = 1;//ɾ��
				}
				t = t->next;   //�������һ��Ա����Ϣ����һ�������㣩
				if (delFlag) {
					delEmployeeByIndex(i--);
				}
				i++;
			}
			printf("��%d�����\n", count);
			printf("-----------------------------------------------------------------------------------------------------\n");
			printf("\n");
		}
		//�������allΪ1�����ʾ�г����о��˳�
		if (all == 1)break;
		//������ˡ�
		printf("��ɸѡ��������������Ͻ���Ļ����ϣ�������������ɸѡ����\n");
		printf("0���˳�\n");
		printf("1���� ���� ɸѡ\n");
		printf("2���� �Ա� ɸѡ\n");
		printf("������ѡ��");
		scanf("%d", &select);
		if (select > 0) {
			if (0 || select == 1 || select == 2) {
				printf("������ɸѡ������");
				scanf("%s", conCharArr);//װ�������Ա�
			}
			else if (0) {
				printf("������ɸѡ��Χm,n���ÿո����(m ��X ��n)��");
				scanf("%lf", &conNum1);
				scanf("%lf", &conNum2);
			}
		}
		else {
			break;
		}
	}
	readEmployee();//���¶�ȡ���ݡ�
}
//Ա�� ����
void sortEmployee() {
	int select, i, j;
	printf("1���� ����     ����\n");
	printf("2���� �Ա�     ����\n");
	printf("3���� �������� ����\n");
	printf("4���� ְ����   ����\n");
	printf("5���� ѧ��     ����\n");
	printf("6���� ְ��     ����\n");
	printf("7���� �绰     ����\n");
	printf("8���� סַ     ����\n");
	printf("������ѡ��");
	scanf("%d", &select);
	Employee* list[100];      //�����ж�ȡ����������д�������������ʱ������
	for (i = 0; i < employeeCount; i++) {
		list[i] = employeeList;
		employeeList = employeeList->next;
	}
	for (i = employeeCount - 1; i > 0; i--) {//ͨ��Ƕ������forѭ�����бȽϣ��Ƚ��ַ���ʹ��strcmp�������Ƚ�����ֱ�����     ð������
		for (j = 0; j < i; j++) {
			if (0        //0||�ı��ʽ����ʾ�߼���ֵ��Ϊ0��Ϊ1
				|| select == 1 && compare(list[j]->name, list[j + 1]->name) > 0   //ǰ�������ڵ����ݽ���˳��Ƚ�
				|| select == 2 && compare(list[j]->gender, list[j + 1]->gender) > 0
				|| select == 3 && compare(list[j]->birth, list[j + 1]->birth) > 0
				|| select == 4 && compare(list[j]->num, list[j + 1]->num) > 0
				|| select == 5 && compare(list[j]->xueli, list[j + 1]->xueli) > 0
				|| select == 6 && compare(list[j]->posit, list[j + 1]->posit) > 0
				|| select == 7 && compare(list[j]->tele, list[j + 1]->tele) > 0
				|| select == 8 && compare(list[j]->location, list[j + 1]->location) > 0
				) {
				Employee* temp = (Employee*)malloc(sizeof(Employee));
				temp = list[j]; //����λ��   ǰ����ĸ������ں��������λ�õ�������������ĸ��ǰ��������
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}

		}
	}
	for (i = 0; i < employeeCount - 1; i++) {      //������ָ����а󶨣�������������
		list[i]->next = list[i + 1];
	}
	list[employeeCount - 1]->next = NULL;//�ͷ���ʱ���������ڴ�ռ��
	employeeList = list[0];
	findEmployee(1);
	writeEmployee();
}

void menu() {
	//�˵�
	printf("*-------------ְ������ϵͳ--------------*\n");
	printf("*-------------1 :���Ա����-------------*\n");
	printf("*-------------2 :ɾ��Ա����-------------*\n");
	printf("*-------------3 :�޸�Ա����-------------*\n");
	printf("*-------------4 :����Ա����-------------*\n");
	printf("*-------------5 :����Ա����-------------*\n");
	printf("*-------------0 :�˳�    ��-------------*\n");
	printf("*---------------------------------------*\n");
	printf("������ѡ��");
}

//�ԱȺ���
int compare(int a, int b) {
	return a - b;
}
int compare(const char* a, const char* b) {
	return strcmp(a, b);
}
