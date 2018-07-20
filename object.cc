#include "object.h";

using namespace std;

Object::Object(ObjectType type): type{type} {}

Object::~Object() {}

ObjectType Object::getType() {
	return type;
}
