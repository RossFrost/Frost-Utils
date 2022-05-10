//make sure your compiler set C++20
//setup a .frost file to experiment with it
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



struct lineProcessor {
	map<int, vector<string>> outdata;
};


void returnValues(vector<string> data, int iteration) {
	lineProcessor lineProcessor;
	lineProcessor.outdata.insert(pair(iteration, data));

}


int isHeader(string line, int iteration) {
	int begin = static_cast<int>(line.find('{'));
	int end = static_cast<int>(line.find('}'));
	int dist = static_cast<int>(end - begin);
	string lineCharacterString;

	for (int character = begin + 1; character != end; ++character) {
		if (line[character] == ' ') { continue; }
		lineCharacterString.push_back(line[character]);
	}

	returnValues({"header", lineCharacterString}, iteration);

	cout << "header: " + lineCharacterString + "\n";
	return ++iteration;
}


int isProperty(string line, int iteration) {
	int equalSign = static_cast<int>(line.find('='));
	string name;
	string value;

	if (equalSign != string::npos) {

		for (int character = 0; character != equalSign; ++character) {
			if (line[character] == ' ') { continue; }
			name.push_back(line[character]);
		}

		cout << "name: " + name + "\n";

		for (int character = equalSign + 1; character != line.size(); ++character ) {
			if (line[character] == ' ') { continue; }
			value.push_back(line[character]);
		}

		cout << "value: " + value + "\n";

	}

	returnValues({ "property", name, value}, iteration);
	return ++iteration;
}




void DATA_STREAM(string file) {
	ifstream stream;
	stream.open(file);

	vector<map<string, string>> output;
	if (stream.is_open()) {
		cout << file << " is open \n";

		string line;
		int iteration = 0;
		map<int, vector<string>> lineProcessor;
		bool gate = false;

		while (getline(stream, line)) {
			cout << iteration << "\n";

			if (line.find('{') != string::npos && line.find('}') != string::npos && line.find(':') != string::npos) {
				iteration = isHeader(line, iteration);
				gate = true;
				continue;
			}

			if (gate == true) {
				if (line.find('{') != string::npos && line.find('}') != string::npos && line.find(':') != string::npos) {
					gate = false; 
					iteration = isHeader(line, iteration); 
					continue;
				}

				iteration = isProperty(line, iteration);
				continue;
			}
			++iteration;
		}
	}
	stream.close();
};


auto out(lineProcessor output) {
	
}





vector<string> GET_FILES() {
	const char mainDirectory[] = "."; 
	path mainDirectoryPath = absolute(mainDirectory);
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
	for (int file = 0; file <= files.size() - 1; ++file) {
		cout << files[file] + "\n";
		DATA_STREAM(files[file]);
	}
}
