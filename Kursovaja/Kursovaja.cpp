#include "stdafx.h"
#include "iostream"
#include "conio.h"
#include <fstream>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

struct student
{
	char *name = NULL;
	char *course = NULL;
	char *dep = NULL;
	char *group = NULL;
	char *rs = NULL;
	char *faculty = NULL;
	char *spec_c = NULL;
	char *spec_d = NULL;
	struct student * next;
};

struct student_f
{
public:
	char name[41];
	char course[2];
	char dep[7];
	char group[6];
	char rs[2];
	char faculty[51];
	char spec_c[11];
	char spec_d[51];
};

void conv(char *in, char *out)
{
	int counter = 0;
	while (out[counter] != '\0')
	{
		in[counter] = out[counter];
		counter++;
	}
	in[counter] = '\0';
}

void conv2(char **in, char out[])
{
	int counter = 0, n;
	while (out[counter] != '\0')
	{
		counter++;
	}
	if (*in != NULL)
	{
		delete[](*in);
		*in = NULL;
	}
	*in = new char[counter + 1];
	for (n = 0; n < counter; n++)
	{
		(*in)[n] = out[n];
	}
	(*in)[counter] = '\0';
}

bool INPUT_BH(char **str, int max)
{
	char *t = NULL, temp_c;
	t = new char[max + 1];
	int counter = 0, key, temp = max + 1;
	while (counter <= max)
	{
		key = _getch();
		if (key != 8 && key != 13 && counter == max && key != 27)
		{
			continue;
		}
		switch (key)
		{
		case 27:
			delete[] t;
			return false;
			break;
		case 8:
			if (counter == 0)
			{
				continue;
			}
			cout << '\b' << ' ' << '\b';
			t[counter] = ' ';
			counter--;
			break;
		case 13:
			if (counter == 0)
			{
				continue;
			}
			t[counter] = '\0';
			temp = counter + 1;
			counter = max + 1;
			break;
		default:
			temp_c = key;
			if (key < 0 || key > 122)
			{
				continue;
			}
			char symb = (char)temp_c;
			if (isdigit(temp_c) != 0 || (key >= 65 && key <= 90) || key == 58 || key == 92 || (key >= 97 && key <= 122) || temp_c == ' ' || temp_c == '.' || temp_c == ',' || temp_c == '-' || temp_c == '!' || temp_c == '"' || temp_c == '?' || temp_c == '/')
			{
				t[counter] = temp_c;
				printf("%c", temp_c);
				counter++;
				break;
			}
		}
	}
	*str = new char[temp];
	for (counter = 0; counter < temp; counter++)
	{
		(*str)[counter] = ' ';
	}
	for (counter = 0; counter < temp; counter++)
	{
		(*str)[counter] = t[counter];
	}
	(*str)[temp - 1] = '\0';
	delete[] t;
	return true;
}

bool OTP_F(student *rec, bool w, char* file_n)	//record in the file
{
	if (rec == NULL)
	{
		return false;
	}
	if (file_n == "d" || file_n == "D")
	{
		file_n = "D:\\Data Base.dat";
	}
	FILE* file = NULL;
	if (w == true)
	{
		file = fopen(file_n, "wb");
		if (file == NULL)
		{
			cout << "\nOpening error";
			_getch();
			return false;
		}
	}
	else
	{
		file = fopen(file_n, "ab");
		if (file == NULL)
		{
			cout << "\nOpening error";
			_getch();
			return false;
		}
	}
	student_f *temp = NULL, k;
	temp = new student_f;
	while (rec != NULL)
	{
		conv(temp->course, rec->course);
		conv(temp->dep, rec->dep);
		conv(temp->group, rec->group);
		conv(temp->name, rec->name);
		conv(temp->rs, rec->rs);
		conv(temp->faculty, rec->faculty);
		conv(temp->spec_c, rec->spec_c);
		conv(temp->spec_d, rec->spec_d);
		rec = rec->next;
		fwrite(temp, sizeof(k), 1, file);
	}
	fclose(file);
	delete temp;
	return true;
}

