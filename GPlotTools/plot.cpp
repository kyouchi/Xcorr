#include "stdafx.h"
#include "plot.h"
#include <iostream>
#include <algorithm>
#include <cassert>

bool Plot::printFile()
{
   std::cout << "plot[Info]:" << filename_ << "に書き込んでいます。" << std::endl;

   writing_file_.open(filename_, std::ios::out);
   try
   {
      if (!this->writing_file_.is_open()) throw "指定したファイルが開けませんでした。";
      if (this->x_.size() != this->y_complex_.size()) throw "std::vectorの変数のsizeが違います。";
      if (this->xlabel_.empty()) throw "x軸ラベルが無記名です。";
      if (this->ylabel_.empty()) throw "y軸ラベルが無記名です。";
      if (this->graph_title_.empty()) throw "グラフタイトルが無記名です。";
      if (this->filename_.empty()) throw "ファイル名が無記名です。";
   }
   catch (const char* error)
   {
      std::cout << "plot[Error]:" << error << std::endl;
      return false;
   }

   //ヘッダーの作成
   writing_file_ << "# " << xlabel_ << " " << ylabel_ << " " << std::endl;

   y_.resize(x_.size());
   for (unsigned i = 0; i < x_.size(); ++i)
   {
      y_[i] = y_complex_[i].real();
      writing_file_ << x_[i] << " " << y_[i] << std::endl;
   }

   std::cout << "plot[Info]:" << filename_ << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool Plot::printFileAbs()
{
   std::cout << "plot[Info]:" << filename_ << "に書き込んでいます。" << std::endl;

   writing_file_.open(filename_, std::ios::out);
   try
   {
      if (!this->writing_file_.is_open()) throw "指定したファイルが開けませんでした。";
      if (this->x_.size() != this->y_complex_.size()) throw "std::vectorの変数のsizeが違います。";
      if (this->xlabel_.empty()) throw "x軸ラベルが無記名です。";
      if (this->ylabel_.empty()) throw "y軸ラベルが無記名です。";
      if (this->graph_title_.empty()) throw "グラフタイトルが無記名です。";
      if (this->filename_.empty()) throw "ファイル名が無記名です。";
   }
   catch (const char* Error)
   {
      std::cout << "plot[Error]:" << Error << std::endl;
      return false;
   }

   //ヘッダーの作成
   writing_file_ << "# " << xlabel_ << " " << ylabel_ << " " << std::endl;

   y_.resize(x_.size());
   for (unsigned i = 0; i < x_.size(); ++i)
   {
      y_[i] = abs(y_complex_[i]);
      writing_file_ << x_[i] << " " << y_[i] << std::endl;
   }

   std::cout << "plot[Info]:" << filename_ << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool Plot::printCommandFile()
{
   std::cout << "plot[Info]:GNU Plot用のコマンドファイルを生成します。" << std::endl;
   std::cout << "plot[Info]:" << command_filename_ << "に書き込んでいます。" << std::endl;

   writing_command_file_.open(command_filename_, std::ios::out);
   try
   {
      if (!this->writing_command_file_.is_open()) throw "指定したコマンドファイルが開けませんでした。";
      if (this->command_filename_.empty()) throw "コマンドファイル名が無記名です。";
   }
   catch (const char* error)
   {
      std::cout << "plot[Error]:" << error << std::endl;
      return false;
   }

   //範囲指定
   auto itr = min_element(x_.begin(), x_.end());
   const auto x_min_index = distance(x_.begin(), itr);
   itr = max_element(x_.begin(), x_.end());
   const auto x_max_index = distance(x_.begin(), itr);
   itr = min_element(y_.begin(), y_.end());
   const auto y_min_index = distance(y_.begin(), itr);
   itr = max_element(y_.begin(), y_.end());
   const auto y_max_index = distance(y_.begin(), itr);

   writing_command_file_ << "set encoding utf8" << std::endl;
   writing_command_file_ << "set xl \"" << xlabel_ << "\"" << std::endl;
   writing_command_file_ << "set yl \"" << ylabel_ << "\"" << std::endl;
   writing_command_file_ << "set xrange [" << x_[x_min_index] << ":" << x_[x_max_index] << "]" << std::endl;
   writing_command_file_ << "set yrange [" << y_[y_min_index] << ":" << y_[y_max_index] << "]" << std::endl;
   writing_command_file_ << "set grid" << std::endl;
   writing_command_file_ << "set title \"" << graph_title_ << "\"" << std::endl;
   writing_command_file_ << "plot \"" << filename_ << "\" " << "with lp" << std::endl;

   std::cout << "plot[Info]:" << command_filename_ << "に書き込みが終わりました。" << std::endl;
   return true;
}

bool Plot::printCommandFileAbs()
{
   std::cout << "plot[Info]:GNU Plot用のコマンドファイルを生成します。" << std::endl;
   std::cout << "plot[Info]:" << command_filename_ << "に書き込んでいます。" << std::endl;

   writing_command_file_.open(command_filename_, std::ios::out);
   try
   {
      if (!this->writing_command_file_.is_open()) throw "指定したコマンドファイルが開けませんでした。";
      if (this->command_filename_.empty()) throw "コマンドファイル名が無記名です。";
   }
   catch (const char* error)
   {
      std::cout << "plot[Error]:" << error << std::endl;
      return false;
   }

   //範囲指定
   auto itr = min_element(x_.begin(), x_.end());
   const auto x_min_index = distance(x_.begin(), itr);
   itr = max_element(x_.begin(), x_.end());
   const auto x_max_index = distance(x_.begin(), itr);
   itr = min_element(y_.begin(), y_.end());
   const auto y_min_index = distance(y_.begin(), itr);
   itr = max_element(y_.begin(), y_.end());
   const auto y_max_index = distance(y_.begin(), itr);

   writing_command_file_ << "set encoding utf8" << std::endl;
   writing_command_file_ << "set xl \"" << xlabel_ << "\"" << std::endl;
   writing_command_file_ << "set yl \"" << ylabel_ << "\"" << std::endl;
   writing_command_file_ << "set xrange [" << 0 << ":" << x_[x_max_index] << "]" << std::endl;
   writing_command_file_ << "set yrange [" << 0 << ":" << y_[y_max_index] << "]" << std::endl;
   writing_command_file_ << "set grid" << std::endl;
   writing_command_file_ << "set title \"" << graph_title_ << "\"" << std::endl;
   writing_command_file_ << "plot \"" << filename_ << "\" " << "with lp" << std::endl;

   std::cout << "plot[Info]:" << command_filename_ << "に書き込みが終わりました。" << std::endl;
   return true;
}

Plot::Plot(const std::vector<double> x, const std::vector<double> y, const std::string xlabel, const std::string ylabel, const std::string graph_title, const std::string filename, const std::string command_filename = "command.bat") : x_(x), xlabel_(xlabel), ylabel_(ylabel), graph_title_(graph_title), filename_(filename), command_filename_(command_filename)
{
   this->y_complex_.resize(y.size());
   auto itr = 0;
   for (auto i : y)
   {
      this->y_complex_[itr].real(i);
      itr++;
   }
   return;
}

Plot::Plot(const std::vector<double> x, const std::vector<std::complex<double>> y, const std::string xlabel, const std::string ylabel, const std::string graph_title, const std::string filename, const std::string command_filename) : x_(x), y_complex_(y), xlabel_(xlabel), ylabel_(ylabel), graph_title_(graph_title), filename_(filename), command_filename_(command_filename)
{
   return;
}

Plot::~Plot()
{
}

void Plot::executionPlot()
{
   auto error = this->printFile();
   assert(error);//"printFile()に失敗"
   error = this->printCommandFile();
   assert(error);// "printcommandFile()に失敗"

   std::cout << "plot[Info]:" << "全ての処理を終了" << std::endl;

   //コマンド用batをwgnuplotで開く
   //auto command = "\"C:\\\\Program Files (x86)\\gnuplot\\bin\\wgnuplot.exe\" -persist " + command_filename;
   //if (system(command.c_str())) std::cout << "plot[Error]:" << command.c_str() << " " << "GNU Plotが開けません。" << std::endl;
}

void Plot::executionPlotAbs()
{
   auto error = this->printFileAbs();
   assert(error);//"printFile()に失敗"
   error = this->printCommandFileAbs();
   assert(error);// "printcommandFile()に失敗"

   std::cout << "plot[Info]:" << "全ての処理を終了" << std::endl;

   //コマンド用batをwgnuplotで開く
   //auto command = "\"C:\\\\Program Files (x86)\\gnuplot\\bin\\wgnuplot.exe\" -persist " + command_filename;
   //if (system(command.c_str())) std::cout << "plot[Error]:" << command.c_str() << " " << "GNU Plotが開けません。" << std::endl;
}
