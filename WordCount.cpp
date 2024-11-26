// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int num = 0;
	for (int i = 0; i < 100; i++) {
		int vecSize = table[i].size();
		for (int j = 0; j < vecSize; j++) {
			if (!table[i].at(j).first.empty()) {
				num += ((table[i]).at(j)).second;
			}
		}
	}
	
	return num;
}

int WordCount::getNumUniqueWords() const {
	int num = 0; 
	for (int i = 0; i < 100; i++) {
		num += (table[i]).size();
	}
	// STUB
	return num;
}

int WordCount::getWordCount(std::string word) const {
	std::string validWord = makeValidWord(word);
	int hashIndex = hash(validWord);
	int vecSize = (table[hashIndex]).size();
	for (int i = 0; i < vecSize; i++) {
		if (table[hashIndex].at(i).first == validWord) {
			return table[hashIndex].at(i).second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);

	if (validWord.empty()) {
		return 0;
	}

	int hashIndex = hash(validWord);
	int vecSize = (table[hashIndex]).size();
	
	for (int i = 0; i < vecSize; i++) {
		if (table[hashIndex].at(i).first == validWord) {
			table[hashIndex].at(i).second++;
			return table[hashIndex].at(i).second;		
		}
	}

	//if we get through the entire loop, the word does not exist so add it
	std::pair<string, int> newPair(validWord, 1);
	table[hashIndex].push_back(newPair);
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);
	int hashIndex = hash(validWord);
	int vecSize = (table[hashIndex]).size();
	
	for (int i = 0; i < vecSize; i++) {
		if (table[hashIndex].at(i).first == validWord) {
			if (table[hashIndex].at(i).second == 1) {
				table[hashIndex].erase(table[hashIndex].begin() + i);
				return 0;
			}	
			table[hashIndex].at(i).second--;
			return table[hashIndex].at(i).second;		
		}
	}
	//if we get through the entire loop, the word does not exist
	return -1;
}

bool WordCount::isWordChar(char c) {
	return std::isalpha(c);
}

std::string WordCount::makeValidWord(std::string word) {
	std::string result = "";
	int wordSize = word.size();
	for (int i = 0; i < wordSize; i++) {
		char c = word.at(i);
		if(isWordChar(c)) {
			result += std::tolower(c);
		}
		else if (((c == '\'') || (c == '-')) && (i > 0) && (i < wordSize -1)) {
			if (std::isalpha(word.at(i+1)) && std::isalpha(word.at(i-1))) {
				result += c;
			}
		}
	}
	// STUB
	return result;
}


void WordCount::dumpWordsSortedByWord(std::ostream &out) const {

	std::vector<std::pair<std::string, int>> wordList;
	for (int i = 0; i < 100; i++) {
		for (const auto &entry : table[i]) {
			wordList.push_back(entry);
		}
 	}

	std::sort(wordList.begin(), wordList.end(), 
			[](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
				return a.first > b.first;
			});

	for (const auto &entry : wordList) {
		out << entry.first << "," << entry.second << "\n";
	}
	// STUB;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {

	std::vector<std::pair<std::string, int>> wordList;
	for (int i = 0; i < 100; i++) {
		for (const auto &entry : table[i]) {
			wordList.push_back(entry);
		}
 	}

	std::sort(wordList.begin(), wordList.end(), 
			[](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
				if (a.second == b.second) {
					return a.first< b.first;
				}
				return a.second < b.second;
			});
	
	for (const auto &entry : wordList) {
		out << entry.first << "," << entry.second << "\n";
	}
}

void WordCount::addAllWords(std::string text) {

	std::string currentWord = "";
	for (size_t i = 0; i < text.size(); i++) {
		char c = text[i];
		if (std::isspace(c)) {
			//process word if its complete
			if (!currentWord.empty()) {
				incrWordCount(currentWord);
				currentWord = "";
			}
		}
			else {
				currentWord += c;
			}
		
	}
	if (!currentWord.empty()) {
		incrWordCount(currentWord);
	}
	// STUB
	return;
}
