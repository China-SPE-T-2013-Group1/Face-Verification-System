vector<Mat> openTrainingSet(string name);

vector<Mat> openTrainingSet(string name)
{
	int imageNumberInt = 1;
	char imageNumberString[4];
	sprintf(imageNumberString, "%d", imageNumberInt);
	Mat image;
	vector<Mat> out;
	image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");		
	
	while (image.data)
	{
		out.push_back(image);
		imageNumberInt++;
		sprintf(imageNumberString, "%d", imageNumberInt);
		image = imread("Training set/" + name + "/" + imageNumberString + ".jpg");
	}

	Mat a;
	return out;
}