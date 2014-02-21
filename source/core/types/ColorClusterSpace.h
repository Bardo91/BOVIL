///////////////////////////////////////////////////////////////////////////////
//
//
//
///////////////////////////////////////////////////////////////////////////////

#include "Colors.h"

#include <math.h>
#include <stdint.h>
#include <string>

#ifndef _OPENBIL_COLORCLUSTERSPACE_H_
#define _OPENBIL_COLORCLUSTERSPACE_H_

#define LOG2 0.3010299957

namespace BIL{
	namespace algorithms {
		template <typename T> class ColorClusterSpace {
		public:
			int size;
			color3<T> *clusters;
			ColorClusterSpace(int, T* _AClass, T* _BClass, T* _CClass, const color3<T>* _colors);
			~ColorClusterSpace();

		private:
			T *AClass;
			T *BClass;
			T *CClass;

		public:
			int operator()(T *_a, T *_b, T *_c){
				c3u col(*_a, *_b, *_c);

				int color =  whichColor(col);	
				if(color != -1){
					*_a = clusters[color].a;
					*_b = clusters[color].b;
					*_c = clusters[color].c;
				} else{
					*_a = 0U;
					*_b = 0U;
					*_c = 0U;
				}

				return color;
			};

			int whichColor(color3<T>& _color){
				int i = (_color.a * (size - 1) / 180); // 666 TODO: improve (get 5%)
				int j = _color.b*(size - 1) >> 7;
				j = (j>>1) + (j&1);
				int k = _color.c*(size - 1) >> 7;
				k = (k>>1) + (k&1);
			

				int res = AClass[i] & BClass[j] & CClass[k]; //Supposing that colors are not over-layed there's only one possible solution and log2(x) returns an integer /

				int aux = 0;

				if (!res)
					return -1;

				while (!(res & 0x01)) {
					res = res >> 1;
					aux += 1;
				}

				return aux;
			}
		};

		template <typename T> ColorClusterSpace<T>::ColorClusterSpace(int n, T *_AClass, T *_BClass,	T *_CClass, const color3<T> *_colors) {

			AClass = new T[n];
			BClass = new T[n];
			CClass = new T[n];
			clusters = new c3u[8];
			size = n;

			for (int i = 0; i < n; i++) {
				AClass[i] = _AClass[i];
				BClass[i] = _BClass[i];
				CClass[i] = _CClass[i];
				if (i < 8)
					clusters[i] = colors[i];
			}
		}

		template <typename T> ColorClusterSpace<T>::~ColorClusterSpace() {
			delete[] AClass;
			delete[] BClass;
			delete[] CClass;
			delete[] clusters;

		}



	} // namespace algorithms.
} // namespace BIL.
#endif // _OPENBIL_COLORCLUSTERSPACE_H_
