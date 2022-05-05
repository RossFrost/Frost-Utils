#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>



using std::map; using std::string; using std::vector; using std::cout;
using std::filesystem::recursive_directory_iterator; using std::filesystem::path;
using std::filesystem::absolute; using std::filesystem::u8path; using std::getline;
using std::ifstream; std::basic_ifstream;



void DATA_STREAM(string file) {
	std::ifstream stream;
	stream.open(file);

	vector<string> props {
		"defaults",
		"properties",
		"$"
	};

	vector<string> commands {
		"#override",
		"!",
		"print -> "
	};


	vector<char> charList {
		'{',
		'}',
		':'

	};

	vector<map<string, string>> output;
	if (stream.is_open()) {
		string line;

		while (getline(stream, line)) {
			map<int, char> processed;


			for (int character = 0; line[character]; ++character) {

				switch (line[character]) {
					case '{' : processed.insert(std::pair<char, int>(character, charList[0]));
					case '}' : processed.insert(std::pair<char, int>(character, charList[1]));
					case ':' : processed.insert(std::pair<char, int>(character, charList[2]));
					default  : continue; 
				};

				if (line[character] == charList[2]) {
					break;
				}


			for (std::map<int, char>::iterator index = processed.begin(); index != processed.end(); ++index) {
				string value;

				auto getHeaderValue = [&]() {
					vector <char> value;

					for (int iterate = index -> first + 1; line[iterate] != charList[1]; ++iterate) {
						value.push_back(line[iterate]);
					}
					
					string returnValue(value.begin(), value.end());
					
					return returnValue;
				};


				if (index -> second == charList[0]) {
					map<string, string> header;

					header.insert(std::pair<string, string>("type", "header"));
					header.insert(std::pair<string, string>("value", getHeaderValue()));
					output.push_back(header); 
				}
				
				}
			}
		}
	}
}


vector<string> GET_FILES() {
	const char mainDirectory[] = u8"."; path mainDirectoryPath = absolute(mainDirectory);
	vector<string> files;

	for (auto const& entry : recursive_directory_iterator{ mainDirectoryPath }) {	
		if (entry.path().extension() == ".frost") {
			files.push_back(entry.path().u8string());}};

	return files;
}			


int main() {
	vector<string> files = GET_FILES();
	for (int file = 0; file <= files.size() - 1; ++file ) {
		cout << files[file] + "\n";
		DATA_STREAM(files[file]);};
}
