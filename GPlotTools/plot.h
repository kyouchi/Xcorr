#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <complex>

class Plot
{
protected:
   std::ofstream writing_file_;
   std::ofstream writing_command_file_;

   std::vector<double> x_;
   std::vector<double> y_;
   std::vector<std::complex<double>> y_complex_;
   std::string xlabel_;
   std::string ylabel_;
   std::string graph_title_;
   std::string filename_;
   std::string command_filename_;

   bool printFile();
   bool printFileAbs();
   bool printCommandFile();
   bool printCommandFileAbs();

public:
   Plot(const std::vector<double> x, const std::vector<double> y, const std::string xlabel, const std::string ylabel, const std::string graph_title, const std::string filename, const std::string command_filename);
   Plot(const std::vector<double> x, const std::vector<std::complex<double>> y, const std::string xlabel, const std::string ylabel, const std::string graph_title, const std::string filename, const std::string command_filename);
   ~Plot();

   void executionPlot();
   void executionPlotAbs();
};
