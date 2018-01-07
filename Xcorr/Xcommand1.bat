set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-7.5:7.49988]
set yrange [-8192:122880]
set grid
set title "Waveform"
plot "Xcorr1.plt" with lp
