///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_>
		Regression<InputSize_>::Regression(const Eigen::Matrix<double, InputSize_, InputSize_> &_hypothesis) {

		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_>
		template<unsigned TrainSize_>
		bool Regression<InputSize_>::train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, 1> &_y) {
			return false;
		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_>
		double Regression<InputSize_>::evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x) {
			return NAN;
		}
	}	//	namespace algorithms
}	//	namespace BOViL
