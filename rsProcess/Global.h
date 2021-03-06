#pragma once
#include<string>
#include<vector>
using namespace std;

//目前所有错误都是1，正确结果都返回0，等整个程序完成再对错误代码进行调整

//日志输出路径
//常量的定义
#define _log_path_ "c:\\process_log\\rsProcess.log"
#define PI 3.14159265358
#define MAX_NUM  99999999
#define MIN_NUM -99999999
#define WGS84LRadius 6378137
#define WGS84Eccentricity 0.0066943850
#define EQUAL_LIMIT 0.000001
const double LIMIT = 0.000003;
#define OVER_LIMIT( var) fabs(var)>LIMIT

//数据头信息
typedef struct stDataInfo
{
	unsigned int	nSensorType;
	unsigned int	nSensorOrder;
	unsigned int	nWidths;
	unsigned int	nSamples;
	unsigned int	nLines;
	unsigned int	nBands;
	unsigned int	nYear;
	unsigned int	nMonth;
	unsigned int	nDay;
	unsigned int	nSecond;
	unsigned int	nMode;
	__int64 nHeadOffset;
	__int64 nEofOffset;
}DINFO;

//ENVI头文件格式
struct MapInfo {
	string projection;	//投影
	string directions;  //方向
	double adfGeotransform[6];//坐标信息
	int    zone;
};
typedef struct stImgHeader {
	//影像基本信息
	int imgWidth;
	int imgHeight;
	int imgBands;

	bool byteorder;	//字节顺序 一般是0 对于某些操作系统字节可能由小到大
	int  datatype;

	bool    bimgGeoProjection;	//是否具有投影信息
	MapInfo mapInfo;			//投影字段
	string coordianteSys;	//坐标字段

	string interleave;		//影像排布方式

	//默认显示波段
	bool bimgDefaultBands;
	vector<int> imgDefaultBands;

	//波段名
	bool bimgBandNames;
	vector<string> imgBandNnames;

	//波长信息
	bool bimgWaveLength;
	vector<float> imgWaveLength;

	//半波宽信息
	bool bimgFWHM;
	vector<float> imgFWHM;
}ENVIHeader;

//SBET文件结构
typedef struct stSbetElement
{
	double dGpsTime;
	double dLatitude;
	double dLongitude;
	double dHeight;
	double dVx;
	double dVy;
	double dVz;
	double dRoll;
	double dPitch;
	double dHeading;
	double dWander;
	double dAx;
	double dAy;
	double dAz;
	double dArx;
	double dAry;
	double dArz;
}SBETELEMENT;

//点数据结构的定义
//二维点和三维点数据结构
struct CPOINT
{
	int x;
	int y;
};
struct DPOINT
{
	double dX;
	double dY;
};
struct THREEDPOINT
{
	double dX;
	double dY;
	double dZ;
};


