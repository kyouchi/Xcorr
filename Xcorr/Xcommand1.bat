set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-37.5:37.499]
set yrange [-7168:76800]
set grid
set title "Waveform"
plot "Xcorr1.plt" with lp
