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


void DATA_STREAM(string file) {
	ifstream stream;
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

	vector<string> lineTypes{
		"header",
		"property",
		"command",
	};

	vector<map<string, string>> output;
	if (stream.is_open()) {
		cout << file << " is open \n";

		string line;

		while (getline(stream, line)) {
			map<int, char> processed;

			int index = 0;
			for (string::iterator character = line.begin(); character != line.end(); ++character) {

				switch (line[index]) {
				case '{': processed.insert(pair<int, char>(index, line[index]));
				case '}': processed.insert(pair<int, char>(index, line[index]));
				case ':': processed.insert(pair<int, char>(index, line[index]));
				default: break;
				};

				if (line[index] == ':') { break; }

				++index;
			}

			vector<char> charArray;
			for (map<int, char>::iterator charIndex = processed.begin(); charIndex != processed.end(); ++charIndex) {
				if (charIndex->second == '{') {
					for (int character = charIndex->first + 1; line[character] != '}'; ++character) {
						charArray.emplace_back(line[character]);
					}
				}

				string charArrayOut;
				for (char character : charArray) {
					charArrayOut.push_back(character);
				}

				//header
				map<string, string> charOut;
				charOut.insert(pair<string, string>(lineTypes[0], charArrayOut));
				output.push_back(charOut);
			}
		}


		stream.close();

	}

	for (int vectorMapIndex = 0; vectorMapIndex != output.size() - 1; ++vectorMapIndex) {
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
