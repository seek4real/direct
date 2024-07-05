//sid.cpp

#include "../include/sid.h"
//#include <hash_map>
#include <unordered_map>
#include <utility>
#include <xhash>

typedef std::pair<sid, const char*> PairSid;
//typedef std::hash_map<sid, const char*> Map;
typedef std::unordered_map<sid, const char*> Map;
static Map gSidTable;


sid getSid(const char* str)
{
	sid id1 = stdext::hash_value(str);

	Map::iterator _pair = gSidTable.find(id1);
	return _pair->first;
}
