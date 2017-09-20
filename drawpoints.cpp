#include <QPainter>
#include <QImage>
#include <QDebug>

#include <vector>

#include <pcl/common/common.h>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>

#include <iostream>
using namespace std;

struct corr{
  double x,y,z;
};

vector<corr> array;

int main(int argc,char** argv){
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::io::loadPCDFile(argv[1],*cloud);
  pcl::PointXYZ minPt, maxPt;

   //获取坐标极值
  pcl::getMinMax3D(*cloud, minPt, maxPt);
  //请按照corr的格式向array填入数据，其坐标值范围为0.0~1500.0
  corr temp;
  int m=(maxPt.x-minPt.x)/0.01;
  int n=(maxPt.y-minPt.y)/0.01;
  for(int i=0;i<cloud->points.size();i++)
  {
    temp.x=2000*(cloud->points[i].x-minPt.x)/(maxPt.x-minPt.x);
    temp.y=1500*(cloud->points[i].y-minPt.y)/(maxPt.y-minPt.y);
    temp.z=1500*(cloud->points[i].z-minPt.z)/(maxPt.z-minPt.z);
    array.push_back(temp);
  }

  QImage image(1500, 2000, QImage::Format_ARGB32);
  QPainter painter(&image);
  image.fill(qRgba(255, 255, 255, 255));
  painter.setPen(qRgb(0,0,0));
  for(vector<corr>::iterator itr=array.begin();itr!=array.end();itr++){
    QPointF p((*itr).y, (*itr).x);
    painter.drawPoint(p);
  }
  image.save("drawpoint2.png");
  return 0;
}
