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

#include "Matrix.hpp"

void Matrix::begin() {
  Serial.println("Initializing the Matrix library...");
  ProtomatterStatus status = _matrix.begin();
  Serial.print("Protomatter begin() status: ");
  Serial.println((int)status);
  if (status != PROTOMATTER_OK) {
    // Reset the MCU in case of a initialization failure
    Serial.println("Matrix library failed to initialize, resetting...");
    delay(5000);
    esp_restart();
  } else {
    Serial.println("Matrix library initialized");
  }
}