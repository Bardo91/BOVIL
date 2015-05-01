///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOVIL: test image segmentation
//			Author: Pablo Ramon Soria
//			Date:	2015-MAY-01
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Color clustered Space creator


#ifndef BOVIL_ALGORITHMS_SEGMENTATION_COLOR_CLUSTERING_TYPES_COLOR_CLUSTERED_SPACE_CREATOR_H_
#define BOVIL_ALGORITHMS_SEGMENTATION_COLOR_CLUSTERING_TYPES_COLOR_CLUSTERED_SPACE_CREATOR_H_

#include "ColorClusterSpace.h"

namespace BOViL{

	/**	\brief This method provide a Color clustered space that could be used to segmentate one single color.
	*
	*
	* @param _c1Top: top threshold of first channel.
	* @param _c1Bottom: bottom threshold of first channel.
	* @param _c2Top: top threshold of second channel.
	* @param _c2Bottom: bottom threshold of second channel.
	* @param _c3Top: top threshold of third channel.
	* @param _c3Bottom: bottom threshold of third channel.
	* @param _c1Max: max value of first channel
	* @param _c2Max: max value of second channel
	* @param _c3Max: max value of third channel
	* @param _subdivision: Resolution of the space.
	*/

	ColorClusterSpace createSingleClusteredSpace(	unsigned char _c1Bottom,
													unsigned char _c1Top,
													unsigned char _c2Bottom,
													unsigned char _c2Top,
													unsigned char _c3Bottom,
													unsigned char _c3Top,
													unsigned char _c1Max,
													unsigned char _c2Max,
													unsigned char _c3Max,
													unsigned char _subdivision ){

		// Channels thresholds.
		unsigned char *AClass = new unsigned char [_subdivision];
		unsigned char *BClass = new unsigned char [_subdivision];
		unsigned char *CClass = new unsigned char [_subdivision];

		unsigned char incC1 = _c1Max/_subdivision;
		unsigned char incC2 = _c2Max/_subdivision;
		unsigned char incC3 = _c3Max/_subdivision;

		for (unsigned i = 0; i < _subdivision; i++){
			AClass[i] = (i*incC1 >= _c1Bottom ) && (i*incC1 <= _c1Top) ? 1 : 0;
			BClass[i] = (i*incC2 >= _c2Bottom ) && (i*incC1 <= _c2Top) ? 1 : 0;
			CClass[i] = (i*incC3 >= _c3Bottom ) && (i*incC1 <= _c3Top) ? 1 : 0;
		}

		// Color dictionary.
		c3u colors[8];
		colors[0] = c3u((_c1Top + _c1Bottom) / 2,
						(_c2Top + _c2Bottom) / 2,
						(_c3Top + _c3Bottom) / 2);

		return ColorClusterSpace(_subdivision, AClass, BClass, CClass, colors);
	}

}

#endif	//	BOVIL_ALGORITHMS_SEGMENTATION_COLOR_CLUSTERING_TYPES_COLOR_CLUSTERED_SPACE_CREATOR_H_
