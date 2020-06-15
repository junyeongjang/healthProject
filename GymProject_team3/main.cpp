#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include "Customer.h"
#include "Gym.h"
using namespace std;

void showMenuPrint() {
	printf("########################################################################\n");
	printf("0. ȸ�� ���� ��� ��� \n\n");
	printf("1. ���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�? \n\n");
	printf("3. ���� �⼮���� ����ȸ����? \n\n");
	printf("4. ���� ����/���� ȸ���� ��� ����? \n\n");
	printf("5. ���� ����� ����/���� ����? \n\n");
	printf("6. ���� ������ ȸ����? \n\n");
	printf("11. PT�� �޴� ȸ�� �� ��Ŀ�� �̿����� �ʴ� ȸ����? \n\n");
	printf("12. ȸ�� �� ���̰� 20���� ȸ���� ������? \n\n");
	printf("13. ���� �������� ���� ���� ȸ����? \n\n");
	printf("14. ���� ���� ����� ����� ���ɼ��� ���� ȸ����? \n\n");
	printf("19. PT�� ���� ����/���� �̿��ϴ� ���ɴ��? \n\n");
	printf("99. �����ϱ� \n\n");
	printf("�޴� �������� �����ϼ��� >> ");
}
int main() {
	FILE* fp = fopen("JOJO.csv", "r+t");
	Gym myGym;
	char line[1000];
	int n = 0;
	fgets(line, sizeof(line), fp);
	while (!feof(fp)) {
		fgets(line, sizeof(line), fp);
		myGym.addCustomer(line);
	}
	int menuSelect;
	showMenuPrint();
	while (true) {
		cin >> menuSelect;
		system("cls");
		printf("..........................................................\n\n");
		switch (menuSelect) {
		case 1:
			myGym.getMaxCustomerOfTrainer();
			break;
		case 3:
			myGym.getMaxAttendanceCustomer();
			break;
		case 4:
			myGym.getMaxMinHomeCustomer();
			break;
		case 5:
			myGym.getMaxRegistMonth();
			break;
		case 6:
			myGym.getMaxOldCustomer();
			break;
		case 11:
			myGym.getPTMemberAndNoLocker();
			break;
		case 12:
			myGym.getRateAgeTwenty();
			break;
		case 13:
			myGym.getMaxLongestDoNotAttendanceCustomer();
			break;
		case 14:
			myGym.getEarlyRegistCancleCustomer();
			break;
		case 19:
			myGym.getMaxMinAgeLevel();
			break;
		case 0:
			myGym.printAllCustomerInformation();
			break;
		case 99:
			fclose(fp);
			return 0;
		default:
			printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���.\n");
		}
		printf("..........................................................\n\n");
		showMenuPrint();
	}
	return 0;
}