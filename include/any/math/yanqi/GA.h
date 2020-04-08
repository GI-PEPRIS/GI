#include <math.h>
#include <vector>
#include <bitset>
using namespace std;

#include "..\anymath.h"

#include "boost/function.hpp"

#include "RandomCreate.h"

#define MaxBiteNumberFor1Integer 64  //(单个)变量二进制编码允许的最大长度(bit个数)
#define MaxVariableNumber 10  //遗传个体中所允许的最大变量数


struct GA_UserData     //在种群中专门用于保存用户数据的结构
{
        public:
            int n;
            double *v;
};


//typedef double(*GA_ObjFunction)(int nP, double *P, vector<GA_UserData> UserData);            //计算目标函数值的用户自定义函数
//typedef bool(*GA_ParametersIsAvailable)(int nx, double *x);   //判断参数是否符合目标函数限制的函数的用户自定义函数
//typedef double(*GA_ObjFunValueToFitness)(int nx, double *x, double ObjFunValue);  //目标函数值转换为适应度值的转换函数的用户自定义函数
//typedef int(*GA_CalPrecisionValue)(int nx, double *x, double ObjFunValue, double Fitness, double &PrecisionValue);  //计算精度值的用户自定义函数

typedef boost::function<double (int, double*, std::vector<GA_UserData>&)> GA_ObjFunction;
typedef boost::function<bool (int, double *)> GA_ParametersIsAvailable;
typedef boost::function<double (int, double*, double)> GA_ObjFunValueToFitness;
typedef boost::function<int (int, double*, double, double, double&)> GA_CalPrecisionValue;

//上列定义中P指规划变量的当前值, nP为规划变量个数

int GA_BinaryCodingForFloat(double v, double vmin, double vmax, int vprecision, bitset<MaxBiteNumberFor1Integer> &C);
double GA_BinaryUncodingForFloat(double vmin, double vmax, int vprecision, int n, bitset<MaxBiteNumberFor1Integer> C);

int GA_BinaryCodingForPositiveInteger(unsigned int m, bitset<MaxBiteNumberFor1Integer> &C);
unsigned int GA_BinaryUncodingForPositiveInteger(int n, bitset<MaxBiteNumberFor1Integer> C);

struct GA_VariableDescrible     //对参见遗传计算的变量参数的描述
{
        public:
            double min, max;  //群体中各遗传个体所包含变量的取值范围
            short int precision;   //群体中各遗传个体所包含变量的取值精度(需要保留的小数点后的位数)
            unsigned int nC;     //该变量二进制编码的长度(根据min,max,precision等参数所计算出的最大编码长度)
};


struct GA_VariableCoding     //遗传个体中变量的二进制编码及其描述
{
        public:
            double v;   //变量值
            bitset<MaxBiteNumberFor1Integer> C;  //各变量（在不同遗传个体中）的二进制编码
};


class GA_Individal   //对遗传个体的描述
{
    public:
         unsigned long int ID;   //遗传个体的唯一性标识
         double Fitness;  //遗传个体的适应度值
         double ObjFunctionValue;  //遗传个体的目标函数值
         double Prob;     //由遗传个体的适应度值转化的(选择)概率值
         double AProb;    //由遗传个体的适应度值转化的(选择)累积概率值
         GA_VariableCoding *V;  //遗传个体中所包含的各变量的值及其编码参数
         bitset<MaxBiteNumberFor1Integer*MaxVariableNumber> Code;   //遗传个体中所包含的变量全部值编码连接后的总编码
         int nCode;    //变量的编码的总长度，等于GA_VariableDescrible中的nC之和, 每个个体的值都相同

    GA_Individal(int N){   //N为变量个数
         V = new GA_VariableCoding[N];
         V->C.reset();  //把C中的所有位的值设置为0
         Code.reset();  //把Code中的所有位的值设置为0
         Fitness=0;
         Prob=0;
         AProb=0;
    }
    ~GA_Individal(){
         delete[] V;
    }
};