bool INP_F(student **rec, char * file_n)	//reading the file
{
	student * t, *first = *rec;
	FILE *file;
	if (*rec != NULL)
	{
		while ((*rec)->next != NULL)
		{
			*rec = (*rec)->next;
		}
	}
	student_f *temp = NULL, k;
	if (file_n == "d" || file_n == "D")
	{
		file_n = "D:\\Data Base.dat";
	}
	temp = new student_f;
	file = fopen(file_n, "rb");
	if (file == NULL)
	{
		cout << "\nOpening error";
		return false;
	}
	int counter = 0, i;
	while (!feof(file))
	{
		fread(temp, sizeof(k), 1, file);
		counter++;
	}
	fclose(file);
	file = fopen(file_n, "rb");
	for (i = 0; i < counter - 1; i++)
	{
		fread(temp, sizeof(k), 1, file);
		t = new student;
		conv2(&t->course, temp->course);
		conv2(&t->dep, temp->dep);
		conv2(&t->name, temp->name);
		conv2(&t->rs, temp->rs);
		conv2(&t->group, temp->group);
		conv2(&t->faculty, temp->faculty);
		conv2(&t->spec_d, temp->spec_d);
		conv2(&t->spec_c, temp->spec_c);
		t->next = NULL;
		if ((*rec) == NULL)
		{
			*rec = new student;
			*rec = t;
			first = *rec;
		}
		else
		{
			(*rec)->next = t;
			*rec = (*rec)->next;
		}

	}
	delete temp;
	*rec = first;
	fclose(file);
	return true;
}

int INPUT(student **list)
{
	int n = 0, key = 0;
	student * rec, *first = *list;
	if (*list != NULL)
	{
		n++;
		while ((*list)->next != NULL)
		{
			n++;
			*list = (*list)->next;
		}
	}
	bool f, flag = true;
	while (flag == true)
	{
		rec = new student;
		cout << "\nRecord " << n + 1 << "\nInput name of student : ";
		f = INPUT_BH(&rec->name, 40);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput name of faculty : ";
		f = INPUT_BH(&rec->faculty, 6);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput name of department : ";
		f = INPUT_BH(&rec->dep, 6);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput code of speciality : ";
		f = INPUT_BH(&rec->spec_c, 10);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput desription of speciality : ";
		f = INPUT_BH(&rec->spec_d, 50);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput course of student : ";
		f = INPUT_BH(&rec->course, 1);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput group of student : ";
		f = INPUT_BH(&rec->group, 5);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		cout << "\nInput session result : ";
		f = INPUT_BH(&rec->rs, 1);
		if (f == false)
		{
			*list = first;
			return 0;
		}
		rec->next = NULL;
		if (*list == NULL)
		{
			*list = rec;
			first = *list;
		}
		else
		{
			(*list)->next = rec;
			*list = (*list)->next;
		}
		n++;
		cout << "\nPress Enter to continue,Esc to finish input";
		do
		{
			key = _getch();
		} while (key != 13 && key != 27);
		if (key == 27)
		{
			flag = false;
		}
	}
	*list = first;
	return n;
}

void DEL_LIST(student **list, int i, int j)
{
	student *temp = *list, *prev = *list, *first = *list;
	int counter = 0;
	bool flag = true;
	if (*list == NULL)
	{
		cout << "\nThe list is empty";
		_getch();
		return;
	}
	else
	{
		while (*list != NULL)
		{
			counter++;
			*list = (*list)->next;
		}
	}
	*list = temp;
	if (i == 0 && j == 0)
	{
		j = counter;
		i = 1;
	}
	if (i == 1)
	{
		flag = false;
	}
	counter = 1;
	while (i != counter)
	{
		prev = *list;
		*list = (*list)->next;
		counter++;
	}
	while (*list != NULL && i <= j)
	{
		temp = *list;
		delete[]temp->course;
		temp->course = NULL;
		delete[]temp->dep;
		temp->dep = NULL;
		delete[]temp->group;
		temp->group = NULL;
		delete[]temp->name;
		temp->name = NULL;
		delete[]temp->rs;
		temp->rs = NULL;
		delete[]temp->faculty;
		temp->faculty = NULL;
		delete[]temp->spec_c;
		temp->spec_c = NULL;
		delete[]temp->spec_d;
		temp->spec_d = NULL;
		*list = (*list)->next;
		delete temp;
		i++;
	}
	if (flag == true)
	{
		prev->next = *list;
		*list = first;
	}
}

