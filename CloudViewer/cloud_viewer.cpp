#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include "build/quickHull_implementation.h"

int user_data;

void
viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere(o, 0.25, "sphere", 0);
    std::cout << "i only run once" << std::endl;

}

void
viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
    viewer.removeShape("text", 0);
    viewer.addText(ss.str(), 200, 300, "text", 0);

    //FIXME: possible race condition here:
    user_data++;
}
void convertIpair(pcl::PointCloud<pcl::PointXYZRGBA> cloud,vector<iPair> &list)
{
    int len = cloud.size();
    
    for (int i = 0; i < len; i++)
    {
        iPair point;
        point.first = cloud[i].x;
        point.second = cloud[i].y;
      list.push_back(point);

    }
}

int main()
{


    pcl::PointCloud<pcl::PointXYZRGBA> cloud;
    cloud.push_back(pcl::PointXYZRGBA(0,3,0));
    cloud.push_back(pcl::PointXYZRGBA(1,1, 0));
    cloud.push_back(pcl::PointXYZRGBA(2,2, 0));
    cloud.push_back(pcl::PointXYZRGBA(4,4, 0));
    cloud.push_back(pcl::PointXYZRGBA(0,0, 0));
    cloud.push_back(pcl::PointXYZRGBA(1,2, 0));
    cloud.push_back(pcl::PointXYZRGBA(3,1, 0));
    cloud.push_back(pcl::PointXYZRGBA(3,3, 0));
    for (int i = 0; i < 55; i++)
    {
        cloud.push_back(pcl::PointXYZRGBA(i, i, 0));
        cloud.push_back(pcl::PointXYZRGBA(i, -i, 0));
        cloud.push_back(pcl::PointXYZRGBA(-i, i, 0));
        cloud.push_back(pcl::PointXYZRGBA(-i, -i, 0));
    }
    


    vector<iPair> a = { {0, 3}, {1, 1}, {2, 2}, {4, 4},
              {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    vector<iPair> newList;
    convertIpair(cloud, newList);
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudPTR(new pcl::PointCloud<pcl::PointXYZRGBA>);
    *cloudPTR = cloud;


    int n = sizeof(a) / sizeof(a[0]);
    int len = newList.size();
    printHull(newList, len);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    //blocks until the cloud is actually rendered
    viewer.showCloud(cloudPTR);
    viewer.runOnVisualizationThreadOnce(viewerOneOff);
    viewer.runOnVisualizationThread(viewerPsycho);
    while (!viewer.wasStopped())
    {
    }
    return 0;

    /*
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile("ism_test_cat.pcd", *cloud);

    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    //blocks until the cloud is actually rendered
    viewer.showCloud(cloud);

    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer

    //This will only get called once
    viewer.runOnVisualizationThreadOnce(viewerOneOff);

    //This will get called once per visualization iteration
    viewer.runOnVisualizationThread(viewerPsycho);
    while (!viewer.wasStopped())
    {
        //you can also do cool processing here
        //FIXME: Note that this is running in a separate thread from viewerPsycho
        //and you should guard against race conditions yourself...
        user_data++;
    }
    */
    return 0;
}