#ifndef __PACKENTRY_HPP
#define __PACKENTRY_HPP
class PackEntry;
#include <istream>
#include <ostream>

class PackEntry {
	private:
		std::istream*	file;
		int		id;
		off_t		where;
		size_t		size;
	public:
				 PackEntry	(int,std::istream&);
		int		getID		() const;
		std::ostream&	getData		(std::ostream&);
};

#endif
