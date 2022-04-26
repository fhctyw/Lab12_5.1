#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct Numbers
{
	int a, b, c;
};

void Generate(string path, size_t cnt)
{
	Numbers* nums = new Numbers[cnt];
	for (size_t i = 0; i < cnt; i++)
		nums[i] = { 1 + rand() % 10, 1 + rand() % 10, 1 + rand() % 10 };
	
	fstream file(path, ios::out | ios::binary);
	if (file.is_open())
	{
		file.write((char*)&cnt, sizeof(size_t));
		for (size_t i = 0; i < cnt; i++)
			file.write((char*)&nums[i], sizeof(Numbers));
	}
	else
		cout << "Generate()" << endl;
	delete[] nums;
	file.close();
}

void Display(string path)
{
	Numbers* nums = nullptr;
	size_t cnt = 0;
	fstream file(path, ios::in | ios::binary);
	if (file.is_open())
	{
		file.read((char*)&cnt, sizeof(size_t));
		nums = new Numbers[cnt];
		for (size_t i = 0; i < cnt; i++)
			file.read((char*)(& nums[i]), sizeof(Numbers));
	}
	else
		cout << "Display()" << endl;

	cout << "-------------" << endl;
	cout << "|id| a| b| c|" << endl;
	cout << "-------------" << endl;
	cout << left;
	for (size_t i = 0; i < cnt; i++)
		cout << setw(3) << i << "|" << setw(2) << nums[i].a << "|" << setw(2) << nums[i].b << "|" << setw(2) << nums[i].c << "|" << endl;
	cout << "-------------" << endl;

	delete[] nums;
	file.close();
}

struct avg
{
	double p1, p2;
};

avg Avg(Numbers* nums, size_t cnt)
{
	double p = 0, p1 = 0;
	int cp = 0, cp1 = 0;

	for (size_t i = 0; i < cnt; i++)
	{
		if (i % 2 == 0) {
			p += nums[i].a + nums[i].b + nums[i].c;
			cp+=3;
		}

		if (i % 2 != 0)
		{
			p1 += nums[i].a + nums[i].b + nums[i].c;
			cp1+=3;
		}
	}

	p /= cp;
	p1 /= cp1;
	return avg{ p, p1 };
}

void create_avg_file(string path, string new_path)
{
	size_t cnt = 0;
	Numbers* nums = nullptr;
	fstream file(path, ios::binary | ios::in);
	if (file.is_open())
	{
		file.read((char*)&cnt, sizeof(size_t));
		nums = new Numbers[cnt];
		for (size_t i = 0; i < cnt; i++)
			file.read((char*)(&nums[i]), sizeof(Numbers));
	}
	else
		cout << "path create_avg_file()" << endl;
	file.close();
	
	avg a = Avg(nums, cnt);

	fstream f(new_path, ios::binary | ios::out);
	if (f.is_open())
	{
		f.write((char*)&a.p1, sizeof(a.p1));
		f.write((char*)&a.p2, sizeof(a.p2));
	}
	else
		cout << "new_path create_avg_file()" << endl;
	
	delete[] nums;
	f.close();
}

void read_avg_file(string path)
{
	fstream file(path, ios::binary | ios::in);
	double p1, p2;
	if (file.is_open())
	{
		file.read((char*)&p1, sizeof(p1));
		file.read((char*)&p2, sizeof(p2));

		cout << "Середнє за парними: " << p1 << endl;
		cout << "Середнє за не парними: " << p2 << endl;
	}
	else
		cout << "read_avg_file()" << endl;

	file.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	string path, new_path;
	cout << "Введіть файл для генерації: "; getline(cin, path);
	size_t cnt;
	cout << "Введіть кількість: "; cin >> cnt;
	Generate(path, cnt);
	Display(path);
	cin.sync();
	cout << "Введіть файл для середніх заначень: ";
	cin.get();
	getline(cin, new_path);
	create_avg_file(path, new_path);
	read_avg_file(new_path);

	return 0;
}