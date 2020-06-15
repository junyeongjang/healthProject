#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include<queue>
#include<ctime>
#include "Customer.h"
#include "Gym.h"
using namespace std;
vector<string> split(const char line[], char delimiter) {
	vector<string> tokenizer;
	stringstream ss(line);
	string temp;

	while (getline(ss, temp, delimiter)) {
		tokenizer.push_back(temp);
	}
	
	string& lastElem = tokenizer.back();
	size_t lastElemSize = lastElem.size();
	if (lastElem.at(lastElemSize - 1) == '\n')
		lastElem = lastElem.substr(0, lastElemSize - (size_t)1);
	
	return tokenizer;
}

Gym::Gym(){}
time_t Gym::curr = time(NULL);
struct tm* Gym::d = localtime(&curr);

void Gym::addCustomer(char line[]) {
	vector<string> token = split(line, ',');

	int token12 = 0;
	if (!(token[12] == "-" || token[12] == "")) {
		token12 = stoi(token[12]);
	}
	int token14 = 0;
	if (!(token[14] == "-" || token[14] == "")) {
		token14 = stoi(token[14]);
	}
	int token15 = 0;
	if (!(token[15] == "-" || token[15] == "")) {
		token15 = stoi(token[15]);
	}
	this->customerList.push_back(Customer(stoi(token[0]), token[1], token[2], token[3], token[4], token[5], token[6], token[7] == "Y" ? true : false, token[8], 
												stod(token[9]), stod(token[10]), stod(token[11]), token12, token[13], token14, token15, token[16], token[17]));
}

void Gym::printAllCustomerInformation() {
	printCustomerListInformation(this->customerList);
}

void Gym::printCustomerListInformation(const vector<Customer>& customerListDetail) {
	for (const Customer& customers : customerListDetail) {
		printCustomerOneInformation(customers);
	}
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>�� [" << customerListDetail.size() << "]���� ����Ͽ����ϴ�.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
}
void Gym::printCustomerOneInformation(const Customer& customer){
	printf(" %3d ", customer.customerID);
	printf(" %8s ", customer.name.c_str());
	printf(" %8s ", customer.home.c_str());
	printf(" %14s ", customer.phoneNumber.c_str());
	printf(" %8s ", customer.recommender.c_str());
	printf(" %9s ", customer.birthday.c_str());
	printf(" %8s ", customer.lastOrderTickeMonth.c_str());
	customer.isPTmember ? printf(" Y ") : printf(" N ");
	printf(" %8s ", customer.trainerName.c_str());
	printf(" %.2lf ", customer.firstBMI);
	printf(" %.2lf ", customer.currentBMI);
	printf(" %.2lf ", customer.objectBMI);
	printf(" %4d ", customer.locker);
	printf(" %9s ", customer.firstRegistDate.c_str());
	printf(" %3d ", customer.countExercise);
	printf(" %3d ", customer.countPT);
	printf(" %9s ", customer.lastExerciseDate.c_str());
	printf(" %9s ", customer.expiredDate.c_str());
	printf("\n\n");
}

void Gym::printCustomerOneInformationByCustomerID(unsigned int cid) {
	if (cid <= 0) {
		printf("ȸ�� ���̵� 0 ������ ���� ã�� ��ʴϴ�. ȸ�� ���̵�� 1���� �����մϴ�. �ٽ� �ѹ� Ȯ���� �ֽʽÿ�.\n");
		return;
	}
	printCustomerOneInformation(this->customerList[cid - 1]);
}
void Gym::printCustomerListInformationByCustomerID(const vector<int>& customerListDetailByID) {
	for (int customerID : customerListDetailByID) {
		printCustomerOneInformationByCustomerID(customerID);
	}
	cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>�� [" << customerListDetailByID.size() << "]���� ����Ͽ����ϴ�.<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
}

Customer& Gym::getCustomerInformationByID(unsigned int cid) {
	if (cid <= 0) {
		printf("ȸ�� ���̵� 0 ������ ���� ã�� ��ʴϴ�. ȸ�� ���̵�� 1���� �����մϴ�. �ٽ� �ѹ� Ȯ���� �ֽʽÿ�.\n");
		return customerList[0];
	}
	return this->customerList[cid - 1];
}

