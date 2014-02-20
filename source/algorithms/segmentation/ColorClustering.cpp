/////////////////////////////////////////////////////////////////////////////////////////
//		OpenBIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-13
/////////////////////////////////////////////////////////////////////////////////////////
//

#include "ColorClustering.h"		// Header of the algorithm

using namespace std;

namespace BIL{
	namespace algorithms{
		template<typename T> void ColorClustering(	T *_image, 
													int _width,
													int _height, 
													int _threshold, 
													std::vector<ImageObject> _objects,
													std::function<int (T _a, T _b, T _c)> _function){
			vector<vector<LineRLE>> aRLE;		// Matrix with every RLE encoded objects
			vector<SegmentedObject> objects;	// Auxiliary object that store Segmented objects while they are been growing.

			short int color, colorRLE = -1;
			short int js = 0;
			for(short int i = 0; i < _height ; i ++){	// Main vertical loop on the image

				// First horizontal loop. It will segmentate every pixel and encode it in a RLE if it's a desired color.
				vector<LineRLE> temp;
				for(int j = 0; j < _width ; j ++){		
					// 666 TODO:	Si hacemos una funcion que directamente modifique la imagen nos ahorramos 
					//				tener que comprobar luego el color que la funcion que determina el color elige para 
					//				luego modificar la imagen de nuevo para poner los colores simplificados (menos ifs... menos indirecciones.... etc....).
					

					// This function segmentate the pixel and return the color of those.
					color = _function(_image[i + 3*j + 0],
													_image[i + 3*j + 1],
													_image[i + 3*j + 2]);

					if(color != -1){
						if(j == 0){			// If it's the first pixel of the row, set the current RLE color to the current pixel's color and initialize the js counter of columns.
							colorRLE = color;
							js = 0;
						} else {			// If not
							if (color != colorRLE){	// If the color of the current pixel is not the same that the current lineRLE's color then create the previous lineRLE and start a new.
								LineRLE lineRLE(i, js, j, colorRLE);
								temp.push_back(lineRLE);
								colorRLE = color;
								js = j;

							} else if (j == _height - 1){	// If it's the last pixel of the row finallize the last RLE line of this row.
								LineRLE lineRLE(i, js, j, colorRLE);
								temp.push_back(lineRLE);

							} 
						}
					}
				}
				aRLE.push_back(temp);
				// End of first horizontal loop for RLE encoding and segmentation.

				// Now start the harder step, that takes the lineRLE objects of the current and previous row and connect them in order to collect every piece of the complete object
				if(i){	//First line cannot have parents
					unsigned short int pcRLE = 0, ppRLE = 0; 		// Index of the current lineRLE on the i row of aRLE
					unsigned short int jc = aRLE[i][pcRLE], jp = aRLE[i-1][ppRLE];	// Index of current row's column and previous row's column.

					while(1){	// Connecting RLEs
						if(	aRLE[i-1][ppRLE].color == aRLE[i][pcRLE].color &&	// If lineRLEs have same color and have some column in common...
							aRLE[i-1][ppRLE].je >= aRLE[i][pcRLE].js &&
							aRLE[i-1][ppRLE].js <= aRLE[i][pcRLE].je){
								if(!aRLE[i][pcRLE].hasParent){			// If current lineRLE has no parent
									if(aRLE[i-1][ppRLE].hasParent){		// Use previous parent
										aRLE[i][pcRLE].pi = aRLE[i-1][ppRLE].pi;
										aRLE[i][pcRLE].pj = aRLE[i-1][ppRLE].pj;
										aRLE[i][pcRLE].hasParent = true;

									} else {			// Previous lineRLE is the parent
										aRLE[i][pcRLE].pi = i-1;
										aRLE[i][pcRLE].pj = ppRLE;
										aRLE[i][pcRLE].hasParent = true;

									}
								}else{	// If current lineRLE has parent --> OVERLAP
									if(aRLE[i-1][ppRLE].hasParent){		// There is a "family" of RLE lines
										if((aRLE[i-1][ppRLE].pi != aRLE[i][pcRLE].pi) && (aRLE[i-1][ppRLE].pj != aRLE[i][pcRLE].pj)){
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].pi = aRLE[i][pcRLE].pi;
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].pj = aRLE[i][pcRLE].pj;
											aRLE[aRLE[i-1][ppRLE].pi][aRLE[i-1][ppRLE].pj].hasParent = true;
										}


									} else {			// There is an orphan RLE line
										aRLE[i-1][ppRLE].pi = aRLE[i][pcRLE].pi;
										aRLE[i-1][ppRLE].pj = aRLE[i][pcRLE].pj;
										aRLE[i-1][ppRLE].hasParent = true;

									}
								}
						}	// Connecting RLEs
						if(pcRLE >= aRLE[i].size() - 1 ||ppRLE >= aRLE[i-1].size() -1)
							breal;
						if(jp >= jc){
							pcRLE++;
							jc += aRLE[i][pcRLE].size;
						} else if( jp <= jc){
							ppRLE++;
							jp += aRLE[i-1][ppRLE].size;
						}
					}	// while(1).

				}	// If not first row.

			}	// Vertical loop for each row
			
			// Re-assing overlaped parents
			for(unsigned short int i = 0 ; i < aRLE.size() ; i++){
				for(unsigned short int j = 0 ; j < aRLE[i].size() ; j++){
					if(aRLE[i][j].hasParent){
						LineRLE auxRLE = aRLE[aRLE[i][j].pi][aRLE[i][j].pj];

						int loopCounter = 0;
						while(auxRLE.hasParent && loopCounter < 30){
							aRLE[i][j].pi = auxRLE.pi;
							aRLE[i][j].pj = auxRLE.pj;

							auxRLE = aRLE[auxRLE.pi][auxRLE.pj]

							loopCounter++;
						}
						if (aRLE[i][j].parentJ->iObj == -1) {
							aRLE[aRLE[i][j].pi][aRLE[i][j].pj].iObj = objs.size();
							SegmentedObject obj(aRLE[aRLE[i][j].pi][aRLE[i][j].pj]);
							objects.push_back(obj);
						}
					}
				}	// for i
			}	// for j

			for(unsigned short int i = 0 ; i < aRLE.size() ; i++){
				for(unsigned short int j = 0 ; j < aRLE[i].size() ; j++){
					if(aRLE[i][j].hasParent){
						objects[aRLE[aRLE[i][j].pi][aRLE[i][j].pj].iObjs].addLineObjRLE(aRLE[i][j]);
					}
				}	// for i
			}	// for j
			
			for(unsigned int i = 0; i < objs.size() ; i ++){
				if(objects[i].getSize() >= _sizeThreshold)
					_objects.push_back(ImageObject(objects[i].getUpperLeft(), objects[i].getDownRight(), objects[i].getSize(), objects[i].getColor()));
			}

		}	// ColorClustering(...);

	}	// namespace algorithms.
}	// namespace BIL