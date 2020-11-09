#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Student
{

public:

	string fio1, fio2, fio3;
	int day, month, year;
	int year_of_entrance; // год поступления в институт
	string faculty;
	string department; // кафедра
	int group;
	int number_of_gradebook; // номер зачётной книжки
	
	vector<vector<pair<string, int> > > sessions; // сессии состоят из предметов, предметы - из названий и оценок
	

	void set_fio1(string fio1)
	{
		this->fio1 = fio1;
	}
	
	void set_fio2(string fio2)
	{
		this->fio2 = fio2;
	}
	
	void set_fio3(string fio3)
	{
		this->fio3 = fio3;
	}
	
	void set_birthday(int day, int month, int year)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	void set_year_of_entrance(int year_of_entrance)
	{
		this->year_of_entrance = year_of_entrance;
	}
	
	void set_faculty(string faculty)
	{
		this->faculty = faculty;
	}
	
	void set_department(string department)
	{
		this->department = department;
	}
	
	void set_group(int group)
	{
		this->group = group;
	}
	
	void set_number_of_gradebook(int number_of_gradebook)
	{
		this->number_of_gradebook = number_of_gradebook;
	}
	
	void add_empty_session()
	{
		this->sessions.push_back(vector<pair<string, int> >()); // добавляем пустой вектор
	}
	
	void add_subject(int session_number, string name, int grade)
	{
		// добавляем предмет к сессии
		this->sessions[session_number].push_back(make_pair(name, grade)); 
	}
	
	void delete_session(int session_number)
	{
		this->sessions.erase(this->sessions.begin() + session_number);
	}
	
	void delete_subject(int session_number, int subject_number)
	{
		this->sessions[session_number].erase(this->sessions[session_number].begin() + subject_number);
	}
	
	void change_subject_name(int session_number, int subject_number, string new_name)
	{
		this->sessions[session_number][subject_number].first = new_name;
	}
	
	void change_subject_grade(int session_number, int subject_number, int new_grade)
	{
		this->sessions[session_number][subject_number].second = new_grade;
	}
	
};

void do_work(vector <Student> & students_vec)
{
	
	/*
		Вариант 36. Распечатать в порядке убывания всех студентов, по количеству пятерок во 2-ом
		семестре с поиском лиц определенного пола
	*/
	vector<pair<int, Student> > a;
	for (int i = 0; i < (int) students_vec.size(); ++i)
	{
		int num = 0;
		if ((int) students_vec[i].sessions.size() >= 2)
		{
			for (int j = 0; j < (int) students_vec[i].sessions[1].size(); ++j)
			{
				if (students_vec[i].sessions[1][j].second == 5) ++num;
			}
		}
		a.push_back(make_pair(num, students_vec[i]));
	}
	sort(a.begin(), a.end(), [](auto x, auto y) {  // лямбда-функция для сравнения по кол-ву пятерок во 2 семестре
		return x.first >= y.first;
	}); 
	cout << endl;
	for (int i = 0; i < (int) a.size(); ++i)
	{
		//cout << i + 1 << ". ";
		cout << a[i].second.fio1 << " ";
		cout << a[i].second.fio2 << " ";
		cout << a[i].second.fio3 << " - " << a[i].first << endl;
	}
	cout << endl;
	int choose;
	cout << "0. Выйти" << endl;
	cout << "1. Сохранить в result.txt" << endl;
	
	bool bad = 0;
		
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Ваш выбор: ";
		cin >> choose;
		bad = 1;
	}
	while (!(choose >= 0 && choose <= 1));
	
	if (!choose) return;
	
	ofstream fout("result.txt");
	
	for (int i = 0; i < (int) a.size(); ++i)
	{
		fout << a[i].second.fio1 << " ";
		fout << a[i].second.fio2 << " ";
		fout << a[i].second.fio3 << " - " << a[i].first << endl;
	}
	fout << endl;
	
	fout.close();

}

