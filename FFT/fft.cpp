//Source by nurs(http://d.hatena.ne.jp/nurs/20130617/1371483633)
//Mod by FuCrowRabbit

#include "stdafx.h"
#include "fft.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
using namespace std;

int lc_fft_calc_ids(
                    const int N,
                    vector< int >* pids
                    )
{
    // fft 計算前に一度だけ本関数を使いID並び列情報、ids, n_levelを計算しておきます。
    // ここで得られた ids, n_level を、fftの計算で使用します。
    // 配列サイズが変わらない限りids, n_levelは使い回し可能。
    //【入力】N:入力信号配列の大きさ（２のべき乗）
    //【出力】pids:ID並び（呼出時は空を前提）
    //      戻り値: n_level
    int n_level;
    {
        auto& i = n_level;
        for( i=0; i<64; ++i )// マジック★ナンバー！
            if( N>>i == 1) break;
    }
    vector< int >& ids = *pids;
    // ID 並び列の計算
    ids.reserve( N );
    {
        ids.push_back( 0 );
        ids.push_back( 1 );
        for( auto i=0; i<n_level-1; ++i )
        {
            auto sz = ids.size();
            for_each( ids.begin(), ids.end(), [](int& x){ x*=2; } );
            ids.insert( ids.end(), ids.begin(), ids.end() );
            auto it = ids.begin();
            std::advance( it, sz );
            for_each( it, ids.end(), [](int&x){ x+=1; } );
        }// i
    }
    return n_level;
}
void lc_fft(
            const vector< complex<double> >& a,
            const vector< int >& ids,
            const int n_level,
            vector< complex< double > >* pout,
            bool is_inverse/*=0*/
            )
{
    // fft
    // 入力信号 a 数値列の、高速フーリエ変換を行います。
    //【入力】a: 数値列としての離散入力信号、
    //         (a.size()は２のべき乗数であることが大前提)
    //     ids/n_level: 内部使用する情報(lc_fft_calc_iid()の出力)
    //【出力】pout: 数値列としての計算結果。（呼び出し時は空を前提）
    //【オプション】is_inverse：直接は使わないで下さい。
    //      逆変換には、lc_fft_inverse()を使用します。
    auto N = a.size();
    auto& F = *pout;
    {
        F.resize( N );
        for(unsigned i=0; i<N; ++i )
            F[ i ] = a[ids[i]];
    }
    unsigned int po2 = 1;
    for( auto i_level=1; i_level<=n_level; ++i_level )
    {
        po2<<=1;
        const int po2m = po2>>1;
        // 高価なexp()計算呼出は最小回数に抑える。
        auto w =
        exp( std::complex<double>(.0,2*M_PI/static_cast<double>(po2)) );
        // そして逆変換の場合は、wの素を複素共役に。
        w = is_inverse ? conj(w): w;
        auto ws = complex<double>(1,0);
        // バタフライダイヤグラム：Wを共有する項をまとめて計算。
        for( auto k=0; k<po2m; ++k )
        {
            for(unsigned j=0; j<N; j+=po2 )
            {
                auto pa = &F[j+k];
                auto pb = &F[j+k+po2m];
                auto wfb = ws**pb;
                *pb = *pa - wfb;
                *pa += wfb;
            }// j
            ws *= w;
        }// k
    }// i_level
    return;
}
void lc_inverse_fft( const vector< complex<double> >& a,
                    const vector< int >& ids, const int n_level,
                    vector< complex< double > >* pout )
{
    // inverse_fft
    // 入力信号 a 数値列の、高速フーリエ逆変換を行います。
    // a.size()は２のべき乗数であることが大前提です。
    lc_fft( a, ids, n_level, pout, !0 );
    auto N = a.size();
    for_each( pout->begin(), pout->end(),
             [N](complex<double>& val){val/=static_cast<double>(N);} );
    return;
}
