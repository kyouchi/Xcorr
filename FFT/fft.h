#pragma once
#include <iostream>
#include <vector>
#include <complex>

// fft header
int lc_fft_calc_ids( const int N, std::vector< int >* pids );
void lc_fft(
            const std::vector< std::complex<double> >& a,
            const std::vector< int >& ids, const int n_level,
            std::vector< std::complex< double > >* pout, bool is_inverse=false );
void lc_inverse_fft(
                    const std::vector< std::complex<double> >& a,
                    const std::vector< int >& ids,const int n_level,
                    std::vector< std::complex< double > >* pout );