bool OTP_LIST(student *list)
{
	if (list == NULL)
	{
		cout << "\nThe list is empty";
		_getch();
		return false;
	}
	student * temp = list;
	int counter = 0;
	while (list != NULL)
	{
		counter++;
		list = list->next;
	}
	list = temp;
	cout << "\nBase has " << counter << " records";
	counter = 1;
	while (list != NULL)
	{
		cout << "\nRecord " << counter;
		cout << "\nName : " << "\t\t\t" << list->name;
		cout << "\nFaculty : " << "\t\t" << list->faculty;
		cout << "\nDepartment : " << "\t\t" << list->dep;
		cout << "\nSpeciality code : \t" << list->spec_c;
		cout << "\nSpeciality descripton : " << list->spec_d;
		cout << "\nCourse : " << "\t\t" << list->course;
		cout << "\nGroup : " << "\t\t" << list->group;
		cout << "\nSession result : " << '\t' << list->rs;
		list = list->next;
		counter++;
	}
	return true;
}

bool EDIT_EL(char **str, int max)
{
	char *t, temp_c;
	t = new char[max + 1];
	int counter = 0, counter1 = 0, key, temp = max + 1;
	while ((*str)[counter] != '\0')
	{
		t[counter] = (*str)[counter];
		printf("%c", t[counter]);
		counter++;
	}
	t[counter] = '\0';
	if (counter > max)
	{
		counter = max;
	}
	delete *str;
	*str = NULL;
	while (counter <= max)
	{
		key = _getch();
		if (key != 8 && key != 13 && counter == max && key != 27)
		{
			continue;
		}
		switch (key)
		{
		case 27:
			*str = new char[counter + 1];
			while (t[counter1] != '\0' && counter1 != counter)
			{
				(*str)[counter1] = t[counter1];
				counter1++;
			}
			(*str)[counter] = '\0';
			delete[] t;
			return false;
			break;
		case 8:
			if (counter == 0)
			{
				continue;
			}
			cout << '\b' << ' ' << '\b';
			t[counter] = ' ';
			counter--;
			break;
		case 13:
			if (counter == 0)
			{
				continue;
			}
			t[counter] = '\0';
			temp = counter + 1;
			counter = max + 1;
			break;
		default:
			temp_c = key;
			char symb = (char)temp_c;
			if (isdigit(temp_c) != 0 || (key >= 65 && key <= 90) || key == 58 || key == 92 || (key >= 97 && key <= 122) || temp_c == ' ' || temp_c == '.' || temp_c == ',' || temp_c == '-' || temp_c == '!' || temp_c == '"' || temp_c == '?')
			{
				t[counter] = temp_c;
				printf("%c", temp_c);
				counter++;
				break;
			}
		}
	}
	*str = new char[temp];
	for (counter = 0; counter < temp; counter++)
	{
		(*str)[counter] = ' ';
	}
	for (counter = 0; counter < temp; counter++)
	{
		(*str)[counter] = t[counter];
	}
	(*str)[temp - 1] = '\0';
	delete[] t;
	return true;
}

bool EDIT(student **list, int i, int j, char * e)
{
	if (*list == NULL)
	{
		cout << "\nThe list is empty";
		_getch();
		return false;
	}
	student * temp = *list;
	int counter = 0;
	if (i == 0 && j == 0)
	{
		while (*list != NULL)
		{
			counter++;
			*list = (*list)->next;
		}
		i = 1;
		j = counter;
	}
	char *temp_c = new char[2];
	temp_c[1] = '\0';
	bool f, flag = false, f2 = true;
	int t;
	counter = 1;
	*list = temp;
	while (*list != NULL && counter != i)
	{
		*list = (*list)->next;
		counter++;
	}
	while (*list != NULL && i <= j)
	{
		cout << "\nRecord " << i;
		cout << "\n1)Name : " << "\t\t  " << (*list)->name;
		cout << "\n2)Faculty : " << "\t\t  " << (*list)->faculty;
		cout << "\n3)Department : " << "\t\t  " << (*list)->dep;
		cout << "\n4)Speciality code : \t  " << (*list)->spec_c;
		cout << "\n5)Speciality descripton : " << (*list)->spec_d;
		cout << "\n6)Course : " << "\t\t  " << (*list)->course;
		cout << "\n7)Group : " << "\t\t  " << (*list)->group;
		cout << "\n8)Session result : " << "\t  " << (*list)->rs;
		counter = 0;
		while (e[counter] != '\0')
		{
			temp_c[0] = e[counter];
			counter++;
			t = atof(temp_c);
			switch (t)
			{
			case 1:
				cout << "\nName : " << "\t\t\t";
				f = EDIT_EL(&((*list)->name), 40);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 2:
				cout << "\nFaculty : " << "\t\t";
				f = EDIT_EL(&((*list)->faculty), 50);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 3:
				cout << "\nDepartment : " << "\t\t";
				f = EDIT_EL(&((*list)->dep), 6);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 4:
				cout << "\nSpeciality descripton : ";
				f = EDIT_EL(&((*list)->spec_d), 50);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 5:
				cout << "\nSpeciality code : \t";
				f = EDIT_EL(&((*list)->spec_c), 10);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 6:
				cout << "\nCourse : " << "\t\t";
				f = EDIT_EL(&((*list)->course), 1);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 7:
				cout << "\nGroup : " << "\t\t";
				f = EDIT_EL(&((*list)->group), 5);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			case 8:
				cout << "\nSession result : " << '\t';
				f = EDIT_EL(&((*list)->rs), 1);
				if (f == false)
				{
					*list = temp;
					return false;
				}
				break;
			default:
				continue;
				break;
			}
		}
		f2 = false;
		*list = (*list)->next;
		i++;
	}
	*list = temp;
	delete[]temp_c;
}