// 1
void Gym::getMaxCustomerOfTrainer(){
	map<string, int> countMem;
	for (Customer& c : this->customerList) {
		if (isValidCustomer(c) && c.isPTmember)
			countMem[c.trainerName]++;
	}

	priority_queue<pair<int, string>> trainer;
	for (pair<string, int> countPair : countMem) {
		trainer.push(make_pair(countPair.second, countPair.first));
	}
	printf("���� ���� ȸ�� ���� ������ Ʈ���̳� 5�� �����մϴ�.\n\n");
	for (int i = 0; i < 5; i++) {
		pair<int, string> popElem = trainer.top();
		printf("Ʈ���̳� : [%s] ===========> [%d] ���� ȸ�� ���� �����ϰ� �ֽ��ϴ�.\n\n", popElem.second.c_str(), popElem.first);
		trainer.pop();
	}
}
// 3
void Gym::getMaxAttendanceCustomer() {
	priority_queue<pair<double, int>> attendance;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long diffDay = now - totalday(c.firstRegistDate);
			if (diffDay > 0) {
				double rate = (double)c.countExercise / diffDay;
				if (rate < 1) { // ��� Ƚ���� �� ��¥�� ���̺��� ũ�ٸ� ���� ������ �ִ� ������ �̹Ƿ� ������� �ʴ´�.
					attendance.push(make_pair(rate, c.customerID));
				}
			}
		}
	}
	
	// 10�� �̱�
	printf("���� ���� �⼮���� ������ ��� 10���� �����մϴ�.\n\n");
	for (int i = 0; i < 10; i++) {
		const Customer& popElem = getCustomerInformationByID(attendance.top().second);
		printf("%2d��° =====> ȸ����ȣ[%3d] : ȸ���̸�[%6s] : ���� ����� [%s] : ���� � Ƚ�� [%4d] : �⼮��[%lf]\n\n", i + 1, popElem.customerID, popElem.name.c_str(), popElem.firstRegistDate.c_str(), popElem.countExercise, attendance.top().first);
		attendance.pop();
	}
}
// 4
void Gym::getMaxMinHomeCustomer() {
	map<string, int> countHome;
	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c))
			countHome[c.home]++;
	}

	multimap<int, string> countHomeMulti;
	for (const pair<string, int>& pairStringInt : countHome) {
		countHomeMulti.insert(make_pair(pairStringInt.second, pairStringInt.first));
	}

	auto maxElem = countHomeMulti.rbegin();
	printf("���� ���� �������� ������ �����ϴ�. ======> ");
	for (int i = 0; i < 2; i++) {
		printf("<[%s] : [%3d��]> ", maxElem->second.c_str(), maxElem->first);
		maxElem++;
	}
	printf("\n\n");
	printf("���� ���� �������� ������ �����ϴ�. ======> ");
	auto minElem = countHomeMulti.begin();
	for (int i = 0; i < 2; i++) {
		printf("<[%s] : [%3d��]> ", minElem->second.c_str(), minElem->first);
		minElem++;
	}
	printf("\n\n");
}
// 5
void Gym::getMaxRegistMonth() {
	int month[13] = { 0, };
	for (Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			int mm = stoi(c.firstRegistDate.substr(7, 2));
			month[mm]++;
		}

	}
	int maxMonth = 1;
	int minMonth = 1;
	int maxValue = month[1];
	int minValue = month[1];


	for (int i = 2; i <= 12; i++) {
		if (month[i] > maxValue) {
			maxMonth = i;
			maxValue = month[i];
		}
		if (month[i] < minValue) {
			minMonth = i;
			minValue = month[i];
		}
	}
	for (int i = 1; i <= 12; i++) {
		printf("%2d��\t", i);
	}
	printf("\n");
	for (int i = 1; i <= 12; i++) {
		printf(" %3d\t", month[i]);
	}
	printf("\n\n");


	printf("�ִ� ��� ����[");
	for (int i = 1; i < 13; i++) {
		if (maxValue == month[i])
			printf("%d ", i);
	}
	printf("]�� �Դϴ� \n\n");

	printf("�ּ� ��� ����[");
	for (int i = 1; i < 13; i++) {
		if (minValue == month[i])
			printf("%d ", i);
	}
	printf("]�� �Դϴ� \n\n");
}
// 6
void Gym::getMaxOldCustomer() { 
	priority_queue<pair<long long, int>> oldCustomer;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long firstDate = totalday(c.firstRegistDate);
			if(now - firstDate >= 0)
				oldCustomer.push(make_pair(now - firstDate, c.customerID));
		}
	}
	
	// 10�� �̱�
	printf("��ϵ� ȸ�� �� ���� ������� ���� ��� 10���� �����մϴ�.\n\n");
	for (int i = 0; i < 10; i++) {
		const pair<long long, int>& popElem = oldCustomer.top();
		const Customer& popCustomer = getCustomerInformationByID(popElem.second);
		printf("%2d��° =====> ȸ����ȣ[%3d] : ȸ���̸�[%6s] : ��ϱ� ��������[%s] :���� ����� [%s] : ���� ��¥���� ����[%lld]\n\n", i + 1, popCustomer.customerID, popCustomer.name.c_str(), popCustomer.expiredDate.c_str(), popCustomer.firstRegistDate.c_str(), popElem.first);
		oldCustomer.pop();
	}
}
// 11
void Gym::getPTMemberAndNoLocker() {
	vector<Customer> customerList;
	for (const Customer& customers : this->customerList) {
		if (isValidCustomer(customers) && customers.isPTmember && customers.locker == 0) {
			customerList.push_back(customers);
		}
	}
	printCustomerListInformation(customerList);
}
// 12
void Gym::getRateAgeTwenty() {
	int totalValidMember = 0;
	int twentyMember = 0;

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			totalValidMember++;
			int tempAge = getAge(c);
			if (tempAge >= 20 && tempAge <= 29) {
				twentyMember++;
			}
		}
	}
	printf("��ϵ� ȸ���� ���� [%d]���̰�, 20�� ȸ���� ���� [%d]�� �Դϴ�. \n\n", totalValidMember, twentyMember);
	printf("20���� ������ ������ �����ϴ�. [%lf]%% \n", ((double)twentyMember / totalValidMember) * 100);
}
// 13
void Gym::getMaxLongestDoNotAttendanceCustomer() {
	priority_queue<pair<long long, int>> doNotAttendance;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		if (isValidCustomer(c)) {
			long long diffDay = now - totalday(c.lastExerciseDate);
			if (diffDay > 0) { // ������ ���¥�� ���� ��¥���� ũ�� ���� ������ �ִ� ������ �̹Ƿ� ó������ �ʴ´�.
				doNotAttendance.push(make_pair(diffDay, c.customerID));
			}
		}
	}
	printf("����� ������ �ֱٿ� ��� ���� ���� ��� 10���� �����մϴ�.\n\n");
	for (int i = 0; i < 10; i++) {
		const Customer& popElem = getCustomerInformationByID(doNotAttendance.top().second);
		printf("%2d��° =====> ȸ����ȣ[%3d] : ȸ���̸�[%6s] : ��ϱ� ��������[%s] : �ֱ� ���¥[%s] : �Ἦ�ϼ�[%4lld]\n\n", i + 1, popElem.customerID, popElem.name.c_str(), popElem.expiredDate.c_str(), popElem.lastExerciseDate.c_str(), doNotAttendance.top().first);
		doNotAttendance.pop();
	}
}
// 14
void Gym::getEarlyRegistCancleCustomer() {
	priority_queue<CancleCustomer> earlyCancleCustomer;
	long long now = totalday(this->d->tm_year + 1900, this->d->tm_mon + 1, this->d->tm_mday);

	for (const Customer& c : this->customerList) {
		long long diffDay = totalday(c.expiredDate) - now;

		if (isValidCustomer(c) && (diffDay <= 30)) { // ��� ���� ȸ���� �߿� 30�� �̳��� �������
			CancleCustomer temp;
			temp.id = c.customerID;

			long long lastExerciseDiffDay = now - totalday(c.lastExerciseDate); // ������ ��Ϸ� �� ��¥���� ����
			temp.diffDay = lastExerciseDiffDay;
			// ������ ���¥���� ���̸� ���� �κ�
			if (lastExerciseDiffDay >= 70)
				temp.score1 = 7;
			else if (lastExerciseDiffDay >= 60) 
				temp.score1 = 6;
			else if (lastExerciseDiffDay >= 50) 
				temp.score1 = 5;
			else if (lastExerciseDiffDay >= 40) 
				temp.score1 = 4;
			else if (lastExerciseDiffDay >= 30) 
				temp.score1 = 3;
			else if (lastExerciseDiffDay >= 20) 
				temp.score1 = 2;
			else if (lastExerciseDiffDay >= 10) 
				temp.score1 = 1;
			else
				temp.score1 = 0;
			// �⼮���� ���� �κ�
			long long firstRegistDateDiffDay = now - totalday(c.firstRegistDate);
			if (firstRegistDateDiffDay > 0) { // ���ʷ� ����� ��¥�� �� ũ�� ���� ������ �ִ� �������̹Ƿ� ����
				double rate = (double)c.countExercise / firstRegistDateDiffDay;
				if (rate < 1) {
					temp.rate = rate;
					if (rate <= 0.1)// �⼮���� 10% ������ ��� 
						temp.score2 = 3;
					else if (rate <= 0.2)// �⼮���� 20% ������ ���
						temp.score2 = 2;
					else if (rate <= 0.35) // �⼮���� 35% ������ ���
						temp.score2 = 1;
					else
						temp.score2 = 0;
				}
			}
			earlyCancleCustomer.push(temp);
		}
	}

	printf("���� ���� ����� ����� �� ���� �ο� 10���� �����մϴ�.\n\n");
	for (int i = 0; i < 10; i++) {
		const CancleCustomer popElem = earlyCancleCustomer.top();
		const Customer& popElemCustomer = getCustomerInformationByID(popElem.id);
		printf("%2d��° =====> ȸ����ȣ[%3d] : ȸ���̸�[%6s] : ��ϱ� ��������[%s] : �ֱ� ���¥[%s] : �ֱ� ���¥ - ���ó�¥ [%lld��][%d��] : �⼮�� [%5.2lf%%][%d��] :ĵ�� ����[%d]\n\n", i + 1, popElemCustomer.customerID, popElemCustomer.name.c_str(), popElemCustomer.expiredDate.c_str(), popElemCustomer.lastExerciseDate.c_str(), popElem.diffDay, popElem.score1, popElem.rate * 100, popElem.score2, popElem.score1 + popElem.score2);
		earlyCancleCustomer.pop();
	}
}
//19
void Gym::getMaxMinAgeLevel() {
	map<int, int> ageLevel;
	for (const Customer& c : this->customerList) {
		if (c.isPTmember && isValidCustomer(c)) {
			ageLevel[getAge(c) / 10]++;
		}
	}
	pair<int, int> maxPair = *ageLevel.begin();
	pair<int, int> minPair = *ageLevel.begin();

	for (pair<int, int> elem : ageLevel) {
		if (elem.second > maxPair.second)
			maxPair = elem;
		if (elem.second < minPair.second) 
			minPair = elem;
	}
	if (maxPair.first == 0) 
		cout << "���� PT�� ���� �̿��ϴ� ���ɴ�� [10�� ����] �̸�, �� [" << maxPair.second << "]�� �ֽ��ϴ�." << endl << endl;
	else
		cout << "���� PT�� ���� �̿��ϴ� ���ɴ�� [" << maxPair.first << "0]�� �̸�, �� [" << maxPair.second << "]�� �ֽ��ϴ�." << endl << endl;
	if(minPair.first == 0)
		cout << "���� PT�� ���� �̿��ϴ� ���ɴ�� [10�� ����] �̸�, �� [" << maxPair.second << "]�� �ֽ��ϴ�." << endl << endl;
	else
		cout << "���� PT�� ���� �̿��ϴ� ���ɴ�� [" << minPair.first << "0]�� �̸�, �� [" << minPair.second << "]�� �ֽ��ϴ�." << endl;
}


