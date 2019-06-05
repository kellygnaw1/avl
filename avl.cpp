#include "Tree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
int main(int argc, char *argv[]){
	if(argc != 2){
		cout << "not enough arguments" << endl;
		return 0;
	}
	Tree tree;
	string arg1(argv[1]);
	string line;
	string command;
	ifstream testFile(arg1);

	if(testFile.is_open()){
		while(getline(testFile, line)){
			if(line == "" || line[0] == '#'){
				continue;
			}

			istringstream iss(line);
			iss >> command;
			if(command == "insert"){
				int arg;
				int count = 0; 
				tree.reset();

				while(iss >> arg){
					tree.insert(arg);
					count += 1;
				}
				cout << "Added " << tree.getInsert() << " of " << count << " nodes." << endl;
				cout << "Visited " << tree.getVisit() << " (" << (1.0 * tree.getVisit()) / count << ") nodes and performed " << tree.getRotation() << " (" << (1.0*tree.getRotation())/ count << ") rotations." << endl;
			}else if(command == "print"){
				string arg;
				iss >> arg;
				if(arg == "tree"){
					tree.print();

				}else if(arg == "left-left"){
					tree.reset();
					tree.printRotation();
					vector<pair<int, int> > temp = tree.get_llPair();
					if(temp.size() == 0){
						cout << "No inserts would cause a left-left rotation." << endl;
					}else{
						cout << "The following inserts would cause a left-left rotation:" << endl;
						for(size_t i = 0; i < temp.size()-1; i++){
							if(temp[i].first != temp[i].second)
								cout << temp[i].first << " to " << temp[i].second << ", ";
							else 
								cout << temp[i].first << ", ";
						}

						if(temp[temp.size()-1].first != temp[temp.size()-1].second)
							cout << temp[temp.size()-1].first << " to " << temp[temp.size()-1].second << endl;
						else
							cout << temp[temp.size()-1].first << endl;
					}
					

				}else if(arg == "left-right"){
					tree.reset();
					tree.printRotation();
					tree.get_lrPair();
					vector<pair<int, int> > temp = tree.get_lrPair();
					if(temp.size() == 0){
						cout << "No inserts would cause a left-right rotation." << endl;
					}else{
						cout << "The following inserts would cause a left-right rotation:" << endl;
						for(size_t i = 0; i < temp.size()-1; i++){
							if(temp[i].first != temp[i].second)
								cout << temp[i].first << " to " << temp[i].second << ", ";
							else 
								cout << temp[i].first << ", ";
						}

						if(temp[temp.size()-1].first != temp[temp.size()-1].second)
							cout << temp[temp.size()-1].first << " to " << temp[temp.size()-1].second << endl;
						else
							cout << temp[temp.size()-1].first << endl;
					}

				}else if(arg == "right-left"){
					tree.reset();
					tree.printRotation();
					vector<pair<int, int> > temp = tree.get_rlPair();
					if(temp.size() == 0){
						cout << "No inserts would cause a right-left rotation." << endl;
					}else{
						cout << "The following inserts would cause a right-left rotation:" << endl;
						for(size_t i = 0; i < temp.size()-1; i++){
							if(temp[i].first != temp[i].second)
								cout << temp[i].first << " to " << temp[i].second << ", ";
							else 
								cout << temp[i].first << ", ";
						}

						if(temp[temp.size()-1].first != temp[temp.size()-1].second)
							cout << temp[temp.size()-1].first << " to " << temp[temp.size()-1].second << endl;
						else
							cout << temp[temp.size()-1].first << endl;
					}

				}else if(arg == "right-right"){
					tree.reset();
					tree.printRotation();
					vector<pair<int, int> > temp = tree.get_rrPair();
					if(temp.size() == 0){
						cout << "No inserts would cause a right-right rotation." << endl;
					}else{
						cout << "The following inserts would cause a right-right rotation:" << endl;
						for(size_t i = 0; i < temp.size()-1; i++){
							if(temp[i].first != temp[i].second)
								cout << temp[i].first << " to " << temp[i].second << ", ";
							else 
								cout << temp[i].first << ", ";
						}

						if(temp[temp.size()-1].first != temp[temp.size()-1].second)
							cout << temp[temp.size()-1].first << " to " << temp[temp.size()-1].second << endl;
						else
							cout << temp[temp.size()-1].first << endl;
					}
				}

			}else if (command == "lookup"){
				int arg;
				int count = 0; 
				vector<int> args;
				tree.reset();

				while(iss >> arg){
					if(tree.lookup(arg)){
						args.push_back(arg);
					}
					count += 1;
				}
				cout << "Found " << args.size() << " of " << count << " nodes: [";
				// for(int a : args){
				// 	if(a != args.front()){
				// 		cout << ", ";
				// 	}
				// 	cout << a;
				// }
				if(args.size() != 0){
					for(size_t i = 0; i < args.size()-1; i++){
						cout << args[i] << ", "; 
					}
					cout<<args[args.size()-1];
				}
				//cout <<args[args.size()-1];
				cout << "]\n" << "Visited " << tree.getVisit() << " (" << (1.0*tree.getVisit()) / count << ") nodes and performed " << tree.getRotation() << " (" << (1.0*tree.getRotation())/count << ") rotations." << endl;

			}
			cout << endl;
		}
		testFile.close();
	}else {
		cout << "cannot open file" << endl;
	}
	return 0;
}