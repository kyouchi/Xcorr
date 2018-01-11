set encoding utf8
set xl "t[sec]"
set yl "Amplitude"
set xrange [-37.5:37.499]
set yrange [-18307.1:38513.1]
set grid
set title "Waveform"
plot "Xcorr4.plt" with lp