int compareAge(const Customer& left, const Customer& right) {
	if (getAge(left) < getAge(right))
		return 1;
	else if (getAge(left) > getAge(right))
		return -1;
	else
		return 0;
}
int getAge(const Customer& customer) {
	vector<string> YYMMDD = split(customer.birthday.c_str(), '.');
	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	int age;
	age = (Gym::d->tm_year - yy) % 100;
	if (mm - (Gym::d->tm_mon + 1) > 0)
		age = age - 1;
	else if (mm - (Gym::d->tm_mon + 1) == 0) {
		if (dd - (Gym::d->tm_mday) > 0)
			age = age - 1;
	}

	return age;
}
bool isValidCustomer(const Customer& customer) {
	vector<string> YYMMDD = split(customer.expiredDate.c_str(), ' ');
	YYMMDD[0] = YYMMDD[0].substr(0, YYMMDD[0].size() - 2);
	YYMMDD[1] = YYMMDD[1].substr(0, YYMMDD[1].size() - 2);
	YYMMDD[2] = YYMMDD[2].substr(0, YYMMDD[2].size() - 2);

	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	if (yy - (Gym::d->tm_year + 1900) < 0) {
		return false;
	}
	else if (yy - (Gym::d->tm_year + 1900) == 0) {
		if ((mm - (Gym::d->tm_mon + 1) < 0)) {
			return false;
		}
		else if ((mm - (Gym::d->tm_mon + 1) == 0)) {
			if (dd - (Gym::d->tm_mday) < 0)
				return false;
		}
	}
	return true;
}

long long totalday(int yy, int mm, int dd) {
	int months[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int i;
	long long total;

	total = ((long long)yy - 1L) * 365L;
	total += ((long long)yy - 1L) / 4L - ((long long)yy - 1L) / 100L + ((long long)yy - 1) / 400L;

	if (!(yy % 4) && yy % 100 || !(yy % 400)) // �����̸�
		months[1]++;

	for (i = 0; i < mm - 1; i++)
		total += months[i];

	total += dd;

	return total;
}

long long totalday(string strdate) {
	vector<string> YYMMDD = split(strdate.c_str(), ' ');
	YYMMDD[0] = YYMMDD[0].substr(0, YYMMDD[0].size() - 2);
	YYMMDD[1] = YYMMDD[1].substr(0, YYMMDD[1].size() - 2);
	YYMMDD[2] = YYMMDD[2].substr(0, YYMMDD[2].size() - 2);

	int yy = stoi(YYMMDD[0]);
	int mm = stoi(YYMMDD[1]);
	int dd = stoi(YYMMDD[2]);

	return totalday(yy, mm, dd);
}