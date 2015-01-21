///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParticleFilter class

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_>
void ParticleFilterCPU<ParticleType_>::step(const Particle &_realParticle) {
	simulate();
	calcWeigh(_realParticle);
	resample();
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_>
void ParticleFilterCPU<ParticleType_>::init(){
	for (unsigned i = 0; i < mNuParticles; i++){
		mParticles.push_back(ParticleType_());
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_>
void ParticleFilterCPU<ParticleType_>::simulate() {
	for (unsigned i = 0; i < mNuParticles; i ++) {
		mParticles[i].simulate();
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_>
void ParticleFilterCPU<ParticleType_>::calcWeigh(const Particle &_realParticle) {
	for (unsigned i = 0; i < mNuParticles; i++) {
		mParticles[i].calcWeigh(_realParticle);
	}
}

//---------------------------------------------------------------------------------------------------------------------
template<typename ParticleType_>
void ParticleFilterCPU<ParticleType_>::resample() {
	std::vector<ParticleType_> newParticles;
	double beta = 0.0;
	unsigned index = unsigned(double(rand()) / RAND_MAX * mNuParticles);
	double maxWeigh = 0.0;

	for (unsigned i = 0; i < mNuParticles; i++) {
		if (mParticles[i].weigh() > maxWeigh)
			maxWeigh = mParticles[i].weigh();
	}

	for (unsigned i = 0; i < mNuParticles; i++) {
		beta += double(rand()) / RAND_MAX * 2.0 * maxWeigh;
		while (beta > mParticles[index].weigh()) {
			beta -= mParticles[index].weigh();
			index = (index + 1) % mNuParticles;
		}
		newParticles.push_back(mParticles[index]);
	}
	
	mParticles = newParticles;
}
