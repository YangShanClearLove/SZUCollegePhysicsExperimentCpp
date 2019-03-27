#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;
struct Data
{
	double origin;//原始测量数据
	double deal;//消除零刻度误差
	double error;//绝对误差
	 
};
int main()
{
	fstream input("D:\\PhysicsExperiment\\Input.txt");
 
	int times;//测量次数
	double L0;//仪器零点
	double average = 0;//算数平均值，数据期望
	double stdVarience = 0;//标准差
	double uA = 0;//A类标准不确定度，算数平均值的标准差
	double uB = 0;//B类标准不确定度
	double u = 0;//不确定度
	double tp = 0;//tp因子
	double x = 0;//精确到小数点后x位
	string measure;//测量数据的单位 
	string s;//文字缓冲
	input >> s >> times;
	input >> s >> L0;
	input >> s >> tp;
	input >> s >> uB;
	input >> s >> x ;
	input >> s >> measure >> s;
	Data *data = new Data[times];
	int i;
	for (i = 0; i < times; ++i)
	{
		input >> data[i].origin;
		data[i].deal = data[i].origin - L0;
		average += data[i].deal;
	}
	average /= times;
	for (int i = 0; i < times; ++i)
	{
		data[i].error = fabs(data[i].deal - average);
		stdVarience += powf(data[i].error, 2);
	}
	stdVarience = sqrtf(stdVarience / (times - 1));
	uA = stdVarience / sqrtf(times);
	uB = uB / sqrtf(3);
	u = sqrtf(powf(tp*uA, 2) + powf(uB, 2));
	cout << "|序号|   处理数据   | 绝对误差（error）|"<<endl;
	for (int i = 0; i < times; ++i)
	{
		cout << setiosflags(ios::fixed) << setiosflags(ios::right) <<"| " << setw(2) <<i+1<<setprecision(x) << " |  " << setw(7) << data[i].deal << "mm   |    " << setprecision(x)<< data[i].error << "mm    |"<<endl;
	}
	cout << setiosflags(ios::fixed) << setprecision(x);
	cout << "算术平均值： " << average <<" "<< measure << endl;
	cout << "标准差： " << stdVarience << endl;
	cout << "A类标准不确定度uA： " << uA <<" "<< measure <<endl;
	cout << "B类标准不确定度uB： " << uB <<" "<< measure << endl;
	cout << "绝对不确定度u: " << u <<" "<< measure << endl;
	cout << "相对不确定度ur： " << u * 100 / average << "%" << endl;
	cout << "测量结果X： " << average << "±" << u<<" "<< measure <<endl;
	
	input.close();
	char closingApp;
	cout << "测量完成，请按任意键退出。" << endl; 
	cin.get();
	
}
