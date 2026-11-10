#ifdef NDEBUG
#undef NDEBUG
#endif
#include "q35_scratch_arena.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <random>
#include <stdexcept>
#include <cstdio>
using poly_scratch::plan;
template<size_t N>void check(const std::array<size_t,N>& sz,const std::array<size_t,N>& at,size_t limit){for(size_t i=0;i<N;++i){assert(at[i]%64==0);assert(at[i]<=limit&&sz[i]<=limit-at[i]);for(size_t j=0;j<i;++j)if(sz[i]&&sz[j])assert(at[i]>=at[j]+sz[j]||at[j]>=at[i]+sz[i]);}}
int main(){
 std::array<size_t,6>r={16777216,16777216,8388608,65536,65536,8388608};std::array<size_t,7>a={16777216,8388608,1048576,1048576,1048576,8388608,12681217};auto p=plan(r,a);assert(p.a_size==50462720);assert(p.b_size==49381440);assert(p.total==50462720);assert(p.saved==49381440);check(r,p.a,p.total);check(a,p.b,p.total);
 std::mt19937_64 rng(42);for(int k=0;k<10000;++k){for(auto&v:r)v=rng()%100000;for(auto&v:a)v=rng()%100000;p=plan(r,a);check(r,p.a,p.total);check(a,p.b,p.total);assert(p.total==std::max(p.a_size,p.b_size));assert(p.saved==std::min(p.a_size,p.b_size));}
 r.fill(0);a.fill(0);p=plan(r,a);assert(p.total==0&&p.saved==0);r[0]=std::numeric_limits<size_t>::max();bool threw=false;try{(void)plan(r,a);}catch(const std::overflow_error&){threw=true;}assert(threw);
 r.fill(std::numeric_limits<size_t>::max()/2-127);threw=false;try{(void)plan(r,a);}catch(const std::overflow_error&){threw=true;}assert(threw);
 std::puts("PASS10004 arena fixtures: Tiel geometry, independent-family bounds/disjointness, alignment, empty and overflow");
}
