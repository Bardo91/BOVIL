/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: test
//
//		Author: Pablo Ram�n Soria
//		Date:	2014-05-12
//
/////////////////////////////////////////////////////////////////////////////////////////

#include "TestGroundEKF.h"
#include <Dense>

using namespace Eigen;
using namespace std;

bool openInputFile(std::ifstream& _inFile, std::string _path);
bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer);

void testSegmentation(std::string _filePath, std::function<std::string(unsigned int)> _nameGen, QuadParser _parser){
	///////////////////////////////////////////////////
	std::ofstream outFile;
	std::string pathName;
	pathName = "./outputFile_GroundTracking.txt";
	outFile.open(pathName.c_str());
	///////////////////////////////////////////////////


	std::cout << "TESTING SEGMENTATION ALGORITHM && EKF" << std::endl;
	//cv::Mat img, ori;
	unsigned char img;
	int width, height, channels;
	
	std::cout << "--Path of images: " << _filePath << std::endl;

	bool condition = true;
	int i = 0;

	std::cout << "--Init Timer" << std::endl;
	BOViL::STime::init();

	BOViL::STime *time = BOViL::STime::get();

	double t0, t1, t2, t3;

	std::cout << "--Create Clustered Space" << std::endl;
	BOViL::ColorClusterSpace *cs = BOViL::CreateHSVCS_8c(255U,255U, std::uint8_t(BOViL::bin2dec("00000010")));

	//-------
	std::cout << "--Init Stereo EKF" << std::endl;
	BOViL::algorithms::GroundTrackingEKF groundEKF;

	Matrix<double, 4, 4> Q;
	Q <<	0.05, 0, 0, 0,
			0, 0.05, 0, 0,
			0, 0, 0.05, 0,
			0, 0, 0, 0.05;
	Matrix<double, 2, 2> R;
	R <<	0.1, 0,
			0, 0.1;
	Matrix<double, 4, 1> x0;
	x0 <<	5.0,//0, 
			12.0,//0, 
			0.0,//0, 
			0.0;

	groundEKF.setUpEKF(Q, R, x0);

	groundEKF.setUpCamera(738.143358488352310, 346.966835812843040, 240.286986071815390);
	double inputBuffer[128];	// Size is huge enough to storing many objects's variables
	std::ifstream inputFile;
	
	std::cout << "--Open Input File" << std::endl;
	
	std::stringstream viconSS;
	viconSS << _filePath;
	viconSS << "ViconData2.txt";

	condition = openInputFile(inputFile, viconSS.str());	

	double lastTime = 0;

	
	while (condition){
		t0 = time->getTime();

		// ----------------- IMAGE SEGMENTATION ------------------------
		std::stringstream ss;

		ss << _filePath;
		ss << _nameGen(i);

		std::string imagePath = ss.str();

		SOIL_load_image(imagePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

		//img = cv::imread(imagePath, 1/*CV_LOAD_IMAGE_COLOR*/);
		//img.copyTo(ori);

		std::vector<BOViL::ImageObject> objects;

		cv::cvtColor(img, img, 40 /*CV_BGR2HSV*/);

		BOViL::algorithms::ColorClustering<std::uint8_t>(img.data,		// Image pointer
			img.cols,		// Width
			img.rows,		// Height
			5,				// Size Threshold
			objects,		// Output Objects
			*cs);			// Segmentation function 

		t1 = time->getTime();
		std::cout << "Number of detected Objects1 in the scene: " << objects.size() << std::endl;

		// ----------------- TRACKING ALGORITHM ------------------------

		// Select Oject
		int maxSize = 0, maxIndex = 0;
		for (unsigned int obj = 0; obj < objects.size(); ++obj){
			if (objects[obj].getSize() > maxSize){
				maxSize = objects[obj].getSize();
				maxIndex = obj;
			}
		}

		if (objects.size() == 0){
			cv::hconcat(ori, img, ori);
			cv::imshow("ORIGINAL", ori);
			cv::waitKey(3);
			continue;
		}

 		BOViL::Point2ui p = objects[maxIndex].getCentroid();
		cv::circle(ori, cv::Point2d(p.x, p.y), objects[maxIndex].getHeight() / 2, cv::Scalar(0, 255, 0), 1);

		cv::hconcat(ori, img, ori);
		cv::imshow("ORIGINAL", ori);

		t2 = time->getTime();
		dropLineIntoBuffer(inputFile, inputBuffer);		// Get objects info.
		QuadState state = _parser(inputBuffer);

		// Update cameras pos and ori
		
		AngleAxis<double> Rx(state.eulerAngles[0], Vector3d(1, 0, 0));
		AngleAxis<double> Ry(state.eulerAngles[1], Vector3d(0, 1, 0));
		AngleAxis<double> Rz(state.eulerAngles[2], Vector3d(0, 0, 1));

		//Matrix<double, 3, 3> Rx = createRotationMatrix(eEdges::EdgeX, state.eulerAngles[0]);
		//Matrix<double, 3, 3> Ry = createRotationMatrix(eEdges::EdgeY, state.eulerAngles[1]);
		//Matrix<double, 3, 3> Rz = createRotationMatrix(eEdges::EdgeZ, state.eulerAngles[2]);

		Matrix<double, 3, 3> camOri = (Rz*Ry*Rx).matrix();
		

		// Adaptation to Alex edges.
		AngleAxis<double> rot1(3.1416 / 2, Vector3d(1, 0, 0));
		AngleAxis<double> rot2(3.1416 / 2, Vector3d(0, 0, 1));

		Matrix<double, 3, 3> adaptRot = (rot1*rot2).matrix();
		
		//Matrix<double, 3, 3> adaptRot =	createRotationMatrix(eEdges::EdgeX, PiCte / 2)*
		//								createRotationMatrix(eEdges::EdgeZ, PiCte / 2);
		
		
		camOri = adaptRot*camOri;

		//Matrix<double> camOri = createRotationMatrixEuler(inputBuffer[10] - 3.1416 / 2, inputBuffer[11], inputBuffer[12] - 3.1416 / 2);


		Matrix<double, 3, 1> posC1;
		posC1 << state.position[0], state.position[1], state.position[2];

		groundEKF.updateCamera(	posC1, camOri, inputBuffer[3]);

		// EKF step
		Matrix<double, 2, 1> zk;
		zk << double(objects[maxIndex].getCentroid().x),
			img.rows - double(objects[maxIndex].getCentroid().y);

		groundEKF.stepEKF(zk, inputBuffer[0] - lastTime);
		lastTime = inputBuffer[0];

		Matrix<double, 3, 1> stateEKF = groundEKF.getStateVector();

		t3 = time->getTime();
		//double fps = 1 / (t1 - t0);
		//std::cout << fps << " fps" << std::endl;

		cout << stateEKF << endl;
		
		outFile << inputBuffer[0] << "\t" << stateEKF[0] << "\t" << stateEKF[1] << "\t" << stateEKF[2] << "\t" << zk[0] << "\t" << zk[1] << "\t" << 1 / (t1 - t0) << "\t" << 1 / (t3 - t2) << "\n";

		cv::waitKey(1);

		++i;
	}

	std::cout << "----------End----------" << std::endl;

}


bool openInputFile(std::ifstream& _inFile, std::string _path){
	_inFile.open(_path);

	if(!_inFile.is_open() || !_inFile.good())
			return false;

	return true;
}

bool dropLineIntoBuffer(std::ifstream& _inFile, double* _buffer){
	std::string line;
	int colCounter = 0;
	int init = 0;
	int counter = 0;

	getline(_inFile, line);
	colCounter = line.size();

	if(colCounter < 0)
		return false;
				
	int index = 0;
	for (int i = 0; i < colCounter; i++) {
		if (((int) line.at(i)) == 9) {
			std::string part = line.substr(init, i - init);
			_buffer[index] = atof(part.c_str());
			init = i + 1;
			counter++;
			index++;
		}
	}

	return true;
}
