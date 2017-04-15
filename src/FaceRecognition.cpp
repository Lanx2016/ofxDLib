//
//  FaceRecognition.h
//  example_FaceRecognition
//
//  Created by Dario Longobardi on 15-04-17.
//
//

#include "FaceRecognition.h"
using namespace ofxDLib;

std::vector<matrix<rgb_pixel>> FaceRecognition::jitter_image( const matrix<rgb_pixel>& img )
{
    thread_local random_cropper cropper;
    cropper.set_chip_dims(150,150);
    cropper.set_randomly_flip(true);
    cropper.set_max_object_height(0.99999);
    cropper.set_background_crops_fraction(0);
    cropper.set_min_object_height(0.97);
    cropper.set_translate_amount(0.02);
    cropper.set_max_rotation_degrees(3);

    std::vector<mmod_rect> raw_boxes(1), ignored_crop_boxes;
    raw_boxes[0] = shrink_rect(get_rect(img),3);
    std::vector<matrix<rgb_pixel>> crops;

    matrix<rgb_pixel> temp;
    for (int i = 0; i < 100; ++i)
    {
	cropper(img, raw_boxes, temp, ignored_crop_boxes);
	crops.push_back(move(temp));
    }
    return crops;
}

int FaceRecognition::find(ofPixels p)
{		
	toDLib(p,img);
	fac = detector(img);
	faces.clear();
	for (auto face : fac)
	{
		auto shape = sp(img, face);
		matrix<rgb_pixel> face_chip;
		extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
		faces.push_back(move(face_chip));
	}
	return faces.size();
}

void FaceRecognition::cluster()
{
	if(faces.size() > 0)
	{
		std::vector<matrix<float,0,1>> face_descriptors = net(faces);
		std::vector<sample_pair> edges;
		for (size_t i = 0; i < face_descriptors.size(); ++i)
		{
			for (size_t j = i+1; j < face_descriptors.size(); ++j)
			{
				if (length(face_descriptors[i]-face_descriptors[j]) < 0.6)
					edges.push_back(sample_pair(i,j));
			}
		}
		std::vector<unsigned long> labels;
		const auto num_clusters = chinese_whispers(edges, labels);
		//ofLog()<< "number of people found in the image: "<< num_clusters;
		num_share_cluster = num_clusters;

		std::vector<matrix<rgb_pixel>> temp;
		images_cluster.clear();

		for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
		{
			temp.clear();
			std::vector<ofImage> cluster_temp;
			for (size_t j = 0; j < labels.size(); ++j)
			{
				if (cluster_id == labels[j]) 
				{
					temp.push_back(faces[j]);
					ofImage im;
					toOf(faces[j],im);
					if(im.isAllocated())
					{
						cluster_temp.push_back(im);
					}
				}
			}
			images_cluster.push_back(cluster_temp);
			//ofLog()<<"face cluster " + cast_to_string(cluster_id);
		}
	}
}

int FaceRecognition::getNumClusters()
{
	return num_share_cluster;
}

void FaceRecognition::threadedFunction() 
{
	while(isThreadRunning())
	{
		cluster();
		ofSleepMillis(25);
	}
}

void FaceRecognition::setup(string pred, string recogn)
{
	detector = get_frontal_face_detector();
	deserialize(ofToDataPath(pred)) >> sp;
	deserialize(ofToDataPath(recogn)) >> net;
}

std::vector< std::vector<ofImage> > FaceRecognition::getClusterImages()
{
	return images_cluster;
}

void FaceRecognition::start()
{
	startThread(true);
}

void FaceRecognition::stop()
{
	stopThread();
}
