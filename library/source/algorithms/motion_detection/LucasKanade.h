///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL:	Lucas Kanade
//			Author:	Pablo Ramon Soria (a.k.a. Bardo91)
//			Date:	2015-APR-14
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


namespace BOViL{
	namespace algorithms{
		struct ImageHandle{
			ImageHandle(unsigned char* _data, unsigned _width, unsigned _height){
				mData		= _data;
				mWidth		= _width;
				mHeight		= _height;
			}

			unsigned char operator() (unsigned _col, unsigned _row, unsigned _channel = 0){
				return mData[_row*mWidth + _col];
			}

		private:
			unsigned char *mData;
			unsigned mWidth, mHeight;
		};

		void lucasKanade(	unsigned char * _image1,
							unsigned char * _image2,
							unsigned		_width,
							unsigned		_height, 
							unsigned		_kernelSize);



	}	//	namespace algorithms
}	//	namespace BOViL