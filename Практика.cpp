#include <iostream>
#include <stdio.h>
#include "classes.h"
using namespace std;

int menu(){ //функция вызова меню
	system("cls");
	cout << "1. Информация об армии\n"
			"2. Юниты\n"
			"3. Бой\n\n"
			"4. Выход\n";	
}

int value(){ //функция выбора пункта в различных меню
	int val;
	cin >> val;
	return val;
}

void stats(){ //функция подсчёта общих характеристик

	system("cls");
	cout << "Общие характеристики всех базовых юнитов\n\n"; 
	cout << "Общий урон: " << Catapult().dmg+Ranger1().dmg+Bard().dmg+Paladin().dmg+Ranger2().dmg << "\n"
			"Общая защита: " << Ranger1().armor+Bard().armor+Paladin().armor+Ranger2().armor << "\n"
			"Общее здоровье: " << Catapult().hp+Ranger1().hp+Bard().hp+Paladin().hp+Ranger2().hp << "\n" 
			"Общая численность войск: 5 юнитов и 2 eздовых животных\n";
	system("pause");
}

void units(){ //функция вывода информации о каждом из юнитов
	system("cls"); 
	cout << "Полный список юнитов: \n"
			"1. Катапульта\n"
			"2. Следопыт в железном доспехе\n"
			"3. Бард\n"
			"4. Паладин\n"	
			"5. Следопыт в стальном доспехе\n"
			"6. Волк\n\n"	
			"0. Назад\n";
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

void listOfUnits(Units* mas, int length){ //список юнитов для выбора атакующего
	for (int i=1; i<=length; i++)
	{
		if (mas[i-1].getHp()>0)
		{
			cout << i << ". " << mas[i-1].name << "\n";	
		}
		else {;}
	}
}

void allStats(int HP1, int DMG1, int HP2, int DMG2){ //общая информация в конце каждого хода
		cout << "\nЗдоровье вашей армии: " << HP1 << "\n";
		cout << "Урон вашей армии: " << DMG1 << "\n";
		cout << "\nЗдоровье армии противника: " << HP2 << "\n";
		cout << "Урон армии противника: " << DMG2 << "\n";
}

void fight(Units* Army, Units* ArmyP, int HP1, int DMG1, int HP2, int DMG2, int length){ //функция боя
	int num, count=1; //счётчик ходов
	system ("cls");
	cout << "Бой начинается!\n";
	int pos=0; //позиция атакующего вражеского юнита в массиве
	while(HP1>0 and HP2>0)
	{
		if (count%2==1)
		{
			cout << "Выберите юнита, которым вы хотите атаковать \n";
			listOfUnits(Army, length);
			cin >> num;
			HP2=0; DMG2=0;
			cout << "\nЮнит " << Army[num-1].name << " наносит " << Army[num-1].getDmg() << " единиц урона!\n";
			for(int i=0; i<length; i++)
			{
				ArmyP[i].setDmg(Army[num-1].getDmg());
				if (ArmyP[i].getHp()==0) {;}
				else {cout << "У вражеского "; ArmyP[i].resist();}
				HP2+=ArmyP[i].getHp();
				DMG2+=ArmyP[i].getDmg();
			}
		}
		if (count%2==0)
		{
			cout << "Атака противника " << "\n";
			HP1=0; DMG1=0;
			if (ArmyP[pos].getHp()>0) 
			cout << "\nВражеский " << ArmyP[pos].name << " наносит " << ArmyP[pos].getDmg() << " единиц урона!\n";
			for(int i=0; i<length; i++)
			{
				Army[i].setDmg(ArmyP[pos].getDmg());
				if (Army[i].getHp()==0) {;}
				else {cout << "У вашего "; Army[i].resist();}
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
	cout << "Бой окончен.\n";	
	system ("pause");
	menu();
}

void recruiting(){ //сбор войск
	int length, num, HP1=0, HP2=0, DMG1=0, DMG2=0; //масштаб армии, общее количество здоровья и урона армий 1 и 2
	system("cls");
	cout << "Укажите количество юнитов в одном войске: ";
	cin >> length;
	Units* Army = new Units[length];   			   //массив дружественной армии
	cout << "Выберите юнитов для своей армии: \n"
			"1. Катапульта\n"
			"2. Следопыт в железном доспехе\n"
			"3. Бард\n"
			"4. Паладин\n"	
			"5. Следопыт в стальном доспехе\n\n";
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
		else {cout << "Попробуйте снова\n"; i--;}
	}
	cout << "Здоровье вашей армии " << HP1 << "\n\n";
	Units* ArmyP = new Units[length]; //массив армии противника
	cout << "Выберите юнитов для армии противника: \n\n";
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
		else {cout << "Попробуйте снова\n"; i--;}
	}
	cout << "Здоровье армии врага " << HP2 << "\n\n";
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
			case 4: system("cls"); cout << "Заходите ещё..."; exit(0);
		}
	}
}
