set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-37.5:37.499]
set yrange [-18176:38400]
set grid
set title "Waveform"
plot "Xcorr3.plt" with lp
