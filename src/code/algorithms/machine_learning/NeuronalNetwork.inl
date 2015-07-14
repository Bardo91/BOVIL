///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


namespace BOViL {
	namespace algorithms {
		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned Layers_, unsigned HiddenUnits_, unsigned OutputSize_>
		template<unsigned TrainSize_>
		void NeuronalNetwork<InputSize_, Layers_, HiddenUnits_, OutputSize_>::train(const Eigen::Matrix<double, TrainSize_, InputSize_> &_x, const Eigen::Matrix<double, TrainSize_, OutputSize_> &_y) {

		}

		//-------------------------------------------------------------------------------------------------------------
		template<unsigned InputSize_, unsigned Layers_, unsigned HiddenUnits_, unsigned OutputSize_>
		Eigen::Matrix<double, OutputSize_, 1> NeuronalNetwork<InputSize_, Layers_, HiddenUnits_, OutputSize_>::evaluate(const Eigen::Matrix<double, InputSize_, 1> &_x) {
			Eigen::Matrix<double, OutputSize_, 1> y;
			return y;
		}

	}
}