bool COMP_EL(student_f *el1, student_f *el2, char *sr_w)
{
	int counter = 0, t, c;
	char k[2];
	bool flag = false;
	k[1] = '\0';
	while (sr_w[counter] != '\0' && flag == false)
	{
		k[0] = sr_w[counter];
		t = atof(k);
		switch (t)
		{
		case 1:
			c = _stricmp(el1->name, el2->name);
			break;
		case 2:
			c = _stricmp(el1->faculty, el2->faculty);
			break;
		case 3:
			c = _stricmp(el1->dep, el2->dep);
			break;
		case 4:
			c = _stricmp(el1->spec_c, el2->spec_c);
			break;
		case 5:
			c = _stricmp(el1->spec_d, el2->spec_d);
			break;
		case 6:
			c = _stricmp(el1->course, el2->course);
			break;
		case 7:
			c = _stricmp(el1->group, el2->course);
			break;
		case 8:
			c = _stricmp(el1->rs, el2->rs);
			break;
		}
		if (c != 0)
		{
			switch (sr_w[counter + 1])
			{
			case 'u':
			case 'U':
				if (c > 0)
				{
					return false;
				}
				break;
			case 'd':
			case 'D':
				if (c < 0)
				{
					return false;
				}
			}
		}
		counter = counter + 2;
	}
	return true;
}

bool FILTER(student ** list)
{
	if (*list == NULL)
	{
		return false;
	}
	char *** points, *numbers, n[2];
	cout << "\n1)Name";
	cout << "\n2)Faculty";
	cout << "\n3)Department";
	cout << "\n4)Speciality code";
	cout << "\n5)Speciality descripton";
	cout << "\n6)Course";
	cout << "\n7)Group";
	cout << "\n8)Session result";
	cout << "\nInput numbers of fields to put filter on ";
	bool f;
	f = INPUT_BH(&numbers, 8);
	if (f == false)
	{
		return false;
	}
	int counter = 0, t, q_p, i;
	q_p = strlen(numbers);
	n[1] = '\0';
	points = new char**[q_p];
	while (numbers[counter] != '\0')
	{
		char ** temp = new char*[10];
		n[0] = numbers[counter];
		t = atoi(n);
		switch (t)
		{
		case 1:
			cout << "\nInput filter for Name";
			break;
		case 2:
			cout << "\nInput filter for Faculty";
			break;
		case 3:
			cout << "\nInput filter for Department";
			break;
		case 4:
			cout << "\nInput filter for Speciality code";
			break;
		case 5:
			cout << "\nInput filter for Speciality descripton";
			break;
		case 6:
			cout << "\nInput filter for Course";
			break;
		case 7:
			cout << "\nInput filter for Group";
			break;
		case 8:
			cout << "\nInput filter for Session result";
			break;
		}
		f = true;
		i = 0;
		int p;
		while (f == true && i < 10)
		{
			cout << '\n';
			f = INPUT_BH(&(temp[i]), 51);
			i++;
		}
		points[t] = new char*[i];
		for (p = 0; p < i - 1; p++)
		{
			points[t][p] = temp[p];
		}
		points[t][p] = NULL;
		delete[]temp;
		counter++;
	}
	counter = 0;
	char * file = "D:\\filter.dat";
	student * first = *list;
	OTP_F(*list, true, file);
	int x, j = 1;
	while (*list != NULL)
	{
		counter = 0;
		while (numbers[counter] != '\0')
		{
			n[0] = numbers[counter];
			t = atoi(n);
			i = 0;
			f = true;
			while (points[t][i] != NULL)
			{
				switch (t)
				{
				case 1:
					x = _stricmp((*list)->name, points[t][i]);
					break;
				case 2:
					x = _stricmp((*list)->faculty, points[t][i]);
					break;
				case 3:
					x = _stricmp((*list)->dep, points[t][i]);
					break;
				case 4:
					x = _stricmp((*list)->spec_c, points[t][i]);
					break;
				case 5:
					x = _stricmp((*list)->spec_d, points[t][i]);
					break;
				case 6:
					x = _stricmp((*list)->course, points[t][i]);
					break;
				case 7:
					x = _stricmp((*list)->group, points[t][i]);
					break;
				case 8:
					x = _stricmp((*list)->rs, points[t][i]);
					break;
				}
				if (x == 0)
				{
					*list = (*list)->next;
					DEL_LIST(&first, j, j);
					j--;
					f = false;
					break;
				}
				i++;
			}
			if (f == false)
			{
				break;
			}
			counter++;
		}
		if (f == true)
		{
			*list = (*list)->next;
		}
		j++;
	}
	OTP_LIST(first);
	DEL_LIST(&first, 0, 0);
	INP_F(list, file);
	return true;
}

