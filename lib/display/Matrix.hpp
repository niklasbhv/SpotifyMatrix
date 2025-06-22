/**
 *  Copyright 2025 Niklas Meyer
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <Adafruit_Protomatter.h>
#include <Arduino.h>

class Matrix {
 private:
  Adafruit_Protomatter _matrix;

 public:
  Matrix(uint8_t rgbPins[], uint8_t addrPins[], uint8_t clockPin,
         uint8_t latchPin, uint8_t oePin)
      : _matrix(
            64,          // Width of matrix (or matrix chain) in pixels
            4,           // Bit depth, 1-6
            1, rgbPins,  // # of matrix chains, array of 6 RGB pins for each
            4,
            addrPins,  // # of address pins (height is inferred), array of pins
            clockPin, latchPin, oePin,  // Other matrix control pins
            false) {}
  void begin();
};