#include <iostream>
using namespace std;

class Units{
	public:
		int hp, dmg, armor=0; //показатели здоровья, урона
		string type, name, attack; //тип, имя юнита, название атаки
		int getHp() { //узнать текущее здоровье юнита
			if (hp>0) {return hp;}
		};
		int getDmg() { //узнать текущий урон юнита
			if (hp>0) {return dmg;} 
			else {return 0;}
		};
		int setDmg(int punch){ //получить урон в результате атаки
			if (armor>0){
				if (hp>punch*(100-armor)/100) {hp-=(punch*(100-armor)/100);}
				else {hp=0;}
			} 
			else {
				if (hp-punch>0) {hp-=punch;}
				else {hp=0;}			
			}
		};
		void resist(){ //вывод системных уведомлений об уроне с учётом наличия или отсутствия брони
			if (armor>0) {cout << name << " остаётся " << getHp() << " хп" << " (" << armor << "% сопротивление урону)\n";}
			else {cout << name << " остаётся " << getHp() << " хп\n";}
		}
};

class noArmor: public Units{
	public:
		void print(){
			cout << "\nТип: " << type << "\n";
			cout << "Название: " << name << "\n";
			cout << "Здоровье: " << hp << "\n";
			cout << "Атака: " << attack << " урон=" << dmg << ")\n";
		};
		
};

class Armor: public Units{
	public:
		string equip; //наименование экипировки 
		void print(){ //вывод информации о юните
			cout << "\nТип: " << type << "\n";
			cout << "Название: " << name << "\n";
			cout << "Здоровье: " << hp << "\n";
			cout << "Урон: " << dmg << "\n";
			cout << "Броня: " << equip << " (защита=" << armor << ")\n";
		};
};

class Wolf: public noArmor{
	public:
		int dex; //показатель скорости
	public: Wolf()
		{
			type="Животное";
			name="Wolf";
			hp=25;
			dmg=5;
			dex=8;
		}
		void print()
		{
			cout << "\nТип: " << type << "\n";
			cout << "Название: " << name << "\n";
			cout << "Здоровье: " << hp << "\n";
			cout << "Урон: " << dmg << "\n";
			cout << "Скорость: " << dex << "\n";
		}
};

class Catapult: public noArmor{
	public: Catapult()
		{
			type="Механизм";
			name="Catapult";
			hp=641;
			attack="Bolt (Untouchable Horror";
			dmg=18;	
		}
};

class Bard: public Armor{
	public: Bard()
		{
			type="Солдат";
			name="Bard";
			hp=99;
			dmg=1;
			equip="Iron armor";
			armor=40;	
		}
};

class Paladin: public Armor{
	public: Paladin()
	   {
			type="Солдат";
			name="Paladin";
			hp=140;
			dmg=15;	
			equip="Iron armor";
			armor=40;
		}
};

class Ranger1: public Armor{
	public: Ranger1()
		{
			type="Солдат";
			name="Ranger";
			hp=122+Wolf().hp;
			dmg=15+Wolf().dmg;
			equip="Iron armor";
			armor=40;
		}
		void print()
		{
			cout << "\nТип: " << type << "\n";
			cout << "Название: " << name << "\n";
			cout << "Здоровье: " << hp << " (" << Wolf().hp << "-здоровье волка)\n";
			cout << "Урон: " << dmg << " (" << Wolf().dmg << "-урон волка)\n";
			cout << "Броня: " << equip << " (защита=" << armor << ")\n";
			cout << "Данный юнит является всадником на волке\n";
		}
};

class Ranger2: public Ranger1{
	public: Ranger2()
		{
			type="Солдат";
			name="Ranger";
			hp=140+Wolf().hp;;
			dmg=15+Wolf().dmg;;
			equip="Steel armor";
			armor=50;
		}
};
