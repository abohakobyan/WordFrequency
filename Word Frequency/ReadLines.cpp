#include "ReadLines.h"
#include "sortedlist.h"
#include <cctype>
#include <algorithm>
using namespace std;
int BinSearch(std::vector<WordC> list,int low, int high, WordC target);
/*Opens File using fileNameVariable and pulls text line by line into a string vector and sets a line number count*/
std::vector<std::string> ReadLines::openFile() {
	fileStream.open(fileName);
	std::string line;
	if (!fileStream) //Check if file is open return error
	{
		std::cout << "Error opening output file (ReadLines Error Contact Admin):" << std::endl;
		system("pause");
		return individualLines;
	}
	 size_of_data = std::count(std::istreambuf_iterator<char>(fileStream), // Count # of spaces
		std::istreambuf_iterator<char>(), '\n') +1;
	individualLines.reserve(size_of_data);
	fileStream.clear(); //reset stream
	fileStream.seekg(0, std::ios::beg);
	while (std::getline(fileStream, line)) //Fill in the vector
	{
		individualLines.push_back(line);
	}
	fileStream.close();
	return individualLines;
}

std::vector<std::vector<std::string>> ReadLines::organizeByWords()
{
	vector<WordC>  data;
	vector<std::string> words;
	for (int i = 0; i < size_of_data; i++) { //seperate the words
		individualLines[i].erase(std::remove_if(individualLines[i].begin(), individualLines[i].end(), ispunct), individualLines[i].end()); //Removes punctuation
		istringstream iss(individualLines[i]);
		copy(istream_iterator<string>(iss),
			istream_iterator<string>(),
			back_inserter(words));
		
		
		
		for (int j = 0; j < words.size(); j++) {
			WordC a;
			std::string uw = words[j];
			std::transform(uw.begin(), uw.end(), uw.begin(), ::toupper);
			a.add(uw);
			//int location = BinSearch(data, data.size(), a);
			int low = 0, mid, high = data.size() - 1;
			int location = BinSearch(data, low, high, a);
			if(location == -1) {
				data.push_back(a);
				std::sort(data.begin(), data.end());
			}else {
				data[location].increase();
			}
			words.clear();
		}
	}
	return std::vector<std::vector<std::string>>();
}
int BinSearch(vector<WordC> list,int low, int high, WordC target) {
	/*if (list.size() < 10) {
		for (int i = 0; i < list.size(); i++) {
			if (list[i] == target) {
				return i;
			}
			return -1;
		}
	}
	*/	int index;

		if (low > high)
			index = -1;
		else
		{
			int mid = (low + high) / 2;
			if (target == list[mid])
				index = mid;
			else
				if (target < list[mid])
					index = BinSearch(list, low, mid - 1, target);
				else
					index = BinSearch(list, mid + 1, high, target);
		} 
		return index;
	}

void ReadLines::printLines() {
	for (int i = 0; i < individualLines.size(); i++) {
			std::cout << individualLines[i] << '\n';
	}
}