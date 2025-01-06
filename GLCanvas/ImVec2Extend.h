#pragma once
#include <GLBox.h>

template<typename TpA, typename TpB>
inline ImVec2 operator+(TpA A, TpB B) { return ImVec2(A.x+B.x, A.y+B.y); }

template<typename TpA, typename TpB>
inline ImVec2 operator-(TpA A, TpB B) { return ImVec2(A.x-B.x, A.y-B.y); } 

template<typename T>
inline ImVec2 operator*(T vec, float val) { return ImVec2(vec.x*val, vec.y*val); }

template<typename T>
inline ImVec2 operator/(T vec, float val) { return ImVec2(vec.x/val, vec.y/val); }

template<typename TpA, typename TpB>
inline ImVec2 operator*(TpA A, TpB B) { return ImVec2(A.x*B.y, A.y*B.y); }

template<typename TpA, typename TpB>
inline ImVec2 operator/(TpA A, TpB B) { return ImVec2(A.x/B.x, A.y/B.y); }
