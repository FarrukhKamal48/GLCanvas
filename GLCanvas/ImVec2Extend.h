#pragma once
#include <GLBox.h>

inline bool operator!=(ImVec2 A, glm::vec2 B) { return A.x!=B.x || A.y!=B.y; }
inline bool operator!=(glm::vec2 A, ImVec2 B) { return A.x!=B.x || A.y!=B.y; }
inline bool operator!=(ImVec2 A, ImVec2 B) { return A.x!=B.x || A.y!=B.y; }

// inline ImVec2 operator+(glm::vec2 A, glm::vec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(ImVec2 A, glm::vec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(glm::vec2 A, ImVec2 B) { return {A.x+B.x, A.y+B.y}; }
inline ImVec2 operator+(ImVec2 A, ImVec2 B) { return {A.x+B.x, A.y+B.y}; }

// inline ImVec2 operator-(glm::vec2 A, glm::vec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(ImVec2 A, glm::vec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(glm::vec2 A, ImVec2 B) { return {A.x-B.x, A.y-B.y}; }
inline ImVec2 operator-(ImVec2 A, ImVec2 B) { return {A.x-B.x, A.y-B.y}; }

// inline ImVec2 operator*(glm::vec2 A, glm::vec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(ImVec2 A, glm::vec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(glm::vec2 A, ImVec2 B) { return {A.x*B.x, A.y*B.y}; }
inline ImVec2 operator*(ImVec2 A, ImVec2 B) { return {A.x*B.x, A.y*B.y}; }

// inline ImVec2 operator/(glm::vec2 A, glm::vec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(ImVec2 A, glm::vec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(glm::vec2 A, ImVec2 B) { return {A.x/B.x, A.y/B.y}; }
inline ImVec2 operator/(ImVec2 A, ImVec2 B) { return {A.x/B.x, A.y/B.y}; }

inline ImVec2 operator*(ImVec2 A, float val) { return {A.x*val, A.y*val}; }
inline ImVec2 operator*(ImVec2 A, int val) { return {A.x*val, A.y*val}; }

inline ImVec2 operator/(ImVec2 A, float val) { return {A.x/val, A.y/val}; }
inline ImVec2 operator/(ImVec2 A, int val) { return {A.x/val, A.y/val}; }
