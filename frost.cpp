#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <regex>


using std::map;
using std::string; 
using std::vector; 
using std::cout;
using std::filesystem::recursive_directory_iterator;
using std::filesystem::path;
using std::filesystem::absolute; 
using std::filesystem::u8path; 
using std::getline;
using std::ifstream; 
using std::basic_ifstream;
using std::ostringstream;
using std::pair;
using std::find;
using std::regex_match;


void DATA_STREAM(string file) {
	ifstream stream;
	stream.open(file);

	vector<string> props {
		"defaults",
		"properties",
		"$",
	};

	vector<string> commands {
		"#override",
		"!",
		"print -> ",
	};

	vector<string> lineTypes{
		"header",
		"property",
		"command",
		"custom_header",

	};

	vector<map<string, string>> output;
	if (stream.is_open()) {
		cout << file << " is open \n";

		string line;

		while (getline(stream, line)) {
			map<int, char> processed;

			int index = 0;
			cout << line;
			for (string::iterator character = line.begin(); character != line.end(); ++character) {
				cout << line[index];
				processed.insert(pair<int, char>(index, line[index]));
				++index;
			};

			

			int lineTypeIndex = 0;
			string charArrayOut;
			map<string, string> charOut;



			for (map<int, char>::iterator charIndex = processed.begin(); charIndex != processed.end(); ++charIndex) {

				switch (charIndex->second) {

				case '{':
					if (line[charIndex->first + 1] == '$') {
						lineTypeIndex = 3;
					}

					for (int character = charIndex->first + 1; line[character] != '}'; ++character) {
						charArrayOut.push_back(line[character]);
					}

					charOut.insert(pair<string, string>(lineTypes[lineTypeIndex], charArrayOut));
					output.push_back(charOut);
					cout << charArrayOut + "\n";

					lineTypeIndex = 0;
					break;
				
				case 'a':
					lineTypeIndex = 1;
					charOut.insert(pair<string, string>(lineTypes[lineTypeIndex], charArrayOut));
					output.push_back(charOut);
					cout << charArrayOut + "\n";

				}
			}
		}


		stream.close();

	}

	for (int vectorMapIndex = 0; vectorMapIndex != output.size(); ++vectorMapIndex) {
		for (map<string, string>::iterator mapIndex = output[vectorMapIndex].begin(); mapIndex != output[vectorMapIndex].end(); ++mapIndex) {
			cout << mapIndex->first;
		}
	}


}


vector<string> GET_FILES() {
	const char mainDirectory[] = "."; path mainDirectoryPath = absolute(mainDirectory);
	vector<string> files;

	for (auto const& entry : recursive_directory_iterator{ mainDirectoryPath }) {	
		if (entry.path().extension() == ".frost") {
			files.push_back(entry.path().string());}};

	return files;
}			


int main() {
	vector<string> files = GET_FILES();
	for (int file = 0; file <= files.size() - 1; ++file ) {
		cout << files[file] + "\n";
		DATA_STREAM(files[file]);
	}
}