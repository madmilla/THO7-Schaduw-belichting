#include <ImageLoader.h>

using namespace ImageLib;
using namespace std;

class RemoveLight{
public:
	RemoveLight();
	void Remove(std::shared_ptr<ImageRGB> image, int TopLeftX, int TopLeftY, int TopRightX, int TopRightY, int BottomLeftX, int BottomLeftY, int BottomRightX, int BottomRightY);
};