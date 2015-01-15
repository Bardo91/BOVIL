///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GLHL Tests - Particle Filter
//			Author:	Pablo R.S.
//			Date:	2014-Dec-21
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main


#include <iostream>
#include <string>
#include <ctime>
	
#include <src/core/base/Context.h>
#include <src/core/utils/time/time.h>

#include "ParticleFilterGPU.h"
#include "ParticleFilterCPU.h"
#include "Robot.h"

class ParticleRobot : public Particle, public Robot{
public:
	ParticleRobot() { setNoise(0.05, 0.05, 5.0); };
	void simulate() { move(0.1, 5.0); };
	void calcWeigh(Particle &_realParticle) { mWeigh = measurementProb(static_cast<ParticleRobot &>(_realParticle).sense()); };

	operator std::array<double, 3>(){ return position(); }

};
//---------------------------------------------------------------------------------------------------------------------
using namespace std;
using namespace GLHL;

//---------------------------------------------------------------------------------------------------------------------
std::array<double, 3> mediumState(std::vector<ParticleRobot> _particles);
void particleFilterCPU();
void particleFilterGPU();

//---------------------------------------------------------------------------------------------------------------------
int main(void){
	
	//particleFilterCPU();
	
	particleFilterGPU();

	std::cout << "Finished" << std::endl;
	
	system("PAUSE");

}

//---------------------------------------------------------------------------------------------------------------------

std::array<double, 3> mediumState(std::vector<ParticleRobot> _particles){
	std::array<double, 3> position = {0.0, 0.0, 0.0};
	for (unsigned i = 0; i < _particles.size(); i++){
		std::array<double, 3> pos = _particles[i];
		position[0] += pos[0];
		position[1] += pos[1];
		position[2] += pos[2];
	}
	position[0] /= _particles.size();
	position[1] /= _particles.size();
	position[2] /= _particles.size();

	return position;
}

void particleFilterCPU() {
	srand(unsigned(time(NULL)));

	ParticleFilterCPU<ParticleRobot> filter(10000);
	filter.init();

	ParticleRobot robot;
	STime *sTime = STime::get();
	double time = 0.0;
	for (unsigned i = 0; i < 50; i++) {
		double t0 = sTime->getTime();
		robot.simulate();
		filter.step(robot);
		time += sTime->getTime() - t0;

		std::array<double, 3> medState = mediumState(filter.particles());
		std::array<double, 3> realState = robot.position();
		std::cout << "-------------------------------------------------------------------" << std::endl;
		std::cout << "Real state. X:" << realState[0] << " ; Y: " << realState[1] << " ; Ori: " << realState[2] << std::endl;
		std::cout << "Promediate state. X:" << medState[0] << " ; Y: " << medState[1] << " ; Ori: " << medState[2] << std::endl;
	}
	std::cout << "Step Time: " << time / 50 << std::endl;

}

void particleFilterGPU() {
	srand(unsigned(time(NULL)));
	Context context;


	Robot robot;
	robot.setNoise(0.05, 0.05, 5.0);

	// 666 TODO Relative path to vertex shader?
	ParticleFilterGPU pfGPU(1000, "../../src/shaders/particleFilterShaderTemplate.fragment");
	STime *sTime = STime::get();
	double time = 0.0;
	for (unsigned i = 0; i < 50; i++) {
		double t0 = sTime->getTime();
		robot.move(0.1, 5.0);
		std::array<double, 4> measure = robot.sense();
		std::cout << "Real particle: " << robot << std::endl;
		pfGPU.step(vec4f(float(measure[0]), float(measure[1]), float(measure[2]), float(measure[3])));
		std::cout << "--------------------------------------------------------------------------------------" << std::endl;

		time += sTime->getTime() - t0;
	}

	std::cout << "Step Time: " << time / 50 << std::endl;
}