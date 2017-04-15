#include "ofxDLib.h"

using namespace dlib;
using namespace std;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2,2,2,2,skip1<tag2<block<N,BN,2,tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block  = BN<con<N,3,3,1,1,relu<BN<con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using level1 = ares<512,ares<512,ares_down<512,SUBNET>>>;
template <typename SUBNET> using level2 = ares<256,ares<256,ares<256,ares<256,ares<256,ares_down<256,SUBNET>>>>>>;
template <typename SUBNET> using level3 = ares<128,ares<128,ares<128,ares_down<128,SUBNET>>>>;
template <typename SUBNET> using level4 = ares<64,ares<64,ares<64,SUBNET>>>;

using anet_type = loss_multiclass_log<fc<1000,avg_pool_everything<
                            level1<
                            level2<
                            level3<
                            level4<
                            max_pool<3,3,2,2,relu<affine<con<64,7,7,2,2,
                            input_rgb_image_sized<227>
                            >>>>>>>>>>>;

namespace ofxDLib {
	class ImageNet {
		public:

		std::vector<string> labels;
		std::vector<ofRectangle> rect_pred;
		std::vector<ofImage> image_pred;
		anet_type net;
		matrix<rgb_pixel> img, crop;

		rectangle make_random_cropping_rect_resnet(const matrix<rgb_pixel>& img,dlib::rand& rnd);
		void randomly_crop_images (const matrix<rgb_pixel>& img,dlib::array<matrix<rgb_pixel>>& crops,dlib::rand& rnd,long num_crops);
		void setup(ofImage _ximg, string _resnet = "resnet34_1000_imagenet_classifier.dnn");
		std::vector<std::string> search();
		std::vector<ofImage> getImageRandomlyCrop();
		std::vector<ofRectangle> getRectRandomlyCrop();
	};
};
