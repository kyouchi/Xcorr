#pragma once
#include <vector>
#include <complex>
#include <functional>
#include <cassert>
#include <chrono>
#include <list>

struct Graph
{
   Graph(const std::vector<double> &x, const std::vector<std::complex<double>> &y);
   Graph(const Graph &obj);
   std::vector<double> x;
   std::vector<std::complex<double>> y;

   Graph operator +(Graph gw) const;

   template<typename T>
   Graph operator *(const T multiple) const;
};

class GenerateWave final
{
   std::vector<double> t_;
   std::vector<std::complex<double>> v_;
   const double fs_;
   const double sec_;
   static constexpr double pi = 3.141592653589793;//円周率

public:
   GenerateWave(double fs, double sec);
   ~GenerateWave();
   GenerateWave(const GenerateWave &obj);

   //tau = 半周期(pi)の長さ
   //a = 波の最大の大きさ
   Graph generateSquare(const double tau, const double a);
   Graph generateTriangle(const double tau, const double a);
   Graph generateSineWave(const double tau, const double a, const double cycle);
   Graph generateSineUnsignedWave(const double tau, const double a, const double cycle);
   Graph generateCosineWave(const double tau, const double a, const double cycle);
   Graph generateCosineUnsignedWave(const double tau, const double a, const double cycle);
   Graph generateCarrierWave(const double fc, const double a);
   Graph generatePow2CosineWave(const double tau, const double a, const double cycle);
   Graph applyRandomNoise(const double random_max);

   //ft = 符号1つのサンプリング周波数(2のべき乗が好ましい)
   Graph generatePrbsWave(const double ft, const std::list<double> &list, const std::function<Graph(double, double)> &fn);

   //getterとsetter
   Graph getGraph() const;
   double getFs() const;
   double getSec() const;
   std::vector<std::complex<double>> getWaveData() const;
   bool setWaveData(const std::vector<std::complex<double>> &p_v);

   //信号をずらす為の関数
   Graph moveAmplitude(const double start_time);

   GenerateWave operator +(GenerateWave &gw) const;

   template<typename T>
   GenerateWave operator *(const T multiple) const;

//Use for FFT
private:
   std::vector<double> output_frequence_;
   std::vector<std::complex<double>> output_amplitude_;

public:
   Graph applyFft();
};


template <typename T>
Graph Graph::operator*(const T multiple) const
{
   //型が数値型ではないので、計算不可
   static_assert(std::is_arithmetic<T>::value, "Typename is not arithmetic.");

   const auto size = this->y.size();

   //コピーを作成
   auto new_gw = *this;

   for (unsigned int i = 0; i < size; ++i)
   {
      new_gw.y[i] = new_gw.y[i] * multiple;
   }

   return new_gw;
}

template <>
inline Graph Graph::operator*<Graph>(Graph gw) const
{
   if (this->x.size() != gw.x.size() || this->y.size() != gw.y.size() || this->x.size() != gw.y.size() || this->y.size() != gw.x.size())
   {
      //xのサイズが違う
      assert(this->x.size() != gw.x.size());
      //yのサイズが違う
      assert(this->y.size() != gw.y.size());

      //xとyでサイズが違う
      assert(this->x.size() != gw.y.size());
      assert(this->y.size() != gw.x.size());
   }

   const auto size = this->x.size();
   //コピーを作成
   std::vector<double> cp_x;
   std::vector<std::complex<double>> cp_y;
   cp_x.resize(this->x.size());
   cp_y.resize(this->y.size());
   Graph output(cp_x, cp_y);

   for (unsigned i = 0; i < size; ++i)
   {
      output.y[i] = this->y[i] * gw.y[i];
   }
   return output;
}

template <typename T>
GenerateWave GenerateWave::operator*(const T multiple) const
{
   //型が数値型ではないので、計算不可
   static_assert(std::is_arithmetic<T>::value, "Typename is not arithmetic.");

   const auto size = this->v_.size();

   //コピーを作成
   auto new_gw = *this;

   for (unsigned int i = 0; i < size; ++i)
   {
      new_gw.v_[i] = new_gw.v_[i] * multiple;
   }

   return new_gw;
}

template <>
inline GenerateWave GenerateWave::operator*<GenerateWave>(GenerateWave gw) const
{
   const auto size = this->v_.size();

   if (size != gw.v_.size() || this->sec_ != gw.sec_ || this->fs_ != gw.fs_)
   {
      //範囲時間が違う
      assert(this->sec_ != gw.sec_);
      //サンプリング周波数が違う
      assert(this->fs_ != gw.fs_);
   }

   //コピーを作成
   auto new_gw = *this;

   for (unsigned int i = 0; i < size; ++i)
   {
      new_gw.v_[i] = new_gw.v_[i] * gw.v_[i];
   }

   return new_gw;
}

//Helper
double getXcorr(Graph& g1, const Graph& g2);
Graph getXcorrEx(const GenerateWave &gw1, GenerateWave &gw2);
