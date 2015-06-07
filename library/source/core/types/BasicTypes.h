/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: core
//
//		OpenBOVIL
//			Author: Pablo Ramon Soria
//			Date:	2014-02-19
/////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef _BOVIL_CORE_TYPES_BASICTYPES_H_
#define _BOVIL_CORE_TYPES_BASICTYPES_H_

namespace BOViL{
	//-----------------------------------------------------------------------------
	/** Basic store types.
	*/
	template<typename Type_>
	struct Vec2{
		// Constructors.
		Vec2():	x(0), y(0)	{};
		Vec2(Type_ _x, Type_ _y):	x(_x),  y(_y)	{};

		// Properties.
		Type_ x, y;		// Coordinates of the point in the image.
	};


	typedef Vec2<double>		Vec2d;
	typedef Vec2<int>			Vec2i;
	typedef Vec2<unsigned>		Vec2ui;
	typedef Vec2<unsigned char> Vec2uc;

	//-----------------------------------------------------------------------------
	/** Basic store types.
	*/
	template<typename Type_>
	struct Vec3{
		// Constructors.
		Vec3():	x(0), y(0), z(0)	{};

		Vec3(Type_ _x, Type_ _y, Type_ _z):	x(_x),  y(_y),	z(_z)	{};

		// Properties.
		Type_ x, y, z;		// Coordinates of the point in the image.
	};


	typedef Vec3<double>		Vec3d;
	typedef Vec3<int>			Vec3i;
	typedef Vec3<unsigned>		Vec3ui;
	typedef Vec3<unsigned char> Vec3uc;

	//-----------------------------------------------------------------------------
	/** Basic class that holds information of generic image object
	*/
	class ImageObject{		// Summarized object.
	public:
		/** \brief
		*/
		ImageObject(Vec2ui _upperLeft, Vec2ui _downRight, int _size, int _color){
			centroid = Vec2ui((_upperLeft.x + _downRight.x)/2, (_upperLeft.y + _downRight.y)/2);
			width = _downRight.x - _upperLeft.x;
			height = _downRight.y - _upperLeft.y;
			size = _size;
			color = _color;
		};

		/** \brief
		*/
		ImageObject(Vec2ui _centroid, unsigned _width, unsigned _height, int _size, int _color){
			centroid = _centroid;
			width = _width;
			height = _height;
			size = _size;
			color = _color;
		};
			
		/** \brief get centroid of object in the image. 666 rename to centroid();
		*/
		Vec2ui getCentroid() const {return centroid;};
		
		/** \brief get width of object. 666 rename to width().
		*/
		int getWidth() const {return width;};
		
		/** \brief get height of object. 666 rename to height().
		*/
		int getHeight() const {return height;};
		
		/** \brief get color of object. 666 rename to color(). 666 Only used in CCS, need review.
		*/
		int getColor() const {return color;};
		
		/** \brief get number of pixels of the object. 666 rename to size().
		*/
		int getSize() const {return size;};
	private:
		Vec2ui centroid;
		int width, height;
		int color;
		int size;
	};

}	// namespace BOViL


#endif	//_BOVIL_CORE_TYPES_BASICTYPES_H_