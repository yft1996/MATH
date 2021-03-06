/*
 * 日期:	2018-12-1
 * 时间:	10:12
 * 姓名:	安帅
 * @func    矩阵类 矩阵常规运算
*/


#ifndef __MATH_MATRIX_H__
#define __MATH_MATRIX_H__
#include "define.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include "MATH/Matrix/vector.hpp"
#include "matrix_LU.hpp"
#include <MATH/math_define.h>
#include "vector.hpp"
#include "../math_define.h"
using namespace std;
using namespace math::matrix;
MATH_NAMESPACE_BEGIN
MATRIX_NAMESPACE_BEGIN
/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~常用矩阵类型别名声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T, int m ,int n> class Matrix;

    typedef Matrix<int,2,2> Matrix2i;
    typedef Matrix<int,3,3> Matrix3i;
    typedef Matrix<int,3,4> Matrix34i;
    typedef Matrix<int,4,4> Matrix4i;

    typedef Matrix<unsigned int,2,2> Matrix2ui;
    typedef Matrix<unsigned int,3,3> Matrix3ui;
    typedef Matrix<unsigned int,3,4> Matrix34ui;
    typedef Matrix<unsigned int,4,4> Matrix4ui;

    typedef Matrix<float ,2,2> Matrix2f;
    typedef Matrix<float ,3,3> Matrix3f;
    typedef Matrix<float ,3,4> Matrix34f;
    typedef Matrix<float ,4,4> Matrix4f;

    typedef Matrix<double ,2,2> Matrix2d;
    typedef Matrix<double ,3,3> Matrix3d;
    typedef Matrix<double ,3,4> Matrix34d;
    typedef Matrix<double ,4,4> Matrix4d;

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~~Matrix类的声明~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    template <typename T,int m, int n>
    class Matrix
    {
    public:
        typedef shared_ptr<Matrix<T,m,n>> Ptr;
        //声明矩阵行列，static保证必须初始化时给定行列值
        static int constexpr rows = m;
        static int constexpr cols = n;

/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~构造函数与析构函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/


        /*
         *  @property   默认构造函数
         *  @func       对矩阵的rows与cols进行初始化
        */
        Matrix();

        /*
         *  @property   普通构造函数
         *  @func       用存在的矩阵（m*n的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   arr
        */
        explicit Matrix(T const *arr);

        /*
         *  @property   普通构造函数
         *  @func       用value对矩阵（m*n的数组）进行初始化
         *  @exlpicit   防止隐式转换修改成员参数值
         *  @param_in   value
        */
        explicit Matrix(T const value);

        /*
         *  @property   拷贝构造函数
         *  @func       用同一类型的vector1matrix1对矩阵（m*n的数组）进行初始化
         *  @param_in   matrix1
        */
        Matrix(Matrix<T,m,n> const& matrix1);

        /*
         *  @property   拷贝构造函数
         *  @func       用任意类型的matrix1对矩阵（m*n的数组）进行初始化
         *  @param_in   matrix1
        */
        template <typename T1>
        Matrix(Matrix<T1,m,n> const &matrix1);

        /*
         *  @property   析构函数
         *  @func       释放M内存
        */
       // ~Matrix();



/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~~~Matrix迭代器~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
        /*
        *  @property   迭代器
        *  @func       代表矩阵第一个元素的指针
        *  @return     T*
        */
        T* begin();

        /*
        *  @property   迭代器
        *  @func       代表矩阵第一个元素的指针
        *  @const      防止修改返回指针
        *  @const2     防止修改类变量
        *  @return     T const*
        */
        T const* begin() const;

        /*
        *  @property   迭代器
        *  @func       代表矩阵最后一个元素的指针的下一个
        *  @return     T*
        */
        T* end();

        /*
        *  @property   迭代器
        *  @func       代表矩阵最后一个元素的指针的下一个
        *  @const1     防止修改返回指针
        *  @const2     防止修改类变量
        *  @return     T const*
        */
        T const* end() const;


/********************************************************************
 *~~~~~~~~~~~~~~~~~~~~~~~~矩阵运算符重载~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
    public:

        /*
         *  @property   矩阵解引用
         *  @func       对矩阵构成的数组解引用
         *  @return     T*
        */
        T *operator*();

        /*
         *  @property   矩阵解引用
         *  @func       对常矩阵构成的数组解引用
         *  @return     T*
        */
        T const* operator*() const;

        /*
         *  @property   矩阵元素访问
         *  @func       对矩阵元素进行访问matrix（m,n）
         *  @param_in   row     矩阵行索引
         *  @param_in   col     矩阵列索引
         *  @return     T&      避免产生临时变量，返回引用与返回值共用一个地址
        */
        T& operator()(int row,int col);

        /*
         *  @property   常矩阵元素访问
         *  @func       对常矩阵元素进行访问matrix（m,n）
         *  @param_in   row         矩阵行索引
         *  @param_in   col         矩阵列索引
         *  @return     T const&    避免产生临时变量，返回引用与返回值共用一个地址
        */
        T const& operator()(int row, int col) const;

        /*
         *  @property   矩阵元素线性访问
         *  @func       对矩阵元素进行线性访问matrix（i）
         *  @param_in   i       数组表示的矩阵中，数组的索引值
         *  @return     T&      避免产生临时变量，返回引用与返回值共用一个地址
        */
        T& operator[](unsigned int i);

        /*
        *  @property   常矩阵元素线性访问
        *  @func       对常矩阵元素进行线性访问matrix（i）
        *  @param_in   i            数组表示的矩阵中，数组的索引值
        *  @return     T const&     避免产生临时变量，返回引用与返回值共用一个地址
        */
        T const& operator[](unsigned int i) const;
/*
        *  @property   矩阵赋值
        *  @func       矩阵赋值
        *  @param_in   matrix1          原始矩阵
        *  @return     Matrix<T,m,n>&   新矩阵
        */
        virtual Matrix<T,m,n>& operator= (Matrix<T,m,n> const& matrix1);
        /*
        *  @property   矩阵加法
        *  @func       对两个矩阵对应元素进行相加
        *  @param_in   matrix1          被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+= (Matrix<T,m,n> const& matrix1);

        /*
        *  @property   矩阵加法
        *  @func       对两个矩阵对应元素进行相加
        *  @param_in   matrix1          被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        *
        *  const函数返回引用对导致函数外部对数值进行修改，const失效。
        *  二元运算函数内部够造临时变量，对临时变量的引用可能导致数据丢失。
        */
        Matrix<T,m,n> operator+ (Matrix<T,m,n> const& matrix1) const;

        /*
        *  @property   矩阵加法
        *  @func       对矩阵中每个元素加上相同数值
        *  @param_in   value            被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator+= (T const& value);

        /*
        *  @property   矩阵加法
        *  @func       对矩阵中每个元素加上相同数值
        *  @param_in   value            被加矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n> operator+ (T const& value) const;

        /*
        *  @property   矩阵减法
        *  @func       对两个矩阵对应元素进行相减
        *  @param_in   matrix1          被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator-= (Matrix<T,m,n> const& matrix1);

        /*
        *  @property   矩阵减法
        *  @func       对两个矩阵对应元素进行相减
        *  @param_in   matrix1          被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n> operator- (Matrix<T,m,n> const& matrix1) const;

        /*
        *  @property   矩阵减法
        *  @func       对矩阵中每个元素减去相同数值
        *  @param_in   value            被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n>& operator-= (T const& value);

        /*
        *  @property   矩阵减法
        *  @func       对矩阵中每个元素减去相同数值
        *  @param_in   value            被减矩阵
        *  @return     Matrix<T,m,n>&   避免产生临时变量，返回引用与返回值共用一个地址
        */
        Matrix<T,m,n> operator- (T const& value) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)xM(n*l)= M(m*l)
        *  @param_in   matrix1          被乘矩阵
        *  @return     Matrix<T,m,l>    避免产生临时变量，返回引用与返回值共用一个地址
        */
        template <int l>
        Matrix<T,m,l> operator* (const Matrix<T,n,l>& matrix1) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)xV(n*1)= V(m*1)
        *  @param_in   vector1          被乘向量
        *  @return     Matrix<T,m,l>&
        */
        Vector<T,m> operator* (Vector<T,n> const & vector1) const;

        /*
        *  @property   矩阵乘法
        *  @func       M(m*n)*a             原矩阵被改变
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>&
        */
        Matrix<T,m,n>& operator*= (T const& num);

        /*
        *  @property   矩阵乘法               原矩阵不被改变
        *  @func       M(m*n)*a
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>
        */
        Matrix<T,m,n> operator* (T const& num) const;

        /*
        *  @property   矩阵除法
        *  @func       M(m*n)/a             原矩阵被改变
        *  @param_in   T                    被乘数
        *  @return     Matrix<T,m,n>&
        */
        Matrix<T,m,n>& operator/= (T const& num);

        /*
        *  @property   矩阵乘法               原矩阵不被改变
        *  @func       M(m*n)xa
        *  @param_in   T                    被除数
        *  @return     Matrix<T,m,n>
        */
        Matrix<T,m,n> operator/ (T const& num) const;


        /*
        *  @property   重载运算符<<  必须重新定义模板
        *  @func       输出运算符
        *  @param_in   Matrix<T1,m1,n1>&
        *  @param_out  out
        *  @return     ostream &
        */
        template <typename T1,int m1,int n1>
        friend ostream & operator<< (ostream& out,const Matrix<T1,m1,n1>& matrix1);

