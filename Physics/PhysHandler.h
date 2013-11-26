/*
 * File: Physics.h
 * Author: Charles Gilljam
 *
 * Date: 2013-11-26 12:36
 *
 */

#ifndef PHYSHANDLER_H
#define PHYSHANDLER_H

#include <vector>

class PhysObject;

class PhysHandler{
public:
	PhysHandler();
	void handle(double time);
	
	void addPhysObject(PhysObject a);
	
	std::vector<PhysObject> physObjects;
private:
	
};

#endif /* PHYSHANDLER_H */
