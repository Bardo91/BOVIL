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
#include <map>

/** This class implements needed pipeline of whole particle filter.  Template arguments are the type of particle and the 
*	type of observable data.
*
*	777 example of use
*/

template<typename ParticleType_, typename ObservableData_>
class ParticleFilterCPU {
public:
	/** \brief	Class constructor. Start particle filter with the given number of particles.
	*	@param	_nuParticles: Number of particles that will be used in the particle filter
	*/
	ParticleFilterCPU(unsigned _nuParticles) :mNuParticles(_nuParticles) { init(); };
	
	/** \brief	Iterate particle filter using given data
	*	@param _data: observable data to feed particle filter.
	*/
	void step(ObservableData_ &_data);
	
	/** \brief	Reinicialize particles using _prob as top threshold of a random number uniformly distributed.
	*	777 Example
	*	@param _prob: number from 0.0 to 1.0 used in condition if less than  => reinitialize particle.
	*/
	void reinitialize(const double &_prob);

	/** \brief	get number of particles.
	*/
	unsigned nuParticles() const { return mNuParticles; };
	
	/** \brief	get set of particles.
	*/
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

