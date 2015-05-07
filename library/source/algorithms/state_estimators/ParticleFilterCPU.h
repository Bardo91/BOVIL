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

// Particle filter class
template<typename ParticleType_, typename ObservableData_>
class ParticleFilterCPU {
public:
	ParticleFilterCPU(unsigned _nuParticles) :mNuParticles(_nuParticles) { init(); };
	
	void step(ObservableData_ &_data);
	
	unsigned nuParticles() const { return mNuParticles; };
	std::vector<ParticleType_> particles() const{ return mParticles; };

private:
	void init();

	void simulate();
	void calcWeigh(ObservableData_ &_data);
	void resample();

private:
	unsigned mNuParticles;
	std::vector<ParticleType_> mParticles;

public:
	// Particle interface
	class Particle {
	public:
		virtual void simulate() = 0;
		virtual void calcWeigh(ObservableData_ &_data) = 0;

		std::pair<unsigned, double> &weigh() { return mWeight; };

	protected:
		std::pair<unsigned, double> mWeight;
	};	//	 class Particle


};	// class ParticleFilterCPU

#include "ParticleFilterCPU.inl"

#endif	//	_GLHL_TEST_PARTICLE_FILTER_CPU_H_