void save_to_file(vector <Student> & students_vec)
{
	system("clear");
	cout << "Сохранение базы студентов в файл" << endl << endl;
	cout << "Введите название файла: ";
	string filename;
	cin >> filename;
	ofstream fout(filename);
	fout << students_vec.size() << endl;
	for (int i = 0; i < (int) students_vec.size(); ++i)
	{
		fout << students_vec[i].fio1 << endl;
		fout << students_vec[i].fio2 << endl;
		fout << students_vec[i].fio3 << endl;
		fout << students_vec[i].day << " " << students_vec[i].month << " "<< students_vec[i].year << endl;
		fout << students_vec[i].year_of_entrance << endl;
		fout << students_vec[i].faculty << endl;
		fout << students_vec[i].department << endl;
		fout << students_vec[i].group << endl;
		fout << students_vec[i].number_of_gradebook << endl;
		fout << students_vec[i].sessions.size() << endl;
		for (int j = 0; j < (int) students_vec[i].sessions.size(); ++j)
		{
			fout << students_vec[i].sessions[j].size() << endl;
			for (int k = 0; k < (int) students_vec[i].sessions[j].size(); ++k)
			{
				fout << students_vec[i].sessions[j][k].first << " " << students_vec[i].sessions[j][k].second << endl;
			}
			fout << endl;
		}
		fout << endl;
	}
	fout.close();
}
	


void add_a_student_from_file(vector <Student> & students_vec)
{
	system("clear");
	cout << "Добавление новых студентов из файла" << endl << endl;
	cout << "Введите название файла: ";
	string filename;
	cin >> filename;
	ifstream fin(filename);

	int count = 0;
	
	/*do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Сколько профилей студентов в этом файле: ";
		cin >> count;
		bad = 1;
	}
	while (!(count >= 0));
	*/
	fin >> count;
	
	for (int i = 0; i < count; ++i)
	{
		Student new_student = Student();
		fin >> new_student.fio1;
		fin >> new_student.fio2;
		fin >> new_student.fio3;
		fin >> new_student.day;
		fin >> new_student.month;
		fin >> new_student.year;
		fin >> new_student.year_of_entrance;
		fin >> new_student.faculty;
		fin >> new_student.department;
		fin >> new_student.group;
		fin >> new_student.number_of_gradebook;
		int number_of_sessions = 0;
		fin >> number_of_sessions;
		
		for (int i = 0; i < number_of_sessions; ++i)
		{
			new_student.add_empty_session();
			int subjects_count;
			fin >> subjects_count;
			
			for (int j = 0; j < subjects_count; ++j)
			{
				string name;
				fin >> name;
				int grade;
				fin >> grade;
				new_student.add_subject(i, name, grade);
			}
			
		}
	
		students_vec.push_back(new_student);
		
	}
	
	fin.close();

}



void add_a_student_from_keyboard(vector <Student> & students_vec)
{
	Student new_student = Student();
	string s, t;
	system("clear");
	cout << "Добавление нового студента" << endl << endl;
	cout << "Фамилия: ";
	cin >> s;
	new_student.set_fio1(s);
	cout << "Имя: ";
	cin >> s;
	new_student.set_fio2(s);
	cout << "Отчество: ";
	cin >> s;
	new_student.set_fio3(s);
	
	int a, b, c;
	
	bool bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "День рождения в формате \"ДД ММ ГГГГ\": ";
		cin >> a >> b >> c;
		bad = 1;
	}
	while (!(a >= 1 && a <= 31 && b >= 1 && b <= 12 && c >= 1000 && c <= 9999));
	
	new_student.set_birthday(a, b, c);
	
	
	bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Год поступления в институт в формате \"ГГГГ\": ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 1000 && c <= 9999));
	
	new_student.set_year_of_entrance(c);
	
	cout << "Факультет: ";
	cin >> s;
	new_student.set_faculty(s);
	
	cout << "Кафедра: ";
	cin >> s;
	new_student.set_department(s);
	
	bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Группа: ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 0));
	
	new_student.set_group(c);
	
	bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Номер зачётной книжки: ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 0));
	
	new_student.set_number_of_gradebook(c);
	
	bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Количество сессий: ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 0 && c <= 9));
	
	int sessions_count = c;
	
	for (int i = 0; i < sessions_count; ++i)
	{
		new_student.add_empty_session();
		
		bad = 0;
		
		do
		{
			if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
			cout << "Количество предметов в сессии №" << i + 1 << ": ";
			cin >> c;
			bad = 1;
		}
		while (!(c >= 0 && c <= 9));
		
		int subjects_count = c;
		
		for (int j = 0; j < subjects_count; ++j)
		{
			cout << "Название предмета №" << j + 1 << ": ";
			
			getline(cin >> std::ws, s); // считываем с пробелами
			bad = 0;
		
			do
			{
				if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
				cout << "Оценка: ";
				cin >> c;
				bad = 1;
			}
			while (!(c >= 1 && c <= 10));
			
			new_student.add_subject(i, s, c);
		}
		
	}
		
	students_vec.push_back(new_student);


}