bool SORT(student **list, char *sort_w)
{
	int i = 0, j;
	if (*list == NULL)
	{
		std::cout << "\nThe list is empty";
		_getch();
		return false;
	}
	int counter = 1;
	student * temp = *list;
	while ((*list)->next != NULL)
	{
		counter++;
		*list = (*list)->next;
	}
	j = counter - 1;
	student_f  *sr, t;
	sr = new student_f[counter];
	*list = temp;
	counter = 0;
	while (*list != NULL)
	{
		conv(sr[counter].course, (*list)->course);
		conv(sr[counter].dep, (*list)->dep);
		conv(sr[counter].group, (*list)->group);
		conv(sr[counter].name, (*list)->name);
		conv(sr[counter].rs, (*list)->rs);
		conv(sr[counter].faculty, (*list)->faculty);
		conv(sr[counter].spec_c, (*list)->spec_c);
		conv(sr[counter].spec_d, (*list)->spec_d);
		*list = (*list)->next;
		counter++;
	}
	*list = temp;
	bool flag, f;
	int c_i = i;
	for (counter = i; counter <= j; counter++)
	{
		f = true;
		for (c_i = counter; c_i < j; c_i++)
		{
			flag = COMP_EL(&sr[counter], &sr[c_i + 1], sort_w);
			if (flag == false)
			{
				t = sr[counter];
				sr[counter] = sr[c_i + 1];
				sr[c_i + 1] = t;
				f = false;
			}
		}
		if (f == true)
		{
			break;
		}
	}
	counter = 0;
	while (*list != NULL)
	{
		conv2(&(*list)->course, sr[counter].course);
		conv2(&(*list)->dep, sr[counter].dep);
		conv2(&(*list)->name, sr[counter].name);
		conv2(&(*list)->group, sr[counter].group);
		conv2(&(*list)->faculty, sr[counter].faculty);
		conv2(&(*list)->spec_d, sr[counter].spec_d);
		conv2(&(*list)->spec_c, sr[counter].spec_c);
		conv2(&(*list)->rs, sr[counter].rs);
		*list = (*list)->next;
		counter++;
	}
	*list = temp;
	delete[]sr;
	return true;
}

