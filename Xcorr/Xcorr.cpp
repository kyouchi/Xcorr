// Xcorr.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../GPlotTools/plot.h"
#include "../generateWaveHelper/generateWave.h"
#include <memory>
#include <iostream>
#include <list>
#include <thread>


int main()
{
   const auto start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
   const auto fs = 1024;
   std::list<double> list = { -1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1, -1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1, -1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1, -1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1, -1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1};//PN符号

   std::thread th1([&]
   {
      std::cout << "Graph1" << std::endl;
      GenerateWave graph1(fs, static_cast<double>(list.size()));
      const auto fn1 = [&](double tau, double a) {return std::make_unique<GenerateWave>(fs, 1)->generateSquare(tau, a); };
      graph1.generatePrbsWave(fs, list, fn1);
      auto cp_graph1 = graph1;
      const auto graph1_xcorr = getXcorrEx(graph1, cp_graph1);
      Plot(graph1.getGraph().x, graph1.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform1.plt", "command1.bat").executionPlot();
      Plot(graph1_xcorr.x, graph1_xcorr.y, "t[sec]", "Amplitude", "Waveform", "Xcorr1.plt", "Xcommand1.bat").executionPlot();
   });
   std::thread th2([&]
   {
      std::cout << "Graph2" << std::endl;
      GenerateWave graph2(fs, static_cast<double>(list.size()));
      const auto fn2 = [&](double tau, double a) {return std::make_unique<GenerateWave>(fs, 1)->generateSquare(tau, a); };
      graph2.generatePrbsWave(fs, list, fn2);
      auto cp_graph2 = graph2;
      graph2.applyRandomNoise(0.5);
      cp_graph2.applyRandomNoise(0.5);
      const auto graph2_xcorr = getXcorrEx(graph2, cp_graph2);
      Plot(graph2.getGraph().x, graph2.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform2.plt", "command2.bat").executionPlot();
      Plot(graph2_xcorr.x, graph2_xcorr.y, "t[sec]", "Amplitude", "Waveform", "Xcorr2.plt", "Xcommand2.bat").executionPlot();
   });
   std::thread th3([&]
   {
      std::cout << "Graph3" << std::endl;
      GenerateWave graph3(fs, static_cast<double>(list.size()));
      const auto fn3 = [&fs](double tau, double a) {return std::make_unique<GenerateWave>(fs, 1)->generateSineUnsignedWave(tau, a, 1); };
      graph3.generatePrbsWave(fs, list, fn3);
      auto cp_graph3 = graph3;
      const auto graph3_xcorr = getXcorrEx(graph3, cp_graph3);
      Plot(graph3.getGraph().x, graph3.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform3.plt", "command3.bat").executionPlot();
      Plot(graph3_xcorr.x, graph3_xcorr.y, "t[sec]", "Amplitude", "Waveform", "Xcorr3.plt", "Xcommand3.bat").executionPlot();
   });

   std::thread th4([&]
   {
      std::cout << "Graph4" << std::endl;
      GenerateWave graph4(fs, static_cast<double>(list.size()));
      const auto fn4 = [&fs](double tau, double a) {return std::make_unique<GenerateWave>(fs, 1)->generateSineUnsignedWave(tau, a, 1); };
      graph4.generatePrbsWave(fs, list, fn4);
      auto cp_graph4 = graph4;
      graph4.applyRandomNoise(0.5);
      cp_graph4.applyRandomNoise(0.5);
      const auto graph4_xcorr = getXcorrEx(graph4, cp_graph4);
      Plot(graph4.getGraph().x, graph4.getGraph().y, "t[sec]", "Amplitude", "Waveform", "waveform4.plt", "command4.bat").executionPlot();
      Plot(graph4_xcorr.x, graph4_xcorr.y, "t[sec]", "Amplitude", "Waveform", "Xcorr4.plt", "Xcommand4.bat").executionPlot();
   });

   th1.join();
   th2.join();
   th3.join();
   th4.join();

   const auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
   const auto dur = end - start;        // 要した時間を計算
   const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
   std::cout << "AllThreadDone:" << msec << " milli sec \n";
   //Plot(graph2.x, graph2.y, "t[sec]", "Xcorr", "Xcorr", "Xcorr.plt", "Xcorr.bat").executionPlot()   return 0;
}