void profile(vector <Student> & students_vec, int i)
{
	top:
	system("clear");
	cout << "Профиль студента" << endl << endl;
	cout << "1. Фамилия: " << students_vec[i].fio1 << endl;
	cout << "2. Имя: " << students_vec[i].fio2 << endl;
	cout << "3. Отчество: " << students_vec[i].fio3 << endl;
	cout << "4. День рождения - день: " << students_vec[i].day << endl;
	cout << "5. День рождения - месяц: " << students_vec[i].month << endl;
	cout << "6. День рождения - год: " << students_vec[i].year << endl;
	cout << "7. Год поступления: " << students_vec[i].year_of_entrance << endl;
	cout << "8. Факультет: " << students_vec[i].faculty << endl;
	cout << "9. Кафедра: " << students_vec[i].department << endl;
	cout << "10. Группа: " << students_vec[i].group << endl;
	cout << "11. Номер зачётной книжки: " << students_vec[i].number_of_gradebook << endl;
	cout << endl;
	
	for (int j = 0; j < (int) students_vec[i].sessions.size(); ++j)
	{
		cout << 12 + j << ". Сессия №" << j + 1 << ": " << endl << endl;
		for (int k = 0; k < (int) students_vec[i].sessions[j].size(); ++k)
		{
			cout << students_vec[i].sessions[j][k].first << ": " << students_vec[i].sessions[j][k].second << endl;
		}
		cout << endl;
	}
	cout << 12 + (int) students_vec[i].sessions.size() << ". Добавить сессию" << endl;
	
	cout << endl;
	
	int c;
	bool bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Введите номер параметра, который вы хотите изменить (или \"0\", чтобы выйти): ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 0 && c <= 12 + (int) students_vec[i].sessions.size()));
	if (c == 0) return;
	if (c <= 11)
	{
		// не сессии, обычная инфа
		switch(c)
		{
			case 1:
				cout << "Фамилия: ";
				cin >> students_vec[i].fio1;
				break;
			case 2:
				cout << "Имя: ";
				cin >> students_vec[i].fio2;
				break;
			case 3:
				cout << "Отчество: ";
				cin >> students_vec[i].fio3;
				break;
			case 4:
				cout << "День рождения (только число месяца): ";
				cin >> students_vec[i].day;
				break;
			case 5:
				cout << "Месяц рождения: ";
				cin >> students_vec[i].month;
				break;
			case 6:
				cout << "Год рождения: ";
				cin >> students_vec[i].year;
				break;
			case 7:
				cout << "Год поступления: ";
				cin >> students_vec[i].year_of_entrance;
				break;
			case 8:
				cout << "Факультет: ";
				cin >> students_vec[i].faculty;
				break;
			case 9:
				cout << "Кафедра: ";
				cin >> students_vec[i].department;
				break;
			case 10:
				cout << "Группа: ";
				cin >> students_vec[i].group;
				break;
			case 11:
				cout << "Номер зачётной книжки: ";
				cin >> students_vec[i].number_of_gradebook;
				break;	
		}
	}
	else
	{
		// с сессиями чета
		if (c == 12 + (int) students_vec[i].sessions.size())
		{
			//добавить сессию
			
			students_vec[i].add_empty_session();
			
			bad = 0;
			
			do
			{
				if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
				cout << "Количество предметов в сессии: ";
				cin >> c;
				bad = 1;
			}
			while (!(c >= 0 && c <= 9));
			
			int subjects_count = c;
			string s;
			
			for (int j = 0; j < subjects_count; ++j)
			{
				cout << "Название предмета №" << j + 1 << ": ";
				
				getline(cin >> std::ws, s); // считываем с пробелами
				bad = 0;
			
				do
				{
					if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
					cout << "Оценка: ";
					cin >> c;
					bad = 1;
				}
				while (!(c >= 1 && c <= 10));
				
				students_vec[i].add_subject((int) students_vec[i].sessions.size() - 1 , s, c);
			}
			
		}
		else
		{
			int session_number = c - 12;
			for (int j = 0; j < (int) students_vec[i].sessions[session_number].size(); ++j)
			{
				cout << j + 1 << ". Редактировать предмет \"" << students_vec[i].sessions[session_number][j].first << "\"" << endl;
			
			}
			cout << 1 + students_vec[i].sessions[session_number].size() << ". Удалить сессию" << endl;
				
			do
			{
				if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
				cout << "Номер предмета (или 0, чтобы выйти): ";
				cin >> c;
				bad = 1;
			}
			while (!(c >= 0 && c <= 1 + (int) students_vec[i].sessions[session_number].size()));
			int subj = c;
			if (c == 0) goto top;
			if (c == 1 +  (int) students_vec[i].sessions[session_number].size())
			{
				students_vec[i].delete_session(session_number);
			}
			else
			{
				cout << "Название предмета: ";
				string s;
				getline(cin >> std::ws, s); // считываем с пробелами
				bad = 0;
			
				do
				{
					if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
					cout << "Оценка: ";
					cin >> c;
					bad = 1;
				}
				while (!(c >= 1 && c <= 10));
				students_vec[i].change_subject_name(session_number, subj - 1, s);
				students_vec[i].change_subject_grade(session_number, subj - 1, c);
			}
		}
		
		
		
	}
	goto top;
}


void cout_students_names(vector <Student> & students_vec)
{
	top:
	system("clear");
	cout << "Список студентов" << endl << endl;
	int count = students_vec.size();
	//cout << "SIZE = " << count << endl;
	for (int i = 0; i < count; ++i)
	{
		cout << i + 1 << ". ";
		cout << students_vec[i].fio1 << " ";
		cout << students_vec[i].fio2 << " ";
		cout << students_vec[i].fio3 << endl;
	}
	
	cout << endl;
	cout << "Введите номер студента, чтобы посмотреть информацию о нем " << endl << endl;
	cout << "0. Выйти" << endl << endl;
	
	int c;
	bool bad = 0;
	
	do
	{
		if (bad) cout << "Некорректный ввод! Попробуйте еще раз" << endl;
		cout << "Номер студента: ";
		cin >> c;
		bad = 1;
	}
	while (!(c >= 0 && c <= count + 1));
	
	if (c == 0) return;
	profile(students_vec, c - 1);
	goto top;
	
}



int main()
{
	int choice = 0;
	bool was_ok = 1;
	vector <Student> students_vec(0);
	while (1)
	{
		if (!was_ok) goto choise_time;
		system("clear");
		
		cout << "Добро пожаловать! Список возможных действий: " << endl << endl;
		cout << "1. Добавить данные о студенте, используя клавиатуру" << endl;
		cout << "2. Добавить данные о студентах, считав данные из файла" << endl;
		cout << "3. Вывести список всех студентов" << endl;
		cout << "4. Распечатать в порядке убывания всех студентов, по количеству пятерок " << 
		"во втором cеместре с поиском лиц определенного пола" << endl;
		cout << "5. Сохранить текущий список студентов в файл" << endl;
		cout << endl << "0. Завершить работу с программой" << endl << endl;
		cout << "Введите номер действия: ";
		
		choise_time:
		was_ok = 1;
		
		cin >> choice;
		
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				add_a_student_from_keyboard(students_vec);
				break;
			case 2:
				add_a_student_from_file(students_vec);
				break;
			case 3: 
				cout_students_names(students_vec);
				break;
			case 4:
				do_work(students_vec);
				break;
			case 5:
				save_to_file(students_vec);
				break;
			default:
				cout << "Вы ввели недопустимое значение. Попроуйте еще раз: ";
				was_ok = 0;
		}
		
		
	}
	return 0;
}
