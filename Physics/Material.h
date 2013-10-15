/* 
 * File:   Material.h
 * Author: user
 *
 * Created on May 29, 2013, 1:32 PM
 */

#ifndef MATERIAL_H
#define	MATERIAL_H

class Material{
public:
	double& density();
	double& restitution();	

private:
	double density;
	double restitution;
	
	
}
#endif	/* MATERIAL_H */

