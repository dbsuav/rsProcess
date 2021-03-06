#include"RenderProcess.h"

#include"opencv\opencv2\opencv.hpp"
#pragma comment(lib,"opencv_world310d.lib")
using namespace cv;


long LidarTriangleRender(LASSet* lasDataset)
{
	int width = 760, height = 1280;
	Mat img(width, height, CV_8UC3, cv::Scalar(0, 0, 0));
	//最大最小值
	int num = lasDataset->m_numRectangles;
	double minx = DBL_MAX, miny = DBL_MAX, maxx = -DBL_MAX, maxy = -DBL_MAX;
	for (int i = 0; i<num; ++i)
	{
		minx = min(minx, lasDataset->m_lasRectangles[i].m_Rectangle.min[0]);
		maxx = max(maxx, lasDataset->m_lasRectangles[i].m_Rectangle.max[0]);
		miny = min(miny, lasDataset->m_lasRectangles[i].m_Rectangle.min[1]);
		maxy = max(maxy, lasDataset->m_lasRectangles[i].m_Rectangle.max[1]);
	}
	double m_scale = max(double(height) / (maxx - minx), double(width) / (maxy - miny));
	//获取需要显示的三角网
	for (size_t i = 0; i < lasDataset->m_numRectangles; i++)
	{
		int numtriangles = lasDataset->m_lasRectangles[i].m_lasTriangle->nFacets;
		for (size_t j = 0; j < numtriangles; ++j)
		{
			int idx1 = lasDataset->m_lasRectangles[i].m_lasTriangle->pasFacets[j].anVertexIdx[0];
			int idx2 = lasDataset->m_lasRectangles[i].m_lasTriangle->pasFacets[j].anVertexIdx[1];
			int idx3 = lasDataset->m_lasRectangles[i].m_lasTriangle->pasFacets[j].anVertexIdx[2];

			Point2f pnt1 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx1].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx1].m_vec3d.y - miny)*m_scale);
			Point2f pnt2 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx2].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx2].m_vec3d.y - miny)*m_scale);
			cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));
			pnt1 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx2].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx2].m_vec3d.y - miny)*m_scale);
			pnt2 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx3].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx3].m_vec3d.y - miny)*m_scale);
			cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));
			pnt1 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx3].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx3].m_vec3d.y - miny)*m_scale);
			pnt2 = Point2f((lasDataset->m_lasRectangles[i].m_lasPoints[idx1].m_vec3d.x - minx)*m_scale, (lasDataset->m_lasRectangles[i].m_lasPoints[idx1].m_vec3d.y - miny)*m_scale);
			cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));
		}
	}
	imshow("三角网", img);
	waitKey(0);
	return 0;
}

long LidarTriangleRenderGlobal(LASSet* lasDataset, GDALTriangulation* m_triangle)
{
	int width = 760, height = 1280;
	Mat img(width, height, CV_8UC3, cv::Scalar(0, 0, 0));
	//最大最小值
	int num = lasDataset->m_numRectangles;
	double minx = DBL_MAX, miny = DBL_MAX, maxx = -DBL_MAX, maxy = -DBL_MAX;
	for (int i = 0; i<num; ++i)
	{
		minx = min(minx, lasDataset->m_lasRectangles[i].m_Rectangle.min[0]);
		maxx = max(maxx, lasDataset->m_lasRectangles[i].m_Rectangle.max[0]);
		miny = min(miny, lasDataset->m_lasRectangles[i].m_Rectangle.min[1]);
		maxy = max(maxy, lasDataset->m_lasRectangles[i].m_Rectangle.max[1]);
	}

	double m_scale = max(double(height) / (maxx - minx), double(width) / (maxy - miny));
	int totalPoints = 0;
	for (int i = 0; i < lasDataset->m_numRectangles; ++i)
		totalPoints += lasDataset->m_lasRectangles[i].m_lasPoints_numbers;

	//获取需要显示的三角网
	int numtriangles = m_triangle->nFacets;
	for (size_t i = 0; i < numtriangles; i++)
	{
		int idx1 = m_triangle->pasFacets[i].anVertexIdx[0];
		int idx2 = m_triangle->pasFacets[i].anVertexIdx[1];
		int idx3 = m_triangle->pasFacets[i].anVertexIdx[2];
		Point2f pnt1 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx1].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx1].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx1].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx1].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		Point2f pnt2 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx2].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx2].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx2].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx2].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));
		
		pnt1 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx2].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx2].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx2].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx2].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		pnt2 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx3].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx3].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx3].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx3].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));

		pnt1 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx1].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx1].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx1].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx1].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		pnt2 = Point2f((lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx3].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx3].point_idx_inRect].m_vec3d.x - minx)*m_scale,
			(lasDataset->m_lasRectangles[lasDataset->m_LASPointID[idx3].rectangle_idx].m_lasPoints[lasDataset->m_LASPointID[idx3].point_idx_inRect].m_vec3d.y - miny)*m_scale);
		cv::line(img, pnt1, pnt2, Scalar(255, 255, 255));
	}
	imshow("三角网", img);
	waitKey(0);
	return 0;
}