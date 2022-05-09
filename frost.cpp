#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>


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
using std::distance;



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
		int iteration = 0;

		map<int, vector<string>> lineProcessor;
	
		while (getline(stream, line)) {
			vector<string> lineData;
			string lineCharacterString;
			


			if (line.find('{') != string::npos && line.find('}') != string::npos && line.find(':') != string::npos)  {
				int begin = line.find('{');
				int end = line.find('}');
				int dist = end - begin;

				for (int character = begin + 1; character != end; ++character) {
					lineCharacterString.push_back(line[character]);
				}

				cout << lineCharacterString << "\n";
				lineData.push_back("header");
				lineData.push_back(line);
				lineProcessor.insert(pair<int, vector<string>>(iteration, lineData));
			}
				
			++iteration;
		}
	}

	stream.close();
};



vector<string> GET_FILES() {
	const char mainDirectory[] = "."; path mainDirectoryPath = absolute(mainDirectory);
	vector<string> files;

	for (auto const& entry : recursive_directory_iterator{ mainDirectoryPath }) {	
		if (entry.path().extension() == ".frost") {
			files.push_back(entry.path().string());
		}
	};
	return files;
}			


int main() {
	vector<string> files = GET_FILES();
	for (int file = 0; file <= files.size() - 1; ++file ) {
		cout << files[file] + "\n";
		DATA_STREAM(files[file]);
	}
}