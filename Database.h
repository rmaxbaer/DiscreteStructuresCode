#ifndef DATABASE_H
#define DATABASE_H

#include "Relation.h"

#include <map>

using namespace std;
class Database : public map<string, Relation>
{
public:
	Database() {};
	~Database() {};
private:
};


#endif // !DATABASE_H