#ifndef NPC_H
#define NPC_H

class NPC{

public:

private:

	PointVector<> position;

	bool randomBool;

	double velocityx;
	double velocityy;
	double velocityz;

	double climbingAbilityx;
	double climbingAbilityy;
	double climbingAbilityz;

	double getPosition(); 
	double makePosition();
	double updatePosition();
}

#endif /*NPC_H*/