class ANYMATH_CLASS GA_Population
{
        public:
            unsigned long int MaxID;   //种群中当前遗传个体的唯一性标识的最大值
            int GAMode;   //遗传操作方式: 两个父个体交配产生的两个(合法的)子个体
              //    当GAMode=0时,子个体将取代两个父个体直接进入种群, 种群中的个体总数始终保持不变;
              //    当GAMode=1时,子个体将直接添加到种群中,保持两个父个体不变;  种群中的个体总数增长较快
              //    当GAMode=2时,子个体中只有适应度比两个父个体都高子个体进入种群，父个体保留在种群中不变; 种群中的个体总数增长较慢
              //    当GAMode=3时,4个个体(2个父个体,2个子个体)中适应度最大的2个个体进入或保留在种群中,其它2个个体则不进入或从种群中删除, 种群中的个体总数始终保持不变;
              //缺省模式: GAMode=0;

            unsigned int MaxGANum;   //遗传迭代最大次数, 缺省值99999
            double Precision;        //用户要求的迭代精度, 缺省值为0.000001;
            std::vector<GA_Individal *> Individal;   //种群中的遗传个体
            int nV;  //群体中各遗传个体所包含的变量个数
            double PMutation;    //个体发生变异的概率,缺省值为0.01
            std::vector<GA_VariableDescrible *> Vb;  //群体中各遗传个体所包含的变量的参数描述

            std::vector<GA_UserData> UserData;  //储存用户数据

            GA_Individal *BestIndividal;

            GA_ObjFunction ObjFun;
            GA_ParametersIsAvailable ParametersIsAvailable;
            GA_ObjFunValueToFitness CalculateFitness;
            GA_CalPrecisionValue CalPrecisionValue;

        GA_Population(){  //N为群体中各个个体所包含的变量数
            nV=0;
            MaxGANum=99999;
            Precision = 0.000001;
            PMutation=0.01;
            Individal.clear();
            Vb.clear();
            MaxID=0;
            GAMode=0;
            BestIndividal = NULL;  //得到的最佳遗传个体
            UserData.clear();
            srand((unsigned) time(NULL));  //初始化随机数发生器

            CalPrecisionValue=(GA_CalPrecisionValue)NULL;
            ObjFun = (GA_ObjFunction)NULL;
            CalculateFitness = (GA_ObjFunValueToFitness)NULL;
            ParametersIsAvailable = (GA_ParametersIsAvailable)NULL;
        }
        ~GA_Population(){
           int m;

           GA_VariableDescrible *x;
           m = Vb.size();
           for(int i=0; i<m; i++){
               x = Vb[i];
               delete x;
           }
           Vb.clear();

           GA_Individal *y;
           m = Individal.size();
           for(int i=0; i<m; i++){
               y = Individal[i];
               delete y;
           }
           if(BestIndividal != NULL){
               delete BestIndividal;
           }
        }
        int Add_UserData(int n, double *v);
        int CreateInitialPopulation(int n);

        int Add_Variable(double min, double max, short int precision);
        int Add_Individal(double *x);
        int Add_Individal(GA_Individal *Ind);

        void Del_Individal(GA_Individal *Ind);

        void GA_CodingForOneIndividal(GA_Individal *ind);
        void GA_IndividalCodeDividing(GA_Individal *ind);
        void GA_UncodingForOneIndividal(GA_Individal *ind);

        void Main(void);
        void PrepareForGAinterate(void);
        void Reproduction(void);
        void Crossover(GA_Individal *P1, GA_Individal *P2,
                       bitset<MaxBiteNumberFor1Integer*MaxVariableNumber> &C1,
                       bitset<MaxBiteNumberFor1Integer*MaxVariableNumber> &C2);
        void Mutation(GA_Individal *ind);
        void IndividalSelecting(int &P1, int &P2);
        void Cal_IndividalObjFunction(GA_Individal *Ind);
        void Cal_IndividalFitness(GA_Individal *Ind);
        void Cal_IndividalProbability(void);
        bool IndividalIsAvailable(GA_Individal *Ind);
        void GetBestIndividal(void);
        bool IsPrecisionReached(void);

//        void printCode(GA_Individal *Ind);
//        void printIndividal(GA_Individal *Ind);
//        void printPopulation(void);
};