/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~Matrix管理函数~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
        /*
        *  @property   方阵判断
        *  @func       判断是否为方阵， 是 返回True
        *  @return     bool
        */
        bool is_square() const;

        /*
        *  @property   求最小值
        *  @func       求矩阵最小值
        *  @return     T
        */
        T minimum() const;

        /*
        *  @property   求最大值
        *  @func       求矩阵最大值
        *  @return     T
        */
        T maximum() const;

        /*
        *  @property   求矩阵行
        *  @func       获取矩阵第index行
        *  @return     Vector<T,n>
        */
        Vector<T,n> row(int index) const;

        /*
        *  @property   求矩阵列
        *  @func       获取矩阵第index列
        *  @return     Vector<T,m>
        */
        Vector<T,m> col(int index) const;

        /*
        *  @property   水平矩阵拼接
        *  @func       将原矩阵（左）与新矩阵（右）进行拼接
        *  @param_in   matrix1
        *  @return     Matrix<T,m,n + l>
        */
        template <int l>
        Matrix<T,m,n + l> hstack(Matrix<T,m,l> const& matrix1) const;

        /*
        *  @property   纵向矩阵拼接
        *  @func       将原矩阵（上）与新矩阵（下）进行拼接
        *  @param_in   matrix1
        *  @return     Matrix<T,m,n + l>
        */
        template <int l>
        Matrix<T,m + l,n> vstack(Matrix<T,l,n> const& matrix1) const;

        /*
        *  @property   水平矩阵拼接
        *  @func       将原矩阵（左）与新向量（右）进行拼接
        *  @param_in   vector1
        *  @return     Matrix<T,m,n + 1>
        */
        Matrix<T,m,n + 1> hstack(Vector<T,m> const& vector1) const;

        /*
        *  @property   水平矩阵拼接
        *  @func       将原矩阵（上）与新向量（下）进行拼接
        *  @param_in   vector1
        *  @return     Matrix<T,m + 1,n>
        */
        Matrix<T,m + 1,n> vstack(Vector<T,n> const& vector1) const;

        /*
        *  @property   矩阵行删除
        *  @func       将矩阵第index行删除
        *  @param_in   index
        *  @return     Matrix<T,m - 1,n>
        */
        Matrix<T,m - 1,n> delete_row(int index) const;

        /*
        *  @property   矩阵列删除
        *  @func       将矩阵第index列删除
        *  @param_in   index1
        *  @return     Matrix<T,m,n - 1>
        */
        Matrix<T,m,n - 1> delete_col(int index) const;

        Matrix<T,m,n>& fill(T const& value);


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector一元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:
    /*
    *  @property   求矩阵相反值
    *  @func       将矩阵每个元素求相反数,原向量被改变
    *  @return     Matrix<T,m,n>&
    */
    Matrix<T,m,n>& negate();

    /*
    *  @property   求矩阵相反值
    *  @func       将矩阵每个元素求相反数,原向量不改变
    *  @return     Matrix<T,m,n>
    */
    Matrix<T,m,n> negate_const() const;

    /*
    *  @property   求矩阵转置
    *  @func       将矩阵每个元素进行转置,原向量改变
    *  @return     Matrix<T,m,n>&
    */
    Matrix<T,m,n>& transpose();

    /*
    *  @property   求矩阵转置
    *  @func       将矩阵每个元素进行转置,原向量不改变
    *  @return     Matrix<T,m,n>
    */
    Matrix<T,m,n> transpose_const() const;