int _tmain(void)
{
	student * record = NULL;
	const int max = 100;
	char *rw;
	string command;
	int comnum = 0;
	string com[16];
	smatch result;
	com[0] = "inphlist$";
	com[1] = "inpflist .*?$";
	com[2] = "outlist$";
	com[3] = "rewrite .*?$";
	com[4] = "append .*?$";
	com[5] = "del [0-9]*$";
	com[6] = "delf [0-9]+ [0-9]+$";
	com[7] = "dellist$";
	com[8] = "edit [0-9]+ [1-8]+$";
	com[9] = "editf [0-9]+ [0-9]+ [1-8]+$";
	com[10] = "editlist [1-8]+$";
	com[11] = "sortlist ([1-8]((u)|(d)))+$";
	com[12] = "filter$";
	com[13] = "clrscr$";
	com[14] = "help$";
	com[15] = "quit$";
	cout << "Welcome to console University Data Base!" << endl << "Start with command \\help." << endl;
	regex reg;
	bool f, flag;
	bool finish = true;
	while (finish == true)
	{
		rw = "\0";
		cout << "\n\\";
		INPUT_BH(&rw, max);
		string row = rw;
		string::const_iterator start = row.begin();
		string::const_iterator end = row.end();
		flag = false;
		for (int i = 0; i < 16; i++)
		{
			reg = com[i];
			f = regex_search(start, end, result, reg);
			if (f == true)
			{
				flag = true;
				command = result[0];
				comnum = i;
				break;
			}
		}
		if (flag == false)
		{
			continue;
		}
		switch (comnum)
		{
		case 0:
		{
				  string t = command;
				  INPUT(&record);
				  break;
		};
		case 1:
		{
				  string t = command.substr(9, command.length());
				  char * m = new char[1 + t.length()];
				  strcpy(m, t.c_str());
				  INP_F(&record, m);
				  delete[]m;
				  break;
		};
		case 2:
		{
				  string t = command;
				  OTP_LIST(record);
				  break;
		};
		case 3:
		{
				  string t = command.substr(8, command.length());
				  char * m = new char[1 + t.length()];
				  strcpy(m, t.c_str());
				  OTP_F(record, true, m);
				  delete[]m;
				  break;
		};
		case 4:
		{
				  string t = command.substr(7, command.length());
				  char * m = new char[1 + t.length()];
				  strcpy(m, t.c_str());
				  OTP_F(record, false, m);
				  delete[]m;
				  break;
		};
		case 5:
		{
				  string t = command.substr(4, command.length());
				  int temp = stoi(t);
				  DEL_LIST(&record, temp, temp);
				  break;
		};
		case 6:
		{
				  string t = command.substr(5, command.length());
				  int j = 0;
				  while (t[j] != ' ')
					  j++;
				  string t1 = t.substr(0, j);
				  string t2 = t.substr(j + 1, t.length());
				  int temp1 = stoi(t1);
				  int temp2 = stoi(t2);
				  DEL_LIST(&record, temp1, temp2);
				  break;
		};
		case 7:
		{
				  string t = command;
				  DEL_LIST(&record, 0, 0);
				  break;
		};
		case 8:
		{
				  string t = command.substr(5, command.length());
				  int j = 0;
				  while (t[j] != ' ')
					  j++;
				  string t1 = t.substr(0, j);
				  string t2 = t.substr(j + 1, t.length());
				  int temp1 = stoi(t1);
				  char * m = new char[1 + t2.length()];
				  strcpy(m, t2.c_str());
				  EDIT(&record, temp1, temp1, m);
				  delete[]m;
				  break;
		};
		case 9:
		{
				  string t = command.substr(6, command.length());
				  int j = 0, k = 0;
				  while (t[j] != ' ')
					  j++;
				  k = j + 1;
				  while (t[k] != ' ')
					  k++;
				  string t1 = t.substr(0, j);
				  string t2 = t.substr(j + 1, k);
				  string t3 = t.substr(k + 1, t.length());
				  int temp1 = stoi(t1);
				  int temp2 = stoi(t2);
				  char * m = new char[1 + t3.length()];
				  strcpy(m, t3.c_str());
				  EDIT(&record, temp1, temp2, m);
				  delete[]m;
				  break;
		};
		case 10:
		{
				   string t = command.substr(9, command.length());
				   char * m = new char[1 + t.length()];
				   strcpy(m, t.c_str());
				   EDIT(&record, 0, 0, m);
				   delete[]m;
				   break;
		};
		case 11:
		{
				   string t = command.substr(9, command.length());
				   char * m = new char[1 + t.length()];
				   strcpy(m, t.c_str());
				   SORT(&record, m);
				   delete[]m;
				   break;
		};
		case 12:
		{
				   string t = command;
				   FILTER(&record);
				   break;
		};
		case 13:
		{
				   string t = command;
				   system("cls");
				   break;
		};
		case 14:
		{
				   string t = command;
				   cout << endl << "Command list:" << endl << "\\inphlist" << endl << "\\inpflist {pass}" << endl << "\\outlist" << endl << "\\rewrite {pass}" << endl << "\\append {pass}" << endl << "\\del {param}" << endl << "\\delf {param1} {param2}" << endl<< "\\dellist" << endl << "\\edit {param1} {param2}[1-8]" << endl << "\\editf {param1} {param2} {param3}[1-8]" << endl <<  "\\editlist {param}[1-8]" << endl << "\\sortlist ({param}[1-8]{u/d})+" << endl << "\\filter" << endl << "\\clrscr" << endl << "\\help" << endl << "\\quit" << endl;
				   break;
		};
		case 15:
		{
				   string t = command;
				   DEL_LIST(&record, 0, 0);
				   finish = false;
				   break;
		};
		default:
			continue;
		}
	}
}