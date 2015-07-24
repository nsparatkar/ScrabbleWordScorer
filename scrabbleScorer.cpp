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
	string constraint;
	
	bool constraintSatisfied(string word) {
		for(int i = 0; i < constraint.length(); i+=2){
			char constratintCharacter = constraint.at(i);
			int constraintPosition = (int) constraint.at(i+1);
			bool validWord = word.at(constraintPosition) == constraintCharacter;
			if(!validWord)
				return false;
		}
		return true;
	}
	
	bool isWordGeneratable(string word){
		
		int wordPosition = 0;
		int rackPosition = 0;
		int wordCount[26] = {0};
		int rackCount[26] = {0};
		int difference = 0;
		for(int wordPosition = 0; wordPosition < word.length(); wordPosition++) {
			wordCount[word.at(wordPosition) - BASE]++;
		}
		for(int rackPosition = 0; rackPosition < rack.length(); rackPosition++) {
			rackCount[rack.at(rackPosition) - BASE]++;
		}
		for(int i = 0; i < 26; i++) {
			if(wordCount[i] > rackCount[i]) {
				difference += wordCount[i] - rackCount[i];
			}
		}
		return difference <= spaceCount;
	}
	
	int calculateWordScore(string word) {
		int index = 0;
		int score = 0;
		int scrabbleLetterScores[] = {1,3,3,2,1,4,2,4,1,8,10,1,2,1,1,3,8,1,1,1,1,4,10,10,10,10};
		for (index = 0; index < word.length(); index++) {
			score += scrabbleLetterScores[word.at(index) - BASE];
		}
		return score;
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
					for(vector<string>::iterator wordsIterator = tableIterator->second.begin(); wordsIterator != tableIterator->second.end(); wordsIterator++) {
						if(constraintSatisfied(*wordsIterator)) {
							sortedScore[score].push_back(*wordsIterator);
						}
					}
				}
			}
			printScores();
		}
		
		void changeRack(string rack) {
			spaceCount = count(rack.begin(), rack.end(), SPACE);
			rack.erase(remove(rack.begin(), rack.end(), SPACE), rack.end());
			sort(rack.begin(), rack.end());
			this->rack = rack;
		}
	
};

int main(){
	
	ScrabbleSolver scrabble("quizze ");
	scrabble.solve();
	
	return 0;
}
