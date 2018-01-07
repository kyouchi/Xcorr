set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-7.5:7.49988]
set yrange [-28672:61440]
set grid
set title "Waveform"
plot "Xcorr3.plt" with lp