/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~~Vector二元运算~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    public:

        bool is_similar(Matrix<T,m,n> const& matrix1, T const& eps) const;


    protected:
        T M[m * n];


    public:



        //先判断为方阵
        void set_identity();


        //TODO(8): 伴随矩阵
        Matrix<T,m,n> adjoint();


        //TODO(9): 逆矩阵
        Matrix<float,m,n> inverse();


        //TODO(10): 矩阵的迹要判断是否为方阵
        int trace();



        //TODO(11): 矩阵范数 用枚举类型
        enum NORM_TYPE{l1,l2};
        int norm(enum NORM_TYPE norm_type);



        //TODO(13): 行列式
        double determiniant();

        //  TODO(14): 矩阵特征值

        // TODO(15): 特征向量

    };



/********************************************************************
*~~~~~~~~~~~~~~~~~~~~~Matrix成员函数实现~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
********************************************************************/
    template <typename T,int m,int n>
    inline
    matrix::Matrix<T,m,n>::Matrix()
    {

    }

    template <typename T,int m, int n>
    inline
    matrix::Matrix<T,m,n>::Matrix(T const *arr)
    {
        std::copy(arr,arr + m * n,M);
    }

    template <typename T, int m, int n>
    inline
    matrix::Matrix<T,m,n>::Matrix(T const value)
    {
        std::fill(M,M + m*n, value);
    }


    template <typename T, int m,int n>
    inline
    Matrix<T,m,n>::Matrix(Matrix<T,m,n> const& matrix1)
    {
        //std::copy(*matrix1, *matrix1 + m * n, M);
        std::copy(matrix1.M, matrix1.M + m * n, M);
    }


    //TODO::函数风险太大，建议删除@AnShuai
    // 函数传参为Matrix<T,m,n>时，若传入Matrix<T1,m,n>，会调用该构造函数
    // 浮点转整形时精度损失,double/int..转char.. 时数据截断

    template <typename T,int m,int n>
    template <typename T1>
    Matrix<T,m,n>::Matrix(Matrix<T1,m,n> const &matrix1)
    {
        std::copy(*matrix1, *matrix1 + m * n, M);
    }

    /*
    template <typename T, int m, int n>
    Matrix<T,m,n>::~Matrix()
    {
        delete []M;
    }
    */


    template <typename T,int m,int n>
    inline T*
    Matrix<T,m,n>::begin (void)
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::begin (void) const
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T*
    Matrix<T,m,n>::end (void)
    {
        return M + m * n;
    }

    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::end (void) const
    {
        return M + m * n;
    }

    //TODO::*Matrix_obj可读性差，构造指针时(*(*Matrix_ptr))才能返回 M
    // 建议用Matrix_obj.data()代替。@anshuai
    template <typename T, int m, int n>
    inline T*
    Matrix<T,m,n>::operator*()
    {
        return M;
    }

    //TODO::*Matrix_obj可读性差，构造指针时(*(*Matrix_ptr))才能返回 M
    // 建议用Matrix_obj.data()代替。@anshuai
    template <typename T,int m,int n>
    inline T const*
    Matrix<T,m,n>::operator*() const
    {
        return M;
    }

    template <typename T,int m,int n>
    inline T&
    Matrix<T,m,n>::operator()(int row,int col)
    {
        if(row>=this->rows||col>=this->cols)
            throw std::invalid_argument("Invalid index");
        return M[row * n + col];
    }
    template <typename T,int m,int n>
    inline T const&
    Matrix<T,m,n>::operator()(int row, int col) const
    {
        if(row>=this->rows||col>=this->cols)
            throw std::invalid_argument("Invalid index");
        return M[row * n + col];
    }

    template <typename T,int m,int n>
    inline T&
    Matrix<T,m,n>::operator[](unsigned int i)
    {
        if(i>=this->rows*this->cols)
            throw std::invalid_argument("Invalid index");
        return M[i];
    }

    template <typename T,int m,int n>
    inline T const&
    Matrix<T,m,n>::operator[](unsigned int i) const
    {
        if(i>=this->rows*this->cols)
            throw std::invalid_argument("Invalid index");
        return M[i];
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator= (Matrix<T,m,n> const& matrix1)
    {
        if(this!=&matrix1)
            std::copy(matrix1.M, matrix1.M + m * n, M);
        return *this;
    }
    //TODO::+=,-=,*等矩阵操作都可能导致数据溢出@anshuai
    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+= (Matrix<T,m,n> const& matrix1)
    {
        std::transform(M,M + m *n, matrix1.M, M, std::plus<T>());
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator+ (Matrix<T,m,n> const& matrix1) const
    {
        Matrix<T,m,n> tmp(*this);
        tmp += matrix1;
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator+= (T const& value)
    {
            for(auto& a : M)
            {
                a+=value;
            }
            return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator+ (T const& value) const
    {
        Matrix<T,m,n>tmp(*this);
        //return tmp+=value; //多调用一次拷贝函数,tmp+=value为右值
        tmp+=value;
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator-= (Matrix<T,m,n> const& matrix1)
    {
        std::transform(M,M + m *n, *matrix1, M, std::minus<T>());
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator- (Matrix<T,m,n> const& matrix1) const
    {
        Matrix<T,m,n> tmp(*this) ;
        tmp -= matrix1;
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator-= (T const& value)
    {
        for(auto& a : M)
        {
            a-=value;
        }
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator- (T const& value) const
    {
        Matrix<T,m,n> tmp(*this) ;
        tmp-=value;
        return tmp;
    }

    //TODO::to be CUDA @YANG
    template <typename T,int m, int n>
    template <int l>
    inline Matrix<T,m,l>
    Matrix<T,m,n>::operator* (const Matrix<T,n,l>& matrix1) const
    {
        Matrix<T,m,l> matrix2 ;

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j <l ; ++j)
            {
                //若需要进行大矩阵相乘，double依然有溢出可能。
                //T sum = 0;
                double sum=0;
                for (int k = 0; k < n; ++k)
                {
                    sum+=M[i*cols+k]*matrix1.M[k*matrix1.cols+j];
                }
                matrix2.M[i*matrix2.cols+j] = sum;
            }
        }
        return matrix2;
    }
    //TODO::to be CUDA @YANG
    template <typename T,int m, int n>
    inline Vector<T,m>
    Matrix<T,m,n>::operator* (Vector<T,n> const& vector1) const
    {
        Vector<T,m> tmp(1);
        for (int i = 0; i < m; ++i)
        {
            tmp[i] = std::inner_product(M + i * n,M + i * n + n,*vector1,T(0));
        }
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator*= (T const& num)
    {
        for(auto& a : this->M)
            a *= num;
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator* (T const& num) const
    {
        Matrix<T,m,n> tmp(*this);
        tmp*=num;
        return tmp;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::operator/= (T const& num)
    {
        for(auto& a : this->M)
            a /= num;
        return *this;
    }

    template <typename T,int m, int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::operator/ (T const& num) const
    {
        Matrix<T,m,n> tmp(*this);
        tmp/=num;
        return tmp;
    }

    template <typename T,int m,int n>
    ostream& operator<< (ostream& out,const Matrix<T,m,n>& matrix1)
    {
        //out<<endl;
        printf("\n");
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                out<<matrix1(i,j)<<" ";
            }
            printf("\n");//out<<endl;
        }
        return out;
    }
    template <typename T, int m,int n>
    inline bool
    Matrix<T,m,n>::is_square() const
    {
        return m == n;
    }

    template <typename T, int m,int n>
    inline T
    Matrix<T,m,n>::minimum() const
    {
        return *std::min_element(M,M + m * n);
    }

    template <typename T, int m,int n>
    inline T
    Matrix<T,m,n>::maximum() const
    {
        return *std::max_element(M,M + m * n);
    }

    template <typename T, int m,int n>
    inline Vector<T,n>
    Matrix<T,m,n>::row(int index) const
    {
        if(index>=m)
            throw("row_index out of range\n");
        return Vector<T,n>(M + n * index);
    }

    template <typename T, int m,int n>
    inline Vector<T,m>
    Matrix<T,m,n>::col(int index) const
    {
        if(index>=n)
            throw("col_index out of range\n");
        int val=0;
        Vector<T,m> tmp(val);//tmp(0)对Vector(T const *arr),Vector(T const &value)存在歧义
        for (int i = 0; i < m ; i ++)
        {
            tmp(i) = M[i*n+index];
        }
        return tmp;
    }

    template <typename T,int m,int n>
    template <int l>
    inline Matrix<T,m,n + l>
    Matrix<T,m,n>::hstack(Matrix<T,m,l> const& matrix1) const
    {
        Matrix<T,m,n + l> matrix2;
        for (int i = 0; i < m; ++i)
        {
            std::copy(M + i * n ,M + (i + 1) * n, *matrix2 + i * (n + l));
            std::copy(*matrix1 + i * l,*matrix1 + (i + 1)* l, *matrix2 + i * (n + l) + n);
        }
        return matrix2;
    }

    template <typename T,int m,int n>
    template <int l>
    inline Matrix<T,m + l,n>
    Matrix<T,m,n>::vstack(Matrix<T,l,n> const& matrix1) const
    {
        Matrix<T,m + l,n> matrix2;
        std::copy(M,M + m *n,*matrix2);
        std::copy(*matrix1,*matrix1 + l * n,*matrix2 + m * n);
        return matrix2;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n + 1>
    Matrix<T,m,n>::hstack(Vector<T,m> const& vector1) const
    {
        Matrix<T,m,n + 1> matrix2;
        for (int i = 0; i < m; ++i)
        {
            std::copy(M + i * n,M + (i + 1) * n,*matrix2 + i*(n + 1));
            matrix2(i,n) = vector1[i];
        }
        return matrix2;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m + 1,n>
    Matrix<T,m,n>::vstack(Vector<T,n> const& vector1) const
    {
        Matrix<T,m + 1,n> matrix2;
        std::copy(M,M + m *n,*matrix2);
        std::copy(*vector1,*vector1 + n,*matrix2 + m* n);
        return matrix2;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m - 1,n>
    Matrix<T,m,n>::delete_row(int index) const
    {
        if(index>=m)
            throw("row_index out of range\n");
        if(m<=1)
            throw("matrix too small\n");
        Matrix<T,m-1,n> matrix1;
        for (int i = 0; i < m; ++i)
        {
            if (i < index)
            {
                std::copy(M + i * n,M + (i + 1) * n,*matrix1 + i * n);
            }
            if(i > index)
            {
                std::copy(M + i * n,M + (i + 1) * n,*matrix1 + (i - 1) * n);
            }
        }
        return matrix1;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n - 1>
    Matrix<T,m,n>::delete_col(int index) const
    {
        if(index>=n)
            throw("col_index out of range\n");
        if(n<=1)
            throw("matrix too small\n");
        Matrix<T,m,n-1> matrix1;
        T* iter = matrix1.begin();
        for (int i = 0; i < m * n; ++i)
        {
            if(i % n != index)
            {
                *iter = M[i];
                iter ++;
            }

        }
        return matrix1;
    }

    template <typename T,int m, int n>
    Matrix<T,m,n>&
    Matrix<T,m,n>::fill(const T &value)
    {
        std::fill(M,M + m * n,value);
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::negate()
    {
        for(auto& a : M)
        {
            a = 0 - a;
        }
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::negate_const() const
    {
        Matrix<T,m,n> tmp(*this);
        tmp.negate();
        return tmp;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>&
    Matrix<T,m,n>::transpose()
    {
        for (int i = 0; i < m; ++i)
        {
            for (int j = i + 1 ; j < n; ++j)
            {
                swap((*this)(i,j),(*this)(j,i));
            }
        }
        return *this;
    }

    template <typename T,int m,int n>
    inline Matrix<T,m,n>
    Matrix<T,m,n>::transpose_const() const
    {
        Matrix<T,m,n> tmp(*this);
        tmp.transpose();
        return tmp;
    }

    template <typename T,int m,int n>
    inline bool
    Matrix<T,m,n>::is_similar(Matrix<T,m,n> const& matrix1, T const& eps) const
    {

    }
    template <typename T,int m,int n>
    void Matrix<T,m,n>::set_identity()
    {
        if (!this->is_square())
        {
            throw runtime_error("该矩阵不为方阵！");
        }

        Matrix<T,m,n> matrix(T(0));
        for (int i = 0; i < m * n; ++i)
            (matrix)[i] = T(1);
    }
    template <typename T,int m,int n>
    Matrix<float,m,n> Matrix<T,m,n>::inverse() {
        Matrix<float,m,n> _mat_inv((T)0);
        if(m!=n)
            return _mat_inv;

       T* mat= this->M;
       float* _arr_inv=*_mat_inv;
       LuSolveInverse<T>(mat,n,_arr_inv);
       return _mat_inv;
    }

    template <typename T,int m,int n>
    double Matrix<T,m,n>::determiniant(){
        if(m!=n)
            return 0;
        double _result = 1;
        double eps=1e-5;
        float *_A=new float[n*n];
        for(int i=0;i<n*n;i++)
            _A[i]=this->M[i];

        if( n == 2 ) {
            _result = _A[0]*_A[3]-_A[1]*_A[2];
        }
        else if( n == 3 )
            _result = _A[0*3+0]*(_A[1*3+1]*_A[2*3+2] - _A[1*3+2]*_A[2*3+1]) -
                    _A[0*3+1]*(_A[1*3+0]*_A[2*3+2] - _A[1*3+2]*_A[2*3+0]) +
                    _A[0*3+2]*(_A[1*3+0]*_A[2*3+1] - _A[1*3+1]*_A[2*3+0]);
        else if( n == 1 )
            _result = _A[0];
        else {
            int i, j, k;
            size_t _astep = m;
            for (i = 0; i < m; i++) {
                k = i;

                for (j = i + 1; j < m; j++)
                    if (std::abs(_A[j * _astep + i]) > std::abs(_A[k * _astep + i]))
                        k = j;

                if (std::abs(_A[k * _astep + i]) < eps) {
                    _result = 0;
                    break;
                }
                if (k != i) {
                    for (j = i; j < m; j++)
                        std::swap(_A[i * _astep + j], _A[k * _astep + j]);
                    _result = -_result;
                }

                float d = -1 / _A[i * _astep + i];
                for (j = i + 1; j < m; j++) {
                    float alpha = _A[j * _astep + i] * d;

                    for (k = i + 1; k < m; k++)
                        _A[j * _astep + k] += alpha * _A[i * _astep + k];

                }
            }
            for(int i=0;i<n;i++)
                _result*=_A[i*n+i];
        }

        delete[] _A;
        return _result;
    }
    template <typename T,int m,int n>
    Matrix<T,m,n> Matrix<T,m,n>::adjoint(){
        Matrix<T,m,n> adj;
        if(m!=n)
            return adj;
        Matrix<float,m,n> inv=this->inverse();
        double det=this->determiniant();

        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++){
                adj(i,j)=det*inv(i,j);
            }
        return adj;
    }
//建议构造matrix子类做vector类
template <typename T,int m>
class VecMat : public Matrix<T,m,1>
{
public:
    VecMat();
    explicit VecMat(T value);
    explicit VecMat(T const* arr);
    explicit VecMat(Matrix<T,m,1>& mat);
    explicit VecMat(VecMat<T,m>& vec);
    VecMat<T,m>& operator=(const VecMat<T,m>& vec);
    VecMat<T,m>& operator=(const Matrix<T,m ,1>& mat);
public:
    int length;

};
template <typename T,int m>
VecMat<T,m>::VecMat():Matrix<T,m,1>()
{
    length=m;
}
template <typename T,int m>
VecMat<T,m>::VecMat(T const*arr):Matrix<T,m,1>(arr) {
    length=m;
}
template <typename T,int m>
VecMat<T,m>::VecMat(T value):Matrix<T,m,1>(value)
{
    length=m;
}

template <typename T,int m>
VecMat<T,m>::VecMat(Matrix<T,m,1>& mat):Matrix<T,m,1>(mat)
{
    length = m;
}
template <typename T,int m>
VecMat<T,m>::VecMat(VecMat<T,m>& vec):Matrix<T,m,1>(vec)
{
    length = m;
}
template <typename T,int m>
VecMat<T,m>& VecMat<T,m>::operator=(const VecMat<T,m>& vec)
{
    if(this!=&vec)
        std::copy(*vec, *vec + m * 1, Matrix<T,m,1>::M);
    return *this;
}
template <typename T,int m>
VecMat<T,m>& VecMat<T,m>::operator=(const Matrix<T,m ,1>& mat)
{
    std::copy(*mat, *mat + m * 1, Matrix<T,m,1>::M);
    return *this;
}
template <typename T,int m,int n>
void PrintMatrix(Matrix<T,m,n>& mat)
{
    int rows=m>10?10:m;
    int cols=n>10?10:n;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            printf( "%.5f  ", mat(y,x));
        }
        printf("\n");
    }
    printf("\n");
}
MATRIX_NAMESPACE_END
MATH_NAMESPACE_END
#endif //__MATH_MATRIX_H__

