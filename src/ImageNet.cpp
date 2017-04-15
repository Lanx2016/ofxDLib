#include "ImageNet.h"
using namespace ofxDLib;

rectangle ImageNet::make_random_cropping_rect_resnet(
    const matrix<rgb_pixel>& img,
    dlib::rand& rnd
)
{
    double mins = 0.466666666, maxs = 0.875;
    auto scale = mins + rnd.get_random_double()*(maxs-mins);
    auto size = scale*std::min(img.nr(), img.nc());
    rectangle rect(size, size);
    point offset(rnd.get_random_32bit_number()%(img.nc()-rect.width()),
		 rnd.get_random_32bit_number()%(img.nr()-rect.height()));
    return move_rect(rect, offset);
}

void ImageNet::randomly_crop_images (
    const matrix<rgb_pixel>& img,
    dlib::array<matrix<rgb_pixel>>& crops,
    dlib::rand& rnd,
    long num_crops
)
{
    std::vector<chip_details> dets;
    for (long i = 0; i < num_crops; ++i)
    {
	auto rect = make_random_cropping_rect_resnet(img, rnd);
	rect_pred.push_back(ofRectangle(rect.left(),rect.top(),rect.width(),rect.height()));
	dets.push_back(chip_details(rect, chip_dims(227,227)));
    }

    extract_image_chips(img, dets, crops);

    for (auto&& img : crops)
    {
	if (rnd.get_random_double() > 0.5) {
	    img = fliplr(img);
	    ofImage xim;
	    toOf(img,xim);
	    image_pred.push_back(xim);
	}
	apply_random_color_offset(img, rnd);
    }
}

void ImageNet::setup(ofImage _ximg, string _resnet )
{
	deserialize(ofToDataPath(_resnet)) >> net >> labels;
	toDLib(_ximg.getPixels(),img);
}

std::vector<std::string> ImageNet::search()
{
	std::vector<std::string> out;
	softmax<anet_type::subnet_type> snet;
	snet.subnet() = net.subnet();
	dlib::array<matrix<rgb_pixel>> images;
	dlib::rand rnd;


	const int num_crops = 16;
	randomly_crop_images(img, images, rnd, num_crops);

	matrix<float,1,1000> p = sum_rows(mat(snet(images.begin(), images.end())))/num_crops;
	for (int k = 0; k < 5; ++k)
	{
	    unsigned long predicted_label = index_of_max(p);
	    out.push_back( ofToString(p(predicted_label)) + ": " + ofToString(labels[predicted_label]) );
	    p(predicted_label) = 0;
	}
	return out;
}

std::vector<ofImage> ImageNet::getImageRandomlyCrop()
{
	return image_pred;
}

std::vector<ofRectangle> ImageNet::getRectRandomlyCrop()
{
	return rect_pred;
}
