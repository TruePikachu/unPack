#include "packentry.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	if(argc!=3) {
		cout << "Usage: " << argv[0] << " <PACK FILE> <OUTPUT DIR/>\n";
		return 0;
	}

	// Open the pack file
	ifstream packFile(argv[1]);
	// Read the null and the number of entries
	uint32_t buffer;
	packFile.read((char*)&buffer,4);
	if(buffer)
		throw runtime_error("+0x0 != 0x00000000");
	packFile.read((char*)&buffer,4);
	vector< PackEntry > entries;
	for(int i=0;i<buffer;i++)
		entries.push_back(PackEntry(i,packFile));
	// Ensure we have 8 null bytes
	packFile.read((char*)&buffer,4);
	if(buffer)
		throw runtime_error("Null entry not null");
	packFile.read((char*)&buffer,4);
	if(buffer)
		throw runtime_error("Null entry not null");
	// Write each file
	char filename[512];
	for(vector< PackEntry >::iterator it=entries.begin();it!=entries.end();++it) {
		sprintf(filename,"%s%04X.dat",argv[2],it->getID());
		ofstream file(filename);
		it->getData(file);
		file.close();
	}
	cout << "Wrote " << entries.size() << " files.\n";
	return 0;
}
