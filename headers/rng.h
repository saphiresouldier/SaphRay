//-----------------------------------------------------------------------------
/// rng.h: definition of the random number generator functions
//-----------------------------------------------------------------------------

#pragma once

#include <cstdint>

#include "vector.h"

static uint32_t XorShift32(uint32_t& state)
{
  uint32_t x = state;
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 15;
  state = x;
  return x;
}

float RandomFloat01(uint32_t& state)
{
  return (XorShift32(state) & 0xFFFFFF) / 16777216.0f;
}

VECTOR3 RandomInUnitDisk(uint32_t& state)
{
  VECTOR3 p;
  do
  {
    p = VECTOR3(RandomFloat01(state), RandomFloat01(state), 0) - VECTOR3(1, 1, 0) * 2.0;
  } while (p.dot(p) >= 1.0);
  return p;
}

VECTOR3 RandomInUnitSphere(uint32_t& state)
{
  VECTOR3 p;
  do {
    p = VECTOR3(RandomFloat01(state), RandomFloat01(state), RandomFloat01(state)) - VECTOR3(1, 1, 1) * 2.0;
  } while (p.dot(p) >= 1.0);
  return p;
}

VECTOR3 RandomUnitVector(uint32_t& state)
{
  float z = RandomFloat01(state) * 2.0f - 1.0f;
  float a = RandomFloat01(state) * 2.0f * (float)M_PI;
  float r = sqrtf(1.0f - z * z);
  float x = r * cosf(a);
  float y = r * sinf(a);
  return VECTOR3(x, y, z);
}