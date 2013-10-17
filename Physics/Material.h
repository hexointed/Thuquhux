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
	Material();
	~Material();
	double& density();
	double& restitution();	

private:
	double _density;
	double _restitution;
	
	
};
#endif	/* MATERIAL_H */

