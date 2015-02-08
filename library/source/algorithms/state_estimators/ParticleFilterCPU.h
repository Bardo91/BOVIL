///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilterCPU class


#ifndef _GLHL_TEST_PARTICLE_FILTER_CPU_H_
#define _GLHL_TEST_PARTICLE_FILTER_CPU_H_

#include <vector>

// Particle interface
class Particle {
public:
	virtual void simulate() = 0;
	virtual void calcWeigh(Particle &_realParticle) = 0;

	std::pair<unsigned, double> &weigh() { return mWeigh; };
	
protected:
	std::pair<unsigned, double> mWeigh;
};	//	 class Particle


// Particle filter class
template<typename ParticleType_>
class ParticleFilterCPU {
public:
	ParticleFilterCPU(unsigned _nuParticles) :mNuParticles(_nuParticles) { init(); };
	
	void step(Particle &_realParticle);
	
	unsigned nuParticles() const { return mNuParticles; };
	std::vector<ParticleType_> particles() const{ return mParticles; };

private:
	void init();

	void simulate();
	void calcWeigh(Particle &_realParticle);
	void resample();

private:
	unsigned mNuParticles;
	std::vector<ParticleType_> mParticles;

};	// class ParticleFilterCPU

#include "ParticleFilterCPU.inl"

#endif	//	_GLHL_TEST_PARTICLE_FILTER_CPU_H_

