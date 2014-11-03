#include "packentry.hpp"
#include <istream>
#include <ostream>
#include <stdint.h>
using namespace std;

PackEntry::PackEntry(int id, std::istream& file) : id(id),file(file) {
	uint32_t buf;
	file.read((char*)&buf,4);
	where=buf;
	file.read((char*)&buf,4);
	size=buf;
}

int PackEntry::getID() const {
	return id;
}

std::ostream& PackEntry::getData(std::ostream&os) {
	char *fdata = new char[size];
	file.seekg(where);
	file.read(fdata,size);
	os.write(fdata,size);
	delete[] fdata;
	return os;
}
