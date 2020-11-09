#include <iostream>
using namespace std;

class Units{
	public:
		int hp, dmg, armor=0; //���������� ��������, �����
		string type, name, attack; //���, ��� �����, �������� �����
		int getHp() { //������ ������� �������� �����
			if (hp>0) {return hp;}
		};
		int getDmg() { //������ ������� ���� �����
			if (hp>0) {return dmg;} 
			else {return 0;}
		};
		int setDmg(int punch){ //�������� ���� � ���������� �����
			if (armor>0){
				if (hp>punch*(100-armor)/100) {hp-=(punch*(100-armor)/100);}
				else {hp=0;}
			} 
			else {
				if (hp-punch>0) {hp-=punch;}
				else {hp=0;}			
			}
		};
		void resist(){ //����� ��������� ����������� �� ����� � ������ ������� ��� ���������� �����
			if (armor>0) {cout << name << " ������� " << getHp() << " ��" << " (" << armor << "% ������������� �����)\n";}
			else {cout << name << " ������� " << getHp() << " ��\n";}
		}
};

class noArmor: public Units{
	public:
		void print(){
			cout << "\n���: " << type << "\n";
			cout << "��������: " << name << "\n";
			cout << "��������: " << hp << "\n";
			cout << "�����: " << attack << " ����=" << dmg << ")\n";
		};
		
};

class Armor: public Units{
	public:
		string equip; //������������ ���������� 
		void print(){ //����� ���������� � �����
			cout << "\n���: " << type << "\n";
			cout << "��������: " << name << "\n";
			cout << "��������: " << hp << "\n";
			cout << "����: " << dmg << "\n";
			cout << "�����: " << equip << " (������=" << armor << ")\n";
		};
};

class Wolf: public noArmor{
	public:
		int dex; //���������� ��������
	public: Wolf()
		{
			type="��������";
			name="Wolf";
			hp=25;
			dmg=5;
			dex=8;
		}
		void print()
		{
			cout << "\n���: " << type << "\n";
			cout << "��������: " << name << "\n";
			cout << "��������: " << hp << "\n";
			cout << "����: " << dmg << "\n";
			cout << "��������: " << dex << "\n";
		}
};

class Catapult: public noArmor{
	public: Catapult()
		{
			type="��������";
			name="Catapult";
			hp=641;
			attack="Bolt (Untouchable Horror";
			dmg=18;	
		}
};

class Bard: public Armor{
	public: Bard()
		{
			type="������";
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
			type="������";
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
			type="������";
			name="Ranger";
			hp=122+Wolf().hp;
			dmg=15+Wolf().dmg;
			equip="Iron armor";
			armor=40;
		}
		void print()
		{
			cout << "\n���: " << type << "\n";
			cout << "��������: " << name << "\n";
			cout << "��������: " << hp << " (" << Wolf().hp << "-�������� �����)\n";
			cout << "����: " << dmg << " (" << Wolf().dmg << "-���� �����)\n";
			cout << "�����: " << equip << " (������=" << armor << ")\n";
			cout << "������ ���� �������� ��������� �� �����\n";
		}
};

class Ranger2: public Ranger1{
	public: Ranger2()
		{
			type="������";
			name="Ranger";
			hp=140+Wolf().hp;;
			dmg=15+Wolf().dmg;;
			equip="Steel armor";
			armor=50;
		}
};
