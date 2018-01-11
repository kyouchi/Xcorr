set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-37.5:37.499]
set yrange [-7212.73:76674.5]
set grid
set title "Waveform"
plot "Xcorr2.plt" with lp
