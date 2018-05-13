#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	cout << "hello world" << endl;

	vector<string> inFileLines;
	vector<unsigned char> hexArray;
	string line;
	ifstream fileHolder("in.txt" ,  ios::in);

	//zczytanie pliku
	if (fileHolder.is_open())
	{
		while (getline(fileHolder, line))
		{
			inFileLines.push_back(line);
		}
		fileHolder.close();
	}else cout << "Unable to open file";

	//wyci¹gniecie zakresu 0-F
	for (int i = 0 ; i < inFileLines.size() ; i++)
	{
		string newLine = "";

		for (int j = 0 ; j < inFileLines[i].length();j++)
		{
			if ((inFileLines[i][j] >= 48 && inFileLines[i][j] <= 57) || (inFileLines[i][j] >= 65 && inFileLines[i][j] <= 70))
				newLine += inFileLines[i][j];
		}
		
		inFileLines[i] = newLine;
	}

	//tworzenie tablicy hex
	char holder = ' ';
	for (int i = 0; i < inFileLines.size(); i++)
	{
		int j = 0;

		if (holder != ' ')
		{
			char tmp[3] = { holder, inFileLines[i][0], '\0' };
			int byteOut = -1;
			sscanf_s(tmp, "%X", &byteOut);
			hexArray.push_back(byteOut);
			j = 1;
			if (inFileLines[i].length() % 2 == 0)
			{
				holder = inFileLines[i][inFileLines[i].length() - 1];
			}
		}
		else
		{
			if (inFileLines[i].length() % 2 == 1)
			{
				holder = inFileLines[i][inFileLines[i].length()-1];
			}
		}

		for ( j ; j < inFileLines[i].length() - 1; j += 2)
		{
			char tmp[3] = { inFileLines[i][j], inFileLines[i][j + 1], '\0' };
			int byteOut = -1;
			sscanf_s(tmp, "%X", &byteOut);
			hexArray.push_back( byteOut );
		}
	}

	//dzielenie na czêœci
	vector <unsigned char> even;
	vector <unsigned char> notEven;
	for (int i = 0 ; i < hexArray.size() ; i++)
	{
		string binaryRepresentation = "";
		int count1 = 0;

		for (int j = 7; j >= 0; --j) 
		{
			binaryRepresentation += ((hexArray[i] & (1 << j)) ? '1' : '0') ;
		}

		for (int j = 0; j < binaryRepresentation.length(); j++)
		{
			if (binaryRepresentation[j] == '1')
				count1++;
		}

		if (count1 % 2 == 0)
		{
			even.push_back(hexArray[i]);
		}
		else
		{
			notEven.push_back(hexArray[i]);
		}
		
	}

	//sortowanie

	sort(even.begin(), even.end());
	sort(notEven.rbegin(), notEven.rend());

	//tworzenie plików wyjœciowych
	
	ofstream evenFileHolder;
	evenFileHolder.open("even.txt", ios::out);

	if (evenFileHolder.is_open())
	{
		for (int i = 0; i < even.size(); i++)
		{
			evenFileHolder << to_string(even[i]) << "\n";
		}
	}

	evenFileHolder.close();

	ofstream notEvenFileHolder;
	notEvenFileHolder.open("notEven.txt", ios::out);

	for (int i = 0; i < even.size(); i++)
	{
		notEvenFileHolder << to_string(notEven[i]) << "\n";
	}
	notEvenFileHolder.close();

	//system("PAUSE");

	return 0;
}