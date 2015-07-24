#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<fstream>

using namespace std;

class ScrabbleSolver{
	
	string rack;
	int spaceCount;
	map <string, vector<string> > anagramTable;
	map<int, vector<string> > sortedScore;
	const char SPACE = ' ';
	const char BASE = 'a';
	const char END = 'z';
	
	
	public:
		ScrabbleSolver(string rack){
			string inputFileName = "C:/Users/test/Documents/words.txt";
			spaceCount = count(rack.begin(), rack.end(), SPACE);
			rack.erase(remove(rack.begin(), rack.end(), SPACE), rack.end());
			sort(rack.begin(), rack.end());
			this->rack = rack;
			
			ifstream readFile;
			readFile.open(inputFileName.c_str());
			string currentWord;
			while(getline(readFile, currentWord)){
				string sortedWord = currentWord;
				sort(sortedWord.begin(), sortedWord.end());
				anagramTable[sortedWord].push_back(currentWord);
			}
		}
		
		void solve() {
			for(map<string, vector<string> >::iterator tableIterator = anagramTable.begin(); tableIterator != anagramTable.end(); tableIterator++) {
				if(isWordGeneratable(tableIterator->first)) {
					int score = calculateWordScore(tableIterator->first);
					for(vector<string>::iterator j = tableIterator->second.begin(); j != tableIterator->second.end(); j++) {
						sortedScore[score].push_back(*j);
					}
				}
			}
			printScores();
		}
		
		void printScores() {
			for( map<int, vector<string> >::reverse_iterator i = sortedScore.rbegin(); i != sortedScore.rend(); i++){
				cout << i->first << " ";
				for(vector<string>::iterator j = i->second.begin(); j != i->second.end(); j++) {
					cout << *j << " ";
				}
				cout << endl;
			}
		}
	
};

int main(){
	
	ScrabbleSolver scrabble("quizze ");
	scrabble.solve();
	
	return 0;
}
