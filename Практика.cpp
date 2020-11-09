#include <iostream>
#include <stdio.h>
#include "classes.h"
using namespace std;

int menu(){ //������� ������ ����
	system("cls");
	cout << "1. ���������� �� �����\n"
			"2. �����\n"
			"3. ���\n\n"
			"4. �����\n";	
}

int value(){ //������� ������ ������ � ��������� ����
	int val;
	cin >> val;
	return val;
}

void stats(){ //������� �������� ����� �������������

	system("cls");
	cout << "����� �������������� ���� ������� ������\n\n"; 
	cout << "����� ����: " << Catapult().dmg+Ranger1().dmg+Bard().dmg+Paladin().dmg+Ranger2().dmg << "\n"
			"����� ������: " << Ranger1().armor+Bard().armor+Paladin().armor+Ranger2().armor << "\n"
			"����� ��������: " << Catapult().hp+Ranger1().hp+Bard().hp+Paladin().hp+Ranger2().hp << "\n" 
			"����� ����������� �����: 5 ������ � 2 e������ ��������\n";
	system("pause");
}

void units(){ //������� ������ ���������� � ������ �� ������
	system("cls"); 
	cout << "������ ������ ������: \n"
			"1. ����������\n"
			"2. �������� � �������� �������\n"
			"3. ����\n"
			"4. �������\n"	
			"5. �������� � �������� �������\n"
			"6. ����\n\n"	
			"0. �����\n";
	switch (value())
	{
		case 0: menu(); break;
		case 1: Catapult().print(); system("pause"); units(); break;
		case 2: Ranger1().print(); system("pause"); units(); break;
		case 3: Bard().print(); system("pause"); units(); break;
		case 4: Paladin().print(); system("pause"); units(); break;	
		case 5: Ranger2().print(); system("pause"); units(); break;
		case 6: Wolf().print(); system("pause"); units(); break;
		default: units(); break;	
	}
}

void listOfUnits(Units* mas, int length){ //������ ������ ��� ������ ����������
	for (int i=1; i<=length; i++)
	{
		if (mas[i-1].getHp()>0)
		{
			cout << i << ". " << mas[i-1].name << "\n";	
		}
		else {;}
	}
}

void allStats(int HP1, int DMG1, int HP2, int DMG2){ //����� ���������� � ����� ������� ����
		cout << "\n�������� ����� �����: " << HP1 << "\n";
		cout << "���� ����� �����: " << DMG1 << "\n";
		cout << "\n�������� ����� ����������: " << HP2 << "\n";
		cout << "���� ����� ����������: " << DMG2 << "\n";
}

void fight(Units* Army, Units* ArmyP, int HP1, int DMG1, int HP2, int DMG2, int length){ //������� ���
	int num, count=1; //������� �����
	system ("cls");
	cout << "��� ����������!\n";
	int pos=0; //������� ���������� ���������� ����� � �������
	while(HP1>0 and HP2>0)
	{
		if (count%2==1)
		{
			cout << "�������� �����, ������� �� ������ ��������� \n";
			listOfUnits(Army, length);
			cin >> num;
			HP2=0; DMG2=0;
			cout << "\n���� " << Army[num-1].name << " ������� " << Army[num-1].getDmg() << " ������ �����!\n";
			for(int i=0; i<length; i++)
			{
				ArmyP[i].setDmg(Army[num-1].getDmg());
				if (ArmyP[i].getHp()==0) {;}
				else {cout << "� ���������� "; ArmyP[i].resist();}
				HP2+=ArmyP[i].getHp();
				DMG2+=ArmyP[i].getDmg();
			}
		}
		if (count%2==0)
		{
			cout << "����� ���������� " << "\n";
			HP1=0; DMG1=0;
			if (ArmyP[pos].getHp()>0) 
			cout << "\n��������� " << ArmyP[pos].name << " ������� " << ArmyP[pos].getDmg() << " ������ �����!\n";
			for(int i=0; i<length; i++)
			{
				Army[i].setDmg(ArmyP[pos].getDmg());
				if (Army[i].getHp()==0) {;}
				else {cout << "� ������ "; Army[i].resist();}
				HP1+=Army[i].getHp();
				DMG1+=Army[i].getDmg();
			}
			pos++;
			if(pos>length-1){pos=0;}
		}
		allStats(HP1, DMG1, HP2, DMG2);
		count++;
		system ("pause");
		system ("cls");
	}
	cout << "��� �������.\n";	
	system ("pause");
	menu();
}

void recruiting(){ //���� �����
	int length, num, HP1=0, HP2=0, DMG1=0, DMG2=0; //������� �����, ����� ���������� �������� � ����� ����� 1 � 2
	system("cls");
	cout << "������� ���������� ������ � ����� ������: ";
	cin >> length;
	Units* Army = new Units[length];   			   //������ ������������� �����
	cout << "�������� ������ ��� ����� �����: \n"
			"1. ����������\n"
			"2. �������� � �������� �������\n"
			"3. ����\n"
			"4. �������\n"	
			"5. �������� � �������� �������\n\n";
	for(int i=0;i<length;i++)
	{
		cin >> num;
		if (0<num and num<6)
		{
			switch(num){
 				case 1: {Army[i]=Catapult(); break;}	
				case 2: {Army[i]=Ranger1(); break;}
				case 3: {Army[i]=Bard(); break;}
				case 4: {Army[i]=Paladin(); break;}
				case 5: {Army[i]=Ranger2(); break;}
				default: break;	 
			}
			HP1+=Army[i].getHp();
			DMG1+=Army[i].getDmg();
		}
		else {cout << "���������� �����\n"; i--;}
	}
	cout << "�������� ����� ����� " << HP1 << "\n\n";
	Units* ArmyP = new Units[length]; //������ ����� ����������
	cout << "�������� ������ ��� ����� ����������: \n\n";
	for(int i=0;i<length;i++)
	{
		cin >> num;
		if (0<num and num<6)
		{
			switch(num){
 				case 1: {ArmyP[i]=Catapult(); break;}	
				case 2: {ArmyP[i]=Ranger1(); break;}
				case 3: {ArmyP[i]=Bard(); break;}
				case 4: {ArmyP[i]=Paladin(); break;}
				case 5: {ArmyP[i]=Ranger2(); break;}
				default: break;	 
			}
			HP2+=ArmyP[i].getHp();
			DMG2+=ArmyP[i].getDmg();
		}
		else {cout << "���������� �����\n"; i--;}
	}
	cout << "�������� ����� ����� " << HP2 << "\n\n";
	system("pause");
	fight(Army, ArmyP, HP1, DMG1, HP2, DMG2, length);
}

int main(){
	setlocale(LC_ALL, "Rus");
	while(1)
	{
		menu();
		switch(value())
		{
			case 1:	stats(); break;	
			case 2:	units(); break;
			case 3: recruiting(); break;
			case 4: system("cls"); cout << "�������� ���..."; exit(0);
		}
	}
}
