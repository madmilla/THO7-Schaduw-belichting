#ifndef OVEREXPOSURE_TEST
#define OVEREXPOSURE_TEST

#include <ImageLoader.h>

using namespace ImageLib;

/**
*	\Atheur Hendrik Cornelisse
*
*	\Date 14/04/2014
*/

class Overexposure_Test{
public:
	/** Constructor */
	Overexposure_Test();;

	/**	\Overexposure_Detection
	*	\param img
	*	\param Top_Left_X
	*	\param Top_left_Y
	*	\param Top_Right_X
	*	\param Top_Right_Y
	*	\param Bottom_Left_X
	*	\param Bottom_Left_Y
	*	\param Bottom_Right_X
	*	\param Bottom_Right_Y
	*	\return bool
	*/
	bool Overexposure_Detection(std::shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y);

	/**	\Overexposure_Removal
	*	\param img
	*	\param Top_Left_X
	*	\param Top_left_Y
	*	\param Top_Right_X
	*	\param Top_Right_Y
	*	\param Bottom_Left_X
	*	\param Bottom_Left_Y
	*	\param Bottom_Right_X
	*	\param Bottom_Right_Y
	*	\return void
	*/
	void Overexposure_Removal(std::shared_ptr<ImageRGB> img, int Top_Left_X, int Top_Left_Y, int Top_Right_X, int Top_Right_Y, int Bottom_Left_X, int Bottom_Left_Y, int Bottom_Right_X, int Bottom_Right_Y);
};
#endif