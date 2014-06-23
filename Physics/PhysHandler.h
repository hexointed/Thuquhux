/*
 * File: Physics.h
 * Author: Charles Gilljam
 *
 * Date: 2013-11-26 12:36
 *
 */

#ifndef PHYSHANDLER_H
#define PHYSHANDLER_H
#include "../NPC/NPC.h"
#include <vector>

namespace Physics {
	class Object;
}

class PhysHandler{
public:
	PhysHandler();
	void handle(double time);
	
	void addPhysObject(Physics::Object a);
	
	std::vector<Physics::Object> physObjects;
	std::vector<std::pair<NPC , Physics::Object>> NPCs;
private:
	
};

#endif /* PHYSHANDLER_H */
