#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
class ReadLines {
private:
	std::string fileName;
	std::ifstream fileStream;
	std::vector<std::string> individualLines;
	int size_of_data;
	int number_of_words;
	std::vector<std::vector<std::string>> result;
public:
	ReadLines(std::string a) { fileName = a; openFile(); }
	std::vector<std::string> openFile();
	std::vector<std::vector<std::string>> organizeByWords();

	//test functions
	void  printLines();
};
struct WordC {
	std::string word;
	int count;
	void add(std::string w) { word = w; count=1; }
	void increase() { count++; }
	friend bool operator==(const WordC& a, const WordC& b) {
		bool rc = false;
		if (a.word == b.word) {
			rc = true;
		}
		return rc;
	}
	friend bool operator<(const WordC& a, const WordC& b) {
		return a.word < b.word;
	}
	friend bool operator>(const WordC& a, const WordC& b) {
		return a.word > b.word;
	}
	bool isEmpty() {
		if (word.empty()) {
			return true;
		}
		return false;
	}
};
