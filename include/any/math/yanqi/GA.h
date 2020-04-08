#include <math.h>
#include <vector>
#include <bitset>
using namespace std;

#include "..\anymath.h"

#include "boost/function.hpp"

#include "RandomCreate.h"

#define MaxBiteNumberFor1Integer 64  //(����)���������Ʊ����������󳤶�(bit����)
#define MaxVariableNumber 10  //�Ŵ����������������������


struct GA_UserData     //����Ⱥ��ר�����ڱ����û����ݵĽṹ
{
        public:
            int n;
            double *v;
};


//typedef double(*GA_ObjFunction)(int nP, double *P, vector<GA_UserData> UserData);            //����Ŀ�꺯��ֵ���û��Զ��庯��
//typedef bool(*GA_ParametersIsAvailable)(int nx, double *x);   //�жϲ����Ƿ����Ŀ�꺯�����Ƶĺ������û��Զ��庯��
//typedef double(*GA_ObjFunValueToFitness)(int nx, double *x, double ObjFunValue);  //Ŀ�꺯��ֵת��Ϊ��Ӧ��ֵ��ת���������û��Զ��庯��
//typedef int(*GA_CalPrecisionValue)(int nx, double *x, double ObjFunValue, double Fitness, double &PrecisionValue);  //���㾫��ֵ���û��Զ��庯��

typedef boost::function<double (int, double*, std::vector<GA_UserData>&)> GA_ObjFunction;
typedef boost::function<bool (int, double *)> GA_ParametersIsAvailable;
typedef boost::function<double (int, double*, double)> GA_ObjFunValueToFitness;
typedef boost::function<int (int, double*, double, double, double&)> GA_CalPrecisionValue;

//���ж�����Pָ�滮�����ĵ�ǰֵ, nPΪ�滮��������

int GA_BinaryCodingForFloat(double v, double vmin, double vmax, int vprecision, bitset<MaxBiteNumberFor1Integer> &C);
double GA_BinaryUncodingForFloat(double vmin, double vmax, int vprecision, int n, bitset<MaxBiteNumberFor1Integer> C);

int GA_BinaryCodingForPositiveInteger(unsigned int m, bitset<MaxBiteNumberFor1Integer> &C);
unsigned int GA_BinaryUncodingForPositiveInteger(int n, bitset<MaxBiteNumberFor1Integer> C);

struct GA_VariableDescrible     //�Բμ��Ŵ�����ı�������������
{
        public:
            double min, max;  //Ⱥ���и��Ŵ�����������������ȡֵ��Χ
            short int precision;   //Ⱥ���и��Ŵ�����������������ȡֵ����(��Ҫ������С������λ��)
            unsigned int nC;     //�ñ��������Ʊ���ĳ���(����min,max,precision�Ȳ�����������������볤��)
};


struct GA_VariableCoding     //�Ŵ������б����Ķ����Ʊ��뼰������
{
        public:
            double v;   //����ֵ
            bitset<MaxBiteNumberFor1Integer> C;  //���������ڲ�ͬ�Ŵ������У��Ķ����Ʊ���
};


class GA_Individal   //���Ŵ����������
{
    public:
         unsigned long int ID;   //�Ŵ������Ψһ�Ա�ʶ
         double Fitness;  //�Ŵ��������Ӧ��ֵ
         double ObjFunctionValue;  //�Ŵ������Ŀ�꺯��ֵ
         double Prob;     //���Ŵ��������Ӧ��ֵת����(ѡ��)����ֵ
         double AProb;    //���Ŵ��������Ӧ��ֵת����(ѡ��)�ۻ�����ֵ
         GA_VariableCoding *V;  //�Ŵ��������������ĸ�������ֵ����������
         bitset<MaxBiteNumberFor1Integer*MaxVariableNumber> Code;   //�Ŵ��������������ı���ȫ��ֵ�������Ӻ���ܱ���
         int nCode;    //�����ı�����ܳ��ȣ�����GA_VariableDescrible�е�nC֮��, ÿ�������ֵ����ͬ

    GA_Individal(int N){   //NΪ��������
         V = new GA_VariableCoding[N];
         V->C.reset();  //��C�е�����λ��ֵ����Ϊ0
         Code.reset();  //��Code�е�����λ��ֵ����Ϊ0
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
            unsigned long int MaxID;   //��Ⱥ�е�ǰ�Ŵ������Ψһ�Ա�ʶ�����ֵ
            int GAMode;   //�Ŵ�������ʽ: ���������彻�����������(�Ϸ���)�Ӹ���
              //    ��GAMode=0ʱ,�Ӹ��彫ȡ������������ֱ�ӽ�����Ⱥ, ��Ⱥ�еĸ�������ʼ�ձ��ֲ���;
              //    ��GAMode=1ʱ,�Ӹ��彫ֱ����ӵ���Ⱥ��,�������������岻��;  ��Ⱥ�еĸ������������Ͽ�
              //    ��GAMode=2ʱ,�Ӹ�����ֻ����Ӧ�ȱ����������嶼���Ӹ��������Ⱥ�������屣������Ⱥ�в���; ��Ⱥ�еĸ���������������
              //    ��GAMode=3ʱ,4������(2��������,2���Ӹ���)����Ӧ������2����������������Ⱥ��,����2�������򲻽�������Ⱥ��ɾ��, ��Ⱥ�еĸ�������ʼ�ձ��ֲ���;
              //ȱʡģʽ: GAMode=0;

            unsigned int MaxGANum;   //�Ŵ�����������, ȱʡֵ99999
            double Precision;        //�û�Ҫ��ĵ�������, ȱʡֵΪ0.000001;
            std::vector<GA_Individal *> Individal;   //��Ⱥ�е��Ŵ�����
            int nV;  //Ⱥ���и��Ŵ������������ı�������
            double PMutation;    //���巢������ĸ���,ȱʡֵΪ0.01
            std::vector<GA_VariableDescrible *> Vb;  //Ⱥ���и��Ŵ������������ı����Ĳ�������

            std::vector<GA_UserData> UserData;  //�����û�����

            GA_Individal *BestIndividal;

            GA_ObjFunction ObjFun;
            GA_ParametersIsAvailable ParametersIsAvailable;
            GA_ObjFunValueToFitness CalculateFitness;
            GA_CalPrecisionValue CalPrecisionValue;

        GA_Population(){  //NΪȺ���и��������������ı�����
            nV=0;
            MaxGANum=99999;
            Precision = 0.000001;
            PMutation=0.01;
            Individal.clear();
            Vb.clear();
            MaxID=0;
            GAMode=0;
            BestIndividal = NULL;  //�õ�������Ŵ�����
            UserData.clear();
            srand((unsigned) time(NULL));  //��ʼ�������������

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


