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
	template<typename type_>
	struct Point2{
		// Constructors.
		Point2():	x(0), y(0)	{};
		Point2(type_ _x, type_ _y):	x(_x),  y(_y)	{};

		// Properties.
		type_ x, y;		// Coordinates of the point in the image.
	};


	typedef Point2<double>			Point2d;
	typedef Point2<int>				Point2i;
	typedef Point2<unsigned int>		Point2ui;

	//-----------------------------------------------------------------------------
	template<typename type_>
	struct Point3{
		// Constructors.
		Point3():	x(0), y(0), z(0)	{};

		Point3(type_ _x, type_ _y, type_ _z):	x(_x),  y(_y),	z(_z)	{};

		// Properties.
		type_ x, y, z;		// Coordinates of the point in the image.
	};


	typedef Point2<double>			Point2d;
	typedef Point2<int>				Point2i;
	typedef Point2<unsigned int>		Point2ui;

	//-----------------------------------------------------------------------------
	class ImageObject{		// Summarized object.
	public:
		ImageObject(Point2ui _upperLeft, Point2ui _downRight, int _size, int _color){
			centroid = Point2ui((_upperLeft.x + _downRight.x)/2, (_upperLeft.y + _downRight.y)/2);
			width = _downRight.x - _upperLeft.x;
			height = _downRight.y - _upperLeft.y;
			size = _size;
			color = _color;
		};
			
		Point2ui getCentroid() const {return centroid;};
		int getWidth() const {return width;};
		int getHeight() const {return height;};
		int getColor() const {return color;};
	private:
		Point2ui centroid;
		int width, height;
		int color;
		int size;
	};

}	// namespace BOViL


#endif	//_BOVIL_CORE_TYPES_BASICTYPES_H_