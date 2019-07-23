//Opencv C++ Example on Real Time Face Detection from a Video/Webcam Using Haar Cascade
  
/*We can similarly train our own Haar Classifier and Detect any object which we want
Only Thing is we need to load our Classifier in palce of cascade_frontalface_alt2.xml */
//ROS headers
#include <ros/ros.h>
//Centroid message headers
#include <chefbot_facedetection/w_centroid.h>


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
   
#include <iostream>
#include <stdio.h>
   
using namespace std;
using namespace cv;
string cascade_name = "/home/ghostman/ros_dev/catkin_ws/src/chefbot_facedetection/src/haarcascade_upperbody.xml";

int time_delay = 100;
   
int main(int argc,char **argv)
{
    ros::init(argc,argv,"web_cam_detect_node");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<chefbot_facedetection::w_centroid>("/face_centroid",10);
    chefbot_facedetection::w_centroid fc;

   // Load Face cascade (.xml file)
       CascadeClassifier face_cascade;
       face_cascade.load( cascade_name );
       if(!face_cascade.load(cascade_name))
       {
         cerr<<"Error Loading XML file"<<endl;
         return 0;
       }
 
    VideoCapture capture(0);  
    if (!capture.isOpened())  
    throw "Error when reading file";  
    namedWindow("window", 1); 

    ros::Time begin = ros::Time::now();

    for (;;)
     { 
        
        Mat image; 
        capture >> image;  
        if (image.empty())  
        break; 
 
        // Detect faces
        std::vector<Rect> faces;
        face_cascade.detectMultiScale( image, faces, 1.1, 15, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

        if(faces.size() <= 0 ) 
        { 
        	fc.x = 320;fc.y=240;fc.wx=115;
        }
        else
        {
        // Draw circles on the detected faces
        	int face_width_array[faces.size()];

	        for( int i = 0; i < faces.size(); i++ )
	        {
	            Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
	            ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	            
	            face_width_array[i] = faces[i].width;
			}
			// *******************************************************************
			// Sorting (Big) helper variable
			int biggest,c,location = 0;
			int size = faces.size();

			biggest = face_width_array[0];

			for(c=1;c<size;c++)
			{
				if(face_width_array[c] > biggest)
				{
					biggest = face_width_array[c];
					location = c;
				}
			}
			
			//**********************************************************************
			    fc.x = faces[location].x + faces[location].width*0.5;
	        fc.y = faces[location].y + faces[location].width*0.5;
	        fc.wx = faces[location].width;

        }
        imshow( "Detected Face", image );

        
        if(ros::Time::now() - begin >= ros::Duration(0.1))
        {
          //do something
          //ROS_INFO_STREAM(begin);
          pub.publish(fc);
          begin = ros::Time::now();
        }


        if(waitKey(1)==27)
        {
          destroyAllWindows();
          break;
        }  
      }  
                
     return 0;
}