#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <Windows.h>
#include <conio.h> 
#include <stdio.h> 
#include <regex>

using namespace std;

string filename = "input.txt";

int myHash(const string&);

HANDLE hStdout;

bool GetColor(short&);

void Search(const string&, map <int, vector<int>>&, const string&);

int main() {

	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO start_attribute;
	GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	map <int, string> hash_to_string;
	map <int, vector<int> > hash_to_entries;
	string tempstr, word = "";
	string alltext = "";
	ifstream input_file(filename);

	if (!input_file.is_open()) std::cout << "Не удалось открыть файл!";

	map <int, string> ::iterator find_iterator;

	int temphash = 0;

	while (input_file >> tempstr)
	{
		if (tempstr.back() == '!' || tempstr.back() == '.' || tempstr.back() == '?' || tempstr.back() == ',' || tempstr.back() == '—' || tempstr.back() == ';' || tempstr.back() == ':' || tempstr.back() == '"')
		{
			word = tempstr.substr(0, tempstr.length() - 1);
		}
		else if (tempstr.front() == '!' || tempstr.front() == '.' || tempstr.front() == '?' || tempstr.back() == ',' || tempstr.back() == '—' || tempstr.back() == ';' || tempstr.back() == ':' || tempstr.back() == '"')
		{
			word = tempstr.substr(1, tempstr.length());
		}
		else {
			word = tempstr;
		}

		temphash = myHash(word);

		find_iterator = hash_to_string.find(temphash);
		if (find_iterator == hash_to_string.end()) {

			hash_to_string[temphash] = word;
			hash_to_entries[temphash].push_back(alltext.length());
		}

		//

		else {

			hash_to_entries[temphash].push_back(alltext.length());
		}
		alltext += (tempstr + " ");

	}
	map <int, string> ::iterator it = hash_to_string.begin();
	cout << "Полученная хэш-таблица: " << endl;
	printf("============================================================================\n");
	for (int i = 0; it != hash_to_string.end(); it++, i++) { 
		cout << i << ") Ключ = " << it->first << ". Значение = " << it->second << endl;
	}
	printf("============================================================================\n");
	cout << endl;
	printf("============================================================================\n");
	for (map<int, vector<int> >::iterator it = hash_to_entries.begin(); it != hash_to_entries.end(); ++it)
	{
		cout << "Слово " << "\"" << hash_to_string[it->first] << "\"" << " с хэш-ключом " << it->first << " начинаются на символах: ";
		for (auto i : hash_to_entries[it->first])
		{
			cout << i << " ";
		}
		cout << endl;
	}

	printf("============================================================================\n");
	cout << endl;

	cout << "Введенный текст: " << endl << alltext << endl << endl;
	cout << "Введите слово для поиска:" << endl;
	string a;
	cin >> a;
	Search(a, hash_to_entries, alltext);


/*	string text = "";
	char c;
	printf("Text: ");
	while ((c = getc(stdin)) != '\n')
	{
		if ((c < 32) || (c > 126))
		{
			printf("Error!\n");
			fflush(stdin);
			getchar();
			return 0;
		}
		text.push_back(c);
	}
	if (text.length() < 1)
	{
		printf("Error!\n");
		fflush(stdin);
		getchar();
		return 0;
	}

	printf("\n");
	string sourceWord = "";
	printf("Word: ");
	while ((c = getc(stdin)) != '\n')
	{
		if ((c < 32) || (c > 126))
		{
			printf("Error!\n");
			fflush(stdin);
			getchar();
			return 0;
		}
		sourceWord.push_back(c);
	}
	if (sourceWord.length() < 1)
	{
		printf("Error!\n");
		fflush(stdin);
		getchar();
		return 0;
	}

	char stops[20] = { '.', ',', '!', '?', ':', ';', '"', '\'', '\n', ' ', '/', '\\', '|', '(', ')', '[', ']','{','}' };
	int amountOfWords = 0;
	bool wordFound = false;
	bool anotherWordFound = false;
	string word = "";

	for (int i = 0; i < sourceWord.length(); i++)
	{
		if (isStopChar(sourceWord[i], stops, 20))
		{
			wordFound = false;
			continue;
		}
		else
		{
			if (!wordFound)
			{
				wordFound = true;
				amountOfWords++;
				if (amountOfWords > 1) {
					printf("Error!\n");
					fflush(stdin);
					getchar();
					return 0;
				}
			}
			word.push_back(sourceWord[i]);
		}
	}

	int amountOfHashComps = 0;
	int amountOfStrComps = 0;

	printf("Searching word: ");
	for (int i = 0; i < word.length(); i++) printf("%c", word[i]);
	printf("\n\n");

	printf("Words:\n");
	string textWord = "";
	for (int i = 0; i < text.length(); i++)
	{
		if (isStopChar(text[i], stops, 20))
		{
		checkWord:
			if (textWord.length() > 0)
			{
				for (int j = 0; j < textWord.length(); j++)
				{
					printf("%c", textWord[j]);
				}
				printf("\n");
				if (hashComp(textWord, word)) amountOfHashComps++;
				if (strComp(textWord, word)) amountOfStrComps++;
			}
			textWord = "";
		}
		else
		{
			textWord.push_back(text[i]);
		}
	}
	if (textWord.length() > 0) goto checkWord;

	printf("\nHash: %d", amountOfHashComps);
	printf("\nStrings: %d\n", amountOfStrComps);
	printf("\nGOTOVO!\n");
exit:
	fflush(stdin);
	getchar();
	return 0;
*/
}

int myHash(const string& str) {
	int result = 0;
	int base = 1;
	for (int i = 0; i < str.length(); i++)
	{
		result += base * str[i];
		base *= 1000;
	}
	return result;
}

void Search(const string& input_word, map <int, vector<int>>& entries, const string& alltext) {
	int hashw = myHash(input_word);
	vector <int> ends;
	map<int, vector<int> >::iterator find_iterator = entries.begin();
	find_iterator = entries.find(hashw);
	if (find_iterator == entries.end()) {
		cout << "Слово: " << input_word << " не встречается в тексте" << endl;
	}
	else
	{
		cout << "Слово: " << input_word << " встречается в тексте (по хэшу) " << find_iterator->second.size() << " раз" << endl;
		if (find_iterator->second.size() > 1)
		{
			int count = 0;
			int end;
			for (auto num : find_iterator->second)
			{
				for (int i = num; i < alltext.size(); i++)
				{
					if (alltext.substr(i, 1) == "!" || alltext.substr(i, 1) == "." || alltext.substr(i, 1) == " ") end = i;

				}
				if (input_word == alltext.substr(num, end))
				{
					count++;
					ends.push_back(end);
				}
				
			}
			short currentcolor;
			GetColor(currentcolor);

			//cout << "Слово: " << input_word << " встречается в тексте (по буквенное сравнение) " << find_iterator->second.size() << " раз" << endl;
			
			cout << endl;

			SetConsoleTextAttribute(hStdout, currentcolor);
		}
	}
}

bool GetColor(short& ret) {

	CONSOLE_SCREEN_BUFFER_INFO info;

	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info))

		return false;

	ret = info.wAttributes;

	return true;
}


/*bool strComp(string& word1, string& word2)
{
	if (word1.length() != word2.length()) return false;

	for (int i = 0; i < word1.length(); i++)
	{
		if (word1[i] != word2[i]) return false;
	}
	return true;
}*/