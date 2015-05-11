///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilter class

#if defined(__linux__)
#include <stdlib.h>
#endif

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_, typename ObservableData_>
void ParticleFilterCPU<ParticleType_, ObservableData_>::step(ObservableData_ &_data) {
	simulate();
	calcWeigh(_data);
	resample();
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_, typename ObservableData_>
void ParticleFilterCPU<ParticleType_, ObservableData_>::init(){
	for (unsigned i = 0; i < mNuParticles; i++){
		mParticles.push_back(ParticleType_());
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_, typename ObservableData_>
void ParticleFilterCPU<ParticleType_, ObservableData_>::simulate() {
	for (unsigned i = 0; i < mNuParticles; i ++) {
		mParticles[i].simulate();
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_, typename ObservableData_>
void ParticleFilterCPU<ParticleType_, ObservableData_>::calcWeigh(ObservableData_ &_data) {
	for (unsigned i = 0; i < mNuParticles; i++) {
		mParticles[i].calcWeigh(_data);
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_, typename ObservableData_>
void ParticleFilterCPU<ParticleType_, ObservableData_>::resample() {
	// Ponderate weighs
	std::map<unsigned, double> weights;
	for (unsigned i = 0; i < mNuParticles; i++){
		if (weights[mParticles[i].weigh().first] < mParticles[i].weigh().second)
			weights[mParticles[i].weigh().first] = mParticles[i].weigh().second;
	}

	for (std::pair<unsigned, double> weight : weights){
		if (weight.second == 0.0)
			return;	// Data corrupted or null.
	}

	for (unsigned i = 0; i < mNuParticles; i++){
		double weigh = mParticles[i].weigh().second;
		unsigned index = mParticles[i].weigh().first;
		mParticles[i].weigh().second = weigh / weights[index];
	}
	//
	std::vector<ParticleType_> newParticles;
	double beta = 0.0;
	unsigned index = unsigned(double(rand()) / RAND_MAX * mNuParticles);
	double maxWeigh = 1.0;

	for (unsigned i = 0; i < mNuParticles; i++) {
		beta += double(rand()) / RAND_MAX * 2.0 * maxWeigh;
		while (beta > mParticles[index].weigh().second) {
			beta -= mParticles[index].weigh().second;
			index = (index + 1) % mNuParticles;
		}
		newParticles.push_back(mParticles[index]);
	}
	
	mParticles = newParticles;
}
