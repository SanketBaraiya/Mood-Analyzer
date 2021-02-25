#include "fstream"
#include "iostream"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#define TRUE 1
using namespace std;
class moodAnalyzer
{
	float div;
	string name;
	int n, i, l, flag = 0, flagTwo = 0, sum = 0;
	char str[80], arr[10][20], userName[30], fileName[20], userFileData[30];
	char tempConfidence[80], tempAnalytical[80];
	char tempSadness[80], tempJoy[80], tempFear[80], tempAnger[80];
	int varAnger=0, varFear=0, varJoy=0, varSadness=0, varAnalytical=0, varConfident=0;
	fstream Confidence, Analytical, Sadness, Joy, Fear, Anger, userFile, checkStatus;
	public:
		int splitString(char *base, char target[10][20])
		{
			int n=0,i,j=0;
			for(i=0;TRUE;i++)
			{
				if(base[i]!=' ')
					target[n][j++]=base[i];
				else
				{
					target[n][j++]=' ';
					j++;
					target[n][j++]='\0';
					n++;
					j=0;
				}
				if(base[i]=='\0')
					break;
			}
			return n;
		}
		void inputData()
		{
			cout << "Enter your name to get started: ";
			scanf(" %[^\n]%*c", &userName);
			cout << "\nHello " << userName << ", how are you feeling today:\n#";
			cin.get(str,80);	
			n=splitString(str,arr);
			l=strlen(arr[n]);
			for (i=l; i<l+1; i++)
			{
				arr[n][i]=' ';
				arr[n][i+1]='\0';
			}
		}
		void analyzer()
		{
			for(i=0;i<=n;i++)
			{
				Confidence.open("Confident.txt", ios::in);
				while (Confidence.eof() == 0)
				{
					Confidence >> tempConfidence;
					if(strstr(arr[i],tempConfidence) != 0)
					{
						varConfident = 1;
						flag = 1;
					}
				}
				Confidence.close();
				Analytical.open("Analytical.txt", ios::in);
				while (Analytical.eof() == 0)
				{
					Analytical >> tempAnalytical;
					if (strstr(arr[i],tempAnalytical) != 0)
					{
						varAnalytical = 1;
						flag = 1;
					}
				}
				Analytical.close();
				Sadness.open("Sadness.txt", ios::in);
				while (Sadness.eof() == 0)
				{
					Sadness >> tempSadness;
					if (strstr(arr[i],tempSadness) != 0)
					{
						varSadness = 1;
						flag = 1;
					}
				}
				Sadness.close();
				Joy.open("Joy.txt", ios::in);
				while (Joy.eof() == 0)
				{
					Joy >> tempJoy;
					if (strstr(arr[i],tempJoy) != 0)
					{
						varJoy = 1;
						flag = 1;
					}
				}
				Joy.close();
				Fear.open("Fear.txt", ios::in);
				while (Fear.eof() == 0)
				{
					Fear >> tempFear;
					if (strstr(arr[i],tempFear) != 0)
					{
						varFear = 1;
						flag = 1;
					}
				}
				Fear.close();
				Anger.open("Anger.txt", ios::in);
				while (Anger.eof() == 0)
				{	
					Anger >> tempAnger;
					if (strstr(arr[i],tempAnger) != 0)
					{
						varAnger = 1;
						flag = 1;
					}
				}
				Anger.close();
			}
			if (flag == 0)
				cout << "\nI'm not sure I understand.\n";
		}
		void displayDataConsole()
		{
			sum+=varAnger+varFear+varJoy+varSadness+varAnalytical+varConfident;
			div=(100/sum);
			if(varAnger==1)
				varAnger=div;
			if(varFear==1)
				varFear=div;
			if(varJoy==1)
				varJoy=div;
			if(varSadness==1)
				varSadness=div;
			if(varAnalytical==1)
				varAnalytical=div;
			if(varConfident==1)
				varConfident=div;
			cout << "\n\n*Based on my analysis, I've detected this*";
			cout << "\nAnger: \t\t\t"<< varAnger << "%" << endl;
			cout << "Fear: \t\t\t" << varFear << "%" << endl;
			cout << "Joy: \t\t\t" << varJoy << "%" << endl;
			cout << "Sadness: \t\t" << varSadness << "%" << endl;
			cout << "Analytical: \t\t" << varAnalytical << "%" << endl;
			cout << "Confident: \t\t" << varConfident << "%" << endl;
		}
		void enterUserDatabase()
		{
			time_t t = time(0);
		    	tm* now = localtime(&t);
        		string p = to_string(now->tm_mday);
        		string q = to_string((now->tm_mon + 1));
        		string r = to_string((now->tm_year + 1900));
        		name = name + userName + ".txt";
			userFile.open(name, ios::in | ios::out | ios::app);
			userFile << "Mood analysis for date: " << p << "." << q << "." << r << "\n";
			userFile << "You entered: \"" << str << "\""<< endl;
			userFile << "\nAnger: \t\t\t"<< varAnger << "%" << endl;
			userFile << "Fear: \t\t\t" << varFear << "%" << endl;
			userFile << "Joy: \t\t\t" << varJoy << "%" << endl;
			userFile << "Sadness: \t\t" << varSadness << "%" << endl;
			userFile << "Analytical: \t\t" << varAnalytical << "%" << endl;
			userFile << "Confident: \t\t" << varConfident << "%\n\n";
			userFile.close();
		}
		void checkExistingUser()
		{
			system("ls > fileListing.txt");
			checkStatus.open("fileListing.txt", ios::in);
			while(checkStatus.eof() == 0)
			{
				checkStatus >> fileName;
				if (strstr(fileName,userName) != 0)
				{
					userFile.open(name, ios::in | ios:: out | ios::app);
					system("clear");
					cout << "*Mood Analysis*\n";
					string command = "cat " + name;
					int n = command.length();
					char charArray[n+1];
					strcpy(charArray,command.c_str());
					system(charArray);
					flagTwo = 1;
					userFile.close();
				}	
			}
			checkStatus.close();
			if (flagTwo == 0)
				cout << "No files found";
		}
};
int main()
{
	int i;
	char ans = 'N';
	moodAnalyzer O1;
	system("clear");
	O1.inputData();	
	for (i=1000000; i<=3000000; i+=1000000)
	{
		cout << "\n*Running my artificial intelligence*";
		usleep(i);
	}
	usleep(500000);
	O1.analyzer();
	O1.displayDataConsole();
	O1.enterUserDatabase();
	cout << "\nDo you want to check recent trends(Y/N)? ";
	cin >> ans;
	if (ans == 'Y' || ans == 'y')
		O1.checkExistingUser();
	else
		cout << "Thank you for using Mood Analyzer\n";
}