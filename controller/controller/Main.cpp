// I need this line in the library... to stop the controller from tossing salads everytime he cant load an image.
	#define cimg_debug 0    
#include <memory>
#include <exception>

//UTIL
#include "Util/general.h"
#include "Util/stopwatch.h"
#include "Exceptions/allExceptions.h"

//Classes
#include "Localization/localization.h"
#include "Shadow_Lighting/shadow_lighting.h"
#include "Rotation/imageCorrection.h"

//#include "OCR1/OCRPatternMatching.h"  TRASH
//#include "OCR1/SplitLicensePlate.h"	TRASH

#include "OCR2/FileData.h"
#include "OCR2/OpticalCharacterRecognition2.h"

	// File: Main.cpp
	// @Author Lars Veenendaal 1633223
	// 0.4 - Implementation Rotation & Cleaned up code and file structure.
	// 0.3 - Implementation Localization & Shadow
	// 0.2 - General testing added.
	// 0.1 - Skeleton setup.

using namespace ImageLib;
using namespace std;

void recognition(char* filename){
	// Needed Defines
	shared_ptr<ImageRGB> img;
	General gen;
	vector<Blob> possibleBlobs;
	// General
	try{
		gen.Input_Control(filename); // Run checks for existance of the file, filetype and size.
	}
	catch (GeneralExceptions &gE){} // If something happens here kill the program.
	catch (std::bad_alloc &gE){ cerr << "Out of memory." << endl; }

	cout << "General checks done: " << endl;
	img = loadImg(filename); // if all is well this work fine now.

	Stopwatch timeKeeper; // Moraalistisch starten we de klok zodra de afbeelding is ingeladen? of zodra de order geplaatst is?

	// Lokalisatie
	try{
		//Gets the img.
		YellowColorFilter ycf;
		BlobDetection bd;
		BlobCheck bc;
		ImageRGB input = *img;
		ycf.filterImage(input);
		int minBlobSize = (input.width() * input.height()) * 0.0015;
		possibleBlobs = bd.Invoke(input, minBlobSize);
		string localisation = filename;
		localisation += "lokalisatie.jpg";
		//saveImg(input, localisation.c_str());
	}
	catch (LocalizationExceptions &lE){ cout << "LOC ERROR" << endl; }

	cout << "Localization done: ";
	timeKeeper.printTimePast();

	// Shadow & Lighting
	Shadow_Lighting snl;
	shared_ptr<ImageRGB> snl_img = img;
	try{
		vector<int> t = possibleBlobs[0].getCornerPoints();
		snl.checkForDefects(snl_img, t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7]);
		string snl = filename;
		snl += "snl.jpg";
		saveImg(*snl_img, snl.c_str());
	}
	catch (ShadowExceptions sE){
		if (sE.GetError() == "SHADOW"){
			cout << "WHOOOP" << endl;
			// snl.ApplyShadowFiltering();
		}
		if (sE.GetError() == "OVEREXPOSED"){
			cout << "WHOOOP" << endl;
			// snl.ApplyShadowFiltering();
		}
	}
	cout << "Shadow and lighting done: ";
	timeKeeper.printTimePast();
	vector<int> t = possibleBlobs[0].getCornerPoints();
	cout << "LT X " << t[0] << " y " << t[1] << endl;
	cout << "RT X " << t[2] << " y " << t[3] << endl;
	cout << "LB X " << t[4] << " y " << t[5] << endl;
	cout << "RB X " << t[6] << " y " << t[7] << endl;

	// Rotation 'n warping
	shared_ptr<ImageRGB> rnw_img_rgb = img;
	shared_ptr<ImageGray> rnw_result;

	try{
		// Gets the img.
		cout << "RNW" << snl_img->height() << endl;
		float tmpCoord[8] = { t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7] };
		ImageCorrection::imageCorrection Correction = ImageCorrection::imageCorrection(tmpCoord);
		rnw_result = Correction.correct(*snl_img.get());
		// Rotates and fixes up the image and cut out the plate.
		string rnw = filename;
		rnw += "RNW.jpg";
		saveImg(*rnw_result, rnw.c_str());
	}
	catch (DistortExceptions &lE){ cout << "RNW ERROR" << endl; }
	cout << "Rotation done: ";
	timeKeeper.printTimePast();


	// OCR 
	try{
		//Finds some letters
		/*cout << "OCR" << endl;
		OCRPatternMatching matching;
		std::cout << "Start recognition of " << filename << std::endl;
		SplitLicensePlate* makeSplit = new SplitLicensePlate(*rnw_result);
		std::vector<ImageGray> characters = makeSplit->SplitImage();

		//char recognition starts here
		std::string kenteken = matching.RecognizeLicenseplate(characters);
		std::cout << "LICENSE PLATE: " << kenteken << std::endl;
		delete makeSplit;*/

		//ORC 2
		cout << "OCR2" << endl;
		/* Controller lines: */
		OpticalCharacterRecognition2 OCR2 = OpticalCharacterRecognition2();
		SegmentedImages Characters = OCR2.SegmentateImage(*rnw_result);
		std::string Licence = OCR2.ReadLicencePlate(Characters);
		cout << Licence << endl;
		//Send back the found letters.
	}
	catch (const std::exception& ex) {
		cout << ex.what() << endl;
	}
	catch (DistortExceptions &lE){ cout << "OCR ERROR" << endl; }
	cout << "Controller finished: ";
	timeKeeper.printTimePast();
}


int main(int argc, char* argv[]){

	//char * filename = (argv[1] == NULL) ? "" : argv[1];
	char * filename = "license_plate_9.jpg";
	//removed license_plate_ex_1.jpg because localisation couldn't find it and programm crashed.
	char * filenames[] = { "license_plate_1.jpg", "license_plate_2.jpg", "license_plate_3.jpg", "license_plate_4.jpg", "license_plate_5.jpg", "license_plate_6.jpg", "license_plate_7.jpg", "license_plate_8.jpg", "license_plate_9.jpg", "license_plate_10.jpg", "license_plate_11.jpg", "license_plate_ex_2.jpg", "license_plate_ex_3.jpg", "license_plate_ex_4.png", "license_plate_ex_5.jpg" };
	/*for (int i = 0; i < 15; i++){
		
		recognition(filenames[i]);
	}*/
	recognition(filename);
	


	system("pause");
}